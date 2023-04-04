/*
    nanoui/textbox.h -- Fancy text box with builtin regular
    expression-based validation

    The text box widget was contributed by Christian Schueller.

    NanoGUI was developed by Wenzel Jakob <wenzel.jakob@epfl.ch>.
    The widget drawing code is based on the NanoVG demo application
    by Mikko Mononen.

    All rights reserved. Use of this source code is governed by a
    BSD-style license that can be found in the LICENSE.txt file.
*/
/** \file */
#pragma once


#include "Widget.h"
#include "Screen.h"
#include "aura/user/user/interaction.h"
#include <sstream>
#include <limits>


namespace nanoui
{


/**
 * \class TextBox textbox.h nanoui/textbox.h
 *
 * \brief Fancy text box with builtin regular expression-based validation.
 *
 * \remark
 *     This class overrides \ref nanoui::Widget::mIconExtraScale to be ``0.8f``,
 *     which affects all subclasses of this Widget.  Subclasses must explicitly
 *     set a different value if needed (e.g., in their constructor).
 */
   class CLASS_DECL_NANOUI TextBox : public Widget {
   public:
      /// How to align the text in the text box.
      enum class Alignment {
         Left,
         Center,
         Right
      };

      Color                         m_colorBackground = Color(32, 32);
      
      ::write_text::font_pointer       m_pfontSpin;

      TextBox(Widget * parent, const ::scoped_string & value = "Untitled");

      bool editable() const { return m_editable; }
      void set_editable(bool editable);

      bool spinnable() const { return m_spinnable; }
      void set_spinnable(bool spinnable) { m_spinnable = spinnable; }

      ::string value() const { return m_value; }
      void set_value(const ::scoped_string & value) {
         m_value = value;

         auto pscreen = screen();

         if (pscreen)
         {

            auto puserinteraction = pscreen->m_puserinteraction;

            if (puserinteraction)
            {
               puserinteraction->set_need_redraw();
               puserinteraction->post_redraw();

            }

         }

      }

      ::string default_value() const { return m_default_value; }
      void set_default_value(const ::scoped_string & default_value) { m_default_value = default_value; }

      Alignment alignment() const { return m_alignment; }
      void set_alignment(Alignment align) { m_alignment = align; }

      ::string units() const { return m_units; }
      void set_units(const ::scoped_string & units) { m_units = units; }

      int units_image() const { return m_units_image; }
      void set_units_image(int image) { m_units_image = image; }

      /// Return the underlying regular expression specifying valid formats
      ::string format() const { return m_format; }
      /// Specify a regular expression specifying valid formats
      void set_format(const ::scoped_string & format) { m_format = format; }

      /// Return the placeholder text to be displayed while the text box is empty.
      ::string placeholder() const { return m_placeholder; }
      /// Specify a placeholder text to be displayed while the text box is empty.
      void set_placeholder(const ::scoped_string & placeholder) { m_placeholder = placeholder; }

      /// Set the \ref Theme used to draw this widget
      virtual void set_theme(Theme * theme) override;

      /// The callback to execute when the value of this TextBox has changed.
      ::function<bool(const ::scoped_string & str)> callback() const { return m_callback; }

      /// Sets the callback to execute when the value of this TextBox has changed.
      void set_callback(const ::function<bool(const ::scoped_string & str)> & callback) { m_callback = callback; }

      bool mouse_enter_event(const Vector2i & p, bool enter, const ::user::e_key & ekeyModifiers) override;
      bool mouse_button_event(const Vector2i & p, ::user::e_mouse emouse, bool down, const ::user::e_key & ekeyModifiers) override;
      bool mouse_motion_event(const Vector2i & p, const Vector2i & rel, const ::user::e_key & ekeyModifiers) override;
      bool mouse_drag_event(const Vector2i & p, const Vector2i & rel, const ::user::e_key & ekeyModifiers) override;
      bool focus_event(bool focused) override;
      bool keyboard_event(::user::enum_key ekey, int scancode, int action, const ::user::e_key & ekeyModifiers, const ::string & strText) override;
      bool keyboard_character_event(unsigned int codepoint) override;

      Vector2i preferred_size(::nano2d::context * pcontext, bool bRecalcTextSize = true) override;
      void draw(::nano2d::context * pcontext) override;
   protected:
      bool check_format(const ::scoped_string & input, const ::scoped_string & format);
      bool copy_selection();
      void paste_from_clipboard();
      bool delete_selection();

      void update_cursor(::nano2d::context * pcontext, float lastx,
         const ::nano2d::glyphPosition * glyphs, int size);
      float cursor_index_to_position(int index, float lastx,
         const ::nano2d::glyphPosition * glyphs, int size);
      int position_to_cursor_index(float posx, float lastx,
         const ::nano2d::glyphPosition * glyphs, int size);

      /// The location (if any) for the spin area.
      enum class SpinArea { None, Top, Bottom };
      SpinArea spin_area(const Vector2i & pos);

   protected:
      bool m_editable;
      bool m_spinnable;
      bool m_committed;
      ::string m_value;
      ::string m_default_value;
      Alignment m_alignment;
      ::string m_units;
      ::string m_format;
      int m_units_image;
      ::function<bool(const ::scoped_string & str)> m_callback;
      bool m_valid_format;
      ::string m_value_temp;
      ::string m_placeholder;
      int m_cursor_pos;
      int m_selection_pos;
      Vector2i m_mouse_pos;
      Vector2i m_mouse_down_pos;
      Vector2i m_mouse_drag_pos;
      ::user::e_key m_mouse_down_modifier;
      float m_text_offset;
      class ::time m_last_click;
};

/**
 * \class IntBox textbox.h nanoui/textbox.h
 *
 * \brief A specialization of TextBox for representing integral values.
 *
 * Template parameters should be integral types, e.g. ``int``, ``long``,
 * ``uint32_t``, etc.
 */
template <typename Scalar> class IntBox : public TextBox {
public:
   IntBox(Widget * parent, Scalar value = (Scalar)0) : TextBox(parent) {
      set_default_value("0");
      set_format(::std::is_signed<Scalar>::value ? "[-]?[0-9]*" : "[0-9]*");
      set_value_increment(1);
      set_min_max_values(::std::numeric_limits<Scalar>::lowest(), ::std::numeric_limits<Scalar>::max());
      set_value(value);
      set_spinnable(false);
   }

   Scalar value() const {
      Scalar value = 0;
      from_string(value, TextBox::value());
      return value;
   }

   void set_value(Scalar value) {
      Scalar clamped_value = std::min(std::max(value, m_min_value), m_max_value);
      TextBox::set_value(::as_string(clamped_value));
   }

   void set_callback(const ::function<void(Scalar)> & cb) {
      TextBox::set_callback(
         [cb, this](const ::scoped_string & str) {
            Scalar value = 0;
            from_string(value, str);
            set_value(value);
            cb(value);
            return true;
         }
      );
   }

   void set_value_increment(Scalar incr) {
      m_value_increment = incr;
   }

   void set_min_value(Scalar min_value) {
      m_min_value = min_value;
   }

   void set_max_value(Scalar max_value) {
      m_max_value = max_value;
   }

   void set_min_max_values(Scalar min_value, Scalar max_value) {
      set_min_value(min_value);
      set_max_value(max_value);
   }

   virtual bool mouse_button_event(const Vector2i & p, ::user::e_mouse emouse, bool down, const ::user::e_key & ekeyModifiers) override
   {

      if ((m_editable || m_spinnable) && down)
      {

         m_mouse_down_value = value();

      }

      SpinArea area = spin_area(p);
      if (m_spinnable && area != SpinArea::None && down && !focused()) {
         if (area == SpinArea::Top) {
            set_value(value() + m_value_increment);
            if (m_callback)
               m_callback(m_value);

         }
         else if (area == SpinArea::Bottom) {
            set_value(value() - m_value_increment);
            if (m_callback)
               m_callback(m_value);
         }
         return true;
      }

      return TextBox::mouse_button_event(p, emouse, down, ekeyModifiers);
   }


   virtual bool mouse_drag_event(const Vector2i & p, const Vector2i & rel, const ::user::e_key & ekeyModifiers) override
   {

      if (TextBox::mouse_drag_event(p, rel, ekeyModifiers))
      {

         return true;

      }

      if (m_spinnable && !focused() && ekeyModifiers & ::user::e_key_right_button && m_mouse_down_pos.x() != -1)
      {

         int value_delta = static_cast<int>((p.x() - m_mouse_down_pos.x()) / float(10));

         set_value(m_mouse_down_value + value_delta * m_value_increment);

         if (m_callback)
         {

            m_callback(m_value);

         }

         return true;

      }

      return false;

   }


   virtual bool scroll_event(const Vector2i & p, const Vector2f & rel) override
   {

      if (Widget::scroll_event(p, rel))
      {

         return true;

      }

      if (m_spinnable && !focused())
      {

         int value_delta = (rel.y() > 0) ? 1 : -1;

         set_value(value() + value_delta * m_value_increment);

         if (m_callback)
         {

            m_callback(m_value);

         }

         return true;

      }

      return false;

   }

private:
   Scalar m_mouse_down_value;
   Scalar m_value_increment;
   Scalar m_min_value, m_max_value;
};

/**
 * \class FloatBox textbox.h nanoui/textbox.h
 *
 * \brief A specialization of TextBox representing floating point values.

 *  The emplate parametersshould a be floating point type, e.g. ``float`` or
 *  ``double``.
 */
template <typename Scalar> class FloatBox : public TextBox {
public:
   FloatBox(Widget * parent, Scalar value = (Scalar)0.f) : TextBox(parent) {
      m_number_format = sizeof(Scalar) == sizeof(float) ? "%.4g" : "%.7g";
      set_default_value("0");
      set_format("[-+]?[0-9]*\\.?[0-9]+([e_e][-+]?[0-9]+)?");
      set_value_increment((Scalar)0.1);
      set_min_max_values(std::numeric_limits<Scalar>::lowest(),
         std::numeric_limits<Scalar>::max());
      set_value(value);
      set_spinnable(false);
   }

   ::string number_format() const { return m_number_format; }

   void number_format(const ::scoped_string & format) { m_number_format = format; }

   Scalar value() const 
   {
      Scalar scalar;
      ::from_string(scalar, TextBox::value());
      return scalar;
   }

   void set_value(Scalar value) {
      Scalar clamped_value = std::min(std::max(value, m_min_value), m_max_value);
      char buffer[50];
      std::snprintf(buffer, 50, m_number_format.c_str(), clamped_value);
      TextBox::set_value(buffer);
   }

   void set_callback(const ::function<void(Scalar)> & cb) {
      TextBox::set_callback([cb, this](const ::scoped_string & str) {
         Scalar scalar;
         ::from_string(scalar, str);
         set_value(scalar);
         cb(scalar);
         return true;
         });
   }

   void set_value_increment(Scalar incr) {
      m_value_increment = incr;
   }

   void set_min_value(Scalar min_value) {
      m_min_value = min_value;
   }

   void set_max_value(Scalar max_value)
   {

      m_max_value = max_value;

   }


   void set_min_max_values(Scalar min_value, Scalar max_value)
   {

      set_min_value(min_value);

      set_max_value(max_value);

   }


   bool mouse_button_event(const Vector2i & p, ::user::e_mouse emouse, bool down, const ::user::e_key & ekeyModifiers) override
   {

      if ((m_editable || m_spinnable) && down)
      {

         m_mouse_down_value = value();

      }

      SpinArea area = spin_area(p);

      if (m_spinnable && area != SpinArea::None && down && !focused())
      {

         if (area == SpinArea::Top)
         {

            set_value(value() + m_value_increment);

            if (m_callback)
            {

               m_callback(m_value);

            }

         }
         else if (area == SpinArea::Bottom) 
         {

            set_value(value() - m_value_increment);

            if (m_callback)
            {

               m_callback(m_value);

            }

         }

         return true;

      }

      return TextBox::mouse_button_event(p, emouse, down, ekeyModifiers);

   }


   bool mouse_drag_event(const Vector2i & p, const Vector2i & rel, const ::user::e_key & ekeyModifiers) override 
   {

      if (TextBox::mouse_drag_event(p, rel, ekeyModifiers))
      {

         return true;

      }

      if (m_spinnable && !focused() && ekeyModifiers & ::user::e_key_right_button && m_mouse_down_pos.x() != -1) 
      {

         int value_delta = static_cast<int>((p.x() - m_mouse_down_pos.x()) / float(10));

         set_value(m_mouse_down_value + value_delta * m_value_increment);

         if (m_callback)
         {

            m_callback(m_value);

         }

         return true;

      }

      return false;

   }


   virtual bool scroll_event(const Vector2i & p, const Vector2f & rel) override 
   {

      if (Widget::scroll_event(p, rel))
      {

         return true;

      }

      if (m_spinnable && !focused()) 
      {

         int value_delta = (rel.y() > 0) ? 1 : -1;

         set_value(value() + value_delta * m_value_increment);

         if (m_callback)
         {

            m_callback(m_value);

         }

         return true;

      }

      return false;

   }

private:

   ::string m_number_format;

   Scalar m_mouse_down_value;

   Scalar m_value_increment;

   Scalar m_min_value, m_max_value;

};




} // namespace nanoui





