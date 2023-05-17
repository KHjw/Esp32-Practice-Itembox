#include <Adafruit_PN532.h>
#include <Adafruit_NeoPixel.h>
#include <HAS2_Wifi.h>

#define PN532_SCK     18
#define PN532_MISO    19
#define PN532_MOSI    23
#define PN532_SS      5

#define encoderPinA   34
#define encoderPinB   35
#define buttonPin     32

#define ENCODER_NEOPIN  25
#define ENCODER_NEONUM  16