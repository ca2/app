#include "framework.h"
#include "aura/id.h"
#include "_.h"
#include "core_data.h"


namespace html
{


   core_data::image::image()
   {

      defer_create_mutex();

   }


   bool core_data::image::load_image()
   {

      m_pimage = ::object::load_image(m_strPath);

      return m_pimage;

   }


   core_data::core_data()
   {

      defer_create_mutex();

      m_pcoredata = this;

      m_elemental.m_pdata = this;
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

      ::aura::del(m_ptag);

      m_pform = nullptr;

   }

   ::estatus core_data::initialize_html_data(html_data * pdata)
   {

      auto estatus = ::html_data::initialize_html_data(pdata);

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }

   //i64 core_data::add_ref()
   //{

   //   return ::object::add_ref(OBJ_REF_DBG_ARGS);

   //}


   //i64 core_data::dec_ref()
   //{

   //   return ::object::dec_ref(OBJ_REF_DBG_ARGS);

   //}


   font * core_data::get_font(elemental * pelemental)
   {

      i32 iFont = -1;

      if (pelemental->m_pimpl->m_bHover)
      {

         if (!pelemental->m_pimpl->m_mapFont.lookup("hover", iFont))
         {

            iFont = create_font(pelemental);
            pelemental->m_pimpl->m_mapFont.set_at("hover", iFont);
         }
         return m_fonta.element_at(iFont);
      }
      else if (pelemental->m_pimpl->has_link())
      {
         if (!pelemental->m_pimpl->m_mapFont.lookup("link", iFont))
         {
            iFont = create_font(pelemental);
            pelemental->m_pimpl->m_mapFont.set_at("link", iFont);
         }
         return m_fonta.element_at(iFont);
      }
      else
      {
         if (!pelemental->m_pimpl->m_mapFont.lookup("", iFont))
         {
            iFont = create_font(pelemental);
            pelemental->m_pimpl->m_mapFont.set_at("", iFont);
         }
         return m_fonta.element_at(iFont);
      }

   }


   i32 core_data::create_font(elemental * pelemental)
   {

      string strSubClass;

      class font font;

      if (!pelemental->m_pimpl->m_bHover
         || !pelemental->m_pstyle->get_text("font-family", "hover", this, pelemental, font.m_strFamily))
      {
         if (!pelemental->m_pimpl->has_link()
            || !pelemental->m_pstyle->get_text("font-family", "link", this, pelemental, font.m_strFamily))
         {
            pelemental->m_pstyle->get_text("font-family", "", this, pelemental, font.m_strFamily);
         }
      }
      if (!pelemental->m_pimpl->m_bHover
         || !pelemental->m_pstyle->get_text("font-size", "hover", this, pelemental, font.m_strSize))
      {
         if (!pelemental->m_pimpl->has_link()
            || !pelemental->m_pstyle->get_text("font-sizef", "link", this, pelemental, font.m_strSize))
         {
            pelemental->m_pstyle->get_text("font-size", "", this, pelemental, font.m_strSize);
         }
      }
      if (!pelemental->m_pimpl->m_bHover
         || !pelemental->m_pstyle->get_text("font-weight", "hover", this, pelemental, font.m_strWeight))
      {
         if (!pelemental->m_pimpl->has_link()
            || !pelemental->m_pstyle->get_text("font-weight", "link", this, pelemental, font.m_strWeight))
         {
            pelemental->m_pstyle->get_text("font-weight", "", this, pelemental, font.m_strWeight);
         }
      }
      if (pelemental->m_pimpl->m_bHover
         && !pelemental->m_pstyle->get_text("text-decoration", "hover", this, pelemental, font.m_strTextDecoration))
      {
         if (pelemental->m_pimpl->has_link()
            && !pelemental->m_pstyle->get_text("text-decoration", "link", this, pelemental, font.m_strTextDecoration))
         {
            pelemental->m_pstyle->get_text("text-decoration", "", this, pelemental, font.m_strTextDecoration);
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
      pfont->create(get_context_object());
      m_fonta.add(pfont);
      pfont->m_iIndex = (i32)m_fonta.get_upper_bound();
      return (i32)pfont->m_iIndex;
   }


   void core_data::delete_contents()
   {

      sync_lock lock(mutex());

      destroy();

   }


   void core_data::update(::update * pupdate)
   {

      html_data::update(pupdate);

   }


   void core_data::destroy()
   {

      m_focusptra.remove_all();

      m_elemental.destroy(this);

      m_bImplemented = false;

      m_bLaidout = false;

   }


   void core_data::delete_implementation()
   {

      m_focusptra.remove_all();

      m_elemental.delete_implementation(this);

      m_bImplemented = false;

   }


   void core_data::load(const char * psz)
   {

      delete_contents();

      auto phtmlreader = __create_new < lite_html_reader >();

      ::html::reader reader;

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

      m_elemental.load(this, m_ptag);

      m_pform->set_need_layout();

      m_pform->set_need_redraw();

      m_pform->post_redraw();

   }


   void core_data::implement(::draw2d::graphics_pointer & pgraphics)
   {

      __guard_wait(m_bImplement);

      m_pgraphics = pgraphics;

      m_focusptra.remove_all();

      m_elemental.implement(this);

      IGUI_MSG_LINK(WM_KEYDOWN, m_puserinteraction, this, &core_data::_001OnKeyDown);

      m_bImplemented = true;

   }


   void core_data::_001OnKeyDown(::message::message * pmessage)
   {

      SCAST_PTR(::message::key, pkey, pmessage);

      if (pkey->m_ekey == ::user::key_tab)
      {

         ::user::primitive * pfocus = Session.get_keyboard_focus();

         if (pfocus != nullptr)
            pfocus = pfocus->keyboard_get_next_focusable();

         if (pfocus != nullptr)
            Session.set_keyboard_focus(pfocus);

         pkey->m_bRet = true;

         return;

      }

   }


   void core_data::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

      sync_lock sl(mutex());

      if (!m_bImplemented)
      {

         implement(pgraphics);

      }

      m_pgraphics = pgraphics;

      m_layoutstate1.reset();

      m_layoutstate2.reset();

      m_layoutstate3.reset();

      m_elemental.on_layout(this);

      if (m_pcallback != nullptr)
      {
         ::user::control_event ev;
         ev.m_puie = m_puserinteraction;
         ev.m_eevent = ::user::event_form_initialize;
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

      sync_lock sl(mutex());

      m_pgraphics = pgraphics;

      //if(m_strPathName.find_ci("alarms_index") >= 0)
      //{

      //   pgraphics->fill_rect(100,100,100,100,ARGB(190, 255, 0, 0));

      //}

      m_bDrawFirstBody = false;

      m_elemental._001OnDraw(this);

      //if(m_strPathName.find_ci("alarms_index") >= 0)
      //{

      //   pgraphics->fill_rect(200,200,100,100,ARGB(190, 0, 255, 0));

      //}

   }


   elemental * core_data::get_element_by_name(id id)
   {

      return m_elemental.get_element_by_name(id);

   }


   elemental * core_data::get_element_by_id(id id)
   {

      return m_elemental.get_element_by_id(id);

   }


   void core_data::layout_state1::reset()
   {

      m_bHasChar = false;

      m_cxMax.remove_all();

      m_cxMax.add(0.f);

      m_cxa.remove_all();

      m_cxa.add(0.f);

      m_cya.remove_all();

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

      //      m_cyStack.remove_all();
      m_yParent.remove_all();
      m_cya.remove_all();
      m_xParent.remove_all();
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


   string core_data::process_url(const char * pszUrl)
   {
   
      string strUrl(pszUrl);

      if (strUrl.find(":") >= 0)
      {

      }
      else if (strUrl[0] == '\\')
      {

      }
      else if (::str::begins(m_strPathName, "http://") ||
         ::str::begins(m_strPathName, "https://"))
      {

         strUrl = System.url().path(m_strPathName, strUrl);

      }
      else
      {

         strUrl = m_strPathName.sibling(strUrl);

         strUrl.replace("/", "\\");

      }

      return strUrl;

   }


   image_pointer core_data::get_image(const char* pszUrl)
   {

      string strUrl = process_url(pszUrl);

      auto pimage = System.get_image(this, strUrl);

      return pimage;

   }


   void core_data::load_image_asynch(image* pimage)
   {

      fork([=]()
         {

            if (load_image(pimage))
            {

               on_image_loaded(pimage);

            }

         });

   }


   bool core_data::load_image(image* pimage)
   {

      sync_lock lockImage(pimage->mutex());

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

      UNREFERENCED_PARAMETER(pimage);

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


   bool core_data::open_link(const char* pszPath)
   {

      string strPath(pszPath);

      if (::str::begins_eat(strPath, "ext://"))
      {

         Context.hyperlink().open_link(strPath);

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


   bool core_data::open_document(const var & varFile)
   {

      //i32 iRetry = 0;

      sync_lock lock(mutex());

   //restart:


      //var var;

      //var = 1;

      //var = 2;

      //var[0] = 2;

      //var["element1"] = pelement1;

      //var = 3;

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

      //bool bCancel = FALSE;

      ////on_before_navigate(varFile, 0, 0, ba, nullptr, &bCancel);

      //if (bCancel)
      //{

      //   return false;

      //}

      varFile["http_set"]["app"] = get_context_application();

      //varQuery.propset()["headers"].propset()[__id(accept)] = "text/xml,application/xml,application/xhtml+xml,text/html;q=0.9,text/plain;q=0.8,video/x-mng,image/png,image/jpeg,image/gif;q=0.2,*/*;q=0.1";
      varFile["http_set"]["headers"].propset()[__id(accept)] = "text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8";
      //      varQuery.propset()["headers"].propset()["Accept-Language"] = "en-us,en;q=0.5";
            //varQuery.propset()["headers"].propset()["Accept-Encoding"] = "gzip,deflate";
      //      varQuery.propset()["headers"].propset()["Accept-Charset"] = "ISO-8859-1,utf-8;q=0.7,*;q=0.7";
      varFile["http_set"]["headers"].propset()["Cache-Control"] = "MAX-age=0";

      string str;

   repeat:

      varFile["nocache"] = bNoCache;

      string strDebugUrl2 = varFile.get_file_path();

      str = Context.file().as_string(varFile);

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
      //      varFile = System.url().override_if_set_at_source(varFile, varFile["http_set"]["get_headers"].propset()["Location"]);

      //      goto restart;

      //   }
      //}

      if (str.is_empty())
      {
         string strCandidate = m_strPathName / varFile.get_file_path();
         str = Context.file().as_string(strCandidate);
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
   
   
   ::estatus     core_data::open_html(const ::string & strParam)
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


   //void core_data::on_before_navigate(var& varFile, u32 nFlags, const char* pszTargetFrameName, byte_array& baPostedData, const char* pszHeaders, bool* pbCancel)

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
      
      return  (get_form()->GetParentFrame());

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

      sync_lock lock(mutex());

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

      sync_lock lock(mutex());

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

      sync_lock lock(mutex());

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







