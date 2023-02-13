/*
 * SCSerial.h
 * 飞特串行舵机硬件接口层程序
 * 日期: 2019.4.27
 * 作者: 
 */


#include "feetech_scs/SCSerial.h"
#include <chrono>

SCSerial::SCSerial()
{
	IOTimeOut = 100;
	pSerial = NULL;
}

SCSerial::SCSerial(u8 End):SCS(End)
{
	IOTimeOut = 100;
	pSerial = NULL;
}

SCSerial::SCSerial(u8 End, u8 Level):SCS(End, Level)
{
	IOTimeOut = 100;
	pSerial = NULL;
}


// - Source code --------------------------------------------------------
//   std::string dev = "/dev/ttyUSB0";
//   int baudrate = 115200;
//   const auto port_handler = std::make_unique<PortHandler>(dev, baudrate);

//   // Open port
//   pSerial->openPort();

//   // Get available bytes
//   ssize_t available_bytes = pSerial->getBytesAvailable();

//   // Read serial packet into read_buf
//   char read_buf[128];
//   pSerial->readPort(read_buf, sizeof(read_buf));

//   // Write serial packet
//   char write_buf[] = "Hello World";
//   pSerial->writePort(write_buf, strlen(write_buf))

//   // Close port
//   pSerial->closePort();
// ----------------------------------------------------------------------


int SCSerial::readSCS(unsigned char *nDat, int nLen)
{
	int Size = 0;
	// int ComData;
	// using chrono::system_clock;
	auto t_begin = std::chrono::system_clock::now();
	auto t_user = std::chrono::duration<int64_t, std::nano>(0);
	char read_buf[128];
	while (1)
	{
		// read : pSerial->readPort(read_buf, sizeof(read_buf));
		// get available bytes and read
		ssize_t available_bytes = pSerial->getBytesAvailable();
		if (available_bytes != -1)
		{
			pSerial->readPort(read_buf, sizeof(read_buf));
			for (int i = 0; i < available_bytes; i++)
			{
				if (nDat)
				{
					nDat[Size] = read_buf[i];
				}
				Size++;
			}
			t_begin = std::chrono::system_clock::now();
		}
		// if size is greater than or equal to nLen
		if (Size >= nLen)
		{
			break;
		}
		// get time user
		t_user = std::chrono::system_clock::now() - t_begin;
		// if time user is greater than IOTimeOut
		if (t_user.count() > IOTimeOut)
		{
			break;
		}
	}
	return Size;
}


// 	while(1){
// 		ComData = pSerial->read();
// 		if(ComData!=-1){
// 			if(nDat){
// 				nDat[Size] = ComData;
// 			}
// 			Size++;
// 			t_begin = millis();
// 		}
// 		if(Size>=nLen){
// 			break;
// 		}
// 		t_user = millis() - t_begin;
// 		if(t_user>IOTimeOut){
// 			break;
// 		}
// 	}
// 	return Size;
// }

// int SCSerial::writeSCS(unsigned char *nDat, int nLen)
// {
// 	if(nDat==NULL){
// 		return 0;
// 	}
// 	return pSerial->write(nDat, nLen);
// }

int SCSerial::writeSCS(unsigned char *nDat, int nLen)
{
	if (nDat == NULL)
	{
		return 0;
	}
	// write : pSerial->writePort(write_buf, strlen(write_buf))
	return pSerial->writePort((char *)nDat, nLen);
}

// int SCSerial::writeSCS(unsigned char bDat)
// {
// 	return pSerial->write(&bDat, 1);
// }
int SCSerial::writeSCS(unsigned char bDat)
{
	return pSerial->writePort((char *)&bDat, 1);
}

// void SCSerial::rFlushSCS()
// {
// 	while(pSerial->read()!=-1);
// }
void SCSerial::rFlushSCS()
{
	char read_buf[1];
	while (pSerial->readPort(read_buf, sizeof(read_buf)) != -1)
		;
}

void SCSerial::wFlushSCS()
{
}