String message[] = {
  "FUCK you!",
  "Go FUCK yourself!",
  "FUCK",
  "FUCK u motherFUCKer",
  "FUCK this, FUCK that and FUCK YOU!"
};

String message2[] = {
  "Who the FUCK do u think YOU are?",
  "YOU Shut the FUCK up!",
  "Are YOU FUCKing kidding me?",
  "YOU FUCKing psycho!",
  "YOU're FUCKed up!"
};

int message_quant = 5;

String get_mess() {
  return message[random(message_quant)];
}

String read_mess(String m) {
  String answer = "";

  if (m.indexOf("fuck") >= 0) {
    answer = message2[random(message_quant)];
  }
  if (m.indexOf("info") >= 0) {
    answer = use_info();
  }
  if (m.indexOf("fuck") < 0 && answer.length()==0) {
    answer = message[random(message_quant)];
  }
//  if (m.indexOf(com_1) > 0) {
//    answer = "Reset!";
//  }
//  if (m.indexOf(com_2) > 0) {
//    answer = "Init!";
//  }
  return answer;
}
