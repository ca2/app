#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
////#include "aura/user/user/_component.h"
#endif
#include <math.h>
#include "font_list.h"
#include "aura/graphics/draw2d/graphics.h"
#include "aura/graphics/write_text/fonts.h"
#include "aura/graphics/write_text/font_enumeration_item.h"
#include "aura/graphics/image/image.h"
#include "aura/graphics/image/drawing.h"
#include "aura/graphics/draw2d/lock.h"
#include "aura/user/user/interaction.h"


#define BOX 0
#define BOX_SEL 1
#define BOX_HOVER 2

template < primitive_rectangle RECTANGLE >
 tracer & operator << (tracer&  tracer, const RECTANGLE& r)
 {
    return tracer << r.left << ","<<r.top << ","<<r.right<< "," << r.bottom;
 }

namespace write_text
{


   font_list_item::font_list_item()
   {

   }


   font_list_item::~font_list_item()
   {

   }


   font_list::font_list()
   {

      m_bUpdatingFontList = false;

      m_iSelUpdateId = -1;

      m_puserinteraction = nullptr;

      m_rectangleMargin = rectangle_i32(5, 5, 5, 5);

      m_iSel = -1;

      m_iHover = -1;

      defer_create_mutex();

      m_uaForegroundColor[0][0] = argb(255, 80, 80, 80);
      m_uaForegroundColor[0][1] = argb(255, 45, 45, 45);
      m_uaForegroundColor[0][2] = argb(255, 255, 255, 255);

      m_uaBackgroundColor[0][0] = argb(0, 0, 0, 0);
      m_uaBackgroundColor[0][1] = argb(128, 128, 200, 152);
      m_uaBackgroundColor[0][2] = argb(128, 80, 80, 80);

      m_uaForegroundColor[1][0] = argb(255, 210, 210, 210);
      m_uaForegroundColor[1][1] = argb(128, 40, 40, 40);
      m_uaForegroundColor[1][2] = argb(128, 80, 80, 80);

      m_uaBackgroundColor[1][0] = argb(0, 0, 0, 0);
      m_uaBackgroundColor[1][1] = argb(127, 255, 255, 255);
      m_uaBackgroundColor[1][2] = argb(127, 230, 230, 230);

      m_efontlist = e_font_list_single_column;

   }


   font_list::~font_list()
   {


   }


   bool font_list::set_sel_by_name(string str)
   {

      synchronous_lock synchronouslock(mutex());

      index iSel = find_name(str);

      m_iSel = iSel;

      m_strFontFamily = str;

      return m_iSel >= 0;

   }


   void font_list::_001OnDrawWide(::draw2d::graphics_pointer & pgraphics)
   {

      INFORMATION("font_list::_001OnDrawWide 1");
      INFORMATION("font_list::_001OnDrawWide 2");
      INFORMATION("font_list::_001OnDrawWide 3");

      synchronous_lock synchronouslock(mutex());

      pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

      ::rectangle_i32 rectangleClient = m_puserinteraction->get_client_rect();

      rectangleClient += m_puserinteraction->get_context_offset();

      auto pfontlistdata = m_pfontlistdata;

      if (!pfontlistdata)
      {

         INFORMATION("!pfontlistdata");

         m_puserinteraction->set_need_layout();

         m_puserinteraction->set_need_redraw();

         m_puserinteraction->post_redraw();

         return;

      }

      auto cListDataCount = pfontlistdata->get_count();

      for (int i = 0; i < cListDataCount; i++)
      {

         if (i == m_iSel || i == m_iHover)
         {

            continue;

         }

         auto pitem = pfontlistdata->element_at(i);

         if (!pitem)
         {

            INFORMATION("!pitem (pfontlistdata->element_at(i))");

            continue;

         }

         text_box * pbox = &pitem->m_box[BOX];

         if (!pbox->is_layout_ok(this))
         {

            INFORMATION("!pitem (pbox->is_layout_ok(this))");

            continue;

         }

         if (!pbox->m_rectangle.intersects(rectangleClient))
         {

            if (pbox->m_rectangle.is_empty())
            {

               //INFORMATION("!pitem (pbox->m_rectangle.intersects(rectangleClient(EMPTY)))");

            }
            else if (rectangleClient.area() < 10'000)
            {

               //INFORMATION("!pitem (pbox->m_rectangle.intersects(rectangleClient(<10'000)))");

            }


            continue;

         }

         if (!pbox->is_drawing_ok(this))
         {

            pbox->update(this, BOX, pitem->m_strSample);

         }

         pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

         image_source imagesource(pbox->m_pimage);

         auto rectangle = pbox->m_rectangle;

         //INFORMATION("rect:" << rectangle);

         image_drawing_options imagedrawingoptions(rectangle);

         image_drawing imagedrawing(imagedrawingoptions, imagesource);

         pgraphics->draw(imagedrawing);

      }

      if (m_iSel >= 0)
      {

         auto pitem = pfontlistdata->element_at(m_iSel);

         if (pitem)
         {

            text_box* pbox = &pitem->m_box[BOX_SEL];

            if (!pbox->is_layout_ok(this))
            {

               update_extents(pfontlistdata, pitem, pgraphics, BOX_SEL);

            }

            if (!pbox->is_drawing_ok(this))
            {

               pbox->update(this, BOX_SEL, pitem->m_strSample);

            }

            pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

            image_source imagesource(pbox->m_pimage);

            auto rectangle = pbox->m_rectangle;

            image_drawing_options imagedrawingoptions(rectangle);

            image_drawing imagedrawing(imagedrawingoptions, imagesource);

            pgraphics->draw(imagedrawing);

         }

      }

      if (m_iHover >= 0 && m_iHover != m_iSel)
      {

         auto pitem = pfontlistdata->element_at(m_iHover);

         if (pitem)
         {

            text_box* pbox = &pitem->m_box[BOX_HOVER];

            if (!pbox->is_layout_ok(this))
            {

               update_extents(pfontlistdata, pitem, pgraphics, BOX_HOVER);

            }

            if (!pbox->is_drawing_ok(this))
            {

               pbox->update(this, BOX_HOVER, pitem->m_strSample);

            }

            pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

            image_source imagesource(pbox->m_pimage);

            rectangle_f64 rectangle(pbox->m_rectangle);

            image_drawing_options imagedrawingoptions(rectangle);

            image_drawing imagedrawing(imagedrawingoptions, imagesource);

            pgraphics->draw(imagedrawing);

         }

      }

   }


   void font_list::_001OnDrawSingleColumn(::draw2d::graphics_pointer & pgraphics)
   {

      synchronous_lock synchronouslock(mutex());

      pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

      auto pfontlistdata = m_pfontlistdata;

      rectangle_i32 rectangleClient = m_puserinteraction->get_client_rect();

      rectangleClient += m_puserinteraction->get_context_offset();

      auto pwindowing = m_puserinteraction->windowing();

      auto pointCursor = m_puserinteraction->get_cursor_position();

      pointCursor += m_puserinteraction->screen_to_client();

      pointCursor += m_puserinteraction->get_context_offset();

      bool bCheckHover = true;

      bool bIntersected = false;

      for (int i = 0; i < pfontlistdata->get_count(); i++)
      {

         if (pfontlistdata->element_at(i) == nullptr)
         {

            continue;

         }

         int iBox;

         iBox = BOX;

         auto pfontlistdata = m_pfontlistdata;

         text_box * pbox = &pfontlistdata->element_at(i)->m_box[iBox];

         rectangle_i32 rectangle = pbox->m_rectangle;

         rectangle.right = rectangle.left + m_size.cx;

         if (!pbox->is_drawing_ok(this))
         {

            pbox->update(this, iBox, pfontlistdata->element_at(i)->m_strSample);

         }

         if (!rectangleClient.intersects(rectangle))
         {

            if (bIntersected)
            {

               break;

            }

            continue;

         }

         if (bCheckHover && rectangle.contains_y(pointCursor.y))
         {

            m_puserinteraction->m_pitemHover = __new(::item({ ::e_element_item, i }));

            m_iHover = i;

            bCheckHover = false;

         }

         bIntersected = true;

         if (i == m_iSel)
         {

            if (!bCheckHover && i == m_iHover)
            {

               pgraphics->fill_rectangle(rectangle, m_puserinteraction->get_color(pgraphics->m_puserstyle, ::e_element_background, ::user::e_state_selected | ::user::e_state_hover));

            }
            else
            {

               pgraphics->fill_rectangle(rectangle, m_puserinteraction->get_color(pgraphics->m_puserstyle, ::e_element_background, ::user::e_state_selected));

            }

         }
         else if (!bCheckHover && i == m_iHover)
         {

            auto color = m_puserinteraction->get_color(pgraphics->m_puserstyle, ::e_element_background, ::user::e_state_hover);

            int iA = color.alpha;

            pgraphics->fill_rectangle(rectangle, color);

         }

         {

            pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

            image_source imagesource(pbox->m_pimage);

            rectangle_f64 rectangle(pbox->m_rectangle);

            image_drawing_options imagedrawingoptions(rectangle);

            image_drawing imagedrawing(imagedrawingoptions, imagesource);

            pgraphics->draw(imagedrawing);

         }

      }

   }


   void font_list::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      synchronous_lock synchronouslock(mutex());

      if (m_efontlist == e_font_list_wide)
      {

         _001OnDrawWide(pgraphics);

      }
      else
      {

         _001OnDrawSingleColumn(pgraphics);

      }

   }


   void font_list::update_extents(font_list_data * pfontlistdata, font_list_item * pitem, ::draw2d::graphics_pointer & pgraphics, index iBox)
   {

      text_box* pbox = &pitem->m_box[iBox];

      synchronous_lock synchronouslock(mutex());

      if (::is_null(pbox))
      {

         return;

      }

      if (!pbox->is_layout_ok(this))
      {

         synchronouslock.unlock();

         ::size_f64 s;

         string strText = m_strTextLayout;

         string str = pitem->m_strName;

         pbox->m_pfont.create(this);

         if (str.compare_ci("GOUDY STOUT") == 0)
         {

            output_debug_string("test05");

         }

         pbox->m_pfont->create_pixel_font(str, pfontlistdata->m_iaSize[iBox]);

         ::draw2d::lock draw2dlock(this);

         if (!pgraphics)
         {

            auto psystem = m_psystem->m_paurasystem;

            auto pdraw2d = psystem->draw2d();

            pgraphics = pdraw2d->create_memory_graphics(m_puserinteraction);

         }

         pgraphics->set(pbox->m_pfont);

         pbox->m_pfont->m_echaracterseta = pitem->m_echaracterseta;

         if (iBox == 0)
         {

            strText = m_strTextLayout;

            if (strText.is_empty() ||
               (pbox->m_pfont->get_character_set(pgraphics) != ::e_character_set_ansi
                  && pbox->m_pfont->get_character_set(pgraphics) != ::e_character_set_default))
            {

               strText = ::write_text::font::get_sample_text(pbox->m_pfont->m_echaracterset);

               if (strText.is_empty())
               {

                  strText = pitem->m_strName;

               }

            }

            if (strText.has_char())
            {

               s = pgraphics->get_text_extent(strText);

            }

            if (strText.has_char() && s.area() <= 0)
            {

               string strSample;

               int maxarea = 0;

               ::enum_character_set echarsetFound = pbox->m_pfont->get_character_set(pgraphics);

               size_i32 sSample;

               if (maxarea <= 0)
               {

                  strSample = m_strTextLayout;

                  if (strSample.has_char())
                  {

                     sSample = pgraphics->get_text_extent(strSample);

                     if (sSample.area() > maxarea)
                     {

                        maxarea = (int)(sSample.area());

                        strText = strSample;

                        s = sSample;

                     }

                  }

               }

               if (maxarea <= 0)
               {

                  strSample = pitem->m_strName;

                  if (strSample.has_char())
                  {

                     sSample = pgraphics->get_text_extent(strSample);

                     if (sSample.area() > maxarea)
                     {

                        maxarea = (int)(sSample.area());

                        strText = strSample;

                        s = sSample;

                     }

                  }

               }

               pbox->m_pfont->m_echaracterset = echarsetFound;

            }

            pitem->m_strSample = strText;

         }
         else
         {

            pbox->m_pfont->m_echaracterset = pitem->m_box[0].m_pfont->m_echaracterset;

            s = pgraphics->get_text_extent(pitem->m_strSample);

         }

         s.cx += m_rectangleMargin.left + m_rectangleMargin.right;

         s.cy += m_rectangleMargin.top + m_rectangleMargin.bottom;

         pbox->m_size = s;

         pbox->set_text_box_ok(false);

         pbox->set_text_box_init();

      }

   }


   void font_list::initialize(::object * pobject)
   {

      //auto estatus = 
      
      ::object::initialize(pobject);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      auto psystem = m_psystem->m_papexsystem;

      auto psignal = psystem->get_signal(id_operating_system_user_color_change);

      psignal->add_handler(this);

      call(id_operating_system_user_color_change);

      //return estatus;

   }


//   void font_list::on_subject(::topic * ptopic)
//   {
//
//      ::manager::on_subject(ptopic);
//
//   }


   void font_list::handle(::topic * ptopic, ::context * pcontext)
   {

      ::enum_id eid = (::enum_id)ptopic->m_atom.i64();

      if (eid == id_font_enumeration)
      {

         auto psystem = m_psystem->m_paurasystem;

         auto pdraw2d = psystem->draw2d();

         auto pwritetext = pdraw2d->write_text();

         pwritetext->handle_font_enumeration(ptopic);

      }
      else if (eid == id_font_extents)
      {

         update_extents();

      }
      else if (eid == id_font_list_layout)
      {

         layout();

      }
      else if (eid == id_font_list_total_size)
      {

         m_puserinteraction->set_need_layout();

         m_puserinteraction->set_need_redraw();

         m_puserinteraction->post_redraw();

      }
      else if (eid == id_font_list_redraw)
      {

         m_puserinteraction->set_need_redraw();

         m_puserinteraction->post_redraw();

      }
      else if (eid == id_operating_system_user_color_change)
      {

         auto psystem = m_psystem;

         auto pnode = psystem->node();

         m_bDarkMode = pnode->dark_mode();

      }

   }

   
   void font_list::set_font_list_type(enum_font_list efontlist)
   {

      m_efontlist = efontlist;

      if (::is_set(m_puserinteraction))
      {

         m_puserinteraction->set_need_layout();

         m_puserinteraction->set_need_redraw();

         m_puserinteraction->post_redraw();

      }

   }


   enum_font_list font_list::get_font_list_type() const
   {

      return m_efontlist;

   }


   void font_list::update_extents()
   {

      int_array iaSize;

      int iBaseSize;

      auto pfontlistdata = m_pfontlistdata;

      bool bSameSize = false;

      {

         auto psystem = m_psystem->m_paurasystem;

         auto pdraw2d = psystem->draw2d();

         auto pwritetext = pdraw2d->write_text();

         auto pfonts = pwritetext->fonts();

         auto pfontenumeration = pfonts->enumeration();

         if (!pfontenumeration->m_eventReady.wait(30_s))
         {

            return;

         }

         {

            synchronous_lock synchronouslock(mutex());

            m_pfontenumeration = pfontenumeration;

            m_pfontenumerationitema = pfontenumeration->m_pfontenumerationitema;

            if (!m_pfontenumerationitema)
            {

               return;

            }

         }

         if (m_efontlist != e_font_list_single_column && !m_rectangleClient)
         {

            return;

         }

         //if (m_rectangleClient.is_empty())
         //{

         //   return;

         //}

         if (m_efontlist == e_font_list_wide)
         {

            int iBaseHeight = maximum(250, m_rectangleClient.height());

            iBaseHeight = iBaseHeight + 250;

            int iStep = 200;

            int iDiv = 10;

            iBaseSize = ((iBaseHeight / iStep) * iStep) / iDiv;

         }
         else
         {

            iBaseSize = 18;

         }

         if (pfontlistdata.is_set() &&
            pfontlistdata->m_iUpdateId == m_pfontenumeration->m_iUpdateId
            && (m_efontlist == e_font_list_single_column ||
               pfontlistdata->m_rectangleClient == m_rectangleClient))
         {

            auto pfontlist = this;

            pfontlist->signal(id_font_list_layout);

            return;

         }

         if (pfontlistdata.is_set() && iBaseSize == pfontlistdata->m_iBaseSize)
         {

            if (pfontlistdata->m_iUpdateId == m_pfontenumeration->m_iUpdateId)
            {

               auto pfontlist = this;

               pfontlist->signal(id_font_list_layout);

               return;

            }

            bSameSize = true;

         }

         if (m_efontlist == e_font_list_wide)
         {

            iaSize.add(iBaseSize * 16 / 40);

            iaSize.add(iBaseSize * 24 / 40);

            iaSize.add(iBaseSize * 32 / 40);

         }
         else
         {

            iaSize.add(18);

         }

         if (pfontlistdata.is_set() && iaSize == pfontlistdata->m_iaSize
            && pfontlistdata->m_iUpdateId == m_pfontenumeration->m_iUpdateId)
         {

            auto pfontlist = this;

            pfontlist->signal(id_font_list_layout);

            return;

         }
         else
         {

            bSameSize = false;

         }

      }

      if (pfontlistdata == nullptr)
      {

         pfontlistdata = __create_new < font_list_data >();

         pfontlistdata->m_iSerial = 0;

         m_pfontlistdata = pfontlistdata;

         auto countFont = m_pfontenumerationitema->get_count();

         pfontlistdata->set_size(countFont);

      }
      else
      {

         // Remove absent/erased fonts

         __pointer(font_list_item) pitem;

         {

            synchronous_lock synchronouslock(mutex());

            for (index iItem = 0; iItem < pfontlistdata->get_count(); )
            {

               auto pitem = pfontlistdata->element_at(iItem);

               if (pitem && pitem->m_strName.has_char() && !m_pfontenumeration->has_font_name(pitem->m_strName))
               {

                  pfontlistdata->erase_at(iItem);

               }
               else
               {

                  iItem++;

               }

            }

            // Make room for new fonts

            for (index iItem = 0; iItem < m_pfontenumerationitema->get_count(); iItem++)
            {

               auto pitem = pfontlistdata->element_at(iItem);

               if (pitem && pitem->m_strName.has_char() && pitem->m_strName != m_pfontenumerationitema->ptr_at(iItem)->m_strName)
               {

                  __pointer(font_list_item) pitemNewEmpty;

                  pfontlistdata->insert_at(iItem, pitemNewEmpty);

               }

            }

            ASSERT(pfontlistdata->get_size() == m_pfontenumerationitema->get_count());

            pfontlistdata->m_iSerial++;

         }

         pfontlistdata->m_rectangleClient = m_rectangleClient;

         pfontlistdata->m_iUpdateId = m_pfontenumeration->m_iUpdateId;

         pfontlistdata->m_iUpdatedCount = 0;

         pfontlistdata->m_bLayoutStillIntersect = true;

         m_iLayoutSerial = 0;

      }

      pfontlistdata->m_iBaseSize = iBaseSize;

      pfontlistdata->m_iaSize = iaSize;

      auto iFontCount = pfontlistdata->get_count();

      

      auto procedure1 = [this, pfontlistdata, bSameSize](index iOrder, index iStart, index iCount, index iScan)
      {

         auto psystem = m_psystem->m_paurasystem;

         auto pdraw2d = psystem->draw2d();

         auto pgraphics = pdraw2d->create_memory_graphics(m_puserinteraction);

      restart:

         index iSerial = pfontlistdata->m_iSerial;

         string strText = m_strTextLayout;

         size_i32 s;

         ::rectangle_i32 rectangle;

         __pointer(font_list_item) plistitem;

         __pointer(font_enumeration_item) penumitem;

         //single_lock lock(mutex());

         for (index iItem = iStart; iItem < pfontlistdata->get_count(); iItem += iScan)
         {

            {

               synchronous_lock synchronouslock(mutex());

               if (pfontlistdata->m_iSerial != iSerial)
               {

                  goto restart;

               }

               if (iItem >= m_pfontenumerationitema->get_count())
               {

                  break;

               }

               plistitem = pfontlistdata->element_at(iItem);

               penumitem = m_pfontenumerationitema->element_at(iItem);

            }

            bool bNew = false;

            if (!penumitem)
            {

               continue;

            }

            if (!plistitem || plistitem->m_strFont.is_empty())
            {

               bNew = true;

               plistitem = __new(font_list_item);

               plistitem->m_iItem = iItem;

               plistitem->m_strFont = penumitem->m_strName;

               plistitem->m_strName = penumitem->m_strName;

               plistitem->m_echaracterseta = penumitem->m_echaracterseta;

            }
            else if (plistitem->m_strFont != penumitem->m_mapFileName[0])
            {

               INFORMATION("what?!?!");

               continue;

            }

            if (bNew || !bSameSize)
            {

               update_extents(pfontlistdata, plistitem, pgraphics, 0);

            }

            {

               synchronous_lock synchronouslock(mutex());

               if (pfontlistdata->m_iSerial != iSerial)
               {

                  goto restart;

               }

               pfontlistdata->element_at(iItem) = plistitem;

               if (!m_bLayoutWideStillIntersect)
               {

                  continue;

               }

            }

         }

      };

      auto procedure2 = [this, pfontlistdata]()
      {

         auto procedure3 = [this, pfontlistdata](index iOrder, index iStart, index iCount, index iScan)
         {

            auto iSerial = pfontlistdata->m_iSerial;

            ::draw2d::graphics_pointer pgraphics;

            string strText = m_strTextLayout;

            size_i32 s;

            ::rectangle_i32 rectangle;

            for (index i = iStart; i < iCount && ::task_get_run(); i += iScan)
            {

               auto pitem = pfontlistdata->element_at(i);

               for (index iBox = 1; iBox < pfontlistdata->m_iaSize.get_count(); iBox++)
               {

                  if (pfontlistdata->m_iSerial != iSerial)
                  {

                     return;

                  }

                  update_extents(pfontlistdata, pitem, pgraphics, iBox);

               }

            }

         };

         auto procedure4 = [this]()
         {

            layout();

         };

         fork_count(this, pfontlistdata->get_count(), procedure3, procedure4);

      };

      fork_count(this, pfontlistdata->get_count(), procedure1, procedure2);

   }


   void font_list::layout()
   {

      synchronous_lock synchronouslock(mutex());

      ::size_i32 sizeTotal;

      if (m_efontlist == e_font_list_wide)
      {

         sizeTotal = layout_wide();

      }
      else
      {

         sizeTotal = layout_single_column();

      }

      if (sizeTotal != m_size)
      {

         m_size = sizeTotal;

      }

      m_puserinteraction->set_need_layout();

      m_puserinteraction->set_need_redraw();

      m_puserinteraction->post_redraw();

      INFORMATION("font_list::layout() FINISHED 1");
      INFORMATION("font_list::layout() FINISHED 2");
      INFORMATION("font_list::layout() FINISHED 3");

   }


   ::size_i32 font_list::layout_wide()
   {

      if (::is_null(m_puserinteraction))
      {

         return ::size_i32();

      }

      INFORMATION("font_list::layout_wide");

      synchronous_lock synchronouslock(mutex());

      ::size_i32 sizeTotal;

      bool bIntersected = false;

      m_bLayoutWideStillIntersect = true;

      string strText = m_strTextLayout;

      size_i32 s;

      int iMargin = 40;

      int w = m_rectangleClient.width() - iMargin * 2;

      int iPadding = 15;

      int x = iMargin;

      int y = iMargin + iPadding;

      int h = 0;

      int hExtra = 0;

      int nextx;

      sizeTotal.cx = m_rectangleClient.width();

      rectangle_i32 rectangleClient = m_puserinteraction->get_client_rect();

      rectangleClient += m_puserinteraction->get_context_offset();

      auto pfontlistdata = m_pfontlistdata;

      if (pfontlistdata.is_null())
      {

         return sizeTotal;

      }

      int iLineStart = 0;

      auto iFontCount = pfontlistdata->get_count();

      for (int i = 0; i < iFontCount; i++)
      {

         font_list_item * pitem = pfontlistdata->element_at(i);

         if (pitem
            && !m_pfontenumeration->has_font_name(pitem->m_strFont)
            && !m_pfontenumeration->has_font_name(pitem->m_strName))
         {

            //pfontlistdata->erase_at(i);

            //iFontCount = pfontlistdata->get_count();

            //i--;

            continue;

         }

         if (pitem == nullptr)
         {

            sizeTotal.cy = y + hExtra;

            return sizeTotal;

         }

         size_i32 & s = pitem->m_box[0].m_size;

         auto & rectangle = pitem->m_box[0].m_rectangle;

         x += iPadding;

         nextx = x + s.cx + iPadding;

         if (nextx > w )
         {

            int iDen = (i - iLineStart - 1);

            if (iDen >= 1)
            {

               int iInc = (w - x + iPadding * 4) / (i - iLineStart - 1);

               int iOffset = iInc;

               for (int j = iLineStart + 1; j < i; j++)
               {

                  font_list_item * pitem2 = pfontlistdata->element_at(j);

                  auto & rect2 = pitem2->m_box[0].m_rectangle;

                  rect2.offset_x(iOffset);

                  iOffset += iInc;

               }

            }

            iLineStart = i;

            x = iMargin + iPadding;

            nextx = x + s.cx + iPadding;

            y += h + iPadding;

            h = 0;

            hExtra = 0;

         }

         //pgraphics->text_out(x + m_rectangleMargin.left,y + m_rectangleMargin.top,strText);

         rectangle.left = x;

         rectangle.top = y;

         rectangle.right = rectangle.left + s.cx;

         rectangle.bottom = rectangle.top + s.cy;

         if (rectangle.intersects(rectangleClient))
         {

            bIntersected = true;

         }
         else
         {

            if (bIntersected)
            {

               bIntersected = false;

               m_bLayoutWideStillIntersect = false;

            }

         }

         x = nextx;

         h = maximum(h, s.cy);

         hExtra = maximum(hExtra, s.cy);

      }

      for (int i = 0; i < iFontCount; i++)
      {

         font_list_item * pitem = pfontlistdata->element_at(i);

         size_i32 & s = pitem->m_box[0].m_size;

         auto & rectangle = pitem->m_box[0].m_rectangle;

         for (index j = 1; j < 3; j++)
         {

            auto & size2 = pitem->m_box[j].m_size;
            auto & rect2 = pitem->m_box[j].m_rectangle;

            int dw = (size2.cx - s.cx) / 2;
            int dh = (size2.cy - s.cy) / 2;

            int x = m_rectangleClient.center_x() - rectangle.center_x();

            if (x > 0)
            {

               x = m_rectangleClient.center_x() - rectangle.left;

            }
            else
            {

               x = m_rectangleClient.center_x() - rectangle.right;

            }

            x = x * (m_rectangleClient.width() + iPadding * 2) / w;

            if (x > 0)
            {
               rect2.left = m_rectangleClient.center_x() - x;
               rect2.right = rect2.left + size2.cx;
            }
            else
            {
               rect2.right = m_rectangleClient.center_x()- x;
               rect2.left = rect2.right - size2.cx;
            }
            rect2.top = rectangle.top - dh;
            rect2.bottom = rect2.top + size2.cy;

            hExtra = maximum(hExtra, size2.cy);

         }

      }

      sizeTotal.cy = y + hExtra + 5;

      return sizeTotal;

   }


   ::size_i32 font_list::layout_single_column()
   {

      synchronous_lock synchronouslock(mutex());

      ::size_i32 sizeTotal;

      string strText = m_strTextLayout;

      size_i32 s;

      int h = 0;

      sizeTotal.cx = 0;

      int xSingleColumn = 0;
      int ySingleColumn = 0;

      auto pfontlistdata = m_pfontlistdata;

      for (int i = 0; i < pfontlistdata->get_count(); i++)
      {

         font_list_item * pitem = pfontlistdata->element_at(i);

         if (pitem == nullptr)
         {

            sizeTotal.cy = ySingleColumn;

            return sizeTotal;

         }

         size_i32 & s = pitem->m_box[0].m_size;

         auto & rectangle = pitem->m_box[0].m_rectangle;



         pitem->m_box[0].m_rectangle.left = xSingleColumn;
         pitem->m_box[0].m_rectangle.top = ySingleColumn;
         pitem->m_box[0].m_rectangle.right = xSingleColumn + s.cx;
         pitem->m_box[0].m_rectangle.bottom = ySingleColumn + s.cy;

         sizeTotal.cx = maximum(m_size.cx, pitem->m_box[0].m_rectangle.right + 4);

         ySingleColumn += s.cy;

         h = maximum(h, s.cy);

      }

      sizeTotal.cy = ySingleColumn;

      return sizeTotal;

   }



   ::item_pointer font_list::hit_test(const ::point_i32& point)
   {

      synchronous_lock synchronouslock(mutex());

      if (m_efontlist == e_font_list_wide)
      {

         return hit_test_wide(point);

      }
      else
      {

         return hit_test_single_column(point);

      }

   }


   ::item_pointer font_list::hit_test_wide(const ::point_i32 & point)
   {

      synchronous_lock synchronouslock(mutex());

      auto pfontlistdata = m_pfontlistdata;

      if (!pfontlistdata)
      {

         auto pitemNone = __new(::item(::e_element_none));

         return pitemNone;

      }

      if (m_iHover >= 0)
      {

         if (pfontlistdata->element_at(m_iHover)->m_box[BOX_HOVER].m_rectangle.contains(point))
         {

            return __new(::item(::e_element_item, m_iHover));

         }

      }

      for (::index iItem = 0; iItem < pfontlistdata->get_size(); iItem++)
      {

         if (pfontlistdata->element_at(iItem) == nullptr)
         {

            continue;

         }

         if (pfontlistdata->element_at(iItem)->m_box[BOX].m_rectangle.contains(point))
         {

            return __new(::item(::e_element_item, iItem));

         }

      }

      auto pitemNone = __new(::item(::e_element_none));

      return pitemNone;

   }


   ::item_pointer font_list::hit_test_single_column(const ::point_i32 & point)
   {

      synchronous_lock synchronouslock(mutex());

      auto pfontlistdata = m_pfontlistdata;

      if (!pfontlistdata)
      {

         auto pitemNone = __new(::item(::e_element_none));

         return pitemNone;

      }

      for (index iItem = 0; iItem < pfontlistdata->get_size(); iItem++)
      {

         if (pfontlistdata->element_at(iItem) == nullptr)
         {

            continue;

         }

         rectangle_i32 rectangle(pfontlistdata->element_at(iItem)->m_box[BOX].m_rectangle);

         rectangle.right = rectangle.left + m_size.cx;

         if (rectangle.contains(point))
         {

            return __new(::item(::e_element_item, iItem));

         }

      }

      auto pitemNone = __new(::item(::e_element_none));

      return pitemNone;

   }


   bool font_list::get_box_rect(RECTANGLE_I32 * lprect, ::index i)
   {

      synchronous_lock synchronouslock(mutex());

      if (m_efontlist == e_font_list_wide)
      {

         return get_box_rect_wide(lprect, i);

      }
      else
      {

         return get_box_rect_single_column(lprect, i);

      }

   }


   bool font_list::get_box_rect_wide(RECTANGLE_I32 * lprect, ::index i)
   {

      synchronous_lock synchronouslock(mutex());

      auto pfontlistdata = m_pfontlistdata;

      if (!pfontlistdata)
      {

         return false;

      }

      if (i < 0 || i >= pfontlistdata->get_size())
      {

         return false;

      }

      if (pfontlistdata->element_at(i) == nullptr)
      {

         return false;

      }

      *lprect = pfontlistdata->element_at(i)->m_box[BOX].m_rectangle;

      return true;

   }


   bool font_list::get_box_rect_single_column(RECTANGLE_I32 * lprect, ::index i)
   {

      synchronous_lock synchronouslock(mutex());

      auto pfontlistdata = m_pfontlistdata;

      if (!pfontlistdata)
      {

         return false;

      }

      if (i < 0 || i >= pfontlistdata->get_size())
      {

         return false;

      }

      if (pfontlistdata->element_at(i) == nullptr)
      {

         return false;

      }

      *lprect = pfontlistdata->element_at(i)->m_box[BOX].m_rectangle;

      lprect->right = lprect->left + m_size.cx;

      return true;

   }


   void font_list::set_client_rectangle(const RECTANGLE_I32 * lpcrectangle)
   {

      ::rectangle_i32 rectangle(lpcrectangle);

      if (rectangle != m_rectangleClient)
      {

         ::size_i32 sizeOld(m_rectangleClient.size());

         ::size_i32 sizeNew(rectangle.size());

         m_rectangleClient = *lpcrectangle;

         if (sizeOld != sizeNew)
         {

            fork([this]()
               {

                  update_extents();

               });

         }

      }

   }


   index font_list::find_name(string str)
   {

      synchronous_lock synchronouslock(mutex());

      auto pfontlistdata = m_pfontlistdata;

      if (pfontlistdata.is_null())
      {

         return -1;

      }

      for (index i = 0; i < pfontlistdata->get_size(); i++)
      {

         if (m_pfontenumerationitema->element_at(i) == nullptr)
         {

            continue;

         }

         if(m_pfontenumerationitema->element_at(i)->m_strName.compare_ci(str) == 0)
         {

            return i;

         }

      }

      return -1;


   }


   bool font_list::is_updating() const
   {

      if (!m_pfontenumeration)
      {

         return true;

      }

      if (m_pfontenumeration->m_bUpdating)
      {

         return true;

      }

      return m_bUpdatingFontList;

   }


} // namespace write_text



