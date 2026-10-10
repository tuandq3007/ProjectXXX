#ifndef FOC_CONTROLLER_H_
#define FOC_CONTROLLER_H_

#include"pid.h"
#include"user.h"

typedef struct foc_controller_t FOC;

struct foc_controller_t{

	PI* pi;

	float ia_feedback;
	float ib_feedback;
	float ic_feedback;

	float i_alpha_feedback;
	float i_beta_feedback;

	float id_feedback;
	float iq_feedback;

	float flux_angle;
	float e_speed_radps;
	float bemf_estimate;

	float id_sp;
	float iq_sp;

	float vd_ref;
	float vq_ref;

	float vd_sat;
	float vq_sat;

	float v_alpha_sp;
	float v_beta_sp;
};

void foc_init(FOC* p_foc, const float vs_max, const float ls_d_H, const float ls_q_H, const float pole_flux);

static void foc_clarke_transform(FOC* p_foc){

	p_foc->i_alpha_feedback = clarke_transfor_alpha(p_foc->ia_feedback, p_foc->ib_feedback,p_foc->ic_feedback);
	p_foc->i_beta_feedback = clarke_transfor_beta(p_foc->ib_feedback,p_foc->ic_feedback);
}

static void foc_park_transform(FOC* p_foc, const float sin_theta, const float cos_theta) {

	p_foc->id_feedback = park_transfor_d(p_foc->i_alpha_feedback,p_foc->i_beta_feedback, cos_theta, sin_theta);
	p_foc->iq_feedback = park_transfor_q(p_foc->i_alpha_feedback,p_foc->i_beta_feedback, cos_theta, sin_theta);
}
void foc_running(FOC* p_foc, const float id_ref, const float iq_ref,
		const float id_feedback, const float iq_feedback, const float e_speed_radps)
{
	//id_pi
	float error_id = id_ref - id_feedback;
	p_foc->vd_ref = pi_current_loop_running(p_foc->pi, error_id, p_foc->vd_ref, p_foc->vd_sat);
	//iq_pi
	float error_iq = iq_ref - iq_feedback;
	p_foc->vq_ref = pi_current_loop_running(p_foc->pi, error_iq, p_foc->vq_ref, p_foc->vq_sat);
	//decoupling
	ri_pi_decoupling(p_foc, id_feedback, iq_feedback, e_speed_radps);
	//saturation
	ri_pi_saturation(p_foc);
}
#endif
