# Commander OS

**Commander** is (meant to be) a toy operating system written from scratch.

## Running

Run `nix-shell --run run-commander-vm`. This will build and start a very light Commander OS VM for development purposes.

## Building

To build the EFI FAT image, run `nix-build -A distro.bootImage` in the root of the repo. You'll find the built image in `result/boot.img`.

To build the kernel, run `nix-build -A pkgs.kernel`. You'll find the built kernel in `result/bin/kernel`. To run it, use the Limine bootloader.
