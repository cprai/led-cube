{nixpkgs}:
with nixpkgs;
pkgsi686Linux.stdenv.mkDerivation {
      src = fetchurl{
        url = http://software-dl.ti.com/codegen/esd/cgt_public_sw/PRU/2.3.2/ti_cgt_pru_2.3.2_linux_installer_x86.bin;
        sha256 = "06nplns1bsfv763ppc8kln4hpfxy5zfm7w1dczanfvflb6h7h4dg";
      };

      system = "x86_64-linux";

      name = "ti_cgt_pru";
      version = "_2.3.2";

      /* src = ./ti_cgt_pru_2.3.2_linux_installer_x86.bin; */

      filename = "ti_cgt_pru_2.3.2_linux_installer_x86.bin";

      nativeBuildInputs = [
          autoPatchelfHook
          file
      ];

      unpackPhase = "false";
      phases = [ "installPhase"];

      NIX_CFLAGS_COMPILE="";

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
      cp -r $TMP/ti-cgt-pru_2.3.2/ $out
      ls $out
      '';
      /* fixupPhase = ''
      PATH=$PATH:$out/ti-cgt-pru_2.3.2/bin
      ''; */
  }
