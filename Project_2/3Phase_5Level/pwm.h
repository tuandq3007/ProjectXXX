#ifndef PWM_H_
#define PWM_H_

#include "math.h"
#include "stdint.h"
#include "user.h"

typedef struct pwm_t				PWM;					  
struct pwm_t {
	int		Sa11;
	int		Sa12;
	int		Sa13;
	int		Sa14;

	int		Sb11;
	int		Sb12;
	int		Sb13;
	int		Sb14;

	int		Sc11;
	int		Sc12;
	int		Sc13;
	int		Sc14;

	int		Sa21;
	int		Sa22;
	int		Sa23;
	int		Sa24;

	int		Sb21;
	int		Sb22;
	int		Sb23;
	int		Sb24;

	int		Sc21;
	int		Sc22;
	int		Sc23;
	int		Sc24;

};
#endif
