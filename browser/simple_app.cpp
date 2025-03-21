// Copyright (c) 2013 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.
#include "framework.h"
#include "simple_app.h"

#include "include/cef_browser.h"
#include "include/cef_command_line.h"
#include "include/views/cef_browser_impact.h"
#include "include/views/cef_window.h"
#include "include/wrapper/cef_helpers.h"
#include "simple_handler.h"

namespace
{

// When using the Views framework this object provides the delegate
// implementation for the CefWindow that hosts the Views-based browser.
   class SimpleWindowDelegate : public CefWindowDelegate
   {
   public:
      explicit SimpleWindowDelegate(CefRefPtr<CefBrowserView> browser_impact)
         : browser_impact_(browser_impact) {}

      void OnWindowCreated(CefRefPtr<CefWindow> window) OVERRIDE
      {
         // Add the browser impact and show the window.
         window->AddChildView(browser_impact_);
         window->Show();

         // Give keyboard focus to the browser impact.
         browser_impact_->RequestFocus();
      }

      void OnWindowDestroyed(CefRefPtr<CefWindow> window) OVERRIDE
      {
         browser_impact_ = nullptr;
      }

      bool CanClose(CefRefPtr<CefWindow> window) OVERRIDE
      {
         // Allow the window to close if the browser says it's OK.
         CefRefPtr<CefBrowser> browser = browser_impact_->GetBrowser();
         if (browser)
            return browser->GetHost()->TryCloseBrowser();
         return true;
      }

   private:
      CefRefPtr<CefBrowserView> browser_impact_;

      IMPLEMENT_REFCOUNTING(SimpleWindowDelegate);
      DISALLOW_COPY_AND_ASSIGN(SimpleWindowDelegate);
   };

}  // namespace

SimpleApp::SimpleApp() { m_bCefInitialized = false; }

void SimpleApp::OnContextInitialized()
{
   CEF_REQUIRE_UI_THREAD();

   CefRefPtr<CefCommandLine> command_line =
   CefCommandLine::GetGlobalCommandLine();

#if defined(OS_WIN) || defined(OS_LINUX)
   // Create the browser using the Views framework if "--use-views" is specified
   // via the command-line. Otherwise, create the browser using the native
   // platform framework. The Views framework is currently only supported on
   // Windows and Linux.
   const bool use_impacts = command_line->HasSwitch("use-views");
#else
   const bool use_impacts = false;
#endif

   m_bCefInitialized = true;

//   // SimpleHandler implements browser-level callbacks.
//   CefRefPtr<SimpleHandler> handler(___new SimpleHandler(use_impacts));
//
//   // Specify CEF browser settings here.
//   CefBrowserSettings browser_settings;
//
//   std::string url;
//
//   // Check if a "--url=" value was provided via the command-line. If so, use
//   // that instead of the default URL.
//   url = command_line->GetSwitchValue("url");
//   if (url.empty())
//      url = "http://www.google.com";
//
//   if (use_impacts)
//   {
//      // Create the BrowserImpact.
//      CefRefPtr<CefBrowserView> browser_impact = CefBrowserImpact::CreateBrowserView(
//            handler, url, browser_settings, nullptr, nullptr);
//
//      // Create the Window. It will show itself after creation.
//      CefWindow::CreateTopLevelWindow(___new SimpleWindowDelegate(browser_impact));
//   }
//   else
//   {
//      // Information used when creating the native window.
//      CefWindowInfo window_info;
//
//#if defined(OS_WIN)
//      // On Windows we need to specify certain flags that will be passed to
//      // CreateWindowEx().
//      //window_info.SetAsPopup(nullptr, "browser");
//#endif
//      CefWindowInfo info;
//      window_info.SetAsChild(m_hwnd, m_rectangle);
//      // Create the first browser window.
//      CefBrowserHost::CreateBrowser(window_info, handler, url, browser_settings,
//                                    nullptr);
//   }
}
