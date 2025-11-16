{ pkgs ? import <nixpkgs> {} }:

pkgs.mkShell {
  buildInputs = [
    pkgs.gcc-arm-embedded
    pkgs.gnumake
    pkgs.git
    pkgs.dfu-util
  ];

  shellHook = ''
    export PATH=$PATH:${pkgs.gcc-arm-embedded}/bin
  '';
}
