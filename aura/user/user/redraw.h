// Created by camilo on 2023-06-30 18:27 <3ThomasBorregaardSorensen!!
// Enhanced by camilo on 2023-06-30 18:46 <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/prototype/geometry2d/rectangle_array.h"
#include "acme/prototype/geometry2d/shift.h"


namespace user
{

   class redraw_item :
      public ::particle
   {
   public:


      ::rectangle_int_array               m_rectanglea;
      ::array < ::function <void() > >    m_functiona;


      redraw_item();
      ~redraw_item() override;

#ifdef _DEBUG

      i64 increment_reference_count() override;
      i64 decrement_reference_count() override;

#endif

   };


   class CLASS_DECL_AURA redraw :
      public ::particle
   {
   public:

      bool                             m_bEnabled = true;
      ::draw2d::graphics_pointer       m_pgraphics;
      ::rectangle_int_array            m_rectangleaNeedRedraw;


      void initialize(::particle * pparticle) override;

      void clear();
      void initialize_and_transfer(pointer_array < redraw_item > & redrawitema);
      void set_need_redraw(const ::rectangle_i32 & rectangle);
      void set_need_redraw(const ::rectangle_int_array & rectanglea);
      bool needs_to_draw(const ::rectangle_i32 & rectangle);
      void apply_clip(shift_i32 ΔHostToClient);


   };


} // namespace user



