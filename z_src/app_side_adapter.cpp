// APP side started after PLATFORM side.
#include <iostream>
#include "app_side_adapter.h"

int main(void)
{

Fifo_ipc_msg appSideFifo(false);

unsigned char wrBuf[1];
wrBuf[0]='W';

unsigned char rdBuf[1];
rdBuf[0]='R';

int cnt=0;

bool loopit = true;
while(loopit)
	{
	appSideFifo.z_write(wrBuf,1);
	size_t bcnt = appSideFifo.z_read(rdBuf,1);
	if (rdBuf[0]!='W' || (bcnt<=0))
		{
		std::cout << "APP Unexpected msg! " << bcnt << std::endl;
		loopit=false;
		break;
		}
	if (rdBuf[0]=='W' && cnt%512==0)
		{
		std::cout << "APP Expected msg OK! " << cnt << std::endl;
		}
	cnt++;
	if (cnt%2049==0) loopit=false;
	//re-init buffers to wrong content.	
	wrBuf[0]='W';
	rdBuf[0]='R';
	}

return 0;
}
