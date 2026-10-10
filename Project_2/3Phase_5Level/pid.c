#include "pid.h"
#define PID_RESOLUTION		FOC_RESOLUTION
PI* pi_create(const float_t initial_value, const float_t ki,
		const float_t kp,const float_t kc, const float_t td)
{
	PI* p_pi = (PI*) malloc(sizeof(PI));
	while (p_pi == NULL)
		;
	p_pi->i_prev = initial_value;
	p_pi->output = initial_value;

	p_pi->kp = kp;
	p_pi->ki = ki;
	p_pi->td = td;
	p_pi->kitd = (p_pi->td * p_pi->ki) / PID_RESOLUTION;
	p_pi->kc = kc;
	return p_pi;

}

RAM_FUNC void pi_reset(PI* p_pi){
	p_pi->output=0;
	p_pi->i_prev=0;
}

void pi_destroy(PI* p_pi){
	free(p_pi);
}

void pi_set_para(PI* p_pi, const float_t ki,
		const float_t kp, float kc, const float_t td)
{
	p_pi->kp = kp;
	p_pi->ki = ki;
	p_pi->td = td;
	p_pi->kitd = (p_pi->td * p_pi->ki) / PID_RESOLUTION;
	p_pi->kc = kc;

}
