#pragma once


namespace universal_windows
{


   ref class directx_framework_impact :
      public impact
   {
   internal:


      ::windowing::window * m_pimpl;

      ::winrt::Windows::Foundation::Point                m_pointLastCursor;

      ::u32                                     m_dwMouseMoveThrottle;

      ::duration m_durationLastMouseMove;

      ::winrt::Windows::UI::ViewManagement::UISettings ^     m_puisettings;

      String ^                                  m_strId;

      //::winrt::Windows::UI::Core::CoreWindow^   m_window;

      impact^ m_impact;


      directx_base ^                            m_directx;

      bool                                      m_bFontopusShift;

      ::pointer < ::mutex >                                     m_pmutex;

      //::acme::system *                          system();

      //::acme::application *                     m_pacmeapplication;

      ::pointer<directx_interaction>           m_pdxi;

      bool                                      m_bLeftButton;

      bool                                      m_bMiddleButton;

      bool                                      m_bRightButton;

      ::winrt::Windows::Foundation::Rect                 m_rectangleLastWindowRect;
      ::winrt::Windows::Foundation::Rect                 m_rectangleInputContentRect;
      ::winrt::Windows::Foundation::Rect                 m_rectangleInputSelectionRect;


      directx_framework_impact(::acme::system * psystem,String ^ strId);


      void install_directx_application_message_routing();

      void initialize_directx_application();

      

      ::acme::system * get_context_system() const;

   public:





      // IFrameworkView Methods
      virtual void Initialize(_In_ ::winrt::Windows::ApplicationModel::Core::CoreApplicationView^ applicationView) override;
      virtual void SetWindow(_In_ ::winrt::Windows::UI::Core::CoreWindow^ window)override;
      virtual void Load(_In_ String^ entryPoint)override;
      virtual void Run()override;
      virtual void Uninitialize()override;


      virtual ::winrt::Windows::Foundation::Rect window_rectangle() override;
      virtual ::winrt::Windows::Foundation::Point get_cursor_position() override;

      virtual ::winrt::Windows::Foundation::Rect get_input_content_rect() override;
      virtual ::winrt::Windows::Foundation::Rect get_input_selection_rect() override;


      virtual ~directx_framework_impact();

   private:

      void OnUISettingsColorValuesChange(::winrt::Windows::UI::ViewManagement::UISettings^, Platform::Object^);


      // Event Handlers
      void OnWindowSizeChanged(
      _In_ ::winrt::Windows::UI::Core::CoreWindow^ sender,
      _In_ ::winrt::Windows::UI::Core::WindowSizeChangedEventArgs^ args
      );

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

      ::acme::system * system();

      string m_strId;

      directx_application_source(::acme::system * paxissystem,const ::string & strId);

   public:

      virtual ::winrt::Windows::ApplicationModel::Core::IFrameworkView ^ CreateImpact();

   };


   CLASS_DECL_ACME directx_application_source ^ new_directx_application_source(::acme::system * psystem, const ::string & str);


} // namespace universal_windows



