#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "aura/user/_user.h"
#endif

#include <math.h>

#define BOX 0
#define BOX_SEL 1
#define BOX_HOVER 2


namespace draw2d
{


   font_list_item::font_list_item()
   {

   }


   font_list_item::~font_list_item()
   {

   }


   font_list::font_list()
   {

      m_bUpdatesHooked = false;

      m_bUpdating = false;

      m_iSelUpdateId = -1;

      m_puserinteraction = nullptr;
      m_rectMargin = rect(5, 5, 5, 5);
      m_iSel = -1;
      m_iHover = -1;

      defer_create_mutex();

      m_dwaFg.add(ARGB(255, 80, 80, 80));
      m_dwaFg.add(ARGB(255, 45, 45, 45));
      m_dwaFg.add(ARGB(255, 255, 255, 255));

      m_dwaBg.add(ARGB(0, 0, 0, 0));
      m_dwaBg.add(ARGB(128, 128, 200, 152));
      m_dwaBg.add(ARGB(128, 80, 80, 80));

      m_etype = type_single_column;

   }


   font_list::~font_list()
   {


   }


   void font_list::defer_font_enumeration(::promise::subject * psubject)
   {

      try
      {

         sync_lock sl(mutex());

         if (m_pfontenumeration.is_null())
         {

            System.draw2d().fonts().defer_create_font_enumeration(psubject);

            m_pfontenumeration = System.draw2d().fonts().m_pfontenumeration;

         }

      }
      catch (...)
      {

      }

   }


   void font_list::update_font_enumeration(::promise::subject * psubject)
   {

      try
      {

         sync_lock sl(mutex());

         defer_font_enumeration(psubject);

         m_pfontenumeration->update(psubject);

      }
      catch (...)
      {

      }

   }


   void font_list::sync_font_enumeration(::promise::subject * psubject)
   {

      try
      {

         sync_lock sl(mutex());

         defer_font_enumeration(psubject);

         m_pitema = m_pfontenumeration->m_pitema;

      }
      catch (...)
      {

      }

   }


   bool font_list::set_sel_by_name(string str)
   {

      sync_lock sl(mutex());

      index iSel = find_name(str);

      m_iSel = iSel;

      m_strFontFamily = str;

      return m_iSel >= 0;

   }


   void font_list::_001OnDrawWide(::draw2d::graphics_pointer & pgraphics)
   {

      sync_lock sl(mutex());

      pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

      ::rect rectClient = pgraphics->m_puserinteraction->get_client_rect();

      rectClient += pgraphics->m_puserinteraction->get_viewport_offset();

      auto plistdata = m_plistdata;

      if (plistdata.is_null())
      {

         //m_puserinteraction->set_need_layout();

         //m_puserinteraction->set_need_redraw();

         return;

      }

      auto cListDataCount = plistdata->get_count();

      for (int i = 0; i < cListDataCount; i++)
      {

         if (i == m_iSel || i == m_iHover)
         {

            continue;

         }

         auto pitem = plistdata->element_at(i);

         if (!pitem)
         {

            continue;

         }

         text_box * pbox = &pitem->m_box[BOX];

         if (!pbox->m_bInit)
         {

            continue;

         }

         if (!pbox->m_rect.intersects(rectClient))
         {

            continue;

         }

         if (!pbox->m_bOk)
         {

            pbox->update(this, BOX, pitem->m_strSample);

         }

         pgraphics->draw(pbox->m_rect, pbox->m_pimage);

      }

      if (m_iSel >= 0)
      {

         auto pitem = plistdata->element_at(m_iSel);

         if (pitem)
         {

            text_box* pbox = &pitem->m_box[BOX_SEL];

            if (!pbox->m_bInit)
            {

               update_extents(plistdata, pitem, pgraphics, BOX_SEL);

            }

            if (!pbox->m_bOk)
            {

               pbox->update(this, BOX_SEL, pitem->m_strSample);

            }

            pgraphics->draw(pbox->m_rect, pbox->m_pimage);

         }

      }

      if (m_iHover >= 0 && m_iHover != m_iSel)
      {

         auto pitem = plistdata->element_at(m_iHover);

         if (pitem)
         {

            text_box* pbox = &pitem->m_box[BOX_HOVER];

            if (!pbox->m_bInit)
            {

               update_extents(plistdata, pitem, pgraphics, BOX_HOVER);

            }

            if (!pbox->m_bOk)
            {

               pbox->update(this, BOX_HOVER, pitem->m_strSample);

            }

            pgraphics->draw(pbox->m_rect, pbox->m_pimage);

         }

      }

   }


   void font_list::_001OnDrawSingleColumn(::draw2d::graphics_pointer & pgraphics)
   {

      sync_lock sl(mutex());

      pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

      auto plistdata = m_plistdata;

      ::rect rectClient = pgraphics->m_puserinteraction->get_client_rect();

      rectClient += pgraphics->m_puserinteraction->get_viewport_offset();

      auto psession = Session;

      auto pointCursor = psession->get_cursor_pos();

      pgraphics->m_puserinteraction->_001ScreenToClient(pointCursor);

      pointCursor += pgraphics->m_puserinteraction->get_viewport_offset();

      bool bCheckHover = true;

      bool bIntersected = false;

      for (int i = 0; i < plistdata->get_count(); i++)
      {

         if (plistdata->element_at(i) == nullptr)
         {

            continue;

         }

         int iBox;

         iBox = BOX;

         auto plistdata = m_plistdata;

         text_box * pbox = &plistdata->element_at(i)->m_box[iBox];

         rect rect = pbox->m_rect;

         rect.right = rect.left + m_size.cx;

         if (!pbox->m_bOk)
         {

            pbox->update(this, iBox, plistdata->element_at(i)->m_strSample);

         }

         if (!rectClient.intersects(rect))
         {

            if (bIntersected)
            {

               break;

            }

            continue;

         }

         if (bCheckHover && rect.contains_y(pointCursor.y))
         {

            pgraphics->m_puserinteraction->m_itemHover = __new(::user::item({ ::user::element_item, i }));

            m_iHover = i;

            bCheckHover = false;

         }

         bIntersected = true;

         if (i == m_iSel)
         {

            if (!bCheckHover && i == m_iHover)
            {

               pgraphics->fill_rect(rect, pgraphics->m_puserinteraction->get_color(pgraphics->m_puserstyle, ::user::element_background, ::user::e_state_selected | ::user::e_state_hover));

            }
            else
            {

               pgraphics->fill_rect(rect, pgraphics->m_puserinteraction->get_color(pgraphics->m_puserstyle, ::user::element_background, ::user::e_state_selected));

            }

         }
         else if (!bCheckHover && i == m_iHover)
         {

            color32_t cr = pgraphics->m_puserinteraction->get_color(pgraphics->m_puserstyle, ::user::element_background, ::user::e_state_hover);

            int iA = colorref_get_a_value(cr);

            pgraphics->fill_rect(rect, cr);

         }

         pgraphics->draw(pbox->m_rect, pbox->m_pimage);

      }

   }


   void font_list::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      sync_lock sl(mutex());

      if (m_etype == type_wide)
      {

         _001OnDrawWide(pgraphics);

      }
      else
      {

         _001OnDrawSingleColumn(pgraphics);

      }

   }


   void font_list::update_extents(font_list_data * plistdata, font_list_item * pitem, ::draw2d::graphics_pointer & pgraphics, index iBox)
   {

      text_box* pbox = &pitem->m_box[iBox];

      sync_lock sl(mutex());

      if (::is_null(pbox))
      {

         return;

      }

      if (!pbox->m_bInit)
      {

         sl.unlock();

         ::sized s;

         string strText = m_strTextLayout;

         string str = pitem->m_strName;

         pbox->m_pfont.create(this);

         if (str.compare_ci("GOUDY STOUT") == 0)
         {

            output_debug_string("test05");

         }

         pbox->m_pfont->create_pixel_font(str, plistdata->m_iaSize[iBox]);

         pgraphics->set(pbox->m_pfont);

         pbox->m_pfont->m_echarseta = pitem->m_echarseta;

         if (iBox == 0)
         {

            strText = m_strTextLayout;

            if (strText.is_empty() ||
               (pbox->m_pfont->get_char_set(pgraphics) != ::char_set_ansi
                  && pbox->m_pfont->get_char_set(pgraphics) != ::char_set_default))
            {

               strText = ::draw2d::font::get_sample_text(pbox->m_pfont->m_echarset);

               if (strText.is_empty())
               {

                  strText = pitem->m_strName;

               }

            }

            if (strText.has_char())
            {

               s = pgraphics->GetTextExtent(strText);

            }

            if (strText.has_char() && s.area() <= 0)
            {

               string strSample;

               int maxarea = 0;

               ::e_char_set echarsetFound = pbox->m_pfont->get_char_set(pgraphics);

               size sSample;

               if (maxarea <= 0)
               {

                  strSample = m_strTextLayout;

                  if (strSample.has_char())
                  {

                     sSample = pgraphics->GetTextExtent(strSample);

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

                     sSample = pgraphics->GetTextExtent(strSample);

                     if (sSample.area() > maxarea)
                     {

                        maxarea = (int)(sSample.area());

                        strText = strSample;

                        s = sSample;

                     }

                  }

               }

               pbox->m_pfont->m_echarset = echarsetFound;

            }

            pitem->m_strSample = strText;

         }
         else
         {

            pbox->m_pfont->m_echarset = pitem->m_box[0].m_pfont->m_echarset;

            s = pgraphics->GetTextExtent(pitem->m_strSample);

         }

         s.cx += m_rectMargin.left + m_rectMargin.right;

         s.cy += m_rectMargin.top + m_rectMargin.bottom;

         pbox->m_size = s;

         pbox->m_bOk = false;

         pbox->m_bInit = true;

      }

   }


   void font_list::set_need_layout()
   {

      if (m_puserinteraction)
      {

         m_puserinteraction->set_need_layout();

      }

      set_need_redraw();

   }


   void font_list::set_need_redraw()
   {
      
      if (::is_null(m_puserinteraction))
      {

         return;

      }

      m_puserinteraction->set_need_redraw();

      m_puserinteraction->post_redraw();

   }


   ::estatus font_list::initialize(::layered* pobjectContext)
   {

      auto estatus = ::object::initialize(pobjectContext);

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }

   void font_list::on_subject(::promise::subject * psubject)
   {

      if (psubject->m_esubject == e_subject_prepare)
      {

         e_id eid = (e_id)psubject->id().i64();

         if (eid == id_font_extents)
         {

            update_extents();

         }
         else if (eid == id_font_list_layout)
         {

            layout();

         }
         else if (eid == id_font_list_total_size)
         {

            set_need_layout();

         }
         else if (eid == id_font_list_redraw)
         {

            set_need_redraw();

         }

      }

   }



   void font_list::on_subject(::promise::subject * psubject, ::promise::context * pcontext)
   {

      e_id eid = (e_id)psubject->id().i64();

      if (eid == id_font_enumeration)
      {

         sync_font_enumeration(psubject);

         if (!m_rectClient.is_empty())
         {

            psubject->set_modified();

         }

      }
      //else if (eid == id_font_extents)
      //{

      //   update_extents();

      //}
      //else if (eid == id_font_list_layout)
      //{

      //   layout();

      //}
      //else if (eid == id_font_list_total_size)
      //{

      //   set_need_layout();

      //}
      //else if (eid == id_font_list_redraw)
      //{

      //   set_need_redraw();

      //}

   }

   
   void font_list::set_font_list_type(enum_type etype)
   {

      m_etype = etype;

      if (!m_bUpdatesHooked)
      {

         m_bUpdatesHooked = true;

         System.delivery_for(id_font_enumeration, this, true);

         delivery_for(id_font_extents, this, true);

         delivery_for(id_font_list_layout, this, true);

         delivery_for(id_font_list_total_size, this, true);

      }
      else
      {

         set_modified(id_font_extents);

      }

   }


   font_list::enum_type font_list::get_font_list_type() const
   {

      return m_etype;

   }


   void font_list::update_extents()
   {

      sync_lock sl(mutex());

      if (!m_pitema)
      {

         return;

      }

      if (m_etype != type_single_column && !m_rectClient)
      {

         return;

      }

      if (m_rectClient.is_empty())
      {

         return;

      }

      int iBaseSize;

      if (m_etype == type_wide)
      {

         int iBaseHeight = max(250, m_rectClient.height());

         iBaseHeight = iBaseHeight + 250;

         int iStep = 200;

         int iDiv = 10;

         iBaseSize = ((iBaseHeight / iStep) * iStep) / iDiv;

      }
      else
      {

         iBaseSize = 18;

      }

      auto plistdata = m_plistdata;

      if (plistdata.is_set() &&
            plistdata->m_iUpdateId == m_pfontenumeration->m_iUpdateId
            && (m_etype == type_single_column ||
               plistdata->m_rectClient == m_rectClient))
      {

         set_modified(id_font_list_layout);

         return;

      }

      bool bSameSize = false;

      if (plistdata.is_set() && iBaseSize == plistdata->m_iBaseSize)
      {

         if (plistdata->m_iUpdateId == m_pfontenumeration->m_iUpdateId)
         {

            set_modified(id_font_list_layout);

            return;

         }

         bSameSize = true;

      }

      int_array iaSize;

      if (m_etype == type_wide)
      {

         iaSize.add(iBaseSize * 16 / 40);

         iaSize.add(iBaseSize * 24 / 40);

         iaSize.add(iBaseSize * 32 / 40);

      }
      else
      {

         iaSize.add(18);

      }

      if (plistdata.is_set() && iaSize == plistdata->m_iaSize
         && plistdata->m_iUpdateId == m_pfontenumeration->m_iUpdateId)
      {

         set_modified(id_font_list_layout);

         return;

      }
      else
      {

         bSameSize = false;

      }

      if (plistdata == nullptr)
      {

         plistdata = __new(font_list_data);

         plistdata->m_iSerial = 0;

         m_plistdata = plistdata;

         plistdata->set_size(m_pitema->get_count());

      }
      else
      {

         // Remove absent/removed fonts

         __pointer(font_list_item) pitem;

         sync_lock sl(mutex());

         for (index iItem = 0; iItem < plistdata->get_count(); )
         {

            auto pitem = plistdata->element_at(iItem);

            if (pitem && pitem->m_strName.has_char() && !m_pfontenumeration->has_font_name(pitem->m_strName))
            {

               plistdata->remove_at(iItem);

            }
            else
            {

               iItem++;

            }

         }

         // Make room for new fonts

         for (index iItem = 0; iItem < m_pitema->get_count(); iItem++)
         {

            auto pitem = plistdata->element_at(iItem);

            if (pitem && pitem->m_strName.has_char() && pitem->m_strName != m_pitema->ptr_at(iItem)->m_strName)
            {

               __pointer(font_list_item) pitemNewEmpty;

               plistdata->insert_at(iItem, pitemNewEmpty);

            }

         }

         ASSERT(plistdata->get_size() == m_pitema->get_count());

         plistdata->m_iSerial++;

      }

      plistdata->m_rectClient = m_rectClient;

      plistdata->m_iUpdateId = m_pfontenumeration->m_iUpdateId;

      plistdata->m_iUpdatedCount = 0;

      plistdata->m_iBaseSize = iBaseSize;

      plistdata->m_iaSize = iaSize;

      plistdata->m_bLayoutStillIntersect = true;

      m_iLayoutSerial = 0;

      sl.unlock();

      auto iFontCount = plistdata->get_count();

      auto pcounter = fork_count(this, plistdata->get_count(), [this, plistdata, bSameSize](index iOrder, index iStart, index iCount, index iScan)
      {

         ::draw2d::graphics_pointer g(e_create);

         g->CreateCompatibleDC(nullptr);

         ::draw2d::graphics_pointer & pgraphics = g;

      restart:

         index iSerial = plistdata->m_iSerial;

         string strText = m_strTextLayout;

         size s;

         ::rect rect;

         __pointer(font_list_item) pitem;

         for (index iItem = iStart; iItem < plistdata->get_count(); iItem += iScan)
         {

            {

               sync_lock sl(mutex());

               if (plistdata->m_iSerial != iSerial)
               {

                  goto restart;

               }

               if (iItem >= m_pitema->get_count())
               {

                  break;

               }

            }

            {

               sync_lock sl(mutex());

               pitem = plistdata->element_at(iItem);

            }

            bool bNew = false;

            if (!pitem || pitem->m_strFont.is_empty())
            {

               bNew = true;

               pitem = __new(font_list_item());

               pitem->m_iItem = iItem;

               pitem->m_strFont = m_pitema->ptr_at(iItem)->m_strName;

               pitem->m_strName = m_pitema->ptr_at(iItem)->m_strName;

               pitem->m_echarseta = m_pitema->ptr_at(iItem)->m_echarseta;

            }
            else if (pitem->m_strFont != m_pitema->ptr_at(iItem)->m_strFile)
            {

               TRACE("what?!?!");

               continue;

            }

            if (bNew || !bSameSize)
            {

               update_extents(plistdata, pitem, pgraphics, 0);

            }

            {

               sync_lock sl(mutex());

               if (plistdata->m_iSerial != iSerial)
               {

                  goto restart;

               }

               plistdata->element_at(iItem) = pitem;

               if (!m_bLayoutWideStillIntersect)
               {

                  continue;

               }

            }

         }

      });

      if (pcounter->lock(30_s))
      {

         {

            sync_lock sl(mutex());

            if (plistdata != m_plistdata)
            {

               return;

            }

            set_modified(id_font_list_layout);

         }

         pcounter = fork_count(this, plistdata->get_count(), [this, plistdata](index iOrder, index iStart, index iCount, index iScan)
         {

            auto iSerial = plistdata->m_iSerial;

            ::draw2d::graphics_pointer g(e_create);

            g->CreateCompatibleDC(nullptr);

            ::draw2d::graphics_pointer & pgraphics = g;

            string strText = m_strTextLayout;

            size s;

            ::rect rect;

            for (index i = iStart; i < iCount && ::thread_get_run(); i += iScan)
            {

               auto pitem = plistdata->element_at(i);

               for (index iBox = 1; iBox < plistdata->m_iaSize.get_count(); iBox++)
               {

                  if (plistdata->m_iSerial != iSerial)
                  {

                     return;

                  }

                  update_extents(plistdata, pitem, pgraphics, iBox);

               }

            }

         });

         if (pcounter->lock(30_s))
         {

            {

               sync_lock sl(mutex());

               if (plistdata != m_plistdata)
               {

                  return;

               }

               set_modified(id_font_list_layout);

            }

         }

      }

   }


   void font_list::layout()
   {

      sync_lock sl(mutex());

      ::size sizeTotal;

      if (m_etype == type_wide)
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

         set_modified(id_font_list_total_size);

      }

   }


   ::size font_list::layout_wide()
   {

      if (::is_null(m_puserinteraction))
      {

         return ::size();

      }

      TRACE("font_list::layout_wide");

      sync_lock sl(mutex());

      ::size sizeTotal;

      bool bIntersected = false;

      m_bLayoutWideStillIntersect = true;

      string strText = m_strTextLayout;

      size s;

      int iMargin = 40;

      int w = m_rectClient.width() - iMargin * 2;

      int iPadding = 15;

      int x = iMargin;

      int y = iMargin + iPadding;

      int h = 0;

      int hExtra = 0;

      int nextx;

      sizeTotal.cx = m_rectClient.width();

      ::rect rectClient = m_puserinteraction->get_client_rect();

      rectClient += m_puserinteraction->get_viewport_offset();

      auto plistdata = m_plistdata;

      if (plistdata.is_null())
      {

         return sizeTotal;

      }

      int iLineStart = 0;

      auto iFontCount = plistdata->get_count();

      for (int i = 0; i < iFontCount; i++)
      {

         font_list_item * pitem = plistdata->element_at(i);

         if (pitem
            && !m_pfontenumeration->has_font_name(pitem->m_strFont)
            && !m_pfontenumeration->has_font_name(pitem->m_strName))
         {

            //plistdata->remove_at(i);

            //iFontCount = plistdata->get_count();

            //i--;

            continue;

         }

         if (pitem == nullptr)
         {

            sizeTotal.cy = y + hExtra;

            return sizeTotal;

         }

         size & s = pitem->m_box[0].m_size;

         rect & rect = pitem->m_box[0].m_rect;

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

                  font_list_item * pitem2 = plistdata->element_at(j);

                  ::rect & rect2 = pitem2->m_box[0].m_rect;

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

         //pgraphics->text_out(x + m_rectMargin.left,y + m_rectMargin.top,strText);

         rect.left = x;

         rect.top = y;

         rect.right = rect.left + s.cx;

         rect.bottom = rect.top + s.cy;

         if (rect.intersects(rectClient))
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

         h = max(h, s.cy);

         hExtra = max(hExtra, s.cy);

      }

      for (int i = 0; i < iFontCount; i++)
      {

         font_list_item * pitem = plistdata->element_at(i);

         size & s = pitem->m_box[0].m_size;

         rect & rect = pitem->m_box[0].m_rect;

         for (index j = 1; j < 3; j++)
         {

            auto & size2 = pitem->m_box[j].m_size;
            auto & rect2 = pitem->m_box[j].m_rect;

            int dw = (size2.cx - s.cx) / 2;
            int dh = (size2.cy - s.cy) / 2;

            int x = m_rectClient.center_x() - rect.center_x();

            if (x > 0)
            {

               x = m_rectClient.center_x() - rect.left;

            }
            else
            {

               x = m_rectClient.center_x() - rect.right;

            }

            x = x * (m_rectClient.width() + iPadding * 2) / w;

            if (x > 0)
            {
               rect2.left = m_rectClient.center_x() - x;
               rect2.right = rect2.left + size2.cx;
            }
            else
            {
               rect2.right = m_rectClient.center_x()- x;
               rect2.left = rect2.right - size2.cx;
            }
            rect2.top = rect.top - dh;
            rect2.bottom = rect2.top + size2.cy;

            hExtra = max(hExtra, size2.cy);

         }

      }

      sizeTotal.cy = y + hExtra + 5;

      return sizeTotal;

   }


   ::size font_list::layout_single_column()
   {

      sync_lock sl(mutex());

      ::size sizeTotal;

      string strText = m_strTextLayout;

      size s;

      int h = 0;

      sizeTotal.cx = 0;

      int xSingleColumn = 0;
      int ySingleColumn = 0;

      auto plistdata = m_plistdata;

      for (int i = 0; i < plistdata->get_count(); i++)
      {

         font_list_item * pitem = plistdata->element_at(i);

         if (pitem == nullptr)
         {

            sizeTotal.cy = ySingleColumn;

            return sizeTotal;

         }

         size & s = pitem->m_box[0].m_size;

         rect & rect = pitem->m_box[0].m_rect;



         pitem->m_box[0].m_rect.left = xSingleColumn;
         pitem->m_box[0].m_rect.top = ySingleColumn;
         pitem->m_box[0].m_rect.right = xSingleColumn + s.cx;
         pitem->m_box[0].m_rect.bottom = ySingleColumn + s.cy;

         sizeTotal.cx = max(m_size.cx, pitem->m_box[0].m_rect.right + 4);

         ySingleColumn += s.cy;

         h = max(h, s.cy);

      }

      sizeTotal.cy = ySingleColumn;

      return sizeTotal;

   }



   ::user::item font_list::hit_test(const ::point& point)
   {

      sync_lock sl(mutex());

      if (m_etype == type_wide)
      {

         return hit_test_wide(point);

      }
      else
      {

         return hit_test_single_column(point);

      }

   }


   ::user::item font_list::hit_test_wide(const ::point & point)
   {

      sync_lock sl(mutex());

      auto plistdata = m_plistdata;

      if (!plistdata)
      {

         return ::user::element_none;

      }

      if (m_iHover >= 0)
      {

         if (plistdata->element_at(m_iHover)->m_box[BOX_HOVER].m_rect.contains(point))
         {

            return ::user::item(::user::element_item, m_iHover);

         }

      }

      for (::index iItem = 0; iItem < plistdata->get_size(); iItem++)
      {

         if (plistdata->element_at(iItem) == nullptr)
         {

            continue;

         }

         if (plistdata->element_at(iItem)->m_box[BOX].m_rect.contains(point))
         {

            return ::user::item(::user::element_item, iItem);

         }

      }

      return ::user::element_none;

   }


   ::user::item font_list::hit_test_single_column(const ::point & point)
   {

      sync_lock sl(mutex());

      auto plistdata = m_plistdata;

      if (!plistdata)
      {

         return ::user::element_none;

      }

      for (index iItem = 0; iItem < plistdata->get_size(); iItem++)
      {

         if (plistdata->element_at(iItem) == nullptr)
         {

            continue;

         }

         rect rect(plistdata->element_at(iItem)->m_box[BOX].m_rect);

         rect.right = rect.left + m_size.cx;

         if (rect.contains(point))
         {

            return { ::user::element_item, iItem };

         }

      }

      return ::user::element_none;

   }


   bool font_list::get_box_rect(LPRECT32 lprect, ::index i)
   {

      sync_lock sl(mutex());

      if (m_etype == type_wide)
      {

         return get_box_rect_wide(lprect, i);

      }
      else
      {

         return get_box_rect_single_column(lprect, i);

      }

   }


   bool font_list::get_box_rect_wide(LPRECT32 lprect, ::index i)
   {

      sync_lock sl(mutex());

      auto plistdata = m_plistdata;

      if (!plistdata)
      {

         return false;

      }

      if (i < 0 || i >= plistdata->get_size())
      {

         return false;

      }

      if (plistdata->element_at(i) == nullptr)
      {

         return false;

      }

      *lprect = plistdata->element_at(i)->m_box[BOX].m_rect;

      return true;

   }


   bool font_list::get_box_rect_single_column(LPRECT32 lprect, ::index i)
   {

      sync_lock sl(mutex());

      auto plistdata = m_plistdata;

      if (!plistdata)
      {

         return false;

      }

      if (i < 0 || i >= plistdata->get_size())
      {

         return false;

      }

      if (plistdata->element_at(i) == nullptr)
      {

         return false;

      }

      *lprect = plistdata->element_at(i)->m_box[BOX].m_rect;

      lprect->right = lprect->left + m_size.cx;

      return true;

   }


   void font_list::set_client_rect(LPCRECT32 lpcrect)
   {

      ::rect rect(lpcrect);

      if (rect != m_rectClient)
      {

         ::size sizeOld(m_rectClient.size());

         ::size sizeNew(rect.size());

         m_rectClient = *lpcrect;

         if (sizeOld != sizeNew)
         {

            set_modified(id_font_extents);

         }

      }

   }


   index font_list::find_name(string str)
   {

      sync_lock sl(mutex());

      auto plistdata = m_plistdata;

      if (plistdata.is_null())
      {

         return -1;

      }

      for (index i = 0; i < plistdata->get_size(); i++)
      {

         if (m_pitema->element_at(i) == nullptr)
         {

            continue;

         }

         if(m_pitema->element_at(i)->m_strName.compare_ci(str) == 0)
         {

            return i;

         }

      }

      return -1;


   }


   //void font_list::update()
   //{

   //   m_bUpdating = true;

   //   try
   //   {

   //      //update_font_enumeration();
   //      sync_font_enumeration();



   //      update_extents();

   //   }
   //   catch (...)
   //   {

   //   }

   //   set_need_layout();

   //   //try
   //   //{

   //   //   m_puserinteraction->set_need_layout();

   //   //   m_puserinteraction->set_need_redraw();

   //   //   m_puserinteraction->post_redraw();

   //   //}
   //   //catch (...)
   //   //{

   //   //}

   //   m_bUpdating = false;

   //}


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

      return m_bUpdating;

   }


} // namespace user



