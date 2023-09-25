#include "filemanager.hpp"
#include <errno.h>
#include <string.h>

#include "bytearray.hpp"

FileManager::FileManager() :
	fd(0)
{
	
}

FileManager::~FileManager()
{
	Close();
}

bool FileManager::Open(const char *file_name, const char *file_params)
{
	fd = fopen(file_name, file_params);
	if(!fd)
		return false;
	return true;
}

int FileManager::GetCurrentPos()
{
	int pos = ftell(fd);
	return pos;
}

int FileManager::GetRestFileSize()
{
	int curr_pos = GetCurrentPos();
	int size = GetFileSize();
	int rest = size - curr_pos;
	return rest;
}

void FileManager::SetPos(const int pos)
{
	fseek(fd, pos, SEEK_SET);
}

void FileManager::SetStartPos()
{
	fseek(fd, 0, SEEK_SET);
}

int FileManager::GetFileSize()
{
	int pos = GetCurrentPos();
	fseek(fd, 0, SEEK_END);
	int size = ftell(fd);
	fseek(fd, pos, SEEK_SET);
	return size;
}

bool FileManager::Write(const char *data, int len)
{
	int i;
	for(i = 0; i < len; i++)
		fputc(data[i], fd);
	return true;
}

bool FileManager::Read(char *data, int len)
{
	int i;
	int curr_size = GetRestFileSize();
	if(len > curr_size) {
		len = curr_size;
	}

	for(i = 0; i < len; i++)
		data[i] = fgetc(fd); 
	return true;
}

bool FileManager::Read(ByteArray &data, int len)
{
	int i;
	char c;
	int curr_size = GetRestFileSize();

	if(len > curr_size) {
		len = curr_size;
	}

	for(i = 0; i < len; i++) {
		c = fgetc(fd);
		data.Append(c);
	}
	return true;
}

bool FileManager::Read(ByteArray &data)
{
	int i;
	char c;
	int curr_size = GetRestFileSize();

	for(i = 0; i < curr_size; i++) {
		c = fgetc(fd);
		data.Append(c);
	}
	return true;
}

bool FileManager::Copy(const char *file_name)
{
	FILE *cfd = fopen(file_name, "w");
	if(!cfd)
		return false;

	int size = GetFileSize();
	int i;
	char c;
	for(i = 0; i < size; i++) {
		c = fgetc(fd);
		fputc(c, cfd);
	}
	fclose(cfd);
	return true;
	
}

bool FileManager::CopyBinary(const char *file_name)
{
	FILE *cfd = fopen(file_name, "w+b");
	if(!cfd)
		return false;

	int size = GetFileSize();
	int i;
	char c;
	for(i = 0; i < size; i++) {
		c = fgetc(fd);
		fputc(c, cfd);
	}
	fclose(cfd);
	return true;
}

void FileManager::Close()
{
	if(fd) {
		fclose(fd);
		fd = 0;
	}
}

char *FileManager::GetErr()
{
	char *err_str = strerror(errno);
	return err_str;
}

void FileManager::GetErr(char *str)
{
	char *err_str = strerror(errno);
	strcpy(str, err_str);
}

void FileManager::GetErr(char *str, int len)
{
	char *err_str = strerror(errno);
	strncpy(str, err_str, len);
}

