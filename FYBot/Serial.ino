
void s_setup(){
  Serial.begin(115200);
  }


void s_loop(){
  if(Serial.available()>0){
    String serial_message=Serial.readString();
    if(serial_message.length()>0){
    if(serial_message.indexOf("reset")>0){
      serial("opaa");
      delay(1000);
      }
      }
    }
  }

void serial(String s){
  Serial.println(s);
  }
