#pragma once


CLASS_DECL_AXIS void srand_dup(unsigned int seed);
CLASS_DECL_AXIS int  rand_dup();

CLASS_DECL_AXIS int abs_dup(int i);
CLASS_DECL_AXIS double fabs_dup(double d);

#ifdef SUPORTA_MATEMATICA_AVANCADA
CLASS_DECL_AXIS double atan_dup(double d);
CLASS_DECL_AXIS double asin_dup(double d);
CLASS_DECL_AXIS double acos_dup(double d);
CLASS_DECL_AXIS double sqrt_dup(double d);
CLASS_DECL_AXIS double pow_dup(double aura, double e);
CLASS_DECL_AXIS double exp_dup(double d);
CLASS_DECL_AXIS double log_dup(double d);
CLASS_DECL_AXIS double tan_dup(double d);
CLASS_DECL_AXIS double sin_dup(double d);
CLASS_DECL_AXIS double cos_dup(double d);
CLASS_DECL_AXIS double fmod_dup(double x, double y);
#endif



CLASS_DECL_AXIS i64 ftoi64(double d);
CLASS_DECL_AXIS int ftol(double d);
