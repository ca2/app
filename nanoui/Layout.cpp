/*
    src/layout.cpp -- A collection of useful layout managers

    The grid layout was contributed by Christian Schueller.

    NanoGUI was developed by Wenzel Jakob <wenzel.jakob@epfl.ch>.
    The pwidget drawing code is based on the NanoVG demo application
    by Mikko Mononen.

    All rights reserved. Use of this source code is governed by a
    BSD-style license that can be found in the LICENSE.txt file.
*/
#include "framework.h"
#include "Layout.h"
#include "Window.h"
#include "Label.h"
//#include <numeric>

namespace nanoui
{


   BoxLayout::BoxLayout(enum_orientation orientation, enum_alignment alignment,
      int margin, int spacing)
      : m_eorientation(orientation), m_ealignment(alignment), m_iMargin(margin),
      m_iSpacing(spacing) {
   }


   size_i32 BoxLayout::preferred_size(::nano2d::context* pcontext, Widget* pwidget, bool bRecalcTextSize)
   {

      size_i32 size(2 * m_iMargin, 2 * m_iMargin);

      int y_offset = 0;

      const Window* window = dynamic_cast<const Window*>(pwidget);

      if (window && window->title().has_char()) 
      {

         if (m_eorientation == e_orientation_vertical)
         {

            size[1] += pwidget->theme()->m_iWindowHeaderHeight - m_iMargin / 2;

         }
         else
         {

            y_offset = pwidget->theme()->m_iWindowHeaderHeight;

         }

      }

      bool bFirst = true;

      auto iAxisIndex1 = index_of(m_eorientation);

      auto iAxisIndex2 = orthogonal2_index_of(m_eorientation);

      for (auto pwidgetChild : pwidget->children())
      {

         if (!pwidgetChild->visible())
         {

            continue;

         }

         if (bFirst)
         {

            bFirst = false;

         }
         else
         {

            size[iAxisIndex1] += m_iSpacing;

         }

         auto sizeFixed = pwidgetChild->fixed_size();

         size_i32 sizeTarget = sizeFixed.pred_prefer_self_coordinate_if_positive(
            [pwidgetChild, pcontext, bRecalcTextSize]()
            {

               return pwidgetChild->preferred_size(pcontext, bRecalcTextSize);

            });

         size[iAxisIndex1] += sizeTarget[iAxisIndex1];

         size[iAxisIndex2] = ::maximum(size[iAxisIndex2], sizeTarget[iAxisIndex2] + 2 * m_iMargin);

         bFirst = false;

      }

      size[iAxisIndex1] += m_iSpacing;
      
      return size + size_i32(0, y_offset);
      
   }


   void BoxLayout::perform_layout(::nano2d::context* pcontext, Widget* pwidget, bool bRecalcTextSize)
   {

      size_i32 sizeFixed = pwidget->fixed_size();

      auto container_size = sizeFixed.prefer_self_coordinate_if_positive(pwidget->size());

      auto iAxisIndex1 = index_of(m_eorientation);

      auto iAxisIndex2 = orthogonal2_index_of(m_eorientation);

      int position = m_iMargin;

      int y_offset = 0;

      const Window* window = dynamic_cast<const Window*>(pwidget);

      if (window && window->title().has_char())
      {

         if (m_eorientation == e_orientation_vertical)
         {

            position += pwidget->theme()->m_iWindowHeaderHeight - m_iMargin / 2;

         }
         else
         {

            y_offset = pwidget->theme()->m_iWindowHeaderHeight;

            container_size[1] -= y_offset;

         }

      }

      bool bFirst = true;

      for (auto pwidgetChild : pwidget->children())
      {

         if (!pwidgetChild->visible())
         {

            continue;

         }

         if (bFirst)
         {

            bFirst = false;

         }
         else
         {

            position += m_iSpacing;

         }

         auto sizeFixed = pwidgetChild->fixed_size();

         size_i32 sizeTarget = sizeFixed.pred_prefer_self_coordinate_if_positive(
            [pwidgetChild, pcontext, bRecalcTextSize]()
            {

               return pwidgetChild->preferred_size(pcontext, bRecalcTextSize);

            });


         size_i32 pos(0, y_offset);

         pos[iAxisIndex1] = position;

         switch (m_ealignment)
         {
         case e_alignment_minimum:
            pos[iAxisIndex2] += m_iMargin;
            break;
         case e_alignment_middle:
            pos[iAxisIndex2] += (container_size[iAxisIndex2] - sizeTarget[iAxisIndex2]) / 2;
            break;
         case e_alignment_maximum:
            pos[iAxisIndex2] += container_size[iAxisIndex2] - sizeTarget[iAxisIndex2] - m_iMargin * 2;
            break;
         case e_alignment_fill:
            pos[iAxisIndex2] += m_iMargin;
            sizeTarget[iAxisIndex2] = sizeFixed[iAxisIndex2] ? sizeFixed[iAxisIndex2] : (container_size[iAxisIndex2] - m_iMargin * 2);
            break;
         }

         pwidgetChild->set_position(pos);

         pwidgetChild->set_size(sizeTarget);

         pwidgetChild->perform_layout(pcontext);

         position += sizeTarget[iAxisIndex1];

      }

   }


   size_i32 GroupLayout::preferred_size(::nano2d::context* pcontext, Widget* pwidget, bool bRecalcTextSize)
   {

      int height = m_iMargin, width = 2 * m_iMargin;

      const Window* window = dynamic_cast<const Window*>(pwidget);
      if (window && window->title().has_char())
         height += pwidget->theme()->m_iWindowHeaderHeight - m_iMargin / 2;

      bool bFirst = true, indent = false;

      for (auto pwidgetChild : pwidget->children())
      {

         if (!pwidgetChild->visible())
         {

            continue;

         }

         ::pointer <Label> plabel = pwidgetChild;

         if (!bFirst)
         {

            height += !plabel ? m_iSpacing : m_group_spacing;

         }

         bFirst = false;

         auto sizeFixed = pwidgetChild->fixed_size();

         ::size_i32 sizeTarget = sizeFixed.pred_prefer_self_coordinate_if_positive(
            [pwidgetChild, pcontext, bRecalcTextSize]()
            {

               return pwidgetChild->preferred_size(pcontext, bRecalcTextSize);

            });


         bool indent_cur = indent && !plabel;

         height += sizeTarget.cy();

         width = ::maximum(width, sizeTarget.cx() + 2 * m_iMargin + (indent_cur ? m_group_indent : 0));

         if (plabel)
         {

            indent = plabel->caption().has_char();

         }

      }

      height += m_iMargin;

      return size_i32(width, height);

   }


   void GroupLayout::perform_layout(::nano2d::context* pcontext, Widget* pwidget, bool bRecalcTextSize)
   {

      int height = m_iMargin;

      int available_width = (pwidget->fixed_width() ? pwidget->fixed_width() : pwidget->width()) - 2 * m_iMargin;

      const Window* window = dynamic_cast<const Window*>(pwidget);

      if (window && window->title().has_char())
      {

         height += pwidget->theme()->m_iWindowHeaderHeight - m_iMargin / 2;

      }

      bool bFirst = true;

      bool indent = false;

      for (auto pwidgetChild : pwidget->children())
      {

         if (!pwidgetChild->visible())
         {

            continue;

         }

         ::pointer < Label > plabel = pwidgetChild;

         if (!bFirst)
         {

            height += (!plabel) ? m_iSpacing : m_group_spacing;

         }

         bFirst = false;

         bool indent_cur = indent && !plabel;

         auto sizeFixed = pwidgetChild->fixed_size();

         size_i32 sizeTarget = sizeFixed.pred_prefer_self_coordinate_if_positive(
            [&]()
            {

               return size_i32(available_width - (indent_cur ? m_group_indent : 0),
               pwidgetChild->preferred_size(pcontext, bRecalcTextSize).cy());

            });

         pwidgetChild->set_position(point_i32(m_iMargin + (indent_cur ? m_group_indent : 0), height));

         pwidgetChild->set_size(sizeTarget);

         pwidgetChild->perform_layout(pcontext);

         height += sizeTarget.cy();

         if (plabel)
         {

            indent = plabel->caption().has_char();

         }

      }

   }


   size_i32 GridLayout::preferred_size(::nano2d::context* pcontext, Widget* pwidget, bool bRecalcTextSize)
   {

      /* Compute minimum row / column sizes */
      ::i32_array grid[2];

      compute_layout(pcontext, pwidget, grid, bRecalcTextSize);

      sequence2_i32 size(
         2 * m_iMargin + grid[0].get_sum()
         + ::maximum((::i32) grid[0].size() - 1, 0) * m_sizeSpacing[0],
         2 * m_iMargin + grid[1].get_sum()
         + ::maximum((::i32) grid[1].size() - 1, 0) * m_sizeSpacing[1]
      );

      const Window* window = dynamic_cast<const Window*>(pwidget);

      if (window && window->title().has_char())
      {

         size[1] += pwidget->theme()->m_iWindowHeaderHeight - m_iMargin / 2;

      }

      return size;

   }


   void GridLayout::compute_layout(::nano2d::context* pcontext, Widget* pwidget, ::i32_array * grid, bool bRecalcTextSize) const
   {

      auto iAxisIndex1 = index_of(m_eorientation);

      auto iAxisIndex2 = orthogonal2_index_of(m_eorientation);

      auto iChildrenCount = pwidget->children().size();

      ::count iVisibleChildrenCount = 0;

      for (auto pwidgetChild : pwidget->children())
      {

         iVisibleChildrenCount += pwidgetChild->visible() ? 1 : 0;

      }

      sequence2_i32 dim;

      dim[iAxisIndex1] = m_resolution;

      dim[iAxisIndex2] = (::i32)((iVisibleChildrenCount + m_resolution - 1) / m_resolution);

      grid[iAxisIndex1].clear(); grid[iAxisIndex1].resize(dim[iAxisIndex1], 0);

      grid[iAxisIndex2].clear(); grid[iAxisIndex2].resize(dim[iAxisIndex2], 0);

      ::index iChildIndex = 0;

      for (int i2 = 0; i2 < dim[iAxisIndex2]; i2++)
      {

         for (int i1 = 0; i1 < dim[iAxisIndex1]; i1++)
         {

            Widget* pwidgetChild = nullptr;

            do
            {

               if (iChildIndex >= iChildrenCount)
               {

                  return;

               }

               pwidgetChild = pwidget->children()[iChildIndex++];

            } while (!pwidgetChild->visible());

            auto sizeFixed = pwidgetChild->fixed_size();

            size_i32 sizeTarget = sizeFixed.pred_prefer_self_coordinate_if_positive(
               [&]()
               {

                  auto sizePreferred = pwidgetChild->preferred_size(pcontext, bRecalcTextSize);

                  return sizePreferred;

               });



            /*if (sizeFixed.is_set())
            {

               sizeTarget = sizeFixed;

            }
            else
            {

               

               sizeTarget = sizePreferred;

            }*/

            grid[iAxisIndex1][i1] = ::maximum(grid[iAxisIndex1][i1], sizeTarget[iAxisIndex1]);

            grid[iAxisIndex2][i2] = ::maximum(grid[iAxisIndex2][i2], sizeTarget[iAxisIndex2]);

         }

      }

   }


   void GridLayout::perform_layout(::nano2d::context* pcontext, Widget* pwidget, bool bRecalcTextSize)
   {

      auto sizeFixed = pwidget->fixed_size();

      auto container_size = sizeFixed.prefer_self_coordinate_if_set(pwidget->size());

      /* Compute minimum row / column sizes */
      ::i32_array grid[2];

      compute_layout(pcontext, pwidget, grid, bRecalcTextSize);

      int dim[2] = { (int)grid[0].size(), (int)grid[1].size() };

      size_i32 sizeExtra;

      const Window* window = dynamic_cast<const Window*>(pwidget);

      if (window && window->title().has_char())
         sizeExtra[1] += pwidget->theme()->m_iWindowHeaderHeight - m_iMargin / 2;

      /* Strech to size provided by \pwidgetChild pwidget */
      for (int i = 0; i < 2; i++) {
         int grid_size = 2 * m_iMargin + sizeExtra[i];
         for (int s : grid[i]) {
            grid_size += s;
            if (i + 1 < dim[i])
               grid_size += m_sizeSpacing[i];
         }

         if (grid_size < container_size[i]) {
            /* Re-distribute remaining space evenly */
            int gap = container_size[i] - grid_size;
            int g = gap / dim[i];
            int rest = gap - g * dim[i];
            for (int j = 0; j < dim[i]; ++j)
               grid[i][j] += g;
            for (int j = 0; rest > 0 && j < dim[i]; --rest, ++j)
               grid[i][j] += 1;
         }
      }

      auto iAxisIndex1 = ::index_of(m_eorientation);

      auto iAxisIndex2 = ::orthogonal2_index_of(m_eorientation);

      point_i32 start = sizeExtra + ::size_i32(m_iMargin, m_iMargin);

      auto iChildrenCount = pwidget->children().size();

      ::index iChildIndex = 0;

      sequence2_i32 pos = start;

      for (int i2 = 0; i2 < dim[iAxisIndex2]; i2++)
      {

         pos[iAxisIndex1] = start[iAxisIndex1];

         for (int i1 = 0; i1 < dim[iAxisIndex1]; i1++)
         {

            Widget* pwidgetChild = nullptr;

            do
            {

               if (iChildIndex >= iChildrenCount)
               {

                  return;

               }

               pwidgetChild = pwidget->children()[iChildIndex++];

            } while (!pwidgetChild->visible());

            auto sizeFixed = pwidgetChild->fixed_size();

            size_i32 sizeTarget = sizeFixed.pred_prefer_self_coordinate_if_positive(
               [pwidgetChild, pcontext, bRecalcTextSize]()
               {

                  return pwidgetChild->preferred_size(pcontext, bRecalcTextSize);

               });


            sequence2_i32 item_pos(pos);
            for (int j = 0; j < 2; j++) {
               int iAxisIndex = (iAxisIndex1 + j) % 2;
               int item = j == 0 ? i1 : i2;
               enum_alignment align = alignment(iAxisIndex, item);

               switch (align) {
               case e_alignment_minimum:
                  break;
               case e_alignment_middle:
                  item_pos[iAxisIndex] += (grid[iAxisIndex][item] - sizeTarget[iAxisIndex]) / 2;
                  break;
               case e_alignment_maximum:
                  item_pos[iAxisIndex] += grid[iAxisIndex][item] - sizeTarget[iAxisIndex];
                  break;
               case e_alignment_fill:
                  sizeTarget[iAxisIndex] = sizeFixed[iAxisIndex] ? sizeFixed[iAxisIndex] : grid[iAxisIndex][item];
                  break;
               }
            }
            pwidgetChild->set_position(item_pos);
            pwidgetChild->set_size(sizeTarget);
            pwidgetChild->perform_layout(pcontext, bRecalcTextSize);
            pos[iAxisIndex1] += grid[iAxisIndex1][i1] + m_sizeSpacing[iAxisIndex1];
         }
         pos[iAxisIndex2] += grid[iAxisIndex2][i2] + m_sizeSpacing[iAxisIndex2];
      }
   }

   AdvancedGridLayout::AdvancedGridLayout(const ::i32_array& cols, const ::i32_array& rows, int margin)
      : m_cols(cols), m_rows(rows), m_iMargin(margin) {
      m_col_stretch.resize(m_cols.size(), 0);
      m_row_stretch.resize(m_rows.size(), 0);
   }

   
   size_i32 AdvancedGridLayout::preferred_size(::nano2d::context* pcontext, Widget* pwidget, bool bRecalcTextSize)
   {

      /* Compute minimum row / column sizes */
      ::i32_array grid[2];

      compute_layout(pcontext, pwidget, grid);

      size_i32 size(grid[0].get_sum(), grid[1].get_sum());

      size_i32 sizeExtra(2 * m_iMargin, 2 * m_iMargin);

      const Window* window = dynamic_cast<const Window*>(pwidget);

      if (window && window->title().has_char())
      {

         sizeExtra[1] += pwidget->theme()->m_iWindowHeaderHeight - m_iMargin / 2;

      }

      return size + sizeExtra;

   }


   void AdvancedGridLayout::perform_layout(::nano2d::context* pcontext, Widget* pwidget, bool bRecalcTextSize)
   {

      ::i32_array grid[2];
      compute_layout(pcontext, pwidget, grid);

      grid[0].insert_at(0, m_iMargin);
      const Window* window = dynamic_cast<const Window*>(pwidget);
      if (window && window->title().has_char())
         grid[1].insert_at(0, pwidget->theme()->m_iWindowHeaderHeight + m_iMargin / 2);
      else
         grid[1].insert_at(0, m_iMargin);

      for (int iAxisIndex = 0; iAxisIndex < 2; ++iAxisIndex)
      {

         for (::index i = 1; i < grid[iAxisIndex].size(); ++i)
         {

            grid[iAxisIndex][i] += grid[iAxisIndex][i - 1];

         }

         for (Widget* pwidgetChild : pwidget->children())
         {

            if (!pwidgetChild->visible() || dynamic_cast<const Window*>(pwidgetChild) != nullptr)
            {

               continue;

            }

            Anchor anchor = this->anchor(pwidgetChild);

            int item_pos = grid[iAxisIndex][anchor.pos[iAxisIndex]];

            int cell_size = grid[iAxisIndex][anchor.pos[iAxisIndex] + anchor.size[iAxisIndex]] - item_pos;

            ::i32 sizeTarget;

            auto sizeFixed = pwidgetChild->fixed_size()[iAxisIndex];

            if (sizeFixed > 0)
            {

               sizeTarget = sizeFixed;

            }
            else
            {

               sizeTarget = pwidgetChild->preferred_size(pcontext, bRecalcTextSize)[iAxisIndex];

            }

            switch (anchor.align[iAxisIndex])
            {
            case e_alignment_minimum:
               break;
            case e_alignment_middle:
               item_pos += (cell_size - sizeTarget) / 2;
               break;
            case e_alignment_maximum:
               item_pos += cell_size - sizeTarget;
               break;
            case e_alignment_fill:
               sizeTarget = sizeFixed ? sizeFixed : cell_size;
               break;
            }

            auto pos = pwidgetChild->position();

            auto size = pwidgetChild->size();

            pos[iAxisIndex] = item_pos;

            size[iAxisIndex] = sizeTarget;

            pwidgetChild->set_position(pos);

            pwidgetChild->set_size(size);

            pwidgetChild->perform_layout(pcontext);

         }

      }

   }

   void AdvancedGridLayout::compute_layout(::nano2d::context* pcontext, Widget* pwidget, ::i32_array* _grid)
   {

      sequence2_i32 fs_w = pwidget->fixed_size();
      sequence2_i32 container_size(
         fs_w[0] ? fs_w[0] : pwidget->width(),
         fs_w[1] ? fs_w[1] : pwidget->height()
      );

      size_i32 extra(2 * m_iMargin, 2 * m_iMargin);
      Window* window = dynamic_cast<Window*>(pwidget);
      if (window && window->title().has_char())
         extra[1] += pwidget->theme()->m_iWindowHeaderHeight - m_iMargin / 2;

      container_size -= extra;

      for (int iAxisIndex = 0; iAxisIndex < 2; ++iAxisIndex) {
         ::i32_array& grid = _grid[iAxisIndex];
         ::i32_array& sizes = iAxisIndex == 0 ? m_cols : m_rows;
         ::f32_array& stretch = iAxisIndex == 0 ? m_col_stretch : m_row_stretch;
         grid = sizes;

         for (int phase = 0; phase < 2; ++phase) {
            for (auto pair : m_anchor) {
               Widget* pwidgetChild = pair.m_element1;
               if (!pwidgetChild->visible() || dynamic_cast<const Window*>(pwidgetChild) != nullptr)
                  continue;
               Anchor& anchor = pair.m_element2;
               if ((anchor.size[iAxisIndex] == 1) != (phase == 0))
                  continue;

               i32 sizeTarget;

               auto sizeFixed = pwidgetChild->fixed_size()[iAxisIndex];

               if (sizeFixed > 0)
               {

                  sizeTarget = sizeFixed;

               }
               else
               {

                  sizeTarget = pwidgetChild->preferred_size(pcontext)[iAxisIndex];

               }

               if (anchor.pos[iAxisIndex] + anchor.size[iAxisIndex] > (int)grid.size())
                  throw std::runtime_error(
                     "Advanced grid layout: pwidget is out of bounds: " +
                     (::string)anchor);

               int current_size = 0;
               float total_stretch = 0;
               for (int i = anchor.pos[iAxisIndex];
                  i < anchor.pos[iAxisIndex] + anchor.size[iAxisIndex]; ++i) {
                  if (sizes[i] == 0 && anchor.size[iAxisIndex] == 1)
                     grid[i] = ::maximum(grid[i], sizeTarget);
                  current_size += grid[i];
                  total_stretch += stretch[i];
               }
               if (sizeTarget <= current_size)
                  continue;
               if (total_stretch == 0)
                  throw std::runtime_error(
                     "Advanced grid layout: no space to place pwidget: " +
                     (::string)anchor);
               float amt = (sizeTarget - current_size) / total_stretch;
               for (int i = anchor.pos[iAxisIndex];
                  i < anchor.pos[iAxisIndex] + anchor.size[iAxisIndex]; ++i)
                  grid[i] += (int)::round(amt * stretch[i]);
            }
         }

         auto current_size = grid.get_sum();

         float total_stretch = stretch.get_sum();

         if (current_size >= container_size[iAxisIndex] || total_stretch == 0)
         {

            continue;

         }

         float amt = (container_size[iAxisIndex] - current_size) / total_stretch;

         for (::index i = 0; i < grid.size(); ++i)
         {

            grid[i] += (int)::round(amt * stretch[i]);

         }

      }

   }


} // namespace nanoui


