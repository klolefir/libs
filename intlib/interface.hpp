#ifndef INTERFACE_HPP_SENTRY
#define INTERFACE_HPP_SENTRY

class ByteArray;

struct InterfaceSettings {
};

class Interface {
protected:
	int sd;
	bool is_connect;
public:
	Interface();
	virtual ~Interface();
	virtual bool Connect(InterfaceSettings *settings) = 0;
	virtual bool Disconnect();
#if 0
	virtual bool Send(const ByteArray &data) = 0;
	virtual bool Recv(ByteArray &data, const int &len) = 0;
	virtual bool Recv(ByteArray &data) = 0;
#endif
	virtual bool Send(const ByteArray &data);
	virtual bool Recv(ByteArray &data, const int &len);
	virtual bool Recv(ByteArray &data);
	virtual void Delay(const unsigned int &delay_ms);
	virtual void CheckConnection() = 0;
	virtual void Flush();
	virtual bool IsConnect() { return is_connect; }
};

#endif
