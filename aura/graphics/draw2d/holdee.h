// Created by camilo on 2022-06-23 20:13 <3ThomasBorregaardSorensen!!
#pragma once


#include "path.h"

//#include "acme/prototype/prototype/pointer.h"
#include "acme/prototype/collection/int_map.h"


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


   class CLASS_DECL_AURA holdee_group :
      virtual public ::subparticle
   {
   public:

      ::pointer_array < ::draw2d::path >        m_patha;
      ::pointer_array < ::draw2d::brush >       m_brusha;
      ::pointer_array < ::draw2d::pen >         m_pena;
      ::pointer_array < ::write_text::font >    m_fonta;

      holdee_group()
      {

      }

         ~holdee_group()
      {

      }

   };


   class CLASS_DECL_AURA holdee :
      virtual public ::particle
   {
   public:


      ::map < e_change, ::index_map < ::pointer < holdee_group > > >   m_map;

      holdee();
      ~holdee() override;


   };


} // namespace draw2d



