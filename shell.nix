{ pkgs ? import <nixpkgs> {} }:

pkgs.mkShell {
  name = "objectsRotator Nix Shell file";
  buildInputs = with pkgs; [
     cmake
     gcc
     SDL2
  ];
  
  shellHook = ''
   echo "Starting objectsRotator development ENV";
  '';
}
