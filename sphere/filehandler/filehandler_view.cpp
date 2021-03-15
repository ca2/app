#include "framework.h"
#include "aqua/xml.h"


namespace filehandler
{


   view::view(::context_object * pcontextobject) :
      ::object(pobject),
      m_pfont(e_create)
   {
      m_pxmldoc = new xml::document(this);
      m_pfont->create_point_font(os_font_name(e_font_sans_ex),14.0);

   }


   view::~view()
   {

      ::acme::del(m_pxmldoc);

   }


   void view::install_message_routing(::channel * pchannel)
   {

      ::user::form::install_message_routing(pchannel);
      MESSAGE_LINK(e_message_create, pchannel, this, &view::on_message_create);
//
      MESSAGE_LINK(e_message_left_button_up, pchannel, this, &view::on_message_left_button_up);

   }


   void view::refresh()
   {

      m_plistWorking = __new(list(this));

      m_plistWorking->parse(psystem->filehandler(), ::file::path(m_strName).extension());

      m_plist = m_plistWorking;

      m_plistWorking = nullptr;

      on_layout(::draw2d::graphics_pointer & pgraphics);

   }


   void view::_001OnTimer(::timer * ptimer)
   {

      form_view::_001OnTimer(ptimer);;

      if(ptimer->m_uEvent == 8888)
      {

         refresh();

      }

   }


   void view::on_message_create(::message::message * pmessage)
   {

      if(pmessage->previous())
         return;

      SetTimer(8888, 5000, nullptr);

   }


   void view::item::parse(const char * pszApp)
   {

      m_strApp = pszApp;

   }


   void view::list::parse(::filehandler::handler * phandler, const char * pszTopic)
   {

      remove_all();

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

   view::item::item(::context_object * pcontextobject) :
      ::object(pobject)
   {

   }

   void view::item::draw(__pointer(view) pview, ::draw2d::graphics_pointer & pgraphics, list * plist)
   {

      UNREFERENCED_PARAMETER(plist);



      color32_t cr;
      __pointer(::aura::application) papp = pview->get_application();
      
      bool bHover = pview->m_itemHover == m_iIndex;

      cr = bHover ? argb(255, 230, 255, 230) : argb(255, 200, 255, 200);
      if(!Sess(papp).savings().is_trying_to_save(::e_resource_processing)
            && !Sess(papp).savings().is_trying_to_save(::e_resource_display_bandwidth)
            && !Sess(papp).savings().is_trying_to_save(::e_resource_memory))
      {
         class imaging & imaging = App(papp).imaging();
         imaging.color_blend(pgraphics, m_rectItem, cr, 127);
      }
      else
      {
         pgraphics->fill_rectangle(m_rectItem, cr);
      }
      cr = bHover ? argb(255, 150, 255, 150) : argb(255, 50, 255, 50);
      pgraphics->fill_rectangle(m_rectStatusImage, cr);
      color32_t cr1;
      color32_t cr2;
      if(bHover)
      {
         cr = argb(255, 0, 100, 0);
         cr1 = argb(255, 120, 255, 150);
         cr2 = argb(255, 23, 200, 33);
      }
      else
      {
         cr = argb(255, 40, 40, 40);
         cr1 = argb(255, 100, 100, 100);
         cr2 = argb(255, 10, 10, 10);
      }
      pgraphics->draw3d_rect(m_rectItem, cr1, cr2);
      cr |= 0xff000000;
      ::draw2d::brush_pointer brushText(e_create);
      brushText->create_solid(cr);
      //pgraphics->set_color(cr);
      pgraphics->draw_text(m_strApp, m_rectName, e_align_bottom_left);
   }


   view::list::list(::context_object * pcontextobject) :
      ::object(pobject)
   {
      m_iItemHeight = 30;
   }

   void view::list::on_layout(const RECTANGLE_I32 * lpcrect)
   {
      i32 top = lpcrect->top;
      for(i32 i = 0; i < get_count(); i++)
      {
         item & item = operator()(i);
         item.m_rectItem.left = lpcrect.left;
         item.m_rectItem.right = lpcrect.right;
         item.m_rectItem.top = top;
         item.m_rectItem.bottom = item.m_rectItem.top + m_iItemHeight;
         top = item.m_rectItem.bottom + 2;
         item.m_rectStatusImage = item.m_rectItem;
         item.m_rectStatusImage.right = item.m_rectStatusImage.left + m_iItemHeight;
         item.m_rectStatusImage.deflate(2, 2);
         item.m_rectName = item.m_rectItem;
         item.m_rectName.left = item.m_rectStatusImage.right;
         item.m_rectName.deflate(2, 2);

      }
   }

   void view::list::draw(__pointer(view) pview, ::draw2d::graphics_pointer & pgraphics)
   {
      for(i32 i = 0; i < get_count(); i++)
      {
         element_at(i)->draw(pview, pgraphics, this);
      }
   }


   void view::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

      if (m_plist.is_null())
         return;

      layout_list(m_plist);


   }

   void view::layout_list(list * plist)
   {

      auto pgraphics = create_memory_graphics();

      auto rectClient = get_client_rect();

      plist->on_layout(rectClient);

   }


   void view::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      if (m_plist.is_null())
         return;

      //select_font(pimage->g());

      m_plist->draw(this, pgraphics);


   }



   void view::on_message_left_button_up(::message::message * pmessage)
   {

      __pointer(::message::mouse) pmouse(pmessage);

      auto point = screen_to_client(pmouse->m_point);

      auto item = hit_test(pmouse);

      if(item)
      {

         /*
         ::payload varRequest;

         varRequest = "app://" + m_list[iItem].m_strApp + "/" + m_strName;

         psession->request(varRequest);
         */

         __pointer(::create) pcreate(e_create);

         pcreate->m_pcommandline->m_strApp = m_plist->operator [](item)->m_strApp;

         pcreate->m_pcommandline->m_varFile                = m_strName;

         psession->do_request(pcreate);

         //varFile = pcreate->m_pcommandline->m_varFile;

      }

   }


   void view::on_hit_test(::user::item & item)
   {

      if (m_plist.is_null())
      {

         item = ::user::e_element_none;

         return;

      }

      for(i32 i = 0; i < m_plist->get_count(); i++)
      {
         
         if(m_plist->element_at(i)->m_rectName.contains(item.m_pointHitTest))
         {
            
            item = { ::user::e_element_text, i };

            return;

         }

         if (m_plist->element_at(i)->m_rectStatusImage.contains(item.m_pointHitTest))
         {
            
/*            item = { ::user::e_element_status_image, i };

            return;

         }

         if (m_plist->element_at(i)->m_rectItem.contains(item.m_pointHitTest))
         {
            
            item = { ::user::e_element_area, i };

            return;
            
         }

      }

      item = ::user::e_element_none;

   }


   bool view::get_font(::write_text::font_pointer & font)
   {

      font = m_pfont;

      return true;

   }

} // namespace filehandler




