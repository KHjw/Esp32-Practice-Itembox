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