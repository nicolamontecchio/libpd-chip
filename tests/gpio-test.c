#include <stdio.h>
#include <string.h>


int main(int argc, char **argv)
{

  if (argc != 2)
  {
    printf("usage: %s {on/off}\n", argv[0]);
    return 1;
  }

  FILE *fp = fopen("/sys/class/gpio/gpio1019/value", "w");
  if (!fp)
  {
    printf("cannot open file; is pin 1019 being exported? is suid set?\n");
    return 1;
  }

  int value = strcmp(argv[1], "on") == 0 ? 1 : 0;
  fprintf(fp, "%d\n", value);
  fclose(fp);

  return 0;
}
