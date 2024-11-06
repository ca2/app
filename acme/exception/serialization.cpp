// Created by camilo on 2021-01-15 16:47 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "serialization.h"


serialization_exception::serialization_exception(::e_status estatus, const ::scoped_string & scopedstrMessage, int iSkip) :
   ::exception(estatus, scopedstrMessage, nullptr, iSkip)
{

}


serialization_exception::~serialization_exception()
{

}
