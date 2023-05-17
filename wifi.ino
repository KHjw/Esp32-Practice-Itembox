void wifi_conn(){
  HAS2_Wifi();
  Setup();
}

void wifi_state_update(){
  Receive(itembox);
  if((int)my["shift_machine"] != 0){
    wifi_Gstate_appl();
    wifi_Dstate_appl();
  }
}

void wifi_state_send(){

}

// (String)(const char*)my["game_state"] == ;

void wifi_Gstate_appl(){
  wifi_Gstate = (String)(const char*)my["game_state"];
  if(wifi_Gstate != current_Gstate){
    Serial.print("Game State :: ");
    if(wifi_Gstate == "setting"){
      Serial.println("Setting");
      NeoShowColor(White);
    }
    else if(wifi_Gstate == "ready"){
      Serial.println("Ready");
      NeoShowColor(Red);
    }
    else if(wifi_Gstate == "activate"){
      Serial.println("Activate");
      wifi_Dstate = "activate";
      current_Dstate = "";
    }
    current_Gstate = wifi_Gstate;
  }
}

void wifi_Dstate_appl(){
  if((String)(const char*)my["device_state"] != current_Dstate){
    Serial.print("Device State :: ");
    if((String)(const char*)my["device_state"] == "activate"){
      Serial.println("Activate");
      RfidLoop();
    }
    else if((String)(const char*)my["device_state"] == "used"){
      Serial.println("Used");
    }
    else if((String)(const char*)my["device_state"] == "open"){
      Serial.println("Open");
    }
    else if((String)(const char*)my["device_state"] == "close"){
      Serial.println("Close");
    }
    else if((String)(const char*)my["device_state"] == "repaired_all"){
      Serial.println("All Repaired");
    }
    else if((String)(const char*)my["device_state"] == "player_win"){
      
    }
    else if((String)(const char*)my["device_state"] == "player_lose"){
      
    }
    current_Dstate = (String)(const char*)my["device_state"];
  }

}

void get_role(){
  Receive(RfidID);
  if((String)(const char*)my["role"] == player){

  }
  else{

  }
}