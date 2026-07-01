{
  inputs = {
    flake-compat = {
      flake = false;
      url = "github:NixOS/flake-compat";
    };
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
    ms0503-lib = {
      inputs = {
        flake-compat.follows = "";
        flake-parts.follows = "flake-parts";
        git-hooks.follows = "";
        nixpkgs.follows = "nixpkgs";
        treefmt-nix.follows = "";
      };
      url = "github:ms0503/lib.nix";
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
  nixConfig = {
    experimental-features = [
      "flakes"
      "nix-command"
      "pipe-operators"
    ];
    substituters = [
      "https://cache.nixos.org"
      "https://nix-community.cachix.org"
    ];
    trusted-public-keys = [
      "cache.nixos.org-1:6NCHdD59X431o0gWypbMrAURkbJ16ZPMQFGspcDShjY="
      "nix-community.cachix.org-1:mB9FSh9qf2dCimDSUo8Zy7bkq5CX+/rkCWyvRCYg3Fs="
    ];
  };
  outputs =
    inputs@{
      flake-parts,
      ms0503-lib,
      systems,
      ...
    }:
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
          devShells.shell = pkgs.mkShell {
            packages = builtins.concatLists [
              config.pre-commit.settings.enabledPackages
              (config.treefmt.build.programs |> lib.attrValues)
              (with pkgs; [
                (writeScriptBin "clangd" ''
                  #!/usr/bin/env bash
                  exec ${clang-tools}/bin/clangd --query-driver="$(command -v "$CC")" "$@"
                '')
                cmake
                doxygen
                ninja
              ])
              (with pkgs.pkgsCross.armhf-embedded.buildPackages; [
                gcc-arm-embedded
                gdb
              ])
              (with pkgs.pkgsCross.riscv32-embedded.buildPackages; [
                gcc
                gdb
              ])
            ];
            shellHook = ''
              ${config.pre-commit.shellHook}
            '';
          };
          packages =
            # OS環境向け
            rec {
              default = serilib-shared;
              # 静的ライブラリ
              serilib = pkgs.callPackage ./nix/package.nix {
                myLib = ms0503-lib.lib;
                preset = "Release";
                sharedSupport = false;
              };
              # 共有ライブラリ
              serilib-shared = pkgs.callPackage ./nix/package.nix {
                myLib = ms0503-lib.lib;
                preset = "Release";
                sharedSupport = true;
              };
            }
            # Arm(32bit・Soft Float)組み込み向け(クロスコンパイル)
            // {
              # Cortex-M0+
              serilib-arm-m0plus = pkgs.callPackage ./nix/package.nix {
                inherit (pkgs.pkgsCross.arm-embedded) stdenv;
                myLib = ms0503-lib.lib;
                preset = "Release-arm-m0plus";
                sharedSupport = false;
              };
              # Cortex-M3
              serilib-arm-m3 = pkgs.callPackage ./nix/package.nix {
                inherit (pkgs.pkgsCross.arm-embedded) stdenv;
                myLib = ms0503-lib.lib;
                preset = "Release-arm-m3";
                sharedSupport = false;
              };
              # Cortex-M4
              serilib-arm-m4 = pkgs.callPackage ./nix/package.nix {
                inherit (pkgs.pkgsCross.arm-embedded) stdenv;
                myLib = ms0503-lib.lib;
                preset = "Release-arm-m4";
                sharedSupport = false;
              };
            }
            # Arm(32bit・Hard Float)組み込み向け(クロスコンパイル)
            // {
              # Cortex-M4
              serilib-armhf-m4 = pkgs.callPackage ./nix/package.nix {
                inherit (pkgs.pkgsCross.armhf-embedded) stdenv;
                myLib = ms0503-lib.lib;
                preset = "Release-armhf-m4";
                sharedSupport = false;
              };
              # Cortex-M7 (単精度FPU)
              serilib-armhf-m7 = pkgs.callPackage ./nix/package.nix {
                inherit (pkgs.pkgsCross.armhf-embedded) stdenv;
                myLib = ms0503-lib.lib;
                preset = "Release-armhf-m7";
                sharedSupport = false;
              };
              # Cortex-M7 (単精度・倍精度FPU)
              serilib-armhf-m7-double = pkgs.callPackage ./nix/package.nix {
                inherit (pkgs.pkgsCross.armhf-embedded) stdenv;
                myLib = ms0503-lib.lib;
                preset = "Release-armhf-m7-double";
                sharedSupport = false;
              };
              # Cortex-M33
              serilib-armhf-m33 = pkgs.callPackage ./nix/package.nix {
                inherit (pkgs.pkgsCross.armhf-embedded) stdenv;
                myLib = ms0503-lib.lib;
                preset = "Release-armhf-m33";
                sharedSupport = false;
              };
              # Cortex-M55 (単精度FPU)
              serilib-armhf-m55 = pkgs.callPackage ./nix/package.nix {
                inherit (pkgs.pkgsCross.armhf-embedded) stdenv;
                myLib = ms0503-lib.lib;
                preset = "Release-armhf-m55";
                sharedSupport = false;
              };
              # Cortex-M55 (単精度・倍精度FPU)
              serilib-armhf-m55-double = pkgs.callPackage ./nix/package.nix {
                inherit (pkgs.pkgsCross.armhf-embedded) stdenv;
                myLib = ms0503-lib.lib;
                preset = "Release-armhf-m55-double";
                sharedSupport = false;
              };
              # Cortex-M85 (単精度FPU)
              serilib-armhf-m85 = pkgs.callPackage ./nix/package.nix {
                inherit (pkgs.pkgsCross.armhf-embedded) stdenv;
                myLib = ms0503-lib.lib;
                preset = "Release-armhf-m85";
                sharedSupport = false;
              };
              # Cortex-M85 (単精度・倍精度FPU)
              serilib-armhf-m85-double = pkgs.callPackage ./nix/package.nix {
                inherit (pkgs.pkgsCross.armhf-embedded) stdenv;
                myLib = ms0503-lib.lib;
                preset = "Release-armhf-m85-double";
                sharedSupport = false;
              };
            }
            # RISC-V(32bit)組み込み向け(クロスコンパイル)
            // {
              # ESP32-C3
              serilib-riscv32-esp32c3 = pkgs.callPackage ./nix/package.nix {
                inherit (pkgs.pkgsCross.riscv32-embedded) stdenv;
                myLib = ms0503-lib.lib;
                preset = "Release-riscv32-esp32c3";
                sharedSupport = false;
              };
            };
        };
      systems = import systems;
    };
}
