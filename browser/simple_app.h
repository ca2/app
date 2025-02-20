// Copyright (c) 2013 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.

#ifndef CEF_TESTS_BROWSER_SIMPLE_APP_H_
#define CEF_TESTS_BROWSER_SIMPLE_APP_H_

#include "include/cef_app.h"

// Implement application-level callbacks for the browser process.
class SimpleApp : public CefApp, public CefBrowserProcessHandler
{
public:

   bool m_bCefInitialized;

   //HWND m_hwnd;
   //::int_rectangle m_rectangle;
   SimpleApp();

   // CefApp methods:
   virtual CefRefPtr<CefBrowserProcessHandler> GetBrowserProcessHandler()
   OVERRIDE
   {
      return this;
   }

   // CefBrowserProcessHandler methods:
   virtual void OnContextInitialized() OVERRIDE;

private:
   // Include the default object counting implementation.
   IMPLEMENT_REFCOUNTING(SimpleApp);
};

#endif  // CEF_TESTS_BROWSER_SIMPLE_APP_H_
