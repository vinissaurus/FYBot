#include <Arduino.h>
#include "AsyncTelegram.h"
AsyncTelegram myBot;

      // REPLACE myPassword YOUR WIFI PASSWORD, IF ANY
const char* token = bot_token;     // REPLACE myToken WITH YOUR TELEGRAM BOT TOKEN

void t_setup() {
    serial("Starting TelegramBot...");


  
    // To ensure certificate validation, WiFiClientSecure needs time upadated
    // myBot.setInsecure(false);
    myBot.setClock("CET-1CEST,M3.5.0,M10.5.0/3");
  
    myBot.setUpdateTime(2000);
    myBot.setTelegramToken(token);
    
    // Check if all things are ok
    serial("\nTest Telegram connection... ");
    myBot.begin();
    
    serial("Bot name:");  
    serial(myBot.userName);
}

void t_loop() {
  // a variable to store telegram message data
  TBMessage msg;

  // if there is an incoming message...
  if (myBot.getNewMessage(msg)){  
    
    String message ;  
    // Send a message to specific user who has started your bot
    // Target user can find it's own userid with the bot @JsonDumpBot 
    // https://t.me/JsonDumpBot         
    //int32_t userid = 1234567890;  
    //myBot.sendToUser(userid, msg.text); 
    
    // echo the received message
    myBot.sendMessage(msg, get_mess().c_str());

    // check if the message comes from a chat group (the group id is negative)
    if (msg.chatId < 0) {
      // echo the message to the chat group
      message += "\nGroup ID: "; 
      message += int64ToAscii(msg.group.id);  
      //myBot.sendToGroup(msg.group.id, message);   //DEPRECATED
      //or initialized msg.chatId with the id of the group you want to send the message to
      myBot.sendMessage(msg, message);  
    }       
      }
}
