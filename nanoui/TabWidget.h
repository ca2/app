/*
    nanoui/tabwidget.h -- Widget for organizing multiple
    sub-widgets into tabs

    NanoGUI was developed by Wenzel Jakob <wenzel.jakob@epfl.ch>.
    The pwidget drawing code is based on the NanoVG demo application
    by Mikko Mononen.

    All rights reserved. Use of this source code is governed by a
    BSD-style license that can be found in the LICENSE.txt file.
*/
/** \file */
#pragma once


#include "Widget.h"
#include "acme/primitive/collection/int_map.h"
//#include <functional>
//#include <unordered_map>

namespace nanoui
{


   /**
    * \class TabWidgetBase tabwidget.h nanoui/tabwidget.h
    *
    * \brief Basic implementation of a tab pwidget with (optionally) draggable and
    * closeable tabs and popup menus. No rendering of the content is done---for an
    * example implementation, refer to \ref TabWidget.
    */
   class CLASS_DECL_NANOUI TabWidgetBase :
      public Widget
   {
   public:


      ::string                                  m_font;
      ::string_array                            m_straTabCaptions;
      ::index_array                             m_iaTabIds;
      ::i32_array                               m_iaTabOffsets;
      int                                       m_iCloseButtonWidth = 0;
      ::index                                 m_iActiveTab = 0;
      ::index                                 m_iTabDragIndex = -1;
      ::index                                 m_iTabDragMinimum = -1;
      ::index                                 m_iTabDragMaximum = -1;
      ::index                                 m_iTabDragStart = -1;
      ::index                                 m_iTabDragEnd = -1;
      ::index                                 m_iCloseIndex = -1;
      ::index                                 m_iCloseIndexPushed = -1;
      bool                                      m_bTabsDraggable = false;
      bool                                      m_bTabsCloseable = false;
      Popup *                                   m_ppopup = nullptr;
      int                                       m_iTabCounter = 0;
      int                                       m_iPadding = 3;
      ::function<void(::index)>               m_callback;
      ::function<void(::index)>               m_closecallback;
      ::function<Popup* (::index, Screen*)>   m_popupcallback;
      ::color::color                            m_colorBackground;


      /// Construct a memory_new tab pwidget
      TabWidgetBase(Widget* parent, const ::scoped_string& scopedstrFont = "sans-bold");

      /// Return the total number of tabs
      ::count tab_count() const { return (::count)m_straTabCaptions.size(); };

      /// Return the ID of the tab at a given iIndex
      ::index tab_id(::index iIndex) const { return m_iaTabIds[iIndex]; };

      /// Return the iIndex of the tab with a given ID (or throw an exception)
      ::index tab_index(::index iId) const;

      /// Inserts a memory_new tab at the specified position and returns its ID.
      ::index insert_tab(::index iIndex, const ::scoped_string& caption);

      /// Appends a memory_new tab and returns its ID.
      ::index append_tab(const ::scoped_string& caption);

      /// Removes a tab with the specified ID
      virtual void erase_tab(::index iId);

      /// Return the ID of the currently active tab
      ::index selected_id() const { return m_iaTabIds.empty() ? -1 : tab_id(m_iActiveTab); }
      /// Set the ID of the currently active tab
      void set_selected_id(::index iId) { m_iActiveTab = tab_index(iId); update_visibility(); }

      /// Return the iIndex of the currently active tab
      ::index selected_index() const { return m_iActiveTab; }
      /// Set the iIndex of the currently active tab
      void set_selected_index(::index iIndex) { m_iActiveTab = iIndex; update_visibility(); }

      /// Return the caption of the tab with the given ID
      ::string tab_caption(::index iId) const { return m_straTabCaptions[tab_index(iId)]; };
      /// Change the caption of the tab with the given ID
      void set_tab_caption(::index iId, const ::scoped_string& caption) { m_straTabCaptions[tab_index(iId)] = caption; };

      /// Return whether tabs provide a close button
      bool tabs_closeable() const { return m_bTabsCloseable; }
      void set_tabs_closeable(bool value) { m_bTabsCloseable = value; }

      /// Return whether tabs can be dragged to different positions
      bool tabs_draggable() const { return m_bTabsDraggable; }
      void set_tabs_draggable(bool value) { m_bTabsDraggable = value; }

      /// Return the padding between the tab pwidget boundary and pwidgetChild widgets
      int padding() const { return m_iPadding; }
      void set_padding(int value) { m_iPadding = value; }

      /// Set the pwidget's background color (a global property)
      void set_background_color(const ::color::color& colorBackground) {
         m_colorBackground = colorBackground;
      }

      /// Return the pwidget's background color (a global property)
      const ::color::color& colorBackground() const {
         return m_colorBackground;
      }

      /// Callback that is used to notify a listener about tab changes (will be called with the tab ID)
      ::function<void(::index)> callback() const { return m_callback; }
      /// Set a callback that is used to notify a listener about tab changes (will be called with the tab ID)
      void set_callback(const ::function<void(::index)>& callback) { m_callback = callback; }

      /// Callback that is used to notify a listener about tab close events (will be called with the tab ID)
      ::function<void(::index)> close_callback() const { return m_closecallback; }
      /// Set a callback that is used to notify a listener about tab close events (will be called with the tab ID)
      void set_close_callback(const ::function<void(::index)>& close_callback) { m_closecallback = close_callback; }

      /// Callback that is used to notify a listener about popup events (will be called with the tab ID)
      ::function<Popup* (::index, Screen*)> popup_callback() const { return m_popupcallback; }
      /// Set a callback that is used to notify a listener about popup events (will be called with the tab ID)
      void set_popup_callback(const ::function<Popup* (::index, Screen*)>& popup_callback) { m_popupcallback = popup_callback; }

      // Widget implementation
      void perform_layout(::nano2d::context* pcontext, bool bRecalcTextSize = true) override;
      vector2_i32 preferred_size(::nano2d::context* pcontext, bool bRecalcTextSize = true) override;
      
      void draw(::nano2d::context* pcontext) override;

      bool mouse_button_event(const vector2_i32& p, ::user::e_mouse emouse, bool down, bool bDoubleClick, const ::user::e_key& ekeyModifiers) override;
      bool mouse_enter_event(const vector2_i32& p, bool enter, const ::user::e_key& ekeyModifiers) override;
      bool mouse_motion_event(const vector2_i32& p, const vector2_i32& rel, bool bDown, const ::user::e_key& ekeyModifiers) override;

      ::item_pointer hit_test(const vector2_i32 & p, bool test_vertical = true) const;

      virtual void update_visibility();

   };


   /**
    * \class TabWidget tabwidget.h nanoui/tabwidget.h
    *
    * \brief A wrapper around the widgets TabHeader and StackedWidget which hooks
    *        the two classes together.
    *
    * \rst
    *
    * .. warning::
    *
    *    Unlike other widgets, children may **not** be added *directly* to a
    *    TabWidget.  For example, the following code will raise an exception:
    *
    *    .. code-block:: cpp
    *
    *       // `this` might be say a nanoui::Screen instance
    *       Window *window = memory_new Window(this, "Window Title");
    *       TabWidget *tab_widget = window->add<TabWidget>();
    *       // this label would be a direct pwidgetChild of tabWidget,
    *       // which is forbidden, so an exception will be raised
    *       memory_new Label(tab_widget, "Some Label");
    *
    *    Instead, you are expected to be creating tabs and adding widgets to those.
    *
    *    .. code-block:: cpp
    *
    *       // `this` might e.g. be a nanoui::Screen instance
    *       Window *window = memory_new Window(this, "Window Title");
    *       TabWidget *tab_widget = window->add<TabWidget>();
    *       // Create a tab bFirst
    *       Widget *tab = memory_new Widget(tab_widget);
    *       int tab_id = tab_widget->append_tab("Tab Name", tab);
    *       // Add children to the created tabs
    *       tab->set_layout(memory_new GroupLayout());
    *       memory_new Label(tab, "Some Label");
    *
    *    A slightly more involved example of creating a TabWidget can also be found
    *    in :ref:`nanoui_example_1` (search for ``tab_widget`` in the file).
    *
    * \endrst
    */
   class CLASS_DECL_NANOUI TabWidget :
      public TabWidgetBase 
   {
   public:

      ::index_map < Widget*>        m_widgets;
      bool                          m_bEraseChildren = true;


      /// Construct a memory_new tab pwidget
      TabWidget(Widget* parent, const ::scoped_string& font = "sans-bold");

      /// Inserts a memory_new tab at the specified position and returns its ID.
      ::index insert_tab(::index iIndex, const ::scoped_string& caption, Widget* pwidget);

      /// Appends a memory_new tab and returns its ID.
      ::index append_tab(const ::scoped_string& caption, Widget* pwidget);

      /// Removes a tab with the specified ID
      void erase_tab(::index iId) override;

      /// Remove pwidgetChild widgets when the associated tab is closed/erased?
      bool erase_children() const { return m_bEraseChildren; }

      /// Remove pwidgetChild widgets when the associated tab is closed/erased?
      void set_erase_children(bool value) { m_bEraseChildren = value; }

      void perform_layout(::nano2d::context* pcontext, bool bRecalcTextSize = true) override;
      vector2_i32 preferred_size(::nano2d::context* pcontext, bool bRecalcTextSize = true) override;
      void update_visibility() override;


   };



} // namespace nanoui


