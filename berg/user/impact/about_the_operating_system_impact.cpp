// From app_simple_application/impact.cpp to app_simple_about_the_operationg_system/main_impact.cpp by
//    camilo on 2026-03-30 17:49 <3ThomasBorregaardSørensen!!
#include "framework.h"
//#include "application.h"
//#include "document.h"
#include "about_the_operating_system_impact.h"
//#include "imaging_freeimage/image_context.h"
#include "acme/platform/_referencing_debugging.h"
#include "acme/user/simple/dialog_box_line.h"
#include "acme/constant/user_message.h"
#include "acme/filesystem/filesystem/file_context.h"
#include "acme/filesystem/filesystem/file_system.h"
#include "acme/platform/node.h"
#include "acme/prototype/mathematics/mathematics.h"
#include "acme/user/simple/dialog_box_line.h"
#include "aura/graphics/draw2d/draw2d.h"
#include "aura/graphics/image/context.h"
#include "aura/graphics/image/drawing.h"
#include "aura/graphics/write_text/write_text.h"
#include "aura/message/user.h"
#include "berg/platform/application.h"


CLASS_DECL_AURA ::color::color dk_red(); // <3 tbs


namespace berg
{


   about_the_operating_system_impact::about_the_operating_system_impact()
   {

      m_flagNonClient -= e_non_client_background;
      m_iSequence = 0;
      m_bNeedFullRedrawOnResize = true;

      m_bDefaultClickHandling = true;

      m_bEmptyAreaIsClientArea = true;
   }


   about_the_operating_system_impact::~about_the_operating_system_impact() {}


#ifdef _DEBUG


   long long about_the_operating_system_impact::increment_reference_count() { return ::user::impact::increment_reference_count(); }


   long long about_the_operating_system_impact::decrement_reference_count() { return ::user::impact::decrement_reference_count(); }


#endif


   void about_the_operating_system_impact::install_message_routing(::channel *psender)
   {

      ::user::impact::install_message_routing(psender);

      USER_MESSAGE_LINK(::user::e_message_create, psender, this, &impact::on_message_create);
      USER_MESSAGE_LINK(::user::e_message_destroy, psender, this, &impact::on_message_destroy);
   }


   void about_the_operating_system_impact::on_message_create(::message::message *pmessage)
   {

      ::pointer<::message::create> pcreate(pmessage);

      // display();

      pcreate->previous();

      if (pcreate->m_bRet)
      {

         return;
      }
      ::cast < ::apex::system > papexsystem = system();
      ::string strOperatingSystemImageUrl = papexsystem->operating_system_icon_url({128, 128});
image()->load_image(strOperatingSystemImageUrl,
{
   .sync=false,.functionLoaded = [this](::image::image * pimage)
   {
      m_pimageOperatingSystem = pimage;

   }
});

#if defined(LINUX)
      ::string strOperatingAmbientImageUrl = papexsystem->operating_ambient_icon_url({64, 64});
      image()->load_image(strOperatingAmbientImageUrl,
      {
         .sync=false,.functionLoaded = [this](::image::image * pimage)
         {
            m_pimageOperatingAmbient = pimage;

         }
      });
#endif
      // application()->show_about_box();
   }


   void about_the_operating_system_impact::on_message_destroy(::message::message *pmessage) {}


   void about_the_operating_system_impact::handle(::topic *ptopic, ::handler_context *phandlercontext)
   {

      ::user::impact::handle(ptopic, phandlercontext);
   }


   //document *about_the_operating_system_impact::get_document() { return dynamic_cast<document *>(::user::impact::get_document()); }


   void about_the_operating_system_impact::_001OnClip(::draw2d::graphics_pointer &pgraphics) {}


   ::write_text::font * about_the_operating_system_impact::get_font(::simple_dialog_box_line * psimpledialogboxline)
   {

      auto & pfont = m_mapFontThomasBS_[psimpledialogboxline->m_esimpledialogstyle];

      if (pfont)
      {

         return pfont;

      }

      auto rectangleX = this->rectangle();

      if (rectangleX.is_empty())
      {

         return nullptr;

      }

      auto psystem = system();

      auto pnode = psystem->draw2d();

      auto pwritetext = pnode->write_text();

      //auto fontsizeHeading1 = ::write_text::font_size(psimpledialogboxline->m_dFontSizeEm * 36.0 * rectangleX.height() / 1'080, e_unit_pixel);

      auto dFontSizeEm = psimpledialogboxline->get_font_size_em();

      auto iFontWeight = psimpledialogboxline->get_font_weight();

      auto fontsize = ::write_text::font_size(dFontSizeEm * 36.0 * rectangleX.height() / 1'080, e_unit_pixel);

//      m_pfontThomasBSHeading1 =

      pfont = pwritetext->font(e_font_sans_ui, fontsize, iFontWeight);

      return pfont;

   }


   void about_the_operating_system_impact::_001OnDraw(::draw2d::graphics_pointer &pgraphics)
   {

      auto rectangleX = this->rectangle();

      if (rectangleX.is_empty())
      {

         return;
      }

      //      if (pgraphics->payload("set_transparent") == "set_transparent")
      //      {
      //
      //         information() << "set_transparent called";
      //
      //      }
      //      else
      //      {
      //
      //         information() << "set_transparent NOT called!!";
      //
      //      }

      ::double_rectangle rectangleClipBox;

      // pgraphics->reset_clip();

      // pgraphics->get_clip_box(rectangleClipBox);

      auto matrix = pgraphics->m_matrix;

      // auto origin = pgraphics->origin();

      auto opacity = ::opacity(48);

      pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

      pgraphics->fill_rectangle(rectangleX, argb(208, 0, 0, 0));

      ::color::color color_dk(dk_red());

#ifdef DEBUG_WORK

      ::int_rectangle rectangleDryProWithLove_Work(5, 5, 1915, 1075);

      pgraphics->fill_rectangle(rectangleDryProWithLove_Work, argb(255, 150, 200, 255));

#endif

      pgraphics->set_text_color(color_dk);


      // if (!m_pfontThomasBSHeading1)
      // {
      //
      //    auto psystem = system();
      //
      //    auto pnode = psystem->draw2d();
      //
      //    auto pwritetext = pnode->write_text();
      //
      //    auto fontsizeHeading1 = ::write_text::font_size(72.0 * rectangleX.height() / 1'080, e_unit_pixel);
      //
      //    m_pfontThomasBSHeading1 = pwritetext->font("Fira Code", fontsizeHeading1, 900);
      //
      // }
      //
      // if (!m_pfontThomasBS_)
      // {
      //
      //    auto psystem = system();
      //
      //    auto pnode = psystem->draw2d();
      //
      //    auto pwritetext = pnode->write_text();
      //
      //    auto fontsize = ::write_text::font_size(36.0 * rectangleX.height() / 1'080, e_unit_pixel);
      //
      //    m_pfontThomasBS_ = pwritetext->font("Fira Code", fontsize);
      //
      // }
      //
      // if (!m_pfontThomasBSDetail)
      // {
      //
      //    auto psystem = system();
      //
      //    auto pnode = psystem->draw2d();
      //
      //    auto pwritetext = pnode->write_text();
      //
      //    auto fontsizeHeading1 = ::write_text::font_size(24.0 * rectangleX.height() / 1'080, e_unit_pixel);
      //
      //    m_pfontThomasBSDetail = pwritetext->font("Fira Code", fontsizeHeading1, 200);
      //
      // }


      _synchronous_lock synchronouslockDocument(get_document()->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      auto stra = m_papp->get_operating_system_information_lines();

      double x = 0.;

      double y = 0.;

      ::int_point point;

      string strText;

      m_iSequence++;

      strText.formatf("psimpleapplication->m_pimpact->_001OnDraw(pgraphics); %d", m_iSequence);

      auto size = pgraphics->get_text_extent(strText);

      bool bFixedPosition = true;

      if (bFixedPosition)
      {

         point = {10, 10};
      }
      else
      {

         point.x = mathematics()->random(0, (int)(rectangleX.width() - size.cx - 128 - 11));
         point.y = mathematics()->random(0, (int)(rectangleX.height() - size.cy * 2));
      }

      if (m_pimageOperatingSystem)
      {

//         pimage->g()->set_interpolation_mode(::draw2d::e_interpolation_mode_high_quality_bicubic);

         ::image::image_source imagesource(m_pimageOperatingSystem);

         ::image::image_drawing_options imagedrawingoptions(::int_rectangle_dimension(point.x, point.y, m_pimageOperatingSystem->width(), m_pimageOperatingSystem->height()));

         ::image::image_drawing imagedrawing(imagedrawingoptions, imagesource);

         pgraphics->draw(imagedrawing);


      }

      if (m_pimageOperatingAmbient)
      {

         //         pimage->g()->set_interpolation_mode(::draw2d::e_interpolation_mode_high_quality_bicubic);

         ::image::image_source imagesource(m_pimageOperatingAmbient);

         ::image::image_drawing_options imagedrawingoptions(::int_rectangle_dimension(point.x, point.y + 128+ 11, m_pimageOperatingAmbient->width(), m_pimageOperatingAmbient->height()));

         ::image::image_drawing imagedrawing(imagedrawingoptions, imagesource);

         pgraphics->draw(imagedrawing);


      }


      point.x += 128+11;
      ::color::color color;

      //int iFont = -1024;

             pgraphics->set_text_rendering_hint(write_text::e_rendering_anti_alias);
      //
             pgraphics->set_alpha_mode(draw2d::e_alpha_mode_blend);


      for (auto &strItem: stra)
      {

         auto psimpledialogboxline = create_newø < ::simple_dialog_box_line > ();

         psimpledialogboxline->_001Parse(strItem);

         auto pfont = get_font(psimpledialogboxline);

//         ::string strLine = strItem;


         // if (strLine.begins_eat("#"))
         // {
         //
         //    strLine.trim();
         //
         //    if (iFont != 1)
         //    {
         //
         //       iFont = 1;
         //
         //       pgraphics->set(m_pfontThomasBSHeading1);
         //
         //       pgraphics->set_text_rendering_hint(write_text::e_rendering_anti_alias);
         //
         //       pgraphics->set_alpha_mode(draw2d::e_alpha_mode_blend);
         //       opacity = ::opacity(218);
         //       color = color::white;
         //
         //       color &= opacity;
         //
         //       pgraphics->set_text_color(color);
         //    }
         // }
         // else if (strLine.begins_eat("-#"))
         // {
         //
         //    strLine.trim();
         //
         //    if (iFont != -1)
         //    {
         //
         //       iFont = -1;
         //
         //       pgraphics->set(m_pfontThomasBSDetail);
         //
         //       pgraphics->set_text_rendering_hint(write_text::e_rendering_anti_alias);
         //
         //       pgraphics->set_alpha_mode(draw2d::e_alpha_mode_blend);
         //       opacity = ::opacity(160);
         //       color = color::white;
         //
         //       color &= opacity;
         //
         //       pgraphics->set_text_color(color);
         //    }
         // }
         // else
         // {
         //    if (iFont != 10)
         //    {
         //
         //       iFont = 10;
         //       pgraphics->set(m_pfontThomasBS_);
         //
         //       pgraphics->set_text_rendering_hint(write_text::e_rendering_anti_alias);
         //
         //       pgraphics->set_alpha_mode(draw2d::e_alpha_mode_blend);
         //       color = color::white;
         //       opacity = ::opacity(160);
         //       color &= opacity;
         //
         //       pgraphics->set_text_color(color);
         //    }
         // }

         pgraphics->set(pfont);

         color = color::white;

         auto opacity = ::opacity(psimpledialogboxline->get_byte_text_color_strength());

         color &= opacity;

         pgraphics->set_text_color(color);

         if (psimpledialogboxline->m_str.has_character())
         {
         
            pgraphics->text_out(point.x, point.y + y, psimpledialogboxline->m_str);

         }

         auto s = pgraphics->get_text_extent(psimpledialogboxline->get_line_height_text());

         y += s.cy;

      }

      pgraphics->set_smooth_mode(::draw2d::e_smooth_mode_none);

   }


   void about_the_operating_system_impact::on_layout(::draw2d::graphics_pointer &pgraphics)
   {

      auto rectangleX = this->rectangle();

      if (rectangleX.is_empty())
      {

         return;
      }

      ::user::impact::on_layout(pgraphics);

      setup_default_client_area_user_item();
   }


   bool about_the_operating_system_impact::on_click(::item *pitem, ::user::mouse *pmouse)
   {

      //if (::is_set(pitem))
      //{

      //   if (pitem->m_item.m_eelement == ::e_element_client)
      //   {

      //      print_line("on_click : e_element_client");

      //      ::file::file_dialog_filter filter;

      //      filter.add({"application.txt", "application.txt"});

      //      pick_single_file_to_open(filter,
      //                               [this](::file::file_dialog *pdialog)
      //                               {
      //                                  try
      //                                  {

      //                                     if (pdialog->m_patha.has_element())
      //                                     {

      //                                        auto memory = file()->as_memory(pdialog->m_patha.first());

      //                                        auto size = memory.size();

      //                                        informationf("got file with %d bytes", size);

      //                                        file()->put_memory(m_papp->m_pathApplicationText, memory);
      //                                     }
      //                                  }
      //                                  catch (...)
      //                                  {

      //                                     auto pmessageboxpayload = message_box("No file loaded...");

      //                                     post(pmessageboxpayload);
      //                                  }
      //                               });

      //      return true;
      //   }
      //}

      return ::user::impact::on_click(pitem, pmouse);
   }


} // namespace app_simple_application
