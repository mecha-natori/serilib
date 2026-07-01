{ inputs, ... }:
{
  imports = [
    (inputs.git-hooks.flakeModule or { })
  ];
  perSystem =
    { config, lib, ... }:
    lib.optionalAttrs (inputs.git-hooks ? flakeModule) {
      pre-commit = {
        check.enable = true;
        settings = {
          hooks = {
            actionlint.enable = false; # treefmt
            clang-format.enable = false; # treefmt
            clang-tidy.enable = true;
            cmake-format.enable = false; # treefmt
            markdownlint = {
              enable = true;
              settings.configuration = {
                MD013 = false;
                MD024 = false;
                MD026 = false;
                MD033 = false;
                MD041 = false;
              };
            };
            mdformat.enable = false; # treefmt
            nil.enable = true;
            nixfmt-rfc-style.enable = false; # treefmt
            treefmt = {
              enable = true;
              package = config.treefmt.build.wrapper;
            };
            yamlfmt.enable = false; # treefmt
            yamllint.enable = false; # treefmt
          };
          src = ../.;
        };
      };
    };
}
