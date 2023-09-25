#ifndef CONVMANAGER_HPP_SENTRY
#define CONVMANAGER_HPP_SENTRY

#include "devicemanager.hpp"

class ByteArray;

enum {
	conv_sig_in 	= 0xBA,
	conv_sig_out 	= 0xAB
};

enum { /*bytes*/
	conv_block_maxsize 	= 256,
	conv_devaddr 		= 0x01,
	conv_addrspace		= 0x01
};

enum { /*bytes*/
	conv_instr_size 	= 2,
	conv_sig_size 		= 1,
	conv_cmd_size 		= 1,


	conv_addr_size 		= 2,
	conv_devaddr_size 	= 1,
	conv_addrspace_size = 1,

	conv_regaddr_size	= 4,
	conv_regaddr3_size	= 1,
	conv_regaddr2_size	= 1,
	conv_regaddr1_size	= 1,
	conv_regaddr0_size	= 1,

	conv_data_size		= 4,
	conv_data3_size		= 1,
	conv_data2_size		= 1,
	conv_data1_size		= 1,
	conv_data0_size		= 1,

	conv_crc_size		= 2
};

enum {
	conv_instr_pos		= 0,
	conv_sig_pos		= conv_instr_pos,
	conv_cmd_pos		= conv_instr_pos + 1,

	conv_addr_pos		= 2,
	conv_devaddr_pos	= conv_addr_pos,
	conv_addrspace_pos	= conv_addr_pos + 1,

	conv_regaddr_pos	= 4,
	conv_regaddr3_pos	= conv_regaddr_pos,
	conv_regaddr2_pos	= conv_regaddr_pos + 1,
	conv_regaddr1_pos	= conv_regaddr_pos + 2,
	conv_regaddr0_pos	= conv_regaddr_pos + 3,

	conv_data_pos		= 8,
	conv_data3_pos		= conv_data_pos, 
	conv_data2_pos		= conv_data_pos + 1,
	conv_data1_pos		= conv_data_pos + 2,
	conv_data0_pos		= conv_data_pos + 3,
};

enum {
	conv_addrspace_blockparams 	= 0x00,
	conv_addrspace_chparams 	= 0x01,
	conv_addrspace_chelement 	= 0x02,
	conv_addrspace_rom 			= 0x03,
	conv_addrspace_telemetry 	= 0x04,
	conv_addrspace_strobeform 	= 0x05,
	conv_addrspace_extradata 	= 0x06,
	conv_addrspace_ipsettings 	= 0x07
};

enum {
	conv_crc_init = 0xFFFF,
	conv_crc_poly = 0x1021
};

enum {
	conv_cmd_readbit 	= 0xA0,
	conv_cmd_readbyte 	= 0xA1,
	conv_cmd_readword	= 0xA2,
	conv_cmd_readdword	= 0xA3,

	conv_cmd_writebit 	= 0xA4,
	conv_cmd_writebyte 	= 0xA5,
	conv_cmd_writeword 	= 0xA6,
	conv_cmd_writedword = 0xA7,

	conv_cmd_test		= 0x88
};

class ConvManager : public DeviceManager {
private:
public:
	ConvManager();
	~ConvManager();
	unsigned short CalculateCRC16(const ByteArray &cmd);
	void FormReadByte(ByteArray &cmd, unsigned int addr);
	void FormWriteByte(ByteArray &cmd, unsigned int addr, unsigned char data);
	void FormTest(ByteArray &cmd);
	/*void Decode(ByteArray &cmd);*/
	/*bl_status_t GetStatus() const { return status; }*/
private:
	/*void SetStatus(bl_status_t new_status) { status = new_status; }*/
};

#endif
