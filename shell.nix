{ pkgs ? import <nixpkgs> {} }:

pkgs.mkShell {
  buildInputs = [
    pkgs.gcc-arm-embedded
    pkgs.gnumake
    pkgs.git
    pkgs.dfu-util
    pkgs.bear
  ];

  shellHook = ''
    export PATH=$PATH:${pkgs.gcc-arm-embedded}/bin
    export C_INCLUDE_PATH=${pkgs.gcc-arm-embedded}/arm-none-eabi/include:$C_INCLUDE_PATH
    bear -- make
  '';
}
