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


   enum_pen             m_epen;
   enum_line_cap        m_elinecapStart;
   enum_line_cap        m_elinecapEnd;
   ::f64                m_fWidth;
   ::color::color       m_color;


   pen();
   ~pen() override;

   virtual void create_pen(enum_pen epen, ::f64 fWidth, const ::color::color &color);

   virtual void set_start_cap(enum_line_cap elinecap);
   virtual void set_end_cap(enum_line_cap elinecap);


};



   } // namespace graphics


} // namespace nano




