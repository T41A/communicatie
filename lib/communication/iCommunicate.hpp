#ifndef COMM_H
#define  COMM_H

// Included libraries
#include <SPI.h>
#include <MCP2515.h>
#include <Arduino.h>

class iCommunicate {

public:
  bool Init();
  void Read();
  bool Write(CANMSG msg);
  void SetCallback(void(*callback)(CANMSG msg));


private:
  MCP2515 _can;
  CANMSG msg;
  void(*_callback)(CANMSG msg);
};




#endif
