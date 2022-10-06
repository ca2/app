#include "framework.h"
#include "aqua/xml/document.h"
#include "impact.h"
#include "aura/graphics/write_text/font.h"
#include "aura/graphics/draw2d/brush.h"
#include "aura/graphics/draw2d/pen.h"
#include "aura/graphics/image/context_image.h"
#include "aura/graphics/image/drawing.h"
#include "aura/message/user.h"
#include "base/user/user/document.h"
#include "base/user/user/impact_system.h"
#include "base/user/user/split_impact.h"
#include "base/platform/application.h"
#include "base/platform/system.h"
#include "aura/user/user/system.h"
#include "aura/platform/node.h"
#include "aura/user/user/plain_edit.h"
#include "base/user/user/impact_creator.h"


namespace user
{


   menu_impact::menu_impact() 
   {

      m_bClickDefaultMouseHandling = true;

      m_flagNonClient.erase(e_non_client_background);

      m_flagNonClient.erase(e_non_client_focus_rect);

   }


   menu_impact::~menu_impact()
   {

   }


   void menu_impact::assert_ok() const
   {

      ::user::impact::assert_ok();

   }


   void menu_impact::dump(dump_context & dumpcontext) const
   {

      ::user::impact::dump(dumpcontext);

   }


   void menu_impact::install_message_routing(::channel * pchannel)
   {

      ::user::impact::install_message_routing(pchannel);

      //install_click_default_mouse_handling(pchannel);

      MESSAGE_LINK(e_message_create, pchannel, this, &menu_impact::on_message_create);
      MESSAGE_LINK(e_message_destroy, pchannel, this, &menu_impact::on_message_destroy);

   }


   bool menu_impact::on_click(::item * pitem)
   {

      if (!is_window_enabled())
      {

         return false;

      }

      //auto point = item.m_pointHitTest;

      auto pitemHit = pitem;

      ::atom idCommand;

      if (::is_set(pitemHit) && pitemHit->menu_impact_command() >= 0)
      {

         xml::node * pnodeMain = m_pxmldoc->get_child_at("menubar", 0, 1);

         if (pnodeMain->get_children_count("menubar") <= 0)
         {

            pnodeMain = m_pxmldoc;

         }

         xml::node * pnode = pnodeMain->get_child_at("menubar", pitemHit->menu_impact_group(), 1);

         if (pnode != nullptr)
         {

            xml::node * pnodeItem = pnode->child_at(pitemHit->menu_impact_command());

            if (pnodeItem != nullptr)
            {

               idCommand = pnodeItem->attribute("id").atom();

            }

         }

      }
      else
      {

         idCommand = "home";

      }

      m_pitemCurrent = pitemHit;

      set_need_redraw();

      if (!idCommand.is_empty())
      {

         ::message::command command(idCommand);

         route_command(&command);

         return command.m_bRet;

      }

      return false;

   }


   void menu_impact::on_message_create(::message::message * pmessage)
   {

      payload(FONTSEL_IMPACT) = true;

      m_pbrushBkSel.create(this);
      m_pbrushBkHoverSel.create(this);
      m_ppenBkSel.create(this);
      m_ppen.create(this);


      m_pbrushBkHoverSel->create_solid(argb(255, 230, 230, 230));
      m_pbrushBkSel->create_solid(argb(255, 240, 240, 240));
      m_ppenBkSel->create_solid(3.0, argb(255, 0, 148, 202));
      m_ppen->create_solid(1.0, argb(255, 210, 210, 210));


      __pointer(::message::create) pcreate(pmessage);

      pcreate->previous();

      if (pcreate->m_bRet)
         return;

      //auto estatus = 
      
      __compose_new(m_pxmldoc);

      //if (!estatus)
      //{

      //   pcreate->failed("Failed to create memory_new xml document for menu impact");

      //   return;

      //}

      //set_topic_text("menu_impact> ");

      auto atom = get_document()->m_pimpactsystem->m_atom;

      string strText;

      auto papp = get_app();

      papp->data_get(m_atom + ".cur_text", strText);

      auto pcontext = m_pcontext->m_pauracontext;

      auto pcontextimage = pcontext->context_image();

      m_pimageLogo = pcontextimage->load_image("matter://main/logo.png", { .cache = false });

      m_pfontTitle.create(this);

      auto psystem = m_psystem->m_pbasesystem;

      auto pnode = psystem->node();

      m_pfontTitle->create_point_font(pnode->font_name(e_font_sans_ui), 14, 800);

      m_pfont.create(this);

      m_pfont->create_point_font(pnode->font_name(e_font_sans_ui), 14, 400);

      if (get_typed_parent<::user::split_impact>() != nullptr)
      {

         if (get_typed_parent<::user::split_impact>()->get_child_by_id("top_edit_impact") != nullptr)
         {

            auto pinteraction = get_typed_parent<::user::split_impact>()->get_child_by_id("top_edit_impact");

            pinteraction->_001SetText(strText, ::e_source_initialize);

         }

      }

   }


   void menu_impact::on_message_destroy(::message::message * pmessage)
   {

   }


   void menu_impact::handle(::topic * ptopic, ::context * pcontext)
   {

      ::user::impact::handle(ptopic, pcontext);

      if (ptopic)
      {

         if (ptopic->m_atom == id_after_change_text)
         {

            auto peditimpact = _001TypedWindow < ::user::plain_edit_impact >();

            if (peditimpact != nullptr && ptopic->m_puserelement == peditimpact)
            {

               string strText;

               peditimpact->_001GetText(strText);

            }

         }

      }

   }


   bool menu_impact::get_item_rect(index i, RECTANGLE_I32 * prectangle)
   {

      int iHeight = (int) ( m_pfontTitle->m_dFontSize * 1.25 + 20);

      int x = 10;

      int y = 10;

      y += m_pimageLogo->height();

      y += 10;

      ::rectangle_i32 rectangleClient;

      get_client_rect(rectangleClient);

      int w = rectangleClient.width() - x * 2;

      int k = 0;

      int iSep = 0;

      for (int j = 0; j < m_iaPopup.get_count(); j++)
      {

         if (i < k + m_iaPopup[j])
         {

            break;

         }

         k += m_iaPopup[j];

         iSep++;
      }

      prectangle->top = (::i32)( y + (i + iSep) * iHeight);

      prectangle->bottom = prectangle->top + iHeight;

      prectangle->left = x;

      prectangle->right = x + w;


      return true;

   }


   ::item_pointer menu_impact::on_hit_test(const ::point_i32 &point)
   {

      index iPos = 0;

      ::rectangle_i32 rectangle;

      xml::node * pnodeMain = m_pxmldoc->get_child_at("menubar", 0, 1);

      if (pnodeMain->get_children_count("menubar") <= 0)
      {

         pnodeMain = m_pxmldoc;

      }

      for (::index iMenu = 0; iMenu < pnodeMain->get_children_count("menubar"); iMenu++)
      {

         xml::node * pnode = pnodeMain->get_child_at("menubar", iMenu, 1);

         ::index iCommand = -1;

         get_item_rect(iPos, rectangle);

         if (rectangle.contains(point))
         {

            return __new(::item(::e_element_item, iPos, iMenu, -1));

         }

         iPos++;

         for (iCommand = 0; iCommand < pnode->get_children_count(); iCommand++)
         {

            get_item_rect(iPos, rectangle);

            if (rectangle.contains(point))
            {

               return __new(::item(::e_element_item, iPos, iMenu, iCommand));

            }

            iPos++;

         }

      }

      auto pitemNone = __new(::item(e_element_none));

      return pitemNone;

   }


   void menu_impact::_001OnDraw(::draw2d::graphics_pointer & pgraphicsParam)
   {

      ::image_pointer pimage1;

      __defer_construct(m_pimageMem);

      pimage1 = m_pimageMem;

      ::rectangle_i32 rectangleClient;

      get_client_rect(rectangleClient);

      if (rectangleClient.area() <= 0)
      {

         return;

      }

      pimage1->create(rectangleClient.size());

      ::draw2d::graphics_pointer pgraphics = pimage1->get_graphics();

      if (is_window_enabled())
      {

         pimage1->fill_byte(255);

      }
      else
      {

         pimage1->fill(255, 200, 200, 200);

      }

      pgraphics->set_interpolation_mode(::draw2d::e_interpolation_mode_high_quality_bicubic);

      image_source imagesource(m_pimageLogo);

      image_drawing_options imagedrawingoptions(m_pimageLogo->rectangle({ 10, 10 }));

      image_drawing imagedrawing(imagedrawingoptions, imagesource);

      pgraphics->draw(imagedrawing);

      ::rectangle_i32 rectangle;

      rectangle_i32_array raMenu;

      int iPos = 0;

      xml::node * pnodeMain = m_pxmldoc->get_child_at("menubar", 0, 1);

      if (pnodeMain->get_children_count("menubar") <= 0)
      {

         pnodeMain = m_pxmldoc;

      }

      for (int i = 0; i < pnodeMain->get_children_count("menubar"); i++)
      {

         ::rectangle_i32 rMenu;

         xml::node * pnode = pnodeMain->get_child_at("menubar", i, 1);

         string strTitle;
         
         strTitle = pnode->attribute("title");

         pgraphics->set(m_pfontTitle);

         get_item_rect(iPos, rMenu);

         pgraphics->set(m_ppen);

         draw_header_rectangle(pgraphics, rMenu);

         pgraphics->set_text_color(argb(255, 0, 0, 0));

         pgraphics->text_out(rMenu.left + 10, rMenu.top + 5, strTitle);

         iPos++;

         for (int j = 0; j < pnode->get_children_count(); j++)
         {

            xml::node * pnodeItem = pnode->child_at(j);

            if (pnodeItem->get_name() == "item")
            {

               string strItem;

               strItem = pnodeItem->get_value();

               get_item_rect(iPos, rectangle);

               rMenu.unite(rMenu, rectangle);

               pgraphics->set(m_ppen);

               ::item item(::e_element_item, iPos, i, j);

               if (::is_set(m_pitemHover) && *m_pitemHover == item)
               {

                  if (::is_set(m_pitemCurrent) && *m_pitemCurrent == item)
                  {

                     pgraphics->set(m_pbrushBkHoverSel);

                     draw_item_rectangle_hover_sel001(pgraphics, rectangle);

                  }
                  else
                  {

                     pgraphics->set(m_pbrushBkSel);

                     draw_item_rectangle_hover001(pgraphics, rectangle);

                  }

               }
               else if (::is_set(m_pitemCurrent) && *m_pitemCurrent == item)
               {

                  pgraphics->set(m_pbrushBkSel);

                  draw_item_rectangle_sel001(pgraphics, rectangle);

               }
               else
               {

                  draw_item_rectangle(pgraphics, rectangle);

               }

               pgraphics->set(m_pfont);

               if (::is_set(m_pitemCurrent) && *m_pitemCurrent == item)
               {

                  pgraphics->set_text_color(argb(255, 0, 148, 202));

               }
               else
               {

                  pgraphics->set_text_color(argb(255, 60, 60, 60));

               }

               pgraphics->text_out(rectangle.left + 10, rectangle.top + 5, strItem);

               pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

               ::image_pointer pimage1;

               if (::is_set(m_pitemCurrent) && *m_pitemCurrent == item)
               {

                  pgraphics->set(m_ppenBkSel);

                  pgraphics->set_current_point(rectangle.left + 1, rectangle.top);
                  pgraphics->line_to(rectangle.left + 1, rectangle.bottom - 1);

                  pimage1 = m_pimageMap[pnodeItem->attribute("id").atom()];

               }
               else
               {

                  pimage1 = m_pimageMapGray[pnodeItem->attribute("id").atom()];

               }

               if (pimage1->is_set())
               {

                  ::rectangle_i32 rectangleDib;

                  rectangleDib.left = rectangle.right - pimage1->width() - 10;
                  rectangleDib.top = rectangle.top + (rectangle.height() - pimage1->height()) / 2;
                  rectangleDib.set_size(pimage1->width(), pimage1->height());

                  image_source imagesource(pimage1);

                  image_drawing_options imagedrawingoptions(rectangleDib);

                  image_drawing imagedrawing(imagedrawingoptions, imagesource);

                  pgraphics->draw(imagedrawing);

               }

               iPos++;

            }

         }

         raMenu.add(rMenu);

      }

      iPos = 0;

      for (int i = 0; i < pnodeMain->get_children_count("menubar"); i++)
      {

         xml::node * pnode = pnodeMain->get_child_at("menubar", i, 1);

         get_item_rect(iPos, rectangle);

         pgraphics->set(m_ppen);

         draw_header_separator(pgraphics, rectangle.bottom_left(), rectangle.bottom_right());

         iPos++;

         for (int j = 0; j < pnode->get_children_count() - 1; j++)
         {

            xml::node * pnodeItem = pnode->child_at(j);

            if (pnodeItem->get_name() == "item")
            {

               string strItem;

               strItem = pnodeItem->get_value();

               get_item_rect(iPos, rectangle);

               draw_item_separator(pgraphics, rectangle.bottom_left(), rectangle.bottom_right());

               iPos++;

            }

         }

         iPos++;

      }

      for (int i = 0; i < pnodeMain->get_children_count("menubar"); i++)
      {

         draw_border_rectangle(pgraphics, raMenu[i]);

      }

      if (!is_window_enabled())
      {

         pimage1->saturation(0.0);

      }

      {

         image_source imagesource(pimage1);

         image_drawing_options imagedrawingoptions(rectangleClient);

         image_drawing imagedrawing(imagedrawingoptions, imagesource);

         pgraphicsParam->draw(imagedrawing);

      }

   }


   ::user::document * menu_impact::get_document()
   {

      return  (::user::impact::get_document());

   }


   void menu_impact::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

      ::rectangle_i32 rectangleClient;

      get_client_rect(rectangleClient);

      if (rectangleClient.area() <= 0)
         return;

   }


   bool menu_impact::load_xml(::payload payloadFile)
   {

      auto pcontext = get_context();

      string strXml = pcontext->m_papexcontext->file().as_string(payloadFile);

      try
      {

         m_pxmldoc->load(strXml);

      }
      catch (const ::exception & exception)
      {

         auto psequencer = exception_message_sequencer(exception);

         psequencer->do_asynchronously();

         return false;

      }

      int iPos = 0;

      ::rectangle_i32 rectangle;

      int iMenu;

      int iCommand;

//      auto papp = get_app();

      xml::node * pnodeMain = m_pxmldoc->get_child_at("menubar", 0, 1);

      if (pnodeMain->get_children_count("menubar") <= 0)
      {

         pnodeMain = m_pxmldoc;

      }

      m_iaPopup.erase_all();

      for (iMenu = 0; iMenu < pnodeMain->get_children_count("menubar"); iMenu++)
      {

         xml::node * pnode = pnodeMain->get_child_at("menubar", iMenu, 1);

         m_iaPopup.add((const int)pnode->get_children_count() + 1);

         iPos++;

         for (iCommand = 0; iCommand < pnode->get_children_count(); iCommand++)
         {

            get_item_rect(iPos, rectangle);

            auto pcontext = m_pcontext->m_pauracontext;

            auto pcontextimage = pcontext->context_image();

            ::image_pointer pimage1 = pcontextimage->load_image(pnode->child_at(iCommand)->attribute("image"), { .cache = false });

            if (pimage1)
            {

               m_pimageMap[pnode->child_at(iCommand)->attribute("id").atom()] = pimage1;

               ::image_pointer pimageGray;

               pimageGray = pimage1->clone();

               //pimageGray->from(pimage1);

               pimageGray->saturation(0.0);

               m_pimageMapGray[pnode->child_at(iCommand)->attribute("id").atom()] = pimageGray;

            }



            iPos++;

         }

      }

      return true;

   }


   void menu_impact::draw_border_rectangle(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectangle)
   {

      pgraphics->set_current_point(rectangle.left, rectangle.top);

      pgraphics->line_to(rectangle.right, rectangle.top);

      pgraphics->set_current_point(rectangle.left, rectangle.bottom);

      pgraphics->line_to(rectangle.right, rectangle.bottom);

   }


   void menu_impact::draw_header_separator(::draw2d::graphics_pointer & pgraphics, const ::point_i32& point1, const ::point_i32& point2)
   {

      pgraphics->set_current_point(point1);
      pgraphics->line_to(point2);

   }


   void menu_impact::draw_header_rectangle(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectangle)
   {

      pgraphics->fill_rectangle(rectangle, argb(255, 240, 240, 240));

      pgraphics->set_current_point(rectangle.left, rectangle.top);

      pgraphics->line_to(rectangle.left, rectangle.bottom);

      pgraphics->set_current_point(rectangle.right, rectangle.top);

      pgraphics->line_to(rectangle.right, rectangle.bottom);




   }


   void menu_impact::draw_item_rectangle(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectangle)
   {

      pgraphics->set_current_point(rectangle.left, rectangle.top);

      pgraphics->line_to(rectangle.left, rectangle.bottom);

      pgraphics->set_current_point(rectangle.right, rectangle.top);

      pgraphics->line_to(rectangle.right, rectangle.bottom);


   }


   void menu_impact::draw_item_rectangle_hover001(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectangle)
   {

      pgraphics->fill_rectangle(rectangle);


      pgraphics->set_current_point(rectangle.left, rectangle.top);

      pgraphics->line_to(rectangle.left, rectangle.bottom);



      pgraphics->set_current_point(rectangle.right, rectangle.top);

      pgraphics->line_to(rectangle.right, rectangle.bottom);


   }


   void menu_impact::draw_item_rectangle_sel001(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectangle)
   {

      pgraphics->fill_rectangle(rectangle);

      pgraphics->set_current_point(rectangle.left, rectangle.top);

      pgraphics->line_to(rectangle.left, rectangle.bottom);

      pgraphics->set_current_point(rectangle.right, rectangle.bottom - 1);

      int h = ::height(rectangle);

      point_f64_array pta;
      pta.add(rectangle.right, rectangle.bottom - h / 3 - 2);

      pta.add(rectangle.right + h * 3 / 16, rectangle.bottom - h / 2 - 2);

      pta.add(rectangle.right, rectangle.bottom - h * 2 / 3 - 2);

      pgraphics->fill_polygon(pta);
      pgraphics->line_to(rectangle.right, rectangle.bottom - h / 3 - 2);

      pgraphics->line_to(rectangle.right + h * 3 / 16, rectangle.bottom - h / 2 - 2);

      pgraphics->line_to(rectangle.right, rectangle.bottom - h * 2 / 3 - 2);

      pgraphics->line_to(rectangle.right, rectangle.top);

   }

   void menu_impact::draw_item_rectangle_hover_sel001(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectangle)
   {

      pgraphics->fill_rectangle(rectangle);

      pgraphics->set_current_point(rectangle.left, rectangle.top);

      pgraphics->line_to(rectangle.left, rectangle.bottom);

      pgraphics->set_current_point(rectangle.right, rectangle.bottom - 1);

      int h = ::height(rectangle);

      point_f64_array pta;
      pta.add(rectangle.right, rectangle.bottom - h / 3 - 2);

      pta.add(rectangle.right + h * 3 / 16, rectangle.bottom - h / 2 - 2);

      pta.add(rectangle.right, rectangle.bottom - h * 2 / 3 - 2);

      pgraphics->fill_polygon(pta);
      pgraphics->line_to(rectangle.right, rectangle.bottom - h / 3 - 2);

      pgraphics->line_to(rectangle.right + h * 3 / 16, rectangle.bottom - h / 2 - 2);

      pgraphics->line_to(rectangle.right, rectangle.bottom - h * 2 / 3 - 2);


      pgraphics->line_to(rectangle.right, rectangle.top);


   }


   void menu_impact::draw_item_separator(::draw2d::graphics_pointer & pgraphics, const ::point_i32 & point1, const ::point_i32 & point2)
   {

      pgraphics->set_current_point(point1);
      pgraphics->line_to(point2);
   }


} // namespace user


