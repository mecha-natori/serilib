{ inputs, ... }:
{
  imports = [
    inputs.treefmt-nix.flakeModule
  ];
  perSystem =
    { pkgs, ... }:
    {
      treefmt = {
        programs = {
          actionlint.enable = true;
          clang-format.enable = true;
          cmake-format.enable = true;
          mdformat = {
            enable = true;
            package = pkgs.mdformat.withPlugins (
              ps: with ps; [
                mdformat-gfm
              ]
            );
            settings = {
              end-of-line = "lf";
              number = true;
              wrap = 80;
            };
          };
          nixfmt.enable = true;
          yamlfmt.enable = true;
        };
        settings.formatter.cmake-format.includes = [
          "**/CMakeLists.txt"
        ];
      };
    };
}
