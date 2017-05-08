#include <SPI.h>
#include <MCP2515.h>
#include <Arduino.h>
#include <SoftwareSerial.h>
#include <iCommunicate.hpp>

CANMSG msg;
// Should be private in implementation
iCommunicate _com;

void GetMessage(CANMSG msg);
void SendMockMsg();

void setup() {
  // Setup serial
  Serial.begin(9600);
  while(!Serial); // Wait for Serial connection from PC

  // Setup SPI (Could de moved to iCommunicate?)
  SPI.setClockDivider(SPI_CLOCK_DIV8);

  // Setup CAN
  if (!_com.Init()) {
    Serial.println("Setting up CAN failed");
  }

  // De functie die voldoet aan de voorwaarde voor de callback
  _com.SetCallback(GetMessage);

  Serial.println("Setup completed");
}


// De Read() functie is er om te pollen of er een nieuwe message is
// Deze zo vaak mogelijk aanroepen om niks te missen
void loop() {
  _com.Read();
  //  SendMockMsg();
}

// Voorbeeld callback methode, deze wordt aangeroepen als
// er een message is. in msg.data is staat de data.
void GetMessage(CANMSG msg) {
  for (uint8_t i = 0; i < msg.dataLength; i++) {
    Serial.print("Msg: ");
    Serial.print(i);
    Serial.print(" Data: ");
    Serial.println(msg.data[i]);
  }
}

// Zo kan een message er uit zien
void SendMockMsg() {
  msg.adrsValue = 0x7df;
  msg.isExtendedAdrs = false;
  msg.rtr = false;
  msg.dataLength = 8;
  msg.data[0] = 0x02;
  msg.data[1] = 0x01;
  msg.data[2] = 123;
  msg.data[3] = 0;
  msg.data[4] = 0;
  msg.data[5] = 0;
  msg.data[6] = 0;
  msg.data[7] = 0;

  if (_com.Write(msg)) {
    Serial.println("Wrote msg");
  }
  else {
    Serial.println("Writing went wrong");
  }
 }
