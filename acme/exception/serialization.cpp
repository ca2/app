// Created by camilo on 2021-01-15 16:47 <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "serialization.h"


serialization_exception::serialization_exception(::e_status estatus, const ::scoped_string & scopedstrMessage, i32 iSkip) :
   ::exception(estatus, scopedstrMessage, nullptr, iSkip)
{

}


serialization_exception::~serialization_exception()
{

}
