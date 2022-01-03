// Created by camilo from gz on 2021-11-10 10:0743 BRT <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "acme/filesystem/file/transfer.h"
#include "compress.h"


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



::u32 compress::crc32(::u32 uCrc, const ::block& block)
{

   throw interface_only_exception("this function is expected to be called just from zlib compress implementation. So no need to implement it except at compress_zlib.");

   return 0;

}


