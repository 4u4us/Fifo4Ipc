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
	platfSideFifo.z_read((unsigned char*)&msg_id,sizeof(int));
	std::cout << "PLATF msg rcv id " << msg_id << std::endl;
	size_t bcnt = 0;
	platfSideFifo.z_read((unsigned char*)&bcnt,sizeof(size_t));
	std::cout << "PLATF msg rcv size " << bcnt << std::endl;
	unsigned char* msgToDecode = rdBuf+sizeof(size_t);
	switch(msg_id)
	{
	case Fifo_ipc_msg::PRINT_MSG_REQ:
		std::string sensorName = "";
		int sensorValue;
		bool retErr = platfSideFifo.deserializePrintReq(msgToDecode, sensorName, sensorValue);
		std::cout << "PLATF Sensor " << sensorName << " value=" << sensorValue << std::endl;
	break;
	default:
		std::cout << "PLATF Unexpected msg! " << __LINE__ << std::endl;
	break;
	}
	
	platfSideFifo.z_write(wrBuf,lengthResp); 
	//re-init buffers  
	free(rdBuf);
	free(wrBuf);
	wrBuf=NULL;
	rdBuf=NULL;
	}

return 0;
}
