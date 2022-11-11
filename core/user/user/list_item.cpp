// From list.cpp by camilo on 2022-06-29 05:39 <3ThomasBorregaardSorensen!! 
#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
//#include "core/user/user/_component.h"
#endif
#include "aura/graphics/image/drawing.h"
#include "aura/graphics/image/list.h"
#include "aura/graphics/image/fastblur.h"
#include "aura/graphics/draw2d/draw2d.h"
#include "aura/graphics/draw2d/brush.h"
#include "list.h"
#include "list_item.h"
#include "list_column.h"


namespace user
{


   list_subitem::list_subitem()
   {

      m_plistsubitem = this;

   }


   void list_subitem::initialize_list_subitem(list_item * plistitem)
   {

      mesh_subitem::initialize_mesh_subitem(plistitem);

   }


   draw_list_subitem::draw_list_subitem()
   {

      m_pdrawlistsubitem = this;

   }


   void draw_list_subitem::initialize_draw_list_subitem(list_item * plistitem)
   {

      list_subitem::initialize_list_subitem(plistitem);

   }


   list_item::list_item()
   {

      m_plistitem = this;
      //m_iGroup = -1;
      m_iItem = -1;
      m_iDisplayItem = -1;
      //m_iColumn = -1;
      //m_iColumnKey = -1;
      //m_iOrder = -1;
      //m_iSubItem = -1;
      //m_iListItem = -1;
      //m_colorText = __indexed_color(-1);
      //m_colorTextBackground = argb(255, 0, 0, 0);
      //m_colorItemBackground = ::color::transparent;
      m_iState = -1;
      //m_iImage = -1;
      m_bOk = false;

      m_iGroupTopDisplayIndex = -1;
      m_iGroupCount = -1;

   }


   void list_item::initialize_list_item(list * plist)
   {

      initialize_mesh_item(plist);

   }


   draw_list_item::draw_list_item::draw_list_item()
   {

      m_pdrawlistitem = this;

      m_prectClient = nullptr;

      //m_iColumn = -1;
      m_iColumnWidth = 0;
      //m_pcolumn = nullptr;

      //m_iItemRectItem = -1;

      //m_iSubItemRectItem = -1;
      //m_iSubItemRectSubItem = -1;
      //m_iSubItemRectOrder = -1;
      //m_iSubItemRectColumn = -1;
      //m_pcolumn = nullptr;

      //m_iListItemRectItem = -1;
      //m_iListItemRectSubItem = -1;
      //m_iListItemRectListItem = -1;

   }


   void draw_list_item::initialize_draw_list_item(list * plist)
   {

      initialize_list_item(plist);

   }


   void draw_list_item::update_item_color(::draw2d::graphics_pointer & pgraphics)
   {

      auto pstyle = m_pmesh->m_plist->get_style(pgraphics);

      auto estate = get_user_state();

      m_colorItemBackground = m_pmesh->m_plist->get_color(pstyle, ::e_element_item_background, estate);

   }


   ::image_list * draw_list_subitem::get_image_list()
   {

      if (m_pitem->m_pdrawmeshitem->m_bListItemHover && m_pcolumn->m_pimagelistHover != nullptr)
      {

         return m_pcolumn->m_pimagelistHover;

      }
      else
      {

         return m_pcolumn->m_pimagelist;

      }

   }


   void draw_list_subitem::draw_image(::draw2d::graphics_pointer & pgraphics)
   {

      if (m_pcolumn->m_bIcon)
      {

         draw2d::icon * picon;

         if (m_pcolumn->m_mapIcon.lookup((i32)m_iImage, picon))
         {

            pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

            image_source imagesource(picon);

            image_drawing_options imagedrawingoptions(m_rectangleImage);

            image_drawing imagedrawing(imagedrawingoptions, imagesource);

            //m_pgraphics->draw(imagedrawing) != false;

            pgraphics->draw(imagedrawing);

         }

      }
      else
      {

         //synchronous_lock synchronouslock(get_image_list()->mutex());

         auto pimagelist = get_image_list();

         if (pimagelist->m_pimage->is_null() || pimagelist->m_pimage->area() <= 0)
         {

            return;

         }

         if ((m_pitem->m_pmesh->m_plist->m_iIconBlur > 0 && m_pitem->m_pmesh->m_plist->m_iIconBlurRadius > 0)
            || (m_pitem->m_pmesh->m_plist->m_dIconSaturation < 1.0)
            || (m_pitem->m_pmesh->m_plist->m_dIconLightness < 1.0)
            || (m_pitem->m_pmesh->m_plist->m_dIconOpacity < 1.0))
         {

            auto & pimage = m_pitem->m_pmesh->m_plist->m_mapIconBlur[m_iImage];

            m_pitem->m_pmesh->__defer_construct(pimage);

            int iRate = 3;

            if (pimage.nok() && m_iImage >= 0 && m_iImage < get_image_list()->get_image_count())
            {

               if (m_pitem->m_pmesh->m_plist->m_iIconBlur > 0 && m_pitem->m_pmesh->m_plist->m_iIconBlurRadius > 0)
               {


                  pimage->create(m_rectangleImage.size() + size_i32(m_pitem->m_pmesh->m_plist->m_iIconBlurRadius * iRate * 2, m_pitem->m_pmesh->m_plist->m_iIconBlurRadius * iRate * 2));
                  //m_plist->m_pfastblurIcon->initialize(m_rectangleImage.size() , m_plist.m_iIconBlurRadius);

               }
               else
               {

                  pimage->create(m_rectangleImage.size());

               }

               pimage->get_graphics()->set_alpha_mode(::draw2d::e_alpha_mode_set);

               pimage->get_graphics()->fill_rectangle(pimage->size(), ::color::transparent);

               get_image_list()->draw(pimage->g(), (i32)m_iImage,
                  point_i32(m_pitem->m_pmesh->m_plist->m_iIconBlurRadius * iRate, m_pitem->m_pmesh->m_plist->m_iIconBlurRadius * iRate), m_rectangleImage.size(), ::point_i32(), 0);

               if (m_pitem->m_pmesh->m_plist->m_dIconSaturation < 1.0)
               {

                  pimage->saturation(m_pitem->m_pmesh->m_plist->m_dIconSaturation);

               }

               if (m_pitem->m_pmesh->m_plist->m_dIconLightness < 1.0)
               {

                  pimage->lightness(m_pitem->m_pmesh->m_plist->m_dIconLightness);

               }


               if (m_pitem->m_pmesh->m_plist->m_dIconOpacity < 1.0)
               {

                  pimage->opacity(m_pitem->m_pmesh->m_plist->m_dIconOpacity);

               }

               //pimage->g()->fill_rectangle(::rectangle_i32(pimage->size()), argb(255, 200, 220, 255));
               if (m_pitem->m_pmesh->m_plist->m_iIconBlur > 0 && m_pitem->m_pmesh->m_plist->m_iIconBlurRadius > 0)
               {

                  for (index i = 0; i < m_pitem->m_pmesh->m_plist->m_iIconBlur; i++)
                  {

                     m_pitem->m_pmesh->m_plist->__defer_construct_new(m_pitem->m_pmesh->m_plist->m_pfastblurIcon);

                     m_pitem->m_pmesh->m_plist->m_pfastblurIcon->blur(pimage, m_pitem->m_pmesh->m_plist->m_iIconBlurRadius);

                  }

               }

            }

            m_pitem->m_pdrawlistitem->m_pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

            if (::is_ok(pimage))
            {

               image_source imagesource(pimage);

               rectangle_f64 rectangleDib(m_rectangleImage.top_left() - size_i32(m_pitem->m_pmesh->m_plist->m_iIconBlurRadius * iRate, m_pitem->m_pmesh->m_plist->m_iIconBlurRadius * iRate),
                  m_rectangleImage.size() + size_i32(m_pitem->m_pmesh->m_plist->m_iIconBlurRadius * iRate * 2, m_pitem->m_pmesh->m_plist->m_iIconBlurRadius * iRate * 2));

               image_drawing_options imagedrawingoptions(rectangleDib);

               image_drawing imagedrawing(imagedrawingoptions, imagesource);

               m_pitem->m_pdrawlistitem->m_pgraphics->draw(imagedrawing);

            }

            ::rectangle_i32 rectangleI;

            if (m_pitem->m_pmesh->m_plist->m_pimageSpot->is_set() && m_pitem->m_pmesh->m_plist->m_pimageSpot->area() > 0 && rectangleI.intersect(m_rectangleImage, m_pitem->m_pmesh->m_plist->m_rectangleSpot)
               && m_iImage >= 0 && m_iImage < get_image_list()->get_image_count())
            {
               ///return true;

               m_pitem->m_pmesh->m_plist->m_pimageTime = m_pitem->m_pmesh->m_pcontext->m_pauracontext->create_image(m_pitem->m_pmesh->m_plist->m_pimageSpot->size());

               ::rectangle_i32 rectangle = rectangleI;

               rectangle.offset(-m_rectangleImage.top_left());

               //m_plist->m_pimageTime->get_graphics()->set_alpha_mode(::draw2d::e_alpha_mode_set);

               //m_plist->m_pimageTime->get_graphics()->fill_rectangle(r, 0);

               ::rectangle_i32 rect2 = rectangleI;

               rect2.offset(-m_pitem->m_pmesh->m_plist->m_rectangleSpot.top_left());

               m_pitem->m_pmesh->m_plist->m_pimageTime->get_graphics()->set_alpha_mode(::draw2d::e_alpha_mode_set);

               get_image_list()->draw(m_pitem->m_pmesh->m_plist->m_pimageTime->get_graphics(), (i32)m_iImage,
                  rect2.top_left(),
                  rectangle.size(), rectangle.top_left(), 0);

               //m_pgraphics->draw(rectangleI + point_i32(200,200), m_plist->m_pimageTime->get_graphics(), rect2.top_left());

               //m_plist->m_pimageTime->div_alpha(rect2->top_left(), rect2->size());

               m_pitem->m_pmesh->m_plist->m_pimageTime->channel_multiply(::color::e_channel_alpha, m_pitem->m_pmesh->m_plist->m_pimageSpot, rect2);

               //m_plist->m_pimageTime->mult_alpha(rect2->top_left(), rect2->size());

               m_pitem->m_pdrawlistitem->m_pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

               {

                  image_source imagesource(m_pitem->m_pmesh->m_plist->m_pimageTime, rect2);

                  image_drawing_options imagedrawingoptions(rectangleI);

                  image_drawing imagedrawing(imagedrawingoptions, imagesource);

                  m_pitem->m_pdrawlistitem->m_pgraphics->draw(imagedrawing);

               }

            }

            return;

         }
         //if(m_plist->m_bMorePlain)
         //{

         //   m_pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_set);
         //   return m_pgraphics->BitBlt(m_rectangleImage.left, m_rectangleImage.top, m_rectangleImage.width(), m_rectangleImage.height(),get_image_list()->m_pimage->g(), m_iImage * m_rectangleImage->width());

         //}
         else
         {

            m_pitem->m_pdrawlistitem->m_pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

            //auto ret = 

            pimagelist->_draw(m_pitem->m_pdrawlistitem->m_pgraphics, (i32)m_iImage, m_rectangleImage.top_left(), m_rectangleImage.size(), ::point_i32(), 0);

            //auto pimageDebug = create_image(m_rectangleImage.size());
            //{

            //   auto ret = get_image_list()->draw(pimageDebug->g(), (i32)m_iImage, { 0,0 }, m_rectangleImage.size(), ::point_i32(), 0);
            //   auto pcolorref = pimageDebug->get_data();
            //   output_debug_string("imageDebug");

            //}

            return;

         }

      }
      
   }

   
   list_group::list_group()
   {


   }


   void draw_list_group::draw_group_image(::draw2d::graphics_pointer & pgraphics)
   {

      //return 

      m_pmesh->m_plist->m_pimagelistGroup->draw(m_pgraphics, (i32)m_iImage, m_rectangleImage.top_left(), m_rectangleImage.size(), ::point_i32(), 0);

   }


   ::color::color draw_list_subitem::calculate_text_color(::draw2d::graphics_pointer & pgraphics, ::user::enum_state estate)
   {

      auto pstyle = m_pitem->m_pmesh->m_plist->get_style(pgraphics);

      return m_pitem->m_pmesh->m_plist->get_color(pstyle, ::e_element_item_text, estate);

   }


   void draw_list_subitem::update_color(::draw2d::graphics_pointer & pgraphics)
   {

      if (!(m_pitem->m_pmesh->m_ecachehinting & e_cache_hinting_subitem_color_per_theme_and_state))
      {

         m_pitem->m_pmesh->m_plist->_001GetSubItemColor(this);

      }

      auto estate = m_pitem->m_pdrawlistitem->get_user_state();

      auto & pdrawlistcolumn = m_pcolumn->m_pdrawlistcolumn;

      if (estate < 16)
      {

         auto & color = pdrawlistcolumn->m_coloraText[(int)estate];

         if (!color.is_ok())
         {

            color = calculate_text_color(pgraphics, estate);

            color = ::success;

         }

         m_colorText = color;

      }
      else
      {

         m_colorText = calculate_text_color(pgraphics, estate);

      }


   }


   void draw_list_subitem::set_text_color(::draw2d::graphics_pointer & pgraphics)
   {

      auto estate = m_pitem->m_pdrawlistitem->get_user_state();

      auto & pdrawlistcolumn = m_pcolumn->m_pdrawlistcolumn;

      auto & pbrushText = pdrawlistcolumn->m_brushaText[estate & 15];

      if (!pbrushText)
      {

         m_pitem->m_pmesh->m_plist->__construct(pbrushText);

      }

      if (!m_pitem->m_pmesh->m_plist->m_bHighHighLight)
      {

         ::color::color color;

         color.set_COLORREF(m_colorText);

         color.alpha = color.alpha / 3;

         if (color != pbrushText->m_color)
         {

            pbrushText->create_solid(color);

         }
         else
         {

            //output_debug_string("OptHilite(listItemColorText)\n");

         }

      }
      else
      {

         if (m_colorText != pbrushText->m_color)
         {

            pbrushText->create_solid(m_colorText);

         }
         else
         {

            //output_debug_string("Opt(listItemColorText)\n");

         }

      }

      m_pitem->m_pdrawlistitem->m_pgraphics->set(pbrushText);

   }


   void draw_list_subitem::draw_text(::draw2d::graphics_pointer & pgraphics)
   {

      if (m_bOk)
      {

         if (m_pitem->m_pmesh->m_plist->m_eview == list::impact_icon && m_pitem->m_pmesh->m_plist->m_bEmboss && ((m_pitem->m_pmesh->m_plist->m_iTextBlurRadius > 0 && m_pitem->m_pmesh->m_plist->m_iTextBlur > 0) || m_pitem->m_pmesh->m_plist->m_iTextSpreadRadius > 0))
         {

            if (m_strText.has_char())
            {

               ::image_pointer & pimage2 = m_pitem->m_pmesh->m_plist->m_mapBlur[m_pitem->m_iItem];

               m_pitem->m_pmesh->m_plist->__defer_construct(pimage2);

               auto psystem = m_pitem->m_pmesh->m_plist->acmesystem()->m_paurasystem;

               auto pdraw2d = psystem->draw2d();

               //if (

               pdraw2d->embossed_text_out(
                  m_pitem->m_pdrawlistitem->m_pgraphics,
                  m_rectangleText,
                  m_strText,
                  *m_pitem->m_pmesh->m_plist->m_pfastblur,
                  pimage2,
                  m_pitem->m_pdrawlistitem->m_pgraphics->m_pfont,
                  m_pcolumn->m_pdrawlistcolumn->m_ealign,
                  m_pcolumn->m_pdrawlistcolumn->m_edrawtext,
                  m_colorText,
                  m_colorTextBackground,
                  m_pitem->m_pmesh->m_plist->m_iTextSpreadRadius, m_pitem->m_pmesh->m_plist->m_iTextBlurRadius,
                  m_pitem->m_pmesh->m_plist->m_iTextBlur,
                  m_strText != m_pitem->m_pmesh->m_plist->m_mapText[m_pitem->m_iItem] || m_colorTextBackground != m_pitem->m_pmesh->m_plist->m_mapBackColor[m_pitem->m_iItem]);

               //)
               {

                  m_pitem->m_pmesh->m_plist->m_mapText[m_pitem->m_iItem] = m_strText;

                  m_pitem->m_pmesh->m_plist->m_mapBackColor[m_pitem->m_iItem] = m_colorTextBackground;

               }

            }

         }
         else if (m_strText.has_char())
         {

            //auto pbrushText = __create < ::draw2d::brush > ();

            update_color(pgraphics);

            //pbrushText->create_solid(m_colorText);

            //m_pgraphics->set(pbrushText);

            m_pitem->m_pdrawlistitem->m_pgraphics->set_text_rendering_hint(::write_text::e_rendering_anti_alias);

            auto pstyle = m_pitem->m_pmesh->m_plist->get_style(m_pitem->m_pdrawlistitem->m_pgraphics);

            auto ealign = (::enum_align)m_pitem->m_pmesh->m_plist->get_int(pstyle, e_int_list_item_text_align);

            auto edrawtext = (::enum_draw_text)m_pitem->m_pmesh->m_plist->get_int(pstyle, e_int_list_item_draw_text_flags);

            set_text_color(pgraphics);

            m_pitem->m_pdrawlistitem->m_pgraphics->draw_text(m_strText, m_rectangleText, ealign, edrawtext);

            //m_pgraphics->fill_rectangle(m_rectangleText.left, m_rectangleText.top, 100, 100, argb(128, 100, 125, 255));

            if (m_strText == "LOVE OR NOTHING")
            {

               output_debug_string("LOVE OR NOTHING");

            }

         }

      }

   }


   draw_list_group::draw_list_group()
   {


   }


   void draw_list_group::initialize_draw_list_group(list * plist)
   {

      initialize_draw_mesh_group(plist);

   }


} // namespace user




