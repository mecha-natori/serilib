{
  callPackage,
  cmake,
  doxygen,
  lib,
  mdbook,
  myLib,
  ninja,
  preset,
  sharedSupport,
  stdenv,
}:
let
  inherit (myLib) filters;
  inherit (myLib.build) cleanSourcePipe;
  autoprefixer = callPackage ./autoprefixer.nix {
    postcss-cli = callPackage ./postcss-cli { };
  };
in
stdenv.mkDerivation {
  buildPhase = ''
    runHook preBuild

    # Build library
    cmake --build --preset "$cmakePreset" --parallel "$NIX_BUILD_CORES"

    # Build documents
    pushd ./docs
    tmp=$(mktemp)
    autoprefixer ./root/style.css -o "$tmp"
    mv "$tmp" ./root/style.css
    unset tmp
    doxygen
    mv ./apidocs/html ./root/apidocs
    pushd ./manual
    mdbook build
    popd
    mv ./manual/book ./root/manual
    popd

    runHook postBuild
  '';
  cmakeBuildDir = "build/${preset}";
  cmakePreset = preset;
  configurePhase = ''
    runHook preConfigure
    cmake --preset "$cmakePreset" \
      -DCMAKE_INSTALL_PREFIX="$out" \
      -DSERI_USE_SHARED=${if sharedSupport then "1" else "0"}
    runHook postConfigure
  '';
  installPhase = ''
    runHook preInstall
    cmake --install "$cmakeBuildDir"
    install -dm755 "$doc/share/doc"
    cp -r ./docs/root/* "$doc/share/doc/"
    runHook postInstall
  '';
  meta = {
    homepage = "https://github.com/mecha-natori/serilib#readme";
    license = lib.licenses.mit;
    sourceProvenance = with lib.sourceTypes; [
      fromSource
    ];
  };
  nativeBuildInputs = [
    autoprefixer
    cmake
    doxygen
    mdbook
    ninja
  ];
  outputs = [
    "dev"
    "doc"
    "out"
  ];
  pname = "serilib";
  src = cleanSourcePipe ../. [
    filters.isNotNixDirectory
    filters.isNotNixFiles
  ];
  version = builtins.readFile ../VERSION |> lib.trim;
}
