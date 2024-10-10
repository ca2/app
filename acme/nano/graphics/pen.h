//
// Created by camilo on 31/01/2022 14:38 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "object.h"

namespace nano
{

namespace graphics
{

class CLASS_DECL_ACME pen :
   virtual public ::nano::graphics::object
{
public:


   int                  m_iWidth;
   ::color::color       m_color;


   pen();
   ~pen() override;


};



   } // namespace graphics


} // namespace nano




