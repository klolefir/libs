#ifndef BLOADERMANAGER_HPP_SENTRY
#define BLOADERMANAGER_HPP_SENTRY

#include "devicemanager.hpp"

class ByteArray;

enum { /* bytes */
	bl_page_size = 256
};

enum {
	bl_sig_out		= 0xF9BE,
	bl_sig_in		= 0xBEF9,
	bl_esig_in		= 0xBEFE
};

enum { /* byte */
	bl_sig_pos 		= 0,
	bl_cmd_pos 		= bl_sig_pos + 2,
	bl_status_pos 	= bl_cmd_pos,
	bl_addr_pos 	= bl_sig_pos + 6,
	bl_len_pos		= bl_sig_pos + 10,
	bl_data_pos 	= bl_sig_pos + 14
};

enum {
	bl_sig_size 	= 2,
	bl_cmd_size 	= 4,
	bl_status_size 	= bl_cmd_size,
	bl_addr_size 	= 4,
	bl_len_size 	= 4
};

enum {
	bl_cmd_reset 	= 0x00000002,
	bl_cmd_gomain 	= 0x00000003,
	bl_cmd_write	= 0x00000004,
	bl_cmd_read		= 0x00000005,
	bl_cmd_erase	= 0x00000006,
	bl_cmd_test		= 0x00000007
};

typedef enum {
#if 0
	bl_ok_erase		= 0x000000A0,
	bl_bad_erase 	= 0x000000E0,
	bl_ok_write		= 0x000000A1,
	bl_bad_write 	= 0x000000E1,
	bl_ok_read		= 0x000000A2,
	bl_bad_read 	= 0x000000E2,
	bl_bad_len	 	= 0x000000E3,
#endif
	bl_ok			= 0x000000AA,
	bl_busy			= 0x000000E4,
	bl_pgerr		= 0x000000E5,
	bl_pgaerr		= 0x000000E6,
	bl_wperr		= 0x000000E7,
	bl_toerr		= 0x000000E8,
	bl_blen			= 0x000000E9,
	bl_none			= 0x000000EE,
	bl_bcmd			= 0x000000EA,
	bl_baddr		= 0x000000EB,
	bl_bsig
} bl_status_t;

class BloaderManager : public DeviceManager {
private:
	bl_status_t status;
public:
	BloaderManager();
	~BloaderManager();
	void FormReset(ByteArray &cmd);
	void FormGoMain(ByteArray &cmd);
	void FormErase(ByteArray &cmd, unsigned int addr, unsigned int len);
	void FormRead(ByteArray &cmd, unsigned int addr, unsigned int len);
	void FormWrite(ByteArray &cmd, unsigned int addr, unsigned int len, ByteArray &data);
	void FormTest(ByteArray &cmd);
	void Decode(ByteArray &cmd, unsigned int &addr, unsigned int &len);
	bl_status_t GetStatus() const { return status; } 
private:
	void SetStatus(bl_status_t new_status) { status = new_status; }
};

#endif
