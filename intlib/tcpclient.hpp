#ifndef TCPCLIENT_HPP_SENTRY
#define TCPCLIENT_HPP_SENTRY

#include "interface.hpp"

struct TcpSettings : InterfaceSettings {
	char addr[20];
	unsigned int port;
};

class TcpClient : public Interface {
	int port;
public:
	TcpClient(const int port);
	virtual ~TcpClient();
	virtual bool Connect(InterfaceSettings *settings);
#if 0
	virtual bool Send(const ByteArray &data);
	virtual bool Recv(ByteArray &data, const int &len);
	virtual bool Recv(ByteArray &data);
#endif
	virtual void CheckConnection();
private:
	bool Bind();
};

#endif
