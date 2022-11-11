// Created by camilo from gz on 2021-11-10 10:12 BRT <3ThomasBorregaardSørensen!!
#pragma once


#include "acme/primitive/primitive/particle.h"


class CLASS_DECL_ACME file_transfer :
   virtual public ::particle
{
public:


   virtual void transfer(::file::file* pfileOut, ::file::file* pfileIn);


};

   

