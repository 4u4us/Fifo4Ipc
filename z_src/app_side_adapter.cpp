// APP side started after PLATFORM side.
#include <iostream>
#include "app_side_adapter.h"

int main(void)
{

Fifo_ipc_msg appSideFifo(false);

unsigned char *wrBuf = NULL;
unsigned char *rdBuf = NULL;

bool loopit = true;
while(loopit)
	{
	std::string sensorName = std::string("Voltage");
	int sensorVal = 154;
	size_t msgLength = 0;
	appSideFifo.serializePrintReq(&wrBuf, msgLength, sensorName, sensorVal);
	appSideFifo.z_write(wrBuf, msgLength, true);
	
	size_t respLength = 1;
	rdBuf = new unsigned char(respLength);
	appSideFifo.z_read(rdBuf, respLength, true);
	
	//re-init buffers	
	delete rdBuf;
	delete wrBuf;
	wrBuf=NULL;
	rdBuf=NULL;
	}

return 0;
}
