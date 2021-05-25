

void page_upload(){
  // Web Page Heading
  client.println("<!DOCTYPE html><html>");
  client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"><style>");
  client.println("html{font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
  client.println("h1{font-family: verdana; font-size: 1.3em; color: #f5f5f5; text-shadow: 1px 1px 1px #919191, 1px 2px 1px #919191, 1px 3px 1px #919191, 1px 4px 1px #919191, 1px 5px 1px #919191, 1px 6px 1px #919191, 1px 7px 1px #919191, 1px 18px 6px rgba(16,16,16,0.4), 1px 22px 10px rgba(16,16,16,0.2), 1px 25px 35px rgba(16,16,16,0.2), 1px 30px 60px rgba(16,16,16,0.4);}");
  //CSS styling
  client.println(".submit_button{box-shadow: 3px 4px 0px 0px #7a8eb9; background:linear-gradient(to bottom, #637aad 5%, #5972a7 100%); background-color:#637aad; border-radius:15px; border:1px solid #314179; display:inline-block; cursor:pointer; color:#ffffff; font-family:Arial; font-size:17px; padding:7px 25px; text-decoration:none; text-shadow:0px 1px 0px #7a8eb9;}");
  client.println(".pump_button_gray{box-shadow: 3px 4px 0px 0px #899599; background:linear-gradient(to bottom, #ededed 5%, #bab1ba 100%); background-color:#ededed; border-radius:15px; border:1px solid #d6bcd6; display:inline-block; cursor:pointer; color:#3a8a9e; font-family:Arial; font-size:17px; padding:7px 25px; text-decoration:none; text-shadow:0px 1px 0px #e1e2ed;}");
  client.println(".pump_button_red{box-shadow: 3px 4px 0px 0px #8a2a21; background:linear-gradient(to bottom, #c62d1f 5%, #f24437 100%); background-color:#c62d1f; border-radius:15px; border:1px solid #d02718; display:inline-block; cursor:pointer; color:#ffffff; font-family:Arial; font-size:17px; padding:7px 25px; text-decoration:none; text-shadow:0px 1px 0px #810e05;}");
  client.println(".grid-item {border: 1px solid rgba(0, 0, 0, 0.8); padding: 20px; font-size: 30px; text-align: center;}");
  client.println(".slider{text-align: center;width: 80%;}");
  client.println("input[type=\"range\"]{-webkit-appearance: none !important; width: 100%; height: 15px; background-color: #A3CD99; border: 1px solid darken(#A3CD99, 4%); radius: 10px; margin: auto; transition: all 0.3s ease;}"); 
  client.println("input[type=\"range\"]::-webkit-slider-thumb -webkit-appearance: none !important width: 20px height: 20px background: color: #579E81 border: radius: 30px box-shadow: 0px 0px 3px darken(#579E81, 15%) transition: all 0.5s ease");
  client.println("rangevalue{text-align: center; font-family: Arial; font-size: 18px; display: block; margin: auto; padding: 10px 0px; width: 100%; color: #579E81;}");
  client.println("#customers th {color: white; width:33%;}");
  client.println("</style></head><body style=\"background-color:#e0e0eb;\"><div style=\"height: 60px; background: linear-gradient(to bottom, #0066cc 0%, #66ccff 100%);\"><h1 style=\"font-size: 2em;\">Smart Irrigation System</h1></div>");
  client.println("<div style=\"height:120px; background: linear-gradient(to bottom, #0099ff 0%, #99ccff 100%)\"><h1 style=\"text-align: center; position: relative; top:10px; \"> Pump Activation</h1>");
  // If the watering_pin State is off, it displays the ON button 
  if(!digitalRead(watering_pin))
    client.println("<a href=\"PUMP=ON\"><button class=\"pump_button_gray\" style=\"position:relative; top:20px;\">Start</button></a></div>");
  //else display the OFF button
  else
    client.println("<a href=\"PUMP=OFF\"><button class=\"pump_button_red\" style=\"position:relative; top:20px;\">Stop</button></a></div>");
  client.println("<div style=\"height:8px; background-color:#e0e0eb;\"> </div>");
  client.println("<div style=\"height:320px; background: linear-gradient(to bottom, #0099ff 0%, #99ccff 100%);\"><h1 style=\"text-align: center; position: relative; top:10px;\"> Time Programming</h1>");//<div class=\"slider\"><a href=\"range=\" + rangevalue.value ><input type = \"range\" min=\"0\" max=\"100\" onchange=\"rangevalue.value=value\"/><output id=\"rangevalue\">50</output><b style=\"text-align: center; font-size: 1.3em; position: relative; left: 80%; top:-25px;\"> Minutes to water </b></div>");
  client.println("<center><table id=\"customers\" style=\"position:relative; top:20px; font-size:1em;\">");
  client.println("<tr><th>Minutes to water</th><th>Time of Day</th><th>Days Delay</th></tr>");
  client.println("<tr><th>"+String(water_duration)+"</th><th>"+String(watering_hour)+":"+String(watering_minutes)+"</th><th>"+String(days_delay)+"</th></tr>");
  client.println("<tr style=\" height: 180px;\"><th><center><input type=\"number\"  id=\"Duration\" min=\"1\" max=\"60\" style=\"font-size: 1.5em; \"></center></th><th><center><input type=\"time\" id=\"daytime\" style=\"font-size: 2em;\"></center></th><th><center><input type=\"number\"  id=\"DayDelay\" min=\"1\" max=\"30\" style=\"font-size: 1.5em; \"></center></th></tr></table></center>");
  
  //Post Local IP(in case you used mDNS), current time and seconds untill next watering for debbuging purposes  
  IPAddress ip = WiFi.localIP();
  String ipStr = String(ip[0]) + '.' + String(ip[1]) + '.' + String(ip[2]) + '.' + String(ip[3]);
  client.println("<a href=\"s\" onclick=\"location.href=this.href+'?r='+Duration.value + '-t=' + daytime.value + '-del=' + DayDelay.value; return false;\"><button class=\"submit_button\" style=\"position:relative; top:-20px;\">Submit</button></a></div><div style=\"background-color:#0099ff;\">"+String(time_now.tm_hour)+":"+String(time_now.tm_min)+"  -  "+String(next_watering_seconds)+"  -  Local IP: " + ipStr + "</div></body></html>");

}
