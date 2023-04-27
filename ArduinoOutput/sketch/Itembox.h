#line 1 "c:\\Github\\Esp32-Practice-Itembox\\Itembox.h"
#ifndef _DONE_ITEMBOX_CODE_
#define _DONE_ITEMBOX_CODE_

#include "Library_and_pin.h"

//****************************************Rfid SETUP****************************************
Adafruit_PN532 nfc(PN532_SCK, PN532_MISO, PN532_MOSI, PN532_SS);

void RfidInit();
void RfidLoop();
void Rfid_Identify();
void RfidCheckLoop();

char RfidID;

//****************************************Encoder SETUP**************************************************
void Encoder_Setup();
long readEncoderValue(void);
void updateEncoder();
void Encoder_Progress_Loop();
void Encoder_RevCount();

volatile int lastEncoded = 0;
volatile long encoderValue = 0;
long lastencoderValue = 0;

int lastMSB = 0;
int lastLSB = 0;

int RawVal = 0;
int Player_guess = 0;
volatile int encoder_revcount[2] = {0, 0};
int QuizCount = 0;
int Quiz_answer[3] = {10, 40, 27};                      // 퀴즈 [1,2,3] 정답 (0~47)

//****************************************Game SETUP**************************************************
void GameSetup();
void GameSystem();
int cnt();

int RfidPASS = 0;
int QuizPASS = 0;

//****************************************Neopixel SETUP**************************************************
void NeopixelInit();

void NeoGreen(int time);
void NeorBlink(int num, int time);
void NeoWaiting_Blue();

Adafruit_NeoPixel encoder_neo(ENCODER_NEONUM,ENCODER_NEOPIN,NEO_GRB + NEO_KHZ800);

#endif