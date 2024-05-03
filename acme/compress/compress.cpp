// Created by camilo from gz on 2021-11-10 10:0743 BRT <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "compress.h"
#include "acme/exception/interface_only.h"


compress::compress()
{

}


compress::~compress()
{


}


void compress::set_level(int iLevel)
{

   throw ::interface_only();

}


void compress::transfer(::file::file* pfileOut, ::file::file* pfileIn, transfer_progress_function transferprogressfunction)
{

   throw ::interface_only();

}


::u32 compress::crc32(::u32 uCrc, const ::block& block)
{

   throw ::interface_only("this function is expected to be called just from zlib compress implementation. So no need to implement it except at compress_zlib.");

   return 0;

}


