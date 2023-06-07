/*
    NanoGUI was developed by Wenzel Jakob <wenzel.jakob@epfl.ch>.
    The pwidget drawing code is based on the NanoVG demo application
    by Mikko Mononen.

    All rights reserved. Use of this source code is governed by a
    BSD-style license that can be found in the LICENSE.txt file.
*/
/**
 * \file nanoui/layout.h
 *
 * \brief A collection of useful layout managers.  The \::pointer nanoui::GridLayout
 *        was contributed by Christian Schueller.
 */
#pragma once


#include "_constant.h"
#include "Object.h"
#include "acme/primitive/collection/numeric_array.h"
#include "acme/primitive/geometry2d/size.h"
//#include "acme/primitive/geometry2d/vector.h"


namespace nanoui
{



   /**
    * \class Layout layout.h nanoui/layout.h
    *
    * \brief Basic interface of a layout engine.
    */
   class CLASS_DECL_NANOUI Layout :
      public Object 
   {
   public:

      /// Default destructor (exists for inheritance).
      virtual ~Layout() { }

      /**
       * Performs applies all layout computations for the given pwidget.
       *
       * \param pcontext
       *     The ``NanoVG`` context being used for drawing.
       *
       * \param pwidget
       *     The Widget whose pwidgetChild widgets will be positioned by the layout class..
       */
      virtual void perform_layout(::nano2d::context* pcontext, Widget* pwidget, bool bRecalcTextSize = true) = 0;

      /**
       * Compute the preferred size for a given layout and pwidget
       *
       * \param pcontext
       *     The ``NanoVG`` context being used for drawing.
       *
       * \param pwidget
       *     Widget, whose preferred size should be computed
       *
       * \return
       *     The preferred size, accounting for things such as spacing, padding
       *     for icons, etc.
       */
      virtual size_i32 preferred_size(::nano2d::context* pcontext, Widget* pwidget, bool bRecalcTextSize = true) = 0;
   };

   /**
    * \class BoxLayout layout.h nanoui/layout.h
    *
    * \brief Simple horizontal/vertical box layout
    *
    * This pwidget stacks up a bunch of widgets horizontally or vertically. It adds
    * margins around the entire container and a custom spacing between adjacent
    * widgets.
    */
   class CLASS_DECL_NANOUI BoxLayout : public Layout
   {
   public:

      /// The enum_orientation of this BoxLayout.
      enum_orientation m_eorientation;

      /// The enum_alignment of this BoxLayout.
      enum_alignment m_ealignment;

      /// The margin padding of this BoxLayout.
      int m_iMargin;

      /// The spacing between widgets of this BoxLayout.
      int m_iSpacing;

      /**
       * \brief Construct a box layout which packs widgets in the given \pwidgetChild enum_orientation
       *
       * \param orientation
       *     The enum_orientation this BoxLayout expands along
       *
       * \param alignment
       *     Widget alignment perpendicular to the chosen orientation
       *
       * \param margin
       *     Margin around the layout container
       *
       * \param spacing
       *     Extra spacing placed between widgets
       */
      BoxLayout(enum_orientation orientation, enum_alignment alignment = e_alignment_middle,
         int margin = 0, int spacing = 0);

      /// The enum_orientation this BoxLayout is using.
      enum_orientation orientation() const { return m_eorientation; }

      /// Sets the enum_orientation of this BoxLayout.
      void set_orientation(enum_orientation orientation) { m_eorientation = orientation; }

      /// The enum_alignment of this BoxLayout.
      enum_alignment alignment() const { return m_ealignment; }

      /// Sets the enum_alignment of this BoxLayout.
      void set_alignment(enum_alignment alignment) { m_ealignment = alignment; }

      /// The margin of this BoxLayout.
      int margin() const { return m_iMargin; }

      /// Sets the margin of this BoxLayout.
      void set_margin(int margin) { m_iMargin = margin; }

      /// The spacing this BoxLayout is using to pad in between widgets.
      int spacing() const { return m_iSpacing; }

      /// Sets the spacing of this BoxLayout.
      void set_spacing(int spacing) { m_iSpacing = spacing; }

      /* Implementation of the layout interface */

      /// See \::pointer Layout::preferred_size.
      virtual size_i32 preferred_size(::nano2d::context* pcontext, Widget* pwidget, bool bRecalcTextSize = true) override;

      /// See \::pointer Layout::perform_layout.
      virtual void perform_layout(::nano2d::context* pcontext, Widget* pwidget, bool bRecalcTextSize = true) override;

   };

   /**
    * \class GroupLayout layout.h nanoui/layout.h
    *
    * \brief Special layout for widgets grouped by labels.
    *
    * This pwidget resembles a box layout in that it arranges a set of widgets
    * vertically. All widgets are indented on the horizontal iAxisIndex except for
    * \::pointer Label widgets, which are not indented.
    *
    * This creates a pleasing layout where a number of widgets are grouped
    * under some high-level heading.
    */
   class CLASS_DECL_NANOUI GroupLayout : public Layout {
   public:
      /**
       * Creates a GroupLayout.
       *
       * \param margin
       *     The margin around the widgets added.
       *
       * \param spacing
       *     The spacing between widgets added.
       *
       * \param group_spacing
       *     The spacing between groups (groups are defined by each Label added).
       *
       * \param group_indent
       *     The amount to indent widgets in a group (underneath a Label).
       */
      GroupLayout(int margin = 15, int spacing = 6, int group_spacing = 14,
         int group_indent = 20)
         : m_iMargin(margin), m_iSpacing(spacing), m_group_spacing(group_spacing),
         m_group_indent(group_indent) {}

      /// The margin of this GroupLayout.
      int margin() const { return m_iMargin; }

      /// Sets the margin of this GroupLayout.
      void set_margin(int margin) { m_iMargin = margin; }

      /// The spacing between widgets of this GroupLayout.
      int spacing() const { return m_iSpacing; }

      /// Sets the spacing between widgets of this GroupLayout.
      void set_spacing(int spacing) { m_iSpacing = spacing; }

      /// The indent of widgets in a group (underneath a Label) of this GroupLayout.
      int group_indent() const { return m_group_indent; }

      /// Sets the indent of widgets in a group (underneath a Label) of this GroupLayout.
      void set_group_indent(int group_indent) { m_group_indent = group_indent; }

      /// The spacing between groups of this GroupLayout.
      int group_spacing() const { return m_group_spacing; }

      /// Sets the spacing between groups of this GroupLayout.
      void set_group_spacing(int group_spacing) { m_group_spacing = group_spacing; }

      /* Implementation of the layout interface */

      /// See \::pointer Layout::preferred_size.
      virtual size_i32 preferred_size(::nano2d::context* pcontext, Widget* pwidget, bool bRecalcTextSize = true) override;

      /// See \::pointer Layout::perform_layout.
      virtual void perform_layout(::nano2d::context* pcontext, Widget* pwidget, bool bRecalcTextSize = true) override;

   protected:
      /// The margin of this GroupLayout.
      int m_iMargin;

      /// The spacing between widgets of this GroupLayout.
      int m_iSpacing;

      /// The spacing between groups of this GroupLayout.
      int m_group_spacing;

      /// The indent amount of a group under its defining Label of this GroupLayout.
      int m_group_indent;
   };

   /**
    * \class GridLayout layout.h nanoui/layout.h
    *
    * \brief Grid layout.
    *
    * Widgets are arranged in a grid that has a fixed grid resolution \pwidgetChild resolution
    * along one of the axes. The layout orientation indicates the fixed dimension;
    * widgets are also appended on this iAxisIndex. The spacing between items can be
    * specified per iAxisIndex. The horizontal/vertical alignment can be specified per
    * row and column.
    */
   class CLASS_DECL_NANOUI GridLayout :
      public Layout 
   {
   public:


      /// The enum_orientation of the GridLayout.
      enum_orientation m_eorientation;
      /// The default enum_alignment of the GridLayout.
      enum_alignment m_default_alignment[2];
      /// The actual enum_alignment being used for each column/row
      ::array<enum_alignment> m_ealignment[2];
      /// The number of rows or columns before starting a memory_new one, depending on the enum_orientation.
      int m_resolution;
      /// The spacing used for each dimension.
      size_i32 m_sizeSpacing;
      /// The margin around this GridLayout.
      int m_iMargin;
      /**
       * Create a 2-column grid layout by default.
       *
       * \param orientation
       *     The fixed dimension of this GridLayout.
       *
       * \param resolution
       *     The number of rows or columns in the grid (depending on the enum_orientation).
       *
       * \param alignment
       *     How widgets should be aligned within each grid cell.
       *
       * \param margin
       *     The amount of spacing to add around the border of the grid.
       *
       * \param spacing
       *     The amount of spacing between widgets added to the grid.
       */
      GridLayout(enum_orientation orientation = e_orientation_horizontal, int resolution = 2,
         enum_alignment alignment = e_alignment_middle,
         int margin = 0, int spacing = 0)
         : m_eorientation(orientation), m_resolution(resolution), m_iMargin(margin)
      {
         m_default_alignment[0] = m_default_alignment[1] = alignment;
         m_sizeSpacing = { spacing, spacing };
      }

      /// The enum_orientation of this GridLayout.
      enum_orientation orientation() const { return m_eorientation; }

      /// Sets the enum_orientation of this GridLayout.
      void set_orientation(enum_orientation orientation) {
         m_eorientation = orientation;
      }

      /// The number of rows or columns (depending on the enum_orientation) of this GridLayout.
      int resolution() const { return m_resolution; }
      /// Sets the number of rows or columns (depending on the enum_orientation) of this GridLayout.
      void set_resolution(int resolution) { m_resolution = resolution; }

      /// The spacing at the specified iAxisIndex (row or column number, depending on the enum_orientation).
      int spacing(int iAxisIndex) const { return m_sizeSpacing[iAxisIndex]; }
      /// Sets the spacing for a specific iAxisIndex.
      void set_spacing(int iAxisIndex, int spacing) { m_sizeSpacing[iAxisIndex] = spacing; }
      /// Sets the spacing for all axes.
      void set_spacing(int spacing) { m_sizeSpacing[0] = m_sizeSpacing[1] = spacing; }

      /// The margin around this GridLayout.
      int margin() const { return m_iMargin; }
      /// Sets the margin of this GridLayout.
      void set_margin(int margin) { m_iMargin = margin; }

      /**
       * The enum_alignment of the specified iAxisIndex (row or column number, depending on
       * the enum_orientation) at the specified index of that row or column.
       */
      enum_alignment alignment(int iAxisIndex, int item) const {
         if (item < (int)m_ealignment[iAxisIndex].size())
            return m_ealignment[iAxisIndex][item];
         else
            return m_default_alignment[iAxisIndex];
      }

      /// Sets the enum_alignment of the columns.
      void set_col_alignment(enum_alignment value) { m_default_alignment[0] = value; }

      /// Sets the enum_alignment of the rows.
      void set_row_alignment(enum_alignment value) { m_default_alignment[1] = value; }

      /// Use this to set variable enum_alignment for columns.
      void set_col_alignment(const ::array<enum_alignment>& value) { m_ealignment[0] = value; }

      /// Use this to set variable enum_alignment for rows.
      void set_row_alignment(const ::array<enum_alignment>& value) { m_ealignment[1] = value; }

      /* Implementation of the layout interface */
      /// See \::pointer Layout::preferred_size.
      virtual size_i32 preferred_size(::nano2d::context* pcontext, Widget* pwidget, bool bRecalcTextSize = true) override;

      /// See \::pointer Layout::perform_layout.
      virtual void perform_layout(::nano2d::context* pcontext, Widget* pwidget, bool bRecalcTextSize = true) override;


      // Compute the maximum row and column sizes
      void compute_layout(::nano2d::context* pcontext, Widget* pwidget, ::i32_array * grid, bool bRecalcTextSize) const;

   };

   /**
    * \class AdvancedGridLayout layout.h nanoui/layout.h
    *
    * \brief Advanced Grid layout.
    *
    * The is a fancier grid layout with support for items that span multiple rows
    * or columns, and per-pwidget alignment flags. Each row and column additionally
    * stores a stretch factor that controls how additional space is redistributed.
    * The downside of this flexibility is that a layout anchor data structure must
    * be provided for each pwidget.
    *
    * An example:
    *
    * \rst
    * .. code-block:: cpp
    *
    *    using Anchor = AdvancedGridLayout::Anchor;
    *    Label *label = memory_new Label(window, "A label");
    *    // Add a centered label at grid position (1, 5), which spans two horizontal cells
    *    layout->set_anchor(label, Anchor(1, 5, 2, 1, e_alignment_middle, e_alignment_middle));
    *
    * \endrst
    *
    * The grid is initialized with user-specified column and row size vectors
    * (which can be expanded later on if desired). If a size value of zero is
    * specified for a column or row, the size is set to the maximum preferred size
    * of any widgets contained in the same row or column. Any remaining space is
    * redistributed according to the row and column stretch factors.
    *
    * The high level usage somewhat resembles the classic HIG layout:
    *
    * - https://web.archive.org/web/20070813221705/http://www.autel.cz/dmi/tutorial.html
    * - https://github.com/jaapgeurts/higlayout
    */
   class CLASS_DECL_NANOUI AdvancedGridLayout : public Layout {
   public:
      /**
       * \struct Anchor layout.h nanoui/layout.h
       *
       * \brief Helper struct to coordinate anchor points for the layout.
       */
      struct Anchor {
         uint8_t pos[2];    ///< The ``(x, y)`` position.
         uint8_t size[2];   ///< The ``(x, y)`` size.
         enum_alignment align[2];///< The ``(x, y)`` enum_alignment.

         /// Creates a ``0`` Anchor.
         Anchor() { }

         /// Create an Anchor at position ``(x, y)`` with specified enum_alignment.
         Anchor(int x, int y, enum_alignment horiz = e_alignment_fill,
            enum_alignment vert = e_alignment_fill) {
            pos[0] = (uint8_t)x; pos[1] = (uint8_t)y;
            size[0] = size[1] = 1;
            align[0] = horiz; align[1] = vert;
         }

         /// Create an Anchor at position ``(x, y)`` of size ``(pwidgetChild, h)`` with specified alignments.
         Anchor(int x, int y, int pwidgetChild, int h,
            enum_alignment horiz = e_alignment_fill,
            enum_alignment vert = e_alignment_fill) {
            pos[0] = (uint8_t)x; pos[1] = (uint8_t)y;
            size[0] = (uint8_t)pwidgetChild; size[1] = (uint8_t)h;
            align[0] = horiz; align[1] = vert;
         }

         /// Allows for printing out Anchor position, size, and alignment.
         operator ::string() const {
            char buf[80];
            std::snprintf(buf, 80, "Format[pos=(%i, %i), size=(%i, %i), align=(%i, %i)]",
               pos[0], pos[1], size[0], size[1], (int)align[0], (int)align[1]);
            return buf;
         }
      };


      /// The columns of this AdvancedGridLayout.
      ::i32_array m_cols;

      /// The rows of this AdvancedGridLayout.
      ::i32_array m_rows;

      /// The stretch for each column of this AdvancedGridLayout.
      ::f32_array m_col_stretch;

      /// The stretch for each row of this AdvancedGridLayout.
      ::f32_array m_row_stretch;

      /// The mapping of widgets to their specified anchor points.
      ::map<Widget*, Anchor> m_anchor;

      /// The margin around this AdvancedGridLayout.
      int m_iMargin;


      /// Creates an AdvancedGridLayout with specified columns, rows, and margin.
      AdvancedGridLayout(const ::i32_array& cols = {}, const ::i32_array& rows = {}, int margin = 0);

      /// The margin of this AdvancedGridLayout.
      int margin() const { return m_iMargin; }
      /// Sets the margin of this AdvancedGridLayout.
      void set_margin(int margin) { m_iMargin = margin; }

      /// Return the number of cols
      int col_count() const { return (int)m_cols.size(); }

      /// Return the number of rows
      int row_count() const { return (int)m_rows.size(); }

      /// Append a row of the given size (and stretch factor)
      void append_row(int size, float stretch = 0.f) { m_rows.add(size); m_row_stretch.add(stretch); };

      /// Append a column of the given size (and stretch factor)
      void append_col(int size, float stretch = 0.f) { m_cols.add(size); m_col_stretch.add(stretch); };

      /// Set the stretch factor of a given row
      void set_row_stretch(int index, float stretch) { m_row_stretch.element_at(index) = stretch; }

      /// Set the stretch factor of a given column
      void set_col_stretch(int index, float stretch) { m_col_stretch.element_at(index) = stretch; }

      /// Specify the anchor data structure for a given pwidget
      void set_anchor(Widget* pwidget, const Anchor& anchor) { m_anchor[pwidget] = anchor; }

      /// Retrieve the anchor data structure for a given pwidget
      const Anchor & anchor(Widget* pwidget) const 
      {
         
         auto p = m_anchor.plookup(pwidget);

         if (m_anchor.is_end(p))
         {

            throw std::runtime_error("Widget was not registered with the grid layout!");

         }

         return p->element2();

      }


      /* Implementation of the layout interface */

      /// See \::pointer Layout::preferred_size.
      virtual size_i32 preferred_size(::nano2d::context* pcontext, Widget* pwidget, bool bRecalcTextSize = true) override;

      /// See \::pointer Layout::perform_layout.
      virtual void perform_layout(::nano2d::context* pcontext, Widget* pwidget, bool bRecalcTextSize = true) override;

      // Compute the maximum row and column sizes
      void compute_layout(::nano2d::context* pcontext, Widget* pwidget, ::i32_array* grid);

   };



} // namespace nanoui


