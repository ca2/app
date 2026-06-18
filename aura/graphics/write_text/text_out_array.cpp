// Created by camilo on 2021-06-08 02:50 BRT <3ThomasBorregaardSorensen__!!
#include "framework.h"
#include "text_out_array.h"
#include "text_out.h"



namespace write_text
{


   text_out_array::text_out_array()
   {

      m_pLastOsData = nullptr;
      m_ealignLast = e_align_none;
      m_etextwrapLast = e_text_wrap_none;
      m_bHasLayoutContext = false;

   }


   text_out_array::~text_out_array()
   {

   }


   ::collection::index text_out_array::hit_test(const ::i32_point & point, ::user::e_zorder ezorder)
   {

      ::collection::index iFound = -1;

      for (::collection::index iItem = 0; iItem < this->text_out_count(); iItem++)
      {

         auto& ptextout = text_out_at(iItem);

         if (ptextout->hit_test(point))
         {

            iFound = iItem;

            break;

         }

      }

      return iFound;

   }


   bool text_out_array::is_updated(const ::scoped_string & str, void * pOsData) const
   {

      return m_strLast == str && m_pLastOsData == pOsData;

   }


   bool text_out_array::is_updated(const ::scoped_string & str, void * pOsData,
      const ::i32_rectangle & rectangle, const ::e_align & ealign,
      const ::enum_text_wrap & etextwrap) const
   {

      return m_bHasLayoutContext
         && is_updated(str, pOsData)
         && m_rectangleLast == rectangle
         && m_ealignLast == ealign
         && m_etextwrapLast == etextwrap;

   }


} // namespace write_text



