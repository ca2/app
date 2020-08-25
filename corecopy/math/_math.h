#pragma once


CLASS_DECL_CORE void srand_dup(u32 seed);
CLASS_DECL_CORE i32  rand_dup();

CLASS_DECL_CORE i32 abs_dup(i32 i);
CLASS_DECL_CORE double fabs_dup(double d);

#ifdef SUPORTA_MATEMATICA_AVANCADA
CLASS_DECL_CORE double atan_dup(double d);
CLASS_DECL_CORE double asin_dup(double d);
CLASS_DECL_CORE double acos_dup(double d);
CLASS_DECL_CORE double sqrt_dup(double d);
CLASS_DECL_CORE double pow_dup(double aura, double e);
CLASS_DECL_CORE double exp_dup(double d);
CLASS_DECL_CORE double log_dup(double d);
CLASS_DECL_CORE double tan_dup(double d);
CLASS_DECL_CORE double sin_dup(double d);
CLASS_DECL_CORE double cos_dup(double d);
CLASS_DECL_CORE double fmod_dup(double x, double y);
#endif



CLASS_DECL_CORE i64 ftoi64(double d);
CLASS_DECL_CORE i32 ftol(double d);
