// Created by camilo from gz on 2021-11-10 10:043 BRT <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/filesystem/file/transfer.h"


class CLASS_DECL_ACME uncompress :
   virtual public ::file_transfer
{
public:


   uncompress();
   ~uncompress() override;


   void transfer(::file::file* pfileOut, ::file::file* pfileIn) override;


};



