// APP side started after PLATFORM side.
#include <iostream>
#include "app_side_adapter.h"


int main(void)
{

char testlnkname[] = "testlnkname.testlock";
int fd_testlnkname = open(testlnkname, O_CREAT | O_RDWR, 0666);
char lnkname[PATH_MAX];  
char passParamLnkname[PATH_MAX];
memset(lnkname,0,PATH_MAX);
memset(passParamLnkname,0,PATH_MAX);
snprintf(lnkname,PATH_MAX,"/proc/%d/fd/%d",getpid(),fd_testlnkname);
// this way with readlink, we get the full path
readlink(lnkname, passParamLnkname, PATH_MAX);

Fifo_ipc_msg appSideFifo(false);

unsigned char *wrBuf = NULL;
unsigned char *rdBuf = NULL;

bool loopit = true;
//while(loopit)
	{
	std::string sensorName = std::string("Voltage");
	int sensorVal = 134;
	size_t msgLength = 0;
	int msg_id = Fifo_ipc_msg::PRINT_MSG_REQ;
	
	appSideFifo.serializePrintReq( msg_id , &wrBuf, msgLength, sensorName, sensorVal,passParamLnkname);
	std::cout << "APP msg snd id " << msg_id << std::endl;
	std::cout << "APP msg length " << msgLength << std::endl;
	std::cout << "APP sensorName length " << sensorName.length() << " Name: " <<  sensorName << std::endl;
	appSideFifo.z_write(wrBuf, msgLength, true);

	
#ifdef USE_SIMPLE_RESP
	size_t respLength = 1;
	rdBuf = new unsigned char[respLength];
	rdBuf[0]='X';
	appSideFifo.z_read(rdBuf, respLength, true);
	std::cout << "APP msg rcv  " << rdBuf[0] << std::endl;	
#endif

	size_t bcnt = 512;
	rdBuf = new unsigned char[bcnt];
	unsigned char* rdBufPtr = rdBuf;
	appSideFifo.z_read(rdBufPtr, bcnt, true);
	msg_id = *((int*)rdBufPtr);
	rdBufPtr += sizeof(int);
	bcnt = *((size_t*)rdBufPtr);
	rdBufPtr += sizeof(size_t);
	std::cout << "APP msg rcv id " << msg_id << std::endl;
	std::cout << "APP msg rcv size " << bcnt << std::endl;

	switch(msg_id)
	{
		case Fifo_ipc_msg::PRINT_MSG_RESP:
			{
			std::string respStr;
			bool retErr = appSideFifo.deserializePrintResp(rdBufPtr, respStr);
			std::cout << "APP rcv Resp " << respStr << "  Err=" << retErr << std::endl;
			break;
			}
		default:
			{
			std::cout << "PLATF Unexpected msg! " << __LINE__ << std::endl;
			loopit=false;
			break;
			}
	}
	
	delete [] rdBuf;
	delete [] wrBuf;
	wrBuf=NULL;
	rdBuf=NULL;
	}

close(fd_testlnkname);
return 0;
}
