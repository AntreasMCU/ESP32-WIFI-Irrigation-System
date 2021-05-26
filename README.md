# ESP32 WIFI Irrigation System

A WIFI irrigation system based on ESP32-Wroom32 module.

Dont forget to change WIFI name and passward to be able to connect to your network.
Change watering_pin at ESP32_Auto_Lawn_Springler.ino to your prefered IO.

![Web Page](https://github.com/AntreasMCU/ESP32-WIFI-Irrigation-System/blob/main/images/sis_web.jpg)

ESP32 connects to NTP Server on startup and every 1 hour after that to get the correct time.
*Change gmtOffset_sec and daylightOffset_sec on Time.ino to your local settings*



TODO: Change page width based on user screen to fix problems with mobile browser.
