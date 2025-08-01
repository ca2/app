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


#include "nanoui/Object.h"
#include "nanoui/Theme.h"
#include "nanoui/in_place_edit_mapper.h"
///#include "acme/prototype/geometry2d/_geometry2d.h"
#include "acme/handler/item.h"
#include "acme/prototype/geometry2d/size.h"
#include "acme/prototype/geometry2d/rectangle.h"
#include "acme/user/user/container.h"
//#include <xxxvector>
//#include <xxxalgorithm>
//#include "acme/prototype/prototype/function.h"

namespace nanoui
{

   class in_place_edit;
   
   using layout_callback = ::function < void(::nano2d::context *) >;

   enum class Cursor; // do not put a docstring, this is already documented

   /**
    * \class Widget pwidget.h nanoui/pwidget.h
    *
    * \brief Base class of all widgets.
    *
    * \::pointer Widget is the base class of all widgets in \pwidgetChild nanoui. It can
    * also be used as an panel to arrange an arbitrary number of pwidgetChild
    * widgets using a layout generator (see \::pointer Layout).
    */
   class CLASS_DECL_NANOUI Widget :
      public Object,
      public ::user::acme_container,
      public in_place_edit_mapper
   {
   public:


      ::string                m_strAnnotation;
      bool                    m_bNeedLayout;
      ::pointer < Widget>     m_pwidgetParent;
      ::pointer<Theme>        m_ptheme;
      ::pointer<Layout>       m_playout;
      int_point               m_pos;
      int_size                m_size;
      int_size                m_fixed_size;
      bool                    m_bHoverCache;
      ::pointer<::nano2d::text_box>    m_ptextboxTooltip;

      //int_size                m_offsetToApplyOnDraw;
      //int_size                m_offsetSizeToApplyOnDraw;
      ::pointer<Widget>       m_pwidgetDragDropArena;
      ::pointer_array<Widget> m_children;
      //::collection::index               m_iHoverCandidateChildStart;
      //::collection::index               m_iHoverCandidateChildEnd;
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
       * CheckBox cannot be changed, or a TextBox will not allow ___new input.
       */
      bool                 m_bEnabled;
      /// bool m_focused;

      bool                 m_bMouseHover;
      ::string             m_tooltip;
      int                  m_font_size;



      /**
       * \brief The amount of extra icon scaling used in addition the the theme's
       *        default icon font scale.  Default value is ``1.0``, which implies
       *        that \::pointer nanoui::Widget::icon_scale simply returns the value
       *        of \::pointer nanoui::Theme::m_fIconScale.
       *
       * Most widgets do not need extra scaling, but some (e.g., CheckBox, TextBox)
       * need to adjust the Theme's default icon scaling
       * (\::pointer nanoui::Theme::m_fIconScale) to properly display icons within their
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
       *       virtual void draw(::nano2d::context  *ctx) {
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

      //::function < void(::nano2d::context  *) >    m_callbackSizing;
      layout_callback      m_callbackLayout;

      ::pointer < in_place_edit > m_pinplaceedit;




      //virtual void _nanoui_to_user(::user::interaction * puserinteraction);



   /// Construct a ___new pwidget with the given parent pwidget
      Widget(Widget* parent);

      /// Return the parent pwidget
      Widget* parent() { return m_pwidgetParent; }
      /// Return the parent pwidget
      const Widget* parent() const { return m_pwidgetParent; }
      /// Set the parent pwidget
      void set_parent(Widget* parent) { m_pwidgetParent = parent; }

      bool has_ascendant(Widget* pwidgetAscendantCandidate) const;

      template < typename TYPE >
      bool has_ascendant_of_type() const
      {

         auto pwidgetAscendant = this->parent();

         while (pwidgetAscendant != nullptr)
         {

            if (dynamic_cast < TYPE * >((Widget *)pwidgetAscendant) != nullptr)
            {

               return true;

            }

            pwidgetAscendant = pwidgetAscendant->parent();

         }

         return false;

      }


      /// Return the used \::pointer Layout generator
      Layout* layout() { return m_playout; }
      /// Return the used \::pointer Layout generator
      const Layout* layout() const { return m_playout.get(); }
      /// Set the used \::pointer Layout generator
      void set_layout(const ::pointer < Layout > & playout); 

      /// Return the \::pointer Theme used to draw this pwidget
      Theme* theme() { return m_ptheme; }
      /// Return the \::pointer Theme used to draw this pwidget
      const Theme* theme() const { return m_ptheme.get(); }
      /// Set the \::pointer Theme used to draw this pwidget
      virtual void set_theme(const ::pointer < Theme > & theme);

      /// Return the position relative to the parent pwidget
      const int_point& position() const { return m_pos; }
      /// Set the position relative to the parent pwidget
      void set_position(const int_point& pos) { m_pos = pos; }

      /// Return the absolute position on pscreen
      int_point absolute_position() const {
         return m_pwidgetParent ?
            (parent()->absolute_position() + m_pos) : m_pos;
      }

      virtual int_point screen_position() const;


      virtual int_size get_scroll_offset() const;
      virtual int_size get_accumulated_scroll_offset() const;

      /// Return the size of the pwidget
      const int_size& size() const { return m_size; }
      /// set the size of the pwidget
      virtual void set_size(const int_size& size);

      /// Return the width of the pwidget
      int width() const { return m_size.cx(); }
      /// Set the width of the pwidget
      void set_width(int width) { m_size.cx() = width; }

      /// Return the height of the pwidget
      int height() const { return m_size.cy(); }
      /// Set the height of the pwidget
      void set_height(int height) { m_size.cy() = height; }

      ::pointer < TextBox > create_in_place_edit(const ::float_rectangle& rectangle, const ::scoped_string & scopedstr);

      // returns true if something changed that needs redrawing
      virtual bool end_in_place_edit();

      virtual void end_all_in_place_edits();

      virtual bool on_mouse_button_in_place_edit(in_place_edit* pinplacedit, bool bDown, bool bDoubleClick);
      virtual void on_before_in_place_edit(in_place_edit* pinplaceedit);

      /// Whether or not this CheckBox is currently pushed.  See \::pointer nanoui::CheckBox::m_pushed.
      virtual bool is_mouse_down() const;
      virtual void set_mouse_down(bool bMouseDown);


      ::int_rectangle interaction_rectangle() const;

      virtual void set_need_redraw(const ::int_rectangle& rectangle = {}, function < void() > function = nullptr);

      virtual void post_redraw();

      virtual void fixed_placement(const ::int_rectangle& rectangle);

      virtual void expose_fixed_size(const ::int_rectangle& rectangle, bool bRedraw = true);


      /**
       * \brief Set the fixed size of this pwidget
       *
       * If nonzero, components of the fixed size attribute override any values
       * computed by a layout generator associated with this pwidget. Note that
       * just setting the fixed size alone is not enough to actually change its
       * size; this is done with a call to \::pointer set_size or a call to \::pointer perform_layout()
       * in the parent pwidget.
       */
      virtual void set_fixed_size(const int_size& fixed_size) { m_fixed_size = fixed_size; }

      /// Return the fixed size (see \::pointer set_fixed_size())
      const int_size& fixed_size() const { return m_fixed_size; }

      // Return the fixed width (see \::pointer set_fixed_size())
      int fixed_width() const { return m_fixed_size.cx(); }
      // Return the fixed height (see \::pointer set_fixed_size())
      int fixed_height() const { return m_fixed_size.cy(); }
      /// Set the fixed width (see \::pointer set_fixed_size())
      void set_fixed_width(int width) { m_fixed_size.cx() = width; }
      /// Set the fixed height (see \::pointer set_fixed_size())
      void set_fixed_height(int height) { m_fixed_size.cy() = height; }

      /// Return whether or not the pwidget is currently visible (assuming all parents are visible)
      virtual bool visible() const;
      virtual bool is_child_visible() const;
      /// Set whether or not the pwidget is currently visible (assuming all parents are visible)
      virtual void set_visible(bool bVisible);
      virtual void toggle_visible();

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

      //::collection::count get_child_as_item_count() override;
      
      //item_pointer get_child_as_item(::collection::index iIndex) override;

      item_pointer selected_item() override;

      item_pointer hover_item() override;

      /// Return the list of pwidgetChild widgets of the current pwidget
      const ::pointer_array<Widget>& children() const { return m_children; }

      /**
       * \brief Add a pwidgetChild pwidget to the current pwidget at
       * the specified iIndex.
       *
       * This function almost never needs to be called by hand,
       * since the constructor of \::pointer Widget automatically
       * adds the current pwidget to its parent
       */
      virtual void insert_child_at(::collection::index iIndex, Widget* pwidget);

      /// Convenience function which appends a pwidget at the end
      void add_child(Widget* pwidget);

      /// Remove a pwidgetChild pwidget by iIndex
      void erase_child_at(::collection::index iIndex);

      /// Remove a pwidgetChild pwidget by value
      void erase_child(Widget* pwidget);

      void to_top();

      virtual void destroy_window();

      virtual void on_destroy_window();

      /// Retrieves the pwidgetChild at the specific position
      const Widget* child_at(::collection::index iIndex) const { return m_children[(size_t)iIndex]; }

      /// Retrieves the pwidgetChild at the specific position
      Widget* child_at(::collection::index iIndex) { return m_children[(size_t)iIndex]; }

      /// Returns the iIndex of a specific pwidgetChild or -1 if not found
      int child_index(Widget* pwidget) const;

      /// Variadic shorthand notation to construct and add a pwidgetChild pwidget
      template<typename WidgetClass, typename... Args>
      ::pointer < WidgetClass>  add(const Args&... args) {
         return __allocate WidgetClass(this, args...);
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
      virtual void request_focus();
      /// Request to loose focus
      virtual void kill_focus();

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
       * See \::pointer nanoui::Widget::m_icon_extra_scale.
       */
      float icon_extra_scale() const { return m_icon_extra_scale; }

      /**
       * Sets the amount of extra scaling applied to *icon* fonts.
       * See \::pointer nanoui::Widget::m_icon_extra_scale.
       */
      void set_icon_extra_scale(float scale) { m_icon_extra_scale = scale; }

      /// Return a pointer to the cursor of the pwidget
      Cursor cursor() const { return m_cursor; }
      /// Set the cursor of the pwidget
      void set_cursor(Cursor cursor) { m_cursor = cursor; }

      /// Check if the pwidget contains a certain position
      bool contains(const int_point& p) const;

      /// Determine the pwidget located at the given position value (recursive)
      Widget* find_widget(const int_point& p);
      const Widget* find_widget(const int_point& p) const;

      /// Handle a mouse button happening (default implementation: propagate to children)
      virtual bool mouse_button_event(const int_point& p, ::user::e_mouse emouse, bool down, bool bDoubleClick, const ::user::e_key& ekeyModifiers);

      /// Handle a mouse motion happening (default implementation: propagate to children)
      virtual bool mouse_motion_event(const int_point& p, const int_size& rel, bool bDown, const ::user::e_key& ekeyModifiers);

      /// Handle a mouse drag happening (default implementation: do nothing)
      // virtual bool mouse_drag_event(const int_point& p, const int_size& rel, const ::user::e_key& ekeyModifiers);

      /// Handle a mouse enter/leave happening (default implementation: record this fact, but do nothing)
      virtual bool mouse_enter_event(const int_point& p, bool enter, const ::user::e_key& ekeyModifiers);

      virtual void set_mouse_capture();

      virtual void release_mouse_capture();

      /// Handle a mouse scroll happening (default implementation: propagate to children)
      virtual bool scroll_event(const int_point& p, const float_size& rel);

      /// Handle a focus change happening (default implementation: record the focus status, but do nothing)
      virtual bool focus_event(bool focused);

      /// Handle a keyboard happening (default implementation: do nothing)
      virtual bool keyboard_event(::user::enum_key ekey, int scancode, int action, const ::user::e_key& ekeyModifiers, const ::scoped_string & scopedstrText);

      /// Handle text input (UTF-32 format) (default implementation: do nothing)
      virtual bool keyboard_character_event(unsigned int codepoint);

      virtual bool need_to_draw(::nano2d::context * pcontext);

      virtual void on_begin_draw(::nano2d::context * pcontext);

      /// Compute the preferred size of the pwidget
      virtual int_size preferred_size(::nano2d::context * pcontext, bool bRecalcTextSize = true);


      virtual void set_need_layout();


      /// Invoke the associated layout generator to properly place pwidgetChild widgets, if any
      virtual void perform_layout(::nano2d::context * pcontext, bool bRecalcTextSize = true);


      /// Draw the pwidget (and all pwidgetChild widgets)
      virtual void call_draw(::nano2d::context * pcontext);


      /// Draw the pwidget (and all pwidgetChild widgets)
      virtual void draw(::nano2d::context * pcontext);

      //protected:
         /// Free all resources used by the pwidget and any children
      ~Widget() override;

      /**
       * Convenience definition for subclasses to get the full icon scale for this
       * class of Widget.  It simple returns the value
       * ``m_ptheme->m_fIconScale * this->m_icon_extra_scale``.
       *
       * \remark
       *     See also: \::pointer nanoui::Theme::m_fIconScale and
       *     \::pointer nanoui::Widget::m_icon_extra_scale.  This tiered scaling
       *     strategy may not be appropriate with fonts other than ``entypo.ttf``.
       */
      float icon_scale() const { return m_ptheme->m_fIconScale * m_icon_extra_scale; }


   };


   template < typename T >
   void defer_destroy_window(::pointer < T > & p)
   {
      
      if(p)
      {
         
         try
         {
            
            p->destroy_window();
            
         }
         catch(...)
         {
            
         }
         
         p.release();
         
      }
      
   }

} // namespace nanoui


