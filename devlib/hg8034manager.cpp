#include "hg8034manager.hpp"
#include "bytearray.hpp"

#include <stdio.h>
#include <string.h>

static void FloatAngleToStr(float angle, char *angle_str);
static void IntAngleToStr(int angle, char *angle_str);

HG8034Manager::HG8034Manager()
{

}

HG8034Manager::~HG8034Manager()
{

}

bool HG8034Manager::FormSetSpeed(ByteArray &command, float speed)
{
	command.Append(set_speed_sig);
	char speed_str[10];
	snprintf(speed_str, sizeof(speed_str) - 1, "%04.1f", speed);
	command.Append(speed_str);
	command.Append(terminal_sig);
	return true;
}

bool HG8034Manager::FormGetSpeed(ByteArray &command)
{
	command.Append(get_speed_sig);
	command.Append(terminal_sig);
	return true;
}

bool HG8034Manager::FormRotate(ByteArray &command, float angle)
{
	command.Append(rotate_sig);
	char angle_str[10];
	FloatAngleToStr(angle, angle_str);
	command.Append(angle_str);
	command.Append(terminal_sig);
	return true;
}

bool HG8034Manager::FormStop(ByteArray &command)
{
	command.Append(stop_sig); 
	command.Append(terminal_sig);
	return true;
}

bool HG8034Manager::FormSetAccel(ByteArray &command, float accel)
{
	command.Append(set_accel_sig);
	char accel_str[10];
	sprintf(accel_str, "%1.1f", accel);
	command.Append(accel_str);
	command.Append(terminal_sig);
	return true;
}

bool HG8034Manager::FormGetParams(ByteArray &command, int axis)
{
	command.Append(major_sig);
	command.Append(axis);
	command.Append(get_params_sig);
	command.Append(terminal_sig);
	return true;
}

bool HG8034Manager::FormRatioCalib(ByteArray &command, int axis, float angle)
{
	command.Append(major_sig);
	command.Append(axis);
	command.Append(ratio_calib_sig);
	char angle_str[10];
	FloatAngleToStr(angle, angle_str);
	command.Append(angle_str);
	command.Append(terminal_sig);
	return true;
}


bool HG8034Manager::FormAbsCalib(ByteArray &command)
{
	command.Append(abs_calib_sig);
	command.Append(terminal_sig);
	return true;
}

bool HG8034Manager::FormAutoTime(ByteArray &command, int time)
{
	command.Append(auto_time_sig);
	char angle_str[10];
	IntAngleToStr(time, angle_str);
	command.Append(angle_str);
	command.Append(terminal_sig);
	return true;
}


bool HG8034Manager::FormReset(ByteArray &command)
{
	command.Append(reset_sig);
	command.Append(terminal_sig);
	return true;
}


bool HG8034Manager::FormSetMax(ByteArray &command, int axis, int angle)
{
	command.Append(major_sig);
	command.Append(axis);
	command.Append(set_max_sig);
	char angle_str[10];
	IntAngleToStr(angle, angle_str);
	command.Append(angle_str);
	command.Append(terminal_sig);
	return true;
}

bool HG8034Manager::FormSetMin(ByteArray &command, int axis, int angle) {
	command.Append(major_sig);
	command.Append(axis);
	command.Append(set_min_sig);
	char angle_str[10];
	IntAngleToStr(angle, angle_str);
	command.Append(angle_str);
	command.Append(terminal_sig);
	return true;
}

bool HG8034Manager::FormSetLimit(ByteArray &command, int axis, bool limit_flag)
{
	command.Append(major_sig);
	command.Append(axis);
	command.Append(set_limit_sig);
	(limit_flag) ? command.Append('1') : command.Append('0');
	command.Append(terminal_sig);
	return true;
}

bool HG8034Manager::FormAutoRotate(ByteArray &command, int axis, void *rotate_params)
{
	command.Append(major_sig);
	command.Append(axis);
	command.Append(auto_rotate_sig);
	/*AutoBox::RotateParams *params = static_cast<RotateParams *>(rotate_params);*/
	RotateParams *params = static_cast<RotateParams *>(rotate_params);
	char angle_str[10];	
	int from_angle, to_angle, count;
	from_angle = params->from_angle;
	to_angle = params->to_angle;	
	count = params->count;

	IntAngleToStr(from_angle, angle_str);
	command.Append(angle_str);
	command.Append(' ');

	IntAngleToStr(to_angle, angle_str);
	command.Append(angle_str);
	command.Append(' ');

	snprintf(angle_str, sizeof(angle_str) - 1, "%d", count);
	command.Append(angle_str);

	command.Append(terminal_sig);
	return true;
}
#if 0
bool HG8034Manager::FormAutoRotate(ByteArray &command, int axis, void *rotate_params)
{
	command.Append(major_sig);
	command.Append(axis);
	command.Append(auto_rotate_sig);
	AutoBox::RotateParams *params = static_cast<AutoBox::RotateParams *>(rotate_params);
	char angle_str[10];	
	int from_angle, to_angle, count;
	from_angle = params->from_angle;	
	to_angle = params->to_angle;	
	count = params->count;

	IntAngleToStr(from_angle, angle_str);
	command.Append(angle_str);
	command.Append(' ');

	IntAngleToStr(to_angle, angle_str);
	command.Append(angle_str);
	command.Append(' ');

	snprintf(angle_str, sizeof(angle_str) - 1, "%d", count);
	command.Append(angle_str);

	command.Append(terminal_sig);
	return true;
}
#endif

bool HG8034Manager::FormAutoCoord(ByteArray &command, int axis, int angle)
{
	command.Append(major_sig);
	command.Append(axis);
	command.Append(auto_coord_sig);
	char angle_str[10];
	IntAngleToStr(angle, angle_str);
	command.Append(angle_str);
	command.Append(terminal_sig);
	return true;
}

bool HG8034Manager::FormGetPos(ByteArray &command)
{
	command.Append(get_pos_sig);
	command.Append(terminal_sig);
	return true;
}

bool HG8034Manager::FormGetSignature(ByteArray &command)
{
	command.Append(major_sig);
	command.Append('0');
	command.Append(get_signature_sig);
	command.Append(terminal_sig);
	return true;
}

#if 0
bool HG8034Manager::DecodeGetParams(const ByteArray &answer, QString &decode_answer)
{
	bool err = CheckErr(answer);
	if(err)
		return false;
	
	decode_answer = answer.data();
	return true;
}

bool HG8034Manager::DecodeGetSpeed(const ByteArray &answer, QString &decode_answer)
{
	bool err = CheckErr(answer);
	if(err)
		return false;
	
	decode_answer = answer.data();
	return true;
}

bool HG8034Manager::DecodeGetPos(const ByteArray &answer, QString &decode_answer)
{
	bool err = CheckErr(answer);
	if(err)
		return false;
	
	decode_answer = answer.data();
	return true;
}
#endif

bool HG8034Manager::CheckErr(ByteArray &answer)
{
	const char err_str[] = "ERR!\r";
	char answer_str[100];
	answer.ToStr(answer_str);
	bool is_equal = strcmp(answer_str, err_str);
	if(!is_equal)
		return true;
	return false;
}

void FloatAngleToStr(float angle, char *angle_str)
{
	if(angle >= 0) {
		snprintf(angle_str, sizeof(angle_str) - 1, "%06.2f", angle);
	} else {
		char buff_str[8];
		float right_angle = -angle; 
		snprintf(buff_str, sizeof(buff_str) - 1, "%06.2f", right_angle);
		snprintf(angle_str, sizeof(angle_str) - 1, "-");
		strcat(angle_str, buff_str);
	}
}

void IntAngleToStr(int angle, char *angle_str)
{
	if(angle >= 0)
		snprintf(angle_str, sizeof(angle_str) - 1, "%03d", angle);
	else
		snprintf(angle_str, sizeof(angle_str) - 1, "%04d", angle);
}

