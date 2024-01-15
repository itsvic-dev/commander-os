{ repoRoot }:
let
    nixpkgs = import <nixpkgs> {};
in rec {
    pkgs = import ./pkgs { inherit nixpkgs repoRoot; };
    distro = import ./distro { inherit nixpkgs pkgs; };
}
