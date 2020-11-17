#include "framework.h"
#include "aura/update.h"

#include "include/base/cef_bind.h"
#include "include/cef_app.h"
#include "include/views/cef_browser_view.h"
#include "include/views/cef_window.h"
#include "include/wrapper/cef_closure_task.h"
#include "include/wrapper/cef_helpers.h"
#include "acme/const/timer.h"
int cef_main(HINSTANCE hInstance, HWND hwnd, RECT32 rect);

namespace browser
{


   view::view(::layered * pobjectContext):
      object(pobject),
      impact_base(pobject)
   {
//      m_pclienthandler = nullptr;
      m_bBrowser = false;
      m_bPendingImageChange = false;

      prop(FONTSEL_IMPACT) = true;
      prop(COLORSEL_IMPACT) = true;


      m_flagNonClient.remove(non_client_background);
      m_flagNonClient.remove(non_client_focus_rect);

      m_eeffect                  = effect_none;

      m_bOkPending               = false;
      m_dFps = 0.0;


      m_bHelloLayoutOn001Layout  = false;
      m_b001LayoutIgnoreEmpty    = false;


      m_prender                  = nullptr;

      m_bOkPending = true;

      m_bHelloLayoutOn001Layout = true;

      m_b001LayoutIgnoreEmpty = false;

      m_ppcre = System.create_pcre("\\:\\-\\)");

   }

   view::~view()
   {
   }

   void view::assert_valid() const
   {
      user::box::assert_valid();
   }

   void view::dump(dump_context & dumpcontext) const
   {
      user::box::dump(dumpcontext);
   }

   void view::install_message_routing(::channel * pchannel)
   {

      impact_base::install_message_routing(pchannel);

      MESSAGE_LINK(e_message_create,pchannel,this,&view::_001OnCreate);
      MESSAGE_LINK(e_message_destroy, pchannel, this, &view::_001OnDestroy);
      //MESSAGE_LINK(e_message_left_button_down, pchannel, this, &view::_001OnLButtonDown);
      MESSAGE_LINK(e_message_left_button_down, pchannel, this, &view::_001OnMouse);
      MESSAGE_LINK(e_message_left_button_up, pchannel, this, &view::_001OnMouse);
      MESSAGE_LINK(e_message_mouse_move, pchannel, this, &view::_001OnMouse);

   }


   void view::on_before_initialize_render()
   {


   }


   void view::_001OnCreate(::message::message * pmessage)
   {

      SCAST_PTR(::message::create,pcreate,pmessage);

      pcreate->previous();

      if (pcreate->m_bRet)
      {

         return;

      }




      bool bAlternate = string(m_id).contains_ci("switcher");

      m_prender = __new(render(get_context_application(), bAlternate));

      m_prender->m_pview = this;

      on_before_initialize_render();

      string strId = get_document()->m_pimpactsystem->m_strMatter;

      m_prender->initialize_render(strId);

      //string strText;

      data_get("cur_color", m_prender->m_hlsForeground);

      data_get("cur_font", m_prender->m_strFontSel);

      data_get("cur_text", m_strNewHelloBrowser);

      if(GetTypedParent<::user::split_view>() != nullptr)
      {

         if(GetTypedParent<::user::split_view>()->get_child_by_id("top_edit_view") != nullptr)
         {

            auto pinteraction = GetTypedParent<::user::split_view>()->get_child_by_id("top_edit_view");

            pinteraction->_001SetText(m_strNewHelloBrowser,::source_initialize);

         }

      }

      //set_browser(strText);

      if(Application.m_etype == application::type_normal)
      {

         m_prender->begin();

      }

      SetTimer(::e_timer_update_current_area, 300);

   }


   void view::_001OnTimer(::timer * ptimer)
   {

      if (ptimer->m_uEvent == ::e_timer_update_current_area)
      {

         {

            sync_lock sl(&m_mutexText);

            calc_processed_browser(m_strProcessedHellomultiverse);

         }

         {

            sync_lock sl(&m_mutexText);

            if (m_bPendingImageChange)
            {

               if (millis::now() - m_millisLastImageChange > 750)
               {

                  m_bPendingImageChange = false;

                  string strFork = m_strImage.c_str();

                  sl.unlock();

                  fork([this, strFork]()
                  {

                     get_document()->on_open_document(strFork);

                  });

               }


            }

         }

      }

   }


   void view::_001OnDestroy(::message::message * pmessage)
   {

   }


   void view::on_layout()
   {

      sync_lock sl(mutex());

      {

         sync_lock slText(&m_mutexText);

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

         on_layout(::draw2d::graphics_pointer & pgraphics);

      }

   }


   void view::on_apply(::action * paction)
   {

      impact_base::on_apply(paction);

      if (paction->id() == id_after_change_text)
      {

         auto * peditview = _001TypedWindow < ::userex::top_edit_view >();

         if (peditview != nullptr && paction->m_puserinteraction == peditview)
         {

            string strText;

            peditview->_001GetText(strText);

            set_browser(strText);

         }

      }


   }


   void view::_006OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      if (m_pimageBrowser)
      {

         auto rectClient = get_client_rect();

         pgraphics->draw(::rect(m_pimageBrowser->size()), m_pimageBrowser->g(), m_pimageBrowser->rect());

      }

      m_prender->_006OnDraw(pgraphics);

   }



   void view::_001OnLButtonDown(::message::message * pmessage)
   {

      SCAST_PTR(::message::mouse, pmouse, pmessage);

      pmessage->previous();



   }

   void view::_001OnMouse(::message::message * pmessage)
   {

      SCAST_PTR(::message::mouse, pmouse, pmessage);

      pmessage->previous();

      Application.m_ppaneview->m_pviewLastBilbo = this;

      CefMouseEvent event;

      ::point point = pmouse->m_point;

      _001ScreenToClient(point);

      event.x = point.x;
      event.y = point.y;

      if (pmouse->m_id == e_message_left_button_down)
      {

         Application.m_ppaneview->m_pviewLastBilbo = this;

         m_pbrowser->GetHost()->SendMouseClickEvent(event, cef_mouse_button_type_t::MBT_LEFT, false, 1);

      }
      else if (pmouse->m_id == e_message_left_button_up)
      {

         m_pbrowser->GetHost()->SendMouseClickEvent(event, cef_mouse_button_type_t::MBT_LEFT, true, 1);

      }
      else if (pmouse->m_id == e_message_mouse_move)
      {

         m_pbrowser->GetHost()->SendMouseMoveEvent(event, false);

      }
      pmouse->m_bRet = true;
   }

   ::user::document * view::get_document()
   {

      return  (::user::impact::get_document());

   }


   void view::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

      ::rect rectClient;

      get_client_rect(rectClient);

      if(rectClient.area() <= 0)
         return;


      ::rect rect = get_client_rect();

      client_to_screen(rect);

      GetTopLevel()->screen_to_client(rect);

      if (rect.size() != m_pimageBrowser->size())
      {

         if (Application.get_context_application()->m_bCefInitialized)
         {
            if (!m_bBrowser)
            {

               m_bBrowser = true;
               CefWindowInfo info;
               //info.SetAsChild(get_handle(), rect);
               info.SetAsWindowless(get_handle());

               CefBrowserSettings browserSettings;
               browserSettings.web_security = STATE_DISABLED;
               browserSettings.windowless_frame_rate = 30;
               //            CreateBrow
                           //          Call CefWindowInfo::SetAsWindowless() before passing the CefWindowInfo structure to CefBrowserHost::CreateBrowser().If no parent window is passed to SetAsWindowless some functionality like context menus may not be available.

                           //m_pclienthandler = new ClientHandler(this);
               CreateBrowser(info, browserSettings, CefString("https://ca2.cc/"));
               //m_pthreadBrowser = fork([=]()
               //                        // main_async([=]()
               //{

               //   cef_main(System.m_hinstance, get_handle(), rect);

               //});

            }
            else if (m_pbrowser)
            {

               m_pbrowser->GetHost()->WasResized();
               //auto hwnd = m_pbrowser->GetHost()->GetWindowHandle();
               //auto rect = RECT32{ 0 };
               //get_client_rect(&rect);

               //auto hwnd2 = get_handle();

               //m_pbrowser->

               //::SetWindowPos(hwnd, HWND_TOP, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, SWP_NOZORDER);

               //::set_window_pos(::GetWindow(get_handle(), GW_CHILD), HWND_TOP,
               //               rect.left,
               //               rect.top,
               //               rect.width(),
               //               rect.height(), 0);

            }

         }

      }

      bool bHover = GetTypedParent < pane_view >() != nullptr
                    && GetTypedParent < pane_view >()->m_pviewLast == this
                    && GetTypedParent < pane_view >()->get_cur_tab_id() == FONTSEL_IMPACT;

      //if(m_prender->m_cx == rectClient.width()
      //    && m_prender->m_cy == rectClient.height()
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

      m_prender->m_cx = rectClient.width();

      m_prender->m_cy = rectClient.height();

      m_prender->m_rectClient = rectClient;

      m_prender->m_bNewLayout = true;

      m_bOkPending = true;

      m_prender->m_bFast = true;

   }


   void view::calc_processed_browser(string & strProcessedHellomultiverse)
   {

      sync_lock slText(&m_mutexText);

      string str;

      str = get_browser();

      if (str.c_str() == m_strProcessed.c_str())
      {

         strProcessedHellomultiverse = m_strPostProcessed;

         return;

      }

      m_strProcessed = str;

      strsize iFind = str.find("image:");

      if(iFind >= 0 && (iFind == 0 || !ansi_char_is_alphanumeric(str[iFind-1])))
      {

         bool bData = str.Mid(iFind + strlen("image:")).begins_ci("data:");

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

         string strImage = str.Mid(iFindImage, iFindEnd - iFindImage);

         if (m_strImage != strImage)
         {

            m_strImage = strImage.c_str();

            m_millisLastImageChange = ::millis::now();

            m_bPendingImageChange = true;

         }

         if (m_prender->m_pimageImage)
         {

            if (::str::begins_eat_ci(str, m_strImage))
            {

               ::str::begins_eat_ci(str, ",");

            }

         }

         strsize iLeft = iFind > 0 ? iFind - 1 : iFind;

         str = str.Left(iLeft) + str.Mid(iFindEnd);

      }

      strsize_array ia;

      m_ppcre->matches(ia, str);

      if (ia.get_count() >= 2)
      {

         str.Insert(ia[1], "Smile for you too (pcremade |-) !!");

      }

      if(::str::begins_eat_ci(str, "crt:"))
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


   string view::get_browser()
   {

      sync_lock sl(&m_mutexText);

      if(m_strHelloBrowser.c_str() != m_strNewHelloBrowser.c_str())
      {

         m_strHelloBrowser = m_strNewHelloBrowser;

      }

      if(m_strHelloBrowser.is_empty())
      {

         if(m_prender->m_bAlternate)
         {

            if(m_dFps != 0.0)
            {

               return "Rolling " + Application.m_strAlternateHelloBrowser;

            }
            else
            {

               return Application.m_strAlternateHelloBrowser.c_str();

            }

         }
         else
         {

            if(m_dFps != 0.0)
            {

               return "Rolling " + Application.m_strHelloBrowser;

            }
            else
            {

               return Application.m_strHelloBrowser.c_str();

            }

         }

      }
      else
      {

         return m_strHelloBrowser;

      }

   }


   void view::defer_check_on_draw_layout()
   {

      if (m_prender != nullptr)
      {

         sync_lock sl(&m_mutexText);

         if (m_strProcessedHellomultiverse != m_prender->m_strHelloBrowser)
         {

            m_prender->m_strHelloBrowser = m_strProcessedHellomultiverse.c_str(); // rationale : string allocation fork *for multithreading*

            sl.unlock();

            set_need_layout();

         }

      }

   }


   void view::on_draw_image_layer(::draw2d::graphics_pointer & pgraphics)
   {

      sync_lock sl(mutex());

      if (m_prender->m_bImageEnable && m_prender->m_pimageImage->is_ok())
      {

         ::rect rectWork(0, 0, m_prender->m_pimageWork->get_size()->cx, m_prender->m_pimageWork->get_size()->cy);

         ::rect rectImage(0, 0, m_prender->m_pimageImage->get_size()->cx, m_prender->m_pimageImage->get_size()->cy);

         rectImage.FitOnCenterOf(rectWork);

         m_pimagePost->get_graphics()->set_alpha_mode(::draw2d::alpha_mode_set);

         if (m_prender->m_pimageImageStretched->is_null()
               || m_prender->m_pimageImageStretched->get_size() != rectImage->size()
               || m_prender->m_bImageChanged)
         {

            ::size size = rectImage.size();

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

                  sync_lock sl(mutex());

/*                  m_prender->m_pimageImageStretched = pimage;

                  m_prender->m_bImageChanged = false;

               }

            });
         }

         if (!m_prender->m_bImageChanged && m_prender->m_pimageImageStretched->is_set() && m_prender->m_pimageImageStretched->area() > 0)
         {

            m_pimagePost->g()->draw(rectImage, m_prender->m_pimageImageStretched->g());

         }

      }

   }

   void view::set_browser(string strText)
   {

      string strFork;

      {

         sync_lock sl(&m_mutexText);

         m_strNewHelloBrowser = strText;

         strFork = strText.c_str();

      }

      data_set("cur_text", strFork);

   }

   void view::OnBrowserCreated(CefRefPtr<CefBrowser> browser)
   {
      m_pbrowser = browser;
   }

   void view::OnBrowserClosing(CefRefPtr<CefBrowser> browser)
   {
   }

   void view::OnBrowserClosed(CefRefPtr<CefBrowser> browser)
   {
      if (m_pbrowser != nullptr &&
            m_pbrowser->GetIdentifier() == browser->GetIdentifier())
      {
         m_pbrowser = nullptr;

         //m_pclienthandler->DetachDelegate();
      }
   }

   void view::OnSetAddress(std::string const & url)
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

   void view::OnSetTitle(std::string const & title)
   {
//      ::SetWindowText(m_hWnd, CefString(title).ToWString().c_str());
   }

   void view::OnSetFullscreen(bool const fullscreen)
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

   void view::OnSetLoadingState(bool const isLoading,
                                bool const canGoBack,
                                bool const canGoForward)
   {
   }

   //void view::OnSize(::u32 nType, int cx, int cy)
   //{
   //   CView::OnSize(nType, cx, cy);

   //   if (m_pclienthandler != nullptr)
   //   {
   //      if (m_pbrowser != nullptr)
   //      {
   //         auto hwnd = m_pbrowser->GetHost()->GetWindowHandle();
   //         auto rect = RECT32{ 0 };
   //         get_client_rect(&rect);

   //         ::set_window_pos(hwnd, HWND_TOP, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, SWP_NOZORDER);
   //      }
   //   }
   //}

   //BOOL view::PreTranslateMessage(MSG* pMsg)
   //{
   //   if (pMsg->message == e_message_key_down)
   //   {
   //      if (pMsg->wParam == VK_F5)
   //      {
   //         m_pbrowser->Reload();
   //      }
   //   }

   //   return CView::PreTranslateMessage(pMsg);
   //}

   
   bool view::GetRootScreenRect(CefRefPtr<CefBrowser> browser, CefRect & rect) 
   {

      auto rectWindow = GetTopLevel()->get_window_rect();

      rect.Set(rectWindow.left, rectWindow.top, rectWindow.width(), rectWindow.height());

      return true;

   }


   bool view::GetViewRect(CefRefPtr<CefBrowser> browser, CefRect& rect)
   {

      ::rect rectClient = get_client_rect();

      _001ClientToScreen(rectClient);

      rect.Set(rectClient.left, rectClient.top, rectClient.width(), rectClient.height());

      return true;

   }


   void view::OnPaint(CefRefPtr<CefBrowser> browser,
                      CefRenderHandler::PaintElementType type,
                      const CefRenderHandler::RectList& dirtyRects,
                      const void* buffer,
                      int width,
                      int height)
   {

      sync_lock sl(mutex());

      pixmap p;

      p.init(::size(width, height), (color32_t *) buffer, width * sizeof(color32_t));

/*      m_pimageBrowser->create_image(this, ::size(width, height));

      //m_pimageBrowser->g()->fill_solid_rect_dim(0, 0, width, height, ARGB(155, 255, 255, 0)) ;

      m_pimageBrowser->map();

      ::copy_colorref(m_pimageBrowser->m_pimpl, &p);

      set_need_redraw();

      post_redraw();

   }


   void view::OnAddressChange(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, const CefString& url)
   {

      CEF_REQUIRE_UI_THREAD();

      // Only update the address for the main (top-level) frame.
      if (frame->IsMain())
      {

         OnSetAddress(url);

      }

   }


   void view::OnTitleChange(CefRefPtr<CefBrowser> browser, const CefString& title)
   {
      
      CEF_REQUIRE_UI_THREAD();

      OnSetTitle(title);

   }


   void view::OnFullscreenModeChange(CefRefPtr<CefBrowser> browser, bool fullscreen)
   {

      CEF_REQUIRE_UI_THREAD();

      OnSetFullscreen(fullscreen);

   }


   void view::OnAfterCreated(CefRefPtr<CefBrowser> browser)
   {
      
      CEF_REQUIRE_UI_THREAD();

      OnBrowserCreated(browser);

   }

   
   bool view::DoClose(CefRefPtr<CefBrowser> browser)
   {
      
      CEF_REQUIRE_UI_THREAD();

      OnBrowserClosing(browser);

      return false;

   }


   void view::OnBeforeClose(CefRefPtr<CefBrowser> browser)
   {
      
      CEF_REQUIRE_UI_THREAD();

      OnBrowserClosed(browser);

   }


   void view::OnLoadError(CefRefPtr<CefBrowser> browser,
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


   void view::OnLoadingStateChange(CefRefPtr<CefBrowser> browser, bool isLoading, bool canGoBack, bool canGoForward)
   {
      
      CEF_REQUIRE_UI_THREAD();

      OnSetLoadingState(isLoading, canGoBack, canGoForward);

   }


   void view::CreateBrowser(CefWindowInfo const & info, CefBrowserSettings const & settings, CefString const & url)
   {

      CefBrowserHost::CreateBrowser(info, this, url, settings, nullptr);

   }


} // namespace browser



