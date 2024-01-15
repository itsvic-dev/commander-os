{ nixpkgs }:
let
    pkgs = nixpkgs.pkgs;
in
pkgs.stdenv.mkDerivation rec {
    name = "limine";
    version = "7.0.0";

    src = fetchTarball {
        url = "https://github.com/limine-bootloader/limine/releases/download/v7.0.0/limine-7.0.0.tar.xz";
        sha256 = "sha256:1ipx5d8lrsccr1i5gvjsdyyiq9blrzy6j2xdb53kdj54r372sa2i";
    };

    configureFlags = [
        "--enable-uefi-x86-64"
    ];

    buildInputs = with pkgs; [ nasm ];
}