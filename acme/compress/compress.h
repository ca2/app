// Created by camilo from gz on 2021-11-10 10:03 BRT <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/filesystem/file/transfer.h"


class CLASS_DECL_ACME compress :
   virtual public ::file_transfer
{
public:


   compress();
   ~compress() override;


   virtual void set_level(int iLevel);


   void transfer(::file::file* pfileOut, ::file::file* pfileIn, transfer_progress_function transferprogressfunction = {}) override;


   virtual unsigned int crc32(unsigned int uCrc, const ::block& block);


};



