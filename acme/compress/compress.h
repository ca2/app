// Created by camilo from gz on 2021-11-10 10:03 BRT <3ThomasBorregaardSørensen!!
#pragma once


class CLASS_DECL_ACME compress :
   virtual public ::file_transfer
{
public:


   compress();
   ~compress() override;


   virtual void set_level(int iLevel);


   void transfer(::file::file * pfileOut, ::file::file * pfileIn) override;


   virtual ::u32 crc32(::u32 uCrc, const ::block& block);


};



