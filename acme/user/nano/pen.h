//
// Created by camilo on 31/01/2022 14:38 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "object.h"


class CLASS_DECL_ACME nano_pen :
   virtual public ::nano_object
{
public:


   int                  m_iWidth;
   ::color::color       m_color;


   nano_pen();
   ~nano_pen() override;


};



