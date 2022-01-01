// Created by camilo from gz on 2021-11-10 10:0743 BRT <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "acme/filesystem/file/transfer.h"
#include "uncompress.h"


uncompress::uncompress()
{

}


uncompress::~uncompress()
{

}


::e_status uncompress::transfer(::file::file* pfileOut, ::file::file* pfileIn)
{

   throw interface_only_exception();

   return error_interface_only;

}



