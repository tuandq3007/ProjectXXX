#include "user.h"
#include "foc.h"
#include "encoder.h"
#include "main.h"
#include "math.h"

extern SVM svm;

__declspec(dllexport) void simuser(float t, float delt, float *in, float *out)
{
	svm.foc->ia_feedback	= in[0];
	svm.foc->ib_feedback	= in[1];
	svm.foc->ic_feedback	= in[2];

	svm.Vc1					= in[3];
	svm.Vc2					= in[4];

	svm.encoder->pulse_A	= in[5];
	svm.encoder->pulse_B	= in[6];
	svm.encoder->pulse_Z	= in[7];

	svm.real_time			= t;
	svm.time_step			= delt;

	// khoi tao bien, chay 1 lan khi khoi tao ban dau
	svm_init(&svm);

	// ngat 20khz, dung de tinh toan vong trong dong dien id, iq
	svm_interrupt_20khz(&svm);

	// ngat 1khz, dung de cap nhat va tinh toan thong so vong ngoai
	svm_interrupt_1khz(&svm);
	
	out[0] = svm.pwm->Sa11;
    out[1] = svm.pwm->Sa12;
    out[2] = svm.pwm->Sa13;
	out[3] = svm.pwm->Sa14;

    out[4] = svm.pwm->Sb11;
    out[5] = svm.pwm->Sb12;
	out[6] = svm.pwm->Sb13;
    out[7] = svm.pwm->Sb14;

    out[8] = svm.pwm->Sc11;
	out[9] = svm.pwm->Sc12;
    out[10] = svm.pwm->Sc13;
    out[11] = svm.pwm->Sc14;

	out[12] = svm.pwm->Sa21;
	out[13] = svm.pwm->Sa22;
    out[14] = svm.pwm->Sa23;
	out[15] = svm.pwm->Sa24;

    out[16] = svm.pwm->Sb21;
    out[17] = svm.pwm->Sb22;
	out[18] = svm.pwm->Sb23;
    out[19] = svm.pwm->Sb24;

    out[20] = svm.pwm->Sc21;
	out[21] = svm.pwm->Sc22;
    out[22] = svm.pwm->Sc23;
    out[23] = svm.pwm->Sc24;

	out[24] = svm.display->speed_ref;
    out[25] = svm.display->id_ref;
    out[26] = svm.display->iq_ref;
	out[27] = svm.display->vsd_ref;
    out[28] = svm.display->vsq_ref;
    out[29] = svm.display->theta;
}