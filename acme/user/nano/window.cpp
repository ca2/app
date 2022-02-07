//
// Created by camilo on 31/01/2022 16:16 <3ThomasBorregaardSørensen!!
//
#include "framework.h"
#include "_nano.h"
#include "acme/id.h"


nano_window::nano_window()
{

   enable_drag_move();

   m_bNcActive = false;

   m_bStartCentered = false;

}


nano_window::~nano_window()
{


}


void nano_window::on_initialize_object()
{

   ::object::on_initialize_object();

   __construct(m_pimplementation);

   m_pimplementation->m_pinterface = this;

}


void nano_window::draw(nano_device * pnanodevice)
{

   __pointer(::nano_pen) pnanopenBorder;

   if (is_active())
   {

      pnanopenBorder = m_ppenBorderFocus;

   }
   else
   {

      pnanopenBorder = m_ppenBorder;

   }

   ::rectangle_i32 rectangleClient;

   get_client_rectangle(rectangleClient);

   pnanodevice->rectangle(rectangleClient, m_pbrushWindow, pnanopenBorder);

   on_draw(pnanodevice);

   draw_children(pnanodevice);

}


void nano_window::draw_children(nano_device * pnanodevice)
{

   for (auto & pchild: m_childa)
   {

      pchild->on_draw(pnanodevice);

   }

}


void nano_window::create()
{

   m_pimplementation->create();

}


void nano_window::on_create()
{


}


void nano_window::destroy()
{

   m_pimplementation->destroy();

}


void nano_window::display_synchronously()
{

   m_pimplementation->display_synchronously();

}


void nano_window::message_loop()
{

   m_pimplementation->message_loop();

}



void nano_window::on_draw(nano_device * pnanodevice)
{

   m_pimplementation->draw(pnanodevice);

}


void nano_window::on_char(int iChar)
{

   if (iChar == '\t' && m_childa.has_element())
   {

      auto iFind = m_childa.find_first(m_pchildFocus);

      iFind++;

      m_pchildFocus = m_childa % iFind;

      redraw();

   }
   else if (m_pchildFocus)
   {

      m_pchildFocus->on_char(iChar);

   }

}


bool nano_window::is_active()
{

   return m_bNcActive;

}


void nano_window::set_active()
{

   m_pimplementation->set_active();

}


void nano_window::delete_drawing_objects()
{

   m_pbrushWindow.release();

   m_ppenBorder.release();

   m_ppenBorder.release();

}


bool nano_window::get_dark_mode()
{

   return m_pimplementation->get_dark_mode();

}


void nano_window::create_drawing_objects()
{

   if (!m_pfont)
   {

      __construct(m_pfont);

      m_pfont->m_iFontSize = 14;

      m_pfont->m_strFontName = m_psystem->node()->font_name(e_font_sans);

   }

   bool bDarkMode = get_dark_mode();

   if (bDarkMode)
   {

      m_colorWindow = rgb(0, 0, 0);
      m_colorText = rgb(255, 255, 255);
      m_colorHyperlink = rgb(40, 90, 245);
      m_colorHyperlinkHover = rgb(70, 180, 255);
      m_colorFocus = rgb(2, 128, 255);

   }
   else
   {

      m_colorWindow = rgb(255, 255, 255);
      m_colorText = rgb(0, 0, 0);
      m_colorHyperlink = rgb(50, 100, 185);
      m_colorHyperlinkHover = rgb(100, 180, 225);
      m_colorFocus = rgb(2, 58, 235);

   }

   m_pbrushWindow = ::nano::create_solid_brush(this, m_colorWindow);

   m_pbrushText = ::nano::create_solid_brush(this, m_colorText);

   m_pbrushHyperlink = ::nano::create_solid_brush(this, m_colorHyperlink);

   m_pbrushHyperlinkHover = ::nano::create_solid_brush(this, m_colorHyperlinkHover);

   m_ppenBorder = ::nano::create_pen(this, 1, m_colorText);

   m_ppenBorderFocus = ::nano::create_pen(this, 1, m_colorFocus);

}


void nano_window::update_drawing_objects()
{

   delete_drawing_objects();

   create_drawing_objects();

}


nano_child * nano_window::hit_test(int x, int y)
{

   x -= m_rectangle.left;

   y -= m_rectangle.top;

   for (auto & pchild: m_childa)
   {

      if (pchild->m_rectangle.contains(point_i32(x, y)))
      {

         return pchild;

      }

   }

   return nullptr;

}


void nano_window::add_child(nano_child * pchild)
{

   pchild->m_pwindow = this;

   m_childa.add(pchild);

}


nano_child * nano_window::get_child_by_id(const ::atom & atom)
{

   for (auto & pchild : m_childa)
   {

      if (pchild->m_atom == atom)
      {

         return pchild;

      }

   }

   return nullptr;

}

::atom nano_window::get_result()
{

   return m_atomResult;

}


void nano_window::on_mouse_move(int x, int y)
{

   if (m_pdragmove && m_pdragmove->m_bLButtonDown)
   {

      set_cursor(e_cursor_move);

      if (!m_pdragmove->m_bDrag)
      {

         m_pdragmove->m_bDrag = true;

         point_i32 pointCursor(x, y);

         auto point = pointCursor - m_pdragmove->m_sizeLButtonDownOffset;

         move_to(point.x, point.y);

         m_pdragmove->m_bDrag = false;

      }

      return;

   }

   if (m_pchildCapture)
   {

      m_pchildCapture->on_mouse_move(x, y);

      return;

   }

   auto pchild = hit_test(x, y);

   if (pchild)
   {

      pchild->on_mouse_move(x, y);

   }

}


void nano_window::on_left_button_down(int x, int y)
{

   set_capture();

   auto pchild = hit_test(x, y);

   if (pchild)
   {

      m_atomLeftButtonDown = pchild->m_atom;

   }
   else
   {

      m_atomLeftButtonDown = e_dialog_result_none;

   }

   if (m_pdragmove && m_atomLeftButtonDown == e_dialog_result_none)
   {

      m_pdragmove->m_bLButtonDown = true;

      m_pdragmove->m_bDrag = false;

      point_i32 pointCursor(x, y);

      m_pdragmove->m_pointLButtonDown = pointCursor;

      m_pdragmove->m_sizeLButtonDownOffset = m_pdragmove->m_pointLButtonDown - m_rectangle.origin();

      return;

   }

   if (::is_set(pchild) && pchild->is_focusable())
   {

      pchild->set_focus();

   }

}


void nano_window::on_left_button_up(int x, int y)
{

   release_capture();

   if (m_pdragmove && (m_pdragmove->m_bLButtonDown || m_pdragmove->m_bDrag))
   {

      m_pdragmove->m_bLButtonDown = false;

      m_pdragmove->m_bDrag = false;

      return;

   }

   auto pchild = hit_test(x, y);

   if (pchild)
   {

      m_atomLeftButtonUp = pchild->m_atom;

   }
   else
   {

      m_atomLeftButtonUp = e_dialog_result_none;

   }

   if (m_atomLeftButtonUp == m_atomLeftButtonDown && m_atomLeftButtonUp != e_dialog_result_none)
   {

      m_atomResult = m_atomLeftButtonUp;

      on_click(m_atomResult);

   }

}


void nano_window::on_click(const ::atom & atom)
{

   
}


void nano_window::move_to(int x, int y)
{

   m_pimplementation->move_to(x, y);

}


void nano_window::redraw()
{

   m_pimplementation->redraw();

}


void nano_window::get_client_rectangle(::rectangle_i32 & rectangle)
{

   rectangle.left = 0;
   rectangle.top = 0;
   rectangle.right = m_rectangle.width();
   rectangle.bottom = m_rectangle.height();

}


void nano_window::get_window_rectangle(::rectangle_i32 & rectangle)
{

   rectangle = m_rectangle;

}


void nano_window::set_capture()
{

   m_pimplementation->set_capture();

}


void nano_window::set_cursor(enum_cursor ecursor)
{

   m_pimplementation->set_cursor(ecursor);

}


bool nano_window::has_capture() const
{

   return m_pimplementation->has_capture();

}



void nano_window::release_capture()
{

   m_pimplementation->release_capture();

}


__pointer(nano_device) nano_window::create_device()
{

   throw interface_only();

   return nullptr;

}



