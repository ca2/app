#include "framework.h"
#include "aqua/xml.h"


namespace filehandler
{


   impact::impact(::particle * pparticle) :
      ::object(pparticle),
      m_pfont(e_create)
   {
      m_pxmldoc = memory_new xml::document(this);
      m_pfont->create_point_font(pnode->font_name(e_font_sans_ex),14.0);

   }


   impact::~impact()
   {

      ::acme::del(m_pxmldoc);

   }


   void impact::install_message_routing(::channel * pchannel)
   {

      ::user::form::install_message_routing(pchannel);
      MESSAGE_LINK(e_message_create, pchannel, this, &impact::on_message_create);
//
      MESSAGE_LINK(e_message_left_button_up, pchannel, this, &impact::on_message_left_button_up);

   }


   void impact::refresh()
   {

      m_plistWorking = __new(list(this));

      m_plistWorking->parse(psystem->filehandler(), ::file::path(m_strName).extension());

      m_plist = m_plistWorking;

      m_plistWorking = nullptr;

      on_layout(pgraphics);

   }


   void impact::_001OnTimer(::timer * ptimer)
   {

      form_impact::_001OnTimer(ptimer);;

      if(ptimer->m_uEvent == 8888)
      {

         refresh();

      }

   }


   void impact::on_message_create(::message::message * pmessage)
   {

      if(pmessage->previous())
         return;

      SetTimer(8888, 5000, nullptr);

   }


   void impact::item::parse(const ::string & pszApp)
   {

      m_strApp = pszApp;

   }


   void impact::list::parse(::filehandler::handler * phandler, const ::string & pszTopic)
   {

      erase_all();

      string_array straApp;

      phandler->get_extension_app(straApp, pszTopic);

      item item(this);

      for(i32 i = 0; i < straApp.get_count(); i++)
      {
         item.parse(straApp[i]);
         item.m_iIndex = i;
         add(__new(class item(item)));
      }

   }

   impact::item::item(::particle * pparticle) :
      ::object(pparticle)
   {

   }

   void impact::item::draw(::pointer<impact>pimpact, ::draw2d::graphics_pointer & pgraphics, list * plist)
   {

      __UNREFERENCED_PARAMETER(plist);



      color32_t color32;
      ::pointer<::aura::application>papp = pimpact->get_app();
      
      bool bHover = pimpact->m_pitemHover == m_iIndex;

      color32 = bHover ? argb(255, 230, 255, 230) : argb(255, 200, 255, 200);
      if(!Sess(papp).savings().is_trying_to_save(::e_resource_processing)
            && !Sess(papp).savings().is_trying_to_save(::e_resource_display_bandwidth)
            && !Sess(papp).savings().is_trying_to_save(::e_resource_memory))
      {
         class imaging & imaging = App(papp).imaging();
         imaging.color_blend(pgraphics, m_rectangleItem, color32, 127);
      }
      else
      {
         pgraphics->fill_rectangle(m_rectangleItem, color32);
      }
      color32 = bHover ? argb(255, 150, 255, 150) : argb(255, 50, 255, 50);
      pgraphics->fill_rectangle(m_rectangleStatusImage, color32);
      color32_t cr1;
      color32_t cr2;
      if(bHover)
      {
         color32 = argb(255, 0, 100, 0);
         cr1 = argb(255, 120, 255, 150);
         cr2 = argb(255, 23, 200, 33);
      }
      else
      {
         color32 = argb(255, 40, 40, 40);
         cr1 = argb(255, 100, 100, 100);
         cr2 = argb(255, 10, 10, 10);
      }
      pgraphics->draw_inset_3d_rectangle(m_rectangleItem, cr1, cr2);
      color32 |= 0xff000000;
      auto pbrushText = __create < ::draw2d::brush > ();
      pbrushText->create_solid(color32);
      //pgraphics->set_color(color32);
      pgraphics->draw_text(m_strApp, m_rectangleName, e_align_bottom_left);
   }


   impact::list::list(::particle * pparticle) :
      ::object(pparticle)
   {
      m_iItemHeight = 30;
   }

   void impact::list::on_layout(const RECTANGLE_I32 * lpcrect)
   {
      i32 top = lpcrect->top;
      for(i32 i = 0; i < get_count(); i++)
      {
         item & item = operator()(i);
         item.m_rectangleItem.left = lpcrect.left;
         item.m_rectangleItem.right = lpcrect.right;
         item.m_rectangleItem.top = top;
         item.m_rectangleItem.bottom = item.m_rectangleItem.top + m_iItemHeight;
         top = item.m_rectangleItem.bottom + 2;
         item.m_rectangleStatusImage = item.m_rectangleItem;
         item.m_rectangleStatusImage.right = item.m_rectangleStatusImage.left + m_iItemHeight;
         item.m_rectangleStatusImage.deflate(2, 2);
         item.m_rectangleName = item.m_rectangleItem;
         item.m_rectangleName.left = item.m_rectangleStatusImage.right;
         item.m_rectangleName.deflate(2, 2);

      }
   }

   void impact::list::draw(::pointer<impact>pimpact, ::draw2d::graphics_pointer & pgraphics)
   {
      for(i32 i = 0; i < get_count(); i++)
      {
         element_at(i)->draw(pimpact, pgraphics, this);
      }
   }


   void impact::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

      if (m_plist.is_null())
         return;

      layout_list(m_plist);


   }

   void impact::layout_list(list * plist)
   {

      auto pgraphics = create_memory_graphics();

      auto rectangleClient = get_client_rect();

      plist->on_layout(rectangleClient);

   }


   void impact::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      if (m_plist.is_null())
         return;

      //select_font(pimage->g());

      m_plist->draw(this, pgraphics);


   }



   void impact::on_message_left_button_up(::message::message * pmessage)
   {

      auto pmouse = pmessage->m_union.m_pmouse;

      auto point = screen_to_client(pmouse->m_point);

      auto item = hit_test(pmouse);

      if(item)
      {

         /*
         ::payload varRequest;

         varRequest = "app://" + m_list[iItem].m_strApp + "/" + m_strName;

         psession->request(varRequest);
         */

         ::pointer<::create>pcreate(e_create);

         pcreate->m_strApp = m_plist->operator [](item)->m_strApp;

         pcreate->m_payloadFile                = m_strName;

         psession->do_request(pcreate);

         //payloadFile = pcreate->m_payloadFile;

      }

   }


   ::item_pointer impact::on_hit_test(const ::point_i32 &point)
   {

      if (m_plist.is_null())
      {

         item = ::e_element_none;

         return;

      }

      for(i32 i = 0; i < m_plist->get_count(); i++)
      {
         
         if(m_plist->element_at(i)->m_rectangleName.contains(item.m_pointHitTest))
         {
            
            item = { ::e_element_text, i };

            return;

         }

         if (m_plist->element_at(i)->m_rectangleStatusImage.contains(item.m_pointHitTest))
         {
            
/*            item = { ::e_element_status_image, i };

            return;

         }

         if (m_plist->element_at(i)->m_rectangleItem.contains(item.m_pointHitTest))
         {
            
            item = { ::e_element_area, i };

            return;
            
         }

      }

      item = ::e_element_none;

   }


   bool impact::get_font(::write_text::font_pointer & font)
   {

      font = m_pfont;

      return true;

   }

} // namespace filehandler




