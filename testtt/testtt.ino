#include <SoftwareSerial.h>

SoftwareSerial chat(D5, D6); // RX, TX

String a;

void setup() {
  pinMode(D5, INPUT);
  pinMode(D6, OUTPUT);

  Serial.begin(115200);

  chat.begin(115200); 

  delay(10);

}

void loop() {
//while (chat.available() > 0)
//  {
//    int rh1 = chat.parseInt();
//    int rh2 = chat.parseInt();
//    int tp1 = chat.parseInt();
//    int tp2 = chat.parseInt();
//    if (chat.read() == '\n')
//    {
//      Serial.print(rh1); Serial.print(".");Serial.print(rh2); Serial.print(" ");  
//      Serial.print(tp1); Serial.print(".");Serial.print(tp2);
//      Serial.println("");
//    }
//  }
    chat.print(123);
   delay(2000);
}
