// PLATFORM side started before APP side.

#include <iostream>
#include "platform_side_adapter.h"

int main(void)
{
Fifo_ipc_msg platfSideFifo(true);

unsigned char wrBuf[1];
wrBuf[0]='W';

unsigned char  rdBuf[1];
rdBuf[0]='R';

int cnt = 0;

bool loopit = true;
while(loopit)
	{
	size_t bcnt = platfSideFifo.z_read(rdBuf,1);
	if (rdBuf[0]!='W' || (bcnt<=0))
		{
		std::cout << "PLATF Unexpected msg! " << bcnt << std::endl;
		loopit=false;
		break;
		}
	if (rdBuf[0]=='W' && cnt%512==0)
		{
		std::cout << "PLATF Expected msg OK! " << cnt << std::endl;
		}
	platfSideFifo.z_write(wrBuf,1);	
	cnt++;
	if (cnt%2049==0) loopit=false;
	//re-init buffers to wrong content.	
	wrBuf[0]='W';
	rdBuf[0]='R';
	}

return 0;
}
