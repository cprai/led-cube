
with import <nixpkgs> {};
let
beaglebone_arm = import <nixpkgs> { crossSystem = {
    system = "beaglebone";
    config = "arm-linux-gnueabihf";
    platform = (import <old1903/lib>).systems.platforms.beaglebone;
};};
  #   ti-clpru = import ./ti-clpru.nix;
  #   support-package = import ./support.nix;
in
mkShell {

  name = "rust-env";

  nativeBuildInputs = with buildPackages; [
    vscode
    rustup
    beaglebone_arm.stdenv.cc
    git
  ];

  shellHook = ''
        export RUSTFLAGS="-C linker=arm-linux-gnueabihf-gcc"
    '';
}
