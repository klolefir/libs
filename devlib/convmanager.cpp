#include "convmanager.hpp"
#include "bytearray.hpp"

#include <arpa/inet.h>
#include <string.h>

ConvManager::ConvManager()
{

}

ConvManager::~ConvManager()
{

}

unsigned short ConvManager::CalculateCRC16(const ByteArray &cmd)
{
	int i, j;
	unsigned short len, crc;
	byte_t *byte_arr = cmd.GetArr();

	len = cmd.GetBytesNum();	
	crc = conv_crc_init;

	for(i = 0; i < len; i++) {
		crc ^= byte_arr[i] << 8;
		for(j = 0; j < 8; j++)
			crc = crc & 0x8000 ? (crc << 1) ^ conv_crc_poly : (crc << 1);
	}
	return crc;
#if 0
	while(len) {
		crc16 ^= *data++ << 8;
		for(int i = 0; i < 8; i++)
			crc16 = crc16 & 0x8000 ? (crc16 << 1) ^ poly : (crc16 << 1);

		len--;
	}
#endif

}

void ConvManager::FormReadByte(ByteArray &cmd, unsigned int regaddr)
{
	unsigned short crc;
#if 0
	cmd.AppendWord(htons(bl_sig_out));
	cmd.AppendDoubleWord(htonl(bl_cmd_read));
	cmd.AppendDoubleWord(htonl(addr));
	cmd.AppendDoubleWord(htonl(len));
#else
	cmd.Append(conv_sig_out);
	cmd.Append(conv_cmd_readbyte);
	cmd.Append(conv_devaddr);
	cmd.Append(conv_addrspace);
	cmd.AppendDoubleWord(regaddr);
	crc = CalculateCRC16(cmd);
	cmd.AppendWord(crc);
#endif
}

void ConvManager::FormWriteByte(ByteArray &cmd, unsigned int regaddr, unsigned char data)
{
	unsigned short crc;
	unsigned char dummy = 0x00;
	cmd.Append(conv_sig_out);
	cmd.Append(conv_cmd_writebyte);
	cmd.Append(conv_devaddr);
	cmd.Append(conv_addrspace);
	cmd.AppendDoubleWord(regaddr);
	cmd.Append(data);
	cmd.Append(dummy);
	cmd.Append(dummy);
	cmd.Append(dummy);
	crc = CalculateCRC16(cmd);
	cmd.AppendWord(crc);
}

#if 0
void BloaderManager::Decode(ByteArray &cmd, unsigned int &addr, unsigned int &len)
{
	unsigned short sig;
	memcpy(&sig, &cmd[bl_sig_pos], bl_sig_size);
/*	unsigned int new_status;*/
	bl_status_t new_status;
	memcpy(&new_status, &cmd[bl_status_pos], bl_status_size);
	memcpy(&addr, &cmd[bl_addr_pos], bl_addr_size);
	memcpy(&len, &cmd[bl_len_pos], bl_len_size);

	if(sig != bl_sig_in)
		SetStatus(bl_bsig);
	else
		SetStatus(new_status);
}
#endif

void ConvManager::FormTest(ByteArray &cmd)
{
	unsigned short crc;
	cmd.Append(conv_sig_out);
	cmd.Append(conv_cmd_test);
	crc = CalculateCRC16(cmd);
	cmd.AppendWord(crc);
}
