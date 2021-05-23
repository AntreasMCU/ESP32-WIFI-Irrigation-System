void wifi_connect(){
  Serial.print("Connecting to ");
  Serial.println(WIFI_NAME);
  WiFi.begin(WIFI_NAME, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
  delay(1000);
  Serial.print("Trying to connect to Wifi Network");
  }
  Serial.println("");
  Serial.println("Successfully connected to WiFi network");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  if (!MDNS.begin("sis")) {
      while(1) {
        Serial.println("Error setting up MDNS responder!");\
        digitalWrite(BuildIn_led, !digitalRead(BuildIn_led));
        delay(1000);
      }
  }

  // Add service to MDNS-SD
  MDNS.addService("http", "tcp", 80);
    
  server.begin();
}

/************************************************************/

void time_init(){
  bool retry_token = true;
  
  while(retry_token){
    time_refresh();
    if(getLocalTime(&time_now)){
      Serial.println("obtain NTP time");
      last_watering_date = time_now;
      retry_token = false;
    }
    if(mktime(&time_now) < 10000){
      Serial.println(&time_now, "%A, %B %d %Y %H:%M:%S"); 
      retry_token = true;
      Serial.println("Failed to obtain time");
      delay(5000);
    }
  }
}
