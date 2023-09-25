#ifndef BYTEARRAY_HPP_SENTRY
#define BYTEARRAY_HPP_SENTRY

typedef unsigned char byte_t;

class ByteArray {
	enum {
		min_len = 1,
		inc_len = 16,
		max_len = 4096
	};
	byte_t *byte_arr;
	int len;
	int bytes_num;

public:
	ByteArray();
	ByteArray(const int &start_len);
	~ByteArray();
	int GetLen() const { return len; }
	byte_t *GetArr() const { return byte_arr; }
	int GetBytesNum() const { return bytes_num; }
	void Append(const byte_t &byte);
	void Append(const char *data);
	//void Append(const unsigned char *data);
	void Append(const ByteArray &data);
	void AppendWord(const unsigned short &word);
	void AppendDoubleWord(const unsigned int &dword);
	void ToStr(char *byte_str);
	void ToStr(char *byte_str, int size);
	void Resize(const int &new_len);
	void Clear();

	byte_t &operator[](const int &ind);
private:
	ByteArray(const ByteArray &) {}
	void operator=(const ByteArray &) {}
};

#endif
