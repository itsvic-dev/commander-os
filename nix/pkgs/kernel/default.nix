{ nixpkgs, repoRoot, limine }:
let
    stdenv = nixpkgs.pkgs.clangStdenv;
in
stdenv.mkDerivation {
    name = "kernel";
    version = "latest";
    src = repoRoot + "/kernel";

    nativeBuildInputs = with nixpkgs.pkgs; [
        meson ninja
    ];

    mesonFlags = [
        "-Dlimine_inc=${limine}/include"
    ];
}
