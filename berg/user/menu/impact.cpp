#include "framework.h"
#include "impact.h"
#include "acme/handler/item.h"
#include "acme/constant/id.h"
#include "acme/constant/message.h"
#include "acme/handler/topic.h"
//#include "acme/handler/sequence.h"
#include "acme/prototype/geometry2d/_collection.h"
#include "acme/nano/nano.h"
#include "acme/user/micro/user.h"
#include "acme/user/user/content.h"
#include "apex/database/_binary_stream.h"
#include "acme/filesystem/filesystem/file_context.h"
#include "aqua/xml/document.h"
#include "aura/graphics/write_text/font.h"
#include "aura/graphics/draw2d/brush.h"
#include "aura/graphics/draw2d/pen.h"
#include "aura/graphics/draw2d/path.h"
#include "aura/graphics/image/context.h"
#include "aura/graphics/image/drawing.h"
#include "aura/message/user.h"
#include "aura/platform/node.h"
#include "aura/user/user/plain_edit.h"
#include "aura/user/user/system.h"
#include "berg/platform/application.h"
#include "berg/platform/system.h"
#include "berg/user/menu/item.h"
#include "berg/user/menu/item_ptra.h"
#include "berg/user/user/document.h"
#include "berg/user/user/impact_system.h"
#include "berg/user/user/split_impact.h"
#include "berg/user/user/impact_creator.h"


namespace user
{


   menu_impact::menu_impact() 
   {

      m_bDefaultClickHandling = true;

      m_bDefaultParentMouseMessageHandling = true;

      m_flagNonClient.erase(e_non_client_background);

      m_flagNonClient.erase(e_non_client_focus_rect);

   }


   menu_impact::~menu_impact()
   {

   }


//   void menu_impact::assert_ok() const
//   {
//
//      ::user::impact::assert_ok();
//
//   }
//
//
//   void menu_impact::dump(dump_context & dumpcontext) const
//   {
//
//      ::user::impact::dump(dumpcontext);
//
//   }


   void menu_impact::install_message_routing(::channel * pchannel)
   {

      ::user::impact::install_message_routing(pchannel);

      //install_click_default_mouse_handling(pchannel);

      MESSAGE_LINK(e_message_create, pchannel, this, &menu_impact::on_message_create);
      MESSAGE_LINK(e_message_destroy, pchannel, this, &menu_impact::on_message_destroy);

   }


   bool menu_impact::on_click(::item * pitem, ::user::mouse * pmouse)
   {

      if (!is_window_enabled())
      {

         return false;

      }

      ::pointer < ::menu::item > pmenuitem = pitem;

      if (pmenuitem->id().is_empty())
      {

         return false;

      }

      auto pcommand = __initialize_new::message::command(pmenuitem->id(), pmouse->user_activation_token());

      route_command(pcommand);

      return pcommand->m_bRet;

   //}

   //   }

      ////auto point = item.m_pointHitTest;

      //::pointer < ::menu::item > pitemHit = pitem;

      //::atom idCommand;

      ////if (::is_set(pitemHit) && pitemHit->m_item.menu_impact_command() >= 0)
      //if (::is_set(pitemHit) && pitemHit->m_iCommand >= 0)
      //{

      //   xml::node * pnodeMain = m_pxmldoc->get_child_at("menubar", 0, 1);

      //   if (pnodeMain->get_children_count("menubar") <= 0)
      //   {

      //      pnodeMain = m_pxmldoc;

      //   }

      //   xml::node * pnode = pnodeMain->get_child_at("menubar", pitemHit->m_iGroup, 1);

      //   if (pnode != nullptr)
      //   {

      //      xml::node * pnodeItem = pnode->child_at(pitemHit->m_iCommand);

      //      if (pnodeItem != nullptr)
      //      {

      //         idCommand = pnodeItem->attribute("id").as_atom();

      //      }

      //   }

      //}
      //else
      //{

      //   idCommand = "home";

      //}

      //main_content().m_pitemCurrent = pitemHit;

      //set_need_redraw();

      //if (!idCommand.is_empty())
      //{

      //   ::message::command command(idCommand);

      //   route_command(&command);

      //   return command.m_bRet;

      //}

      return true;

   }


   void menu_impact::on_message_create(::message::message * pmessage)
   {

      payload(FONTSEL_IMPACT) = true;

      __øconstruct(m_pbrushBkSel);
      __øconstruct(m_pbrushBkHoverSel);
      __øconstruct(m_ppenBkSel);
      __øconstruct(m_ppen);


      m_pbrushBkHoverSel->create_solid(argb(255, 230, 230, 230));
      m_pbrushBkSel->create_solid(argb(255, 240, 240, 240));
      m_ppenBkSel->create_solid(3.0, argb(255, 0, 148, 202));
      m_ppen->create_solid(1.0, argb(255, 210, 210, 210));


      ::pointer<::message::create>pcreate(pmessage);

      pcreate->previous();

      if (pcreate->m_bRet)
         return;

      //auto estatus = 
      
      //__construct_new(m_pxmldoc);

      //if (!estatus)
      //{

      //   pcreate->failed("Failed to create ___new xml document for menu impact");

      //   return;

      //}

      //set_topic_text("menu_impact> ");

      auto atom = get_document()->m_pimpactsystem->id();

      string strText;

      //auto papp = get_app();

      ::cast < ::database::client > pdatabaseclient = application();

      pdatabaseclient->datastream()->get(id() + ".cur_text", strText);

      m_pimageLogo = image()->load_image("matter://main/logo.png", { .cache = false });

      __øconstruct(m_pfontTitle);

      m_pfontTitle->create_font(e_font_sans_ui, 14_pt, 800);

      __øconstruct(m_pfont);

      m_pfont->create_font(e_font_sans_ui, 14_pt, 400);

      if (get_typed_parent<::user::split_impact>() != nullptr)
      {

         if (get_typed_parent<::user::split_impact>()->get_child_by_id("top_edit_impact") != nullptr)
         {

            auto pinteraction = get_typed_parent<::user::split_impact>()->get_child_by_id("top_edit_impact");

            pinteraction->set_text(strText, ::e_source_initialize);

         }

      }

   }


   void menu_impact::on_message_destroy(::message::message * pmessage)
   {

   }


   void menu_impact::handle(::topic * ptopic, ::handler_context * phandlercontext)
   {

      ::user::impact::handle(ptopic, phandlercontext);

      if (ptopic)
      {

         if (ptopic->id() == id_after_change_text)
         {

            auto peditimpact = _001TypedWindow < ::user::plain_edit_impact >();

            if (peditimpact != nullptr && ptopic->m_puserelement == peditimpact)
            {

               string strText;

               strText = peditimpact->as_text();

            }

         }

      }

   }


   ::user::item * menu_impact::layout_user_item_by_index(::collection::index iMenuItemIndex)
   {

      //::status < ::int_rectangle > rectangleMenuItem;

      int iHeight = (int) ( m_pfontTitle->m_fontsize.as_double() * 1.25 + 20);

      int x = 10;

      int y = 10;

      y += m_pimageLogo->height();

      y += 10;

      auto rectangleX = this->rectangle();

      int w = rectangleX.width() - x * 2;

      int iPos = 0;

      int iSep = 0;

      ::pointer < ::menu::item > pmenuitem;

      for (int i = 0; i < m_pmenuitem->m_pmenuitema->get_count(); i++)
      {

         if (iMenuItemIndex == iPos)
         {

            pmenuitem = (*m_pmenuitem->m_pmenuitema)[i];

            break;

         }

         iPos++;

         for (int j = 0; j < (*m_pmenuitem->m_pmenuitema)[i]->m_pmenuitema->get_count(); j++)
         {

            if (iMenuItemIndex == iPos)
            {

               pmenuitem = (*(*m_pmenuitem->m_pmenuitema)[i]->m_pmenuitema)[j];

               break;

            }

            iPos++;

         }

         if (pmenuitem)
         {

            break;

         }

         iSep++;

      }

      auto puseritem = user_item(pmenuitem);

      puseritem->m_rectangle2.top() = (int)( y + (iMenuItemIndex + iSep) * iHeight);

      puseritem->m_rectangle2.bottom() = puseritem->m_rectangle2.top() + iHeight;

      puseritem->m_rectangle2.left() = x;

      puseritem->m_rectangle2.right() = x + w;

      return puseritem;

   }


   ::item_pointer menu_impact::on_hit_test(const ::int_point &point, ::user::e_zorder ezorder)
   {

      //index iPos = 0;

      ::status < ::int_rectangle > statusrectangle;

      for (int i = 0; i < m_pmenuitem->m_pmenuitema->get_count(); i++)
      {

         auto pmenuitemPopup = m_pmenuitem->m_pmenuitema->element_at(i);

         auto puseritemPopup = user_item(pmenuitemPopup);

         if (puseritemPopup->m_rectangle2.contains(point))
         {

            return pmenuitemPopup;

         }

         for (int j = 0; j < pmenuitemPopup->m_pmenuitema->get_count(); j++)
         {

            auto pmenuitem = pmenuitemPopup->m_pmenuitema->element_at(j);

            auto puseritem = user_item(pmenuitem);

            if (puseritem->m_rectangle2.contains(point))
            {

               return pmenuitem;

            }

         }

      }

      return nullptr;

   }


   void menu_impact::_001OnDraw(::draw2d::graphics_pointer & pgraphicsParam)
   {

      ::image::image_pointer pimage1;

      __defer_construct(m_pimageMem);

      pimage1 = m_pimageMem;

      auto rectangleX = this->rectangle();

      if (rectangleX.area() <= 0)
      {

         return;

      }

      pimage1->create(rectangleX.size());

      ::draw2d::graphics_pointer pgraphics = pimage1->get_graphics();

      if (is_window_enabled())
      {

         pimage1->fill_byte(255);

      }
      else
      {

         pimage1->clear_argb(255, 200, 200, 200);

      }

      pgraphics->set_interpolation_mode(::draw2d::e_interpolation_mode_high_quality_bicubic);

      ::image::image_source imagesource(m_pimageLogo);

      ::image::image_drawing_options imagedrawingoptions(m_pimageLogo->rectangle({ 10, 10 }));

      ::image::image_drawing imagedrawing(imagedrawingoptions, imagesource);

      pgraphics->draw(imagedrawing);

      //__construct_new(m_pitema);

//      ::int_rectangle rectangle;

      int_rectangle_array raMenu;

      int iPos = 0;

      //xml::node * pnodeMain = m_pxmldoc->get_child_at("menubar", 0, 1);

      //if (pnodeMain->get_children_count("menubar") <= 0)
      //{

      //   pnodeMain = m_pxmldoc;

      //}

      for (int i = 0; i < m_pmenuitem->m_pmenuitema->get_count(); i++)
      {

         auto pmenuitemPopup = m_pmenuitem->m_pmenuitema->element_at(i);

         ///main_content().add_item(__allocate ::item(::e_element_item, iPos, iMenu, -1));

         string strTitle;
         
         strTitle = pmenuitemPopup->m_strTitle;

         pgraphics->set(m_pfontTitle);

         auto puseritemPopup = layout_user_item_by_index(iPos);

         pgraphics->set(m_ppen);

         draw_header_rectangle(pgraphics, puseritemPopup->m_rectangle2);

         pgraphics->set_text_color(argb(255, 0, 0, 0));

         pgraphics->text_out(puseritemPopup->m_rectangle2.left() + 10, puseritemPopup->m_rectangle2.top() + 5, strTitle);

         iPos++;

         ::int_rectangle rectanglePopupTotal = puseritemPopup->m_rectangle2;

         for (int j = 0; j < pmenuitemPopup->m_pmenuitema->get_count(); j++)
         {

            auto pmenuitem = pmenuitemPopup->m_pmenuitema->element_at(j);

            auto atom = pmenuitem->id();

            auto strItemTitle = pmenuitem->m_strTitle;

            auto puseritem = layout_user_item_by_index(iPos);

            rectanglePopupTotal.unite(rectanglePopupTotal, puseritem->m_rectangle2);

            pgraphics->set(m_ppen);

            ::item item(::e_element_item, iPos, i, j);

            if (::is_set(m_pitemHover))
            {

               information() << "menu_impact::_001OnDraw m_pitemHover (item, subitem) : " << m_pitemHover->m_item.m_iItem << ", " << m_pitemHover->m_item.m_iSubItem;

            }
            else
            {

               information() << "menu_impact::_001OnDraw m_pitemHover is not set";

            }

            if (::is_set(m_pitemHover) && m_pitemHover == pmenuitem)
            {

               if (::is_set(main_content().m_pitemCurrent) && *main_content().m_pitemCurrent == item)
               {

                  pgraphics->set(m_pbrushBkHoverSel);

                  draw_item_rectangle_hover_sel001(pgraphics, puseritem->m_rectangle2);

               }
               else
               {

                  pgraphics->set(m_pbrushBkSel);

                  draw_item_rectangle_hover001(pgraphics, puseritem->m_rectangle2);

               }

            }
            else if (::is_set(main_content().m_pitemCurrent) && *main_content().m_pitemCurrent == item)
            {

               pgraphics->set(m_pbrushBkSel);

               draw_item_rectangle_sel001(pgraphics, puseritem->m_rectangle2);

            }
            else
            {

               draw_item_rectangle(pgraphics, puseritem->m_rectangle2);

            }

            pgraphics->set(m_pfont);

            if (::is_set(main_content().m_pitemCurrent) && *main_content().m_pitemCurrent == item)
            {

               pgraphics->set_text_color(argb(255, 0, 148, 202));

            }
            else
            {

               pgraphics->set_text_color(argb(255, 60, 60, 60));

            }

            pgraphics->text_out(puseritem->m_rectangle2.left() + 10, puseritem->m_rectangle2.top() + 5, strItemTitle);

            pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

            ::image::image_pointer pimage1;

            if (::is_set(main_content().m_pitemCurrent) && *main_content().m_pitemCurrent == item)
            {

               pgraphics->set(m_ppenBkSel);

               pgraphics->line(
                  puseritem->m_rectangle2.left() + 1, puseritem->m_rectangle2.top(),
                  puseritem->m_rectangle2.left() + 1, puseritem->m_rectangle2.bottom() - 1);

               pimage1 = m_pimageMap[atom];

            }
            else
            {

               pimage1 = m_pimageMapGray[atom];

            }

            if (pimage1->is_set())
            {

               ::int_rectangle rectangleDib;

               rectangleDib.left() = puseritem->m_rectangle2.right() - pimage1->width() - 10;
               rectangleDib.top() = puseritem->m_rectangle2.top() + (puseritem->m_rectangle2.height() - pimage1->height()) / 2;
               rectangleDib.set_size(pimage1->width(), pimage1->height());

               ::image::image_source imagesource(pimage1);

               ::image::image_drawing_options imagedrawingoptions(rectangleDib);

               ::image::image_drawing imagedrawing(imagedrawingoptions, imagesource);

               pgraphics->draw(imagedrawing);

            }

            iPos++;

         }

         raMenu.add(rectanglePopupTotal);

      }

      iPos = 0;

      for (int i = 0; i < m_pmenuitem->m_pmenuitema->get_count(); i++)
      {

         auto pmenuitemPopup = m_pmenuitem->m_pmenuitema->element_at(i);

         auto puseritem = layout_user_item_by_index(iPos);

         pgraphics->set(m_ppen);

         draw_header_separator(pgraphics, puseritem->m_rectangle2.bottom_left(), puseritem->m_rectangle2.bottom_right());

         iPos++;

         for (int j = 0; j < pmenuitemPopup->m_pmenuitema->get_count(); j++)
         {

            auto pmenuitem = pmenuitemPopup->m_pmenuitema->element_at(j);

            auto atom = pmenuitem->id();

            auto strItemTitle = pmenuitem->m_strTitle;

            auto puseritem = layout_user_item_by_index(iPos);

            draw_item_separator(pgraphics, puseritem->m_rectangle2.bottom_left(), puseritem->m_rectangle2.bottom_right());

            iPos++;

         }

         //iPos++;

      }

      for (int i = 0; i < m_pmenuitem->m_pmenuitema->get_count(); i++)
      {

         draw_border_rectangle(pgraphics, raMenu[i]);

      }

      if (!is_window_enabled())
      {

         pimage1->saturation(0.0);

      }

      {

         ::image::image_source imagesource(pimage1);

         ::image::image_drawing_options imagedrawingoptions(rectangleX);

         ::image::image_drawing imagedrawing(imagedrawingoptions, imagesource);

         pgraphicsParam->draw(imagedrawing);

      }

   }


   ::user::document * menu_impact::get_document()
   {

      return  (::user::impact::get_document());

   }


   void menu_impact::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

      auto rectangleX = this->rectangle();

      if (rectangleX.area() <= 0)
         return;

   }


   bool menu_impact::load_xml(::payload payloadFile)
   {

      //// auto pcontext = get_context();

      string strXml = file()->as_string(payloadFile);

      auto pxmldoc = __create_new < ::xml::document >();

      try
      {

         pxmldoc->load(strXml);

      }
      catch (const ::exception & exception)
      {

         auto pmessagebox = __allocate ::message_box(exception, __FUNCTION_FILE_LINE__);

         pmessagebox->async();

         return false;

      }

      int iPos = 0;

      ::status < ::int_rectangle > statusrectangle;

      int iMenu;

      int iCommand;

//      auto papp = get_app();

      xml::node * pnodeMain = pxmldoc->get_child_at("menubar", 0, 1);

      if (pnodeMain->get_children_count("menubar") <= 0)
      {

         pnodeMain = pxmldoc;

      }

      //m_iaPopup.erase_all();

      auto pmenuitemParent = __create_new < ::menu::item >();

      m_pmenuitem = pmenuitemParent;

      for (iMenu = 0; iMenu < pnodeMain->get_children_count("menubar"); iMenu++)
      {

         xml::node * pnode = pnodeMain->get_child_at("menubar", iMenu, 1);

         auto pmenuitemMenuBar = __create_new < ::menu::item >();

         pmenuitemMenuBar->m_pmenuitema = __allocate ::menu::item_ptra(pmenuitemMenuBar);

         pmenuitemParent->add_item(pmenuitemMenuBar);

         pmenuitemMenuBar->m_strTitle = pnode->attribute("title");

         pmenuitemMenuBar->m_item.m_iItem = iPos;

         //m_iaPopup.add((const int)pnode->get_children_count() + 1);

         iPos++;

         for (iCommand = 0; iCommand < pnode->get_children_count(); iCommand++)
         {

            auto pnodeChild = pnode->child_at(iCommand);

            auto pmenuitemCommand = __create_new < ::menu::item >();

            //statusrectangle = get_menu_item_rectangle(iPos);

            pmenuitemMenuBar->m_pmenuitema->add(pmenuitemCommand);

            pmenuitemCommand->id() = pnodeChild->attribute("id").as_atom();

            pmenuitemCommand->m_item.m_iItem = iPos;

            ::string strTitle = pnodeChild->value();

            pmenuitemCommand->m_strTitle = strTitle;

            ::image::image_pointer pimage1 = image()->load_image(pnodeChild->attribute("image"), { .cache = false });

            if (pimage1)
            {

               ::string strId = pnode->child_at(iCommand)->attribute("id").as_string();

               m_pimageMap[strId] = pimage1;

               ::image::image_pointer pimageGray;

               pimageGray = pimage1->clone();

               //pimageGray->from(pimage1);

               pimageGray->saturation(0.0);

               m_pimageMapGray[strId] = pimageGray;

            }

            iPos++;

         }

      }

      return true;

   }


   void menu_impact::draw_border_rectangle(::draw2d::graphics_pointer & pgraphics, const ::int_rectangle & rectangle)
   {

      pgraphics->line(
         rectangle.left(), rectangle.top(),
         rectangle.right(), rectangle.top());

      pgraphics->line(
         rectangle.left(), rectangle.bottom(),
         rectangle.right(), rectangle.bottom());

   }


   void menu_impact::draw_header_separator(::draw2d::graphics_pointer & pgraphics, const ::int_point& point1, const ::int_point& point2)
   {

      pgraphics->line(
         point1,
         point2);

   }


   void menu_impact::draw_header_rectangle(::draw2d::graphics_pointer & pgraphics, const ::int_rectangle & rectangle)
   {

      pgraphics->fill_rectangle(rectangle, argb(255, 240, 240, 240));

      pgraphics->line(
         rectangle.left(), rectangle.top(),
         rectangle.left(), rectangle.bottom());

      pgraphics->line(
         rectangle.right(), rectangle.top(),
         rectangle.right(), rectangle.bottom());




   }


   void menu_impact::draw_item_rectangle(::draw2d::graphics_pointer & pgraphics, const ::int_rectangle & rectangle)
   {

      pgraphics->line(
         rectangle.left(), rectangle.top(),
         rectangle.left(), rectangle.bottom());

      pgraphics->line(
         rectangle.right(), rectangle.top(),
         rectangle.right(), rectangle.bottom());

   }


   void menu_impact::draw_item_rectangle_hover001(::draw2d::graphics_pointer & pgraphics, const ::int_rectangle & rectangle)
   {

      pgraphics->fill_rectangle(rectangle);

      pgraphics->line(
         rectangle.left(), rectangle.top(),
         rectangle.left(), rectangle.bottom());

      pgraphics->line(
         rectangle.right(), rectangle.top(),
         rectangle.right(), rectangle.bottom());

   }


   void menu_impact::draw_item_rectangle_sel001(::draw2d::graphics_pointer & pgraphics, const ::int_rectangle & rectangle)
   {

      pgraphics->fill_rectangle(rectangle);

      pgraphics->line(
         rectangle.left(), rectangle.top(),  
         rectangle.left(), rectangle.bottom());

      int h = ::height(rectangle);

      pgraphics->line(
         rectangle.right(), rectangle.bottom() - 1,
         rectangle.right(), rectangle.bottom() - h / 3 - 2);

      double_point_array pta;

      pta.add(rectangle.right(), rectangle.bottom() - h / 3 - 2);

      pta.add(rectangle.right() + h * 3 / 16, rectangle.bottom() - h / 2 - 2);

      pta.add(rectangle.right(), rectangle.bottom() - h * 2 / 3 - 2);

      pgraphics->fill_polygon(pta);

      auto ppath = __øcreate<::draw2d::path>();

      ppath->set_current_point(rectangle.right(), rectangle.bottom() - h * 2 / 3 - 2);
      
      ppath->add_line(rectangle.right(), rectangle.bottom() - h / 3 - 2);

      ppath->add_line(rectangle.right() + h * 3 / 16, rectangle.bottom() - h / 2 - 2);

      ppath->add_line(rectangle.right(), rectangle.bottom() - h * 2 / 3 - 2);

      ppath->add_line(rectangle.right(), rectangle.top());

      pgraphics->draw(ppath);

   }


   void menu_impact::draw_item_rectangle_hover_sel001(::draw2d::graphics_pointer & pgraphics, const ::int_rectangle & rectangle)
   {

      pgraphics->fill_rectangle(rectangle);

      pgraphics->line(
         rectangle.left(), rectangle.top(),
            rectangle.left(), rectangle.bottom());

      int h = ::height(rectangle);

      pgraphics->line(
         rectangle.right(), rectangle.bottom() - 1,
         rectangle.right(), rectangle.bottom() - h / 3 - 2);

      double_point_array pta;

      pta.add(rectangle.right(), rectangle.bottom() - h / 3 - 2);

      pta.add(rectangle.right() + h * 3 / 16, rectangle.bottom() - h / 2 - 2);

      pta.add(rectangle.right(), rectangle.bottom() - h * 2 / 3 - 2);

      pgraphics->fill_polygon(pta);

      auto ppath = __øcreate<::draw2d::path>();

      ppath->set_current_point(rectangle.right(), rectangle.bottom() - h * 2 / 3 - 2);

      ppath->add_line(rectangle.right(), rectangle.bottom() - h / 3 - 2);

      ppath->add_line(rectangle.right() + h * 3 / 16, rectangle.bottom() - h / 2 - 2);

      ppath->add_line(rectangle.right(), rectangle.bottom() - h * 2 / 3 - 2);

      ppath->add_line(rectangle.right(), rectangle.top());

      pgraphics->draw(ppath);

   }


   void menu_impact::draw_item_separator(::draw2d::graphics_pointer& pgraphics, const ::int_point& point1, const ::int_point& point2)
   {

      pgraphics->line(point1, point2);

   }


} // namespace user


