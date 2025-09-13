#include "framework.h"
#include "core_data.h"
#include "data.h"
#include "acme/constant/id.h"
#include "acme/constant/user_message.h"
#include "acme/constant/user_key.h"
#include "acme/handler/topic.h"
#include "acme/parallelization/task_keep.h"
#include "acme/prototype/prototype/url.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/platform/application.h"
#include "acme/platform/hyperlink.h"
#include "acme/prototype/data/listener.h"
#include "acme/filesystem/filesystem/file_context.h"
#include "aura/graphics/image/context.h"
#include "axis/html/element/element.h"
#include "axis/html/impl/element.h"
#include "axis/html/graphics/font.h"
#include "axis/html/graphics/style.h"
#include "axis/html/graphics/reader.h"
#include "axis/html/graphics/tag.h"
#include "axis/html/graphics/value.h"
#include "axis/html/user/form.h"
#include "axis/platform/system.h"
#include "aura/message/user.h"
#include "aura/user/user/frame_interaction.h"


namespace html
{


   core_data::image::image()
   {

      defer_create_synchronization();

   }


   bool core_data::image::load_image()
   {

      m_pimage = ::particle::image()->load_image(m_strPath);

      return m_pimage;

   }


   core_data::core_data()
   {

      defer_create_synchronization();

      m_pcoredata = this;
      m_pcookies = nullptr;
      m_bEdit = false;
      m_puserinteraction = nullptr;
      m_bImplemented = false;
      m_bImplement = false;
      m_bLaidout = false;
      m_ptag = nullptr;
      m_pcallback = nullptr;
   }


   core_data::~core_data()
   {

      ::acme::del(m_ptag);

      m_pform = nullptr;

   }

   void core_data::initialize_html_data(html_data * pdata)
   {

      //auto estatus = 
      
      ::html_data::initialize_html_data(pdata);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //return estatus;

   }

   //long long core_data::increment_reference_count()
   //{

   //   return ::object::increment_reference_count();

   //}


   //long long core_data::decrement_reference_count()
   //{

   //   return ::object::decrement_reference_count();

   //}


   font * core_data::get_font(::html::element * pelement)
   {

      int iFont = -1;

      if (pelement->m_pimpl->m_bHover)
      {

         if (!pelement->m_pimpl->m_mapFont.find("hover", iFont))
         {

            iFont = create_font(pelement);
            pelement->m_pimpl->m_mapFont.set_at("hover", iFont);
         }
         return m_fonta.element_at(iFont);
      }
      else if (pelement->m_pimpl->has_link())
      {
         if (!pelement->m_pimpl->m_mapFont.find("link", iFont))
         {
            iFont = create_font(pelement);
            pelement->m_pimpl->m_mapFont.set_at("link", iFont);
         }
         return m_fonta.element_at(iFont);
      }
      else
      {
         if (!pelement->m_pimpl->m_mapFont.find("", iFont))
         {
            iFont = create_font(pelement);
            pelement->m_pimpl->m_mapFont.set_at("", iFont);
         }
         return m_fonta.element_at(iFont);
      }

   }


   int core_data::create_font(::html::element * pelement)
   {

      string strSubClass;

      class font font;

      if (!pelement->m_pimpl->m_bHover
         || !pelement->m_pstyle->get_text("font-family", "hover", this, pelement, font.m_strFamily))
      {
         if (!pelement->m_pimpl->has_link()
            || !pelement->m_pstyle->get_text("font-family", "link", this, pelement, font.m_strFamily))
         {
            pelement->m_pstyle->get_text("font-family", "", this, pelement, font.m_strFamily);
         }
      }
      if (!pelement->m_pimpl->m_bHover
         || !pelement->m_pstyle->get_text("font-int_size", "hover", this, pelement, font.m_strSize))
      {
         if (!pelement->m_pimpl->has_link()
            || !pelement->m_pstyle->get_text("font-float_size", "link", this, pelement, font.m_strSize))
         {
            pelement->m_pstyle->get_text("font-int_size", "", this, pelement, font.m_strSize);
         }
      }
      if (!pelement->m_pimpl->m_bHover
         || !pelement->m_pstyle->get_text("font-weight", "hover", this, pelement, font.m_strWeight))
      {
         if (!pelement->m_pimpl->has_link()
            || !pelement->m_pstyle->get_text("font-weight", "link", this, pelement, font.m_strWeight))
         {
            pelement->m_pstyle->get_text("font-weight", "", this, pelement, font.m_strWeight);
         }
      }
      if (pelement->m_pimpl->m_bHover
         && !pelement->m_pstyle->get_text("text-decoration", "hover", this, pelement, font.m_strTextDecoration))
      {
         if (pelement->m_pimpl->has_link()
            && !pelement->m_pstyle->get_text("text-decoration", "link", this, pelement, font.m_strTextDecoration))
         {
            pelement->m_pstyle->get_text("text-decoration", "", this, pelement, font.m_strTextDecoration);
         }
      }
      font.m_strFamily.trim();
      font.m_strSize.trim();
      font.m_strWeight.trim();
      font.m_strTextDecoration.trim();
      for (int i = 0; i < m_fonta.get_count(); i++)
      {
         if (*m_fonta[i] == font)
            return i;
      }
      auto pfont = øallocate class font (font);
      pfont->create(this);
      m_fonta.add(pfont);
      pfont->m_iIndex = (int)m_fonta.get_upper_bound();
      return (int)pfont->m_iIndex;
   }


   void core_data::delete_contents()
   {

      synchronous_lock lock(synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      destroy();

   }


   void core_data::handle(::topic * ptopic, ::handler_context * phandlercontext)
   {

      html_data::handle(ptopic, phandlercontext);

   }


   void core_data::destroy()
   {

      m_focusptra.erase_all();

      if (m_pelement)
      {

         m_pelement->destroy(this);

         m_pelement.release();

      }

      m_bImplemented = false;

      m_bLaidout = false;

      //return ::success;

   }


   void core_data::delete_implementation()
   {

      m_focusptra.erase_all();

      m_pelement->delete_implementation(this);

      m_bImplemented = false;

   }


   void core_data::load(const ::scoped_string & scopedstr)
   {

      delete_contents();

      auto phtmlreader = øcreate_new < lite_html_reader >();

      ::html::reader reader;

      phtmlreader->m_phtml = system()->m_phtml;

      phtmlreader->setEventHandler(&reader);

      phtmlreader->read_form_document(scopedstr);

      if (m_ptag != nullptr)
      {

         delete m_ptag;

      }

      m_ptag = reader.detach_main_tag();

      if (m_ptag == nullptr)
      {

         m_ptag = __raw_new tag(nullptr);

         class value * pvalue = __raw_new class value (m_ptag);

         m_ptag->baseptra().add(pvalue);

         pvalue->set_value(" ");

      }

      m_pelement = øallocate ::html::element ();

      m_pelement->initialize_html_elemental(this);

      m_pelement->load(this, m_ptag);

      m_pform->set_need_layout();

      m_pform->set_need_redraw();

      m_pform->post_redraw();

   }


   void core_data::implement(::draw2d::graphics_pointer & pgraphics)
   {
      
      if(::is_null(m_pelement))
      {
         
         return;
         
      }

      m_bImplemented = false;

      m_bLaidout = false;

      __guard_wait(m_bImplement);

      m_pgraphics = pgraphics;

      m_focusptra.erase_all();

      m_pelement->implement(this);

      //auto children = m_pform->synchronized_get_children();

      for_user_interaction_children(puserinteraction, m_pform)
      //if (m_pform->m_puserinteractionpointeraChild)
      {

         //for (auto & pinteraction :children)
         {

            //synchronouslock.unlock();
            
            auto ptopic = create_topic(::id_initialize_control);

            ptopic->m_puserelement = puserinteraction;

            m_pform->route(ptopic);

            //synchronouslock.lock();

         }

      }

      USER_MESSAGE_LINK(::user::e_message_key_down, m_puserinteraction, this, &core_data::on_message_key_down);
      
      m_bImplemented = true;
      
      m_pform->on_form_implemented();
      
   }


   void core_data::on_message_key_down(::message::message * pmessage)
   {

      auto pkey = pmessage->m_union.m_pkey;

      if (pkey->m_ekey == ::user::e_key_tab)
      {

         auto pfocus = get_form()->get_keyboard_focus();

         if (pfocus != nullptr)
         {

            pfocus = pfocus->keyboard_get_next_focusable();

         }

         if (pfocus != nullptr)
         {

            pfocus->set_keyboard_focus();

         }

         pkey->m_bRet = true;

         return;

      }

   }


   void core_data::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

      synchronous_lock synchronouslock(this->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      if (!m_bImplemented)
      {

         implement(pgraphics);

      }

      if (m_pelement)
      {

         m_pgraphics = pgraphics;

         m_layoutstate1.reset();

         m_layoutstate2.reset();

         m_layoutstate3.reset();

         m_pelement->on_layout(this);

      }

      if (m_pcallback != nullptr)
      {

         auto pextendedtopic = create_topic(::id_form_initialize);

         pextendedtopic->m_puserelement = m_puserinteraction;

         m_puserinteraction->route(pextendedtopic);

      }

      m_bLaidout = true;

   }


   void core_data::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      if (!m_bImplemented || !m_bLaidout)
      {

         return;

      }

      synchronous_lock synchronouslock(this->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      m_pgraphics = pgraphics;

      pgraphics->set_text_rendering_hint(::write_text::e_rendering_anti_alias);

      pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

      //if(m_strPathName.case_insensitive_find("alarms_index") >= 0)
      //{

      //   pgraphics->fill_rectangle(100,100,100,100,argb(190, 255, 0, 0));

      //}

      m_bDrawFirstBody = false;

      m_pelement->_001OnDraw(this);

      //if(m_strPathName.case_insensitive_find("alarms_index") >= 0)
      //{

      //   pgraphics->fill_rectangle(200,200,100,100,argb(190, 0, 255, 0));

      //}

   }


   ::html::element * core_data::get_element_by_name(atom atom)
   {

      return m_pelement->get_element_by_name(atom);

   }


   ::html::element * core_data::get_element_by_id(atom atom)
   {

      return m_pelement->get_element_by_id(atom);

   }


   void core_data::layout_state1::reset()
   {

      m_bHasChar = false;

      m_cxMax.erase_all();

      m_cxMax.add(0.f);

      m_cxa.erase_all();

      m_cxa.add(0.f);

      m_cya.erase_all();

      m_cya.add(0.f);

      m_cy = 0.f;

   }


   void core_data::layout_state2::reset()
   {
      m_iBody = 0;
      m_y = 0;
      m_cy = 0;
      m_x = 0;
      m_cx = 0;
      m_bLastBlock = false;
      m_bLastCell = false;
   }


   void core_data::layout_state3::reset()
   {

      //      m_cyStack.erase_all();
      m_yParent.erase_all();
      m_cya.erase_all();
      m_xParent.erase_all();
      m_x = 0.f;

      m_iBody = 0;
      m_y = 0;
      //m_cyStack.add(0.f);
      m_cya.add(0.f);
      m_xParent.add(0.f);
      m_yParent.add(0.f);
      //m_iy = 0;
      m_x = 0.f;
      m_cx = 0;
      m_bLastBlock = false;
      m_bLastCell = false;

   }


   string core_data::process_url(const ::scoped_string & scopedstrUrl)
   {
   
      string strHref(scopedstrUrl);

      ::url::parts parts(m_strPathName);

      parts.set_href(strHref);

      auto strUrl = parts.as_string();

      return strUrl;

   }


   ::image::image_pointer core_data::get_image(const ::scoped_string & scopedstrUrl)
   {

      string strUrl = process_url(scopedstrUrl);

      auto pimage = ::particle::image()->get_image(strUrl);

      return ::transfer(pimage);

   }


   void core_data::load_image_asynch(image* pimage)
   {

      fork([this,pimage]()
         {

            if (load_image(pimage))
            {

               on_image_loaded(pimage);

            }

         });

   }


   bool core_data::load_image(image* pimage)
   {

      synchronous_lock lockImage(pimage->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      bool bRet = false;

      try
      {

         bRet = pimage->load_image();

      }
      catch (...)
      {

         bRet = false;

      }

      return bRet;

   }


   void core_data::on_image_loaded(image* pimage)
   {

      __UNREFERENCED_PARAMETER(pimage);

      if (m_puserinteraction != nullptr)
      {

         m_puserinteraction->post_message(::user::e_message_image_loaded);

      }

   }


   bool core_data::contains(::pointer<::user::interaction>pinteraction)
   {

      return m_uiptra.contains(pinteraction);

   }


   bool core_data::on_create_interaction(::pointer<::user::interaction>pinteraction)
   {
      m_uiptra.add_unique(pinteraction);
      return true;
   }


   bool core_data::open_link(const ::scoped_string & scopedstrPath)
   {

      string strPath(scopedstrPath);

      if (strPath.begins_eat("ext://"))
      {

         auto phyperlink =øcreate_new < hyperlink>();

         phyperlink->m_strLink = strPath;

         phyperlink->run();

         /*         ::aura::shell_launcher launcher(nullptr, "open", strUrl, "", "", SW_SHOWNORMAL);
         launcher.execute();*/

         return true;

      }

      if (m_pform != nullptr && m_pform->has_document())
      {

         return m_pform->on_open_document(scopedstrPath);

      }

      if (strPath.contains(":"))
      {

         return open_document(strPath);

      }
      else if (strPath.begins("/") || strPath.begins("\\"))
      {

         return open_document(strPath);

      }
      else
      {

         return open_document(m_strPathName.sibling(strPath));

      }

   }


   bool core_data::open_document(const ::payload & payloadFile)
   {

      //int iRetry = 0;

      synchronous_lock lock(synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

   //restart:


      //::payload payload;

      //payload = 1;

      //payload = 2;

      //payload[0] = 2;

      //payload["element1"] = pelement1;

      //payload = 3;

      ::file::path pathUrl = payloadFile.as_file_path();

      ::payload payloadFile2;

      payloadFile2["url"] = pathUrl;

      string strDebugUrl1 = payloadFile2.as_file_path();

      if (m_strPathName.has_character())
      {

        payloadFile2["url"] = defer_solve_relative(pathUrl, m_strPathName);

      }

      payloadFile2["http_set"] = property_set()["http_propset"].as_property_set();

      bool bNoCache = payloadFile["nocache"].get_bool();

      byte_array ba;

      //bool bCancel = false;

      ////on_before_navigate(payloadFile, 0, 0, ba, nullptr, &bCancel);

      //if (bCancel)
      //{

      //   return false;

      //}

      payloadFile2["http_set"]["app"] = get_app();

      //varQuery.propset()["headers"].propset()["accept"] = "text/xml,application/xml,application/xhtml+xml,text/html;q=0.9,text/plain;q=0.8,video/x-mng,image/png,image/jpeg,image/gif;q=0.2,*/*;q=0.1";
      payloadFile2["http_set"]["headers"].as_property_set()["accept"] = "text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8";
      //      varQuery.propset()["headers"].propset()["Accept-Language"] = "en-us,en;q=0.5";
            //varQuery.propset()["headers"].propset()["Accept-Encoding"] = "gzip,deflate";
      //      varQuery.propset()["headers"].propset()["Accept-Charset"] = "ISO-8859-1,utf-8;q=0.7,*;q=0.7";
      payloadFile2["http_set"]["headers"].as_property_set()["Cache-Control"] = "maximum-age=0";

      string str;

   repeat:

      payloadFile2["nocache"] = bNoCache;

      string strDebugUrl2 = payloadFile2.as_file_path();

      // auto pcontext = get_context();

      str = file()->as_string(payloadFile2);

      //if (!payloadFile["http_set"]["get_headers"].propset()["Location"].is_empty())
      //{
      //   string strLocation = payloadFile["http_set"]["get_headers"].propset()["Location"];
      //   iRetry++;
      //   if (iRetry > 8)
      //   {
      //      str = "<html>";
      //      str += "<head>";
      //      str += "</head>";
      //      str += "<body>";
      //      str += "<h1>Redirecionamento Incorreto</h1>";
      //      str += "</body>";
      //      str += "</html>";
      //   }
      //   else
      //   {
      //      
      //      payloadFile = purl->override_if_set_at_source(payloadFile, payloadFile["http_set"]["get_headers"].propset()["Location"]);

      //      goto restart;

      //   }
      //}

      if (str.is_empty())
      {
         string strCandidate = m_strPathName / payloadFile.as_file_path();
         str = file()->as_string(strCandidate);
         if (str.is_empty())
         {

            if (!bNoCache)
            {

               bNoCache = true;

               goto repeat;

            }

            return false;

         }

      }
      
      //auto estatus = 
      
      open_html(str);

      //if(::failed(estatus))
      //{
      //   
      //   return false;

      //}

      return true;

   }
   
   
   bool core_data::open_html(const ::scoped_string & scopedstrParam)
   {
      
      string str(scopedstrParam);
      
      delete_contents();
      
      m_strPathName = "html://<see source>";
      
      m_strSource = str;
      
      //auto pset = m_pform->get_form_property_set();
      
      //auto & set = pset->propset();

//      if (::is_set(m_pform))
//      {
//
//         auto pformcallback = m_pform->get_form_callback();
//
//         if (::is_set(pformcallback))
//         {
//
//            pformcallback->property_set_replace(str);
//
//         }
//
//      }
      
      property_set_replace(str);
      
      informationf("%s", str.c_str());
      
      if (str.has_character())
      {
         
         load(str);
         
      }
      
      return true;

   }


   //void core_data::on_before_navigate(::payload& payloadFile, unsigned int nFlags, const ::scoped_string & scopedstrTargetFrameName, byte_array& baPostedData, const ::scoped_string & scopedstrHeaders, bool* pbCancel)

   //{
   //   if (m_pcallback != nullptr)
   //   {
   //      m_pcallback->on_before_navigate(this, payloadFile, nFlags, pszTargetFrameName, baPostedData, pszHeaders, pbCancel);

   //   }
   //   else if (m_pform != nullptr)
   //   {
   //      m_pform->on_before_navigate(payloadFile, nFlags, pszTargetFrameName, baPostedData, pszHeaders, pbCancel);

   //   }
   //}

   
   ::user::form* core_data::get_form()
   {
      
      return m_pform;

   }

   
   ::pointer<::user::interaction>core_data::get_frame()
   {
      
      return  (get_form()->parent_frame());

   }


   void core_data::implement_and_layout(::html_form * pform)
   {

      ::image::image_pointer pimage;

      //auto estatus = 
      
      øconstruct(pimage);
      
      //if (!estatus)
      //{

      //   return;

      //}

      pimage->create({ 50, 50 });

      /*if (!estatus)
      {

         return;

      }*/

      synchronous_lock lock(synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      m_puserinteraction = pform;

      m_pform = pform;

      ::draw2d::graphics_pointer pgraphics;

      pgraphics = pimage->g();

      implement(pgraphics);

      pform->GetClientBox(m_box);

      if (m_box.area() <= 0.f)
      {

         return;

      }

      on_layout(pgraphics);

   }


   void core_data::implement(::html_form * pform)
   {

      ::image::image_pointer pimage;

      //auto estatus = 
      
      øconstruct(pimage);

      //if (!estatus)
      //{

      //   return;

      //}
      
      //estatus =
      
      pimage->create( { 50, 50 } );

      //if (!estatus)
      //{

      //   return;

      //}

      synchronous_lock lock(synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      m_puserinteraction = pform;

      m_pform = pform;

      ::draw2d::graphics_pointer pgraphics;

      pgraphics = pimage->g();

      implement(pgraphics);

   }


   void core_data::layout(::html_form * pform)
   {

      ::image::image_pointer pimage;

      //auto estatus = 
      
      øconstruct(pimage);
      
      //if (!estatus)
      //{

      //   return;

      //}

      //estatus = 
      
      pimage->create( { 50, 50 } );

      //if (!estatus)
      //{

      //   return;

      //}

      synchronous_lock lock(synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      m_puserinteraction = pform;

      m_pform = pform;

      pform->GetClientBox(m_box);

      if (m_box.area() <= 0.f)
      {

         return;

      }

      ::draw2d::graphics_pointer pgraphics;

      pgraphics = pimage->g();

      on_layout(pgraphics);

   }


} // namespace html







