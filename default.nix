(import (
  let
    lock = ./flake.lock |> builtins.readFile |> builtins.fromJSON;
    name = lock.nodes.root.inputs.flake-compat;
  in
  builtins.fetchTarball {
    sha256 = lock.nodes.${name}.locked.narHash;
    url =
      lock.nodes.${name}.locked.url
        or "https://github.com/NixOS/flake-compat/archive/${lock.nodes.${name}.locked.rev}.tar.gz";
  }
) { src = ./.; }).defaultNix
