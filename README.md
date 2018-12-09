# PostGRES_ext
Spatial database course extension to PostGRES

# Build
Currently the build builds all the implementation files and builds postgres_ext.cpp file which includes all interfaces.

```bash
# Get the repo and setup GMP
git clone [URL]
cd PostGRES_ext
wget https://ftp.gnu.org/gnu/gmp/gmp-6.1.2.tar.xz
tar -xf gmp-6.1.2.tar.xz
cd gmp-6.1.2
./configure --prefix=$HOME/.local --enable-cxx
make
make install
cd ..
# Build PostGRES_ext
make clean
make
./postgres_ext
```

# File structure
*include - Contains all *.h files
*src - Contains all *.cpp files 
*obj - Contains compiled obj code; makefile outputs here
