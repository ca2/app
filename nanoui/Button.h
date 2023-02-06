/*
    NanoGUI was developed by Wenzel Jakob <wenzel.jakob@epfl.ch>.
    The widget drawing code is based on the NanoVG demo application
    by Mikko Mononen.

    All rights reserved. Use of this source code is governed by a
    BSD-style license that can be found in the LICENSE.txt file.
*/
/**
 * \file nanoui/button.h
 *
 * \brief Defines the [Normal/Toggle/Radio/Popup] \ref nanoui::Button widget.
 */

#pragma once


#include "Widget.h"


namespace nanoui
{

/**
 * \class Button button.h nanoui/button.h
 *
 * \brief [Normal/Toggle/Radio/Popup] Button widget.
 */
   class NANOUI_EXPORT Button : 
   public Widget
   //,
   //virtual public ::appearance::button
{
   public:
      /// Flags to specify the button behavior (can be combined with binary OR)
      enum Flags {
         NormalButton = (1 << 0), ///< A normal button.
         RadioButton = (1 << 1), ///< A radio button.
         ToggleButton = (1 << 2), ///< A toggle button.
         PopupButton = (1 << 3), ///< A popup button.
         MenuButton = (1 << 4)  ///< A menu button.
      };

      /// The available icon positions.
      enum class IconPosition {
         Left,         ///< Button icon on the far left.
         LeftCentered, ///< Button icon on the left, centered (depends on caption text length).
         RightCentered,///< Button icon on the right, centered (depends on caption text length).
         Right         ///< Button icon on the far right.
      };

   
   
   //protected:
      /// The caption of this Button.
      ::string m_caption;

      float m_tw;
      float m_iw;
      float m_ih;

      /**
       * \brief The icon of this Button (``0`` means no icon).
       *
       * \rst
       * The icon to display with this Button.  If not ``0``, may either be a
       * picture icon, or one of the icons enumerated in
       * :ref:`file_nanoui_entypo.h`.  The kind of icon (image or Entypo)
       * is determined by the functions :func:`nanoui::::nano2d::IsImageIcon` and its
       * reciprocal counterpart :func:`nanoui::::nano2d::IsFontIcon`.
       * \endrst
       */
      int m_icon;

      /// The position to draw the icon at.
      IconPosition m_icon_position;

      /// Whether or not this Button has a Mouse Down On.
      bool m_bMouseDown;

      /// Whether or not this Button is checked.
      bool m_bChecked;

      /// The current flags of this button (see \ref nanoui::Button::Flags for options).
      int m_flags;

      /// The background color of this Button.
      Color m_background_color;

      /// The color of the caption text of this Button.
      Color m_text_color;

      /// The callback issued for all types of buttons.
      ::function<void()> m_callback;

      /// The callback issued for toggle buttons.
      ::function<void(bool)> m_change_callback;

      /// The button group for radio buttons.
      ::array<Button *> m_button_group;
   
      ::write_text::font_pointer        m_pfontIcon;

      /**
       * \brief Creates a button attached to the specified parent.
       *
       * \param parent
       *     The \ref nanoui::Widget this Button will be attached to.
       *
       * \param caption
       *     The name of the button (default ``"Untitled"``).
       *
       * \param icon
       *     The icon to display with this Button.  See \ref nanoui::Button::mIcon.
       */
      Button(Widget * parent, const ::scoped_string & caption = "Untitled", int icon = 0);

      /// Returns the caption of this Button.
      const ::scoped_string & caption() const { return m_caption; }

      /// Sets the caption of this Button.
      void set_caption(const ::scoped_string & caption) { m_caption = caption; }

      /// Returns the background color of this Button.
      const Color & background_color() const { return m_background_color; }
      /// Sets the background color of this Button.
      void set_background_color(const Color & background_color) { m_background_color = background_color; }

      /// Returns the text color of the caption of this Button.
      const Color & text_color() const { return m_text_color; }
      /// Sets the text color of the caption of this Button.
      void set_text_color(const Color & text_color) { m_text_color = text_color; }
   
   
      /// Returns the icon of this Button.  See \ref nanoui::Button::m_icon.
      int icon() const { return m_icon; }
      /// Sets the icon of this Button.  See \ref nanoui::Button::m_icon.
      void set_icon(int icon) { m_icon = icon; }

      /// The current flags of this Button (see \ref nanoui::Button::Flags for options).
      int flags() const { return m_flags; }
      /// Sets the flags of this Button (see \ref nanoui::Button::Flags for options).
      void set_flags(int button_flags) { m_flags = button_flags; }

      /// The position of the icon for this Button.
      IconPosition icon_position() const { return m_icon_position; }
      /// Sets the position of the icon for this Button.
      void set_icon_position(IconPosition icon_position) { m_icon_position = icon_position; }

      /// Whether or not this Button is currently pushed.
      bool checked() const { return m_bChecked; }
      /// Sets whether or not this Button is currently pushed.
      void set_check(bool bCheck) { m_bChecked = bCheck; }

      /// Return the push callback (for any type of button)
      ::function<void()> callback() const { return m_callback; }
      /// Set the push callback (for any type of button).
      void set_callback(const ::function<void()> & callback) { m_callback = callback; }

      /// Return the change callback (for toggle buttons)
      ::function<void(bool)> change_callback() const { return m_change_callback; }
      /// Set the change callback (for toggle buttons).
      void set_change_callback(const ::function<void(bool)> & callback) { m_change_callback = callback; }

      /// Return the button group (for radio buttons)
      const ::array<Button *> & button_group() const { return m_button_group; }
      /// Set the button group (for radio buttons)
      void set_button_group(const ::array<Button *> & button_group) { m_button_group = button_group; }

      /// The preferred size of this Button.
      virtual Vector2i preferred_size(::nano2d::context * pcontext, bool bRecalcTextSize = true) override;
      /// The callback that is called when any type of mouse button event is issued to this Button.
      virtual bool mouse_enter_event(const Vector2i & p, bool enter, const ::user::e_key & ekeyModifiers) override;
      virtual bool mouse_button_event(const Vector2i & p, ::user::e_mouse emouse, bool down, const ::user::e_key & ekeyModifiers) override;
      /// Responsible for drawing the Button.
      virtual void draw(::nano2d::context * pcontext) override;

      
      //bool call_click() override;

      //bool call_check(::enum_check echeck) override;

      //void _nanoui_to_user(::user::interaction * puserinteraction) override;

      void on_click();

};



} // namespace nanoui


