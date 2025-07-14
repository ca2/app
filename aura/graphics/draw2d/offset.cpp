// Created by camilo on 2025-07-14 00:42 <3ThomasBorregaardSørensen!!   
#include "framework.h"
#include "offset.h"


namespace draw2d
{


   offset_context::offset_context(offsetable* poffsetable) :
      m_poffsetable(poffsetable)
   {

      m_poffsetable->_get(this);

   }

   
   offset_context::~offset_context()
   {

      m_poffsetable->_set(this);

   }


   void offset_context::x_offset(double dx) { m_poffsetable->x_offset(dx); }

   void offset_context::y_offset(double dy) { m_poffsetable->y_offset(dy); }

   void offset_context::offset(double dx, double dy) { m_poffsetable->offset(dx, dy); }

   void offset_context::shift_impact_area(double dx, double dy, double w, double h) { m_poffsetable->shift_impact_area(dx, dy, w, h); }


} // namespace draw2d



