// Created by camilo on 2021-01-15 17:12 <3ThomasBorregaardSorensen!!
#include "framework.h"


file_open_exception::file_open_exception(::e_status estatus, const ::scoped_string & scopedstrMessage, int iSkip) :
   ::exception(estatus, pszMessage, nullptr, iSkip)
{

}


file_open_exception::~file_open_exception()
{

}
