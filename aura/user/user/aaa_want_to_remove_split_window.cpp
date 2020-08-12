#include "framework.h"


BaseSplitWnd::BaseSplitWnd()
{
}

BaseSplitWnd::~BaseSplitWnd()
{
}

bool BaseSplitWnd::pre_create_window(::user::create_struct& cs)
{
   cs.dwExStyle &= ~WS_EX_CLIENTEDGE;

   return ::user::interaction::pre_create_window(cs);
}

void BaseSplitWnd::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
{



   i32 i;
   ::rect rect;
   COLORREF cr = RGB(92, 92, 80);
   for(i = 0; i < get_pane_count(); i++)
   {
      CalcPaneRect(i, &rect);

      // Top
      pgraphics->fill_solid_rect_dim(
      rect.left,
      rect.top,
      rect.width(),
      m_cyBorder,
      cr);

      // Right
      pgraphics->fill_solid_rect_dim(
      rect.right - m_cxBorder,
      rect.top,
      m_cxBorder,
      rect.height(),
      cr);

      // Bottom
      pgraphics->fill_solid_rect_dim(
      rect.left,
      rect.bottom - m_cyBorder,
      rect.width(),
      m_cyBorder,
      cr);

      // Left
      pgraphics->fill_solid_rect_dim(
      rect.left,
      rect.top,
      m_cxBorder,
      rect.height(),
      cr);
   }

}


