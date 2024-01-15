{ nixpkgs, repoRoot }:
rec {
    limine = import ./limine { inherit nixpkgs; };
    kernel = import ./kernel { inherit nixpkgs repoRoot limine; };
}
