{
  autoprefixer,
  bash,
  nodejs,
  postcss-cli,
  stdenvNoCC,
  writeScript,
}:
let
  wrapper = writeScript "autoprefixer" ''
    #!${bash}/bin/bash
    set -euo pipefail
    exec "${nodejs}/bin/node" "@out@/lib/node_modules/postcss-cli/index.js" "$@" -u autoprefixer
  '';
in
stdenvNoCC.mkDerivation (finalAttrs: {
  inherit (autoprefixer) version;
  dontUnpack = true;
  installPhase = ''
    runHook preInstall
    mkdir -p "$out/lib/node_modules"
    cp -r "${postcss-cli}/lib/node_modules/"* "$out/lib/node_modules"
    ln -s "${autoprefixer}" "$out/lib/node_modules/autoprefixer"
    mkdir -p "$out/bin"
    substituteAll "${wrapper}" "$out/bin/autoprefixer"
    chmod a+x "$out/bin/autoprefixer"
    runHook postInstall
  '';
  pname = "${autoprefixer.pname}-wrapped";
  src = null;
})
