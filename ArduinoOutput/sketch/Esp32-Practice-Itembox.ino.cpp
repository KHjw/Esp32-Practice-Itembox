#include <Arduino.h>
#line 1 "c:\\Github\\Esp32-Practice-Itembox\\Esp32-Practice-Itembox.ino"
 /*
 * @file Esp32-Practice-EncoderRfid.ino
 * @author 홍진우 KH.jinu (kevinlike@naver.com)
 * @brief
 * @version 1.0
 * @date 2023-04-25
 *
 * @copyright Copyright (c) 2023
 */

#include "Itembox.h"

#line 13 "c:\\Github\\Esp32-Practice-Itembox\\Esp32-Practice-Itembox.ino"
void setup(void);
#line 20 "c:\\Github\\Esp32-Practice-Itembox\\Esp32-Practice-Itembox.ino"
void loop(void);
#line 1 "c:\\Github\\Esp32-Practice-Itembox\\encoder.ino"
long readEncoderValue(void);
#line 5 "c:\\Github\\Esp32-Practice-Itembox\\encoder.ino"
boolean isButtonPushDown(void);
#line 14 "c:\\Github\\Esp32-Practice-Itembox\\encoder.ino"
void Encoder_RevCount();
#line 41 "c:\\Github\\Esp32-Practice-Itembox\\encoder.ino"
void Encoder_Setup();
#line 55 "c:\\Github\\Esp32-Practice-Itembox\\encoder.ino"
void Encoder_Progress_Loop();
#line 74 "c:\\Github\\Esp32-Practice-Itembox\\encoder.ino"
void updateEncoder();
#line 1 "c:\\Github\\Esp32-Practice-Itembox\\game.ino"
void GameSystem();
#line 25 "c:\\Github\\Esp32-Practice-Itembox\\game.ino"
void GameQuiz_system();
#line 35 "c:\\Github\\Esp32-Practice-Itembox\\game.ino"
void GameQuiz_check();
#line 1 "c:\\Github\\Esp32-Practice-Itembox\\neopixel.ino"
void NeopixelInit();
#line 6 "c:\\Github\\Esp32-Practice-Itembox\\neopixel.ino"
void EncoderPointNeo();
#line 32 "c:\\Github\\Esp32-Practice-Itembox\\neopixel.ino"
void NeoGreen(int time);
#line 44 "c:\\Github\\Esp32-Practice-Itembox\\neopixel.ino"
void NeoBlink(int num, int time);
#line 57 "c:\\Github\\Esp32-Practice-Itembox\\neopixel.ino"
void NeoWaiting_Blue();
#line 1 "c:\\Github\\Esp32-Practice-Itembox\\rfid.ino"
void RfidInit();
#line 16 "c:\\Github\\Esp32-Practice-Itembox\\rfid.ino"
void Rfid_Identify(uint8_t data[32]);
#line 40 "c:\\Github\\Esp32-Practice-Itembox\\rfid.ino"
void RfidLoop();
#line 70 "c:\\Github\\Esp32-Practice-Itembox\\rfid.ino"
void RfidCheckLoop();
#line 13 "c:\\Github\\Esp32-Practice-Itembox\\Esp32-Practice-Itembox.ino"
void setup(void) {
  Serial.begin(115200);
  NeopixelInit();
  RfidInit();
  Encoder_Setup();
}

void loop(void) {
  GameSystem();
}

#line 1 "c:\\Github\\Esp32-Practice-Itembox\\encoder.ino"
long readEncoderValue(void){
    return encoderValue/210 -3;
}

boolean isButtonPushDown(void){
  if(!digitalRead(buttonPin)){
    delay(5);
    if(!digitalRead(buttonPin))
      return true;
  }
  return false;
}

void Encoder_RevCount(){
  RawVal = readEncoderValue();

  if(RawVal < 0){
    RawVal = 0;
    encoder_revcount[0] = 1;
    encoder_revcount[1] = 0;
  }
  else if(RawVal >= 0 && RawVal < 16){
    encoder_revcount[0] = 1;
    encoder_revcount[1] = RawVal;
  }
  else if(RawVal >= 16 && RawVal < 32){
    encoder_revcount[0] = 2;
    encoder_revcount[1] = RawVal - 16;
  }
  else if(RawVal >= 32 && RawVal < 48){
    encoder_revcount[0] = 3;
    encoder_revcount[1] = RawVal - 32;
  }
  else{
    RawVal = 47;
    encoder_revcount[0] = 3;
    encoder_revcount[1] = 15;
  }
}

void Encoder_Setup(){
  pinMode(encoderPinA, INPUT);
  pinMode(encoderPinB, INPUT);
  pinMode(buttonPin, INPUT);

  digitalWrite(encoderPinA, HIGH); //turn pullup resistor on
  digitalWrite(encoderPinB, HIGH); //turn pullup resistor on

  //call updateEncoder() when any high/low changed seen
  //on interrupt 0 (pin 2), or interrupt 1 (pin 3)
  attachInterrupt(encoderPinA, updateEncoder, CHANGE);
  attachInterrupt(encoderPinB, updateEncoder, CHANGE);
}

void Encoder_Progress_Loop(){                                // "encoder값, 버튼눌림" 을 표시
  Encoder_RevCount();
  EncoderPointNeo();
  Serial.print(readEncoderValue());
  Serial.print(" / ");
  Serial.print(encoder_revcount[0]);
  Serial.print(", ");
  Serial.print(encoder_revcount[1]);

  if(isButtonPushDown()){
    Serial.print(" / 1");
  }else{
    Serial.print(" / 0");
  }

  Serial.println("");
  delay(50);
}

void updateEncoder(){
  int MSB = digitalRead(encoderPinA); //MSB = most significant bit
  int LSB = digitalRead(encoderPinB); //LSB = least significant bit

  int encoded = (MSB << 1) |LSB; //converting the 2 pin value to single number
  int sum  = (lastEncoded << 2) | encoded; //adding it to the previous encoded value

  if(sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) encoderValue --;
  if(sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) encoderValue ++;


  lastEncoded = encoded; //store this value for next time
}
#line 1 "c:\\Github\\Esp32-Practice-Itembox\\game.ino"
void GameSystem(){
  if(RfidPASS == 0){
    NeoWaiting_Blue();
    RfidLoop();
  }
  else{
    if(QuizPASS == 0){
      if(!(QuizCount == 3)){
        GameQuiz_system();
      }
      else{
        Serial.println("CLEAR!!!");
        // 퀴즈 3회 성공
        QuizPASS = 1;
        QuizCount = 0;
      }
    }
    else{
      NeoWaiting_Blue();
      RfidCheckLoop();
    }
  }
}

void GameQuiz_system(){
  if(isButtonPushDown()){
    Player_guess = RawVal;
    GameQuiz_check();
  }
  else{
    Encoder_Progress_Loop();
  }
}

void GameQuiz_check(){
  if(Player_guess == Quiz_answer[QuizCount]){
    QuizCount += 1;
    Serial.print("[[[[Quiz ");    // 네오픽셀 초록
    Serial.print(QuizCount);
    Serial.println("]]]] Success");
    NeoGreen(1500);
  }
  else{
    Serial.println("Quiz Fail");                            //네오픽셀 빨강
    NeoBlink(3, 500);
  }
}
#line 1 "c:\\Github\\Esp32-Practice-Itembox\\neopixel.ino"
void NeopixelInit()
{
  encoder_neo.begin();
}

void EncoderPointNeo(){
  int rev = 0;
  int point = 0;
  rev = encoder_revcount[0];
  point = encoder_revcount[1];

  for(int i=0; i<point; i++){
    encoder_neo.setPixelColor(i, 0, 0, 0);
  }
  for(int i=(point+1); i<ENCODER_NEONUM; i++){
    encoder_neo.setPixelColor(i, 0, 0, 0);
  }

  if(rev == 1){
    encoder_neo.setPixelColor(point, 10, 2, 2);
  }
  else if(rev == 2){
    encoder_neo.setPixelColor(point, 2, 10, 2);
  }
  else if(rev == 3){
    encoder_neo.setPixelColor(point, 2, 2, 10);
  }

  encoder_neo.show();
}

void NeoGreen(int time){
  for(int i=0; i<ENCODER_NEONUM; i++){
    encoder_neo.setPixelColor(i, 0, 10, 0);
  }
  encoder_neo.show();
  delay(time);
  for(int i=0; i<ENCODER_NEONUM; i++){
    encoder_neo.setPixelColor(i, 0, 0, 0);
  }
  encoder_neo.show();
}

void NeoBlink(int num, int time){
  for(int j=0; j<num; j++){
    for(int i=0; i<ENCODER_NEONUM; i++)
      encoder_neo.setPixelColor(i, 10, 0, 0);
    encoder_neo.show();
    delay(time);
    for(int i=0; i<ENCODER_NEONUM; i++)
      encoder_neo.setPixelColor(i, 0, 0, 0);
    encoder_neo.show();
    delay(time);
  }
}

void NeoWaiting_Blue(){
  for(int i=0; i<ENCODER_NEONUM; i++){
    encoder_neo.setPixelColor(i, 0, 0, 0);
  }
  for(int i=0; i<ENCODER_NEONUM; i++){
    encoder_neo.setPixelColor(i, 0, 0, 10);
  }
  encoder_neo.show();
}
#line 1 "c:\\Github\\Esp32-Practice-Itembox\\rfid.ino"
void RfidInit(){
  Serial.println("------------Rfid Initialized------------");
  nfc.begin();
  uint32_t versiondata = nfc.getFirmwareVersion();

  if (! versiondata) {
    Serial.print("Didn't find PN53x board");
    while (1); // halt
  }
  
  Serial.println("Found PN532");              // Got ok data, print it out!
  nfc.SAMConfig();                            // configure board to read RFID tags
  Serial.println("Waiting for Card ...");
}

void Rfid_Identify(uint8_t data[32]){
  String RfidID = "";

  for(int i=0; i<4; i++){
    RfidID += (char)data[i];
  }

  if(RfidID == "G1P9")
  {
    Serial.print("G1P9");
    RfidPASS = 1;
  }
  else if(RfidID == "G1P7")
  {
    Serial.print("G1P7");
    RfidPASS = 1;
  }
  else{
    Serial.print("Unidentified Chip");
    RfidPASS = 0;
  }
  Serial.println("");
}

void RfidLoop(){
  uint8_t success;
  uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0 };  // Buffer to store the returned UID
  uint8_t uidLength;                        // Length of the UID (4 or 7 bytes depending on ISO14443A card type)

  success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength);
 
  if (success) {
    if (uidLength == 7)
    {
      uint8_t data[32];

      Serial.print("NTAG2xx tag Detected : ");     

      success = nfc.ntag2xx_ReadPage(7, data); 

      if (success) 
      {
        Rfid_Identify(data);
      }
    }
    else
    {
      Serial.println("This doesn't seem to be an NTAG203 tag");
    }
    Serial.flush();    
  }
  delay (50);
}

void RfidCheckLoop(){
  uint8_t success;
  uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0 };  // Buffer to store the returned UID
  uint8_t uidLength;                        // Length of the UID (4 or 7 bytes depending on ISO14443A card type)
    
  success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength);
  
  if (success) {
    if (uidLength == 7)
    {
      uint8_t data[32];
      success = nfc.ntag2xx_ReadPage(7, data); 
      if (success) 
      {
        Serial.print("NTAG2xx tag Detected");
        RfidPASS = 0;
        QuizPASS = 0;
        encoderValue = 0;
      }
    }
    else
    {
      Serial.println("This doesn't seem to be an NTAG203 tag");
    }
    Serial.flush();    
  }
  delay (50);
}
