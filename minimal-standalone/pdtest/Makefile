# detect platform, move libpd dylib to local folder on mac
UNAME = $(shell uname)
SOLIB_PREFIX = lib

ifeq ($(UNAME), Darwin)  # Mac
  SOLIB_EXT = dylib
  PDNATIVE_PLATFORM = mac
else
  ifeq ($(OS), Windows_NT)  # Windows, use Mingw
    SOLIB_EXT = dll
    PDNATIVE_PLATFORM = windows
  else  # Assume Linux
    SOLIB_EXT = so
    PDNATIVE_PLATFORM = linux
  endif
endif

LIBPD_DIR = ../../libpd
LIBPD = $(LIBPD_DIR)/libs/libpd.$(SOLIB_EXT)

PORTAUDIO_DIR = ../../portaudio
PORTAUDIO = $(PORTAUDIO_DIR)/lib/.libs/libportaudio.$(SOLIB_EXT)

SRC_FILES = pdtest.c
TARGET = pdtest

CFLAGS = -I$(LIBPD_DIR)/pure-data/src -I$(LIBPD_DIR)/libpd_wrapper -I$(PORTAUDIO_DIR)/include -O3

.PHONY: clean clobber

$(TARGET): ${SRC_FILES:.c=.o} $(LIBPD) $(PORTAUDIO)
	gcc -o $(TARGET) $^ $(LIBPD) $(PORTAUDIO)
	if [ $(PDNATIVE_PLATFORM) == "mac" ]; then mkdir -p ./libs && cp $(LIBPD) ./libs; fi

$(LIBPD):
	cd $(LIBPD_DIR) && make

$(PORTAUDIO):
	cd $(PORTAUDIO_DIR) && ./configure && make

clean:
	rm -f *.o

clobber: clean
	rm -f $(TARGET)
	if [ $(PDNATIVE_PLATFORM) == "mac" ]; then rm -rf ./libs; fi


flululu:
	echo $(LIBPD_DIR)
