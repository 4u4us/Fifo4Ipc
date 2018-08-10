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
	//re-init buffers	
	free(rdBuf);
	free(wrBuf);
	wrBuf=NULL;
	rdBuf=NULL;
	}

return 0;
}
