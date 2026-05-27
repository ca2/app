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


   //::i32                  m_iWidth;
   //::color::color       m_color;


   pen();
   ~pen() override;

   virtual void create_pen(const ::color::color &color,  ::f64 fWidth);


};



   } // namespace graphics


} // namespace nano




