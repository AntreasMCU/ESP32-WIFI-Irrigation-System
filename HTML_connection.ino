void HTML_connection(){
  Serial.println("New Client is requesting web page"); 
    String current_data_line = ""; 
    while (client.connected()) { 
      if (client.available()) { 
        char new_byte = client.read(); 
//        Serial.write(new_byte); 
        header += new_byte;
        if (new_byte == '\n') {
          int temp_index;
          int temp_number = 0;
//          Serial.println(header); 
                   
          if (current_data_line.length() == 0) 
          {
                      
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();

                        
            if (header.indexOf("LED=ON HTTP") != -1) 
            {
              Serial.println("LED is ON");
              digitalWrite(BuildIn_led, HIGH);
            }
            else
              Serial.println("No Led is ON");
            if (header.indexOf("LED=OFF HTTP") != -1) 
            {
              Serial.println("LED is OFF");
              digitalWrite(BuildIn_led, LOW);
            }
            
            temp_index = header.indexOf("r=");
            if (temp_index != -1){
              temp_index += 2;
              while(isDigit(header[temp_index])){
                temp_number = temp_number*10 + header[temp_index] - '0';
                temp_index++;
              }
              if(temp_number != 0)
                water_duration = temp_number;
              Serial.println(temp_number);
            }

            temp_index = header.indexOf("-t=");
            if (temp_index != -1){
              temp_index += 3;
              temp_number = 0;
              while(isDigit(header[temp_index])){
                temp_number = temp_number*10 + header[temp_index] - '0';
                temp_index++;
              }
              if(temp_number!=0)
                watering_hour = temp_number;
              Serial.println(watering_hour);
              temp_index++;
              temp_number = 0;
              while(isDigit(header[temp_index])){
                temp_number = temp_number*10 + header[temp_index] - '0';
                temp_index++;
              }
              if(temp_number!=0)
                watering_minutes = temp_number;
              Serial.println(watering_minutes);
            }

            temp_index = header.indexOf("del=");
            if (temp_index != -1){
              temp_index += 4;
              temp_number = 0;
              while(isDigit(header[temp_index])){
                temp_number = temp_number*10 + header[temp_index] - '0';
                temp_index++;
              }
              if(temp_number!=0)
                days_delay = temp_number;
              Serial.println(days_delay);
            }

            
            page_upload();
            header = "";
            break;
          } 
          else 
          { 
            current_data_line = "";
          }
        } 
        else if (new_byte != '\r') 
        { 
          current_data_line += new_byte; 
        }                         
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
}
