{
  cmake,
  lib,
  mold,
  ninja,
  primary-fp-type,
  sharedSupport,
  stdenv,
}:
stdenv.mkDerivation {
  cmakeFlags = [
    "-DCMAKE_EXE_LINKER_FLAGS=-fuse-ld=mold"
    "-DCMAKE_SHARED_LINKER_FLAGS=-fuse-ld=mold"
    "-DSERI_PRIMARY_FP_TYPE=${primary-fp-type}"
    "-DSERI_USE_SHARED=${if sharedSupport then "1" else "0"}"
  ];
  meta = {
    homepage = "https://github.com/mecha-natori/serilib#readme";
    license = lib.licenses.mit;
    sourceProvenance = with lib.sourceTypes; [
      fromSource
    ];
  };
  nativeBuildInputs = [
    cmake
    mold
    ninja
  ];
  outputs = [
    "dev"
    "out"
  ];
  pname = "serilib";
  src = ../.;
  version = "0.1.0";
}
