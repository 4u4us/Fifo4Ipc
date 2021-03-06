#ifndef FIFO_IPC_MSG_H
#define FIFO_IPC_MSG_H

#include <cstddef>
#include <string>

#define A_FIFO_NAME "/tmp/fifo_asa_psa"
class Fifo_ipc_msg
{
	public:
	enum {
		READ_FIFO,
		WRITE_FIFO,
		CLOSE_FIFO
	};
	Fifo_ipc_msg(){};
	Fifo_ipc_msg(bool p_create);
	~Fifo_ipc_msg();


	size_t z_write(unsigned char* p_wrBuf, size_t p_nBytes);
	size_t z_read(unsigned char* p_rdBuf, size_t p_nBytes);
	int z_close();

	protected:
	
	int z_open(int p_way);

	private:
	static std::string fifoName; 
	static int fifo_fd;
	
	
};

#endif
