with import<nixpkgs>{};
let ti-clpru = pkgsi686Linux.stdenv.mkDerivation {
      src = fetchurl{
        url = http://software-dl.ti.com/codegen/esd/cgt_public_sw/PRU/2.3.2/ti_cgt_pru_2.3.2_linux_installer_x86.bin;
        sha256 = "06nplns1bsfv763ppc8kln4hpfxy5zfm7w1dczanfvflb6h7h4dg";
      };

      name = "ti_cgt_pru";

      /* src = ./ti_cgt_pru_2.3.2_linux_installer_x86.bin; */

      filename = "ti_cgt_pru_2.3.2_linux_installer_x86.bin";

      nativeBuildInputs = [
          autoPatchelfHook
          file
      ];

      unpackPhase = "false";
      phases = [ "installPhase" ];

      buildInputs = [
      ];
      # builder = ./builder.sh;
      installPhase = ''
      pwd
      cp $src $TMP/$filename
      cd $TMP
      pwd
      ls -la
      mkdir $out
      chmod +x $filename
      chmod +w $filename
      autoPatchelf $filename
      ./$filename
      cp -r $TMP/ti-cgt-pru_2.3.2/* $out
      ls $out

      '';
  };
  /* ti-clpru-libs = pkgsi686Linux.stdenv.mkDerivation{
    name = "ticlpru-libs";
    src = "${ti-clpru}/lib/";
    buildInputs=[autoPatchelfHook ti-clpru];
    installPhase=''
    mkdir -p $TMP/unpack
    cp -r $src/* $TMP/unpack
    cd $TMP/unpack
    autoPatchelf mklib
    chmod +w *
    ./mklib --all
    ls -la
    cd ..
    ls -la
    mkdir $out
    cp -r lib $out
    '';




  }; */
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
    name = "env";
    nativeBuildInputs=[ti-clpru support-package vscode];
    PRU_C_DIR="${ti-clpru}/include/;${ti-clpru}/lib/;${support-package}/";
  }
