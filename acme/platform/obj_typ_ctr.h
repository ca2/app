#pragma once


#if OBJ_TYP_CTR

class element;

void obj_type_ctr_inc(::element* pobject);
void obj_type_ctr_dec(::element* pobject);

#define OBJ_TYP_CTR_INC obj_type_ctr_inc(this)
#define OBJ_TYP_CTR_DEC obj_type_ctr_dec(this)

#else

#define OBJ_TYP_CRT_INC
#define OBJ_TYP_CRT_DEC

#endif



