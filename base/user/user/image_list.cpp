#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "base/user/user/_user.h"
#endif
#include "aura/update.h"
#include "image_list.h"


namespace user
{


   image_list::image_list()
   {

      m_sizeImage.set(0, 0);

      m_iTextHeight = 30;
      m_bMultiSel = true;
      m_size.cx = 128;
      m_size.cy = 128;

      m_bNoName = false;
      m_iPad = 10;
      m_ealign = e_align_top_left;

      //m_scrolldataVert.m_bScrollEnable = true;

   }


   image_list::~image_list()
   {

   }


   bool image_list::update_data(bool bSaveAndValidate)
   {

      if (bSaveAndValidate)
      {

      }
      else
      {

         set_need_layout();

         set_need_redraw();

      }

      return true;

   }


   void image_list::assert_valid() const
   {

      ::user::box::assert_valid();

   }


   void image_list::dump(dump_context & dumpcontext) const
   {

      ::user::box::dump(dumpcontext);

   }


   ::image * image_list::get_current_image()
   {

      sync_lock sl(mutex());

      if (m_iaSel.get_count() != 1)
      {

         return nullptr;

      }

      return m_imagea[m_iaSel[0]];

   }


   string image_list::get_current_image_link()
   {

      if (!get_current_image())
      {

         return "";

      }

      return get_current_image()->extension()->value("read_only_link");

   }


   void image_list::install_message_routing(::channel * pchannel)
   {

      ::user::box::install_message_routing(pchannel);

      install_simple_ui_default_mouse_handling(pchannel);

      MESSAGE_LINK(e_message_create, pchannel, this, &image_list::_001OnCreate);
      MESSAGE_LINK(e_message_destroy, pchannel, this, &image_list::_001OnDestroy);

   }


   bool image_list::on_click(const ::user::item & item)
   {

      index_array iaSel = m_iaSel;

      auto psession = Session;

      if (!psession->is_key_pressed(::user::key_control) || !m_bMultiSel)
      {

         iaSel.remove_all();

      }

      if (psession->is_key_pressed(::user::key_shift) && m_bMultiSel)
      {

         if (m_itemCurrent.is_set())
         {

            for (index i = m_itemCurrent; i <= item.m_iItem; i++)
            {

               iaSel.add_unique(i);

            }

         }

      }
      else
      {

         iaSel.add_unique(item);

      }

      ::user::control_event event;

      event.m_eevent    = ::user::event_image_list_action;

      event.m_item      = item;

      event.m_puie      = this;

      event.m_id        = m_id;

      on_control_event(&event);

      _001SetSelection(iaSel, ::source_user);

      m_itemCurrent     = item;

      return true;

   }



   void image_list::_001OnCreate(::message::message * pmessage)
   {

      SCAST_PTR(::message::create, pcreate, pmessage);

      pcreate->previous();

      if (pcreate->m_bRet)
         return;


   }


   void image_list::_001OnDestroy(::message::message * pmessage)
   {

   }


   bool image_list::get_rect(::user::item & item)
   {

      if (item == ::user::element_item)
      {

         if (!item.is_valid_item(m_imagea.get_count()))
         {

            return false;

         }

         int pad = m_iPad;

         int text_height = m_bNoName ? 0 : m_iTextHeight;

         int xpad = m_iPad;

         auto rectClient = get_client_rect();

         int cx = rectClient.width();

         int w = m_size.cx;

         int h = m_size.cy;

         int iColCount = (cx - xpad) / (w + xpad);

         int cxInternal = iColCount * (w + xpad) - xpad;

         int xLeft;

         if (m_ealign & e_align_horizontal_center)
         {

            xLeft = (cx - cxInternal) / 2;

         }
         else
         {

            xLeft = xpad;

         }

         int x = xLeft;

         int y = pad;

         for (index pos = 0; pos < item.m_iItem; pos++)
         {

            if (x + w + pad + w + pad >= cx)
            {

               x = xLeft;

               y += h + pad + text_height;

            }
            else
            {

               x += w + pad;

            }

         }

         item.m_rect.left = x;

         item.m_rect.right = x + w;

         item.m_rect.top = y;

         item.m_rect.bottom = y + h + text_height;

         return true;

      }
      else if (item == ::user::element_icon)
      {

         {

            __stack(item.m_eelement, element_item);

            if (!get_rect(item))
            {

               return false;

            }

         }

         if (!m_bNoName)
         {

            item.m_rect.bottom -= m_iTextHeight;

         }

         return true;

      }
      else if (item == ::user::element_text)
      {

         if (m_bNoName)
         {

            return false;

         }

         {

            __stack(item.m_eelement, element_item);

            if (!get_rect(item))
            {

               return false;

            }

         }

         item.m_rect.top += m_size.cy;

         return true;

      }

      return false;

   }


   void image_list::on_hit_test(::user::item& item)
   {

      ::count c = m_imagea.get_count();

      for (index i = 0; i < c; i++)
      {

         item = i;

         if (get_rect(item))
         {

            if (item.m_rect.contains(item.m_pointHitTest))
            {

               return;

            }

         }

      }

      item = -1;

      item = ::user::element_none;

   }


   void image_list::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      ::rect rect;

      auto pstyle = get_style(pgraphics);

      auto rectClient = get_client_rect();

      pgraphics->set(get_font(pstyle));

      rectClient.offset(m_pointScroll);

      pgraphics->fill_rect(rectClient, get_color(pstyle, element_background));

      pgraphics->draw_rect(rectClient, ARGB(255, 192, 192, 192));

      pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

      ::count cCount = m_imagea.get_count();

      for (::user::item item = 0; item.m_iItem < cCount; item.m_iItem++)
      {

         ::user::item itemText;

         ::rect rectSel;

         itemText = element_text;

         bool bRectText = get_rect(itemText);

         item = element_icon;

         if (get_rect(item))
         {

            ::image_pointer pimageSrc = m_imagea[item];

            if (::is_ok(pimageSrc))
            {

               if (m_imageaThumb.get_size() < m_imagea.get_size())
               {

                  m_imageaThumb.set_size(m_imagea.get_size());

               }

               if (m_imageaThumb[item]->is_null())
               {

                  m_imageaThumb[item].create(this);

               }

               ::image_pointer pimage = m_imageaThumb[item];

               if (pimage->area() <= 0)
               {

                  ::rect rectImage;

                  double dW = (double)rect.width() / (double)pimageSrc->width();

                  double dH = (double)rect.height() / (double)pimageSrc->height();

                  double dMin = min(dW, dH);

                  ::size szNew = pimageSrc->get_size() * dMin;

                  pimage = create_image(szNew);

                  pimage->g()->set_interpolation_mode(::draw2d::e_interpolation_mode_high_quality_bicubic);

                  pimage->g()->stretch(::rect(szNew), pimageSrc->get_graphics(),pimageSrc->rect());

               }

               ::rect rectImage;

               rectImage.left = rect.left + (rect.width() - pimage->width()) / 2;

               rectImage.top = rect.top + (rect.height() - pimage->height()) / 2;

               rectImage.right = rectImage.left + pimage->width();

               rectImage.bottom = rectImage.top + pimage->height();

               rectSel = rectImage;

               if (!m_bNoName)
               {

                  rectSel.bottom = itemText.m_rect.bottom;

               }

               rectSel.inflate(5, 5);

               color32_t crBorder = 0;

               color32_t crSel = 0;

               bool bSel;

               bool bHover;

               if (m_iaSel.contains(item))
               {

                  bSel = true;

                  if (m_itemHover == item)
                  {

                     crBorder = ARGB(255, 100, 180, 240);

                     crSel = ARGB(108, 100, 180, 240);

                     bHover = true;

                  }
                  else
                  {

                     crBorder = ARGB(255, 80, 140, 200);

                     crSel = ARGB(108, 80, 140, 200);

                     bHover = false;

                  }

               }
               else
               {

                  bSel = false;

                  if (m_itemHover == item)
                  {

                     crBorder = ARGB(255, 80, 130, 180);

                     crSel = ARGB(108, 80, 130, 180);

                     bHover = true;

                  }
                  else
                  {

                     crBorder = ARGB(255, 100, 100, 100);

                     bHover = false;

                  }

               }

               if (bSel || bHover)
               {

                  pgraphics->fill_rect(rectSel, crSel);

               }

               pgraphics->stretch(rectImage, pimage->g());

               if (bSel)
               {


                  rectImage.inflate(1, 1);

                  pgraphics->draw_rect(rectSel, crBorder);

                  rectImage.inflate(1, 1);

                  pgraphics->draw_rect(rectSel, crBorder);

               }

            }

         }

         if (bRectText)
         {

            string str;

            if (_001GetItemText(str, item))
            {

               pgraphics->set_text_color(get_color(pstyle, element_text));

               pgraphics->draw_text(str, itemText.m_rect, e_align_center);

            }

         }

      }

   }


   bool image_list::_001GetItemText(string & str, index iItem)
   {

      return false;

   }


   void image_list::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

      ::rect rectClient;

      ::rect rectTotal(0, 0, 0, 0);

      ::size sizeImage;

      for (index i = 0; i < m_imagea.get_count(); i++)
      {

         ::user::item item(element_item, i);

         if (get_rect(item))
         {

            if (i == 0)
            {

               sizeImage = item.m_rect;

            }

            rectTotal.unite(rectTotal, item.m_rect);

         }

      }

      if (m_sizeImage != sizeImage)
      {

         m_sizeImage = sizeImage;

         //m_iWheelDeltaScroll = (i16) (sizeImage.cy / 3);

         m_imageaThumb.remove_all();

      }

      rectTotal.left = 0;

      rectTotal.top = 0;

      rectTotal.bottom += m_iPad;

      //m_sizeTotal = rectTotal.size();

      //m_scrolldataVert.m_iPage = rectClient.height();

      ::user::box::on_layout(pgraphics);


   }


   image_list_view::image_list_view()
   {

   }


   image_list_view::~image_list_view()
   {

   }


   void image_list_view::assert_valid() const
   {

      ::user::image_list::assert_valid();

   }


   void image_list_view::dump(dump_context & dumpcontext) const
   {

      ::user::image_list::dump(dumpcontext);

   }


   void image_list_view::install_message_routing(::channel * pchannel)
   {

      ::user::impact::install_message_routing(pchannel);
      ::user::image_list::install_message_routing(pchannel);

      MESSAGE_LINK(e_message_create, pchannel, this, &image_list_view::_001OnCreate);
      MESSAGE_LINK(e_message_destroy, pchannel, this, &image_list_view::_001OnDestroy);

   }


   void image_list_view::_001OnCreate(::message::message * pmessage)
   {

      SCAST_PTR(::message::create, pcreate, pmessage);

      pcreate->previous();

   }


   void image_list_view::_001OnDestroy(::message::message * pmessage)
   {

   }


   void image_list_view::on_subject(::promise::subject * psubject, ::promise::context * pcontext)
   {

      ::user::impact::on_subject(psubject, pcontext);

      if (psubject->id() == id_after_change_text)
      {

         __throw(todo("core"));
         //auto * peditview = _001TypedWindow < ::userex::top_edit_view >();

         //if (peditview != nullptr && psubject->m_puserinteraction == peditview)
         //{

         //   string strText;

         //   peditview->_001GetText(strText);

         //}

      }

   }


   ::user::item image_list::current_item()
   {

      sync_lock sl(mutex());

      if (m_iaSel.get_count() == 1)
      {

         return m_iaSel[0];

      }

      return -1;

   }


   index_array image_list::_001GetSelection()
   {

      sync_lock sl(mutex());

      return m_iaSel;

   }


   void image_list::set_current_item(index iFind, const ::action_context & context)
   {

      sync_lock sl(mutex());

      m_iaSel.remove_all();

      m_iaSel.add(iFind);

   }


   void image_list::_001SetSelection(const index_array & ia, const ::action_context & context)
   {

      sync_lock sl(mutex());

      if (!::papaya::array::equals_non_unique_unordered(ia, m_iaSel))
      {

         m_iaSel = ia;

         ::user::control_event ev;

         ev.m_puie = this;

         ev.m_id = m_id;

         ev.m_item = current_item();

         ev.m_eevent = ::user::event_after_change_cur_sel;

         on_control_event(&ev);

      }

   }


} // namespace user



