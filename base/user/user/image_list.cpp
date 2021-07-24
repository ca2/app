#include "framework.h"
#include "base/user/user/_user.h"
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

      //m_scrolldataVertical.m_bScrollEnable = true;

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

      synchronous_lock synchronouslock(mutex());

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

      return string(get_current_image()->extension()->payload("read_only_link"));

   }


   void image_list::install_message_routing(::channel * pchannel)
   {

      ::user::box::install_message_routing(pchannel);

      install_click_default_mouse_handling(pchannel);

      MESSAGE_LINK(e_message_create, pchannel, this, &image_list::on_message_create);
      MESSAGE_LINK(e_message_destroy, pchannel, this, &image_list::on_message_destroy);

   }


   bool image_list::on_click(const ::user::item & item)
   {

      index_array iaSel = m_iaSel;

      auto psession = get_session();

      if (!psession->is_key_pressed(::user::e_key_control) || !m_bMultiSel)
      {

         iaSel.erase_all();

      }

      if (psession->is_key_pressed(::user::e_key_shift) && m_bMultiSel)
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

      event.m_eevent    = ::user::e_event_image_list_action;

      event.m_item      = item;

      event.m_puserinteraction      = this;

      event.m_id        = m_id;

      on_control_event(&event);

      _001SetSelection(iaSel, ::e_source_user);

      m_itemCurrent     = item;

      return true;

   }



   void image_list::on_message_create(::message::message * pmessage)
   {

      __pointer(::message::create) pcreate(pmessage);

      pcreate->previous();

      if (pcreate->m_bRet)
         return;


   }


   void image_list::on_message_destroy(::message::message * pmessage)
   {

   }


   bool image_list::get_rect(::user::item & item)
   {

      if (item == ::user::e_element_item)
      {

         if (!item.is_valid_item(m_imagea.get_count()))
         {

            return false;

         }

         int pad = m_iPad;

         int text_height = m_bNoName ? 0 : m_iTextHeight;

         int xpad = m_iPad;

         auto rectangleClient = get_client_rect();

         int cx = rectangleClient.width();

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

         item.m_rectangle.left = x;

         item.m_rectangle.right = x + w;

         item.m_rectangle.top = y;

         item.m_rectangle.bottom = y + h + text_height;

         return true;

      }
      else if (item == ::user::e_element_icon)
      {

         {

            __stack(item.m_eelement, e_element_item);

            if (!get_rect(item))
            {

               return false;

            }

         }

         if (!m_bNoName)
         {

            item.m_rectangle.bottom -= m_iTextHeight;

         }

         return true;

      }
      else if (item == ::user::e_element_text)
      {

         if (m_bNoName)
         {

            return false;

         }

         {

            __stack(item.m_eelement, e_element_item);

            if (!get_rect(item))
            {

               return false;

            }

         }

         item.m_rectangle.top += m_size.cy;

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

            if (item.m_rectangle.contains(item.m_pointHitTest))
            {

               return;

            }

         }

      }

      item = -1;

      item = ::user::e_element_none;

   }


   void image_list::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      ::rectangle_i32 rectangle;

      auto pstyle = get_style(pgraphics);

      auto rectangleClient = get_client_rect();

      pgraphics->set(get_font(pstyle));

      rectangleClient.offset(m_pointScroll);

      pgraphics->fill_rectangle(rectangleClient, get_color(pstyle, e_element_background));

      pgraphics->draw_rectangle(rectangleClient, argb(255, 192, 192, 192));

      pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

      ::count cCount = m_imagea.get_count();

      for (::user::item item = 0; item.m_iItem < cCount; item.m_iItem++)
      {

         ::user::item itemText;

         ::rectangle_i32 rectSel;

         itemText = e_element_text;

         bool bRectText = get_rect(itemText);

         item = e_element_icon;

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

                  ::rectangle_i32 rectImage;

                  double dW = (double)rectangle.width() / (double)pimageSrc->width();

                  double dH = (double)rectangle.height() / (double)pimageSrc->height();

                  double dMin = minimum(dW, dH);

                  ::size_i32 szNew = pimageSrc->get_size() * dMin;

                  pimage = create_image(szNew);

                  pimage->g()->set_interpolation_mode(::draw2d::e_interpolation_mode_high_quality_bicubic);

                  pimage->g()->stretch(::rectangle_i32(szNew), pimageSrc->get_graphics(),pimageSrc->rectangle());

               }

               ::rectangle_i32 rectImage;

               rectImage.left = rectangle.left + (rectangle.width() - pimage->width()) / 2;

               rectImage.top = rectangle.top + (rectangle.height() - pimage->height()) / 2;

               rectImage.right = rectImage.left + pimage->width();

               rectImage.bottom = rectImage.top + pimage->height();

               rectSel = rectImage;

               if (!m_bNoName)
               {

                  rectSel.bottom = itemText.m_rectangle.bottom;

               }

               rectSel.inflate(5, 5);

               ::color::color crBorder = 0;

               ::color::color crSel = 0;

               bool bSel;

               bool bHover;

               if (m_iaSel.contains(item))
               {

                  bSel = true;

                  if (m_itemHover == item)
                  {

                     crBorder = argb(255, 100, 180, 240);

                     crSel = argb(108, 100, 180, 240);

                     bHover = true;

                  }
                  else
                  {

                     crBorder = argb(255, 80, 140, 200);

                     crSel = argb(108, 80, 140, 200);

                     bHover = false;

                  }

               }
               else
               {

                  bSel = false;

                  if (m_itemHover == item)
                  {

                     crBorder = argb(255, 80, 130, 180);

                     crSel = argb(108, 80, 130, 180);

                     bHover = true;

                  }
                  else
                  {

                     crBorder = argb(255, 100, 100, 100);

                     bHover = false;

                  }

               }

               if (bSel || bHover)
               {

                  pgraphics->fill_rectangle(rectSel, crSel);

               }

               pgraphics->stretch(rectImage, pimage->g());

               if (bSel)
               {


                  rectImage.inflate(1, 1);

                  pgraphics->draw_rectangle(rectSel, crBorder);

                  rectImage.inflate(1, 1);

                  pgraphics->draw_rectangle(rectSel, crBorder);

               }

            }

         }

         if (bRectText)
         {

            string str;

            if (_001GetItemText(str, item))
            {

               pgraphics->set_text_color(get_color(pstyle, e_element_text));

               pgraphics->draw_text(str, itemText.m_rectangle, e_align_center);

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

      ::rectangle_i32 rectangleClient;

      ::rectangle_i32 rectTotal(0, 0, 0, 0);

      ::size_i32 sizeImage;

      for (index i = 0; i < m_imagea.get_count(); i++)
      {

         ::user::item item(e_element_item, i);

         if (get_rect(item))
         {

            if (i == 0)
            {

               sizeImage = item.m_rectangle;

            }

            rectTotal.unite(rectTotal, item.m_rectangle);

         }

      }

      if (m_sizeImage != sizeImage)
      {

         m_sizeImage = sizeImage;

         //m_iWheelDeltaScroll = (i16) (sizeImage.cy / 3);

         m_imageaThumb.erase_all();

      }

      rectTotal.left = 0;

      rectTotal.top = 0;

      rectTotal.bottom += m_iPad;

      //m_sizeTotal = rectTotal.size();

      //m_scrolldataVertical.m_iPage = rectangleClient.height();

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

      MESSAGE_LINK(e_message_create, pchannel, this, &image_list_view::on_message_create);
      MESSAGE_LINK(e_message_destroy, pchannel, this, &image_list_view::on_message_destroy);

   }


   void image_list_view::on_message_create(::message::message * pmessage)
   {

      __pointer(::message::create) pcreate(pmessage);

      pcreate->previous();

   }


   void image_list_view::on_message_destroy(::message::message * pmessage)
   {

   }


   void image_list_view::on_subject(::subject::subject * psubject, ::subject::context * pcontext)
   {

      ::user::impact::on_subject(psubject, pcontext);

      if (psubject->id() == id_after_change_text)
      {

         __throw(todo, "core");
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

      synchronous_lock synchronouslock(mutex());

      if (m_iaSel.get_count() == 1)
      {

         return m_iaSel[0];

      }

      return -1;

   }


   index_array image_list::_001GetSelection()
   {

      synchronous_lock synchronouslock(mutex());

      return m_iaSel;

   }


   void image_list::set_current_item(index iFind, const ::action_context & context)
   {

      synchronous_lock synchronouslock(mutex());

      m_iaSel.erase_all();

      m_iaSel.add(iFind);

   }


   void image_list::_001SetSelection(const index_array & ia, const ::action_context & context)
   {

      synchronous_lock synchronouslock(mutex());

      if (!::papaya::array::equals_non_unique_unordered(ia, m_iaSel))
      {

         m_iaSel = ia;

         ::user::control_event ev;

         ev.m_puserinteraction = this;

         ev.m_id = m_id;

         ev.m_item = current_item();

         ev.m_eevent = ::user::e_event_after_change_cur_sel;

         on_control_event(&ev);

      }

   }


} // namespace user



