#include "framework.h"
#include <math.h>


void kf_cexp(COMPLEXD * x,double phase) /* returns e ** (j*phase)   */
{
#ifdef FIXED_POINT
    x->r = (kiss_fft_scalar) (32767 * cos (phase));
    x->i = (kiss_fft_scalar) (32767 * sin (phase));
#else
    x->r = (kiss_fft_scalar) cos (phase);
    x->i = (kiss_fft_scalar) sin (phase);
#endif
}
