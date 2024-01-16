{ pkgs, nixpkgs }:
rec {
    # Builds a FAT32 boot image for qemuRun.
    bootImage = let
        # built binaries
        kernelElf = "${pkgs.kernel}/bin/kernel";
        bootx64 = "${pkgs.limine}/share/limine/BOOTX64.EFI";
        # limine config
        limineCfg = nixpkgs.pkgs.writeText "limine.cfg" ''
            TIMEOUT=1

            :Commander OS
                PROTOCOL=limine
                KERNEL_PATH=boot:///kernel
        '';
    in nixpkgs.pkgs.runCommand "bootImage" {
        buildInputs = [ nixpkgs.pkgs.mtools ];
    } ''
        dd if=/dev/zero of=boot.img bs=1M count=16
        mformat -i boot.img ::
        mcopy -i boot.img ${limineCfg} ::/limine.cfg
        mcopy -i boot.img ${kernelElf} ::/kernel
        mmd -i boot.img ::/EFI
        mmd -i boot.img ::/EFI/BOOT
        mcopy -i boot.img ${bootx64} ::/EFI/BOOT/BOOTX64.EFI
        mkdir -p $out
        cp boot.img $out
    '';

    # `run-commander-vm` script which launches a QEMU VM with OVMF.
    qemuRun = let
        qemu = "${nixpkgs.pkgs.qemu}/bin/qemu-kvm";
        startScript = ''
            #!${nixpkgs.pkgs.runtimeShell}

            exec ${qemu} -cpu max -drive file=${nixpkgs.pkgs.OVMF.fd}/FV/OVMF.fd,if=pflash,readonly=on \
                -drive file=${bootImage}/boot.img,if=virtio,readonly=on -m 256M
        '';
    in nixpkgs.pkgs.runCommand "commander-vm" {} ''
        mkdir -p $out/bin
        ln -s ${nixpkgs.pkgs.writeScript "run-commander-vm" startScript} $out/bin/run-commander-vm
    '';
}
