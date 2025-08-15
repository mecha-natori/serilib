{
  inputs = {
    flake-parts = {
      inputs.nixpkgs-lib.follows = "nixpkgs";
      url = "github:hercules-ci/flake-parts";
    };
    git-hooks = {
      inputs = {
        flake-compat.follows = "";
        nixpkgs.follows = "nixpkgs";
      };
      url = "github:cachix/git-hooks.nix";
    };
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
    systems = {
      flake = false;
      url = "github:nix-systems/default";
    };
    treefmt-nix = {
      inputs.nixpkgs.follows = "nixpkgs";
      url = "github:numtide/treefmt-nix";
    };
  };
  outputs =
    inputs@{ flake-parts, systems, ... }:
    flake-parts.lib.mkFlake { inherit inputs; } {
      imports = [
        ./nix/treefmt.nix
        ./nix/git-hooks.nix
      ];
      perSystem =
        {
          config,
          lib,
          pkgs,
          ...
        }:
        {
          devShells.default = pkgs.mkShell {
            packages =
              config.pre-commit.settings.enabledPackages
              ++ lib.attrValues config.treefmt.build.programs
              ++ (
                with pkgs;
                (
                  [
                    cmake
                    doxygen
                    ninja
                  ]
                  ++ (with pkgsCross.armhf-embedded.buildPackages; [
                    gcc
                  ])
                )
              );
            shellHook = ''
              ${config.pre-commit.installationScript}
            '';
          };
          packages =
            # OS環境向け
            rec {
              serilib = serilib-float-with-shared;
              # 浮動小数:double 静的ライブラリのみ
              serilib-double = pkgs.callPackage ./nix/package.nix {
                primary-fp-type = "double";
                sharedSupport = false;
              };
              # 浮動小数:double 静的ライブラリ・共有ライブラリ
              serilib-double-with-shared = pkgs.callPackage ./nix/package.nix {
                primary-fp-type = "double";
                sharedSupport = true;
              };
              # 浮動小数:float 静的ライブラリのみ
              serilib-float = pkgs.callPackage ./nix/package.nix {
                primary-fp-type = "float";
                sharedSupport = false;
              };
              # 浮動小数:float 静的ライブラリ・共有ライブラリ
              serilib-float-with-shared = pkgs.callPackage ./nix/package.nix {
                primary-fp-type = "float";
                sharedSupport = true;
              };
              # 浮動小数:long double 静的ライブラリのみ
              serilib-long-double = pkgs.callPackage ./nix/package.nix {
                primary-fp-type = "long double";
                sharedSupport = false;
              };
              # 浮動小数:long double 静的ライブラリ・共有ライブラリ
              serilib-long-double-with-shared = pkgs.callPackage ./nix/package.nix {
                primary-fp-type = "long double";
                sharedSupport = true;
              };
            }
            # Arm(32bit・Soft Float)組み込み向け(クロスコンパイル)
            // rec {
              serilib-arm = serilib-arm-float;
              # 浮動小数:double 静的ライブラリのみ
              serilib-arm-double = pkgs.callPackage ./nix/package.nix {
                inherit (pkgs.pkgsCross.arm-embedded) stdenv;
                primary-fp-type = "double";
                sharedSupport = false;
              };
              # 浮動小数:float 静的ライブラリのみ
              serilib-arm-float = pkgs.callPackage ./nix/package.nix {
                inherit (pkgs.pkgsCross.arm-embedded) stdenv;
                primary-fp-type = "float";
                sharedSupport = false;
              };
              # 浮動小数:long double 静的ライブラリのみ
              serilib-arm-long-double = pkgs.callPackage ./nix/package.nix {
                inherit (pkgs.pkgsCross.arm-embedded) stdenv;
                primary-fp-type = "long double";
                sharedSupport = false;
              };
            }
            # Arm(32bit・Hard Float)組み込み向け(クロスコンパイル)
            // rec {
              serilib-armhf = serilib-armhf-float;
              # 浮動小数:double 静的ライブラリのみ
              serilib-armhf-double = pkgs.callPackage ./nix/package.nix {
                inherit (pkgs.pkgsCross.armhf-embedded) stdenv;
                primary-fp-type = "double";
                sharedSupport = false;
              };
              # 浮動小数:float 静的ライブラリのみ
              serilib-armhf-float = pkgs.callPackage ./nix/package.nix {
                inherit (pkgs.pkgsCross.armhf-embedded) stdenv;
                primary-fp-type = "float";
                sharedSupport = false;
              };
              # 浮動小数:long double 静的ライブラリのみ
              serilib-armhf-long-double = pkgs.callPackage ./nix/package.nix {
                inherit (pkgs.pkgsCross.armhf-embedded) stdenv;
                primary-fp-type = "long double";
                sharedSupport = false;
              };
            }
            # Risc-V(32bit)組み込み向け(クロスコンパイル)
            // rec {
              serilib-riscv32 = serilib-riscv32-float;
              # 浮動小数:double 静的ライブラリのみ
              serilib-riscv32-double = pkgs.callPackage ./nix/package.nix {
                inherit (pkgs.pkgsCross.riscv32-embedded) stdenv;
                primary-fp-type = "double";
                sharedSupport = false;
              };
              # 浮動小数:float 静的ライブラリのみ
              serilib-riscv32-float = pkgs.callPackage ./nix/package.nix {
                inherit (pkgs.pkgsCross.riscv32-embedded) stdenv;
                primary-fp-type = "float";
                sharedSupport = false;
              };
              # 浮動小数:long double 静的ライブラリのみ
              serilib-riscv32-long-double = pkgs.callPackage ./nix/package.nix {
                inherit (pkgs.pkgsCross.riscv32-embedded) stdenv;
                primary-fp-type = "long double";
                sharedSupport = false;
              };
            };
        };
      systems = import systems;
    };
}
