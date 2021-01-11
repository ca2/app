#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "base/user/user/_user.h"
#endif
#include "aura/update.h"
#include "aqua/xml.h"
#include "menu_view.h"


namespace user
{


   menu_view::menu_view() :
      m_brBkSel(e_create),
      m_brBkHoverSel(e_create),
      m_penBkSel(e_create),
      m_pen(e_create)
   {

      value(FONTSEL_IMPACT) = true;

      m_flagNonClient.remove(non_client_background);

      m_flagNonClient.remove(non_client_focus_rect);

      m_brBkHoverSel->create_solid(ARGB(255, 230, 230, 230));

      m_brBkSel->create_solid(ARGB(255, 240, 240, 240));

      m_penBkSel->create_solid(3.0, ARGB(255, 0, 148, 202));

      m_pen->create_solid(1.0, ARGB(255, 210, 210, 210));

   }


   menu_view::~menu_view()
   {

   }


   void menu_view::assert_valid() const
   {

      ::user::impact::assert_valid();

   }


   void menu_view::dump(dump_context & dumpcontext) const
   {

      ::user::impact::dump(dumpcontext);

   }


   void menu_view::install_message_routing(::channel * pchannel)
   {

      ::user::impact::install_message_routing(pchannel);

      install_simple_ui_default_mouse_handling(pchannel);

      MESSAGE_LINK(e_message_create, pchannel, this, &menu_view::_001OnCreate);
      MESSAGE_LINK(e_message_destroy, pchannel, this, &menu_view::_001OnDestroy);

   }




   bool menu_view::on_click(const ::user::item & item)
   {

      if (!is_window_enabled())
      {

         return false;

      }

      //auto point = item.m_pointHitTest;

      auto itemHit = item;

      ::id idCommand;

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

               idCommand = pnodeItem->attribute("id").get_id();

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

         ::user::command command;

         command.m_id = idCommand;

         route_command_message(&command);

         return command.m_bRet;

      }

      return false;

   }


   void menu_view::_001OnCreate(::message::message * pmessage)
   {

      __pointer(::message::create) pcreate(pmessage);

      pcreate->previous();

      if (pcreate->m_bRet)
         return;

      auto estatus = __compose_new(m_pxmldoc);

      if (!estatus)
      {

         pcreate->failed("Failed to create new xml document for menu view");

         return;

      }


      set_topic_text("menu_view> ");

      string strId = get_document()->m_pimpactsystem->m_strMatter;

      string strText;

      Application.data_get(m_id + ".cur_text", strText);

      m_pimageLogo = Application.image().load_image("matter://main/logo.png", false);

      m_fontTitle.create(this);

      m_fontTitle->create_point_font(os_font_name(e_font_sans_ui), 14, 800);

      m_font.create(this);

      m_font->create_point_font(os_font_name(e_font_sans_ui), 14, 400);

      if (GetTypedParent<::user::split_view>() != nullptr)
      {

         if (GetTypedParent<::user::split_view>()->get_child_by_id("top_edit_view") != nullptr)
         {

            auto pinteraction = GetTypedParent<::user::split_view>()->get_child_by_id("top_edit_view");

            pinteraction->_001SetText(strText, ::e_source_initialize);

         }

      }

   }


   void menu_view::_001OnDestroy(::message::message * pmessage)
   {

   }


   void menu_view::on_subject(::promise::subject * psubject, ::promise::context * pcontext)
   {

      ::user::impact::process(psubject);

      if (psubject->id() == id_after_change_text)
      {

         auto peditview = _001TypedWindow < ::user::plain_edit_view >();

         if (peditview != nullptr && psubject->m_puserinteraction == peditview)
         {

            string strText;

            peditview->_001GetText(strText);

         }

      }

   }


   bool menu_view::get_item_rect(index i, RECT32 * prect)
   {

      int iHeight = (int) ( m_fontTitle->m_dFontSize * 1.25 + 20);

      int x = 10;

      int y = 10;

      y += m_pimageLogo->height();

      y += 10;

      ::rect rectClient;

      get_client_rect(rectClient);

      int w = rectClient.width() - x * 2;

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

      prect->top = (::i32)( y + (i + iSep) * iHeight);

      prect->bottom = prect->top + iHeight;

      prect->left = x;

      prect->right = x + w;


      return true;

   }


   void menu_view::on_hit_test(::user::item & item)
   {

      index iPos = 0;

      ::rect rect;

      xml::node * pnodeMain = m_pxmldoc->get_child_at("menubar", 0, 1);

      if (pnodeMain->get_children_count("menubar") <= 0)
      {

         pnodeMain = m_pxmldoc;

      }

      for (::index iMenu = 0; iMenu < pnodeMain->get_children_count("menubar"); iMenu++)
      {

         xml::node * pnode = pnodeMain->get_child_at("menubar", iMenu, 1);

         ::index iCommand = -1;

         get_item_rect(iPos, rect);

         if (rect.contains(item.m_pointHitTest))
         {

            item = { ::user::e_element_item, iPos, iMenu, -1 };

            return;

         }

         iPos++;

         for (iCommand = 0; iCommand < pnode->get_children_count(); iCommand++)
         {

            get_item_rect(iPos, rect);

            if (rect.contains(item.m_pointHitTest))
            {

               item = { ::user::e_element_item, iPos, iMenu, iCommand };

               return;

            }

            iPos++;

         }

      }

      item = ::user::e_element_none;

   }


   void menu_view::_001OnDraw(::draw2d::graphics_pointer & pgraphicsParam)
   {

      ::image_pointer pimage1;

      if (!m_pimageMem)
      {

         m_pimageMem.create();

      }

      pimage1 = m_pimageMem;

      ::rect rectClient;

      get_client_rect(rectClient);

      if (rectClient.area() <= 0)
      {

         return;

      }

      pimage1->create(rectClient.size());

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

      pgraphics->stretch(m_pimageLogo->rect({ 10, 10 }), m_pimageLogo->get_graphics());

      ::rect rect;

      rect_array raMenu;

      int iPos = 0;

      xml::node * pnodeMain = m_pxmldoc->get_child_at("menubar", 0, 1);

      if (pnodeMain->get_children_count("menubar") <= 0)
      {

         pnodeMain = m_pxmldoc;

      }

      for (int i = 0; i < pnodeMain->get_children_count("menubar"); i++)
      {

         ::rect rMenu;

         xml::node * pnode = pnodeMain->get_child_at("menubar", i, 1);

         string strTitle = pnode->attribute("title");

         pgraphics->set(m_fontTitle);

         get_item_rect(iPos, rMenu);

         pgraphics->set(m_pen);

         draw_header_rectangle(pgraphics, rMenu);

         pgraphics->set_text_color(ARGB(255, 0, 0, 0));

         pgraphics->text_out(rMenu.left + 10, rMenu.top + 5, strTitle);

         iPos++;

         for (int j = 0; j < pnode->get_children_count(); j++)
         {

            xml::node * pnodeItem = pnode->child_at(j);

            if (pnodeItem->get_name() == "item")
            {

               string strItem;

               strItem = pnodeItem->get_value();

               get_item_rect(iPos, rect);

               rMenu.unite(rMenu, rect);

               pgraphics->set(m_pen);

               ::user::item item(::user::e_element_item, iPos, i, j);

               if (m_itemHover == item)
               {

                  if (m_itemCurrent == item)
                  {

                     pgraphics->set(m_brBkHoverSel);

                     draw_item_rectangle_hover_sel001(pgraphics, rect);

                  }
                  else
                  {

                     pgraphics->set(m_brBkSel);

                     draw_item_rectangle_hover001(pgraphics, rect);

                  }

               }
               else if (m_itemCurrent == item)
               {

                  pgraphics->set(m_brBkSel);

                  draw_item_rectangle_sel001(pgraphics, rect);

               }
               else
               {

                  draw_item_rectangle(pgraphics, rect);

               }

               pgraphics->set(m_font);

               if (m_itemCurrent == item)
               {

                  pgraphics->set_text_color(ARGB(255, 0, 148, 202));

               }
               else
               {

                  pgraphics->set_text_color(ARGB(255, 60, 60, 60));

               }

               pgraphics->text_out(rect.left + 10, rect.top + 5, strItem);

               pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

               ::image_pointer pimage1;

               if (m_itemCurrent == item)
               {

                  pgraphics->set(m_penBkSel);

                  pgraphics->move_to(rect.left + 1, rect.top);
                  pgraphics->line_to(rect.left + 1, rect.bottom - 1);

                  pimage1 = m_pimageMap[pnodeItem->attribute("id")];

               }
               else
               {

                  pimage1 = m_pimageMapGray[pnodeItem->attribute("id")];

               }

               if (pimage1->is_set())
               {

                  ::rect rectDib;

                  rectDib.left = rect.right - pimage1->width() - 10;
                  rectDib.top = rect.top + (rect.height() - pimage1->height()) / 2;
                  rectDib.set_size(pimage1->width(), pimage1->height());

                  pgraphics->stretch(rectDib, pimage1->g());

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

         get_item_rect(iPos, rect);

         pgraphics->set(m_pen);

         draw_header_separator(pgraphics, rect.bottom_left(), rect.bottom_right());

         iPos++;

         for (int j = 0; j < pnode->get_children_count() - 1; j++)
         {

            xml::node * pnodeItem = pnode->child_at(j);

            if (pnodeItem->get_name() == "item")
            {

               string strItem;

               strItem = pnodeItem->get_value();

               get_item_rect(iPos, rect);

               draw_item_separator(pgraphics, rect.bottom_left(), rect.bottom_right());

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

      pgraphicsParam->stretch(rectClient, pimage1->get_graphics());

   }


   ::user::document * menu_view::get_document()
   {

      return  (::user::impact::get_document());

   }


   void menu_view::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

      ::rect rectClient;

      get_client_rect(rectClient);

      if (rectClient.area() <= 0)
         return;

   }


   bool menu_view::load_xml(payload varFile)
   {

      string str = Context.file().as_string(varFile);

      if (!m_pxmldoc->load(str))
      {

         return false;

      }


      int iPos = 0;

      ::rect rect;

      int iMenu;

      int iCommand;

      xml::node * pnodeMain = m_pxmldoc->get_child_at("menubar", 0, 1);

      if (pnodeMain->get_children_count("menubar") <= 0)
      {

         pnodeMain = m_pxmldoc;

      }

      m_iaPopup.remove_all();

      for (iMenu = 0; iMenu < pnodeMain->get_children_count("menubar"); iMenu++)
      {

         xml::node * pnode = pnodeMain->get_child_at("menubar", iMenu, 1);

         m_iaPopup.add((const int)pnode->get_children_count() + 1);

         iPos++;

         for (iCommand = 0; iCommand < pnode->get_children_count(); iCommand++)
         {

            get_item_rect(iPos, rect);

            ::image_pointer pimage1 = Application.image().load_image(pnode->child_at(iCommand)->attribute("image"), false);

            if (pimage1)
            {

               m_pimageMap[pnode->child_at(iCommand)->attribute("id")] = pimage1;

               ::image_pointer pimageGray;

               pimageGray = pimage1->clone();

               //pimageGray->from(pimage1);

               pimageGray->saturation(0.0);

               m_pimageMapGray[pnode->child_at(iCommand)->attribute("id")] = pimageGray;

            }



            iPos++;

         }

      }

      return true;

   }


   void menu_view::draw_border_rectangle(::draw2d::graphics_pointer & pgraphics, const ::rect & rect)
   {

      pgraphics->move_to(rect.left, rect.top);

      pgraphics->line_to(rect.right, rect.top);

      pgraphics->move_to(rect.left, rect.bottom);

      pgraphics->line_to(rect.right, rect.bottom);

   }


   void menu_view::draw_header_separator(::draw2d::graphics_pointer & pgraphics, const ::point& point1, const ::point& point2)
   {

      pgraphics->move_to(point1);
      pgraphics->line_to(point2);

   }


   void menu_view::draw_header_rectangle(::draw2d::graphics_pointer & pgraphics, const ::rect & rect)
   {

      pgraphics->fill_rect(rect, ARGB(255, 240, 240, 240));

      pgraphics->move_to(rect.left, rect.top);

      pgraphics->line_to(rect.left, rect.bottom);

      pgraphics->move_to(rect.right, rect.top);

      pgraphics->line_to(rect.right, rect.bottom);




   }


   void menu_view::draw_item_rectangle(::draw2d::graphics_pointer & pgraphics, const ::rect & rect)
   {

      pgraphics->move_to(rect.left, rect.top);

      pgraphics->line_to(rect.left, rect.bottom);

      pgraphics->move_to(rect.right, rect.top);

      pgraphics->line_to(rect.right, rect.bottom);


   }


   void menu_view::draw_item_rectangle_hover001(::draw2d::graphics_pointer & pgraphics, const ::rect & rect)
   {

      pgraphics->fill_rect(rect);


      pgraphics->move_to(rect.left, rect.top);

      pgraphics->line_to(rect.left, rect.bottom);



      pgraphics->move_to(rect.right, rect.top);

      pgraphics->line_to(rect.right, rect.bottom);


   }


   void menu_view::draw_item_rectangle_sel001(::draw2d::graphics_pointer & pgraphics, const ::rect & rect)
   {

      pgraphics->fill_rect(rect);

      pgraphics->move_to(rect.left, rect.top);

      pgraphics->line_to(rect.left, rect.bottom);

      pgraphics->move_to(rect.right, rect.bottom - 1);

      int h = ::height(rect);

      point_array pta;
      pta.add(rect.right, rect.bottom - h / 3 - 2);

      pta.add(rect.right + h * 3 / 16, rect.bottom - h / 2 - 2);

      pta.add(rect.right, rect.bottom - h * 2 / 3 - 2);

      pgraphics->fill_polygon(pta);
      pgraphics->line_to(rect.right, rect.bottom - h / 3 - 2);

      pgraphics->line_to(rect.right + h * 3 / 16, rect.bottom - h / 2 - 2);

      pgraphics->line_to(rect.right, rect.bottom - h * 2 / 3 - 2);

      pgraphics->line_to(rect.right, rect.top);

   }

   void menu_view::draw_item_rectangle_hover_sel001(::draw2d::graphics_pointer & pgraphics, const ::rect & rect)
   {

      pgraphics->fill_rect(rect);

      pgraphics->move_to(rect.left, rect.top);

      pgraphics->line_to(rect.left, rect.bottom);

      pgraphics->move_to(rect.right, rect.bottom - 1);

      int h = ::height(rect);

      point_array pta;
      pta.add(rect.right, rect.bottom - h / 3 - 2);

      pta.add(rect.right + h * 3 / 16, rect.bottom - h / 2 - 2);

      pta.add(rect.right, rect.bottom - h * 2 / 3 - 2);

      pgraphics->fill_polygon(pta);
      pgraphics->line_to(rect.right, rect.bottom - h / 3 - 2);

      pgraphics->line_to(rect.right + h * 3 / 16, rect.bottom - h / 2 - 2);

      pgraphics->line_to(rect.right, rect.bottom - h * 2 / 3 - 2);


      pgraphics->line_to(rect.right, rect.top);


   }


   void menu_view::draw_item_separator(::draw2d::graphics_pointer & pgraphics, const ::point & point1, const ::point & point2)
   {

      pgraphics->move_to(point1);
      pgraphics->line_to(point2);
   }


} // namespace user


