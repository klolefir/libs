#include "tcpclient.hpp"

#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <string.h>

#include "bytearray.hpp"

TcpClient::TcpClient(const int new_port) :
	port(new_port)
{
	Bind();
}

bool TcpClient::Bind()
{
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);

	sd = socket(AF_INET, SOCK_STREAM, 0);
	if(sd < 0)
		return false;

#if 0
	int opt = 1;
	setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
#endif
	timeval timeout;
	timeout.tv_sec = 0;
	timeout.tv_usec = 1000;
	setsockopt(sd, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));

	int is_ok;
	is_ok = bind(sd, (struct sockaddr *)&addr, sizeof(addr));
	if(is_ok < 0)
		return false;

	return true;
}

TcpClient::~TcpClient()
{

}

bool TcpClient::Connect(InterfaceSettings *settings/* = 0*/)
{
	if(is_connect)
		return true;


	TcpSettings *tcp_settings;
	if(settings)
		tcp_settings = static_cast<TcpSettings *>(settings);
	else
		throw 1;

#if 0
	bool is_bind;
	is_bind = Bind();
	if(!is_bind)
		return false;
#endif

	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(tcp_settings->port);
	inet_aton(tcp_settings->addr, &(addr.sin_addr));

	int is_ok;
	is_ok = connect(sd, (struct sockaddr *)&addr, sizeof(addr));
	//is_connect = (is_ok < 0) ? (false) : (true);
	if(is_ok < 0)
		return false;

	is_connect = true;
	return true;
}

void TcpClient::CheckConnection()
{
	char byte = 'c';
	int rd;
	if(is_connect) {
		write(sd, &byte, sizeof(byte));
		usleep(1000);

		char err_str[5];
		rd = read(sd, &err_str, sizeof(err_str)); 
		if(rd < 1)
			Disconnect();
	}
}

#if 0
bool TcpClient::Send(const ByteArray &data)
{
	unsigned char *command = data.GetArr();
	int len = data.GetBytesNum();
	write(sd, command, len);
	return true;
}

bool TcpClient::Recv(ByteArray &data, const int &len)
{
	char recv_data[len + 1];
	int rd = read(sd, recv_data, len);
	recv_data[rd] = '\0';

	if(rd < 1) {
		data.Append("No data");
		return false;
	}

	data.Append(recv_data);
	return true;
}

bool TcpClient::Recv(ByteArray &data)
{
	char recv_data[len + 1];
	int rd = read(sd, recv_data, len);
	recv_data[rd] = '\0';

	if(rd < 1) {
		data.Append("No data");
		return false;
	}

	data.Append(recv_data);
	return true;
}
#endif
