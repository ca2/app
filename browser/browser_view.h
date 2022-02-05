#pragma once


#include "base/cef_lock.h"
#include "include/cef_client.h"
#include "include/cef_render_handler.h"

//class ClientHandler : public CefClient,
//   public CefDisplayHandler,
//   public CefLifeSpanHandler,
//   public CefLoadHandler
//{
//public:
//   // Implement this interface to receive notification of ClientHandler
//   // events. The methods of this class will be called on the main thread.
//   class Delegate
//   {
//   public:
//      // Called when the browser is created.
//      virtual void OnBrowserCreated(CefRefPtr<CefBrowser> browser) = 0;
//
//      // Called when the browser is closing.
//      virtual void OnBrowserClosing(CefRefPtr<CefBrowser> browser) = 0;
//
//      // Called when the browser has been closed.
//      virtual void OnBrowserClosed(CefRefPtr<CefBrowser> browser) = 0;
//
//      // Set the window URL address.
//      virtual void OnSetAddress(std::string const & url) = 0;
//
//      // Set the window title.
//      virtual void OnSetTitle(std::string const & title) = 0;
//
//      // Set fullscreen mode.
//      virtual void OnSetFullscreen(bool const fullscreen) = 0;
//
//      // Set the loading state.
//      virtual void OnSetLoadingState(bool const isLoading,
//                                     bool const canGoBack,
//                                     bool const canGoForward) = 0;
//
//
//   protected:
//      virtual ~Delegate() {}
//   };
//
//public:
//   ClientHandler(Delegate* delegate);
//   ~ClientHandler();
//
//
//   // CefClient methods:
//   virtual CefRefPtr<CefDisplayHandler> GetDisplayHandler() override { return this; }
//   virtual CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler() override { return this; }
//   virtual CefRefPtr<CefLoadHandler> GetLoadHandler() override { return this; }
//
//   // CefDisplayHandler methods:
//   virtual void OnAddressChange(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, const CefString& url) override;
//   virtual void OnTitleChange(CefRefPtr<CefBrowser> browser, const CefString& title) override;
//   virtual void OnFullscreenModeChange(CefRefPtr<CefBrowser> browser, bool fullscreen) override;
//
//   // CefLifeSpanHandler methods:
//   virtual void OnAfterCreated(CefRefPtr<CefBrowser> browser) override;
//   virtual bool DoClose(CefRefPtr<CefBrowser> browser) override;
//   virtual void OnBeforeClose(CefRefPtr<CefBrowser> browser) override;
//
//   // CefLoadHandler methods:
//   virtual void OnLoadingStateChange(CefRefPtr<CefBrowser> browser,
//                                     bool isLoading,
//                                     bool canGoBack,
//                                     bool canGoForward) override;
//
//   virtual void OnLoadError(CefRefPtr<CefBrowser> browser,
//                            CefRefPtr<CefFrame> frame,
//                            ErrorCode errorCode,
//                            const CefString& errorText,
//                            const CefString& failedUrl) override;
//
//   // This object may outlive the Delegate object so it's necessary for the
//   // Delegate to detach itself before destruction.
//   void DetachDelegate();
//
//private:
//
//   // Include the default object counting implementation.
//   IMPLEMENT_REFCOUNTING(ClientHandler);
//   // Include the default locking implementation.
//   IMPLEMENT_LOCKING(ClientHandler);
//
//private:
//   Delegate* m_delegate;
//};
namespace browser
{


   class CLASS_DECL_APP_BROWSER impact :
      virtual public impact_base,
      public CefClient,
      public CefRenderHandler,
      public CefDisplayHandler,
      public CefLifeSpanHandler,
      public CefLoadHandler

   {
   public:

      void CreateBrowser(CefWindowInfo const & info, CefBrowserSettings const & settings, CefString const & url);

      void OnPaint(CefRefPtr<CefBrowser> browser,
                   CefRenderHandler::PaintElementType type,
                   const CefRenderHandler::rectList& dirtyRects,
                   const void* buffer,
                   int width,
                   int height);

      void AddRef() const
      {

         ((impact *)this)->increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

      }

      bool Release() const
      {

         return ((impact *)this)->release() == 0;

      }

      bool HasOneRef() const
      {

         return m_countReference == 1;

      }

      bool HasAtLeastOneRef() const
      {

         return m_countReference >= 1;

      }
      ///
      // Called to retrieve the impact rectangle_i32 which is relative to screen
      // coordinates. Return true if the rectangle_i32 was provided.
      ///
      /*--cef()--*/
      virtual bool GetRootScreenRect(CefRefPtr<CefBrowser> browser, CefRect & rectangle) override;
      virtual bool GetViewRect(CefRefPtr<CefBrowser> browser, CefRect& rectangle) override;

      virtual CefRefPtr<CefRenderHandler> GetRenderHandler() override { return this; }
      virtual CefRefPtr<CefDisplayHandler> GetDisplayHandler() override { return this; }
      virtual CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler() override { return this; }
      virtual CefRefPtr<CefLoadHandler> GetLoadHandler() override { return this; }

      //   // CefDisplayHandler methods:
      virtual void OnAddressChange(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, const CefString& url) override;
      virtual void OnTitleChange(CefRefPtr<CefBrowser> browser, const CefString& title) override;
      virtual void OnFullscreenModeChange(CefRefPtr<CefBrowser> browser, bool fullscreen) override;
      //   // CefLifeSpanHandler methods:
      virtual void OnAfterCreated(CefRefPtr<CefBrowser> browser) override;
      virtual bool DoClose(CefRefPtr<CefBrowser> browser) override;
      virtual void OnBeforeClose(CefRefPtr<CefBrowser> browser) override;

      //   // CefLoadHandler methods:
      virtual void OnLoadingStateChange(CefRefPtr<CefBrowser> browser,
                                        bool isLoading,
                                        bool canGoBack,
                                        bool canGoForward) override;

      virtual void OnLoadError(CefRefPtr<CefBrowser> browser,
                               CefRefPtr<CefFrame> frame,
                               ErrorCode errorCode,
                               const CefString& errorText,
                               const CefString& failedUrl) override;

      //The CefRenderHandler::GetViewRect() method will be called to retrieve the desired impact rectangle.
      //The CefRenderHandler::OnPaint() method will be called to provide invalid regions and the updated pixel buffer.The cefclient application draws the buffer using OpenGL but your application can use whatever technique you prefer.
      //To resize the browser call CefBrowserHost::WasResized().This will result in a call to GetViewRect() to retrieve the new size_i32 followed by a call to OnPaint().
      //Call the CefBrowserHost::SendXXX() methods to notify the browser of mouse, keyboard and focus events.
      //Call CefBrowserHost::CloseBrowser() to destroy browser.
      ::task_pointer m_pthreadBrowser;
      string                  m_strServer;
      ::image_pointer        m_pimageAi1;
      ::image_pointer        m_pimageAi2;
      ::image_pointer          m_pimageBrowser;
      string                  m_strImage;
      ::image_pointer        m_pimageColor;

      bool                    m_bOkPending;

      bool m_bBrowser;
      bool                    m_bHelloLayoutOn001Layout;
      bool                    m_b001LayoutIgnoreEmpty;

      string                  m_strProcessed;
      string                  m_strPostProcessed;
      string                  m_strProcessedHellomultiverse;

      ::duration m_durationLastImageChange;
      bool                    m_bPendingImageChange;
//      CefRefPtr <ClientHandler>       m_pclienthandler;
      CefRefPtr<CefBrowser>   m_pbrowser;

      impact(::object * pobject);
      virtual ~impact();

      void assert_valid() const override;
      void dump(dump_context & dumpcontext) const override;

      virtual i64 increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS)
      {
         return ::object::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);
      }
      virtual i64 decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS)
      {
         return ::object::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);
      }


      // Called when the browser is created.
      virtual void OnBrowserCreated(CefRefPtr<CefBrowser> browser);

      // Called when the browser is closing.
      virtual void OnBrowserClosing(CefRefPtr<CefBrowser> browser);

      // Called when the browser has been closed.
      virtual void OnBrowserClosed(CefRefPtr<CefBrowser> browser);

      // Set the window URL address.
      virtual void OnSetAddress(std::string const & url);

      // Set the window title.
      virtual void OnSetTitle(std::string const & title);

      // Set fullscreen mode.
      virtual void OnSetFullscreen(bool const fullscreen);

      // Set the loading state.
      virtual void OnSetLoadingState(bool const isLoading,
                                     bool const canGoBack,
                                     bool const canGoForward);

      void install_message_routing(::channel * pchannel) override;

      virtual void _006OnDraw(::draw2d::graphics_pointer & pgraphics);

      virtual void handle(::topic * ptopic, ::context * pcontext) override;

      ::user::document * get_document();

      virtual void on_before_initialize_render();


      virtual void _001OnTimer(::timer * ptimer) override;


      virtual void on_layout(::draw2d::graphics_pointer & pgraphics);

      DECLARE_MESSAGE_HANDLER(on_message_create);
      DECLARE_MESSAGE_HANDLER(on_message_destroy);
      DECLARE_MESSAGE_HANDLER(on_message_left_button_down);
      DECLARE_MESSAGE_HANDLER(_001OnMouse);

      virtual string get_browser();

      virtual void calc_processed_browser(string & str);

      virtual void set_browser(string strText);

      virtual void defer_check_on_draw_layout();
      virtual void on_draw_image_layer(::draw2d::graphics_pointer & pgraphics);


   };


} // namespace browser



