#ifndef ROTATORMANAGER_HPP_SENTRY
#define ROTATORMANAGER_HPP_SENTRY

#include "devicemanager.hpp"
#include "bytearray.hpp"

class RotatorManager : public DeviceManager {
private:
public:
	RotatorManager();
	virtual ~RotatorManager();

	virtual bool FormSetSpeed(ByteArray &command, float speed) = 0;
	virtual bool FormGetSpeed(ByteArray &command) = 0;
	virtual bool FormRotate(ByteArray &command, float angle) = 0;
	virtual bool FormStop(ByteArray &command) = 0;
	virtual bool FormSetAccel(ByteArray &command, float accel) = 0;
	virtual bool FormGetParams(ByteArray &command, int axis) = 0;
	virtual bool FormRatioCalib(ByteArray &command, int axis, float angle) = 0;
	virtual bool FormAbsCalib(ByteArray &command) = 0;
	virtual bool FormReset(ByteArray &command) = 0;
	virtual bool FormAutoTime(ByteArray &command, int time) = 0;
	virtual bool FormSetLimit(ByteArray &command, int axis, bool limit_flag) = 0;
	virtual bool FormSetMin(ByteArray &command, int axis, int angle) = 0;
	virtual bool FormSetMax(ByteArray &command, int axis, int angle) = 0;
	virtual bool FormAutoCoord(ByteArray &command, int axis, int angle) = 0;
	virtual bool FormGetPos(ByteArray &command) = 0;
	virtual bool FormGetSignature(ByteArray &command) = 0;
	virtual bool FormAutoRotate(ByteArray &command, int axis, void *rotate_params) = 0;
#if 0
	virtual bool DecodeGetSpeed(const QByteArray &answer, QString &decode_answer) = 0;
	virtual bool DecodeGetParams(const QByteArray &answer, QString &decode_answer) = 0;
	virtual bool DecodeGetPos(const QByteArray &answer, QString &decode_answer) = 0;
#endif
	virtual bool CheckErr(ByteArray &answer) = 0;
};

#endif
