#pragma once


namespace uwp
{


   ref class directx_application :
      public impact
   {
   internal:


      ::user::interaction_impl * m_pimpl;

      Windows::Foundation::Point                m_pointLastCursor;

      DWORD                                     m_dwMouseMoveThrottle;

      tick m_tickLastMouseMove;

      ::Windows::UI::ViewManagement::UISettings ^     m_puisettings;

      String ^                                  m_strId;

      //Windows::UI::Core::CoreWindow^   m_window;

      impact^ m_impact;


      directx_base ^                            m_directx;

      bool                                      m_bFontopusShift;

      ::mutex                                     m_mutex;

      //::aura::system *                          m_psystem;

      //::aura::application *                     m_papp;

      __pointer(directx_interaction)            m_pdxinteraction;

      bool                                      m_bLeftButton;

      bool                                      m_bMiddleButton;

      bool                                      m_bRightButton;

      Windows::Foundation::Rect                 m_rectLastWindowRect;
      Windows::Foundation::Rect                 m_rectInputContentRect;
      Windows::Foundation::Rect                 m_rectInputSelectionRect;


      directx_application();


      virtual ::estatus initialize_directx_application(::aura::system* psystem, String^ strId);


      void install_directx_application_message_routing();

      void initialize_directx_application();

      

      ::aura::system * get_context_system() const;

   public:





      // IFrameworkView Methods
      virtual void Initialize(_In_ Windows::ApplicationModel::Core::CoreApplicationView^ applicationView) override;
      virtual void SetWindow(_In_ Windows::UI::Core::CoreWindow^ window)override;
      virtual void Load(_In_ String^ entryPoint)override;
      virtual void Run()override;
      virtual void Uninitialize()override;


      virtual Windows::Foundation::Rect get_window_rect() override;
      virtual Windows::Foundation::Point get_cursor_pos() override;

      virtual Windows::Foundation::Rect get_input_content_rect() override;
      virtual Windows::Foundation::Rect get_input_selection_rect() override;


      virtual ~directx_application();
   internal:
      void on_size(const ::size & size);


   private:

      void OnUISettingsColorValuesChange(Windows::UI::ViewManagement::UISettings^, Platform::Object^);


      // Event Handlers
      void OnWindowSizeChanged(
      _In_ Windows::UI::Core::CoreWindow^ sender,
      _In_ Windows::UI::Core::WindowSizeChangedEventArgs^ args
      );

      void DpiChanged(::Windows::Graphics::Display::DisplayInformation ^ sender, Object ^ obj);

      void DisplayContentsInvalidated(::Windows::Graphics::Display::DisplayInformation ^ sender, Object ^ obj);

      void OnActivated(
      _In_ Windows::ApplicationModel::Core::CoreApplicationView^ applicationView,
      _In_ Windows::ApplicationModel::Activation::IActivatedEventArgs^ args
      );

      void OnSuspending(
      _In_ Object^ sender,
      _In_ Windows::ApplicationModel::SuspendingEventArgs^ args
      );

      void OnResuming(
      _In_ Object^ sender,
      _In_ Object^ args
      );

      
      void OnWindowVisibilityChanged(Windows::UI::Core::CoreWindow^, Windows::UI::Core::VisibilityChangedEventArgs^ args);

      void OnPointerMoved(Windows::UI::Core::CoreWindow^, Windows::UI::Core::PointerEventArgs^ args);

      void OnCharacterReceived(Windows::UI::Core::CoreWindow^, Windows::UI::Core::CharacterReceivedEventArgs^ args);
      void OnKeyDown(Windows::UI::Core::CoreWindow^, Windows::UI::Core::KeyEventArgs^ args);
      void OnKeyUp(Windows::UI::Core::CoreWindow^, Windows::UI::Core::KeyEventArgs^ args);
      void OnPointerPressed(Windows::UI::Core::CoreWindow^, Windows::UI::Core::PointerEventArgs^ args);
      void OnPointerReleased(Windows::UI::Core::CoreWindow^, Windows::UI::Core::PointerEventArgs^ args);


      //Microsoft::WRL::ComPtr<ID2D1SolidColorBrush>                    m_blackBrush;
      //Microsoft::WRL::ComPtr<IDWriteTextFormat>                       m_textFormat;
      //Microsoft::WRL::ComPtr<IDWriteTypography>                       m_textTypography;
      //Microsoft::WRL::ComPtr<IDWriteTextLayout>                       m_textLayout;
      //SampleOverlay^                                                  m_sampleOverlay;

   };


   ref class directx_application_source :
      Windows::ApplicationModel::Core::IFrameworkViewSource
   {
   internal:

      ::aura::system * m_psystem;

      string m_strId;

      directx_application_source(::aura::system * paxissystem,const string & strId);

   public:

      virtual Windows::ApplicationModel::Core::IFrameworkView ^ CreateView();

   };


   CLASS_DECL_AURA directx_application_source ^ new_directx_application_source(::aura::system * psystem, const string & str);


} // namespace uwp



