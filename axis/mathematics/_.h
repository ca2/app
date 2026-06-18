#pragma once


CLASS_DECL_AXIS void srand_dup(::u32 seed);
CLASS_DECL_AXIS ::i32  rand_dup();

CLASS_DECL_AXIS ::i32 abs_dup(::i32 i);
CLASS_DECL_AXIS ::f64 fabs_dup(::f64 d);

#ifdef SUPORTA_MATEMATICA_AVANCADA
CLASS_DECL_AXIS ::f64 atan_dup(::f64 d);
CLASS_DECL_AXIS ::f64 asin_dup(::f64 d);
CLASS_DECL_AXIS ::f64 acos_dup(::f64 d);
CLASS_DECL_AXIS ::f64 sqrt_dup(::f64 d);
CLASS_DECL_AXIS ::f64 pow_dup(::f64 aura, ::f64 e);
CLASS_DECL_AXIS ::f64 exp_dup(::f64 d);
CLASS_DECL_AXIS ::f64 log_dup(::f64 d);
CLASS_DECL_AXIS ::f64 tan_dup(::f64 d);
CLASS_DECL_AXIS ::f64 sin_dup(::f64 d);
CLASS_DECL_AXIS ::f64 cos_dup(::f64 d);
CLASS_DECL_AXIS ::f64 fmod_dup(::f64 x, ::f64 y);
#endif



CLASS_DECL_AXIS ::i64 ftoi64(::f64 d);
CLASS_DECL_AXIS ::i32 ftol(::f64 d);
