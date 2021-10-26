
void s_setup(){
  Serial.begin(115200);
  }


void s_loop(){
  if(Serial.available()){
    String serial_message=Serial.readString();
    if(serial_message.length()>0){
    if(serial_message=="reset"){
      serial("opaa");
      }
      }
    }
  }

void serial(String s){
  Serial.println(s);
  }
