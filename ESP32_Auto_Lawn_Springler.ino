#include <WiFi.h>
#include <ESPmDNS.h>
#include <time.h>

const char* WIFI_NAME= "NOULA1"; 
const char* WIFI_PASSWORD = "2741301248"; 
WiFiServer server(80);

struct tm time_now;

String header;

const int BuildIn_led = 2;

int water_duration = 25;
int watering_hour = 7;
int watering_minutes = 15;
int days_delay = 1;
struct tm last_watering_date;
time_t next_watering_seconds = 0;

WiFiClient client;

void setup() {
  Serial.begin(115200);
  
  pinMode(BuildIn_led, OUTPUT);
  digitalWrite(BuildIn_led, LOW);
  
  wifi_connect();

  time_init();
  
}

void loop(){
  client = server.available(); 
  if (client) {
    HTML_connection(); 
  }

  time_sync();
  
}
