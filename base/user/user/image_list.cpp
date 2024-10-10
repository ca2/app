#include "framework.h"
#include "image_list.h"
#include "acme/constant/id.h"
#include "acme/constant/message.h"
#include "acme/constant/user_key.h"
#include "acme/handler/item.h"
#include "acme/handler/topic.h"
#include "acme/prototype/collection/_array.h"
#include "acme/user/user/content.h"
#include "aura/graphics/image/context.h"
#include "aura/graphics/image/drawing.h"
#include "aura/graphics/image/image.h"
#include "aura/graphics/image/array.h"
#include "aura/message/user.h"
#include "aura/platform/session.h"


namespace user
{


   image_list::image_list()
   {

      m_bDefaultClickHandling = true;
      m_bDefaultParentMouseMessageHandling = true;

      m_sizeImage.set(0, 0);

      m_iTextHeight = 30;
      m_bMultiSel = true;
      m_size.cx() = 128;
      m_size.cy() = 128;

      m_iMargin = 10;

      m_bLabel = true;
      m_iLabelHeight = 18;
      m_ealign = e_align_top_left;

      //m_pscrollstateVertical->m_bScrollEnable = true;

   }


   image_list::~image_list()
   {

   }


   void image_list::update_data(bool bSaveAndValidate)
   {

      if (bSaveAndValidate)
      {

      }
      else
      {

         set_need_layout();

         set_need_redraw();

      }

      //return true;

   }


//   void image_list::assert_ok() const
//   {
//
//      ::user::box::assert_ok();
//
//   }
//
//
//   void image_list::dump(dump_context & dumpcontext) const
//   {
//
//      ::user::box::dump(dumpcontext);
//
//   }


   ::image::image *image_list::get_current_image()
   {

      synchronous_lock synchronouslock(this->synchronization());

      if (m_iaSel.get_count() != 1)
      {

         return nullptr;

      }

      return m_pimagea->image_at(m_iaSel[0]);

   }


   string image_list::get_current_image_link()
   {

      if (!get_current_image())
      {

         return "";

      }

      return get_current_image()->extension()->payload("read_only_link").as_string();

   }


   void image_list::install_message_routing(::channel * pchannel)
   {

      ::user::scroll_base::install_message_routing(pchannel);

      //install_click_default_mouse_handling(pchannel);

      MESSAGE_LINK(MESSAGE_CREATE, pchannel, this, &image_list::on_message_create);
      MESSAGE_LINK(MESSAGE_DESTROY, pchannel, this, &image_list::on_message_destroy);

   }


   bool image_list::on_click(::item * pitem)
   {

      index_array iaSel = m_iaSel;

      auto psession = get_session();

      if (!psession->is_key_pressed(::user::e_key_control) || !m_bMultiSel)
      {

         iaSel.erase_all();

      }

      if (psession->is_key_pressed(::user::e_key_shift) && m_bMultiSel)
      {

         if (main_content().m_pitemCurrent.is_set())
         {

            for (::collection::index i = main_content().m_pitemCurrent->m_item.m_iItem; i <= pitem->m_item.m_iItem; i++)
            {

               iaSel.add_unique(i);

            }

         }

      }
      else
      {

         iaSel.add_unique(pitem->m_item.m_iItem);

      }

      auto ptopic = create_topic(id_image_list_action);

      ptopic->m_pitem = pitem;

      ptopic->m_puserelement = this;

      route(ptopic);

      set_selection(iaSel, ::e_source_user);

      main_content().m_pitemCurrent = pitem;

      return true;

   }


   void image_list::on_message_create(::message::message * pmessage)
   {

      ::pointer<::message::create>pcreate(pmessage);

      pcreate->previous();

      if (pcreate->m_bRet)
      {

         return;

      }

      __construct_new(m_pimagea);
      __construct_new(m_pimageaThumb);


   }


   void image_list::on_message_destroy(::message::message * pmessage)
   {

   }


   //bool image_list::get_rectangle(::item & item)
   //{

   //   if (item == ::e_element_item)
   //   {

   //      if (!item.is_valid_item(m_imagea.get_count()))
   //      {

   //         return false;

   //      }

   //      int pad = m_iPad;

   //      int text_height = m_bNoName ? 0 : m_iTextHeight;

   //      int xpad = m_iPad;

   //      auto rectangleX = this->rectangle();

   //      int cx = rectangleX.width();

   //      int w = m_size.cx();

   //      int h = m_size.cy();

   //      int iColCount = (cx - xpad) / (w + xpad);

   //      int cxInternal = iColCount * (w + xpad) - xpad;

   //      int xLeft;

   //      if (m_ealign & e_align_horizontal_center)
   //      {

   //         xLeft = (cx - cxInternal) / 2;

   //      }
   //      else
   //      {

   //         xLeft = xpad;

   //      }

   //      int x = xLeft;

   //      int y = pad;

   //      for (index pos = 0; pos < item.m_iItem; pos++)
   //      {

   //         if (x + w + pad + w + pad >= cx)
   //         {

   //            x = xLeft;

   //            y += h + pad + text_height;

   //         }
   //         else
   //         {

   //            x += w + pad;

   //         }

   //      }

   //      item.m_rectangle.left() = x;

   //      item.m_rectangle.right() = x + w;

   //      item.m_rectangle.top() = y;

   //      item.m_rectangle.bottom() = y + h + text_height;

   //      return true;

   //   }
   //   else if (item == ::e_element_icon)
   //   {

   //      {

   //         __stack(item.m_eelement, e_element_item);

   //         if (!get_rect(item))
   //         {

   //            return false;

   //         }

   //      }

   //      if (!m_bNoName)
   //      {

   //         item.m_rectangle.bottom() -= m_iTextHeight;

   //      }

   //      return true;

   //   }
   //   else if (item == ::e_element_text)
   //   {

   //      if (m_bNoName)
   //      {

   //         return false;

   //      }

   //      {

   //         __stack(item.m_eelement, e_element_item);

   //         if (!get_rect(item))
   //         {

   //            return false;

   //         }

   //      }

   //      item.m_rectangle.top() += m_size.cy();

   //      return true;

   //   }

   //   return false;

   //}


   ::item_pointer image_list::on_hit_test(const ::point_i32 & point, ::user::e_zorder ezorder)
   {

      return ::user::scroll_base::on_hit_test(point, ezorder);
      //::collection::count c = m_imagea.get_count();

      //for (::collection::index i = 0; i < c; i++)
      //{

      //   //if(item = i;

      //   //if (get_rect(item))
      //   //{

      //   //   if (item.m_rectangle.contains(item.m_pointHitTest))
      //   //   {

      //   //      return;

      //   //   }

      //   //}

      //}

      ////item = -1;

      ////item = ::e_element_none;

      //auto pitemNone = __new ::item(e_element_none);

      //return pitemNone;

   }


   void image_list::_001OnNcDraw(::draw2d::graphics_pointer & pgraphics)
   {

      synchronous_lock synchronouslock(this->synchronization());

      auto pstyle = get_style(pgraphics);

      auto rectangle = this->raw_rectangle();

      pgraphics->set(get_font(pstyle));

      auto pointContextOffset = get_context_offset();

      rectangle.offset(pointContextOffset);

      pgraphics->fill_rectangle(rectangle, get_color(pstyle, e_element_background));

      pgraphics->draw_inset_rectangle(rectangle, argb(255, 192, 192, 192), 1.0);

      pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);


   }


   void image_list::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      synchronous_lock synchronouslock(this->synchronization());

      auto pstyle = get_style(pgraphics);

      auto rectangleClient = this->client2_rectangle();

      //pgraphics->set(get_font(pstyle));

      //rectangleX.offset(m_pointScroll);

      //pgraphics->fill_rectangle(rectangleX, get_color(pstyle, e_element_background));

      //pgraphics->draw_inset_rectangle(rectangleX, argb(255, 192, 192, 192), 1.0);

      pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

      ::collection::count cCount = m_pimagea->image_count();

      for (::collection::index iImage = 0; iImage < cCount; iImage++)
      {

         //::item itemText;

         ::rectangle_i32 rectangleSel;
         ::rectangle_i32 rectangleText;

         //itemText = e_element_text;

         if (::is_null(main_content().m_pitema))
         {

            continue;

         }

         if (iImage >= main_content().m_pitema->get_count())
         {

            continue;

         }

         auto pitem = (*main_content().m_pitema)[iImage];

         if (pitem == nullptr)
         {

            continue;
            //pitem = __create_new<item>();

            //pitem->m_item.m_iItem = iImage;

            //add_user_item(pitem);

         }

         auto puseritem = user_item(pitem);

         auto rectangle1 = user_item_rectangle(puseritem, ::user::e_layout_design);

         if (!rectangleClient.intersects(rectangle1))
         {

            continue;

         }

         ::rectangle_i32 rectangleForImage(rectangle1);

         if (m_bLabel)
         {

            rectangleForImage.bottom() -= m_iLabelHeight;

         }

         //bool bRectText = get_rect(itemText);

         //item = e_element_icon;

         ///if (this->get_item_rectangle(pitem))
         {

            ::image::image_pointer pimageSrc = m_pimagea->image_at(iImage);

            if (pimageSrc.ok())
            {

               __defer_construct_new(m_pimageaThumb);

               if (m_pimageaThumb->image_count() < m_pimagea->image_count())
               {

                  m_pimageaThumb->m_imagea.set_size(m_pimagea->image_count());

               }

               if (m_pimageaThumb->image_at(iImage)->is_null())
               {

                  __construct(m_pimageaThumb->image_at(iImage));

               }

               ::image::image_pointer pimage = m_pimageaThumb->image_at(iImage);

               if (pimage->area() <= 0)
               {

                  ::rectangle_i32 rectangleImage;

                  double dW = (double)rectangleForImage.width() / (double)pimageSrc->width();

                  double dH = (double)rectangleForImage.height() / (double)pimageSrc->height();

                  double dMin = minimum(dW, dH);

                  auto sizeSrc = pimageSrc->get_size();

                  ::size_i32 szNew =  sizeSrc * dMin;

                  if (!szNew.is_empty())
                  {

                     pimage = image()->create_image(szNew);

                     auto pgraphics = pimage->g();

                     pgraphics->set_interpolation_mode(::draw2d::e_interpolation_mode_high_quality_bicubic);

                     ::image::image_source imagesource(pimageSrc);

                     rectangle_f64 rectangleImageNew(szNew);

                     ::image::image_drawing_options imagedrawingoptions(rectangleImageNew);

                     ::image::image_drawing imagedrawing(imagedrawingoptions, imagesource);

                     pgraphics->draw(imagedrawing);

                  }

               }

               ::rectangle_i32 rectangleImage;

               rectangleImage.left() = rectangleForImage.left() + (rectangleForImage.width() - pimage->width()) / 2;

               rectangleImage.top() = rectangleForImage.top() + (rectangleForImage.height() - pimage->height()) / 2;

               rectangleImage.right() = rectangleImage.left() + pimage->width();

               rectangleImage.bottom() = rectangleImage.top() + pimage->height();

               rectangleSel = rectangleImage;

               rectangleText = rectangle1;

               if (m_bLabel)
               {

                  rectangleText.top() = rectangleText.bottom() - m_iLabelHeight;

                  rectangleSel.bottom() = rectangleText.bottom();

               }

               rectangleSel.inflate(5, 5);

               ::color::color crBorder = color::transparent;

               ::color::color crSel = color::transparent;

               bool bSel;

               bool bHover;

               if (m_iaSel.contains(iImage))
               {

                  bSel = true;

                  if (m_pitemHover && m_pitemHover->m_item.m_iItem == iImage)
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

                  if (m_pitemHover && m_pitemHover->m_item.m_iItem == iImage)
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

                  pgraphics->fill_rectangle(rectangleSel, crSel);

               }

               ::image::image_source imagesource(pimage);

               ::image::image_drawing_options imagedrawingoptions(rectangleImage);

               ::image::image_drawing imagedrawing(imagedrawingoptions, imagesource);

               pgraphics->draw(imagedrawing);

               if (bSel)
               {


                  rectangleImage.inflate(1, 1);

                  pgraphics->draw_inset_rectangle(rectangleSel, crBorder, 1.0);

                  rectangleImage.inflate(1, 1);

                  pgraphics->draw_inset_rectangle(rectangleSel, crBorder, 1.0);

               }

            }

         }

         //if (bRectText)
         {

            string str;

            if (_001GetItemText(str, iImage))
            {

               pgraphics->set_text_color(get_color(pstyle, e_element_text));

               pgraphics->draw_text(str, rectangleText, e_align_center);

            }

         }

      }

   }


   bool image_list::_001GetItemText(string & str, ::collection::index iItem)
   {

      return false;

   }


   void image_list::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

      auto rectangleX = this->rectangle();

      if (rectangleX.is_empty())
      {

         return;

      }

      synchronous_lock synchronouslock(this->synchronization());

      int left = m_iMargin;

      int top = m_iMargin;

      int x = left;

      int y = top;

      ::rectangle_i32 rectangleTotal;

      __defer_construct_new(main_content().m_pitema);

      for (::collection::index iImage = 0; iImage < m_pimagea->image_count(); iImage++)
      {

         auto & pitem = main_content().m_pitema->element_at_grow(iImage);

         if (pitem == nullptr)
         {

            pitem = __create_new<::item>();

            pitem->m_item.m_iItem = iImage;

            pitem->m_item.m_eelement = e_element_item;

         }

         auto puseritem = user_item(pitem);

         if (x > left && x + m_size.cx() + m_iMargin >= rectangleX.width())
         {

            x = left;

            y += m_size.cy() + m_iMargin;

            if (m_bLabel)
            {

               y += m_iLabelHeight;

            }

         }

         puseritem->m_rectangle2.left() = x;
         puseritem->m_rectangle2.right() = x + m_size.cx();
         puseritem->m_rectangle2.top() = y;
         puseritem->m_rectangle2.bottom() = y + m_size.cy();

         if (m_bLabel)
         {

            puseritem->m_rectangle2.bottom() += m_iLabelHeight;

         }

         x = puseritem->m_rectangle2.right() + m_iMargin;

         rectangleTotal.unite(rectangleTotal, puseritem->m_rectangle2);

      }

      //if (m_sizeImage != sizeImage)
      //{

      //   m_sizeImage = sizeImage;

      //   //m_iWheelDeltaScroll = (i16) (sizeImage.cy() / 3);

      //   m_pimageaThumb->m_imagea.erase_all();

      //}

      rectangleTotal.left() = 0;

      rectangleTotal.top() = 0;

      rectangleTotal.bottom() += m_iMargin;

      set_total_size(rectangleTotal.size(), ::user::e_layout_design);

      //m_pscrollstateVertical->m_iPage = rectangleX.height();

      ::user::scroll_base::on_layout(pgraphics);

      //on_change_scroll_state(::user::e_layout_design);

   }


   image_list_impact::image_list_impact()
   {

   }


   image_list_impact::~image_list_impact()
   {

   }


//   void image_list_impact::assert_ok() const
//   {
//
//      ::user::image::image_list::assert_ok();
//
//   }
//
//
//   void image_list_impact::dump(dump_context & dumpcontext) const
//   {
//
//      ::user::image::image_list::dump(dumpcontext);
//
//   }


   void image_list_impact::install_message_routing(::channel * pchannel)
   {

      ::user::impact::install_message_routing(pchannel);
      ::user::image_list::install_message_routing(pchannel);

      MESSAGE_LINK(MESSAGE_CREATE, pchannel, this, &image_list_impact::on_message_create);
      MESSAGE_LINK(MESSAGE_DESTROY, pchannel, this, &image_list_impact::on_message_destroy);

   }


   void image_list_impact::on_message_create(::message::message * pmessage)
   {

      ::pointer<::message::create>pcreate(pmessage);

      pcreate->previous();

   }


   void image_list_impact::on_message_destroy(::message::message * pmessage)
   {

   }


   //void image_list_impact::on_layout(::draw2d::graphics_pointer & pgraphics)
   //{

   //   ::user::image::image_list::on_layout(pgraphics);

   //   auto rectangleX = this->rectangle();

   //   if (rectangleX.is_empty())
   //   {

   //      return;

   //   }

   //   m_sizeTotal = m_rectangleTotal.size();

   //   on_change_impact_size(pgraphics);

   //}


   void image_list_impact::handle(::topic * ptopic, ::context * pcontext)
   {

      ::user::impact::handle(ptopic, pcontext);

      if (ptopic->m_atom == id_after_change_text)
      {

         throw ::exception(todo, "core");
         //auto * peditimpact = _001TypedWindow < ::userex::top_edit_impact >();

         //if (peditimpact != nullptr && ptopic->user_interaction() == peditimpact)
         //{

         //   string strText;

         //   peditimpact->get_text(strText);

         //}

      }

   }


   ::item_pointer image_list::current_item()
   {

      synchronous_lock synchronouslock(this->synchronization());

      if (m_iaSel.get_count() == 1)
      {

         return __new ::item(e_element_item, m_iaSel[0]);

      }

      return nullptr;

   }


   index_array image_list::get_selection()
   {

      synchronous_lock synchronouslock(this->synchronization());

      return m_iaSel;

   }


   void image_list::set_current_item(::collection::index iFind, const ::action_context & context)
   {

      synchronous_lock synchronouslock(this->synchronization());

      m_iaSel.erase_all();

      m_iaSel.add(iFind);

   }


   void image_list::set_selection(const index_array & ia, const ::action_context & context)
   {

      synchronous_lock synchronouslock(this->synchronization());

      if (!::acme::array::equals_non_unique_unordered(ia, m_iaSel))
      {

         m_iaSel = ia;

         auto ptopic = create_topic(::id_after_change_cur_sel);

         ptopic->m_puserelement = this;

         ptopic->m_pitem = current_item();

         ptopic->m_atom = ::id_after_change_cur_sel;

         route(ptopic);

      }

   }


} // namespace user



