{
  description = "Project development environment/Project name";

  inputs = {
    nixpkgs.url = "nixpkgs/nixos-25.11";
  };

  outputs =
    { self, nixpkgs }:
    let
      system = "x86_64-linux";
      pkgs = nixpkgs.legacyPackages.${system};
    in
    {
      devShells.${system}.default = pkgs.pkgsMusl.mkShell {
        packages =
          with pkgs.pkgsMusl;
          [
            # packages here remember to run 'direnv allow' to make it work
            gcc
            gnumake
          ]
          ++ (with pkgs; [
            clang-tools
          ]);

        shellHook = ''
          export PROJECT_ROOT=$(pwd)
          echo "Development environment loaded!"
        '';
      };
    };
}
