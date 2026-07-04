{
  cmake,
  lib,
  myLib,
  ninja,
  preset,
  sharedSupport,
  stdenv,
}:
let
  inherit (myLib) filters;
  inherit (myLib.build) cleanSourcePipe;
in
stdenv.mkDerivation {
  buildPhase = ''
    runHook preBuild
    cmake --build --preset "$cmakePreset" --parallel "$NIX_BUILD_CORES"
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
    cmake
    ninja
  ];
  outputs = [
    "dev"
    "out"
  ];
  pname = "serilib";
  src = cleanSourcePipe ../. [
    filters.isNotNixDirectory
    filters.isNotNixFiles
  ];
  version = builtins.readFile ../VERSION |> lib.trim;
}
