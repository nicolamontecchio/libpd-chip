# libpd-chip
running libpd on ntc chip

## building

    git submodule update --init --recursive
    cd minimal-standalone/pdtest
    make

## running
    
    LD_LIBRARY_PATH=../../portaudio/lib/.libs/ ./pdtest test.pd .
    
or run `make install` in `/portaudio`, then it's just `./pdtest test.pd`

