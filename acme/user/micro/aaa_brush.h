//
// Created by camilo on 31/01/2022 14:40 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "object.h"

namespace nano
{

   namespace user
   {
   

class CLASS_DECL_ACME brush :
   virtual public ::micro::object
{
public:


   ::color::color       m_color;


   brush();
   ~brush() override;


};


//namespace nano
//{
//
//
//   ::pointer<::nano::graphics::brush> create_solid_brush(::particle * pparticle, color32_t color);
//
//
//} // namespace nano





   } // namespace user


} // namespace nano



