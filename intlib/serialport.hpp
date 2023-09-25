#ifndef SERIALPORT_HPP_SENTRY
#define SERIALPORT_HPP_SENTRY

#include "interface.hpp"

class ByteArray;

enum BaudRate {
	baudrate_9600,
	baudrate_115200
};
enum DataBits {
	databits_eight
};
enum Parity {
	parity_none	
};
enum StopBits {
	stopbits_one
};

struct SerialSettings : public InterfaceSettings {
	char name[40];
	BaudRate baudrate;
	DataBits databits;
	Parity parity;
	StopBits stopbits;
};

class SerialPort : public Interface {
	/*SerialSettings serial_settings;*/
	/*int timeout;*/
public:
	SerialPort();
	virtual ~SerialPort();
	virtual bool Connect(InterfaceSettings *settings);
#if 0
	virtual bool Send(const ByteArray &data);
	virtual bool Recv(ByteArray &data, const int &len);
	virtual bool Recv(ByteArray &data);
#endif
	virtual void CheckConnection();
private:
	bool SetSettings(SerialSettings *settings);
	/*bool BaseConfigure();*/
	int ConvertLinuxBaud(BaudRate baudrate);
};

#endif
