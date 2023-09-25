#ifndef FILEMANAGER_HPP_SENTRY
#define FILEMANAGER_HPP_SENTRY

#include <stdio.h>

class ByteArray;

class FileManager {
	FILE *fd;
public:
	FileManager();
	~FileManager();
	
	bool Open(const char *file_name, const char *file_params);
	void Close();
	bool Write(const char *data, int len);
	bool Read(char *data, int len);
	bool Read(ByteArray &data, int len);
	bool Read(ByteArray &data);
	bool Copy(const char *file_name);
	bool CopyBinary(const char *file_name);
	void SetPos(const int pos);
	void SetStartPos();
	char *GetErr();
	void GetErr(char *str);
	void GetErr(char *str, int len);
	int GetCurrentPos();
	int GetRestFileSize();
	int GetFileSize();

};

#endif
