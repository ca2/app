#include "framework.h"
#include <math.h>
#include "font_list.h"
#include "acme/constant/id.h"
#include "acme/exception/interface_only.h"
#include "acme/parallelization/fork.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/handler/item.h"
#include "acme/platform/node.h"
#include "acme/user/user/content.h"
#include "apex/handler/signal.h"
#include "apex/platform/application.h"
#include "aura/graphics/draw2d/graphics.h"
#include "aura/graphics/write_text/fonts.h"
#include "aura/graphics/write_text/font_enumeration_item.h"
#include "aura/graphics/image/image.h"
#include "aura/graphics/image/drawing.h"
#include "aura/graphics/draw2d/lock.h"
#include "aura/user/user/interaction.h"
#include "aura/user/user/style.h"


#define BOX 0
#define BOX_SEL 1
#define BOX_HOVER 2

//template < primitive_rectangle RECTANGLE >
//class tracer & operator << (class tracer&  tracer, const RECTANGLE& r)
//{
//
//   return tracer << r.left() << ","<<r.top() << ","<<r.right()<< "," << r.bottom();
//
//}

namespace write_text
{


   font_list_item::font_list_item()
   {

      m_item.m_eelement = e_element_item;

   }


   font_list_item::~font_list_item()
   {

   }


   font_list::font_list()
   {

      m_bUpdatingFontList = false;

      m_iSelUpdateId = -1;

      m_puserinteraction = nullptr;

      m_rectangleMargin = int_rectangle(5, 5, 5, 5);

      //m_iSel = -1;

      //m_iHover = -1;

      defer_create_synchronization();

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


   bool font_list::set_sel_by_name(const ::scoped_string & scopedstr)
   {

      _synchronous_lock synchronouslock(this->synchronization());

      ::collection::index iSel = find_name(scopedstr);

      if (iSel >= 0)
      {

         m_puserinteraction->main_content().m_pitemCurrent = m_pfontlistdata->item_at(iSel);

      }
      else
      {

         m_puserinteraction->main_content().m_pitemCurrent.release();

      }

      m_strFontFamily = scopedstr;

      return ::is_item_set(m_puserinteraction->main_content().m_pitemCurrent);

   }


   void font_list::_001OnDrawWide(::draw2d::graphics_pointer & pgraphics)
   {

      //pgraphics->reset_clip();

      ::double_rectangle rectangleClipBox;
      
      pgraphics->get_clip_box(rectangleClipBox);

      //return;

      //information() << "font_list::_001OnDrawWide 1";
      //information() << "font_list::_001OnDrawWide 2";
      //information() << "font_list::_001OnDrawWide 3";

      _synchronous_lock synchronouslock(this->synchronization());

      pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

      auto rectangleWindow = m_puserinteraction->rectangle();

      auto pfontlistdata = m_pfontlistdata;

      if (!pfontlistdata)
      {

         information() << "!pfontlistdata";

         m_puserinteraction->set_need_layout();

         m_puserinteraction->set_need_redraw();

         m_puserinteraction->post_redraw();

         return;

      }

      if (m_pfontenumeration)
      {

         if (m_pfontenumerationAddRedrawHandler != m_pfontenumeration)
         {

            m_pfontenumerationAddRedrawHandler = m_pfontenumeration;

            m_pfontenumerationAddRedrawHandler->signal(id_font_list_redraw)->add_handler(this);

         }

         _synchronous_lock synchronouslockEnumeration(m_pfontenumeration->synchronization());

         auto pstyle = m_puserinteraction->get_style();

         if (pstyle->is_dark_mode())
         {

            pgraphics->set_text_color(::color::white);

         }
         else
         {

            pgraphics->set_text_color(::color::black);
         }

         pgraphics->set_text_color(::color::white);

         if (m_pfontenumeration->m_pathaLoading.get_count())
         {

            ::double_point point{10.0,10.0};

            for (::collection::index i = 0; i < m_pfontenumeration->m_pathaLoading.get_count(); i++)
            {

               pgraphics->text_out(point, "Loading " + m_pfontenumeration->m_pathaLoading[i].title());

               point.y() += (int)pgraphics->m_pfont->get_height(pgraphics);

            }

            return;

         }

      }

      auto cListDataCount = pfontlistdata->item_count();

      for (int i = 0; i < cListDataCount; i++)
      {

         ::pointer < font_list_item > pitem = pfontlistdata->item_at(i);

         if (!pitem)
         {

            information() << "!pitem (pfontlistdata->element_at(i))";

            continue;

         }

         if (pitem == m_puserinteraction->main_content().m_pitemCurrent || pitem == m_puserinteraction->m_pitemHover)
         {

            continue;

         }


         text_box * pbox = &pitem->m_box[BOX];

         if (!pbox->is_layout_ok(this))
         {

            information() << "!pitem (pbox->is_layout_ok(this))";

            continue;

         }

         if (!pbox->m_rectangle.intersects(rectangleWindow))
         {

            if (pbox->m_rectangle.is_empty())
            {

               //information() << "!pitem (pbox->m_rectangle.intersects(rectangleX(EMPTY)))";

            }
            else if (rectangleWindow.area() < 10'000)
            {

               //information() << "!pitem (pbox->m_rectangle.intersects(rectangleX(<10'000)))";

            }


            continue;

         }

         if (!pbox->is_drawing_ok(this))
         {

            pbox->update(this, BOX, pitem->m_strSample);

         }

         pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

         ::image::image_source imagesource(pbox->m_pimage);

         auto rectangle = pbox->m_rectangle;

         //information() << "rect:" << rectangle;

         ::image::image_drawing_options imagedrawingoptions(rectangle);

         ::image::image_drawing imagedrawing(imagedrawingoptions, imagesource);

         pgraphics->draw(imagedrawing);

      }

      if (::is_item_set(m_puserinteraction->main_content().m_pitemCurrent))
      {

         ::pointer < font_list_item > pitem = m_puserinteraction->main_content().m_pitemCurrent;

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

            ::image::image_source imagesource(pbox->m_pimage);

            auto rectangle = pbox->m_rectangle;

            ::image::image_drawing_options imagedrawingoptions(rectangle);

            ::image::image_drawing imagedrawing(imagedrawingoptions, imagesource);

            pgraphics->draw(imagedrawing);

         }

      }

      if (::is_item_set(m_puserinteraction->m_pitemHover) &&
         m_puserinteraction->m_pitemHover != m_puserinteraction->main_content().m_pitemCurrent)
      {

         ::pointer < font_list_item > pitem = m_puserinteraction->m_pitemHover;

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

            ::image::image_source imagesource(pbox->m_pimage);

            double_rectangle rectangle(pbox->m_rectangle);

            ::image::image_drawing_options imagedrawingoptions(rectangle);

            ::image::image_drawing imagedrawing(imagedrawingoptions, imagesource);

            pgraphics->draw(imagedrawing);

         }

      }

   }


   void font_list::_001OnDrawSingleColumn(::draw2d::graphics_pointer & pgraphics, ::user::interaction * puserinteraction)
   {

      _synchronous_lock synchronouslock(this->synchronization());

      pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

      auto pfontlistdata = m_pfontlistdata;

      int_rectangle rectangleClient = puserinteraction->rectangle();

      //rectangleX += m_puserinteraction->get_context_offset();

      //auto pwindowing = m_puserinteraction->windowing();

      //auto pointcursor = m_puserinteraction->mouse_cursor_position();

      ///pointCursor += m_puserinteraction->get_context_offset();

      //bool bCheckHover = true;

      bool bIntersected = false;

      for (int i = 0; i < pfontlistdata->item_count(); i++)
      {

         if (pfontlistdata->item_at(i) == nullptr)
         {

            continue;

         }

         int iBox;

         iBox = BOX;

         auto pfontlistdata = m_pfontlistdata;

         ::pointer < font_list_item > pfontlistitem = pfontlistdata->item_at(i);

         text_box * pbox = &pfontlistitem->m_box[iBox];

         int_rectangle rectangle = pbox->m_rectangle;

         rectangle.right() = rectangle.left() + m_size.cx();

         if (!pbox->is_drawing_ok(this))
         {

            pbox->update(this, iBox, pfontlistitem->m_strSample);

         }

         if (!rectangleClient.intersects(rectangle))
         {

            if (bIntersected)
            {

               break;

            }

            continue;

         }

         //if (bCheckHover && rectangle.contains_y(pointCursor.y()))
         //{

         //   //m_puserinteraction->m_pitemHover = øallocate ::item({ ::e_element_item, i });

         //   m_puserinteraction->m_pitemHover = pfontlistitem;

         //   //m_iHover = i;

         //   bCheckHover = false;

         //}

         bIntersected = true;

         auto pitemCurrent = puserinteraction->main_content().m_pitemCurrent;

         if (pfontlistitem == pitemCurrent)
         {

            if (pfontlistitem == puserinteraction->m_pitemHover)
            {

               pgraphics->fill_rectangle(rectangle, puserinteraction->get_color(pgraphics->m_puserstyleGraphics, ::e_element_background, ::user::e_state_selected | ::user::e_state_hover));

            }
            else
            {

               pgraphics->fill_rectangle(rectangle, puserinteraction->get_color(pgraphics->m_puserstyleGraphics, ::e_element_background, ::user::e_state_selected));

            }

         }
         else if (pfontlistitem == puserinteraction->m_pitemHover)
         {

            auto color = puserinteraction->get_color(pgraphics->m_puserstyleGraphics, ::e_element_background, ::user::e_state_hover);

            //auto u8Opacity = color.m_uchOpacity;

            pgraphics->fill_rectangle(rectangle, color);

         }

         {

            pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

            ::image::image_source imagesource(pbox->m_pimage);

            double_rectangle rectangle(pbox->m_rectangle);

            ::image::image_drawing_options imagedrawingoptions(rectangle);

            ::image::image_drawing imagedrawing(imagedrawingoptions, imagesource);

            pgraphics->draw(imagedrawing);

         }

      }

   }


   void font_list::_001OnDraw(::draw2d::graphics_pointer & pgraphics, ::user::interaction * puserinteraction)
   {

      _synchronous_lock synchronouslock(this->synchronization());

      if (m_efontlist == e_font_list_wide)
      {

         _001OnDrawWide(pgraphics);

      }
      else
      {

         _001OnDrawSingleColumn(pgraphics, puserinteraction);

      }

   }


   void font_list::update_extents(font_list_data * pfontlistdata, font_list_item * pitem, ::draw2d::graphics_pointer & pgraphics, ::collection::index iBox)
   {

      text_box* pbox = &pitem->m_box[iBox];

      _synchronous_lock synchronouslock(this->synchronization());

      if (::is_null(pbox))
      {

         return;

      }

      if (!pbox->is_layout_ok(this))
      {

         synchronouslock.unlock();

         ::double_size s;

         string strText = m_strTextLayout;

         string str = pitem->m_strName;

         øconstruct(pbox->m_pfont);

         if (str.case_insensitive_order("GOUDY STOUT") == 0)
         {

            informationf("test05");

         }

         pbox->m_pfont->create_font({ str, pitem->m_strBranch }, font_size(pfontlistdata->m_iaSize[iBox], e_unit_pixel));

         pbox->m_pfont->m_path = pitem->m_path;

         ::draw2d::lock draw2dlock(this);

         if (!pgraphics)
         {

            auto psystem = system();

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

               strText = node()->get_character_set_default_sample_text(pbox->m_pfont->m_echaracterset);

               if (strText.is_empty())
               {

                  strText = pitem->m_strName;

               }

            }

            if (strText.has_character())
            {

               s = pgraphics->get_text_extent(strText);

            }

            if (strText.has_character() && s.area() <= 0)
            {

               string strSample;

               int maxarea = 0;

               ::enum_character_set echarsetFound = pbox->m_pfont->get_character_set(pgraphics);

               int_size sSample;

               if (maxarea <= 0)
               {

                  strSample = m_strTextLayout;

                  if (strSample.has_character())
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

                  if (strSample.has_character())
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

         s.cx() += m_rectangleMargin.left() + m_rectangleMargin.right();

         s.cy() += m_rectangleMargin.top() + m_rectangleMargin.bottom();

         pbox->m_size = s;

         pbox->set_text_box_ok(false);

         pbox->set_text_box_init();

         m_size.cx() = (int) maximum(m_size.cx(), s.cx());

      }

   }


   void font_list::initialize(::particle * pparticle)
   {

      //auto estatus = 
      
      ::object::initialize(pparticle);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      auto psystem = system();

      ::cast < ::manager > pmanager = psystem;

      if(pmanager)
      {

         auto psignal = pmanager->signal(id_operating_system_user_color_change);

         if(psignal)
         {

            psignal->add_handler(this);

         }

      }

      send_signal(id_operating_system_user_color_change);

      //return estatus;

   }


//   void font_list::on_subject(::topic * ptopic)
//   {
//
//      ::manager::on_subject(ptopic);
//
//   }


   void font_list::handle(::topic * ptopic, ::handler_context * phandlercontext)
   {

      ::enum_id eid = (::enum_id)ptopic->id().as_long_long();

      if (eid == id_font_enumeration)
      {

         auto psystem = system();

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

         auto psystem = system();

         m_bDarkMode = psystem->dark_mode();

      }
      else if (eid == id_application_dark_mode_change)
      {

         auto psystem = system();

         m_bDarkMode = psystem->dark_mode();

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

      ::int_array_base iaSize;

      int iBaseSize;

      auto pfontlistdata = m_pfontlistdata;

      bool bSameSize = false;

      {

         auto psystem = system();

         auto pdraw2d = psystem->draw2d();

         auto pwritetext = pdraw2d->write_text();

         auto pfonts = pwritetext->fonts();

         auto pfontenumeration = pfonts->enumeration(m_strFontBranch);

         if (!pfontenumeration->m_happeningReady.wait(30_s))
         {

            return;

         }

         {

            _synchronous_lock synchronouslock(this->synchronization());

            m_pfontenumeration = pfontenumeration;

            m_pfontenumerationitema = pfontenumeration->m_pfontenumerationitema;

            if (!m_pfontenumerationitema)
            {

               return;

            }

         }

         if (m_efontlist != e_font_list_single_column && m_rectangleX.is_empty())
         {

            return;

         }

         //if (m_rectangleX.is_empty())
         //{

         //   return;

         //}

         if (m_efontlist == e_font_list_wide)
         {

            int iBaseHeight = maximum(250, m_rectangleX.height());

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
               pfontlistdata->m_rectangleX == m_rectangleX))
         {

            auto pfontlist = this;

            pfontlist->send_signal(id_font_list_layout);

            return;

         }

         if (pfontlistdata.is_set() && iBaseSize == pfontlistdata->m_iBaseSize)
         {

            if (pfontlistdata->m_iUpdateId == m_pfontenumeration->m_iUpdateId)
            {

               auto pfontlist = this;

               pfontlist->send_signal(id_font_list_layout);

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

         if (pfontlistdata.is_set() 
            && ::acme::array::is_equal(iaSize, pfontlistdata->m_iaSize)
            && pfontlistdata->m_iUpdateId == m_pfontenumeration->m_iUpdateId)
         {

            auto pfontlist = this;

            pfontlist->send_signal(id_font_list_layout);

            return;

         }
         else
         {

            bSameSize = false;

         }

      }

      if (pfontlistdata == nullptr)
      {

         pfontlistdata = øcreate_new < font_list_data >();

         pfontlistdata->m_iSerial = 0;

         m_pfontlistdata = pfontlistdata;

         auto countFont = m_pfontenumerationitema->get_count();

         ødefer_construct_new(pfontlistdata->m_pitema);

         pfontlistdata->m_pitema->set_size(countFont);

      }
      else
      {

         // Remove absent/erased fonts

         ::pointer<font_list_item>pitem;

         {

            _synchronous_lock synchronouslock(this->synchronization());

            for (::collection::index iItem = 0; iItem < pfontlistdata->item_count(); )
            {

               ::pointer < font_list_item > pitem = pfontlistdata->item_at(iItem);

               if (pitem && pitem->m_strName.has_character() && !m_pfontenumeration->has_font_name(pitem->m_strName))
               {

                  pfontlistdata->m_pitema->erase_at(iItem);

               }
               else
               {

                  iItem++;

               }

            }

            // Make room for ___new fonts

            for (::collection::index iItem = 0; iItem < m_pfontenumerationitema->get_count(); iItem++)
            {

               ::pointer < font_list_item > pitem = pfontlistdata->item_at(iItem);

               if (pitem && pitem->m_strName.has_character() && pitem->m_strName != m_pfontenumerationitema->ptr_at(iItem)->m_strName)
               {

                  ::pointer<font_list_item>pitemNewEmpty;

                  pitemNewEmpty->m_item.m_iItem = iItem;

                  pfontlistdata->m_pitema->insert_at(iItem, pitemNewEmpty);

               }

            }

            ASSERT(pfontlistdata->item_count() == m_pfontenumerationitema->get_count());

            pfontlistdata->m_iSerial++;

         }

         pfontlistdata->m_rectangleX = m_rectangleX;

         pfontlistdata->m_iUpdateId = m_pfontenumeration->m_iUpdateId;

         pfontlistdata->m_iUpdatedCount = 0;

         pfontlistdata->m_bLayoutStillIntersect = true;

         m_iLayoutSerial = 0;

      }

      pfontlistdata->m_iBaseSize = iBaseSize;

      pfontlistdata->m_iaSize = iaSize;

      auto iFontCount = pfontlistdata->item_count();

      auto procedure1 = [this, pfontlistdata, bSameSize](::collection::index iOrder, ::collection::index iStart, ::collection::index iCount, ::collection::index iScan)
      {

         auto psystem = system();

         auto pdraw2d = psystem->draw2d();

         auto pgraphics = pdraw2d->create_memory_graphics(m_puserinteractionGraphicsContext ? m_puserinteractionGraphicsContext : m_puserinteraction);

      restart:

         ::collection::index iSerial = pfontlistdata->m_iSerial;

         string strText = m_strTextLayout;

         int_size s;

         ::int_rectangle rectangle;

         ::pointer<font_list_item>plistitem;

         ::pointer<font_enumeration_item>penumitem;

         //single_lock lock(mutex());

         for (::collection::index iItem = iStart; iItem < pfontlistdata->item_count(); iItem += iScan)
         {

            {

               _synchronous_lock synchronouslock(this->synchronization());

               if (pfontlistdata->m_iSerial != iSerial)
               {

                  goto restart;

               }

               if (iItem >= m_pfontenumerationitema->get_count())
               {

                  break;

               }

               plistitem = pfontlistdata->item_at(iItem);

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

               plistitem = øallocate font_list_item();

               plistitem->m_item.m_iItem = iItem;

               plistitem->m_strFont = penumitem->m_strName;

               plistitem->m_strName = penumitem->m_strName;

               plistitem->m_strBranch = penumitem->m_strBranch;

               plistitem->m_path = penumitem->m_mapFileName[0];

               plistitem->m_echaracterseta = penumitem->m_echaracterseta;

            }
            //else if (plistitem->m_strFont != penumitem->m_mapFileName[0])
            //{
//
               //information() << "what?!?!";
               //
               //continue;

            //}

            if (bNew || !bSameSize)
            {

               update_extents(pfontlistdata, plistitem, pgraphics, 0);

            }

            {

               _synchronous_lock synchronouslock(this->synchronization());

               if (pfontlistdata->m_iSerial != iSerial)
               {

                  goto restart;

               }

               pfontlistdata->indexed_set_item_at(iItem, plistitem);

               if (!m_bLayoutWideStillIntersect)
               {

                  continue;

               }

            }

         }

      };

      auto procedure2 = [this, pfontlistdata]()
      {

         auto procedure3 = [this, pfontlistdata](::collection::index iOrder, ::collection::index iStart, ::collection::index iCount, ::collection::index iScan)
         {

            auto iSerial = pfontlistdata->m_iSerial;

            ::draw2d::graphics_pointer pgraphics;

            string strText = m_strTextLayout;

            int_size s;

            ::int_rectangle rectangle;

            for (::collection::index i = iStart; i < iCount && ::task_get_run(); i += iScan)
            {

               ::pointer < font_list_item > pitem = pfontlistdata->item_at(i);

               for (::collection::index iBox = 1; iBox < pfontlistdata->m_iaSize.get_count(); iBox++)
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

         m_papplication->fork_count(pfontlistdata->item_count(), procedure3, procedure4);

      };

      m_papplication->fork_count(pfontlistdata->item_count(), procedure1, procedure2);
   }


   void font_list::layout()
   {

      _synchronous_lock synchronouslock(this->synchronization());

      ::int_size sizeTotal;

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

      if (m_puserinteraction)
      {

         m_puserinteraction->set_need_layout();

         m_puserinteraction->set_need_redraw();

         m_puserinteraction->post_redraw();

      }
      else
      {

         send_signal(id_font_list_redraw);

      }

      information() << "font_list::layout() FINISHED 1";
      information() << "font_list::layout() FINISHED 2";
      information() << "font_list::layout() FINISHED 3";

   }


   ::int_size font_list::layout_wide()
   {

      if (::is_null(m_puserinteraction))
      {

         return ::int_size();

      }

      information() << "font_list::layout_wide";

      _synchronous_lock synchronouslock(this->synchronization());

      ::int_size sizeTotal;

      bool bIntersected = false;

      m_bLayoutWideStillIntersect = true;

      string strText = m_strTextLayout;

      int_size s;

      int iMargin = 40;

      int w = m_rectangleX.width() - iMargin * 2;

      int iPadding = 15;

      int x = iMargin;

      int y = iMargin + iPadding;

      int h = 0;

      int hExtra = 0;

      int nextx;

      sizeTotal.cx() = m_rectangleX.width();

      int_rectangle rectangleX = m_puserinteraction->raw_rectangle();

      //rectangleX += m_puserinteraction->get_context_offset();

      auto pfontlistdata = m_pfontlistdata;

      if (pfontlistdata.is_null())
      {

         return sizeTotal;

      }

      int iLineStart = 0;

      auto iFontCount = pfontlistdata->item_count();

      for (int i = 0; i < iFontCount; i++)
      {

         ::pointer < font_list_item > pitem = pfontlistdata->item_at(i);

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

            sizeTotal.cy() = y + hExtra;

            return sizeTotal;

         }

         int_size & s = pitem->m_box[0].m_size;

         auto & rectangle = pitem->m_box[0].m_rectangle;

         x += iPadding;

         nextx = x + s.cx() + iPadding;

         if (nextx > w )
         {

            int iDen = (i - iLineStart - 1);

            if (iDen >= 1)
            {

               int iInc = (w - x + iPadding * 4) / (i - iLineStart - 1);

               int iOffset = iInc;

               for (int j = iLineStart + 1; j < i; j++)
               {

                  ::pointer < font_list_item > pitem2 = pfontlistdata->item_at(j);

                  auto & rect2 = pitem2->m_box[0].m_rectangle;

                  rect2.offset_x(iOffset);

                  iOffset += iInc;

               }

            }

            iLineStart = i;

            x = iMargin + iPadding;

            nextx = x + s.cx() + iPadding;

            y += h + iPadding;

            h = 0;

            hExtra = 0;

         }

         //pgraphics->text_out(x + m_rectangleMargin.left(),y + m_rectangleMargin.top(),strText);

         rectangle.left() = x;

         rectangle.top() = y;

         rectangle.right() = rectangle.left() + s.cx();

         rectangle.bottom() = rectangle.top() + s.cy();

         if (rectangle.intersects(rectangleX))
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

         h = maximum(h, s.cy());

         hExtra = maximum(hExtra, s.cy());

      }

      for (int i = 0; i < iFontCount; i++)
      {

         ::pointer < font_list_item > pitem = pfontlistdata->item_at(i);

         int_size & s = pitem->m_box[0].m_size;

         auto & rectangle = pitem->m_box[0].m_rectangle;

         for (::collection::index j = 1; j < 3; j++)
         {

            auto & size2 = pitem->m_box[j].m_size;
            auto & rect2 = pitem->m_box[j].m_rectangle;

            int dw = (size2.cx() - s.cx()) / 2;
            int dh = (size2.cy() - s.cy()) / 2;

            int x = m_rectangleX.center_x() - rectangle.center_x();

            if (x > 0)
            {

               x = m_rectangleX.center_x() - rectangle.left();

            }
            else
            {

               x = m_rectangleX.center_x() - rectangle.right();

            }

            x = x * (m_rectangleX.width() + iPadding * 2) / w;

            if (x > 0)
            {
               rect2.left() = m_rectangleX.center_x() - x;
               rect2.right() = rect2.left() + size2.cx();
            }
            else
            {
               rect2.right() = m_rectangleX.center_x()- x;
               rect2.left() = rect2.right() - size2.cx();
            }
            rect2.top() = rectangle.top() - dh;
            rect2.bottom() = rect2.top() + size2.cy();

            hExtra = maximum(hExtra, size2.cy());

         }

      }

      sizeTotal.cy() = y + hExtra + 5;

      return sizeTotal;

   }


   ::int_size font_list::layout_single_column()
   {

      _synchronous_lock synchronouslock(this->synchronization());

      ::int_size sizeTotal;

      string strText = m_strTextLayout;

      int_size s;

      int h = 0;

      sizeTotal.cx() = 0;

      int xSingleColumn = 0;
      int ySingleColumn = 0;

      auto pfontlistdata = m_pfontlistdata;

      for (int i = 0; i < pfontlistdata->item_count(); i++)
      {

         ::pointer < font_list_item > pitem = pfontlistdata->item_at(i);

         if (pitem == nullptr)
         {

            sizeTotal.cy() = ySingleColumn;

            return sizeTotal;

         }

         int_size & s = pitem->m_box[0].m_size;

         auto & rectangle = pitem->m_box[0].m_rectangle;

         pitem->m_box[0].m_rectangle.left() = xSingleColumn;
         pitem->m_box[0].m_rectangle.top() = ySingleColumn;
         pitem->m_box[0].m_rectangle.right() = xSingleColumn + s.cx();
         pitem->m_box[0].m_rectangle.bottom() = ySingleColumn + s.cy();

         sizeTotal.cx() = maximum(m_size.cx(), pitem->m_box[0].m_rectangle.right() + 4);

         ySingleColumn += s.cy();

         h = maximum(h, s.cy());

      }

      sizeTotal.cy() = ySingleColumn;

      return sizeTotal;

   }


   ::item_pointer font_list::hit_test(const ::int_point & point, ::user::e_zorder ezorder)
   {

      _synchronous_lock synchronouslock(this->synchronization());

      if (m_efontlist == e_font_list_wide)
      {

         return hit_test_wide(point);

      }
      else
      {

         return hit_test_single_column(point);

      }

   }


   ::item_pointer font_list::hit_test_wide(const ::int_point & point)
   {

      _synchronous_lock synchronouslock(this->synchronization());

      auto pfontlistdata = m_pfontlistdata;

      if (!pfontlistdata)
      {

         auto pitemNone = øallocate ::item(::e_element_none);

         return pitemNone;

      }

      if (::is_item_set(m_puserinteraction->m_pitemHover))
      {

         ::pointer < font_list_item > pfontlistitemHover = m_puserinteraction->m_pitemHover;

         if (pfontlistitemHover && pfontlistitemHover->m_box[BOX_HOVER].m_rectangle.contains(point))
         {

            return m_puserinteraction->m_pitemHover;

         }

      }

      for (::collection::index iItem = 0; iItem < pfontlistdata->item_count(); iItem++)
      {

         if (pfontlistdata->item_at(iItem) == nullptr)
         {

            continue;

         }

         ::pointer < font_list_item > pfontlistitem = pfontlistdata->item_at(iItem);

         if (pfontlistitem->m_box[BOX].m_rectangle.contains(point))
         {

            //return øallocate ::item(::e_element_item, iItem);
            return pfontlistitem;

         }

      }

      //auto pitemNone = øallocate ::item(::e_element_none);

      //return pitemNone;

      return nullptr;

   }


   ::item_pointer font_list::hit_test_single_column(const ::int_point & point)
   {

      _synchronous_lock synchronouslock(this->synchronization());

      auto pfontlistdata = m_pfontlistdata;

      if (!pfontlistdata)
      {

         auto pitemNone = øallocate ::item(::e_element_none);

         return pitemNone;

      }

      for (::collection::index iItem = 0; iItem < pfontlistdata->item_count(); iItem++)
      {

         ::pointer < font_list_item > pfontlistitem = pfontlistdata->item_at(iItem);

         if (!pfontlistitem)
         {

            continue;

         }

         int_rectangle rectangle(pfontlistitem->m_box[BOX].m_rectangle);

         rectangle.right() = rectangle.left() + m_size.cx();

         if (rectangle.contains(point))
         {

            return pfontlistitem;

         }

      }

      //auto pitemNone = øallocate ::item(::e_element_none);

      // return pitemNone;

      return nullptr;

   }


   ::status < int_rectangle >font_list::item_rectangle(::item * pitem)
   {

      ::int_rectangle r;

      if (!get_box_rect(&r, ::item_index(pitem)))
      {

         return error_failed;

      }

      return r;

   }


   bool font_list::get_box_rect(::int_rectangle * lprect, ::collection::index i)
   {

      _synchronous_lock synchronouslock(this->synchronization());

      if (m_efontlist == e_font_list_wide)
      {

         return get_box_rect_wide(lprect, i);

      }
      else
      {

         return get_box_rect_single_column(lprect, i);

      }

   }


   bool font_list::get_box_rect_wide(::int_rectangle * lprect, ::collection::index i)
   {

      _synchronous_lock synchronouslock(this->synchronization());

      auto pfontlistdata = m_pfontlistdata;

      if (!pfontlistdata)
      {

         return false;

      }

      if (i < 0 || i >= pfontlistdata->item_count())
      {

         return false;

      }

      ::pointer < font_list_item > pfontlistitem = pfontlistdata->item_at(i);

      if (!pfontlistitem)
      {

         return false;

      }

      *lprect = pfontlistitem->m_box[BOX].m_rectangle;

      return true;

   }


   bool font_list::get_box_rect_single_column(::int_rectangle * lprect, ::collection::index i)
   {

      _synchronous_lock synchronouslock(this->synchronization());

      auto pfontlistdata = m_pfontlistdata;

      if (!pfontlistdata)
      {

         return false;

      }

      if (i < 0 || i >= pfontlistdata->item_count())
      {

         return false;

      }

      ::pointer < font_list_item > pfontlistitem = pfontlistdata->item_at(i);

      if (!pfontlistitem)
      {

         return false;

      }

      *lprect = pfontlistitem->m_box[BOX].m_rectangle;

      lprect->right() = lprect->left() + m_size.cx();

      return true;

   }


   void font_list::set_client_rectangle(const ::int_rectangle &rectangleParam)
   {

      ::int_rectangle rectangle(rectangleParam);

      if (rectangle != m_rectangleX)
      {

         ::int_size sizeOld(m_rectangleX.size());

         ::int_size sizeNew(rectangle.size());

         m_rectangleX = rectangle;

         if (sizeOld != sizeNew)
         {

            fork([this]()
               {

                  update_extents();

               });

         }

      }

   }


   ::collection::index font_list::find_name(const ::scoped_string & scopedstr)
   {

      _synchronous_lock synchronouslock(this->synchronization());

      auto pfontlistdata = m_pfontlistdata;

      if (pfontlistdata.is_null())
      {

         return -1;

      }

      for (::collection::index i = 0; i < pfontlistdata->item_count(); i++)
      {

         ::pointer < font_list_item > pfontlistitem = pfontlistdata->item_at(i);

         if (!pfontlistitem)
         {

            continue;

         }

         if(pfontlistitem->m_strName.case_insensitive_order(scopedstr) == 0)
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


   void font_list::set_font_branch(const ::scoped_string & scopedstrFontBranch)
   {

      m_strFontBranch = scopedstrFontBranch;

      //on_update_font_branch();

   }


   void font_list::on_update_font_branch()
   {

      update_extents();

   }


} // namespace write_text



