// PLATFORM side started before APP side.

#include <iostream>
#include "platform_side_adapter.h"

int main(void)
{
Fifo_ipc_msg platfSideFifo(true);

unsigned char *wrBuf = NULL;
unsigned char *rdBuf = NULL;


int cnt = 0;

bool loopit = true;
//while(loopit)
	{
	size_t bcnt = 512;
	rdBuf = new unsigned char[bcnt];
	platfSideFifo.z_read(rdBuf, bcnt, true);
	int msg_id = *((int*)rdBuf);
	bcnt = *((size_t*)(rdBuf+sizeof(int)));
	std::cout << "PLATF msg rcv id " << msg_id << std::endl;
	std::cout << "PLATF msg rcv size " << bcnt << std::endl;

	switch(msg_id)
	{
		case Fifo_ipc_msg::PRINT_MSG_REQ:
			{
			std::string sensorName;
			int sensorValue=0;
			bool retErr = platfSideFifo.deserializePrintReq(rdBuf+sizeof(int)+sizeof(size_t), sensorName, sensorValue);
			std::cout << "PLATF Sensor " << sensorName << " value=" << sensorValue << "  Err=" << retErr << std::endl;
			break;
			}
		default:
			{
			std::cout << "PLATF Unexpected msg! " << __LINE__ << std::endl;
			break;
			}
	}
	delete rdBuf;
	rdBuf=NULL;
	size_t lengthResp = 1;
	wrBuf = new unsigned char[lengthResp];
	wrBuf[0] = 'W';
	platfSideFifo.z_write(wrBuf,lengthResp, true);  
	delete wrBuf;
	wrBuf=NULL;
	}

return 0;
}
