#define TIME_CONFIG_DELAY     3600000
#define TIME_ROUTINE_DELAY    1000

const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 7200;
const int   daylightOffset_sec = 3600;
bool watering_token = false;

unsigned long last_time_config = 0;
unsigned long last_time_routine = 0;

/************************************************************/

void time_refresh(){
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
}

/************************************************************/

void time_sync(){
  
  if(millis() - last_time_config > TIME_CONFIG_DELAY){
    last_time_config += TIME_CONFIG_DELAY;
    time_refresh();
  }

  if(millis() - last_time_routine > TIME_ROUTINE_DELAY){
    last_time_routine += TIME_ROUTINE_DELAY;
      
    if(!getLocalTime(&time_now)){
      Serial.println("Failed to obtain time");
      time_refresh();
      return;
    }
    check_next_watering();
  }
}

/************************************************************/

void check_next_watering(){

  struct tm next_watering = last_watering_date;
  time_t next_watering_timestamp;
  time_t timestamp = mktime(&time_now);
  
  next_watering.tm_hour = watering_hour;
  next_watering.tm_min = watering_minutes;
  next_watering_timestamp = mktime(&next_watering) + 86400*days_delay;
  if(next_watering_timestamp - timestamp < 0){
    last_watering_date = time_now;
    digitalWrite(BuildIn_led, HIGH);
    watering_token = true;
    Serial.println("Watering is on!");
  }

  if(watering_token){
    if(timestamp - mktime(&last_watering_date) > water_duration*60){
      digitalWrite(BuildIn_led, LOW);
      watering_token = false;  
    }
  }
  next_watering_seconds = next_watering_timestamp - timestamp;
//  Serial.println(next_watering_seconds);
}

/************************************************************/
