// Created by camilo on 2021-01-15 17:12 <3ThomasBorregaardSørensen!!
#include "framework.h"


file_open_exception::file_open_exception(::e_status estatus, const char* pszMessage, i32 iSkip) :
   ::exception(estatus, pszMessage, nullptr, iSkip)
{

}


file_open_exception::~file_open_exception()
{

}
