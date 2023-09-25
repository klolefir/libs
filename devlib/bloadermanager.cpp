#include "bloadermanager.hpp"
#include "bytearray.hpp"

#include <arpa/inet.h>
#include <string.h>

BloaderManager::BloaderManager() :
	status(bl_ok)
{

}

BloaderManager::~BloaderManager()
{

}

void BloaderManager::FormReset(ByteArray &cmd)
{
#if 0
	cmd.AppendWord(htons(bl_sig_out));
	cmd.AppendDoubleWord(htonl(bl_cmd_reset));
#else
	cmd.AppendWord((bl_sig_out));
	cmd.AppendDoubleWord((bl_cmd_reset));
#endif
}

void BloaderManager::FormGoMain(ByteArray &cmd)
{
	cmd.AppendWord(bl_sig_out);
	cmd.AppendDoubleWord(bl_cmd_gomain);
}

void BloaderManager::FormRead(ByteArray &cmd, unsigned int addr, unsigned int len)
{
#if 0
	cmd.AppendWord(htons(bl_sig_out));
	cmd.AppendDoubleWord(htonl(bl_cmd_read));
	cmd.AppendDoubleWord(htonl(addr));
	cmd.AppendDoubleWord(htonl(len));
#else
	cmd.AppendWord((bl_sig_out));
	cmd.AppendDoubleWord((bl_cmd_read));
	cmd.AppendDoubleWord((addr));
	cmd.AppendDoubleWord((len));
#endif
}

void BloaderManager::FormWrite(ByteArray &cmd, unsigned int addr, unsigned int len, ByteArray &data)
{
	cmd.AppendWord(bl_sig_out);
	cmd.AppendDoubleWord(bl_cmd_write);
	cmd.AppendDoubleWord(addr);
	cmd.AppendDoubleWord(len);
	cmd.Append(data); 
}

void BloaderManager::FormErase(ByteArray &cmd, unsigned int addr, unsigned int len)
{
	cmd.AppendWord(bl_sig_out);
	cmd.AppendDoubleWord(bl_cmd_erase);
	cmd.AppendDoubleWord(addr);
	cmd.AppendDoubleWord(len);
}

void BloaderManager::FormTest(ByteArray &cmd)
{
	cmd.AppendWord(htons(bl_sig_out));
	cmd.AppendDoubleWord(htonl(bl_cmd_test));
}

void BloaderManager::Decode(ByteArray &cmd, unsigned int &addr, unsigned int &len)
{
	unsigned short sig;
	memcpy(&sig, &cmd[bl_sig_pos], bl_sig_size);
/*	unsigned int new_status;*/
	bl_status_t new_status;
	memcpy(&new_status, &cmd[bl_status_pos], bl_status_size);
	memcpy(&addr, &cmd[bl_addr_pos], bl_addr_size);
	memcpy(&len, &cmd[bl_len_pos], bl_len_size);

	if(sig == bl_esig_in)
		SetStatus(new_status);
	else if(sig == bl_sig_in)
		SetStatus(bl_ok);
	else
		SetStatus(bl_bsig);
}
