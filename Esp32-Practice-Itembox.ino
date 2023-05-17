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

void setup(void) {
  Serial.begin(115200);
  timer_id = timer.setInterval(DATA_REFRESH_TIME, timer_interrupt);       //timer.deleteTimer(timer_id)     ->    타이머 멈춤
  NeopixelInit();
  RfidInit();
  Encoder_Setup();
}

void loop(void) {
  timer.run();
  GameSystem();
}
