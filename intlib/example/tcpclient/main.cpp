#include <stdio.h>
#include <string.h>

#include "bytearray.hpp"
#include "tcpclient.hpp"

const char serv_ip[] = "192.168.11.200";
const int serv_port = 4765;

int main()
{
	ByteArray send_data, recv_data;
	send_data.Append("H\r");

	TcpClient client(7654);
	TcpSettings settings;
	strcpy(settings.addr, serv_ip);
	settings.port = serv_port;

	client.Connect(&settings);

	client.Send(send_data);
	client.Recv(recv_data, 10);

	for(int i = 0; i < recv_data.GetBytesNum(); i++) {
		if(recv_data[i] == '\r') {
			printf("\n");
			continue;
		}
		printf("%c", recv_data[i]);
	}
	
	return 0;
}
