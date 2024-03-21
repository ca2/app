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
      m_pwidgetParent = nullptr;

   }


   in_place_edit::~in_place_edit()
   {

   }


   bool in_place_edit::on_end_edit()
   {

      bool bNeedRedraw = false;

      auto pwidgetParent = m_pwidgetParent;

      auto pwidget = m_pwidget;

      if (m_pwidget.is_set())
      {

         m_pwidget.release();

         bNeedRedraw = true;

      }

      if (m_iClickCount >= 0)
      {

         m_iClickCount = -1;

         bNeedRedraw = true;

      }

      if (::is_set(pwidgetParent))
      {
       
         if (pwidgetParent->m_pinplaceedit == this)
         {

            pwidgetParent->m_pinplaceedit.release();

            bNeedRedraw = true;

         }

      }

      if (pwidget)
      {

         if (pwidget->end_in_place_edit())
         {

            bNeedRedraw = true;

         }

      }

      return bNeedRedraw;

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

      return pmapper->inner_to_outer(m_rectangleInternal, this);

   }


   ::rectangle_f32 in_place_edit::get_edit_rectangle(in_place_edit_mapper* pmapper)
   {

      return get_outer_rectangle(pmapper);

   }


   void in_place_edit::set_edit_payload(const ::payload& payload)
   {


   }


} // namespace nanoui