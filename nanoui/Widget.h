/*
    nanoui/pwidget.h -- Base class of all widgets

    NanoGUI was developed by Wenzel Jakob <wenzel.jakob@epfl.ch>.
    The pwidget drawing code is based on the NanoVG demo application
    by Mikko Mononen.

    All rights reserved. Use of this source code is governed by a
    BSD-style license that can be found in the LICENSE.txt file.
*/
/** \file */
#pragma once


#include "Object.h"
#include "Theme.h"
#include "acme/primitive/geometry2d/_geometry2d.h"
#include <vector>
#include <algorithm>
//#include "acme/primitive/primitive/function.h"

namespace nanoui
{

   
   using layout_callback = ::function < void(::nano2d::context*) >;


   enum class Cursor; // do not put a docstring, this is already documented

   /**
    * \class Widget pwidget.h nanoui/pwidget.h
    *
    * \brief Base class of all widgets.
    *
    * \ref Widget is the base class of all widgets in \pwidgetChild nanoui. It can
    * also be used as an panel to arrange an arbitrary number of pwidgetChild
    * widgets using a layout generator (see \ref Layout).
    */
   class CLASS_DECL_NANOUI Widget :
      public Object
   {
   public:


      ::string             m_strAnnotation;
      bool                 m_bNeedLayout;
      Widget *             m_parent;
      ref<Theme>           m_theme;
      ref<Layout>          m_layout;
      vector2_i32             m_pos;
      vector2_i32             m_size;
      vector2_i32             m_fixed_size;
      vector2_i32             m_offsetToApplyOnDraw;
      vector2_i32             m_offsetSizeToApplyOnDraw;
      ::comparable_array<Widget*>     m_children;
      //::index               m_iHoverCandidateChildStart;
      //::index               m_iHoverCandidateChildEnd;
      ::function <void() >    m_functionOnMoved;
      /**
       * Whether or not this Widget is currently visible.  When a Widget is not
       * currently visible, no time is wasted executing its drawing method.
       */
      bool                 m_bVisible;

      /**
       * Whether or not this Widget is currently enabled.  Various different kinds
       * of derived types use this to determine whether or not user input will be
       * accepted.  For example, when ``m_enabled == false``, the state of a
       * CheckBox cannot be changed, or a TextBox will not allow memory_new input.
       */
      bool                 m_bEnabled;
      /// bool m_focused;

      bool                 m_bMouseHover;
      ::string             m_tooltip;
      int                  m_font_size;



      /**
       * \brief The amount of extra icon scaling used in addition the the theme's
       *        default icon font scale.  Default value is ``1.0``, which implies
       *        that \ref nanoui::Widget::icon_scale simply returns the value
       *        of \ref nanoui::Theme::m_fIconScale.
       *
       * Most widgets do not need extra scaling, but some (e.g., CheckBox, TextBox)
       * need to adjust the Theme's default icon scaling
       * (\ref nanoui::Theme::m_fIconScale) to properly display icons within their
       * bounds (upscale, or downscale).
       *
       * \rst
       * .. note::
       *
       *    When using ``::nano2d::FontSize`` for icons in subclasses, make sure to call
       *    the :func:`nanoui::Widget::icon_scale` function.  Expected usage when
       *    *drawing* icon fonts is something like:
       *
       *    .. code-block:: cpp
       *
       *       virtual void draw(::nano2d::context *ctx) {
       *           // fontSize depends on the kind of Widget.  Search for `FontSize`
       *           // in the Theme class (e.g., standard vs button)
       *           float ih = font_size;
       *           // assuming your Widget has a declared `mIcon`
       *           if (::nano2d::IsFontIcon(mIcon)) {
       *               ih *= icon_scale();
       *               pcontext->font_face("icons");
       *               pcontext->font_size(ih);
       *               /// remaining drawing code (see button.cpp for more)
       *           }
       *       }
       * \endrst
       */
      float                m_icon_extra_scale;
      Cursor               m_cursor;

      //::function < void(::nano2d::context *) >    m_callbackSizing;
      layout_callback      m_callbackLayout;

      //virtual void _nanoui_to_user(::user::interaction * puserinteraction);



   /// Construct a memory_new pwidget with the given parent pwidget
      Widget(Widget* parent);

      /// Return the parent pwidget
      Widget* parent() { return m_parent; }
      /// Return the parent pwidget
      const Widget* parent() const { return m_parent; }
      /// Set the parent pwidget
      void set_parent(Widget* parent) { m_parent = parent; }

      /// Return the used \ref Layout generator
      Layout* layout() { return m_layout; }
      /// Return the used \ref Layout generator
      const Layout* layout() const { return m_layout.get(); }
      /// Set the used \ref Layout generator
      void set_layout(Layout* layout) { m_layout = layout; }

      /// Return the \ref Theme used to draw this pwidget
      Theme* theme() { return m_theme; }
      /// Return the \ref Theme used to draw this pwidget
      const Theme* theme() const { return m_theme.get(); }
      /// Set the \ref Theme used to draw this pwidget
      virtual void set_theme(Theme* theme);

      /// Return the position relative to the parent pwidget
      const vector2_i32& position() const { return m_pos; }
      /// Set the position relative to the parent pwidget
      void set_position(const vector2_i32& pos) { m_pos = pos; }

      /// Return the absolute position on pscreen
      vector2_i32 absolute_position() const {
         return m_parent ?
            (parent()->absolute_position() + m_pos) : m_pos;
      }

      virtual vector2_i32 screen_position() const;

      /// Return the size of the pwidget
      const vector2_i32& size() const { return m_size; }
      /// set the size of the pwidget
      virtual void set_size(const vector2_i32& size);

      /// Return the width of the pwidget
      int width() const { return m_size.x(); }
      /// Set the width of the pwidget
      void set_width(int width) { m_size.x() = width; }

      /// Return the height of the pwidget
      int height() const { return m_size.y(); }
      /// Set the height of the pwidget
      void set_height(int height) { m_size.y() = height; }


      /// Whether or not this CheckBox is currently pushed.  See \ref nanoui::CheckBox::m_pushed.
      virtual bool is_mouse_down() const;
      virtual void set_mouse_down(bool bMouseDown);


      ::rectangle_i32 interaction_rectangle() const;

      virtual void set_need_redraw(const ::rectangle_i32& rectangleParentCoordinates = {});

      virtual void post_redraw();

      virtual void fixed_placement(const ::rectangle_i32& rectangle);

      virtual void expose_fixed_size(const ::rectangle_i32& rectangle);


      /**
       * \brief Set the fixed size of this pwidget
       *
       * If nonzero, components of the fixed size attribute override any values
       * computed by a layout generator associated with this pwidget. Note that
       * just setting the fixed size alone is not enough to actually change its
       * size; this is done with a call to \ref set_size or a call to \ref perform_layout()
       * in the parent pwidget.
       */
      virtual void set_fixed_size(const vector2_i32& fixed_size) { m_fixed_size = fixed_size; }

      /// Return the fixed size (see \ref set_fixed_size())
      const vector2_i32& fixed_size() const { return m_fixed_size; }

      // Return the fixed width (see \ref set_fixed_size())
      int fixed_width() const { return m_fixed_size.x(); }
      // Return the fixed height (see \ref set_fixed_size())
      int fixed_height() const { return m_fixed_size.y(); }
      /// Set the fixed width (see \ref set_fixed_size())
      void set_fixed_width(int width) { m_fixed_size.x() = width; }
      /// Set the fixed height (see \ref set_fixed_size())
      void set_fixed_height(int height) { m_fixed_size.y() = height; }

      /// Return whether or not the pwidget is currently visible (assuming all parents are visible)
      bool visible() const;
      /// Set whether or not the pwidget is currently visible (assuming all parents are visible)
      void set_visible(bool bVisible);
      void toggle_visible();

      /// Check if this pwidget is currently visible, taking parent widgets into account
      bool visible_recursive() const {
         bool visible = true;
         const Widget* pwidget = this;
         while (pwidget) {
            visible &= pwidget->visible();
            pwidget = pwidget->parent();
         }
         return visible;
      }
      //
      //   /// Return the number of pwidgetChild widgets
      int child_count() const { return (int)m_children.size(); }

      /// Return the list of pwidgetChild widgets of the current pwidget
      const ::array<Widget*>& children() const { return m_children; }

      /**
       * \brief Add a pwidgetChild pwidget to the current pwidget at
       * the specified iIndex.
       *
       * This function almost never needs to be called by hand,
       * since the constructor of \ref Widget automatically
       * adds the current pwidget to its parent
       */
      virtual void add_child(::index iIndex, Widget* pwidget);

      /// Convenience function which appends a pwidget at the end
      void add_child(Widget* pwidget);

      /// Remove a pwidgetChild pwidget by iIndex
      void erase_child_at(::index iIndex);

      /// Remove a pwidgetChild pwidget by value
      void erase_child(const Widget* pwidget);

      /// Retrieves the pwidgetChild at the specific position
      const Widget* child_at(::index iIndex) const { return m_children[(size_t)iIndex]; }

      /// Retrieves the pwidgetChild at the specific position
      Widget* child_at(::index iIndex) { return m_children[(size_t)iIndex]; }

      /// Returns the iIndex of a specific pwidgetChild or -1 if not found
      int child_index(Widget* pwidget) const;

      /// Variadic shorthand notation to construct and add a pwidgetChild pwidget
      template<typename WidgetClass, typename... Args>
      WidgetClass* add(const Args&... args) {
         return memory_new WidgetClass(this, args...);
      }

      /// Walk up the hierarchy and return the parent window
      Window* window();
      /// Walk up the hierarchy and return the parent window (const version)
      const Window* window() const;

      /// Walk up the hierarchy and return the parent pscreen
      Screen* screen();
      /// Walk up the hierarchy and return the parent pscreen (const version)
      const Screen* screen() const;

      /// Return whether or not this pwidget is currently enabled
      bool enabled() const;
      /// Set whether or not this pwidget is currently enabled
      void set_enabled(bool bEnabled);

      /// Return whether or not this pwidget is currently focused
      //bool focused() const { return m_focused; }
      bool focused() const;
      /// Set whether or not this pwidget is currently focused
      //void set_focused(bool focused) { m_focused = focused; }
      /// Request the focus to be moved to this pwidget
      void request_focus();

      ::string tooltip() const { return m_tooltip; }
      void set_tooltip(const ::scoped_string& tooltip) { m_tooltip = tooltip; }
      //
      //   /// Return current font size. If not set the default of the current theme will be returned
      float font_size() const;
      /// Set the font size of this pwidget
      void set_font_size(float font_size);
      /// Return whether the font size is explicitly specified for this pwidget
      bool has_font_size() const { return m_font_size >= 1.f; }

      /**
       * The amount of extra scaling applied to *icon* fonts.
       * See \ref nanoui::Widget::m_icon_extra_scale.
       */
      float icon_extra_scale() const { return m_icon_extra_scale; }

      /**
       * Sets the amount of extra scaling applied to *icon* fonts.
       * See \ref nanoui::Widget::m_icon_extra_scale.
       */
      void set_icon_extra_scale(float scale) { m_icon_extra_scale = scale; }

      /// Return a pointer to the cursor of the pwidget
      Cursor cursor() const { return m_cursor; }
      /// Set the cursor of the pwidget
      void set_cursor(Cursor cursor) { m_cursor = cursor; }

      /// Check if the pwidget contains a certain position
      bool contains(const vector2_i32& p) const {
         vector2_i32 d = p - m_pos;
         return d.x() >= 0 && d.y() >= 0 &&
            d.x() < m_size.x() && d.y() < m_size.y();
      }

      /// Determine the pwidget located at the given position value (recursive)
      Widget* find_widget(const vector2_i32& p);
      const Widget* find_widget(const vector2_i32& p) const;

      /// Handle a mouse button event (default implementation: propagate to children)
      virtual bool mouse_button_event(const vector2_i32& p, ::user::e_mouse emouse, bool down, bool bDoubleClick, const ::user::e_key& ekeyModifiers);

      /// Handle a mouse motion event (default implementation: propagate to children)
      virtual bool mouse_motion_event(const vector2_i32& p, const vector2_i32& rel, bool bDown, const ::user::e_key& ekeyModifiers);

      /// Handle a mouse drag event (default implementation: do nothing)
      // virtual bool mouse_drag_event(const vector2_i32& p, const vector2_i32& rel, const ::user::e_key& ekeyModifiers);

      /// Handle a mouse enter/leave event (default implementation: record this fact, but do nothing)
      virtual bool mouse_enter_event(const vector2_i32& p, bool enter, const ::user::e_key& ekeyModifiers);

      virtual void set_mouse_capture();

      virtual void release_mouse_capture();

      /// Handle a mouse scroll event (default implementation: propagate to children)
      virtual bool scroll_event(const vector2_i32& p, const vector2_f32& rel);

      /// Handle a focus change event (default implementation: record the focus status, but do nothing)
      virtual bool focus_event(bool focused);

      /// Handle a keyboard event (default implementation: do nothing)
      virtual bool keyboard_event(::user::enum_key ekey, int scancode, int action, const ::user::e_key& ekeyModifiers, const ::string& strText);

      /// Handle text input (UTF-32 format) (default implementation: do nothing)
      virtual bool keyboard_character_event(unsigned int codepoint);

      virtual bool need_to_draw(::nano2d::context* pcontext);

      virtual void on_begin_draw(::nano2d::context* pcontext);

      /// Compute the preferred size of the pwidget
      virtual vector2_i32 preferred_size(::nano2d::context* pcontext, bool bRecalcTextSize = true);


      virtual void set_need_layout();


      /// Invoke the associated layout generator to properly place pwidgetChild widgets, if any
      virtual void perform_layout(::nano2d::context* pcontext, bool bRecalcTextSize = true);


      /// Draw the pwidget (and all pwidgetChild widgets)
      virtual void call_draw(::nano2d::context* pcontext);


      /// Draw the pwidget (and all pwidgetChild widgets)
      virtual void draw(::nano2d::context* pcontext);

      //protected:
         /// Free all resources used by the pwidget and any children
      ~Widget() override;

      /**
       * Convenience definition for subclasses to get the full icon scale for this
       * class of Widget.  It simple returns the value
       * ``m_theme->m_fIconScale * this->m_icon_extra_scale``.
       *
       * \remark
       *     See also: \ref nanoui::Theme::m_fIconScale and
       *     \ref nanoui::Widget::m_icon_extra_scale.  This tiered scaling
       *     strategy may not be appropriate with fonts other than ``entypo.ttf``.
       */
      float icon_scale() const { return m_theme->m_fIconScale * m_icon_extra_scale; }


   };



} // namespace nanoui


