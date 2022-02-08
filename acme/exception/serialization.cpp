// Created by camilo on 2021-01-15 16:47 <3ThomasBorregaardSørensen!!
#include "framework.h"


serialization_exception::serialization_exception(::e_status estatus, const char* pszMessage, i32 iSkip) :
   ::exception(estatus, pszMessage, nullptr, iSkip)
{

}


serialization_exception::~serialization_exception()
{

}
