
PORTAUDIO_DIR = ../portaudio
LIBPD_DIR = ../libpd


SRC_FILES = pdtest.c
TARGET = pdtest

CFLAGS = -I$(LIBPD_DIR)/pure-data/src -I$(LIBPD_DIR)/libpd_wrapper -I$(PORTAUDIO_DIR)/include -O3


pdtest:
	ln -s ../libportaudio.so .
	ln -s ../libpd.so .
	$(CC) $(CFLAGS) -o pdtest -lm pdtest.c libpd.so libportaudio.so
