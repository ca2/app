//
// Created by camilo on 31/01/2022 14:40 <3ThomasBorregaardSørensen!!
//
#pragma once


class CLASS_DECL_ACME nano_brush :
   virtual public ::nano_object
{
public:


   ::color::color       m_color;


   nano_brush();
   ~nano_brush() override;


};


namespace nano
{


   __pointer(nano_brush) create_solid_brush(::object * pobject, color32_t color);


} // namespace nano



