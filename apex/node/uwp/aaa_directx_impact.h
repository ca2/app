#pragma once


namespace universal_windows
{


   ref class impact abstract :
      //public ::winrt::Windows::UI::Xaml::Controls::UserControl
      public ::winrt::Windows::ApplicationModel::Core::IFrameworkView,
      public ::apex::system_window
   {
   public:

      // IFrameworkView Methods
      virtual void Initialize(_In_ ::winrt::Windows::ApplicationModel::Core::CoreApplicationView^ applicationView);
      virtual void SetWindow(_In_ ::winrt::Windows::UI::Core::CoreWindow^ window) ;
      virtual void Load(_In_ String^ entryPoint) = 0;
      virtual void Run() = 0;
      virtual void Uninitialize() = 0;

      virtual ::winrt::Windows::Foundation::Rect get_window_rect() = 0;
      virtual ::winrt::Windows::Foundation::Point get_cursor_position() = 0;


      virtual ::winrt::Windows::Foundation::Rect get_input_content_rect() = 0;
      virtual ::winrt::Windows::Foundation::Rect get_input_selection_rect() = 0;

   internal:


      bool        m_bTextCompositionActive;
      widestring  m_strText;
      widestring  m_strNewText;
      ::apex::system* m_psystem;

      Agile < ::winrt::Windows::UI::Core::CoreWindow > m_window;

      // The _editContext lets us communicate with the input system.
      Agile < ::winrt::Windows::UI::Text::Core::CoreTextEditContext > _editContext;

      // We will use a plain text string to represent the
      // content of the custom text edit control.
      //String^ _text;

      // If the _selection starts and ends at the same point,
      // then it represents the location of the caret (insertion point).
      ::winrt::Windows::UI::Text::Core::CoreTextRange _selection;

      // _internalFocus keeps track of whether our control acts like it has focus.
      bool _internalFocus = false;

      // If there is a nonempty selection, then _extendingLeft is true if the user
      // is using shift+arrow to adjust the starting point of the selection,
      // or false if the user is adjusting the ending point of the selection.
      bool _extendingLeft = false;

      // The input pane object indicates the visibility of the on screen keyboard.
      // Apps can also ask the keyboard to show or hide.
      Agile < ::winrt::Windows::UI::ViewManagement::InputPane > _inputPane;

      ::winrt::Windows::Foundation::EventRegistrationToken m_tokenKeyDown;
      ::winrt::Windows::Foundation::EventRegistrationToken m_tokenPointerPressed;
      //TypedEventHandler < ::winrt::Windows::UI::Core::CoreWindow^, ::winrt::Windows::UI::Core::KeyEventArgs^> m_refPointer;


      impact();


      



      void CoreWindow_PointerPressed(::winrt::Windows::UI::Core::CoreWindow^ sender, ::winrt::Windows::UI::Core::PointerEventArgs^ args);

      void SetInternalFocus();

      void RemoveInternalFocus();

      void RemoveInternalFocusWorker();

      void EditContext_FocusRemoved(::winrt::Windows::UI::Text::Core::CoreTextEditContext^ sender, Object^ args);

      void Element_Unloaded(Object^ sender, ::winrt::Windows::UI::Xaml::RoutedEventArgs^ e);

      // Replace the text in the specified range.
      void ReplaceText(::winrt::Windows::UI::Text::Core::CoreTextRange modifiedRange, String^ text);
      void SetText(String^ text, int iBeg, int iEnd);
      bool HasSelection();

      // Change the selection without notifying CoreTextEditContext of the new selection.
      void SetSelection(::winrt::Windows::UI::Text::Core::CoreTextRange selection);
      // Change the selection and notify CoreTextEditContext of the new selection.
      void SetSelectionAndNotify(::winrt::Windows::UI::Text::Core::CoreTextRange selection);

      // Return the specified range of text. Note that the system may ask for more text
      // than exists in the text buffer.
      void EditContext_TextRequested(::winrt::Windows::UI::Text::Core::CoreTextEditContext^ sender, ::winrt::Windows::UI::Text::Core::CoreTextTextRequestedEventArgs^ args);

      // Return the current selection.
      void EditContext_SelectionRequested(::winrt::Windows::UI::Text::Core::CoreTextEditContext^ sender, ::winrt::Windows::UI::Text::Core::CoreTextSelectionRequestedEventArgs^ args);

      void EditContext_TextUpdating(::winrt::Windows::UI::Text::Core::CoreTextEditContext^ sender, ::winrt::Windows::UI::Text::Core::CoreTextTextUpdatingEventArgs^ args);

      void EditContext_SelectionUpdating(::winrt::Windows::UI::Text::Core::CoreTextEditContext^ sender, ::winrt::Windows::UI::Text::Core::CoreTextSelectionUpdatingEventArgs^ args);


      void EditContext_FormatUpdating(::winrt::Windows::UI::Text::Core::CoreTextEditContext^ sender, ::winrt::Windows::UI::Text::Core::CoreTextFormatUpdatingEventArgs^ args);

      

      void EditContext_LayoutRequested(::winrt::Windows::UI::Text::Core::CoreTextEditContext^ sender, ::winrt::Windows::UI::Text::Core::CoreTextLayoutRequestedEventArgs^ args);

      // This indicates that an IME has started composition.  If there is no handler for this event,
         // then composition will not start.
      void EditContext_CompositionStarted(::winrt::Windows::UI::Text::Core::CoreTextEditContext^ sender, ::winrt::Windows::UI::Text::Core::CoreTextCompositionStartedEventArgs^ args);
      void EditContext_CompositionCompleted(::winrt::Windows::UI::Text::Core::CoreTextEditContext^ sender, ::winrt::Windows::UI::Text::Core::CoreTextCompositionCompletedEventArgs^ args);

      void CoreWindow_KeyDown(::winrt::Windows::UI::Core::CoreWindow^ sender, ::winrt::Windows::UI::Core::KeyEventArgs^ args);
      // Adjust the active endpoint of the selection in the specified direction.
      void AdjustSelectionEndpoint(int direction);

      // Helper function to put a zero-width non-breaking space at the end of a string.
      // This prevents TextBlock from trimming trailing spaces.
      static String ^ PreserveTrailingSpaces(String^ s);

      void UpdateFocusUI();

      void UpdateTextUI();

     // static Rect GetElementRect(FrameworkElement matter);
   };


} // namespace universal_windows



