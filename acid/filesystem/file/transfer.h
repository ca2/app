// Created by camilo from gz on 2021-11-10 10:12 BRT <3ThomasBorregaardSorensen!!
#pragma once


class CLASS_DECL_ACID file_transfer :
   virtual public ::particle
{
public:


   virtual void transfer(::file::file* pfileOut, ::file::file* pfileIn, transfer_progress_function transferprogressfunction = {});


};

   

