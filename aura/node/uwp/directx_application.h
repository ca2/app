#pragma once


namespace universal_windows
{


   ref class directx_framework_view :
      public impact
   {
   internal:

      ::winrt::Windows::Foundation::Point                      m_pointLastCursor;

      ::u32                                           m_dwMouseMoveThrottle;

      millis                                          m_millisLastMouseMove;

      ::winrt::Windows::UI::ViewManagement::UISettings ^     m_puisettings;

      String ^                                        m_strId;

      impact ^                                        m_impact;

      directx_base ^                                  m_directx;

      bool                                            m_bFontopusShift;

      ::mutex                                         m_mutex;

      __pointer(directx_interaction)                  m_pdxi;

      bool                                            m_bLeftButton;

      bool                                            m_bMiddleButton;

      bool                                            m_bRightButton;

      ::winrt::Windows::Foundation::Rect                       m_rectLastWindowRect;
      ::winrt::Windows::Foundation::Rect                       m_rectInputContentRect;
      ::winrt::Windows::Foundation::Rect                       m_rectInputSelectionRect;


      directx_framework_view(::aura::system * psystem,String ^ strId);


      void install_directx_application_message_routing();

      void initialize_directx_application();

      virtual widestring get_input_text() override;
      virtual bool set_input_text(const widestring & wstr) override;


      //::aura::system * get_context_system() const;

   public:





      // IFrameworkView Methods
      virtual void Initialize(_In_ ::winrt::Windows::ApplicationModel::Core::CoreApplicationView^ applicationView) override;
      virtual void SetWindow(_In_ ::winrt::Windows::UI::Core::CoreWindow^ window)override;
      virtual void Load(_In_ String^ entryPoint)override;
      virtual void Run()override;
      virtual void Uninitialize()override;


      virtual ::winrt::Windows::Foundation::Rect get_window_rect() override;
      virtual ::winrt::Windows::Foundation::Point get_cursor_position() override;

      virtual ::winrt::Windows::Foundation::Rect get_input_content_rect() override;
      virtual ::winrt::Windows::Foundation::Rect get_input_selection_rect() override;


      virtual ~directx_framework_view();

   private:


      void OnUISettingsColorValuesChange(::winrt::Windows::UI::ViewManagement::UISettings^, Platform::Object^);


      // Event Handlers
      void OnWindowSizeChanged(
      _In_ ::winrt::Windows::UI::Core::CoreWindow^ sender,
      _In_ ::winrt::Windows::UI::Core::WindowSizeChangedEventArgs^ args
      );

      void on_window_size_changed(::winrt::Windows::UI::Core::CoreWindow ^ sender, const ::size_i32 & size);

      void DpiChanged(::winrt::Windows::Graphics::Display::DisplayInformation ^ sender, Object ^ obj);

      void DisplayContentsInvalidated(::winrt::Windows::Graphics::Display::DisplayInformation ^ sender, Object ^ obj);

      void OnActivated(
      _In_ ::winrt::Windows::ApplicationModel::Core::CoreApplicationView^ applicationView,
      _In_ ::winrt::Windows::ApplicationModel::Activation::IActivatedEventArgs^ args
      );

      void OnSuspending(
      _In_ Object^ sender,
      _In_ ::winrt::Windows::ApplicationModel::SuspendingEventArgs^ args
      );

      void OnResuming(
      _In_ Object^ sender,
      _In_ Object^ args
      );

      void OnWindowClosed(::winrt::Windows::UI::Core::CoreWindow ^ sender, ::winrt::Windows::UI::Core::CoreWindowEventArgs ^ args);
      void OnWindowVisibilityChanged(::winrt::Windows::UI::Core::CoreWindow^, ::winrt::Windows::UI::Core::VisibilityChangedEventArgs^ args);

      void OnPointerMoved(::winrt::Windows::UI::Core::CoreWindow^, ::winrt::Windows::UI::Core::PointerEventArgs^ args);

      void OnCharacterReceived(::winrt::Windows::UI::Core::CoreWindow^, ::winrt::Windows::UI::Core::CharacterReceivedEventArgs^ args);
      void OnKeyDown(::winrt::Windows::UI::Core::CoreWindow^, ::winrt::Windows::UI::Core::KeyEventArgs^ args);
      void OnKeyUp(::winrt::Windows::UI::Core::CoreWindow^, ::winrt::Windows::UI::Core::KeyEventArgs^ args);
      void OnPointerPressed(::winrt::Windows::UI::Core::CoreWindow^, ::winrt::Windows::UI::Core::PointerEventArgs^ args);
      void OnPointerReleased(::winrt::Windows::UI::Core::CoreWindow^, ::winrt::Windows::UI::Core::PointerEventArgs^ args);


      //comptr<ID2D1SolidColorBrush>                    m_blackBrush;
      //comptr<IDWriteTextFormat>                       m_textFormat;
      //comptr<IDWriteTypography>                       m_textTypography;
      //comptr<IDWriteTextLayout>                       m_textLayout;
      //SampleOverlay^                                                  m_sampleOverlay;

   };


   ref class directx_application_source :
      ::winrt::Windows::ApplicationModel::Core::IFrameworkViewSource
   {
   internal:

      
      ::aura::system *     m_psystem;

      string               m_strId;


      directx_application_source(::aura::system * paxissystem, const ::string & strId);

   public:

      virtual ::winrt::Windows::ApplicationModel::Core::IFrameworkView ^ CreateView();

   };


   CLASS_DECL_AURA directx_application_source ^ new_directx_application_source(::aura::system * psystem, const ::string & str);


} // namespace universal_windows



