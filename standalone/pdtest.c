#include <stdio.h>
#include <signal.h>
#include <z_libpd.h>
#include <portaudio.h>


const int PDTICK_LEN = 64;


void pdprint(const char *s) {
  printf("%s", s);
}

void pdnoteon(int ch, int pitch, int vel) {
  printf("noteon: %d %d %d\n", ch, pitch, vel);
}


// handle termination
static volatile int keepRunning = 1;
void intHandler(int dummy) {
    keepRunning = 0;
}


// audio callback, just calls out libpd
static int pa_callback(const void *input_buffer,
		       void *output_buffer,
		       unsigned long frames_per_buffer,
		       const PaStreamCallbackTimeInfo* timeInfo,
		       PaStreamCallbackFlags statusFlags,
		       void *userData )
{
    float *in = (float*) input_buffer;
    float *out = (float*) output_buffer;
    libpd_process_float(frames_per_buffer / PDTICK_LEN, in, out);
    return 0;
}


int main(int argc, char **argv) {

  if (argc < 3) {
    fprintf(stderr, "usage: %s file folder\n", argv[0]);
    return -1;
  }

  // portaudio
  if(Pa_Initialize() != paNoError)
  {
    fprintf(stderr, "an error occurred while initializing portaudio\n");
    return -1;
  }


  // init pd
  int srate = 44100;
  libpd_set_printhook(pdprint);
  libpd_set_noteonhook(pdnoteon);
  libpd_init();
  libpd_init_audio(2, 2, srate);

  // compute audio    [; pd dsp 1(
  libpd_start_message(1); // one entry in list
  libpd_add_float(1.0f);
  libpd_finish_message("pd", "dsp");

  // open patch       [; pd open file folder(
  libpd_openfile(argv[1], argv[2]);

  // open audio stream, libpd code is in callback
  PaStream *stream;
  Pa_OpenDefaultStream(
    &stream, 2, 2, paFloat32, srate, 256, pa_callback, NULL);
  Pa_StartStream( stream );

  // handle ctrl-c
  signal(SIGINT, intHandler);
  while (keepRunning) {
    Pa_Sleep(10000);
  }
  printf("quitting\n");

  if(Pa_Terminate() != paNoError)
  {
    fprintf(stderr, "an error occurred while terminating portaudio\n");
    return -1;
  }
  return 0;
}
