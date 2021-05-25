#include <WiFi.h>
#include <ESPmDNS.h>
#include <time.h>

const char* WIFI_NAME= "******";            //Add your network name 
const char* WIFI_PASSWORD = "*********";    //add your network pass
WiFiServer server(80);

//Initialize time structure to hold current time
struct tm time_now;

//Build in LED of ESP32-WROOM32
const int BuildIn_led = 2;
//change output pin to the pin that you have connected the relay. For testing purposes I leave it the same as the build in led.
const int watering_pin = 2;

//Watering Variables
int water_duration = 25;          //Minutes to water
int watering_hour = 7;            //Time of day             [0-23]
int watering_minutes = 15;        //Minutes of hour         [0-59]
int days_delay = 1;               //Days between watering   [0-30]
struct tm last_watering_date;     //Time structure of the last time we water
time_t next_watering_seconds = 0; //Holding the seconds till the next watering

WiFiClient client;

void setup() {
  //open serial port for debbuging
  Serial.begin(115200);

  
  pinMode(BuildIn_led, OUTPUT);
  digitalWrite(BuildIn_led, LOW);
  pinMode(watering_pin, OUTPUT);
  digitalWrite(watering_pin, LOW);

  //Connect to the wifi network and set mDNS 
  wifi_connect();

  //Get time from network and initialize RTC
  time_init();
  
}

void loop(){
  //check if there is any available HTTP connection
  client = server.available(); 
  if (client) {
    HTML_connection(); 
  }

  //check all timed functions on time tab
  time_sync();
  
}
