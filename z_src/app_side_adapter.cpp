// APP side started after PLATFORM side.
#include <iostream>
#include "app_side_adapter.h"

int main(void)
{

Fifo_ipc_msg appSideFifo(false);

unsigned char *wrBuf = NULL;
unsigned char *rdBuf = NULL;

bool loopit = true;
//while(loopit)
	{
	std::string sensorName = std::string("Voltages");
	int sensorVal = 134;
	size_t msgLength = 0;
	int msg_id = Fifo_ipc_msg::PRINT_MSG_REQ;
	appSideFifo.serializePrintReq( msg_id , &wrBuf, msgLength, sensorName, sensorVal);
	std::cout << "APP msg snd id " << msg_id << std::endl;
	std::cout << "APP msg length " << msgLength << std::endl;
	std::cout << "APP sensorName length " << sensorName.length() << " Name: " <<  sensorName << std::endl;
	appSideFifo.z_write(wrBuf, msgLength, true);
	
	size_t respLength = 1;
	rdBuf = new unsigned char[respLength];
	rdBuf[0]='X';
	appSideFifo.z_read(rdBuf, respLength, true);
	std::cout << "APP msg rcv  " << rdBuf[0] << std::endl;	
	delete [] rdBuf;
	delete [] wrBuf;
	wrBuf=NULL;
	rdBuf=NULL;
	}

return 0;
}
