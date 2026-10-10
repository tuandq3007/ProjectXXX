#ifndef USER_H
#define USER_H

#include "config.h"

#define ENCODER_0_DEG						0.0f
#define ENCODER_30_DEG						30.0f
#define ENCODER_60_DEG						60.0f
#define ENCODER_90_DEG						90.0f
#define ENCODER_120_DEG						120.0f
#define ENCODER_360_DEG						360.0f
#define ENCODER_STEP_INVALID				0x0A

#define DC_BATERRY							100.0f
#define DC_BATERRY_1_DIV_SQRT_3				(0.575f*DC_BATERRY)
#define MAX_DUTY							0.95f
#define VD_VQ_MAX							(MAX_DUTY * DC_BATERRY_1_DIV_SQRT_3)
#define PWM_FRQ_KHZ							10UL

#if LOAD_IM_MOTOR

/* Motor parameter */
#define USER_MOTOR_Rs					0.895f		//Ohm
#define USER_MOTOR_Ls					0.000012f 	//H
#define USER_MOTOR_Rr					0.914f		//Ohm
#define USER_MOTOR_Lr					0.000012f 	//H
#define USER_MOTOR_Lm					0.000125f 	//H
#define USER_MOTOR_Ts					(USER_MOTOR_Ls/USER_MOTOR_Rs)
#define USER_MOTOR_Tr					(USER_MOTOR_Lr/USER_MOTOR_Rr)
#define USER_MOTOR_x					1.0f-(USER_MOTOR_Lm*USER_MOTOR_Lm/USER_MOTOR_Ls*USER_MOTOR_Lr) // xich ma

#define RADS_FROM_RPM					(0.104720f)
#define RPM_FROM_RADPS					(9.5492968f)

/* Stator current controller parameter*/
#define FOC_ID_KI						300.0f//61.0f//300.0f
#define FOC_ID_KP						0.25f//0.1f//0.25f
#define FOC_ID_KC						(1.0f/FOC_ID_KP)

#define FOC_IQ_KI						300.0f//61.0f//300.0f
#define FOC_IQ_KP						(FOC_ID_KP*1.3f) //0.85f
#define FOC_IQ_KC						(1.0f/FOC_IQ_KP)

/* Speed limit controller parameter */
#define SLC_KI							1.0f//3.0f //19.0f
#define SLC_KP							7.0f//12.5f //22.8f
#define SLC_KC							(1.0f/SLC_KP)
#define SLC_TD							4.096f			/* TD_scaled= 1e-3* 2^12 = 4.096 */

#endif

#if LOAD_RL

/* Motor parameter */
#define USER_MOTOR_Rs					0.895f		//Ohm
#define USER_MOTOR_Ls					0.000012f 	//H
#define USER_MOTOR_Rr					0.914f		//Ohm
#define USER_MOTOR_Lr					0.000012f 	//H
#define USER_MOTOR_Lm					0.000125f 	//H
#define USER_MOTOR_Ts					(USER_MOTOR_Ls/USER_MOTOR_Rs)
#define USER_MOTOR_Tr					(USER_MOTOR_Lr/USER_MOTOR_Rr)
#define USER_MOTOR_x					1.0f-(USER_MOTOR_Lm*USER_MOTOR_Lm/USER_MOTOR_Ls*USER_MOTOR_Lr) // xich ma

#define RADS_FROM_RPM					(0.104720f)
#define RPM_FROM_RADPS					(9.5492968f)

/* Stator current controller parameter*/
#define FOC_ID_KI						300.0f//61.0f//300.0f
#define FOC_ID_KP						0.25f//0.1f//0.25f
#define FOC_ID_KC						(1.0f/FOC_ID_KP)

#define FOC_IQ_KI						300.0f//61.0f//300.0f
#define FOC_IQ_KP						(FOC_ID_KP*1.3f) //0.85f
#define FOC_IQ_KC						(1.0f/FOC_IQ_KP)

/* Speed limit controller parameter */
#define SLC_KI							1.0f//3.0f //19.0f
#define SLC_KP							7.0f//12.5f //22.8f
#define SLC_KC							(1.0f/SLC_KP)
#define SLC_TD							4.096f			/* TD_scaled= 1e-3* 2^12 = 4.096 */

#endif

#if LOAD_IPMSMM_MOTOR

/* Motor parameter */
#define USER_MOTOR_Rs					0.895f		//Ohm
#define USER_MOTOR_Ls					0.000012f 	//H
#define USER_MOTOR_Rr					0.914f		//Ohm
#define USER_MOTOR_Lr					0.000012f 	//H
#define USER_MOTOR_Lm					0.000125f 	//H
#define USER_MOTOR_Ts					(USER_MOTOR_Ls/USER_MOTOR_Rs)
#define USER_MOTOR_Tr					(USER_MOTOR_Lr/USER_MOTOR_Rr)
#define USER_MOTOR_x					1.0f-(USER_MOTOR_Lm*USER_MOTOR_Lm/USER_MOTOR_Ls*USER_MOTOR_Lr) // xich ma

#define RADS_FROM_RPM					(0.104720f)
#define RPM_FROM_RADPS					(9.5492968f)

/* Stator current controller parameter*/
#define FOC_ID_KI						300.0f//61.0f//300.0f
#define FOC_ID_KP						0.25f//0.1f//0.25f
#define FOC_ID_KC						(1.0f/FOC_ID_KP)

#define FOC_IQ_KI						300.0f//61.0f//300.0f
#define FOC_IQ_KP						(FOC_ID_KP*1.3f) //0.85f
#define FOC_IQ_KC						(1.0f/FOC_IQ_KP)

/* Speed limit controller parameter */
#define SLC_KI							1.0f//3.0f //19.0f
#define SLC_KP							7.0f//12.5f //22.8f
#define SLC_KC							(1.0f/SLC_KP)
#define SLC_TD							4.096f			/* TD_scaled= 1e-3* 2^12 = 4.096 */

#endif
/****************************************************************************************/
#endif