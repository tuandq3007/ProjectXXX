#ifndef MAIN_H
#define MAIN_H

#include "foc.h"
#include "encoder.h"
#include "pwm.h"

typedef enum
{
	SVM_OK					= 0,
	SVM_ERROR				= 1
}SVM_STATUS;

typedef struct svm_t				SVM;
typedef struct display_t			DISPLAY;
/****************************************************************************************/
struct svm_t {

	uint32_t counter;
	uint32_t timer_1;
	uint32_t timer_2;
	uint32_t timer_3;

	float speed_rpm;
	float speed_radps;
	float speed_kmph;
	float speed_rpm_filter;
	float speed_radps_filter;

	float Vc1;
	float Vc2;

	float time_step;
	double real_time;

	DISPLAY*			display;
	FOC*				foc;
	ENCODER_Sensor*		encoder;
	PWM*				pwm;
};
void svm_init(SVM* p_svm);
static void svm_interrupt_1khz(SVM* p_svm);
static float svm_interrupt_20khz(SVM* p_svm);
static float encoder_speed_get_radps();
/****************************************************************************************/
struct display_t {
	float speed_ref;
	float id_ref;
	float iq_ref;
	float vsd_ref;
	float vsq_ref;
	float theta;
};
void svm_display_init(DISPLAY* p_dpl){
	p_dpl->speed_ref				=	0;
	p_dpl->id_ref					=	0;
	p_dpl->iq_ref					=	0;
	p_dpl->vsd_ref					=	0;
	p_dpl->vsq_ref					=	0;
	p_dpl->theta					=	0;
}
/****************************************************************************************/
void svm_init(SVM* p_svm){
	p_svm->counter					=	0;
	p_svm->timer_1					=	0;
	p_svm->timer_2					=	0;
	p_svm->timer_3					=	0;
	p_svm->speed_rpm				=	0;
	p_svm->speed_radps				=	0;
	p_svm->speed_kmph				=	0;
	p_svm->speed_rpm_filter			=	0;
	p_svm->speed_radps_filter		=	0;
	p_svm->Vc1						=	0;
	p_svm->Vc2						=	0;
	p_svm->time_step				=	0;
	p_svm->real_time				=	0;

	svm_display_init(p_svm->display);

}







/****************************************************************************************/
#endif