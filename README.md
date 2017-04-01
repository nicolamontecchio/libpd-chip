# libpd-chip
running libpd on ntc chip

## building

first download ALSA, build and install it in the

	wget ftp://ftp.alsa-project.org/pub/lib/alsa-lib-1.1.3.tar.bz2
	tar -jxvf alsa-lib-1.1.3.tar.bz2
	cd alsa-lib-1.1.3
	./configure --host arm-linux-gnueabihf --prefix=/usr/arm-linux-gnueabihf
	make
	sudo make install

then build the code; portaudio will pick up ALSA as the default backend

    git submodule update --init --recursive
    cd minimal-standalone/pdtest
    make

## running

	sudo apt-get install libportaudio2
	./pdtest test.pd .
