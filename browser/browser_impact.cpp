#include "framework.h"
//#include "aura/update.h"

#include "include/base/cef_bind.h"
#include "include/cef_app.h"
#include "include/views/cef_browser_impact.h"
#include "include/views/cef_window.h"
#include "include/wrapper/cef_closure_task.h"
#include "include/wrapper/cef_helpers.h"
#include "acme/constant/timer.h"
int cef_main(HINSTANCE hInstance, HWND hwnd, ::rectangle_i32 rectangle_i32);

namespace browser
{


   impact::impact(::particle * pparticle):
      object(pparticle),
      impact_base(pparticle)
   {
//      m_pclienthandler = nullptr;
      m_bBrowser = false;
      m_bPendingImageChange = false;

      prop(FONTSEL_IMPACT) = true;
      prop(COLORSEL_IMPACT) = true;


      m_flagNonClient.erase(e_non_client_background);
      m_flagNonClient.erase(e_non_client_focus_rect);

      m_eeffect                  = effect_none;

      m_bOkPending               = false;
      m_frequencyFramesPerSecond = 0.0;


      m_bHelloLayoutOn001Layout  = false;
      m_b001LayoutIgnoreEmpty    = false;


      m_prender                  = nullptr;

      m_bOkPending = true;

      m_bHelloLayoutOn001Layout = true;

      m_b001LayoutIgnoreEmpty = false;

      m_ppcre = psystem->compile_pcre("\\:\\-\\)");

   }

   impact::~impact()
   {
   }

   void impact::assert_ok() const
   {
      user::box::assert_ok();
   }

   void impact::dump(dump_context & dumpcontext) const
   {
      user::box::dump(dumpcontext);
   }

   void impact::install_message_routing(::channel * pchannel)
   {

      impact_base::install_message_routing(pchannel);

      MESSAGE_LINK(MESSAGE_CREATE,pchannel,this,&impact::on_message_create);
      MESSAGE_LINK(MESSAGE_DESTROY, pchannel, this, &impact::on_message_destroy);
      //MESSAGE_LINK(e_message_left_button_down, pchannel, this, &impact::on_message_left_button_down);
      MESSAGE_LINK(e_message_left_button_down, pchannel, this, &impact::_001OnMouse);
      MESSAGE_LINK(e_message_left_button_up, pchannel, this, &impact::_001OnMouse);
      MESSAGE_LINK(e_message_mouse_move, pchannel, this, &impact::_001OnMouse);

   }


   void impact::on_before_initialize_render()
   {


   }


   void impact::on_message_create(::message::message * pmessage)
   {

      ::pointer<::message::create>pcreate(pmessage);

      pcreate->previous();

      if (pcreate->m_bRet)
      {

         return;

      }




      bool bAlternate = string(m_atom).case_insensitive_contains("switcher");

      m_prender = __new(render(get_app(), bAlternate));

      m_prender->m_pimpact = this;

      on_before_initialize_render();

      string strId = get_document()->m_pimpactsystem->m_strMatter;

      m_prender->initialize_render(strId);

      //string strText;

      datastream()->get("cur_color", m_prender->m_hlsForeground);

      datastream()->get("cur_font", m_prender->m_strFontSel);

      datastream()->get("cur_text", m_strNewHelloBrowser);

      if(get_typed_parent<::user::split_impact>() != nullptr)
      {

         if(get_typed_parent<::user::split_impact>()->get_child_by_id("top_edit_impact") != nullptr)
         {

            auto pinteraction = get_typed_parent<::user::split_impact>()->get_child_by_id("top_edit_impact");

            pinteraction->_001SetText(m_strNewHelloBrowser,::e_source_initialize);

         }

      }

      //set_browser(strText);

      if(papp->m_etype == application::type_normal)
      {

         m_prender->begin();

      }

      SetTimer(::e_timer_update_current_area, 300);

   }


   void impact::_001OnTimer(::timer * ptimer)
   {

      if (ptimer->m_uEvent == ::e_timer_update_current_area)
      {

         {

            synchronous_lock synchronouslock(m_pmutexText);

            calc_processed_browser(m_strProcessedHellomultiverse);

         }

         {

            synchronous_lock synchronouslock(m_pmutexText);

            if (m_bPendingImageChange)
            {

               if (::time::now() - m_timeLastImageChange > 750)
               {

                  m_bPendingImageChange = false;

                  string strFork = m_strImage.c_str();

                  synchronouslock.unlock();

                  fork([this, strFork]()
                  {

                     get_document()->on_open_document(strFork);

                  });

               }


            }

         }

      }

   }


   void impact::on_message_destroy(::message::message * pmessage)
   {

   }


   void impact::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

      synchronous_lock synchronouslock(this->synchronization());

      {

         synchronous_lock slText(m_pmutexText);

         if(m_strNewHelloBrowser.is_empty())
         {

            if(m_prender->m_bFastOnEmpty)
            {

               m_prender->m_bFast = true;

            }

            return;

         }

      }

      m_prender->m_bHelloRender = true;

      if(m_bHelloLayoutOn001Layout)
      {

         m_prender->m_bNewLayout = true;

         m_bOkPending = true;

         m_prender->m_bFast = true;

      }
      else
      {

         on_layout(pgraphics);

      }

   }


   void impact::handle(::topic * ptopic, ::context * pcontext)
   {

      impact_base::handle(ptopic, pcontext);

      if (ptopic->m_atom == id_after_change_text)
      {

         auto * peditview = _001TypedWindow < ::userex::top_edit_impact >();

         if (peditview != nullptr && ptopic->user_interaction() == peditview)
         {

            string strText;

            peditview->_001GetText(strText);

            set_browser(strText);

         }

      }


   }


   void impact::_006OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      if (m_pimageBrowser)
      {

         auto rectangleClient = client_rectangle();

         pgraphics->draw(::rectangle_i32(m_pimageBrowser->size()), m_pimageBrowser->g(), m_pimageBrowser->rectangle());

      }

      m_prender->_006OnDraw(pgraphics);

   }



   void impact::on_message_left_button_down(::message::message * pmessage)
   {

      auto pmouse = pmessage->m_union.m_pmouse;

      pmessage->previous();



   }

   void impact::_001OnMouse(::message::message * pmessage)
   {

      auto pmouse = pmessage->m_union.m_pmouse;

      pmessage->previous();

      papp->m_ppaneimpact->m_pimpactLastBilbo = this;

      CefMouseEvent event;

      ::point_i32 point = pmouse->m_point;

      screen_to_client()(point);

      event.x() = point.x();
      event.y() = point.y();

      if (pmouse->m_atom == e_message_left_button_down)
      {

         papp->m_ppaneimpact->m_pimpactLastBilbo = this;

         m_pbrowser->GetHost()->SendMouseClickEvent(event, cef_mouse_button_type_t::MBT_LEFT, false, 1);

      }
      else if (pmouse->m_atom == e_message_left_button_up)
      {

         m_pbrowser->GetHost()->SendMouseClickEvent(event, cef_mouse_button_type_t::MBT_LEFT, true, 1);

      }
      else if (pmouse->m_atom == e_message_mouse_move)
      {

         m_pbrowser->GetHost()->SendMouseMoveEvent(event, false);

      }
      pmouse->m_bRet = true;
   }

   ::user::document * impact::get_document()
   {

      return  (::user::impact::get_document());

   }


   void impact::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

      ::rectangle_i32 rectangleClient;

      client_rectangle(rectangleClient);

      if(rectangleClient.area() <= 0)
         return;


      ::rectangle_i32 rectangle = client_rectangle();

      client_to_screen(rectangle);

      get_top_level()->screen_to_client(rectangle);

      if (rectangle.size() != m_pimageBrowser->size())
      {

         if (papp->get_app()->m_bCefInitialized)
         {
            if (!m_bBrowser)
            {

               m_bBrowser = true;
               CefWindowInfo info;
               //info.SetAsChild(get_handle(), rectangle);
               info.SetAsWindowless(get_handle());

               CefBrowserSettings browserSettings;
               browserSettings.web_security = STATE_DISABLED;
               browserSettings.windowless_frame_rate = 30;
               //            CreateBrow
                           //          Call CefWindowInfo::SetAsWindowless() before passing the CefWindowInfo structure to CefBrowserHost::CreateBrowser().If no parent window is passed to SetAsWindowless some functionality like context menus may not be available.

                           //m_pclienthandler = memory_new ClientHandler(this);
               CreateBrowser(info, browserSettings, CefString("https://ca2.software/"));
               //m_pthreadBrowser = fork([=]()
               //                        // main_async([=]()
               //{

               //   cef_main(psystem->m_hinstance, get_handle(), rectangle);

               //});

            }
            else if (m_pbrowser)
            {

               m_pbrowser->GetHost()->WasResized();
               //auto hwnd = m_pbrowser->GetHost()->GetWindowHandle();
               //auto rectangle = ::rectangle_i32{ 0 };
               //client_rectangle(&rectangle);

               //auto hwnd2 = get_handle();

               //m_pbrowser->

               //::SetWindowPos(hwnd, HWND_TOP, rectangle.left, rectangle.top, rectangle.right - rectangle.left, rectangle.bottom - rectangle.top, SWP_NOZORDER);

               //::set_window_position(::GetWindow(get_handle(), GW_CHILD), HWND_TOP,
               //               rectangle.left,
               //               rectangle.top,
               //               rectangle.width(),
               //               rectangle.height(), 0);

            }

         }

      }

      bool bHover = get_typed_parent < pane_impact >() != nullptr
                    && get_typed_parent < pane_impact >()->m_pimpactLast == this
                    && get_typed_parent < pane_impact >()->get_current_tab_id() == FONTSEL_IMPACT;

      //if(m_prender->m_cx == rectangleClient.width()
      //    && m_prender->m_cy == rectangleClient.height()
      //  && !bHover
      //&& m_prender->m_strNewFont == m_prender->m_strFont)
      //return;

      if (bHover)
      {

         m_prender->m_strFont = m_prender->m_strFontHover;

      }
      else
      {

         m_prender->m_strFont = m_prender->m_strFontSel;

      }

      m_prender->m_cx = rectangleClient.width();

      m_prender->m_cy = rectangleClient.height();

      m_prender->m_rectangleClient = rectangleClient;

      m_prender->m_bNewLayout = true;

      m_bOkPending = true;

      m_prender->m_bFast = true;

   }


   void impact::calc_processed_browser(string & strProcessedHellomultiverse)
   {

      synchronous_lock slText(m_pmutexText);

      string str;

      str = get_browser();

      if (str.c_str() == m_strProcessed.c_str())
      {

         strProcessedHellomultiverse = m_strPostProcessed;

         return;

      }

      m_strProcessed = str;

      auto pFind = str.find("image:");

      if(::is_set(pFind) && (iFind == 0 || !character_isalnum(str[iFind-1])))
      {

         bool bData = str.substr(iFind + strlen("image:")).case_insensitive_begins("data:");

         strsize iFindEnd = str.find(",", iFind + 1);

         if (iFindEnd < 0)
         {

            iFindEnd = str.length();

         }
         else if (bData)
         {

            iFindEnd = str.find(",", iFindEnd + 1);

            if (iFindEnd < 0)
            {

               iFindEnd = str.length();

            }

         }

         strsize iFindImage = iFind + 6;

         string strImage = str.substr(iFindImage, iFindEnd - iFindImage);

         if (m_strImage != strImage)
         {

            m_strImage = strImage.c_str();

            m_timeLastImageChange = ::time::now();

            m_bPendingImageChange = true;

         }

         if (m_prender->m_pimageImage)
         {

            if (str.case_insensitive_begins_eat(m_strImage))
            {

               str.case_insensitive_begins_eat(",");

            }

         }

         strsize iLeft = iFind > 0 ? iFind - 1 : iFind;

         str = str.left(iLeft) + str.substr(iFindEnd);

      }

      strsize_array ia;

      m_ppcre->matches(ia, str);

      if (ia.get_count() >= 2)
      {

         str.Insert(ia[1], "Smile for you too (pcremade |-) !!");

      }

      if(str.case_insensitive_begins_eat("crt:"))
      {

         m_eeffect = effect_crt;

      }
      else
      {

         m_eeffect = effect_none;

      }


      string_array stra;

      stra.add_lines(str);

      for (auto & strLine : stra)
      {

         strLine.Truncate(120);

      }

      str = stra.implode("\n");

      m_strPostProcessed = str;

      strProcessedHellomultiverse = m_strPostProcessed;

   }


   string impact::get_browser()
   {

      synchronous_lock synchronouslock(m_pmutexText);

      if(m_strHelloBrowser.c_str() != m_strNewHelloBrowser.c_str())
      {

         m_strHelloBrowser = m_strNewHelloBrowser;

      }

      if(m_strHelloBrowser.is_empty())
      {

         if(m_prender->m_bAlternate)
         {

            if(m_frequencyFramesPerSecond != 0.0)
            {

               return "Rolling " + papp->m_strAlternateHelloBrowser;

            }
            else
            {

               return papp->m_strAlternateHelloBrowser.c_str();

            }

         }
         else
         {

            if(m_frequencyFramesPerSecond != 0.0)
            {

               return "Rolling " + papp->m_strHelloBrowser;

            }
            else
            {

               return papp->m_strHelloBrowser.c_str();

            }

         }

      }
      else
      {

         return m_strHelloBrowser;

      }

   }


   void impact::defer_check_on_draw_layout()
   {

      if (m_prender != nullptr)
      {

         synchronous_lock synchronouslock(m_pmutexText);

         if (m_strProcessedHellomultiverse != m_prender->m_strHelloBrowser)
         {

            m_prender->m_strHelloBrowser = m_strProcessedHellomultiverse.c_str(); // rationale : string allocation fork *for parallelization*

            synchronouslock.unlock();

            set_need_layout();

         }

      }

   }


   void impact::on_draw_image_layer(::draw2d::graphics_pointer & pgraphics)
   {

      synchronous_lock synchronouslock(this->synchronization());

      if (m_prender->m_bImageEnable && m_prender->m_pimageImage->is_ok())
      {

         ::rectangle_i32 rectangleWork(0, 0, m_prender->m_pimageWork->get_size()->cx(), m_prender->m_pimageWork->get_size()->cy());

         ::rectangle_i32 rectangleImage(0, 0, m_prender->m_pimageImage->get_size()->cx(), m_prender->m_pimageImage->get_size()->cy());

         rectangleImage.FitOnCenterOf(rectangleWork);

         m_pimagePost->get_graphics()->set_alpha_mode(::draw2d::e_alpha_mode_set);

         if (m_prender->m_pimageImageStretched->is_null()
               || m_prender->m_pimageImageStretched->get_size() != rectangleImage->size()
               || m_prender->m_bImageChanged)
         {

            ::size_i32 size = rectangleImage.size();

            m_prender->m_pimageImageStretched->release();
            {

               //   m_prender->m_pimageImageStretched->create(this);

            }

            fork([=]()
            {

/*               ::image_pointer pimage;

/*               if (pimage = create_image(size))
               {

/*                  pimage->stretch_image(m_prender->m_pimageImage);

                  synchronous_lock synchronouslock(this->synchronization());

/*                  m_prender->m_pimageImageStretched = pimage;

                  m_prender->m_bImageChanged = false;

               }

            });
         }

         if (!m_prender->m_bImageChanged && m_prender->m_pimageImageStretched->is_set() && m_prender->m_pimageImageStretched->area() > 0)
         {

            m_pimagePost->g()->draw(rectangleImage, m_prender->m_pimageImageStretched->g());

         }

      }

   }

   void impact::set_browser(string strText)
   {

      string strFork;

      {

         synchronous_lock synchronouslock(m_pmutexText);

         m_strNewHelloBrowser = strText;

         strFork = strText.c_str();

      }

      datastream()->set("cur_text", strFork);

   }

   void impact::OnBrowserCreated(CefRefPtr<CefBrowser> browser)
   {
      m_pbrowser = browser;
   }

   void impact::OnBrowserClosing(CefRefPtr<CefBrowser> browser)
   {
   }

   void impact::OnBrowserClosed(CefRefPtr<CefBrowser> browser)
   {
      if (m_pbrowser != nullptr &&
            m_pbrowser->GetIdentifier() == browser->GetIdentifier())
      {
         m_pbrowser = nullptr;

         //m_pclienthandler->DetachDelegate();
      }
   }

   void impact::OnSetAddress(std::string const & url)
   {
      //if (frame->IsMain())
      //{

      //}

      //auto main = static_cast<CMainFrame*>(m_wndMain);
      //if (main != nullptr)
      //{
      //   auto newurl = CString{ url.c_str() };
      //   if (newurl.Find(m_startUrl) >= 0)
      //      newurl = "";

      //   main->SetUrl(newurl);
      //}
   }

   void impact::OnSetTitle(std::string const & title)
   {
//      ::SetWindowText(m_hWnd, CefString(title).ToWString().c_str());
   }

   void impact::OnSetFullscreen(bool const fullscreen)
   {
      if (m_pbrowser != nullptr)
      {
         if (fullscreen)
         {
            //CefWindowsHelpers::Maximize(m_pbrowser);
         }
         else
         {
            //CefWindowsHelpers::Restore(m_pbrowser);
         }
      }
   }

   void impact::OnSetLoadingState(bool const isLoading,
                                bool const canGoBack,
                                bool const canGoForward)
   {
   }

   //void impact::OnSize(::u32 nType, int cx, int cy)
   //{
   //   CImpact::OnSize(nType, cx, cy);

   //   if (m_pclienthandler != nullptr)
   //   {
   //      if (m_pbrowser != nullptr)
   //      {
   //         auto hwnd = m_pbrowser->GetHost()->GetWindowHandle();
   //         auto rectangle = ::rectangle_i32{ 0 };
   //         client_rectangle(&rectangle);

   //         ::set_window_position(hwnd, HWND_TOP, rectangle.left, rectangle.top, rectangle.right - rectangle.left, rectangle.bottom - rectangle.top, SWP_NOZORDER);
   //      }
   //   }
   //}

   //BOOL impact::PreTranslateMessage(MSG* pMsg)
   //{
   //   if (pMsg->message == e_message_key_down)
   //   {
   //      if (pMsg->wParam == VK_F5)
   //      {
   //         m_pbrowser->Reload();
   //      }
   //   }

   //   return CImpact::PreTranslateMessage(pMsg);
   //}

   
   bool impact::GetRootScreenRect(CefRefPtr<CefBrowser> browser, CefRect & rectangle) 
   {

      auto rectangleWindow = get_top_level()->window_rectangle();

      rectangle.Set(rectangleWindow.left, rectangleWindow.top, rectangleWindow.width(), rectangleWindow.height());

      return true;

   }


   bool impact::GetImpactRect(CefRefPtr<CefBrowser> browser, CefRect& rectangle)
   {

      ::rectangle_i32 rectangleClient = client_rectangle();

      client_to_screen(rectangleClient);

      rectangle.Set(rectangleClient.left, rectangleClient.top, rectangleClient.width(), rectangleClient.height());

      return true;

   }


   void impact::OnPaint(CefRefPtr<CefBrowser> browser,
                      CefRenderHandler::PaintElementType type,
                      const CefRenderHandler::rectList& dirtyRects,
                      const void* buffer,
                      int width,
                      int height)
   {

      synchronous_lock synchronouslock(this->synchronization());

      pixmap p;

      p.init(::size_i32(width, height), (color32_t *) buffer, width * sizeof(color32_t));

/*      m_pimageBrowser->create_image(this, ::size_i32(width, height));

      //m_pimageBrowser->g()->fill_solid_rect_dim(0, 0, width, height, argb(155, 255, 255, 0)) ;

      m_pimageBrowser->map();

      ::copy_colorref(m_pimageBrowser->m_pimpl, &p);

      set_need_redraw();

      post_redraw();

   }


   void impact::OnAddressChange(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, const CefString& url)
   {

      CEF_REQUIRE_UI_THREAD();

      // Only update the address for the main (top-level) frame.
      if (frame->IsMain())
      {

         OnSetAddress(url);

      }

   }


   void impact::OnTitleChange(CefRefPtr<CefBrowser> browser, const CefString& title)
   {
      
      CEF_REQUIRE_UI_THREAD();

      OnSetTitle(title);

   }


   void impact::OnFullscreenModeChange(CefRefPtr<CefBrowser> browser, bool fullscreen)
   {

      CEF_REQUIRE_UI_THREAD();

      OnSetFullscreen(fullscreen);

   }


   void impact::OnAfterCreated(CefRefPtr<CefBrowser> browser)
   {
      
      CEF_REQUIRE_UI_THREAD();

      OnBrowserCreated(browser);

   }

   
   bool impact::DoClose(CefRefPtr<CefBrowser> browser)
   {
      
      CEF_REQUIRE_UI_THREAD();

      OnBrowserClosing(browser);

      return false;

   }


   void impact::OnBeforeClose(CefRefPtr<CefBrowser> browser)
   {
      
      CEF_REQUIRE_UI_THREAD();

      OnBrowserClosed(browser);

   }


   void impact::OnLoadError(CefRefPtr<CefBrowser> browser,
                          CefRefPtr<CefFrame> frame,
                          ErrorCode errorCode,
                          const CefString& errorText,
                          const CefString& failedUrl)
   {
      
      CEF_REQUIRE_UI_THREAD();

      // Don't display an error for downloaded files.
      if (errorCode == ERR_ABORTED)
         return;

      // Display a load error message.
      std::stringstream ss;
      
      ss << "<html><body bgcolor=\"white\">"
         "<h2>Failed to load URL " << std::string(failedUrl) <<
         " with error " << std::string(errorText) << " (" << errorCode <<
         ").</h2></body></html>";

      frame->LoadString(ss.str(), failedUrl);

   }


   void impact::OnLoadingStateChange(CefRefPtr<CefBrowser> browser, bool isLoading, bool canGoBack, bool canGoForward)
   {
      
      CEF_REQUIRE_UI_THREAD();

      OnSetLoadingState(isLoading, canGoBack, canGoForward);

   }


   void impact::CreateBrowser(CefWindowInfo const & info, CefBrowserSettings const & settings, CefString const & url)
   {

      CefBrowserHost::CreateBrowser(info, this, url, settings, nullptr);

   }


} // namespace browser



