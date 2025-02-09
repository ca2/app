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


      ::int_rectangle_array               m_rectanglea;
      ::array < ::function <void() > >    m_functiona;


      redraw_item();
      ~redraw_item() override;

#ifdef _DEBUG

      long long increment_reference_count() override;
      long long decrement_reference_count() override;

#endif

   };


   class CLASS_DECL_AURA redraw :
      public ::particle
   {
   public:

      bool                             m_bEnabled = true;
      ::draw2d::graphics_pointer       m_pgraphics;
      ::int_rectangle_array            m_rectangleaNeedRedraw;


      void initialize(::particle * pparticle) override;

      void clear();
      void initialize_and_transfer(pointer_array < redraw_item > & redrawitema);
      void set_need_redraw(const ::int_rectangle & rectangle);
      void set_need_redraw(const ::int_rectangle_array & rectanglea);
      bool needs_to_draw(const ::int_rectangle & rectangle);
      void apply_clip(shift_int ΔHostToClient);


   };


} // namespace user



