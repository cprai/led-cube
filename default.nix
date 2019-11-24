with import <nixpkgs> {};
let
beaglebone_arm = import <old1903> { 
    crossSystem = {
      system = "beaglebone";
      config = "arm-linux-gnueabihf";
      # platform = (import <old1903/lib>).systems.platforms.beaglebone;
      platform = (import <old1903/lib>).systems.platforms.beaglebone;
    };
};
ti-clpru = pkgs.callPackage_i686 ./ti-clpru.nix {nixpkgs = pkgs;};
support-package = stdenv.mkDerivation{
    src = fetchgit {
      url = git://git.ti.com/pru-software-support-package/pru-software-support-package.git;
      sha256 = "1420jgyli287r1106bzj5yn2vqgh1gfdn9yzaii17bwd9qr0qdd7";
    };
    /* src = fetchgit{
      url = https://github.com/jadonk/pru-software-support-package;
      sha256 = "19pp61ava3h4hx389mw3zqws1a9wj7941mbl05gqw22gg3y26rc4";
    }; */
    name = "support_package";

    /* src = ./ti_cgt_pru_2.3.2_linux_installer_x86.bin; */

    filename = "ti_cgt_pru_2.3.2_linux_installer_x86.bin";

    nativeBuildInputs = [
        autoPatchelfHook
        file
    ];

    /* unpackPhase = "false"; */
    phases = [ "installPhase" ];
    # builder = ./builder.sh;
    installPhase = ''
    mkdir -p $TMP
    cp -r $src/* $TMP
    chmod -R +w $TMP
    mkdir $out
    cp -r include/* $out

    '';
};
in
mkShell{
  name = "rust-env";

  nativeBuildInputs = with buildPackages; [
    vscode
    rustup
    beaglebone_arm.stdenv.cc
    git
    /* ti-clpru */
    ti-clpru
    cmake
    support-package
  ];

  NIX_CFLAGS_COMPILE='''';

  PRU_C_DIR="${ti-clpru}/ti-cgt-pru_2.3.2/include;${ti-clpru}/ti-cgt-pru_2.3.2/lib/;${support-package}/";

  shellHook = ''
        export RUSTFLAGS="-C linker=arm-linux-gnueabihf-gcc"
        for p in $nativeBuildInputs; do
        if [[ "$p" == *"pru"* ]]; then
          PATH=$PATH:$p/ti-cgt-pru_2.3.2/bin
        fi
        done
    '';
}
/* ti-cgt-pru_2.3.2 */
        /* echo $NIX_LDFLAGS */
