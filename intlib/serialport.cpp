#include "serialport.hpp"

#include <unistd.h>
#include <stdio.h>
#include <termios.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#include "bytearray.hpp"

SerialPort::SerialPort()
{

}

SerialPort::~SerialPort()
{

}

bool SerialPort::Connect(InterfaceSettings *settings)
{
	if(is_connect) {
		/*Disconnect();*/
		return true;
	}

	SerialSettings *serial_settings;
	if(settings)
		serial_settings = static_cast<SerialSettings *>(settings);
	else
		throw 1;

	//sd = open(serial_settings.name, O_RDWR | O_NOCTTY | O_NONBLOCK | O_NDELAY);
	sd = open(serial_settings->name, O_RDWR);
	if(sd == -1)
		return false;

	int is_ok = SetSettings(serial_settings);
	if(!is_ok) {
		Disconnect();
		return false;
	}

	is_connect = true;
	return true;
}


bool SerialPort::SetSettings(SerialSettings *settings)
{
	struct termios opt;

	int is_ok;
	is_ok = tcgetattr(sd, &opt);
	if(is_ok)
		return false;

	opt.c_cflag &= ~(PARENB | CSTOPB | CSIZE);
	opt.c_lflag &= ~(ICANON | ECHO | ECHOE | ECHONL | ISIG | IXON | IXOFF | IXANY);
	//opt.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR | ICRNL);
	opt.c_iflag |= ICRNL;
	opt.c_oflag &= ~(OPOST | ONLCR | OCRNL);

	int baudrate = ConvertLinuxBaud(settings->baudrate);
	cfsetispeed(&opt, baudrate);
	cfsetospeed(&opt, baudrate);

	switch(settings->databits) {
	case databits_eight:	opt.c_cflag |= CS8;
							break;
	default:				opt.c_cflag |= CS8;
	}

	switch(settings->stopbits) {
	case stopbits_one:		opt.c_cflag &= ~CSTOPB;
							break;
	default:				opt.c_cflag &= ~CSTOPB;
	}

	switch(settings->parity) {
	case stopbits_one:		opt.c_cflag &= ~PARENB;
							break;
	default:				opt.c_cflag &= ~PARENB;
	}

	opt.c_cflag &= ~CRTSCTS;
	opt.c_cflag |= (CLOCAL | CREAD);
	opt.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);

	opt.c_cc[VTIME] = 1;
	opt.c_cc[VMIN] = 0;
	//opt.c_cc[VTIME] = 1;
	//opt.c_cc[VMIN] = 80;

	is_ok = tcsetattr(sd, TCSANOW, &opt);
	if(is_ok)
		return false;

	return true;
}

int SerialPort::ConvertLinuxBaud(BaudRate baudrate)
{
	switch(baudrate) {
	case baudrate_115200:	return B115200;
	case baudrate_9600:		return B9600;
	default:				return B115200;
	}	
}

#if 0
bool SerialPort::Send(const ByteArray &data)
{
	int send_bytes;
	unsigned char *barr = data.GetArr();
	int bytes_num = data.GetBytesNum();

	send_bytes = write(sd, barr, bytes_num);
	if(send_bytes < bytes_num)
		return false;

	return true;
}

bool SerialPort::Recv(ByteArray &data)
{
	int i;
	unsigned char barr[20];
	byte_t byte;
	//int count = 0, recv_bytes; //= 0;, recv_len = len;
	int recv_bytes;
	while(1) {
		//barr_ptr += recv_bytes;
		//recv_len -= recv_bytes;
		//recv_bytes = read(sd, barr_ptr, recv_len);
		recv_bytes = read(sd, barr, sizeof(barr) - 1);
		if(!recv_bytes)
			break;
		if(recv_bytes < 0)
			return false;

		//count += recv_bytes;

	//	barr[count] = '\0';
	//	data.Append(barr);
		for(i = 0; i < recv_bytes; i++) {
			byte = barr[i];
			data.Append(byte);
		}

	}
	return true;
#if 0
	barr[count] = '\0';
	data.Append(barr);
#endif

#if 0
	int i;
	unsigned char byte;
	for(i = 0; i < count; i++) {
		byte = barr[i];
		data.Append(byte);
	}
	return true;
#endif
}

bool SerialPort::Recv(ByteArray &data, const int &len)
{
#if 0
	char recv_data[len + 1];
	int rd = read(sd, recv_data, len);
	if(rd < 1) {
		data.Append("No data");
		return false;
	}

	recv_data[rd] = '\0';
	data.Append(recv_data);
	return true;
#else
	unsigned char barr[len + 1];
	unsigned char *barr_ptr = barr;
	int count = 0, recv_bytes = 0, recv_len = len;
	while(count < len) {
		barr_ptr += recv_bytes;
		recv_len -= recv_bytes;
		recv_bytes = read(sd, barr_ptr, recv_len);

		if(recv_bytes < 0)
			return false;
#if 1
		if(!recv_bytes)
			break;
#endif

		count += recv_bytes;
	}
#if 1
	int i;
	unsigned char byte;
	for(i = 0; i < count; i++) {
		byte = barr[i];
		data.Append(byte);
	}
#endif
	return true;
#endif
}
#endif

void SerialPort::CheckConnection()
{
#if 0
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
#endif
}

#if 0
bool SerialPort::Receive(char *data, int len)
{
	int is_ok;
	is_ok = read(sd, data, len);
	if(is_ok < 0)
		return false;
	return true;
}
#endif

#if 0
bool SerialPort::Send(char const *data)
{
	int send_bytes;
	int len = strlen(data);
	send_bytes = write(sd, data, len);
	if(send_bytes < 0 || send_bytes != len)
		return false;

	return true;
}
#endif

#if 0
bool SerialPort::Connect(char const *name)
{
	strcpy(serial_settings.name, name);
	bool is_ok = Connect();
	if(is_ok)
		return true;
	else
		return false;
}
#endif

#if 0
bool SerialPort::Configure(void *settings)
{
	SerialSettings *serial_settings_ptr;
	serial_settings_ptr = static_cast<SerialSettings *>(settings);
	char *dst_name = serial_settings.name;
	char *src_name = serial_settings_ptr->name;
	strcpy(dst_name, src_name);
	serial_settings.baudrate = serial_settings_ptr->baudrate;
	serial_settings.databits = serial_settings_ptr->databits;
	serial_settings.parity = serial_settings_ptr->parity;
	serial_settings.stopbits = serial_settings_ptr->stopbits;
	return true;
}
#endif

#if 0
bool SerialPort::BaseConfigure()
{
	serial_settings.baudrate = baudrate_115200;
	serial_settings.databits = databits_eight;
	serial_settings.parity = parity_none;
	serial_settings.stopbits = stopbits_one;
	return true;
}
#endif
