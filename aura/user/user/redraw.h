// Created by camilo on 2023-06-30 18:27 <3ThomasBorregaardSorensen!!
// Enhanced by camilo on 2023-06-30 18:46 <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/primitive/geometry2d/rectangle_array.h"
#include "acme/primitive/geometry2d/shift.h"


namespace user
{

   class redraw_item :
      public ::particle
   {
   public:


      ::rectangle_i32_array               m_rectanglea;
      ::array < ::function <void() > >    m_functiona;

   };


   class CLASS_DECL_AURA redraw :
      public ::particle
   {
   public:


      ::draw2d::graphics_pointer       m_pgraphics;
      ::rectangle_i32_array            m_rectangleaNeedRedraw;


      void clear();
      void initialize_and_transfer(pointer_array < redraw_item > && redrawitema);
      void set_need_redraw(const ::rectangle_i32 & rectangle);
      void set_need_redraw(const ::rectangle_i32_array & rectanglea);
      bool needs_to_draw(const ::rectangle_i32 & rectangle);
      void apply_clip(shift_i32 ΔHostToClient);


   };


} // namespace user



