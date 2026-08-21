// Created by camilo on 2025-07-14 00:42 <3ThomasBorregaardSørensen!!   
#include "platform.h"
#include "offset.h"


namespace draw2d
{


   ::draw2d::target_scope target_rectangle::target_scope()
   {

      return {this};

   }


   ::f64_rectangle target_rectangle::get_target_rectangle() const
   {

      return {m_pointTarget, m_sizeTarget};

   }

   void target_rectangle::set_target_rectangle(const ::f64_rectangle & rectangle)
   {

      m_pointTarget = rectangle.origin();

      m_sizeTarget = rectangle.size();

   }





   // offset_context::offset_context(offsetable* poffsetable) :
   //    m_poffsetable(poffsetable)
   // {
   //
   //    m_poffsetable->_get(this);
   //
   // }
   //
   //
   // offset_context::~offset_context()
   // {
   //
   //    m_poffsetable->_set(this);
   //
   // }
   //
   //
   // void offset_context::x_offset(::f64 dx) { m_poffsetable->x_offset(dx); }
   //
   // void offset_context::y_offset(::f64 dy) { m_poffsetable->y_offset(dy); }
   //
   // void offset_context::offset(::f64 dx, ::f64 dy) { m_poffsetable->offset(dx, dy); }
   //
   // void offset_context::shift_impact_area(::f64 dx, ::f64 dy, ::f64 w, ::f64 h) { m_poffsetable->shift_impact_area(dx, dy, w, h); }


} // namespace draw2d



