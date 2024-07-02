{ pkgs ? import <nixpkgs> {} }:

pkgs.mkShell {
  name = "objectRotator Nix Shell file";
  buildInputs = with pkgs; [
     cmake
     gcc
     SDL2
  ];
  
  shellHook = ''
   echo "Starting objectRotator development envoriment";
  '';
}
