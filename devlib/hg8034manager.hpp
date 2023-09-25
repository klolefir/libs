#ifndef HG8034MANAGER_HPP_SENTRY
#define HG8034MANAGER_HPP_SENTRY

#include "rotatormanager.hpp"

class ByteArray;

enum {
	azimuth = '0'
};

struct HG8034Params {
	int axis;
	int min_angle;
	int max_angle;
	int accel;
	int limit;
};

struct RotateParams {
	int from_angle;
	int to_angle;
	int count;
};

class HG8034Manager : public RotatorManager {
private:
	enum {
		rotate_sig			= 'Q',
		set_speed_sig		= 'X',
		set_accel_sig		= 'I',
		get_speed_sig		= 'H',
		get_pos_sig			= 'Y',
		stop_sig			= 'S',
		abs_calib_sig		= 'C',
		auto_time_sig		= 'T',
		reset_sig			= 'R',

		major_sig			= 'G',
		ratio_calib_sig		= 'C',
		set_limit_sig		= 'L',
		set_min_sig			= 'A',
		set_max_sig			= 'B',
		auto_rotate_sig		= 'W',
		auto_coord_sig		= 'M',
		get_signature_sig	= 'H',
		get_params_sig		= 'I',


		terminal_sig		= '\r'
	};
public:
	HG8034Manager();
	virtual ~HG8034Manager();
	
	virtual bool FormSetSpeed(ByteArray &command, float speed);
	virtual bool FormGetSpeed(ByteArray &command);
	virtual bool FormRotate(ByteArray &command, float angle);
	virtual bool FormStop(ByteArray &command);
	virtual bool FormSetAccel(ByteArray &command, float accel);
	virtual bool FormGetParams(ByteArray &command, int axis);
	virtual bool FormRatioCalib(ByteArray &command, int axis, float angle);
	virtual bool FormAbsCalib(ByteArray &command);
	virtual bool FormReset(ByteArray &command);
	virtual bool FormAutoCoord(ByteArray &command, int axis, int angle);
	virtual bool FormAutoTime(ByteArray &command, int time);
#if 1
	virtual bool FormSetLimit(ByteArray &command, int axis, bool limit_flag);
	virtual bool FormSetMin(ByteArray &command, int axis, int angle);
	virtual bool FormSetMax(ByteArray &command, int axis, int angle);
	virtual bool FormGetPos(ByteArray &command);
	virtual bool FormGetSignature(ByteArray &command);
	virtual bool FormAutoRotate(ByteArray &command, int axis, void *rotate_params);

#if 0
	virtual bool DecodeGetParams(const ByteArray &answer, QString &decode_answer);
	virtual bool DecodeGetSpeed(const ByteArray &answer, QString &decode_answer);
	virtual bool DecodeGetPos(const ByteArray &answer, QString &decode_answer);
#endif
	virtual bool CheckErr(ByteArray &answer);
#endif
};

#endif
