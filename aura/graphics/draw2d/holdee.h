// Created by camilo on 2022-06-23 20:13 <3ThomasBorregaardS�rensen!!
#pragma once


#include "path.h"
#include "acme/primitive/primitive/particle.h"
//#include "acme/primitive/primitive/pointer.h"
#include "acme/primitive/collection/int_map.h"


namespace draw2d
{


   enum enum_change
   {

      e_change_none, // never changes
      e_change_theme = 1, // changes with theme
      e_change_position = 2, // changes with position
      e_change_layout = 4, // changes with position and/or size

   };


   DECLARE_ENUMERATION(e_change, enum_change);


   class CLASS_DECL_AURA holdee_group
   {
   public:

      ::draw2d::path_pointer           m_patha[8];
      ::draw2d::brush_pointer          m_brusha[8];
      ::draw2d::pen_pointer            m_pena[8];
      ::write_text::font_pointer       m_fonta[8];

   };


   class CLASS_DECL_AURA holdee :
      virtual public ::particle
   {
   public:


      ::map < e_change, ::index_map < holdee_group > >   m_map;

      holdee();
      ~holdee() override;


   };


} // namespace draw2d



