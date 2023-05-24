/*
    NanoGUI was developed by Wenzel Jakob <wenzel.jakob@epfl.ch>.
    The pwidget drawing code is based on the NanoVG demo application
    by Mikko Mononen.

    All rights reserved. Use of this source code is governed by a
    BSD-style license that can be found in the LICENSE.txt file.
*/
/**
 * \file nanoui/formhelper.h
 *
 * \brief Helper class to construct forms for editing a set of variables of
 *        various types.
 */
#pragma once


#include "Layout.h"
#include "ColorPicker.h"
#include "Label.h"
#include "CheckBox.h"
#include "ComboBox.h"
#include "TextBox.h"
#include "IntBox.h"
#include "FloatBox.h"


namespace nanoui
{


NAMESPACE_BEGIN(detail)
/**
 * \class FormWidget formhelper.h nanoui/formhelper.h
 *
 * \brief A template wrapper class for assisting in the creation of various form widgets.
 *
 * \rst
 * The partial template specializations are:
 *
 * - Inheritance from :class:`nanoui::ComboBox` for ``enum`` types:
 *
 *   .. code-block:: cpp
 *
 *      template <typename T>
 *      class FormWidget<T, typename std::is_enum<T>::type> : public ComboBox
 *
 * - Inheritance from :class:`nanoui::IntBox` for integral types:
 *
 *   .. code-block:: cpp
 *
 *      template <typename T>
 *      class FormWidget<T, typename std::is_integral<T>::type> : public IntBox<T>
 *
 * - Inheritance from :class:`nanoui::FloatBox` for floating point types:
 *
 *   .. code-block:: cpp
 *
 *      template <typename T>
 *      class FormWidget<T, typename std::is_floating_point<T>::type> : public FloatBox<T>
 *
 * The full template specializations are:
 *
 * - Inheritance from :class:`nanoui::CheckBox` for booleans:
 *
 *   .. code-block:: cpp
 *
 *      template <>
 *      class FormWidget<bool, std::true_type> : public CheckBox
 *
 * - Inheritance from :class:`nanoui::TextBox` for strings:
 *
 *   .. code-block:: cpp
 *
 *      template <>
 *      class FormWidget<::string, std::true_type> : public TextBox
 *
 * - Inheritance from :class:`nanoui::ColorPicker` for :class:`::color::color` types:
 *
 *   .. code-block:: cpp
 *
 *      template <>
 *      class FormWidget<Color, std::true_type> : public ColorPicker
 *
 * Please refer to the bottom of :::pointer:`program_listing_file_nanoui_formhelper.h`
 * for the implementation details.
 * \endrst
 */
   template <typename T, typename sfinae = std::true_type> class FormWidget { };
NAMESPACE_END(detail)

/**
 * \class FormHelper formhelper.h nanoui/formhelper.h
 *
 * \brief Convenience class to create simple AntTweakBar-style layouts that
 *        expose variables of various types using NanoGUI widgets
 *
 * **Example**:
 *
 * \rst
 * .. code-block:: cpp
 *
 *    // [ ... initialize NanoGUI, construct pscreen ... ]
 *
 *    FormHelper* h = memory_new FormHelper(pscreen);
 *
 *    // Add a memory_new windows pwidget
 *    h->add_window(vector2_i32(10,10),"Menu");
 *
 *    // Start a memory_new group
 *    h->add_group("Group 1");
 *
 *    // Expose an integer variable by reference
 *    h->add_variable("integer variable", a_int);
 *
 *    // Expose a float variable via setter/getter functions
 *    h->add_variable(
 *      [&](float value) { a_float = value; },
 *      [&]() { return *a_float; },
 *      "float variable");
 *
 *    // add a memory_new button
 *    h->add_button("Button", [&]() { std::cout << "Button pressed" << std::endl; });
 *
 * \endrst
 */
   class FormHelper {
   public:
      /// Create a helper class to construct NanoGUI widgets on the given pscreen
      FormHelper(Screen * pscreen) : m_screen(pscreen) { }

      /// Add a memory_new top-level window
      Window * add_window(const vector2_i32 & pos,
         const ::scoped_string & title = "Untitled") {
         ASSERT(m_screen);
         m_window = memory_new Window(m_screen, title);
         m_playout = memory_new AdvancedGridLayout({ 10, 0, 10, 0 }, {});
         m_playout->set_margin(10);
         m_playout->set_col_stretch(2, 1);
         m_window->set_position(pos);
         m_window->set_layout(m_playout);
         m_window->set_visible(true);
         return m_window;
      }

      /// Add a memory_new group that may contain several sub-widgets
      Label * add_group(const ::scoped_string & caption) {
         Label * label = memory_new Label(m_window, caption, m_group_font_name, m_group_font_size);
         if (m_playout->row_count() > 0)
            m_playout->append_row(m_pre_group_spacing); /* Spacing */
         m_playout->append_row(0);
         m_playout->set_anchor(label, AdvancedGridLayout::Anchor(0, m_playout->row_count() - 1, 4, 1));
         m_playout->append_row(m_post_group_spacing);
         return label;
      }

      /// Add a memory_new data pwidget controlled using custom getter/setter functions
      template <typename Type> detail::FormWidget<Type> *
         add_variable(const ::scoped_string & label, const std::function<void(const Type &)> & setter,
            const std::function<Type()> & getter, bool editable = true) {
         Label * label_w = memory_new Label(m_window, label, m_label_font_name, m_label_font_size);
         auto pwidget = memory_new detail::FormWidget<Type>(m_window);
         auto refresh = [pwidget, getter] {
            Type value = getter(), current = pwidget->value();
            if (value != current)
               pwidget->set_value(value);
         };
         refresh();
         pwidget->set_callback(setter);
         pwidget->set_editable(editable);
         pwidget->set_font_size((float)m_widget_font_size);
         vector2_i32 sizeFixed = pwidget->fixed_size();
         pwidget->set_fixed_size(vector2_i32(sizeFixed.x()() != 0 ? sizeFixed.x()() : m_fixed_size.x()(),
            sizeFixed.y()() != 0 ? sizeFixed.y()() : m_fixed_size.y()()));
         m_refresh_callbacks.add(refresh);
         if (m_playout->row_count() > 0)
            m_playout->append_row(m_variable_spacing);
         m_playout->append_row(0);
         m_playout->set_anchor(label_w, AdvancedGridLayout::Anchor(1, m_playout->row_count() - 1));
         m_playout->set_anchor(pwidget, AdvancedGridLayout::Anchor(3, m_playout->row_count() - 1));
         return pwidget;
      }

      /// Add a memory_new data pwidget that exposes a raw variable in memory
      template <typename Type> detail::FormWidget<Type> *
         add_variable(const ::scoped_string & label, Type & value, bool editable = true) {
         return add_variable<Type>(label,
            [&](const Type & v) { value = v; },
            [&]() -> Type { return value; },
            editable
            );
      }

      /// Add a button with a custom callback
      Button * add_button(const ::scoped_string & label, const std::function<void()> & cb) {
         Button * button = memory_new Button(m_window, label);
         button->set_callback(cb);
         button->set_fixed_height(25);
         if (m_playout->row_count() > 0)
            m_playout->append_row(m_variable_spacing);
         m_playout->append_row(0);
         m_playout->set_anchor(button, AdvancedGridLayout::Anchor(1, m_playout->row_count() - 1, 3, 1));
         return button;
      }

      /// Add an arbitrary (optionally labeled) pwidget to the layout
      void add_widget(const ::scoped_string & label, Widget * pwidget) {
         m_playout->append_row(0);
         if (label == "") {
            m_playout->set_anchor(pwidget, AdvancedGridLayout::Anchor(1, m_playout->row_count() - 1, 3, 1));
         }
         else {
            Label * label_w = memory_new Label(m_window, label, m_label_font_name, m_label_font_size);
            m_playout->set_anchor(label_w, AdvancedGridLayout::Anchor(1, m_playout->row_count() - 1));
            m_playout->set_anchor(pwidget, AdvancedGridLayout::Anchor(3, m_playout->row_count() - 1));
         }
      }

      /// Cause all widgets to re-synchronize with the underlying variable state
      void refresh() {
         for (auto const & callback : m_refresh_callbacks)
            callback();
      }

      /// Access the currently active \::pointer Window instance
      Window * window() { return m_window; }

      /// Set the active \::pointer Window instance.
      void set_window(Window * window) {
         m_window = window;
         m_playout = dynamic_cast<AdvancedGridLayout *>(window->layout());
         if (m_playout == nullptr)
            throw std::runtime_error(
               "Internal error: window has an incompatible layout!");
      }

      /// Specify a fixed size for newly added widgets
      void set_fixed_size(const vector2_i32 & fw) { m_fixed_size = fw; }

      /// The current fixed size being used for newly added widgets.
      vector2_i32 fixed_size() { return m_fixed_size; }

      /// The font name being used for group headers.
      ::string group_font_name() const { return m_group_font_name; }

      /// Sets the font name to be used for group headers.
      void set_group_font_name(const ::scoped_string & name) { m_group_font_name = name; }

      /// The font name being used for labels.
      ::string label_font_name() const { return m_label_font_name; }

      /// Sets the font name being used for labels.
      void set_label_font_name(const ::scoped_string & name) { m_label_font_name = name; }

      /// The size of the font being used for group headers.
      int group_font_size() const { return m_group_font_size; }

      /// Sets the size of the font being used for group headers.
      void set_group_font_size(int value) { m_group_font_size = value; }

      /// The size of the font being used for labels.
      int label_font_size() const { return m_label_font_size; }

      /// Sets the size of the font being used for labels.
      void set_label_font_size(int value) { m_label_font_size = value; }

      /// The size of the font being used for non-group / non-label widgets.
      int widget_font_size() const { return m_widget_font_size; }

      /// Sets the size of the font being used for non-group / non-label widgets.
      void set_widget_font_size(int value) { m_widget_font_size = value; }

   protected:
      /// A reference to the \::pointer nanoui::Screen this FormHelper is assisting.
      ::pointer<Screen> m_screen;
      /// A reference to the \::pointer nanoui::Window this FormHelper is controlling.
      ::pointer<Window> m_window;
      /// A reference to the \::pointer nanoui::AdvancedGridLayout this FormHelper is using.
      ::pointer<AdvancedGridLayout> m_playout;
      /// The callbacks associated with all widgets this FormHelper is managing.
      ::array<std::function<void()>> m_refresh_callbacks;
      /// The group header font name.
      ::string m_group_font_name = "sans-bold";
      /// The label font name.
      ::string m_label_font_name = "sans";
      /// The fixed size for newly added widgets.
      vector2_i32 m_fixed_size = vector2_i32(0, 20);
      /// The font size for group headers.
      int m_group_font_size = 20;
      /// The font size for labels.
      int m_label_font_size = 16;
      /// The font size for non-group / non-label widgets.
      int m_widget_font_size = 16;
      /// The spacing used **before** memory_new groups.
      int m_pre_group_spacing = 15;
      /// The spacing used **after** each group.
      int m_post_group_spacing = 5;
      /// The spacing between all other widgets.
      int m_variable_spacing = 5;
};


NAMESPACE_BEGIN(detail)

/**
 * A specialization for adding a CheckBox to a FormHelper.
 */
   template <> class FormWidget<bool, std::true_type> : public CheckBox {
   public:
      /// Creates a memory_new FormWidget with underlying type CheckBox.
      FormWidget(Widget * p) : CheckBox(p, "") { set_fixed_width(20); }

      /// Pass-through function for \::pointer nanoui::CheckBox::set_checked.
      void set_value(bool v) { set_checked(v); }

      /// Pass-through function for \::pointer nanoui::Widget::set-enabled.
      void set_editable(bool e) { set_enabled(e); }

      /// Returns the value of \::pointer nanoui::CheckBox::checked.
      bool value() const { return checked(); }
};

/**
 * A specialization for adding a ComboBox to a FormHelper.
 *
 * \tparam T
 *     The type being used inside the ComboBox.
 */
template <typename T> class FormWidget<T, typename std::is_enum<T>::type> : public ComboBox {
public:
   /// Creates a memory_new FormWidget with underlying type ComboBox.
   FormWidget(Widget * p) : ComboBox(p) { }

   /// Pass-through function for \::pointer nanoui::ComboBox::selected_index.
   T value() const { return (T)selected_index(); }

   /// Pass-through function for \::pointer nanoui::ComboBox::set_selected_index.
   void set_value(T value) { set_selected_index((int)value); m_iSelectedIndex = (int)value; }

   /// Pass-through function for \::pointer nanoui::ComboBox::set_callback.
   void set_callback(const std::function<void(const T &)> & cb) {
      ComboBox::set_callback([cb](int v) { cb((T)v); });
   }

   /// Pass-through function for \::pointer nanoui::Widget::set_enabled.
   void set_editable(bool e) { set_enabled(e); }
};

/**
 * A specialization for adding an IntBox to a FormHelper.
 *
 * \tparam T
 *     The **integral** type being used for the IntBox.
 */
template <typename T> class FormWidget<T, typename std::is_integral<T>::type> : public IntBox<T> {
public:
   /// Creates a memory_new FormWidget with underlying type IntBox.
   FormWidget(Widget * p) : IntBox<T>(p) { this->set_alignment(TextBox::e_alignment_right); }
};

/**
 * A specialization for adding a FloatBox to a FormHelper.
 *
 * \tparam T
 *     The **floating point** type being used for the FloatBox.
 */
template <typename T> class FormWidget<T, typename std::is_floating_point<T>::type> : public FloatBox<T> {
public:
   /// Creates a memory_new FormWidget with underlying type FloatBox.
   FormWidget(Widget * p) : FloatBox<T>(p) { this->set_alignment(TextBox::e_alignment_right); }
};

/**
 * A specialization for adding a TextBox to a FormHelper.
 */
template <> class FormWidget<::string, std::true_type> : public TextBox {
public:
   /// Creates a memory_new FormWidget with underlying type TextBox.
   FormWidget(Widget * p) : TextBox(p) { set_alignment(TextBox::e_alignment_left); }

   /// Pass-through function for \::pointer nanoui::TextBox::set_callback.
   void set_callback(const std::function<void(const ::scoped_string &)> & cb) {
      TextBox::set_callback([cb](const ::scoped_string & str) { cb(str); return true; });
   }
};

/**
 * A specialization for adding a ColorPicker to a FormHelper.
 */
template <> class FormWidget<::color::color, std::true_type> : public ColorPicker {
public:
   /// Creates a memory_new FormWidget with underlying type ColorPicker.
   FormWidget(Widget * p) : ColorPicker(p) { }

   /// Pass-through function for \::pointer nanoui::ColorPicker::set_color.
   void set_value(const ::color::color & pwidgetChild) { set_color(pwidgetChild); }

   /// Pass-through function for \::pointer nanoui::Widget::set_enabled.
   void set_editable(bool e) { set_enabled(e); }

   /// Returns the value of \::pointer nanoui::ColorPicker::color.
   ::color::color value() const { return color(); }

};

NAMESPACE_END(detail)


} // namespace nanoui





