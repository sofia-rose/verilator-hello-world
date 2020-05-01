let
  nixpkgs = import
    (builtins.fetchTarball
      (builtins.fromJSON
        (builtins.readFile ./nixpkgs.json)))
  {};
in
  nixpkgs.mkShell {
    buildInputs = [
      nixpkgs.cmake
      nixpkgs.gtkwave
      nixpkgs.ninja
      nixpkgs.verilator
    ];
  }
