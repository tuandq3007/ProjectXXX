#ifndef CONTROL_PID_H_
#define CONTROL_PID_H_

#include "math.h"
#include "maths.h"
#include "stdint.h"
#include "user.h"

typedef struct parameter_t PARA;
struct parameter_t {
	// Configuration variables - specified by user. Controller does not change
	float kp;             // Proportional gain term * 2^8 (scaling for integer math)
	float ki;             // Integral gain term * 2^8 (scaling for integer math)
	float td;             // Td for d/dt calculation (scaled by 2^10)
	float kitd;           // combine Ki*Td		// max = 0.32
	float kc; 			// integral correction gain.
	float I_k;
	float I_k_minus1;
	float P_k;
	float output;
	float error;
};
typedef struct pi_t PI;
struct pi_t {
	float output;      	// Current value of PID controller output
	float vs_max;
	float vs_min;

	float error;
	float ts;

	PARA current_loop;
	PARA speed_loop;
};
void pi_current_loop_init(PI* p_pi){
	p_pi->current_loop.kp			=	0.0f;
	p_pi->current_loop.ki			=	0.0f;
	p_pi->current_loop.td			=	0.0f;
	p_pi->current_loop.kitd			=	0.0f;
	p_pi->current_loop.kc			=	0.0f;
	p_pi->current_loop.I_k			=	0.0f;
	p_pi->current_loop.I_k_minus1	=	0.0f;
	p_pi->current_loop.P_k			=	0.0f;

	p_pi->current_loop.output		=	0.0f;
	p_pi->current_loop.error		=	0.0f;
}
void pi_speed_loop_init(PI* p_pi){
	p_pi->speed_loop.kp			=	0.0f;
	p_pi->speed_loop.ki			=	0.0f;
	p_pi->speed_loop.td			=	0.0f;
	p_pi->speed_loop.kitd		=	0.0f;
	p_pi->speed_loop.kc			=	0.0f;
	p_pi->speed_loop.I_k		=	0.0f;
	p_pi->speed_loop.I_k_minus1	=	0.0f;
	p_pi->speed_loop.P_k		=	0.0f;

	p_pi->output				=	0.0f;
	p_pi->error					=	0.0f;
}
void pi_controller_init(PI* p_pi){
	p_pi->output	=	0;
	p_pi->vs_max	=	VD_VQ_MAX;
	p_pi->vs_min	=	-(1.0f)*VD_VQ_MAX;

	p_pi->error		=	0;
	p_pi->ts		=	0;

	pi_current_loop_init(p_pi);
	pi_speed_loop_init(p_pi);
}
static float pi_saturation(PI* p_pi, float output){
	if (output > p_pi->vs_max)
    {
        output = p_pi->vs_max;
    }
    else if (output < p_pi->vs_min)
    {
        output = p_pi->vs_min;
    }
	return output;
}
static float pi_current_loop_running(PI* p_pi, float error, float vref_output, float vref_output_sat){
	float error_sat = 0;
	error_sat = p_pi->current_loop.kc * (vref_output - vref_output_sat);

	p_pi->current_loop.P_k = p_pi->current_loop.kp * error;				//	P[k] = Kp * e[k]
	p_pi->current_loop.I_k_minus1 = p_pi->current_loop.I_k;				//	I[k-1]

	//	I[k] = I[k-1] + Ki*Ts * (e[k] - Kc*(u_in[k] - u_sat[k]))
	p_pi->current_loop.I_k = p_pi->current_loop.I_k_minus1 + p_pi->current_loop.kitd * (error - error_sat);

	p_pi->current_loop.output = p_pi->current_loop.I_k + p_pi->current_loop.P_k; 
	return p_pi->current_loop.output;
}
float pi_calculate(PI* pi, float reference, float feedback)
{
    pi->error = reference - feedback;
    pi->integral = pi->integral + pi->ki * pi->ts * pi->error;

    // limit tich phan
    if (pi->integral > pi->output_max)
    {
        pi->integral = pi->output_max;
    }
    else if (pi->integral < pi->output_min)
    {
        pi->integral = pi->output_min;
    }

    // PI output
    pi->output = pi->kp * pi->error + pi->integral;

    // limit output
    if (pi->output > pi->output_max)
    {
        pi->output = pi->output_max;
    }
    else if (pi->output < pi->output_min)
    {
        pi->output = pi->output_min;
    }

    return pi->output;
}
static void ri_pi_decoupling(PI* p_pi, const float id_feedback,
		const float iq_feedback, const float e_speed_radps)
{
	float vd_ff = 0;
	float vq_ff = 0;
	vd_ff = p_pi->ls_q * iq_feedback ;
	vd_ff *= e_speed_radps;

	vq_ff = p_pi->ls_d * id_feedback ;
	vq_ff += p_ri_pi->pole_flux;
	vq_ff *= e_speed_radps;

	p_ri_pi->vd_ref -= vd_ff;
	p_ri_pi->vq_ref += vq_ff;
}
static void ri_pi_saturation(PI* p_pi)
{
	float vs_max = p_ri_pi->vs_max;
	//vd saturation
	p_ri_pi->vd_sat =  saturation_limit(p_ri_pi->vd_ref ,
					(0.9f)*vs_max, -(0.9f)*vs_max );
	//vq max caculation
	float vq_max = saturation_update_vq_max(p_ri_pi, p_ri_pi->vd_sat, vs_max);
	//vq saturation
	p_ri_pi->vq_sat =  saturation_limit(p_ri_pi->vq_ref , (1.0f)*vq_max, -(1.0f)*vq_max);
}
#endif

