///*
//    NanoGUI was developed by Wenzel Jakob <wenzel.jakob@epfl.ch>.
//    The pwidget drawing code is based on the NanoVG demo application
//    by Mikko Mononen.
//
//    All rights reserved. Use of this source code is governed by a
//    BSD-style license that can be found in the LICENSE.txt file.
//*/
///**
// * \file nanoui/button.h
// *
// * \brief Defines the [Normal/Toggle/Radio/Popup] \::pointer nanoui::Button pwidget.
// */
//
//#pragma once
//
//
//#include "Button.h"
//
//
//namespace nanoui
//{
//
//   /**
//    * \class Button button.h nanoui/button.h
//    *
//    * \brief [Normal/Toggle/Radio/Popup] Button pwidget.
//    */
//   class CLASS_DECL_NANOUI ImageButton :
//      public nanoui::Button
//      //,
//      //virtual public ::appearance::button
//   {
//   public:
//      /// Flags to specify the button behavior (can be combined with binary OR)
//      enum Flags {
//         NormalButton = (1 << 0), ///< A normal button.
//         RadioButton = (1 << 1), ///< A radio button.
//         ToggleButton = (1 << 2), ///< A toggle button.
//         PopupButton = (1 << 3), ///< A popup button.
//         ContextMenuButton = (1 << 4)  ///< A context menu button.
//      };
//
//      /// The available icon positions.
//      enum class IconPosition {
//         Left,         ///< Button icon on the far left.
//         LeftCentered, ///< Button icon on the left, centered (depends on caption text length).
//         RightCentered,///< Button icon on the right, centered (depends on caption text length).
//         Right         ///< Button icon on the far right.
//      };
//
//
//
//      //protected:
//         /// The caption of this Button.
//      ::string m_strCaption;
//
//      float m_fTextWidth;
//      ::float_size m_sizeImage;
//      //float m_ih;
//
//      /**
//       * \brief The icon of this Button (``0`` means no icon).
//       *
//       * \rst
//       * The icon to display with this Button.  If not ``0``, may either be a
//       * picture icon, or one of the icons enumerated in
//       * :::pointer:`file_nanoui_entypo.h`.  The kind of icon (image or Entypo)
//       * is determined by the functions :func:`nanoui::nano2d::IsImageIcon` and its
//       * reciprocal counterpart :func:`nanoui::nano2d::IsFontIcon`.
//       * \endrst
//       */
//      int m_iIcon;
//
//      /// The position to draw the icon at.
//      IconPosition m_icon_position;
//
//      /// Whether or not this Button is checked.
//      bool m_bChecked;
//
//      /// The current flags of this button (see \::pointer nanoui::Button::Flags for options).
//      int m_flags;
//
//      /// The background color::color of this Button.
//      color::color m_colorBackground;
//
//      /// The color::color of the caption text of this Button.
//      color::color m_colorText;
//
//      /// The callback issued for all types of buttons.
//      ::function<void()> m_callback;
//
//      /// The callback issued for toggle buttons.
//      ::function<void(bool)> m_change_callback;
//
//      /// The button group for radio buttons.
//      ::array<Button*> m_button_group;
//
//      ::write_text::font_pointer        m_pfontIcon;
//
//      /**
//       * \brief Creates a button attached to the specified parent.
//       *
//       * \param parent
//       *     The \::pointer nanoui::Widget this Button will be attached to.
//       *
//       * \param caption
//       *     The name of the button (default ``"Untitled"``).
//       *
//       * \param icon
//       *     The icon to display with this Button.  See \::pointer nanoui::Button::mIcon.
//       */
//      Button(Widget* parent, const ::scoped_string& caption = "Untitled", int icon = 0);
//
//      /// Returns the caption of this Button.
//      ::string caption() const { return m_strCaption; }
//
//      /// Sets the caption of this Button.
//      void set_caption(const ::scoped_string& caption) { m_strCaption = caption; }
//
//      /// Returns the background color::color of this Button.
//      const color::color& colorBackground() const { return m_colorBackground; }
//      /// Sets the background color::color of this Button.
//      void set_background_color(const color::color& colorBackground) { m_colorBackground = colorBackground; }
//
//      /// Returns the text color::color of the caption of this Button.
//      const color::color& text_color() const { return m_colorText; }
//      /// Sets the text color::color of the caption of this Button.
//      void set_text_color(const color::color& text_color) { m_colorText = text_color; }
//
//
//      /// Returns the icon of this Button.  See \::pointer nanoui::Button::m_icon.
//      int icon() const { return m_iIcon; }
//      /// Sets the icon of this Button.  See \::pointer nanoui::Button::m_icon.
//      void set_icon(int iIcon) { m_iIcon = iIcon; }
//
//      /// The current flags of this Button (see \::pointer nanoui::Button::Flags for options).
//      int flags() const { return m_flags; }
//      /// Sets the flags of this Button (see \::pointer nanoui::Button::Flags for options).
//      void set_flags(int button_flags) { m_flags = button_flags; }
//
//      /// The position of the icon for this Button.
//      IconPosition icon_position() const { return m_icon_position; }
//      /// Sets the position of the icon for this Button.
//      void set_icon_position(IconPosition icon_position) { m_icon_position = icon_position; }
//
//      /// Whether or not this Button is currently pushed.
//      bool checked() const { return m_bChecked; }
//      /// Sets whether or not this Button is currently pushed.
//      virtual void set_checked(bool bChecked, const ::action_context& actioncontext);
//
//
//      /// Return the push callback (for any type of button)
//      ::function<void()> callback() const { return m_callback; }
//      /// Set the push callback (for any type of button).
//      void set_callback(const ::function<void()>& callback) { m_callback = callback; }
//
//      /// Return the change callback (for toggle buttons)
//      ::function<void(bool)> change_callback() const { return m_change_callback; }
//      /// Set the change callback (for toggle buttons).
//      void set_change_callback(const ::function<void(bool)>& callback) { m_change_callback = callback; }
//
//      /// Return the button group (for radio buttons)
//      const ::array<Button*>& button_group() const { return m_button_group; }
//      /// Set the button group (for radio buttons)
//      void set_button_group(const ::array<Button*>& button_group) { m_button_group = button_group; }
//
//      /// The preferred size of this Button.
//      virtual int_size preferred_size(::nano2d::context * pcontext, bool bRecalcTextSize = true) override;
//      /// The callback that is called when any type of mouse button happening is issued to this Button.
//      virtual bool mouse_enter_event(const int_point& p, bool enter, const ::user::e_key& ekeyModifiers) override;
//      virtual bool mouse_button_event(const int_point& p, ::user::e_mouse emouse, bool down, bool bDoubleClick, const ::user::e_key& ekeyModifiers) override;
//      /// Responsible for drawing the Button.
//      virtual void draw(::nano2d::context * pcontext) override;
//
//
//      //bool call_click() override;
//
//      //bool call_check(::enum_check echeck) override;
//
//      //void _nanoui_to_user(::user::interaction * puserinteraction) override;
//
//      void on_click();
//
//   };
//
//
//
//} // namespace nanoui
//
//
