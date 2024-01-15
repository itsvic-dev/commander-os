# Simple shell that exposes the QEMU VM
let
    mkShell = (import <nixpkgs> {}).pkgs.mkShell;
    qemuRun = (import ./.).distro.qemuRun;
in
mkShell {
    build = "commander-qemu-shell";
    buildInputs = [ qemuRun ];
}
