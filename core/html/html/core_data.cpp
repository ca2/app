#include "framework.h"
#include "core/id.h"
#if !BROAD_PRECOMPILED_HEADER
#include "_html.h"
#endif



namespace html
{


   core_data::image::image()
   {

      defer_create_mutex();

   }


   bool core_data::image::load_image()
   {

      auto pcontext = m_pcontext->m_pauracontext;

      auto pcontextimage = pcontext->context_image();

      m_pimage = pcontextimage->load_image(m_strPath);

      return m_pimage;

   }


   core_data::core_data()
   {

      defer_create_mutex();

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

   ::e_status core_data::initialize_html_data(html_data * pdata)
   {

      auto estatus = ::html_data::initialize_html_data(pdata);

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }

   //i64 core_data::increment_reference_count()
   //{

   //   return ::object::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

   //}


   //i64 core_data::decrement_reference_count()
   //{

   //   return ::object::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

   //}


   font * core_data::get_font(::html::element* pelement)
   {

      i32 iFont = -1;

      if (pelement->m_pimpl->m_bHover)
      {

         if (!pelement->m_pimpl->m_mapFont.lookup("hover", iFont))
         {

            iFont = create_font(pelement);
            pelement->m_pimpl->m_mapFont.set_at("hover", iFont);
         }
         return m_fonta.element_at(iFont);
      }
      else if (pelement->m_pimpl->has_link())
      {
         if (!pelement->m_pimpl->m_mapFont.lookup("link", iFont))
         {
            iFont = create_font(pelement);
            pelement->m_pimpl->m_mapFont.set_at("link", iFont);
         }
         return m_fonta.element_at(iFont);
      }
      else
      {
         if (!pelement->m_pimpl->m_mapFont.lookup("", iFont))
         {
            iFont = create_font(pelement);
            pelement->m_pimpl->m_mapFont.set_at("", iFont);
         }
         return m_fonta.element_at(iFont);
      }

   }


   i32 core_data::create_font(::html::element * pelement)
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
         || !pelement->m_pstyle->get_text("font-size_i32", "hover", this, pelement, font.m_strSize))
      {
         if (!pelement->m_pimpl->has_link()
            || !pelement->m_pstyle->get_text("font-size_f32", "link", this, pelement, font.m_strSize))
         {
            pelement->m_pstyle->get_text("font-size_i32", "", this, pelement, font.m_strSize);
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
      for (i32 i = 0; i < m_fonta.get_count(); i++)
      {
         if (m_fonta(i) == font)
            return i;
      }
      auto pfont = __new(class font(font));
      pfont->create(this);
      m_fonta.add(pfont);
      pfont->m_iIndex = (i32)m_fonta.get_upper_bound();
      return (i32)pfont->m_iIndex;
   }


   void core_data::delete_contents()
   {

      synchronous_lock lock(mutex());

      destroy();

   }


   void core_data::on_subject(::subject::subject * psubject, ::subject::context * pcontext)
   {

      html_data::on_subject(psubject, pcontext);

   }


   ::e_status core_data::destroy()
   {

      m_focusptra.erase_all();

      if (m_pelement)
      {

         m_pelement->destroy(this);

         m_pelement.release();

      }

      m_bImplemented = false;

      m_bLaidout = false;

      return ::success;

   }


   void core_data::delete_implementation()
   {

      m_focusptra.erase_all();

      m_pelement->delete_implementation(this);

      m_bImplemented = false;

   }


   void core_data::load(const ::string & psz)
   {

      delete_contents();

      auto phtmlreader = __create_new < lite_html_reader >();

      ::html::reader reader;

      phtmlreader->m_phtml = m_psystem->m_paxissystem->m_phtml;

      phtmlreader->setEventHandler(&reader);

      phtmlreader->read_form_document(psz);

      if (m_ptag != nullptr)
      {

         delete m_ptag;

      }

      m_ptag = reader.detach_main_tag();

      if (m_ptag == nullptr)
      {

         m_ptag = new tag(nullptr);

         class value * pvalue = new class value(m_ptag);

         m_ptag->baseptra().add(pvalue);

         pvalue->set_value(" ");

      }

      m_pelement = __new(element);

      //m_pelement->m_pbase = new ::html::tag(nullptr);

      m_pelement->initialize_html_elemental(this);

      //m_pelement->initialize_html_element(this);

      m_pelement->load(this, m_ptag);

      m_pform->set_need_layout();

      m_pform->set_need_redraw();

      m_pform->post_redraw();

   }


   void core_data::implement(::draw2d::graphics_pointer & pgraphics)
   {

      m_bImplemented = false;

      __guard_wait(m_bImplement);

      m_pgraphics = pgraphics;

      m_focusptra.erase_all();

      m_pelement->implement(this);

      if (m_pform->m_puserinteractionpointeraChild)
      {

         for (auto & pinteraction : m_pform->m_puserinteractionpointeraChild->interactiona())
         {
            
            ::user::control_event event;

            event.m_eevent = ::user::e_event_initialize_control;

            event.m_puserinteraction = pinteraction;

            event.m_id = pinteraction->m_id;

            m_pform->route_control_event(&event);

         }

      }

      MESSAGE_LINK(e_message_key_down, m_puserinteraction, this, &core_data::on_message_key_down);
      
      m_bImplemented = true;
      
      m_pform->on_form_implemented();
      
   }


   void core_data::on_message_key_down(::message::message * pmessage)
   {

      auto pkey = pmessage->m_pkey;

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

      synchronous_lock synchronouslock(mutex());

      if (!m_bImplemented)
      {

         implement(pgraphics);

      }

      m_pgraphics = pgraphics;

      m_layoutstate1.reset();

      m_layoutstate2.reset();

      m_layoutstate3.reset();

      m_pelement->on_layout(this);

      if (m_pcallback != nullptr)
      {
         ::user::control_event ev;
         ev.m_puserinteraction = m_puserinteraction;
         ev.m_eevent = ::user::e_event_form_initialize;
         m_puserinteraction->on_control_event(&ev);

      }

      m_bLaidout = true;

   }


   void core_data::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      if (!m_bImplemented || !m_bLaidout)
      {

         return;

      }

      synchronous_lock synchronouslock(mutex());

      m_pgraphics = pgraphics;

      pgraphics->set_text_rendering_hint(::write_text::e_rendering_anti_alias);

      pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

      //if(m_strPathName.find_ci("alarms_index") >= 0)
      //{

      //   pgraphics->fill_rectangle(100,100,100,100,argb(190, 255, 0, 0));

      //}

      m_bDrawFirstBody = false;

      m_pelement->_001OnDraw(this);

      //if(m_strPathName.find_ci("alarms_index") >= 0)
      //{

      //   pgraphics->fill_rectangle(200,200,100,100,argb(190, 0, 255, 0));

      //}

   }


   ::html::element * core_data::get_element_by_name(id id)
   {

      return m_pelement->get_element_by_name(id);

   }


   ::html::element * core_data::get_element_by_id(id id)
   {

      return m_pelement->get_element_by_id(id);

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


   string core_data::process_url(const ::string & pszUrl)
   {
   
      string strUrl(pszUrl);

      auto psystem = m_psystem->m_paurasystem;

      if (strUrl.find(":") >= 0)
      {

      }
      else if (strUrl[0] == '\\')
      {

      }
      else if (::str::begins(m_strPathName, "http://") ||
         ::str::begins(m_strPathName, "https://"))
      {

         auto psystem = m_psystem;

         auto purl = psystem->url();

         strUrl = purl->path(m_strPathName, strUrl);

      }
      else
      {

         strUrl = m_strPathName.sibling(strUrl);

         strUrl.replace("/", "\\");

      }

      return strUrl;

   }


   image_pointer core_data::get_image(const ::string & pszUrl)
   {

      string strUrl = process_url(pszUrl);

      auto psystem = get_system()->m_pcoresystem;

      auto pimage = psystem->get_image(this, strUrl);

      return pimage;

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

      synchronous_lock lockImage(pimage->mutex());

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

         m_puserinteraction->post_message(message_on_image_loaded);

      }

   }


   bool core_data::contains(__pointer(::user::interaction) pinteraction)
   {

      return m_uiptra.contains(pinteraction);

   }


   bool core_data::on_create_interaction(__pointer(::user::interaction) pinteraction)
   {
      m_uiptra.add_unique(pinteraction);
      return true;
   }


   bool core_data::open_link(const ::string & pszPath)
   {

      string strPath(pszPath);

      if (::str::begins_eat(strPath, "ext://"))
      {

         auto phyperlink =__create_new < hyperlink>();

         phyperlink->m_strLink = strPath;

         phyperlink->run();

         /*         ::aura::shell_launcher launcher(nullptr, "open", strUrl, "", "", SW_SHOWNORMAL);
         launcher.execute();*/

         return true;

      }

      if (m_pform != nullptr && m_pform->get_document() != nullptr)
      {

         return m_pform->get_document()->on_open_document(pszPath);

      }

      if (strPath.find(":") >= 0)
      {

         return open_document(strPath);

      }
      else if (strPath.Left(1) == "/" || strPath.Left(1) == "\\")
      {

         return open_document(strPath);

      }
      else
      {

         return open_document(m_strPathName.sibling(strPath));

      }

   }


   bool core_data::open_document(const ::payload & varFile)
   {

      //i32 iRetry = 0;

      synchronous_lock lock(mutex());

   //restart:


      //::payload payload;

      //payload = 1;

      //payload = 2;

      //payload[0] = 2;

      //payload["element1"] = pelement1;

      //payload = 3;

      ::file::path pathUrl = varFile.get_file_path();

      varFile["url"] = pathUrl;

      string strDebugUrl1 = varFile.get_file_path();

      if (m_strPathName.has_char())
      {

         varFile["url"] = defer_solve_relative(pathUrl, m_strPathName);

      }

      varFile["http_set"] = get_property_set()["http_propset"].propset();

      bool bNoCache = varFile["nocache"].get_bool();

      byte_array ba;

      //bool bCancel = false;

      ////on_before_navigate(varFile, 0, 0, ba, nullptr, &bCancel);

      //if (bCancel)
      //{

      //   return false;

      //}

      varFile["http_set"]["app"] = get_application();

      //varQuery.propset()["headers"].propset()[__id(accept)] = "text/xml,application/xml,application/xhtml+xml,text/html;q=0.9,text/plain;q=0.8,video/x-mng,image/png,image/jpeg,image/gif;q=0.2,*/*;q=0.1";
      varFile["http_set"]["headers"].propset()[__id(accept)] = "text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8";
      //      varQuery.propset()["headers"].propset()["Accept-Language"] = "en-us,en;q=0.5";
            //varQuery.propset()["headers"].propset()["Accept-Encoding"] = "gzip,deflate";
      //      varQuery.propset()["headers"].propset()["Accept-Charset"] = "ISO-8859-1,utf-8;q=0.7,*;q=0.7";
      varFile["http_set"]["headers"].propset()["Cache-Control"] = "maximum-age=0";

      string str;

   repeat:

      varFile["nocache"] = bNoCache;

      string strDebugUrl2 = varFile.get_file_path();

      auto pcontext = get_context();

      str = pcontext->m_papexcontext->file().as_string(varFile);

      //if (!varFile["http_set"]["get_headers"].propset()["Location"].is_empty())
      //{
      //   string strLocation = varFile["http_set"]["get_headers"].propset()["Location"];
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
      //      varFile = purl->override_if_set_at_source(varFile, varFile["http_set"]["get_headers"].propset()["Location"]);

      //      goto restart;

      //   }
      //}

      if (str.is_empty())
      {
         string strCandidate = m_strPathName / varFile.get_file_path();
         str = pcontext->m_papexcontext->file().as_string(strCandidate);
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
      
      auto estatus = open_html(str);

      if(::failed(estatus))
      {
         
         return false;

      }

      return true;

   }
   
   
   ::e_status     core_data::open_html(const ::string & strParam)
   {
      
      string str(strParam);
      
      delete_contents();
      
      m_strPathName = "html://<see source>";
      
      m_strSource = str;
      
      //auto pset = m_pform->get_form_property_set();
      
      //auto & set = pset->propset();

      if (::is_set(m_pform))
      {

         auto pformcallback = m_pform->get_form_callback();

         if (::is_set(pformcallback))
         {

            pformcallback->property_set_replace(str);

         }

      }
      
      property_set_replace(str);
      
      TRACE("%s", str.c_str());
      
      if (str.has_char())
      {
         
         load(str);
         
      }
      
      return success;

   }


   //void core_data::on_before_navigate(::payload& varFile, u32 nFlags, const ::string & pszTargetFrameName, byte_array& baPostedData, const ::string & pszHeaders, bool* pbCancel)

   //{
   //   if (m_pcallback != nullptr)
   //   {
   //      m_pcallback->on_before_navigate(this, varFile, nFlags, pszTargetFrameName, baPostedData, pszHeaders, pbCancel);

   //   }
   //   else if (m_pform != nullptr)
   //   {
   //      m_pform->on_before_navigate(varFile, nFlags, pszTargetFrameName, baPostedData, pszHeaders, pbCancel);

   //   }
   //}

   
   ::user::form* core_data::get_form()
   {
      
      return m_pform;

   }

   
   __pointer(::user::interaction) core_data::get_frame()
   {
      
      return  (get_form()->get_parent_frame());

   }


   void core_data::implement_and_layout(::html_form * pform)
   {

      ::image_pointer pimage;

      auto estatus = __construct(pimage);
      
      if (!estatus)
      {

         return;

      }

      pimage->create({ 50, 50 });

      if (!estatus)
      {

         return;

      }

      synchronous_lock lock(mutex());

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

      ::image_pointer pimage;

      auto estatus = __construct(pimage);

      if (!estatus)
      {

         return;

      }
      
      estatus = pimage->create( { 50, 50 } );

      if (!estatus)
      {

         return;

      }

      synchronous_lock lock(mutex());

      m_puserinteraction = pform;

      m_pform = pform;

      ::draw2d::graphics_pointer pgraphics;

      pgraphics = pimage->g();

      implement(pgraphics);

   }


   void core_data::layout(::html_form * pform)
   {

      ::image_pointer pimage;

      auto estatus = __construct(pimage);
      
      if (!estatus)
      {

         return;

      }

      estatus = pimage->create( { 50, 50 } );

      if (!estatus)
      {

         return;

      }

      synchronous_lock lock(mutex());

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







