#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <MicroGear.h>
#include <SoftwareSerial.h>
SoftwareSerial chat(D5, D6);
//const char* ssid = "モバイル";
//const char* password = "blanches";
const char* ssid = "TS";
const char* password = "hzec1865";

#define APPID "ELS"
#define KEY "Bs4VD0geiazlOOH"
#define SECRET "4HZj3BQiImeDQURwz8iaVq76i"
#define ALIAS "nodeMCU" 
#define WEB "Web"

WiFiClient client;

int timer = 0;
MicroGear microgear(client);

///////////////////////////////////////////////////////////////////////////

// If a new message arrives, do this // 12 71.0 27.8
                                     // 60 24   
void hcontrol(String h){
    chat.print(h);
    //microgear.chat(WEB, "12 72.1 24.5");
    Serial.println(h);
  }
void onMsghandler(char *topic, uint8_t* msg, unsigned int msglen) {
  Serial.print("Incoming message --> ");
  msg[msglen] = '\0';
  
  char strState[msglen];
  for (int i = 0; i < msglen; i++) {
    strState[i] = (char)msg[i];
    Serial.print((char)msg[i]);
  }
  Serial.println();

  String state = String(strState).substring(0, msglen);
  if(state.substring(0,2) =="60"){
    hcontrol(state.substring(3,5));
    delay(1000);
  }else if(state.substring(0,2) == "15"){
    hcontrol("15");
    delay(1000);
  }else if(state.substring(0,2) == "13"){
    hcontrol("13");
    delay(1000);
  }
  // Processing Section

  // Switch the LED on the nodeMCU
  /*if (state == "ON") {
    microgear.chat(ALIAS, 100);
    digitalWrite(LED_BUILTIN, LOW);
  } else if (state == "OFF") {
    microgear.chat(ALIAS, 0);
    digitalWrite(LED_BUILTIN, HIGH);
  }*/

  // Sending a value of i to Web
  
  //End of Processing Section
}

void onFoundgear(char *attribute, uint8_t* msg, unsigned int msglen) {
  Serial.print("Found new member --> ");
  for (int i=0; i<msglen; i++)
      Serial.print((char)msg[i]);
  Serial.println();  
}

void onLostgear(char *attribute, uint8_t* msg, unsigned int msglen) {
  Serial.print("Lost member --> ");
  for (int i=0; i<msglen; i++)
      Serial.print((char)msg[i]);
  Serial.println();
}

// When a microgear is connected, do this
void onConnected(char *attribute, uint8_t* msg, unsigned int msglen) {
  Serial.println("Connected to NETPIE...");
  // Set the alias of this microgear ALIAS
  microgear.setAlias(ALIAS);
}

///////////////////////////////////////////////////////////////////////////

void setup() {
  // put your setup code here, to run once:
  // Add Event listeners 
  // Call onMsghandler() when new message arrives.
  microgear.on(MESSAGE,onMsghandler);

  // Call onFoundgear() when new gear appear.
  microgear.on(PRESENT,onFoundgear);

  // Call onLostgear() when some gear goes offline.
  microgear.on(ABSENT,onLostgear);

  // Call onConnected() when NETPIE connection is established.
  microgear.on(CONNECTED,onConnected);
  pinMode(D5, INPUT);
  pinMode(D6, OUTPUT);
  
  Serial.begin(115200);
  chat.begin(115200); 
  Serial.println("Starting...");

  // Initial WIFI, this is just a basic method to configure WIFI on ESP8266.
  // You may want to use other method that is more complicated, but provide better user experience.
  if (WiFi.begin(ssid, password)) {
      while (WiFi.status() != WL_CONNECTED) {
          delay(500);
          Serial.print(".");
      }
  }

  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  // Initial with KEY, SECRET and also set the ALIAS here.
  microgear.init(KEY,SECRET,ALIAS);

  // connect to NETPIE to a specific APPID.
  microgear.connect(APPID);

  // For testing that is the nodeMCU receives data.
  //pinMode(LED_BUILTIN, OUTPUT);
}

///////////////////////////////////////////////////////////////////////////

void loop() {
  // put your main code here, to run repeatedly:
  // To check if the microgear is still connected.
  if (microgear.connected()) {
      Serial.println("connected");
      // Call this method regularly otherwise the connection may be lost.
      microgear.loop();

      if (timer >= 1000) {
        Serial.println("Publish...");

      // Chat with the microgear named ALIAS which is myself.
        // microgear.chat(ALIAS,20);
        timer = 0;
        //Serial.print("1");
      } 
      else timer += 100;
      if (chat.available() > 0) {
        //Serial.print("2");
        int rh1 = chat.parseInt();
        int rh2 = chat.parseInt();
        int tp1 = chat.parseInt();
        int tp2 = chat.parseInt();
        if (chat.read() == '\n') {
          String val = String("12")+" "+String(rh1)+"."+String(rh2)+" "+String(tp1)+"."+String(tp2);
          Serial.print(val);
          microgear.chat(ALIAS, val);
          microgear.chat(WEB, val);
        }
      }
      
  } else {
      Serial.println("connection lost, reconnect...");
      if (timer >= 5000) {
        microgear.connect(APPID);
        timer = 0;
      } else timer += 100;
  }
  delay(100);
}
