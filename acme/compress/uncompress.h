// Created by camilo from gz on 2021-11-10 10:043 BRT <3ThomasBorregaardSørensen!!
#pragma once


class CLASS_DECL_ACME uncompress :
   virtual public ::file_transfer
{
public:


   uncompress();
   ~uncompress() override;


   ::e_status transfer(::file::file* pfileOut, ::file::file* pfileIn) override;


};



