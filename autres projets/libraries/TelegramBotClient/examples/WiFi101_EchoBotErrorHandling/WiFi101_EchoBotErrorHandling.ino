/**
    WiFi101_EchoBotErrorHandling
    Example show how to receive and send messages via Telegram's Bot API.
    It also send an invalid message every 60 seconds to illustrate 
    error handling
  
    Part of TelegramBotClient (https://github.com/schlingensiepen/TelegramBotClient)    
    Jörn Schlingensiepen <joern@schlingensiepen.com>

    Client's API:   https://schlingensiepen.github.io/TelegramBotClient/
    Telegram's API: https://core.telegram.org/bots/api
*/

#include <WiFi101.h>
#include <TelegramBotClient.h>

// Instantiate Wifi connection credentials
const char* ssid     = "digitalisierung";
const char* password = "cloudification";

// Instantiate Telegram Bot secure token
// This is provided by BotFather
const String botToken = "YOUR BOT TOKEN";

// Instantiate the ssl client used to communicate with Telegram's web API
WiFiSSLClient sslPollClient;

// Instantiate the client with secure token and client
TelegramBotClient client(
      botToken, 
      sslPollClient);
      
// Function called on receiving a message
void onReceive (TelegramProcessError tbcErr, JwcProcessError jwcErr, Message* msg)
{      
    Serial.println("onReceive");
    Serial.print(F("tbcErr")); Serial.print((int)tbcErr); 
    Serial.print(":"); Serial.println(toString(tbcErr));
    
    Serial.print(F("jwcErr")); Serial.print((int)jwcErr); 
    Serial.print(":"); Serial.println(toString(jwcErr));
  
    Serial.print(F("UpdateId: ")); Serial.println(msg->UpdateId);      
    Serial.print(F("MessageId: ")); Serial.println(msg->MessageId);
    Serial.print(F("FromId: ")); Serial.println(msg->FromId);
    Serial.print(F("FromIsBot: ")); Serial.println(msg->FromIsBot);
    Serial.print(F("FromFirstName: ")); Serial.println(msg->FromFirstName);
    Serial.print(F("FromLastName: ")); Serial.println(msg->FromLastName);
    Serial.print(F("FromLanguageCode: ")); Serial.println(msg->FromLanguageCode); 
    Serial.print(F("ChatId: ")); Serial.println(msg->ChatId);
    Serial.print(F("ChatFirstName: ")); Serial.println(msg->ChatFirstName);
    Serial.print(F("ChatLastName: ")); Serial.println(msg->ChatLastName);
    Serial.print(F("ChatType: ")); Serial.println(msg->ChatType);
    Serial.print(F("Text: ")); Serial.println(msg->Text);
    Serial.print(F("Date: ")); Serial.println(msg->Date);

    // Sending the text of received message back to the same chat
    // chat is identified by an id stored in the ChatId attribute of msg
    client.postMessage(msg->ChatId, msg->Text);
    
}

// Function called if an error occures
void onError (TelegramProcessError tbcErr, JwcProcessError jwcErr)
{
  Serial.println(F("onError"));
  Serial.print(F("tbcErr")); Serial.print((int)tbcErr); 
  Serial.print(":"); Serial.println(toString(tbcErr));
  
  Serial.print(F("jwcErr")); Serial.print((int)jwcErr); 
  Serial.print(":"); Serial.println(toString(jwcErr));
}

// Setup WiFi connection using credential defined at begin of file
void setupWiFi()
{
  Serial.println();
  Serial.print(F("Try to connect to network "));
  Serial.println(ssid);
  Serial.println();
    
  WiFi.begin(ssid, password);
  Serial.print(".");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("OK");
  Serial.print(F("IP address .: "));
  Serial.println(WiFi.localIP());

  Serial.print(F("Strength ...: "));
  Serial.println(WiFi.RSSI());
  Serial.println();   
}

// Setup
void setup() {
  Serial.begin(115200);
  delay(10);
  setupWiFi();
  // Sets the functions implemented above as so called callback functions,
  // thus the client will call this function on receiving data or on error.
  client.begin(      
      onReceive,
      onError);    
}

long last = 0; // simple time out by storing millis() of last call time

// Loop
void loop() {
  // To process receiving data this method has to be called each main loop()
  client.loop();

  if ((millis() - last) > 60000) // time out 60 seconds
  {    
    last = millis(); // simple time out by storing millis() of last call time
    // Sending message to a chat with id 100000
    // This will cause an error since our bot will not have access rights to anotherone's chat
    client.postMessage(100000, "test");    
  }
}
