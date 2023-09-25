#include <stdio.h>

#include "bytearray.hpp"
#include "serialport.hpp"

int main()
{
	SerialPort serial_port;
	bool is_ok;
	is_ok = serial_port.Connect("/dev/ttyUSB0");
	if(!is_ok)
		printf("Bad connect");

	ByteArray send_command(100);
	ByteArray recv_command(100);

#if 0
	send_command.Append('G');
	send_command.Append('0');
	send_command.Append('I');
#endif
	char str[] = "H\r";
	send_command.Append(str);
	int command_len = 100;

	char data[100];
	is_ok = serial_port.Send(send_command);
	if(!is_ok)
		printf("bad write");

	is_ok =	serial_port.Receive(recv_command, command_len);
	if(!is_ok)
		printf("bad read");

	for(int i = 0; i < recv_command.GetBytesNum(); i++)
		printf("%c", recv_command[i]);

	return 0;
}
