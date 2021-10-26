String message[] = {
  "FUCK you!",
  "Go FUCK yourself!",
  "FUCK",
  "FUCK u motherFUCKer",
  "FUCK this, FUCK that and FUCK YOU!"
};

String message2[] = {
  "Who the FUCK do u think you are?",
  "Shut the FUCK up!",
  "Are you FUCKing kidding me?",
  "FUCKing psycho!",
  "Youre FUCKed up!"
};

int message_quant = 5;

String get_mess() {
  return message[random(message_quant)];
}

//String read_mess(String m){
//  if(m.indexOf("fuck")!=-1){
//    return message2[random(message_quant)];
//    }
//      if(m.indexOf("info")!=-1){
//    return message2[random(message_quant)];
//    }
//    
//  }
