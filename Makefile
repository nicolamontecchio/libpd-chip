all: pdtest
	echo all done



libportaudio.a:
	echo building portaudio
	cd portaudio \
	&& ./configure --host=arm-linux-gnueabihf \
	&& make -j4
	cp portaudio/lib/.libs/libportaudio.so.2.0.0 libportaudio.so
	cp portaudio/lib/.libs/libportaudio.a libportaudio.a

libpd.so:
	echo building libpd
	cd libpd \
	&& CC=arm-linux-gnueabihf-gcc make -j4
	cp libpd/libs/libpd.so .

pdtest: libportaudio.a libpd.so
	echo building pdtest
	cd standalone \
	&& CC=arm-linux-gnueabihf-gcc make
	cp standalone/pdtest .
