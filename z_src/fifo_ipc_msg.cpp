#include "fifo_ipc_msg.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <iostream>
#include <string.h>

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

size_t Fifo_ipc_msg::z_write(unsigned char* p_wrBuf, size_t p_nBytes, bool done)
{
	size_t ret=0;
	z_open(Fifo_ipc_msg::WRITE_FIFO);
	ret = write(fifo_fd, p_wrBuf, p_nBytes);
	if (true==done)
	{
		z_open(Fifo_ipc_msg::CLOSE_FIFO);
	}
	return ret;
}

size_t Fifo_ipc_msg::z_read(unsigned char* p_rdBuf, size_t p_nBytes, bool done)
{
	size_t ret=0;
	z_open(Fifo_ipc_msg::READ_FIFO);
	ret = read(fifo_fd, p_rdBuf, p_nBytes);
	if (true==done)
	{
		z_open(Fifo_ipc_msg::CLOSE_FIFO);
	}
	return ret;
}

//______________________________________________________________________________

bool Fifo_ipc_msg::serializePrintReq(int p_msgId, unsigned char** p_wrBuf, size_t& p_allocLength,std::string p_str, int p_val, char* aFname )
{
	// buffer was NOT allocated beforehand.
	p_allocLength = sizeof(int) + sizeof(size_t) + sizeof(size_t) + sizeof(int) + p_str.length()*sizeof(unsigned char)
		+ strlen(aFname)+1;
    *p_wrBuf = (unsigned char*)new unsigned char[p_allocLength]; 
	unsigned char* serPtr = *p_wrBuf;
	memcpy(serPtr, &p_msgId, sizeof(int) );
	serPtr += sizeof(int);
	memcpy(serPtr, &p_allocLength, sizeof(size_t) );
	serPtr += sizeof(size_t);
	size_t sensorNameLength = p_str.length();
	memcpy(serPtr, &sensorNameLength, sizeof(size_t) );
	serPtr += sizeof(size_t);
    memcpy(serPtr, &p_val, sizeof(int) );
	serPtr += sizeof(int);
    memcpy(serPtr, (unsigned char*)(p_str.c_str()), p_str.length() * sizeof(unsigned char));
    serPtr += p_str.length() * sizeof(unsigned char);
    memcpy(serPtr, aFname, strlen(aFname)+1);
    
    return true;
    
    
};
bool Fifo_ipc_msg::deserializePrintReq(unsigned char* p_rdBuf, size_t msgLength, std::string& p_str,int& p_val, char* aFname )
{
	// buffer was allocated beforehand.
	// msgId and msgLength have already been decoded.
	unsigned char* deserPtr = p_rdBuf;
	size_t sensorNameLength = 0;
	memcpy(&sensorNameLength, deserPtr, sizeof(size_t));
	deserPtr += sizeof(size_t);
	memcpy(&p_val, deserPtr, sizeof(int));
	deserPtr += sizeof(int);
	unsigned char* sensorname = new unsigned char[sensorNameLength];
	memcpy(sensorname, deserPtr, sensorNameLength);
	//sensorname[sensorNameLength]=0;
	p_str.append((const char*)sensorname);
	delete sensorname;
	deserPtr += sensorNameLength;
	memcpy(aFname, deserPtr, msgLength- sizeof(size_t) - sensorNameLength - sizeof(int));
	
	return true;
	
};

//______________________________________________________________________________
bool Fifo_ipc_msg::serializePrintResp(int p_msgId, unsigned char** p_wrBuf, size_t& p_allocLength, std::string p_str )
{
	// buffer was NOT allocated beforehand.
	p_allocLength = sizeof(int) + sizeof(size_t) + sizeof(size_t) + p_str.length()*sizeof(unsigned char);
    *p_wrBuf = (unsigned char*)new unsigned char[p_allocLength]; 
	unsigned char* serPtr = *p_wrBuf;
	memcpy(serPtr, &p_msgId, sizeof(int) );
	serPtr += sizeof(int);
	memcpy(serPtr, &p_allocLength, sizeof(size_t) );
	serPtr += sizeof(size_t);
	size_t respStrLength = p_str.length();
	memcpy(serPtr, &respStrLength, sizeof(size_t) );
	serPtr += sizeof(size_t);
    memcpy(serPtr, (unsigned char*)(p_str.c_str()), p_str.length() * sizeof(unsigned char));
    
    return true;
};

bool Fifo_ipc_msg::deserializePrintResp(unsigned char* p_rdBuf, std::string& p_str )
{
	// buffer was allocated beforehand.
	// msgId and msgLength have already been decoded.
	unsigned char* deserPtr = p_rdBuf;
	size_t respStrLength = 0;
	memcpy(&respStrLength, deserPtr, sizeof(size_t));
	deserPtr += sizeof(size_t);
	unsigned char* respStr = new unsigned char[respStrLength];
	memcpy(respStr, deserPtr, respStrLength);
	p_str.append((const char*)respStr);
	delete respStr;
	
	return true;
	
};

//______________________________________________________________________________
