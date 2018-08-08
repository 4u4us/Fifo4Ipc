#include "fifo_ipc_msg.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <iostream>

std::string Fifo_ipc_msg::fifoName = A_FIFO_NAME;
int Fifo_ipc_msg::fifo_fd = -1;

Fifo_ipc_msg::Fifo_ipc_msg(bool p_create)
{
	if (true==p_create)
	{
		unlink(Fifo_ipc_msg::fifoName.c_str());
		mkfifo(Fifo_ipc_msg::fifoName.c_str(),0666);
	}
};

Fifo_ipc_msg::~Fifo_ipc_msg()
{
	z_close();	
	unlink(Fifo_ipc_msg::fifoName.c_str());
};

int Fifo_ipc_msg::z_open(int p_way)
{
	int ret=-1;
	if (p_way==Fifo_ipc_msg::READ_FIFO)
		fifo_fd = open(Fifo_ipc_msg::fifoName.c_str(), O_RDONLY);
	else if (p_way==Fifo_ipc_msg::WRITE_FIFO)
		fifo_fd = open(Fifo_ipc_msg::fifoName.c_str(), O_WRONLY);
	else if (p_way==Fifo_ipc_msg::CLOSE_FIFO)
		z_close();

	return ret;
}

int Fifo_ipc_msg::z_close()
{
	int ret=-1;
	if (fifo_fd!=-1) {ret=close(fifo_fd);};
	return ret;
}

size_t Fifo_ipc_msg::z_write(unsigned char* p_wrBuf, size_t p_nBytes)
{
	size_t ret=0;
	z_open(Fifo_ipc_msg::WRITE_FIFO);
	ret = write(fifo_fd, p_wrBuf, p_nBytes);
	z_open(Fifo_ipc_msg::CLOSE_FIFO);
	return ret;
}

size_t Fifo_ipc_msg::z_read(unsigned char* p_rdBuf, size_t p_nBytes)
{
	size_t ret=0;
	z_open(Fifo_ipc_msg::READ_FIFO);
	ret = read(fifo_fd, p_rdBuf, p_nBytes);
	z_open(Fifo_ipc_msg::CLOSE_FIFO);
	return ret;
}
