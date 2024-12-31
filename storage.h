/*
Dependencies.
*/

#ifdef ARDUINO
#include <SD.h>
#else
#include <stdio.h>
#endif

/*
Constants.
*/

#define PIN_SD 8
#define RESULT_FILE_NAME "scan.obj" // TODO: Maybe use the date and time here.

/*
Globals.
*/

#ifdef ARDUINO
File resultFile;
#endif

/*
Functions.
*/

void setupStorage()
{
#ifdef ARDUINO
  if (!SD.begin(PIN_SD)) {
    log("Cannot initialize SD card!\n");
    fail();
  }
#endif
}

void openResultFile()
{
#ifdef ARDUINO
  if (!SD.remove(RESULT_FILE_NAME)) {
    log("Cannot delete %s!\n", RESULT_FILE_NAME);
    fail();
  }
  resultFile = SD.open(RESULT_FILE_NAME, FILE_WRITE);
  if (!resultFile) {
    log("Cannot open %s!\n", RESULT_FILE_NAME);
    fail();
  }
#endif
}

void closeResultFile()
{
#ifdef ARDUINO
  resultFile.close();
#endif
}

void emit(const char *format, ...)
{
  char text[256];
  va_list args;
  va_start(args, format);
  vsnprintf(text, sizeof(text), format, args);
  va_end(args);
#ifdef ARDUINO
  resultFile.print(text);
#else
  printf("%s", text);
#endif
  log(text);
}