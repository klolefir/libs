#include "interface.hpp"

#include <unistd.h>

#include "bytearray.hpp"

Interface::Interface() :
	sd(0),
	is_connect(false)
{

}

Interface::~Interface()
{
	Disconnect();
}

void Interface::Flush()
{
	int rd;
	char byte;
	do {
		rd = read(sd, &byte, sizeof(byte));
	} while(rd > 0);
}

bool Interface::Disconnect()
{
	if(!is_connect)
		return false;

	if(sd)
		close(sd);

	sd = 0;
	is_connect = false;
	return true;
}	

void Interface::Delay(const unsigned int &delay_ms)
{
	usleep(delay_ms);
}

bool Interface::Send(const ByteArray &data)
{
	int send_bytes;
	unsigned char *barr = data.GetArr();
	int bytes_num = data.GetBytesNum();

	send_bytes = write(sd, barr, bytes_num);
	if(send_bytes < bytes_num)
		return false;

	return true;
}

bool Interface::Recv(ByteArray &data)
{
	int i;
	unsigned char barr[20];
	byte_t byte;
	int recv_bytes;
	while(1) {
		recv_bytes = read(sd, barr, sizeof(barr) - 1);
		if(!recv_bytes)
			break;
		if(recv_bytes < 0)
			return false;

		for(i = 0; i < recv_bytes; i++) {
			byte = barr[i];
			data.Append(byte);
		}

	}
	return true;
}

bool Interface::Recv(ByteArray &data, const int &len)
{
	unsigned char barr[len + 1];
	unsigned char *barr_ptr = barr;
	int count = 0, recv_bytes = 0, recv_len = len;
	while(count < len) {
		barr_ptr += recv_bytes;
		recv_len -= recv_bytes;
		recv_bytes = read(sd, barr_ptr, recv_len);

		if(recv_bytes < 0)
			return false;
		if(!recv_bytes)
			break;

		count += recv_bytes;
	}

	int i;
	unsigned char byte;
	for(i = 0; i < count; i++) {
		byte = barr[i];
		data.Append(byte);
	}

	return true;
}
