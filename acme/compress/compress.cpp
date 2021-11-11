// Created by camilo from gz on 2021-11-10 10:0743 BRT <3ThomasBorregaardSørensen!!
#include "framework.h"


compress::compress()
{

}


compress::~compress()
{


}


::e_status compress::set_level(int iLevel)
{

   throw interface_only_exception();

   return error_interface_only;

}


::e_status compress::transfer(::file::file* pfileOut, ::file::file* pfileIn)
{

   throw interface_only_exception();

   return error_interface_only;

}



