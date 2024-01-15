{ nixpkgs }:
rec {
    limine = import ./limine { inherit nixpkgs; };
}
