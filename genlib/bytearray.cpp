#include "string.h"
#include "bytearray.hpp"

ByteArray::ByteArray() :
	len(min_len),
	bytes_num(0)
{
	byte_arr = new byte_t[len];

	int i;
	for(i = 0; i < len; i++)
		byte_arr[i] = 0;
}

ByteArray::ByteArray(const int &start_len) :
	len(start_len),
	bytes_num(0)
{
	if(len > max_len)
		len = max_len;
	else if(len < min_len)
		len = inc_len;

	byte_arr = new byte_t[len];

	int i;
	for(i = 0; i < len; i++)
		byte_arr[i] = 0;
}


ByteArray::~ByteArray()
{
	delete[] byte_arr;
}

void ByteArray::Append(const byte_t &byte)
{
	int new_bytes_num = bytes_num + 1;
	if(new_bytes_num >= max_len)
		new_bytes_num = bytes_num;

	while(new_bytes_num >= len) {
		int new_len = len + inc_len;
		Resize(new_len);
	}

	int curr_ind = new_bytes_num - 1;
	byte_arr[curr_ind] = byte;
	bytes_num = new_bytes_num;
}

void ByteArray::Append(const ByteArray &data)
{
	int i;
	byte_t byte;
	byte_t *arr = data.GetArr();
	int len = data.GetBytesNum();
	for(i = 0; i < len; i++) {
		byte = arr[i];
		Append(byte);
	}
}


void ByteArray::AppendWord(const unsigned short &word)
{
	byte_t byte;
	int i;
	int len = 2;
	for(i = 0; i < len; i++) {
		byte = *(((byte_t *)&word) + i);
		Append(byte);
	}
}

void ByteArray::AppendDoubleWord(const unsigned int &dword)
{
	byte_t byte;
	int i;
	int len = 4;
	for(i = 0; i < len; i++) {
		byte = *(((byte_t *)&dword) + i);
		Append(byte);
	}
}

//void ByteArray::Append(char const *data)
void ByteArray::Append(const char *data)
{
	int i;
	int data_len = strlen(data);
	for(i = 0; i < data_len; i++) {
		int new_bytes_num = bytes_num + 1;
		if(new_bytes_num >= max_len)
			new_bytes_num = bytes_num;

		while(new_bytes_num >= len) {
			int new_len = len + inc_len;
			Resize(new_len);
		}

		int curr_ind = new_bytes_num - 1;
		byte_t byte = data[i];

		byte_arr[curr_ind] = byte;
		bytes_num = new_bytes_num;
	}
}

#if 0
void ByteArray::Append(const unsigned char *data)
{
	int i;
	int data_len = strlen((char *)data);
	for(i = 0; i < data_len; i++) {
		int new_bytes_num = bytes_num + 1;
		if(new_bytes_num >= max_len)
			new_bytes_num = bytes_num;

		while(new_bytes_num >= len) {
			int new_len = len + inc_len;
			Resize(new_len);
		}

		int curr_ind = new_bytes_num - 1;
		byte_t byte = data[i];

		byte_arr[curr_ind] = byte;
		bytes_num = new_bytes_num;
	}
}
#endif

void ByteArray::Clear()
{
	bytes_num = 0;
	int i;
	for(i = 0; i < len; i++)
		byte_arr[i] = 0;
}

void ByteArray::Resize(const int &new_len)
{
	int reinit_len;
	reinit_len = (new_len > max_len) ? (max_len) : (new_len);
	reinit_len = (new_len < min_len) ? (inc_len) : (new_len);
	
	byte_t *new_barr = new byte_t[reinit_len];

	int i;
	if(reinit_len > len) {
		for(i = 0; i < reinit_len; i++)
			new_barr[i] = (i  >= len) ? (0) : (byte_arr[i]);
	} else if(reinit_len < len) {
		for(i = 0; i < reinit_len; i++)
			new_barr[i] = byte_arr[i];
	}

	delete[] byte_arr;

	len = reinit_len;
	byte_arr = new_barr;
}

byte_t &ByteArray::operator[](const int &ind)
{
	int new_ind = ind;
	if(ind >= max_len)
		new_ind = max_len - 1;

	while(new_ind >= len) {
		int new_len = len + inc_len;
		Resize(new_len);
	}

	return byte_arr[new_ind];
}

void ByteArray::ToStr(char *byte_str, int size)
{
	if((!bytes_num) || (size <= bytes_num))
		return;

	int i;
	for(i = 0; i < bytes_num; i++) {
		byte_str[i] = byte_arr[i];
	}
	byte_str[bytes_num] = '\0';
}

void ByteArray::ToStr(char *byte_str)
{
	int str_size = sizeof(byte_str);
	if((!bytes_num) || (str_size <= bytes_num))
		return;

	int i;
	for(i = 0; i < bytes_num; i++) {
#if 0
		if(byte_arr[i] == '\r') {
			byte_str[i] = '\n';
			continue;
		}
#endif
		byte_str[i] = byte_arr[i];
	}
	byte_str[bytes_num] = '\0';
}
