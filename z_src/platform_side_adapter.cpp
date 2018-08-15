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
	size_t bcnt = 512;
	rdBuf = new unsigned char[bcnt];
	unsigned char* rdBufPtr = rdBuf;
	platfSideFifo.z_read(rdBufPtr, bcnt, true);
	int msg_id = *((int*)rdBufPtr);
	rdBufPtr += sizeof(int);
	bcnt = *((size_t*)rdBufPtr);
	rdBufPtr += sizeof(size_t);
	std::cout << "PLATF msg rcv id " << msg_id << std::endl;
	std::cout << "PLATF msg rcv size " << bcnt << std::endl;
	
	switch(msg_id)
	{
		case Fifo_ipc_msg::PRINT_MSG_REQ:
			{
			std::string sensorName;
			int sensorValue=0;
			bool retErr = platfSideFifo.deserializePrintReq(rdBufPtr, sensorName, sensorValue);
			std::cout << "PLATF Sensor " << sensorName << " value=" << sensorValue << "  Err=" << retErr << std::endl;
			std::string resp = std::string("OK");
			std::cout << "PLATF Sending response string:  " << resp << std::endl;
			size_t msgLength = 0;
			int msg_id = Fifo_ipc_msg::PRINT_MSG_RESP;
			platfSideFifo.serializePrintResp( msg_id , &wrBuf, msgLength, resp);
			platfSideFifo.z_write(wrBuf, msgLength, true);
			break;
			}
		default:
			{
			std::cout << "PLATF Unexpected msg! " << __LINE__ << std::endl;
			loopit=false;
			break;
			}
	}

	
#ifdef USE_SIMPLE_RESP
	size_t lengthResp = 1;
	wrBuf = new unsigned char[lengthResp];
	wrBuf[0] = 'W';
	platfSideFifo.z_write(wrBuf,lengthResp, true);
#endif
	delete rdBuf;
	rdBuf=NULL;
	delete wrBuf;
	wrBuf=NULL;

	}

return 0;
}
