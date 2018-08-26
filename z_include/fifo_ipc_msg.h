#ifndef FIFO_IPC_MSG_H
#define FIFO_IPC_MSG_H

#include <cstddef>
#include <string>

#define A_FIFO_NAME "/tmp/fifo_asa_psa"
class Fifo_ipc_msg
{
	public:
	enum {
		PRINT_MSG_REQ = 100,
		PRINT_MSG_RESP,
		READ_FIFO,
		WRITE_FIFO,
		CLOSE_FIFO
	};
	Fifo_ipc_msg(){};
	Fifo_ipc_msg(bool p_create);
	~Fifo_ipc_msg();


	size_t z_write(unsigned char* p_wrBuf, size_t p_nBytes, bool done=true);
	size_t z_read(unsigned char* p_rdBuf, size_t p_nBytes, bool done=true);
	
	bool serializePrintReq(int p_msgId, unsigned char** p_wrBuf, size_t& p_allocLength, std::string p_str, int p_val, char* aFname );
	bool deserializePrintReq( unsigned char* p_rdBuf, size_t msgLength, std::string& p_str , int& val, char* aFname );

	bool serializePrintResp(int p_msgId, unsigned char** p_wrBuf, size_t& p_allocLength, std::string p_str );
	bool deserializePrintResp( unsigned char* p_rdBuf, std::string& p_str );

	protected:
	
	int z_open(int p_way);
	int z_close();
	
	private:
	static std::string fifoName; 
	static int fifo_fd;
	
	
};

#endif
