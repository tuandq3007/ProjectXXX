#include "foc_controller.h"

static void foc_update_bemf_estimate(FOC_Ctrl*p_foc);

FOC_Ctrl* foc_create(const float vs_max, const float ls_d_H, const float ls_q_H, const float pole_flux)
{
	FOC_Ctrl* p_foc = (FOC_Ctrl*) malloc(sizeof(FOC_Ctrl));
	while (p_foc == NULL)
		;

	foc_init(p_foc, vs_max, ls_d_H, ls_q_H, pole_flux);

	return p_foc;
}

void foc_init(FOC_Ctrl* p_foc, const float vs_max, const float ls_d_H, const float ls_q_H, const float pole_flux)
{
	p_foc->p_ri_pi = ri_pi_create(vs_max, ls_d_H, ls_q_H , pole_flux);
	p_foc->p_op_loop = op_loop_create(vs_max, ls_d_H, ls_q_H , pole_flux);

	p_foc->iu_feedback = 0;
	p_foc->iv_feedback = 0;
	p_foc->iw_feedback = 0;
	p_foc->i_alpha_feedback = 0;
	p_foc->i_beta_feedback = 0;
	p_foc->id_feedback = 0;
	p_foc->iq_feedback = 0;

	p_foc->flux_angle = 0.0f;
	p_foc->e_speed_radps = 0.0f;
	p_foc->bemf_estimate = 0.0f;

	p_foc->id_sp=0.0f;
	p_foc->iq_sp=0.0f;
	p_foc->vd_sp=0;
	p_foc->vq_sp=0;
	p_foc->v_beta_sp = 0;
	p_foc->v_alpha_sp = 0;
}

OPTIMIZE_ATTR void foc_inverse_park_transform(FOC_Ctrl* p_foc, const float sin_theta,
		const float cos_theta) {

	p_foc->v_alpha_sp = inverse_park_transfor_alpha(p_foc->vd_sp,
			p_foc->vq_sp, cos_theta, sin_theta);
	p_foc->v_beta_sp = inverse_park_transfor_beta(p_foc->vd_sp,
			p_foc->vq_sp, cos_theta, sin_theta);

}

static OPTIMIZE_ATTR void foc_update_vd_vq(FOC_Ctrl* p_foc) {
	//foc_update_bemf_estimate(p_foc);
#if RIPI
	ri_pi_running(p_foc->p_ri_pi, p_foc->id_sp, p_foc->iq_sp ,
			p_foc->id_feedback, p_foc->iq_feedback, p_foc->e_speed_radps);
	p_foc->vd_sp = ri_pi_get_vd_setpoint(p_foc->p_ri_pi);
	p_foc->vq_sp = ri_pi_get_vq_setpoint(p_foc->p_ri_pi);
#endif
#if RI_OPENLOOP
	op_loop_running(p_foc->p_op_loop, p_foc->iq_sp,
			p_foc->id_feedback, p_foc->iq_feedback, p_foc->e_speed_radps);
	p_foc->vd_sp = op_loop_get_vd_setpoint(p_foc->p_op_loop) ;
	p_foc->vq_sp = op_loop_get_vq_setpoint(p_foc->p_op_loop) ;
#endif
}

OPTIMIZE_ATTR void foc_update_control_loop(FOC_Ctrl* p_foc){

	float sin_theta = f_sin(p_foc->flux_angle);
	float cos_theta = f_cosin(p_foc->flux_angle);
	foc_clarke_transform(p_foc);
	foc_park_transform(p_foc, sin_theta, cos_theta);
	foc_update_vd_vq(p_foc);
	foc_inverse_park_transform(p_foc, sin_theta, cos_theta);
}
OPTIMIZE_ATTR void foc_reset_current_controller(FOC_Ctrl* p_foc){
	ri_pi_reset(p_foc->p_ri_pi);
	op_loop_reset(p_foc->p_op_loop);
	p_foc->id_sp=0.0f;
	p_foc->iq_sp=0.0f;
	p_foc->id_feedback = 0;
	p_foc->iq_feedback = 0;
	p_foc->e_speed_radps=0.0f;
	p_foc->flux_angle=0.0f;
}
static OPTIMIZE_ATTR void foc_update_bemf_estimate(FOC_Ctrl*p_foc){
	p_foc->bemf_estimate = p_foc->e_speed_radps * USER_MOTOR_FLUX;
}

