#include "iCommunicate.hpp"

// TODO: Make init take arguments for CAN config
bool iCommunicate::Init() {
  if(iCommunicate::_can.initCAN(CAN_BAUD_100K) == 0) {
    return false;
  }

  else if (iCommunicate::_can.setCANNormalMode(LOW) == 0) {
    return false;
  }

  return true;
}

void iCommunicate::Read() {
  int i = iCommunicate::_can.receiveCANMessage(&msg, 2000);
  if (i && (msg.data[0] == 0x02)) {
    _callback(msg);
  }
}

// TODO: Change to *msg
bool iCommunicate::Write(CANMSG msg) {
  CANMSG msg2;
  msg2.adrsValue = 0x7df;
  msg2.isExtendedAdrs = false;
  msg2.rtr = false;
  msg2.dataLength = 8;
  msg2.data[0] = 0x02;
  msg2.data[1] = 0x01;
  msg2.data[2] = 123;
  msg2.data[3] = 0;
  msg2.data[4] = 0;
  msg2.data[5] = 0;
  msg2.data[6] = 0;
  msg2.data[7] = 0;
  return iCommunicate::_can.transmitCANMessage(msg2, 1000);
}

void  iCommunicate::SetCallback(void (*callback)(CANMSG msg)) {
  _callback = callback;
  /* code */
}
