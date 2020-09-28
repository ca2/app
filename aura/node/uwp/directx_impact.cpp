#include "framework.h"
#include "_uwp.h"


#undef System


using namespace Platform;
using namespace Microsoft::WRL;
using namespace Windows::Foundation;
using namespace Windows::UI::Core;
using namespace Windows::ApplicationModel;
using namespace Windows::ApplicationModel::Core;
using namespace Windows::ApplicationModel::Activation;
using namespace Windows::System;
using namespace Windows::Graphics::Display;
using namespace Windows::System::Threading;
using namespace Windows::UI::Text::Core;
using namespace Windows::UI::ViewManagement;



namespace uwp
{


   impact::impact()
   {

      m_bTextCompositionActive = false;

   }


   void impact::Initialize(CoreApplicationView^ applicationView)
   {


   }


   void impact::SetWindow(CoreWindow^ window)
   {

      //InitializeComponent();

      // The CoreTextEditContext processes text input, but other keys are
      // the apps's responsibility.
      m_window = window;

      m_tokenKeyDown = m_window->KeyDown += ref new TypedEventHandler < ::Windows::UI::Core::CoreWindow^, ::Windows::UI::Core::KeyEventArgs^>(this, &impact::CoreWindow_KeyDown);

      m_tokenPointerPressed = m_window->PointerPressed += ref new TypedEventHandler < ::Windows::UI::Core::CoreWindow^, ::Windows::UI::Core::PointerEventArgs^>(this, &impact::CoreWindow_PointerPressed);

      // Create a CoreTextEditContext for our custom edit control.
      CoreTextServicesManager^ manager = CoreTextServicesManager::GetForCurrentView();

      _editContext = manager->CreateEditContext();

      // Get the Input Pane so we can programmatically hide and show it.
      _inputPane = InputPane::GetForCurrentView();

      // For demonstration purposes, this sample sets the Input Pane display policy to Manual
      // so that it can manually show the software keyboard when the control gains focus and
      // dismiss it when the control loses focus. If you leave the policy as Automatic, then
      // the system will hide and show the Input Pane for you. Note that on Desktop, you will
      // need to implement the UIA text pattern to get expected automatic behavior.
      _editContext->InputPaneDisplayPolicy = CoreTextInputPaneDisplayPolicy::Automatic;

      // Set the input scope to Text because this text box is for any text.
      // This also informs software keyboards to show their regular
      // text entry layout.  There are many other input scopes and each will
      // inform a keyboard layout and text behavior.
      _editContext->InputScope = CoreTextInputScope::Text;

      // The system raises this event to request a specific range of text.
      _editContext->TextRequested += ref new TypedEventHandler < CoreTextEditContext ^, CoreTextTextRequestedEventArgs^> (this, &impact::EditContext_TextRequested);

      // The system raises this event to request the current selection.
      _editContext->SelectionRequested += ref new TypedEventHandler < CoreTextEditContext^, CoreTextSelectionRequestedEventArgs^>(this, &impact::EditContext_SelectionRequested);

      // The system raises this event when it wants the edit control to remove focus.
      _editContext->FocusRemoved += ref new TypedEventHandler < CoreTextEditContext^, Object^>(this, &impact::EditContext_FocusRemoved);

      // The system raises this event to update text in the edit control.
      _editContext->TextUpdating += ref new TypedEventHandler < CoreTextEditContext^, CoreTextTextUpdatingEventArgs^>(this, &impact::EditContext_TextUpdating);

      // The system raises this event to change the selection in the edit control.
      _editContext->SelectionUpdating += ref new TypedEventHandler < CoreTextEditContext^, CoreTextSelectionUpdatingEventArgs^>(this, &impact::EditContext_SelectionUpdating);

      // The system raises this event when it wants the edit control
      // to apply formatting on a range of text.
      _editContext->FormatUpdating += ref new TypedEventHandler < CoreTextEditContext^, CoreTextFormatUpdatingEventArgs^>(this, &impact::EditContext_FormatUpdating);

      // The system raises this event to request layout information.
      // This is used to help choose a position for the IME candidate window.
      _editContext->LayoutRequested += ref new TypedEventHandler < CoreTextEditContext^, CoreTextLayoutRequestedEventArgs^>(this, &impact::EditContext_LayoutRequested);

      // The system raises this event to notify the edit control
      // that the string composition has started.
      _editContext->CompositionStarted += ref new TypedEventHandler < CoreTextEditContext^, CoreTextCompositionStartedEventArgs^>(this, &impact::EditContext_CompositionStarted);

      // The system raises this event to notify the edit control
      // that the string composition is finished.
      _editContext->CompositionCompleted += ref new TypedEventHandler < CoreTextEditContext^, CoreTextCompositionCompletedEventArgs^>(this, &impact::EditContext_CompositionCompleted);

      // The system raises this event when the NotifyFocusLeave operation has
      // completed. Our sample does not use this event.
      // _editContext->NotifyFocusLeaveCompleted += EditContext_NotifyFocusLeaveCompleted;

      // Set our initial UI.
      UpdateTextUI();
      UpdateFocusUI();
   }

   void impact::CoreWindow_PointerPressed(::Windows::UI::Core::CoreWindow^ sender, ::Windows::UI::Core::PointerEventArgs ^args)
   {
      // See whether the pointer is inside or outside the control.
      //Rect contentRect = GetElementRect(BorderPanel);
      //if (contentRect.Contains(args.CurrentPoint.Position))
      //{
      //   // The user tapped inside the control. Give it focus.
      //   SetInternalFocus();

      //   // Tell XAML that this element has focus, so we don't have two
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
      if (!_internalFocus)
      {
         // Update internal notion of focus.
         _internalFocus = true;

         // Update the UI.
         //UpdateTextUI();
         //UpdateFocusUI();

         // Notify the CoreTextEditContext that the edit context has focus,
         // so it should start processing text input.
         _editContext->NotifyFocusEnter();
      }

      // Ask the software keyboard to show.  The system will ultimately decide if it will show.
      // For example, it will not show if there is a keyboard attached.
      _inputPane->TryShow();

   }

   void impact::RemoveInternalFocus()
   {
      if (_internalFocus)
      {
         //Notify the system that this edit context is no longer in focus
         _editContext->NotifyFocusLeave();

         RemoveInternalFocusWorker();
      }
   }

   void impact::RemoveInternalFocusWorker()
   {
      //Update the internal notion of focus
      _internalFocus = false;

      // Ask the software keyboard to dismiss.
      _inputPane->TryHide();

      // Update our UI.
      UpdateTextUI();
      UpdateFocusUI();
   }

   void impact::EditContext_FocusRemoved(CoreTextEditContext ^sender, Object ^ args)
   {
      RemoveInternalFocusWorker();
   }


   void impact::Element_Unloaded(Object ^ sender, ::Windows::UI::Xaml::RoutedEventArgs ^ e)
   {
      m_window->KeyDown -= m_tokenKeyDown;
      m_window->PointerPressed -= m_tokenPointerPressed;
   }

   void impact::SetText(String^ text, int iBeg, int iEnd)
   {

      m_strText = text;
      
      main_async([this, iBeg, iEnd, text]()
         {
            
            CoreTextRange sel;

            sel.StartCaretPosition = iBeg;

            sel.EndCaretPosition = iEnd < 0 ? text->Length() + iEnd + 1 : iEnd;

            _editContext->NotifyTextChanged(_selection, m_strText.length(), sel);

         });

   }

   // Replace the text in the specified range.
   void impact::ReplaceText(CoreTextRange  modifiedRange, String ^ text)
   {
      // Modify the internal text store.
      m_strText = m_strText.Left(modifiedRange.StartCaretPosition) +
         text->Begin() +
         m_strText.Mid(modifiedRange.EndCaretPosition);

      // Move the caret to the end of the replacement text.
      _selection.StartCaretPosition = modifiedRange.StartCaretPosition + m_strText.length();
      _selection.EndCaretPosition = _selection.StartCaretPosition;

      // Update the selection of the edit context.  There is no need to notify the system
      // of the selection change because we are going to call NotifyTextChanged soon.
      SetSelection(_selection);

      // Let the CoreTextEditContext know what changed.
      _editContext->NotifyTextChanged(modifiedRange, m_strText.length(), _selection);
   }


   bool impact::HasSelection()
   {

      return _selection.StartCaretPosition != _selection.EndCaretPosition;

   }


   // Change the selection without notifying CoreTextEditContext of the new selection.
   void impact::SetSelection(CoreTextRange selection)
   {
      // Modify the internal selection.
      _selection = selection;

      //Update the UI to show the new selection.
      UpdateTextUI();
   }


   // Change the selection and notify CoreTextEditContext of the new selection.
   void impact::SetSelectionAndNotify(CoreTextRange selection)
   {

      SetSelection(selection);

      _editContext->NotifySelectionChanged(_selection);

   }


   // Return the specified range of text. Note that the system may ask for more text
   // than exists in the text buffer.
   void impact::EditContext_TextRequested(CoreTextEditContext ^ sender, CoreTextTextRequestedEventArgs ^args)
   {
      CoreTextTextRequest ^ request = args->Request;
      request->Text = m_strText.Mid(
         request->Range.StartCaretPosition,
         min(request->Range.EndCaretPosition, m_strText.length()) - request->Range.StartCaretPosition);
   }

   // Return the current selection.
   void impact::EditContext_SelectionRequested(CoreTextEditContext ^sender, CoreTextSelectionRequestedEventArgs ^args)
   {
      CoreTextSelectionRequest^ request = args->Request;
      request->Selection = _selection;
   }

   void impact::EditContext_TextUpdating(CoreTextEditContext ^sender, CoreTextTextUpdatingEventArgs ^ args)
   {
      CoreTextRange range = args->Range;
      widestring newText = args->Text;
      CoreTextRange newSelection = args->NewSelection;
      auto pwsz= newText.c_str();
      m_strNewText = newText;
      // Modify the internal text store.
      m_strText = m_strText.Left( range.StartCaretPosition) +
         newText +
         m_strText.Mid(min(m_strText.length(), range.EndCaretPosition));

      // You can set the proper font or direction for the updated text based on the language by checking
      // args.InputLanguage.  We will not do that in this sample.

      // Modify the current selection.
      newSelection.EndCaretPosition = newSelection.StartCaretPosition;

      // Update the selection of the edit context. There is no need to notify the system
      // because the system itself changed the selection.
      SetSelection(newSelection);

      if(m_strNewText.has_char())
      {

         auto pfocusui = Session.get_focus_ui();


         if (pfocusui)
         {

            pfocusui->on_text_composition(m_strText);

         }
         else
         {



            pointer < ::message::base > spbase;

            auto pkey = __new(::message::key);

            spbase = pkey;

            bool bTextFocus = Session.get_focus_ui() != nullptr;

            bool bSpecialKey = false;

            pkey->m_id = WM_KEYDOWN;
            pkey->m_puserinteraction = Session.m_puiHost;
            pkey->m_nChar = 0;
            pkey->m_ekey = ::user::key_refer_to_text_member;
            pkey->m_wparam = pkey->m_nChar;
            pkey->m_nFlags = 0;
            pkey->m_lparam = pkey->m_nFlags << 16;
            pkey->m_strText = m_strNewText;
            //      pkey->m_key = args;

            auto puiHost = __user_interaction(m_psystem->get_context_session()->m_puiHost);

            puiHost->m_pimpl->queue_message_handler(spbase);

         }

      }

   }


   void impact::EditContext_SelectionUpdating(CoreTextEditContext ^sender, CoreTextSelectionUpdatingEventArgs ^ args)
   {
      // Set the new selection to the value specified by the system.
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
         //TextDecoration underline = new TextDecoration(args.Range,args.UnderlineType.Value,args.UnderlineColor.Value);

         //InternalAddTextDecoration(underline);
      }
      else
      {
         //InternalRemoveTextDecoration(args.Range);
      }
   }

   //Rect impact::ScaleRect(Rect rect, double scale)
   //{
   //   rect.X *= scale;
   //   rect.Y *= scale;
   //   rect.Width *= scale;
   //   rect.Height *= scale;
   //   return rect;
   //}


   void impact::EditContext_LayoutRequested(CoreTextEditContext ^sender, CoreTextLayoutRequestedEventArgs ^args)
   {
      
      CoreTextLayoutRequest ^ request = args->Request;

      // Get the screen coordinates of the entire control and the selected text.
      // This information is used to position the IME candidate window.

      // First, get the coordinates of the edit control and the selection
      // relative to the Window.

      Rect contentRect = get_input_content_rect();

      Rect selectionRect = get_input_selection_rect();


      // Next, convert to screen coordinates in view pixels.
      Rect windowBounds = m_window->Bounds;
      contentRect.X += windowBounds.X;
      contentRect.Y += windowBounds.Y;
      selectionRect.X += windowBounds.X;
      selectionRect.Y += windowBounds.Y;

      // Finally, scale up to raw pixels.
      double scaleFactor = DisplayInformation::GetForCurrentView()->RawPixelsPerViewPixel;

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
      auto pfocusui = Session.get_focus_ui();

      if (pfocusui)
      {

         pfocusui->on_text_composition_done();

      }

   }


   void impact::CoreWindow_KeyDown(::Windows::UI::Core::CoreWindow^ sender, KeyEventArgs ^args)
   {
      // Do not process keyboard input if the custom edit control does not
      // have focus.
      if (!_internalFocus)
      {
         return;
      }

      // This holds the range we intend to operate on, or which we intend
      // to become the new selection. Start with the current selection.
      CoreTextRange  range = _selection;

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
         //   range.StartCaretPosition = max(0, range.StartCaretPosition - 1);
         //   ReplaceText(range, "");
         //}
         //m_strNewText.Empty();
         break;

         // Left arrow
      case VirtualKey::Left:
         // If the shift key is down, then adjust the size of the selection.
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
         //      range.StartCaretPosition = max(0, range.StartCaretPosition - 1);
         //      range.EndCaretPosition = range.StartCaretPosition;
         //      SetSelectionAndNotify(range);
         //   }
         //}
         //m_strNewText.Empty();
         break;

         // Right arrow
      case VirtualKey::Right:
         // If the shift key is down, then adjust the size of the selection.
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
         //      range.StartCaretPosition = min(m_strText.length(), range.StartCaretPosition + 1);
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
      CoreTextRange range = _selection;
      if (_extendingLeft)
      {
         range.StartCaretPosition = max(0, range.StartCaretPosition + direction);      
      }
      else
      {
         range.EndCaretPosition = min(m_strText.length(), range.EndCaretPosition + direction);
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
      //BorderPanel->BorderBrush = _internalFocus ? new ::Windows::UI::Xaml::Media::SolidColorBrush(::Windows::UI::Colors::Green) : null;
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

   //Rect impact::GetElementRect(FrameworkElement element)
   //{
   //   GeneralTransform transform = element.TransformToVisual(null);
   //   Point point = transform.TransformPoint(new Point());
   //   return new Rect(point, new Size(element.ActualWidth, element.ActualHeight));
   //}




} // namespace uwp




