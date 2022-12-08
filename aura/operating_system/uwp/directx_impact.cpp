#include "framework.h"
#include "_uwp.h"
#include "aura/os/windows_common/draw2d_direct2d_global.h"


#undef ::auraacmesystem()


using namespace Platform;
using namespace Microsoft::WRL;
using namespace ::winrt::Windows::Foundation;
using namespace ::winrt::Windows::UI::Core;
using namespace ::winrt::Windows::ApplicationModel;
using namespace ::winrt::Windows::ApplicationModel::Core;
using namespace ::winrt::Windows::ApplicationModel::Activation;
using namespace ::winrt::Windows::auraacmesystem();
using namespace ::winrt::Windows::Graphics::Display;
using namespace ::winrt::Windows::auraacmesystem()::Threading;
using namespace ::winrt::Windows::UI::Text::Core;
using namespace ::winrt::Windows::UI::ViewManagement;


namespace universal_windows
{


   impact::impact()
   {

      m_bInternalFocus = false;
      m_bExtendingLeft = false;
      m_bTextCompositionActive = false;

   }


   void impact::Initialize(CoreApplicationView^ applicationView)
   {

   }


   void impact::SetWindow(CoreWindow^ window)
   {

      m_window = window;
      
      m_resizemanager = ::winrt::Windows::UI::Core::CoreWindowResizeManager::GetForCurrentImpact();

      m_resizemanager->ShouldWaitForLayoutCompletion = true;

      //auto coreTitleBar = ::winrt::Windows::ApplicationModel::Core::CoreApplication::GetCurrentImpact()->TitleBar;

      //coreTitleBar->ExtendViewIntoTitleBar = true;

      m_tokenActivated = m_window->Activated += ref memory_new TypedEventHandler < ::winrt::Windows::UI::Core::CoreWindow^, ::winrt::Windows::UI::Core::WindowActivatedEventArgs^>(this, &impact::CoreWindow_WindowActivated);

      m_tokenClosed = m_window->Closed += ref memory_new TypedEventHandler < ::winrt::Windows::UI::Core::CoreWindow ^, ::winrt::Windows::UI::Core::CoreWindowEventArgs ^>(this, &impact::CoreWindow_CoreWindowClosed);

      m_tokenKeyDown = m_window->KeyDown += ref memory_new TypedEventHandler < ::winrt::Windows::UI::Core::CoreWindow^, ::winrt::Windows::UI::Core::KeyEventArgs^>(this, &impact::CoreWindow_KeyDown);

      m_tokenPointerPressed = m_window->PointerPressed += ref memory_new TypedEventHandler < ::winrt::Windows::UI::Core::CoreWindow^, ::winrt::Windows::UI::Core::PointerEventArgs^>(this, &impact::CoreWindow_PointerPressed);

      CoreTextServicesManager ^ manager = CoreTextServicesManager::GetForCurrentImpact();

      m_editcontext = manager->CreateEditContext();

      // Get the Input Pane so we can programmatically hide and show it.
      m_inputpane = InputPane::GetForCurrentImpact();

      // For demonstration purposes, this sample sets the Input Pane display policy to Manual
      // so that it can manually show the software keyboard when the control gains focus and
      // dismiss it when the control loses focus. If you leave the policy as Automatic, then
      // the system will hide and show the Input Pane for you. Note that on Desktop, you will
      // need to implement the UIA text pattern to get expected automatic behavior.
      m_editcontext->InputPaneDisplayPolicy = CoreTextInputPaneDisplayPolicy::Automatic;

      // Set the input scope to Text because this text box is for any text.
      // This also informs software keyboards to show their regular
      // text entry layout.  There are many other input scopes and each will
      // inform a keyboard layout and text behavior.
      m_editcontext->InputScope = CoreTextInputScope::Text;

      // The system raises this event to request a specific range of text.
      m_editcontext->TextRequested += ref memory_new TypedEventHandler < CoreTextEditContext ^, CoreTextTextRequestedEventArgs^> (this, &impact::EditContext_TextRequested);

      // The system raises this event to request the current selection.
      m_editcontext->SelectionRequested += ref memory_new TypedEventHandler < CoreTextEditContext^, CoreTextSelectionRequestedEventArgs^>(this, &impact::EditContext_SelectionRequested);

      // The system raises this event when it wants the edit control to erase focus.
      m_editcontext->FocusRemoved += ref memory_new TypedEventHandler < CoreTextEditContext^, Object^>(this, &impact::EditContext_FocusRemoved);

      // The system raises this event to update text in the edit control.
      m_editcontext->TextUpdating += ref memory_new TypedEventHandler < CoreTextEditContext^, CoreTextTextUpdatingEventArgs^>(this, &impact::EditContext_TextUpdating);

      // The system raises this event to change the selection in the edit control.
      m_editcontext->SelectionUpdating += ref memory_new TypedEventHandler < CoreTextEditContext^, CoreTextSelectionUpdatingEventArgs^>(this, &impact::EditContext_SelectionUpdating);

      // The system raises this event when it wants the edit control
      // to apply formatting on a range of text.
      m_editcontext->FormatUpdating += ref memory_new TypedEventHandler < CoreTextEditContext^, CoreTextFormatUpdatingEventArgs^>(this, &impact::EditContext_FormatUpdating);

      // The system raises this event to request layout information.
      // This is used to help choose a position for the IME candidate window.
      m_editcontext->LayoutRequested += ref memory_new TypedEventHandler < CoreTextEditContext^, CoreTextLayoutRequestedEventArgs^>(this, &impact::EditContext_LayoutRequested);

      // The system raises this event to notify the edit control
      // that the string composition has started.
      m_editcontext->CompositionStarted += ref memory_new TypedEventHandler < CoreTextEditContext^, CoreTextCompositionStartedEventArgs^>(this, &impact::EditContext_CompositionStarted);

      // The system raises this event to notify the edit control
      // that the string composition is finished.
      m_editcontext->CompositionCompleted += ref memory_new TypedEventHandler < CoreTextEditContext^, CoreTextCompositionCompletedEventArgs^>(this, &impact::EditContext_CompositionCompleted);

      // The system raises this event when the NotifyFocusLeave operation has
      // completed. Our sample does not use this event.
      m_editcontext->NotifyFocusLeaveCompleted += ref memory_new TypedEventHandler < CoreTextEditContext ^, ::Platform::Object ^>(this, &impact::EditContext_NotifyFocusLeaveCompleted);

      // Set our initial UI.
      UpdateTextUI();

      UpdateFocusUI();

   }

   void impact::CoreWindow_PointerPressed(::winrt::Windows::UI::Core::CoreWindow^ sender, ::winrt::Windows::UI::Core::PointerEventArgs ^args)
   {
      // See whether the pointer is inside or outside the control.
      //Rect contentRect = GetElementRect(BorderPanel);
      //if (contentRect.Contains(args.CurrentPoint.Position))
      //{
      //   // The user tapped inside the control. Give it focus.
      //   SetInternalFocus();

      //   // Tell XAML that this matter has focus, so we don't have two
      //   // focus elements. That is the extent of our integration with XAML focus.
      //   Focus(FocusState.Programmatic);

      //   // A more complete custom control would move the caret to the
      //   // pointer position. It would also provide some way to select
      //   // text via touch. We do neither in this sample.

      //}
      //else
      //{
      //   // The user tapped outside the control. Remove focus.
      //   RemoveInternalFocus();
      //}
   }

   
   void impact::SetInternalFocus()
   {

      if (!m_bInternalFocus)
      {

         // Update internal notion of focus.
         m_bInternalFocus = true;

         // Update the UI.
         //UpdateTextUI();
         //UpdateFocusUI();

         // Notify the CoreTextEditContext that the edit context has focus,
         // so it should start processing text input.
         m_editcontext->NotifyFocusEnter();

      }

      // Ask the software keyboard to show.  The system will ultimately decide if it will show.
      // For example, it will not show if there is a keyboard attached.
      m_inputpane->TryShow();

   }


   void impact::RemoveInternalFocus()
   {
      
      if (m_bInternalFocus)
      {
         
         //Notify the system that this edit context is no longer in focus
         m_editcontext->NotifyFocusLeave();

         RemoveInternalFocusWorker();

      }

   }


   void impact::RemoveInternalFocusWorker()
   {

      //Update the internal notion of focus
      m_bInternalFocus = false;

      // Ask the software keyboard to dismiss.
      m_inputpane->TryHide();

      // Update our UI.
      UpdateTextUI();

      UpdateFocusUI();

   }


   void impact::EditContext_FocusRemoved(CoreTextEditContext ^sender, Object ^ args)
   {
   
      RemoveInternalFocusWorker();

   }


   void impact::Element_Unloaded(Object ^ sender, ::winrt::Windows::UI::Xaml::RoutedEventArgs ^ e)
   {

      m_window->KeyDown -= m_tokenKeyDown;

      m_window->PointerPressed -= m_tokenPointerPressed;

   }


   void impact::SetText(String^ text, int iBeg, int iEnd)
   {

      //auto 

//      m_strText = text;

      set_input_text(text);
      
      synchronization([this, iBeg, iEnd, text]()
      {
            
         CoreTextRange sel;

         sel.StartCaretPosition = iBeg;

         sel.EndCaretPosition = iEnd < 0 ? text->Length() + iEnd + 1 : iEnd;

         widestring wstrText = get_input_text();

         m_editcontext->NotifyTextChanged(m_selection, wstrText.length(), sel);

      });

   }


   // Replace the text in the specified range.
   void impact::ReplaceText(CoreTextRange  modifiedRange, String ^ text)
   {

      wstring wstrText = get_input_text();

      // Modify the internal text store.
      wstrText = wstrText.Left(modifiedRange.StartCaretPosition) +
         text->Begin() +
         wstrText.Mid(modifiedRange.EndCaretPosition);

      // Move the caret to the end of the replacement text.
      m_selection.StartCaretPosition = modifiedRange.StartCaretPosition + wstrText.length();
      m_selection.EndCaretPosition = m_selection.StartCaretPosition;

      // Update the selection of the edit context.  There is no need to notify the system
      // of the selection change because we are going to call NotifyTextChanged soon.
      SetSelection(m_selection);

      // Let the CoreTextEditContext know what changed.
      m_editcontext->NotifyTextChanged(modifiedRange, wstrText.length(), m_selection);

   }


   bool impact::HasSelection()
   {

      return m_selection.StartCaretPosition != m_selection.EndCaretPosition;

   }


   // Change the selection without notifying CoreTextEditContext of the memory_new selection.
   void impact::SetSelection(CoreTextRange selection)
   {
      
      // Modify the internal selection.
      m_selection = selection;

      //Update the UI to show the memory_new selection.
      UpdateTextUI();

   }


   // Change the selection and notify CoreTextEditContext of the memory_new selection.
   void impact::SetSelectionAndNotify(CoreTextRange selection)
   {

      SetSelection(selection);

      m_editcontext->NotifySelectionChanged(m_selection);

   }


   // Return the specified range of text. Note that the system may ask for more text
   // than exists in the text buffer.
   void impact::EditContext_TextRequested(CoreTextEditContext ^ sender, CoreTextTextRequestedEventArgs ^args)
   {
      
      CoreTextTextRequest ^ request = args->Request;

      widestring wstrText = get_input_text();

      wstrText = wstrText.Mid(
         request->Range.StartCaretPosition,
         minimum(request->Range.EndCaretPosition, wstrText.length()) - request->Range.StartCaretPosition);

      request->Text = wstrText;

   }


   // Return the current selection.
   void impact::EditContext_SelectionRequested(CoreTextEditContext ^sender, CoreTextSelectionRequestedEventArgs ^args)
   {
      
      CoreTextSelectionRequest^ request = args->Request;

      request->Selection = m_selection;

   }


   void impact::EditContext_TextUpdating(CoreTextEditContext ^sender, CoreTextTextUpdatingEventArgs ^ args)
   {
   
      CoreTextRange range = args->Range;

      ::output_debug_string("range" + as_string(range.StartCaretPosition) + "," + as_string(range.EndCaretPosition) +"\n");

      widestring newText = args->Text;

      CoreTextRange newSelection = args->NewSelection;

      auto pwsz = newText.c_str();

      widestring wstrText = get_input_text();

      string strText = wstrText.Left( range.StartCaretPosition) + newText + wstrText.Mid(range.EndCaretPosition);

      m_strNewText = newText;

      // Modify the internal text store.
      //m_strText = strText;

      // You can set the proper font or direction for the updated text based on the language by checking
      // args.InputLanguage.  We will not do that in this sample.

      // Modify the current selection.
      newSelection.EndCaretPosition = newSelection.StartCaretPosition;

      // Update the selection of the edit context. There is no need to notify the system
      // because the system itself changed the selection.
      SetSelection(newSelection);

      if(m_strNewText.has_char())
      {

         auto pfocusui = host()->get_keyboard_focus();

         if (pfocusui)
         {

            pfocusui->insert_text(m_strNewText, false, e_source_sync);

         }
         else
         {

            ::pointer<::user::message>spbase;

            auto pkey = __new(::message::key);

            spbase = pkey;

            auto psession = get_session();

            bool bTextFocus = host()->get_user_interaction() != nullptr;

            bool bSpecialKey = false;

            pkey->m_atom = e_message_key_down;
            pkey->m_playeredUserPrimitive = psession->get_user_interaction_host();
            pkey->m_nChar = 0;
            pkey->m_ekey = ::user::e_key_refer_to_text_member;
            pkey->m_wparam = pkey->m_nChar;
            pkey->m_nFlags = 0;
            pkey->m_lparam = pkey->m_nFlags << 16;
            pkey->m_strText = m_strNewText;

            auto puserinteractionHost = __user_interaction(acmesystem()->get_session()->m_puserinteractionHost);

            puserinteractionHost->m_pimpl->queue_message_handler(spbase);

         }

      }

   }


   void impact::EditContext_SelectionUpdating(CoreTextEditContext ^sender, CoreTextSelectionUpdatingEventArgs ^ args)
   {

      // Set the memory_new selection to the value specified by the system.
      CoreTextRange range = args->Selection;

      // Update the selection of the edit context. There is no need to notify the system
      // because the system itself changed the selection.
      SetSelection(range);

   }

   
   void impact::EditContext_FormatUpdating(CoreTextEditContext ^sender, CoreTextFormatUpdatingEventArgs ^ args)
   {

      // The following code specifies how you would apply any formatting to the specified range of text
      // For this sample, we do not make any changes to the format.

      // Apply text color if specified.
      // A null value indicates that the default should be used.
      if (args->TextColor != nullptr)
      {

         //InternalSetTextColor(args.Range, args.TextColor.Value);

      }
      else
      {

         //InternalSetDefaultTextColor(args.Range);

      }

      // Apply background color if specified.
      // A null value indicates that the default should be used.
      if (args->BackgroundColor != nullptr)
      {

         //InternalSetBackgroundColor(args.Range, args.BackgroundColor.Value);

      }
      else
      {

         //InternalSetDefaultBackgroundColor(args.Range);

      }

      // Apply underline if specified.
      // A null value indicates that the default should be used.
      if (args->UnderlineType != nullptr)
      {

         //TextDecoration underline = memory_new TextDecoration(args.Range,args.UnderlineType.Value,args.UnderlineColor.Value);

         //InternalAddTextDecoration(underline);

      }
      else
      {

         //InternalRemoveTextDecoration(args.Range);

      }

   }


   void impact::EditContext_LayoutRequested(CoreTextEditContext ^sender, CoreTextLayoutRequestedEventArgs ^args)
   {
      
      CoreTextLayoutRequest ^ request = args->Request;

      // Get the screen coordinates of the entire control and the selected text.
      // This information is used to position the IME candidate window.

      // First, get the coordinates of the edit control and the selection
      // relative to the Window.

      Rect contentRect = get_input_content_rect();

      Rect selectionRect = get_input_selection_rect();

      // Next, convert to screen coordinates in impact pixels.
      Rect windowBounds = m_window->Bounds;
      contentRect.X += windowBounds.X;
      contentRect.Y += windowBounds.Y;
      selectionRect.X += windowBounds.X;
      selectionRect.Y += windowBounds.Y;

      // Finally, scale up to raw pixels.
      double scaleFactor = DisplayInformation::GetForCurrentImpact()->RawPixelsPerViewPixel;

      contentRect = ScaleRect(contentRect, scaleFactor);
      selectionRect = ScaleRect(selectionRect, scaleFactor);

      // This is the bounds of the selection.
      // Note: If you return bounds with 0 width and 0 height, candidates will not appear while typing.
      request->LayoutBounds->TextBounds = selectionRect;

      //This is the bounds of the whole control
      request->LayoutBounds->ControlBounds = contentRect;

   }

   
   // This indicates that an IME has started composition.  If there is no handler for this event,
   // then composition will not start.
   void impact::EditContext_CompositionStarted(CoreTextEditContext ^ sender, CoreTextCompositionStartedEventArgs ^ args)
   {

      m_bTextCompositionActive = true;

   }


   void impact::EditContext_CompositionCompleted(CoreTextEditContext ^sender, CoreTextCompositionCompletedEventArgs ^ args)
   {

      m_bTextCompositionActive = false;

      auto pfocusui = m_puserinteraction->get_keyboard_focus();

      //m_strText.Empty();

      //m_strNewText.Empty();

      if (pfocusui)
      {

         pfocusui->on_text_composition_done();

      }

   }


   void impact::EditContext_NotifyFocusLeaveCompleted(::winrt::Windows::UI::Text::Core::CoreTextEditContext ^ sender, ::Platform::Object ^ args)
   {


   }


   void impact::CoreWindow_WindowActivated(::winrt::Windows::UI::Core::CoreWindow^ sender, ::winrt::Windows::UI::Core::WindowActivatedEventArgs^ args)
   {

      if (args->WindowActivationState == ::winrt::Windows::UI::Core::CoreWindowActivationState::Deactivated)
      {

         ::output_debug_string("Deactivated");

         //auto puserinteractionHost = Sess(acmesystem()).host();

         //puserinteractionHost->set_need_layout();

         //puserinteractionHost->set_need_redraw();

         //puserinteractionHost->post_redraw();

      }

   }


   void impact::CoreWindow_CoreWindowClosed(::winrt::Windows::UI::Core::CoreWindow ^ sender, ::winrt::Windows::UI::Core::CoreWindowEventArgs ^ args)
   {

      ::output_debug_string("window closed");

   }


   void impact::CoreWindow_KeyDown(::winrt::Windows::UI::Core::CoreWindow^ sender, KeyEventArgs ^args)
   {

      // Do not process keyboard input if the custom edit control does not
      // have focus.
      if (!m_bInternalFocus)
      {

         return;

      }

      // This holds the range we intend to operate on, or which we intend
      // to become the memory_new selection. Start with the current selection.
      CoreTextRange  range = m_selection;

      // For the purpose of this sample, we will support only the left and right
      // arrow keys and the backspace key. A more complete text edit control
      // would also handle keys like Home, End, and Delete, as well as
      // hotkeys like Ctrl+V to paste.
      //
      // Note that this sample does not properly handle surrogate pairs
      // nor does it handle grapheme clusters.

      switch (args->VirtualKey)
      {
         // Backspace
      case VirtualKey::Back:
         // If there is a selection, then delete the selection.
         //if (HasSelection())
         //{
         //   // Set the text in the selection to nothing.
         //   ReplaceText(range, "");
         //}
         //else
         //{
         //   // Delete the character to the left of the caret, if one exists,
         //   // by creating a range that encloses the character to the left
         //   // of the caret, and setting the contents of that range to nothing.
         //   range.StartCaretPosition = maximum(0, range.StartCaretPosition - 1);
         //   ReplaceText(range, "");
         //}
         //m_strNewText.Empty();
         break;

         // Left arrow
      case VirtualKey::Left:
         // If the shift key is down, then adjust the size_i32 of the selection.
         //if ((int)m_window->GetKeyState(VirtualKey::Shift) & (int) CoreVirtualKeyStates::Down)
         //{
         //   // If this is the start of a selection, then remember which edge we are adjusting.
         //   if (!HasSelection())
         //   {
         //      _extendingLeft = true;
         //   }

         //   // Adjust the selection and notify CoreTextEditContext.
         //   AdjustSelectionEndpoint(-1);
         //}
         //else
         //{
         //   // The shift key is not down. If there was a selection, then snap the
         //   // caret at the left edge of the selection.
         //   if (HasSelection())
         //   {
         //      range.EndCaretPosition = range.StartCaretPosition;
         //      SetSelectionAndNotify(range);
         //   }
         //   else
         //   {
         //      // There was no selection. Move the caret left one code unit if possible.
         //      range.StartCaretPosition = maximum(0, range.StartCaretPosition - 1);
         //      range.EndCaretPosition = range.StartCaretPosition;
         //      SetSelectionAndNotify(range);
         //   }
         //}
         //m_strNewText.Empty();
         break;

         // Right arrow
      case VirtualKey::Right:
         // If the shift key is down, then adjust the size_i32 of the selection.
         //if ((int)m_window->GetKeyState(VirtualKey::Shift) & (int) CoreVirtualKeyStates::Down)
         //{
         //   // If this is the start of a selection, then remember which edge we are adjusting.
         //   if (!HasSelection())
         //   {
         //      _extendingLeft = false;
         //   }

         //   // Adjust the selection and notify CoreTextEditContext.
         //   AdjustSelectionEndpoint(+1);
         //}
         //else
         //{
         //   // The shift key is not down. If there was a selection, then snap the
         //   // caret at the right edge of the selection.
         //   if (HasSelection())
         //   {
         //      range.StartCaretPosition = range.EndCaretPosition;
         //      SetSelectionAndNotify(range);
         //   }
         //   else
         //   {
         //      // There was no selection. Move the caret right one code unit if possible.
         //      range.StartCaretPosition = minimum(m_strText.length(), range.StartCaretPosition + 1);
         //      range.EndCaretPosition = range.StartCaretPosition;
         //      SetSelectionAndNotify(range);
         //   }
         //}
         //m_strNewText.Empty();
         break;
      }
   }

   // Adjust the active endpoint of the selection in the specified direction.
   void impact::AdjustSelectionEndpoint(int direction)
   {

      CoreTextRange range = m_selection;

      if (m_bExtendingLeft)
      {

         range.StartCaretPosition = maximum(0, range.StartCaretPosition + direction);      

      }
      else
      {

         widestring wstrText = get_input_text();

         range.EndCaretPosition = minimum(wstrText.length(), range.EndCaretPosition + direction);

      }

      SetSelectionAndNotify(range);

   }


   // Helper function to put a zero-width non-breaking space at the end of a string.
   // This prevents TextBlock from trimming trailing spaces.
   String ^ impact::PreserveTrailingSpaces(String ^ s)
   {

      return s + L"\ufeff";

   }


   void impact::UpdateFocusUI()
   {

      //BorderPanel->BorderBrush = _internalFocus ? memory_new ::winrt::Windows::UI::Xaml::Media::SolidColorBrush(::winrt::Windows::UI::Colors::Green) : null;

   }


   void impact::UpdateTextUI()
   {

      // The raw materials we have are a string (_text) and information about
      // where the caret/selection is (_selection). We can render the control
      // any way we like.

      //BeforeSelectionText->Text = PreserveTrailingSpaces(_text->Substring(0, _selection->StartCaretPosition));
      //if (HasSelection())
      //{
      //   // There is a selection. Draw that.
      //   CaretText.Visibility = Visibility.Collapsed;
      //   SelectionText.Text = PreserveTrailingSpaces(
      //      _text->Substring(_selection->StartCaretPosition, _selection->EndCaretPosition - _selection->StartCaretPosition));
      //}
      //else
      //{
      //   // There is no selection. Remove it.
      //   SelectionText.Text = "";

      //   // Draw the caret if we have focus.
      //   CaretText.Visibility = _internalFocus ? Visibility.Visible : Visibility.Collapsed;
      //}

      //AfterSelectionText.Text = PreserveTrailingSpaces(_text->Substring(_selection->EndCaretPosition));

      //// Update statistics for demonstration purposes.
      //FullText.Text = _text;
      //SelectionStartIndexText.Text = _selection->StartCaretPosition.ToString();
      //SelectionEndIndexText.Text = _selection->EndCaretPosition.ToString();
   }


   //Rect impact::GetElementRect(FrameworkElement matter)
   //{
   //   GeneralTransform transform = matter.TransformToVisual(null);
   //   Point point = transform.TransformPoint(memory_new Point());
   //   return memory_new Rect(point, memory_new Size(matter.ActualWidth, matter.ActualHeight));
   //}


} // namespace universal_windows



