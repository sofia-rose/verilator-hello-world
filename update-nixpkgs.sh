#!/usr/bin/env bash

set -eu
set -o pipefail

AWK_EXE=${AWK_EXE:-awk}
DATE_EXE=${DATE_EXE:-date}
ECHO_EXE=${ECHO_EXE:-echo}
GIT_EXE=${GIT_EXE:-git}
NIX_PREFETCH_URL_EXE=${NIX_PREFETCH_URL_EXE:-nix-prefetch-url}

GIT_HASH=$("${GIT_EXE}" ls-remote https://github.com/nixos/nixpkgs-channels nixos-unstable | "${AWK_EXE}" "{print \$1}")
TARBALL_URL="https://github.com/nixos/nixpkgs/archive/${GIT_HASH}.tar.gz"
SHA256=$("${NIX_PREFETCH_URL_EXE}" --unpack "${TARBALL_URL}")

{
  "${ECHO_EXE}" "{"
  "${ECHO_EXE}" "  \"name\": \"nixos-unstable-$("${DATE_EXE}" -u '+%Y-%m-%dT%H%M%SZ')\","
  "${ECHO_EXE}" "  \"url\": \"${TARBALL_URL}\","
  "${ECHO_EXE}" "  \"sha256\": \"${SHA256}\""
  "${ECHO_EXE}" "}"
} > nixpkgs.json
