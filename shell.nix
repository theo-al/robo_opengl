{ pkgs ? import <nixpkgs> {} }:

pkgs.mkShell {
  packages = with pkgs; [
    gcc gnumake

    libGL libGLU freeglut
  ];
}

