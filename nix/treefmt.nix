{ inputs, ... }:
{
  imports = [
    (inputs.treefmt-nix.flakeModule or { })
  ];
  perSystem =
    { lib, pkgs, ... }:
    lib.optionalAttrs (inputs.treefmt-nix ? flakeModule) {
      treefmt.programs = {
        actionlint.enable = true;
        clang-format.enable = true;
        cmake-format = {
          enable = true;
          excludes = [
            "**/CMakeLists.txt"
          ];
        };
        mdformat = {
          enable = true;
          plugins =
            ps: with ps; [
              mdformat-gfm
            ];
          settings = {
            end-of-line = "lf";
            number = true;
            wrap = 80;
          };
        };
        nixfmt.enable = true;
        yamlfmt.enable = false;
        yamllint.enable = true;
      };
    };
}
