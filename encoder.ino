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