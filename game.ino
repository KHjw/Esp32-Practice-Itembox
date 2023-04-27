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