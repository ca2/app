#include "framework.h"
#include "base/user/user/_user.h"
#include "aura/update.h"
#include "aqua/xml.h"
#include "menu_view.h"
#include "aura/graphics/draw2d/_draw2d.h"


namespace user
{


   menu_view::menu_view() 
   {

      m_bClickDefaultMouseHandling = true;

      payload(FONTSEL_IMPACT) = true;

      m_flagNonClient.erase(non_client_background);

      m_flagNonClient.erase(non_client_focus_rect);

      m_pbrushBkHoverSel->create_solid(argb(255, 230, 230, 230));

      m_pbrushBkSel->create_solid(argb(255, 240, 240, 240));

      m_ppenBkSel->create_solid(3.0, argb(255, 0, 148, 202));

      m_ppen->create_solid(1.0, argb(255, 210, 210, 210));

   }


   menu_view::~menu_view()
   {

   }


   void menu_view::assert_ok() const
   {

      ::user::impact::assert_ok();

   }


   void menu_view::dump(dump_context & dumpcontext) const
   {

      ::user::impact::dump(dumpcontext);

   }


   void menu_view::install_message_routing(::channel * pchannel)
   {

      ::user::impact::install_message_routing(pchannel);

      //install_click_default_mouse_handling(pchannel);

      MESSAGE_LINK(e_message_create, pchannel, this, &menu_view::on_message_create);
      MESSAGE_LINK(e_message_destroy, pchannel, this, &menu_view::on_message_destroy);

   }


   bool menu_view::on_click(const ::item & item)
   {

      if (!is_window_enabled())
      {

         return false;

      }

      //auto point = item.m_pointHitTest;

      auto itemHit = item;

      ::atom idCommand;

      if (itemHit.menu_view_command() >= 0)
      {

         xml::node * pnodeMain = m_pxmldoc->get_child_at("menubar", 0, 1);

         if (pnodeMain->get_children_count("menubar") <= 0)
         {

            pnodeMain = m_pxmldoc;

         }

         xml::node * pnode = pnodeMain->get_child_at("menubar", itemHit.menu_view_group(), 1);

         if (pnode != nullptr)
         {

            xml::node * pnodeItem = pnode->child_at(itemHit.menu_view_command());

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

      m_itemCurrent = itemHit;

      set_need_redraw();

      if (!idCommand.is_empty())
      {

         ::message::command command;

         command.m_atom = idCommand;

         route_command(&command);

         return command.m_bRet;

      }

      return false;

   }


   void menu_view::on_message_create(::message::message * pmessage)
   {

      m_pbrushBkSel.create(this);
      m_pbrushBkHoverSel.create(this);
      m_ppenBkSel.create(this);
      m_ppen.create(this);

      __pointer(::message::create) pcreate(pmessage);

      pcreate->previous();

      if (pcreate->m_bRet)
         return;

      //auto estatus = 
      
      __compose_new(m_pxmldoc);

      //if (!estatus)
      //{

      //   pcreate->failed("Failed to create new xml document for menu impact");

      //   return;

      //}

      //set_topic_text("menu_view> ");

      auto atom = get_document()->m_pimpactsystem->m_atom;

      string strText;

      auto papplication = get_application();

      papplication->data_get(m_atom + ".cur_text", strText);

      auto pcontext = m_pcontext->m_pauracontext;

      auto pcontextimage = pcontext->context_image();

      m_pimageLogo = pcontextimage->load_image("matter://main/logo.png", { .cache = false });

      m_pfontTitle.create(this);

      auto psystem = m_psystem->m_pbasesystem;

      auto pnode = psystem->node();

      m_pfontTitle->create_point_font(pnode->font_name(e_font_sans_ui), 14, 800);

      m_pfont.create(this);

      m_pfont->create_point_font(pnode->font_name(e_font_sans_ui), 14, 400);

      if (GetTypedParent<::user::split_view>() != nullptr)
      {

         if (GetTypedParent<::user::split_view>()->get_child_by_id("top_edit_view") != nullptr)
         {

            auto pinteraction = GetTypedParent<::user::split_view>()->get_child_by_id("top_edit_view");

            pinteraction->_001SetText(strText, ::e_source_initialize);

         }

      }

   }


   void menu_view::on_message_destroy(::message::message * pmessage)
   {

   }


   void menu_view::handle(::topic * ptopic, ::context * pcontext)
   {

      ::user::impact::handle(ptopic, pcontext);

      if (ptopic->m_atom == id_after_change_text)
      {

         auto peditview = _001TypedWindow < ::user::plain_edit_view >();

         if (peditview != nullptr && ptopic->get_extended_topic()->m_puserelement == peditview)
         {

            string strText;

            peditview->_001GetText(strText);

         }

      }

   }


   bool menu_view::get_item_rect(index i, RECTANGLE_I32 * prectangle)
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


   void menu_view::on_hit_test(::item & item)
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

         if (rectangle.contains(item.m_pointHitTest))
         {

            item = ::item(::e_element_item, iPos, iMenu, -1);

            return;

         }

         iPos++;

         for (iCommand = 0; iCommand < pnode->get_children_count(); iCommand++)
         {

            get_item_rect(iPos, rectangle);

            if (rectangle.contains(item.m_pointHitTest))
            {

               item = ::item(::e_element_item, iPos, iMenu, iCommand);

               return;

            }

            iPos++;

         }

      }

      item = ::e_element_none;

   }


   void menu_view::_001OnDraw(::draw2d::graphics_pointer & pgraphicsParam)
   {

      ::image_pointer pimage1;

      __defer_construct_new(m_pimageMem);

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

               if (m_itemHover == item)
               {

                  if (m_itemCurrent == item)
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
               else if (m_itemCurrent == item)
               {

                  pgraphics->set(m_pbrushBkSel);

                  draw_item_rectangle_sel001(pgraphics, rectangle);

               }
               else
               {

                  draw_item_rectangle(pgraphics, rectangle);

               }

               pgraphics->set(m_pfont);

               if (m_itemCurrent == item)
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

               if (m_itemCurrent == item)
               {

                  pgraphics->set(m_ppenBkSel);

                  pgraphics->move_to(rectangle.left + 1, rectangle.top);
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


   ::user::document * menu_view::get_document()
   {

      return  (::user::impact::get_document());

   }


   void menu_view::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

      ::rectangle_i32 rectangleClient;

      get_client_rect(rectangleClient);

      if (rectangleClient.area() <= 0)
         return;

   }


   bool menu_view::load_xml(::payload payloadFile)
   {

      auto pcontext = get_context();

      string str = pcontext->m_papexcontext->file().as_string(payloadFile);

      if (!m_pxmldoc->load(str))
      {

         return false;

      }

      int iPos = 0;

      ::rectangle_i32 rectangle;

      int iMenu;

      int iCommand;

//      auto papplication = get_application();

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


   void menu_view::draw_border_rectangle(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectangle)
   {

      pgraphics->move_to(rectangle.left, rectangle.top);

      pgraphics->line_to(rectangle.right, rectangle.top);

      pgraphics->move_to(rectangle.left, rectangle.bottom);

      pgraphics->line_to(rectangle.right, rectangle.bottom);

   }


   void menu_view::draw_header_separator(::draw2d::graphics_pointer & pgraphics, const ::point_i32& point1, const ::point_i32& point2)
   {

      pgraphics->move_to(point1);
      pgraphics->line_to(point2);

   }


   void menu_view::draw_header_rectangle(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectangle)
   {

      pgraphics->fill_rectangle(rectangle, argb(255, 240, 240, 240));

      pgraphics->move_to(rectangle.left, rectangle.top);

      pgraphics->line_to(rectangle.left, rectangle.bottom);

      pgraphics->move_to(rectangle.right, rectangle.top);

      pgraphics->line_to(rectangle.right, rectangle.bottom);




   }


   void menu_view::draw_item_rectangle(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectangle)
   {

      pgraphics->move_to(rectangle.left, rectangle.top);

      pgraphics->line_to(rectangle.left, rectangle.bottom);

      pgraphics->move_to(rectangle.right, rectangle.top);

      pgraphics->line_to(rectangle.right, rectangle.bottom);


   }


   void menu_view::draw_item_rectangle_hover001(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectangle)
   {

      pgraphics->fill_rectangle(rectangle);


      pgraphics->move_to(rectangle.left, rectangle.top);

      pgraphics->line_to(rectangle.left, rectangle.bottom);



      pgraphics->move_to(rectangle.right, rectangle.top);

      pgraphics->line_to(rectangle.right, rectangle.bottom);


   }


   void menu_view::draw_item_rectangle_sel001(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectangle)
   {

      pgraphics->fill_rectangle(rectangle);

      pgraphics->move_to(rectangle.left, rectangle.top);

      pgraphics->line_to(rectangle.left, rectangle.bottom);

      pgraphics->move_to(rectangle.right, rectangle.bottom - 1);

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

   void menu_view::draw_item_rectangle_hover_sel001(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectangle)
   {

      pgraphics->fill_rectangle(rectangle);

      pgraphics->move_to(rectangle.left, rectangle.top);

      pgraphics->line_to(rectangle.left, rectangle.bottom);

      pgraphics->move_to(rectangle.right, rectangle.bottom - 1);

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


   void menu_view::draw_item_separator(::draw2d::graphics_pointer & pgraphics, const ::point_i32 & point1, const ::point_i32 & point2)
   {

      pgraphics->move_to(point1);
      pgraphics->line_to(point2);
   }


} // namespace user


