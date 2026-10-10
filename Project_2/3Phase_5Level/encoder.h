#ifndef ENCODER_H
#define ENCODER_H

#include "stdint.h"

#define ENCODER_0_DEG						0.0f
#define ENCODER_30_DEG						30.0f
#define ENCODER_60_DEG						60.0f
#define ENCODER_90_DEG						90.0f
#define ENCODER_120_DEG						120.0f
#define ENCODER_360_DEG						360.0f
#define ENCODER_STEP_INVALID				0x0A

typedef enum
{
	ENCODER_OK					= 0,
	ENCODER_ERROR				= 1
}ENCODER_STATUS;

typedef struct encoder_t				ENCODER_Sensor;
typedef struct encoder_speed_t			ENCODER_Speed;

/****************************************************************************************/

struct encoder_speed_t {

	uint32_t counter;

	float speed_rpm;
	float speed_radps;
	float speed_kmph;
	float speed_rpm_filter;
	float speed_radps_filter;
};
void encoder_speed_init(ENCODER_Sensor* p_ss);
static void encoder_speed_update_speed(ENCODER_Sensor* p_ss);
static float encoder_speed_get_rpm(ENCODER_Sensor* p_ss);
static float encoder_speed_get_radps(ENCODER_Sensor* p_ss);

/****************************************************************************************/
struct encoder_t {

	int pulse_A;
	int pulse_B;
	int pulse_Z;
	
	ENCODER_Speed speed;

};
void encoder_sensor_init(ENCODER_Sensor* p_ss);
static void encoder_sensor_calculate_speed(ENCODER_Sensor* p_ss);
static void encoder_sensor_calculate_angle(ENCODER_Sensor* p_ss);

/****************************************************************************************/
#endif