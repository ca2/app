#pragma once


#if OBJ_TYP_CTR

class matter;

void obj_type_ctr_inc(::matter* pobject);
void obj_type_ctr_dec(::matter* pobject);

#define OBJ_TYP_CTR_INC obj_type_ctr_inc(this)
#define OBJ_TYP_CTR_DEC obj_type_ctr_dec(this)

#else

#define OBJ_TYP_CRT_INC
#define OBJ_TYP_CRT_DEC

#endif



