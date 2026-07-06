{
  buildNpmPackage,
  fetchFromGitHub,
  nodejs,
}:
buildNpmPackage (finalAttrs: {
  inherit nodejs;
  dontNpmBuild = true;
  npmDepsHash = "sha256-SDgwc4bUYLmSLMk+ZOo5Wfeck5I8luvXfU67A+z9Yzk=";
  patches = [
    ./enable-lock-file.patch
  ];
  pname = "postcss-cli";
  postPatch = ''
    cp "${./package-lock.json}" ./package-lock.json
  '';
  src = fetchFromGitHub {
    hash = "sha256-47OklUatlbunv3FcS816nZhWlbGjeZb7Vg6891fp2Gs=";
    owner = "postcss";
    repo = "postcss-cli";
    rev = finalAttrs.version;
  };
  version = "11.0.1";
})
