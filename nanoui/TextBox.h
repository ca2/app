/*
    nanoui/textbox.h -- Fancy text box with builtin regular
    expression-based validation

    The text box pwidget was contributed by Christian Schueller.

    NanoGUI was developed by Wenzel Jakob <wenzel.jakob@epfl.ch>.
    The pwidget drawing code is based on the NanoVG demo application
    by Mikko Mononen.

    All rights reserved. Use of this source code is governed by a
    BSD-style license that can be found in the LICENSE.txt file.
*/
/** \file */
#pragma once


#include "Widget.h"
#include "Screen.h"
#include "aura/user/user/interaction.h"
//#include <sstream>
//#include <limits>


namespace nanoui
{


   /**
    * \class TextBox textbox.h nanoui/textbox.h
    *
    * \brief Fancy text box with builtin regular expression-based validation.
    *
    * \remark
    *     This class overrides \::pointer nanoui::Widget::mIconExtraScale to be ``0.8f``,
    *     which affects all subclasses of this Widget.  Subclasses must explicitly
    *     set a different value if needed (e.g., in their constructor).
    */
   class CLASS_DECL_NANOUI TextBox : 
      public Widget
   {
   public:
      
      /// How to align the text in the text box.
      
      enum enum_alignment 
      {
         e_alignment_left,
         e_alignment_center,
         e_alignment_right
      };

      bool                                            m_bChanged;
      bool                                            m_bEditable;
      bool                                            m_bSpinnable;
      bool                                            m_bCommitted;
      ::string                                        m_strValue;
      ::string                                        m_strDefaultValue;
      enum_alignment                                  m_ealignment;
      ::string                                        m_strUnit;
      ::string                                        m_strFormat;
      int                                             m_iUnitImage;
      ::function<bool(const ::scoped_string& str) >   m_callback;
      ::function<void() >                             m_callbackEndEdit;
      ::function<void() >                             m_callbackOnEdit;
      bool                                            m_bValidFormat;
      ::string                                        m_strValueEdit;
      ::string                                        m_strPlaceHolder;
      ::character_count                                       m_iSelectionEnd;
      ::character_count                                       m_iSelectionStart;
      int_point                                        m_mouse_pos;
      //bool                                            m_bMouseDown;
      int_point                                        m_pointMouseDown;
      int_point                                        m_pointMouseDrag;
      ::user::e_key                                   m_ekeyMouseDownModifier;
      float                                           m_fTextOffset;
      //class ::time m_timeLast;
      ::color::color                                  m_colorDeepBackground = ::color::transparent;
      ::color::color                                  m_colorBackground = ::color::color(32, 32);
      ::write_text::font_pointer                      m_pfontSpin;
      bool                                            m_bAutoDeleteOnFinishEditing;

      


      TextBox(Widget* parent, const ::scoped_string& value = "Untitled");


      bool editable() const { return m_bEditable; }
      void set_editable(bool editable);

      bool spinnable() const { return m_bSpinnable; }
      void set_spinnable(bool spinnable) { m_bSpinnable = spinnable; }

      ::string value() const { return m_strValue; }
      void set_value(const ::scoped_string& value, const ::action_context & actioncontext);

      ::string default_value() const { return m_strDefaultValue; }
      void set_default_value(const ::scoped_string& default_value) { m_strDefaultValue = default_value; }

      enum_alignment alignment() const { return m_ealignment; }
      void set_alignment(enum_alignment align) { m_ealignment = align; }

      ::string unit() const { return m_strUnit; }
      void set_unit(const ::scoped_string& units) { m_strUnit = units; }

      int unit_image() const { return m_iUnitImage; }
      void set_unit_image(int image) { m_iUnitImage = image; }

      /// Return the underlying regular expression specifying valid formats
      ::string format() const { return m_strFormat; }
      /// Specify a regular expression specifying valid formats
      void set_format(const ::scoped_string& format) { m_strFormat = format; }

      /// Return the placeholder text to be displayed while the text box is empty.
      ::string placeholder() const { return m_strPlaceHolder; }
      /// Specify a placeholder text to be displayed while the text box is empty.
      void set_placeholder(const ::scoped_string& placeholder) { m_strPlaceHolder = placeholder; }

      /// Set the \::pointer Theme used to draw this pwidget
      virtual void set_theme(const  ::pointer < Theme > & theme) override;

      /// The callback to execute when the value of this TextBox has changed.
      ::function<bool(const ::scoped_string& str)> callback() const { return m_callback; }

      /// Sets the callback to execute when the value of this TextBox has changed.
      void set_callback(const ::function<bool(const ::scoped_string& str)>& callback) { m_callback = callback; }

      bool mouse_enter_event(const int_point& p, bool enter, const ::user::e_key& ekeyModifiers) override;
      bool mouse_button_event(const int_point& p, ::user::e_mouse emouse, bool down, bool bDoubleClick, const ::user::e_key& ekeyModifiers) override;
      bool mouse_motion_event(const int_point& p, const int_size& rel, bool bDown, const ::user::e_key& ekeyModifiers) override;
      //bool mouse_drag_event(const sequence2_int & p, const sequence2_int & rel, const ::user::e_key & ekeyModifiers) override;
      bool focus_event(bool focused) override;
      bool keyboard_event(::user::enum_key ekey, int scancode, int action, const ::user::e_key& ekeyModifiers, const ::string& strText) override;
      bool keyboard_character_event(unsigned int codepoint) override;

      virtual bool on_command(const ::atom& atom);
      virtual void edit_select_all();
      virtual void edit_copy();
      virtual void edit_cut();
      virtual void edit_paste();

      
      virtual void start_in_place_edit();

      // returns true if something changed that needs redrawing
      bool end_in_place_edit() override;


      int_size preferred_size(::nano2d::context* pcontext, bool bRecalcTextSize = true) override;
      void draw(::nano2d::context* pcontext) override;
   protected:
      bool check_format(const ::scoped_string& input, const ::scoped_string& format);
      bool copy_selection();
      void paste_from_clipboard();
      bool delete_selection();

      void update_cursor(::nano2d::context* pcontext, float lastx,
         const ::nano2d::glyphPosition* glyphs, ::character_count size);
      float cursor_index_to_position(::character_count iIndex, float lastx,
         const ::nano2d::glyphPosition* glyphs, ::character_count size);
      ::character_count position_to_cursor_index(float posx, float lastx,
         const ::nano2d::glyphPosition* glyphs, ::character_count size);

      /// The location (if any) for the spin area.
      enum class SpinArea { None, Top, Bottom };
      
      SpinArea spin_area(const int_point & pos);
      

   };


} // namespace nanoui



