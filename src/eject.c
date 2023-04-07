#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <doslib.h>

void show_help_message() {
  printf("usage: eject <0 or 1>\n");
}

int32_t main(int32_t argc, uint8_t* argv[]) {

  int32_t rc = -1;

  if (argc < 2) {
    show_help_message();
    goto exit;
  }

  int16_t drive = -1;
  if (strcmp(argv[1], "0") == 0) {
    drive = 1;
  } else if (strcmp(argv[1], "1") == 0) {
    drive = 2;
  }
  if (drive < 0) {
    show_help_message();
    goto exit;
  }

  int32_t sns = DRVCTRL(0, drive);
//  printf("sns=%02X\n", sns);
  if (sns & 0x40) {
    printf("error: eject operation is protected.\n");
    goto exit;
  } else if (sns & 0x04) {
    printf("error: no media.\n");
    goto exit;
  }

  DRVCTRL(1, drive);

  rc = 0;

exit:
  return rc;
}