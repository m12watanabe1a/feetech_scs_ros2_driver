#include "feetech_scs/INST.h"
#include "feetech_scs/SCS.h"
#include "feetech_scs/SCSCL.h"
#include "feetech_scs/SCSerial.h"

#include <unistd.h>

void delay(int ms)
{
  usleep(ms * 1000);
}

int main(int argc, char **argv)
{
  SCSCL sc;
  u16 Position[2];
  u16 Speed[2];
  u8 ID[2];

  std::cout << "start" << std::endl;
  sc.pSerial = std::make_unique<h6x_serial_interface::PortHandler>("/dev/ttyUSB0", 1000000);
  sc.pSerial->openPort();
  ID[0] = 1;
  ID[1] = 2;
  std::cout << "open" << std::endl;

  while (1)
  {
    std::cout << "write" << std::endl;
    Position[0] = 1000;
    Position[1] = 1000;
    Speed[0] = 1500;
    Speed[1] = 1500;
    sc.SyncWritePos(ID, 2, Position, 0, Speed);//舵机((ID1/ID2))以最高速度V=1500步/秒,运行至P1=1000
    std::cout << "delay" << std::endl;
    delay(754);//[(P1-P0)/V]*1000+100

    Position[0] = 20;
    Position[1] = 20;
    Speed[0] = 1500;
    Speed[1] = 1500;
    sc.SyncWritePos(ID, 2, Position, 0, Speed);//舵机((ID1/ID2))以最高速度V=1500步/秒,运行至P1=20
    delay(754);//[(P1-P0)/V]*1000+100
    std::cout << "loop" << std::endl;
  }
  return 0;
}
