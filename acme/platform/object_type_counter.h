#pragma once


#if OBJECT_TYPE_COUNTER

class matter;

void object_type_counter_increment(::matter* pobject);
void object_type_counter_decrement(::matter* pobject);

#define OBJECT_TYPE_COUNTER_INCREMENT object_type_counter_increment(this)
#define OBJECT_TYPE_COUNTER_DECREMENT object_type_counter_decrement(this)

#else

#define OBJ_TYP_CRT_INC
#define OBJ_TYP_CRT_DEC

#endif



