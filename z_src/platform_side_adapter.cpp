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
while(loopit)
	{
	int msg_id = 0;
	platfSideFifo.z_read((unsigned char*)&msg_id,sizeof(int), false);
	std::cout << "PLATF msg rcv id " << msg_id << std::endl;
	size_t bcnt = 0;
	platfSideFifo.z_read((unsigned char*)&bcnt,sizeof(size_t), false);
	std::cout << "PLATF msg rcv size " << bcnt << std::endl;
	rdBuf = new unsigned char(bcnt);
	platfSideFifo.z_read(rdBuf,bcnt, true);
	switch(msg_id)
	{
	case Fifo_ipc_msg::PRINT_MSG_REQ:
		{
		std::string sensorName = "";
		int sensorValue;
		bool retErr = platfSideFifo.deserializePrintReq(rdBuf, sensorName, sensorValue);
		std::cout << "PLATF Sensor " << sensorName << " value=" << sensorValue << "Err=" << retErr << std::endl;
		break;
		}
	default:
		{
		std::cout << "PLATF Unexpected msg! " << __LINE__ << std::endl;
		break;
		}
	}
	size_t lengthResp = 1;
	wrBuf = new unsigned char(lengthResp);
	wrBuf[0] = 'W';
	platfSideFifo.z_write(wrBuf,lengthResp, true); 
	//re-init buffers  
	delete rdBuf;
	delete wrBuf;
	wrBuf=NULL;
	rdBuf=NULL;
	}

return 0;
}
