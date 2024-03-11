// Created by camilo on 2024-03-10 22:00 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "in_place_edit.h"
#include "Widget.h"


namespace nanoui
{


   in_place_edit::in_place_edit()
   {

      m_iClickCount = -1;
      m_bEdit = false;

   }


   in_place_edit::~in_place_edit()
   {

   }


   void in_place_edit::on_end_edit()
   {

      auto pwidgetParent = m_pwidgetParent;

      m_pwidgetParent.release();

      auto pwidget = m_pwidget;

      m_pwidget.release();

      if (pwidgetParent)
      {
       
         if (pwidgetParent->m_pinplaceedit == this)
         {

            pwidgetParent->m_pinplaceedit.release();

         }

      }

      if (pwidget)
      {

         pwidget->end_in_place_edit();

      }

   }


   void in_place_edit::set_need_update()
   {


   }


   ::string in_place_edit::get_name_for_editing() const
   {

      return {};

   }


   ::rectangle_f32 in_place_edit::get_outer_rectangle(in_place_edit_mapper* pmapper)
   {

      auto top_left = m_rectangleInternal.top_left();

      auto bottom_right = m_rectangleInternal.bottom_right();

      ::rectangle_f32 rectangleOuter;

      rectangleOuter.top_left() = pmapper->inner_to_outer(top_left, this);

      rectangleOuter.bottom_right() = pmapper->inner_to_outer(bottom_right, this);

      return rectangleOuter;

   }


   void in_place_edit::set_edit_payload(const ::payload& payload)
   {


   }


} // namespace nanoui