//
// Created by camilo on 31/01/2022 14:40 <3ThomasBorregaardSørensen!!
//
#pragma once


#include "object.h"


class CLASS_DECL_ACME nano_brush :
   virtual public ::nano_object
{
public:


   ::color::color       m_color;


   nano_brush();
   ~nano_brush() override;


};


//namespace nano
//{
//
//
//   ::pointer<nano_brush> create_solid_brush(::particle * pparticle, color32_t color);
//
//
//} // namespace nano



