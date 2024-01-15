let
    nixpkgs = import <nixpkgs> {};
in rec {
    pkgs = import ./pkgs { inherit nixpkgs; };
}
