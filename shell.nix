# Simple shell that exposes the QEMU VM
let
    mkShell = (import <nixpkgs> {}).pkgs.mkShell;
    commander = import ./.;
in
mkShell {
    build = "commander-qemu-shell";
    buildInputs = [ commander.distro.qemuRun ];
    shellHook = ''
        export LIMINE_INC=${commander.pkgs.limine}/include
    '';
}
