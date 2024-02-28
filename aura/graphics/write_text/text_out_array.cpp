// Created by camilo on 2021-06-08 02:50 BRT <3ThomasBorregaardSorensen__!!
#include "framework.h"
#include "text_out_array.h"
#include "text_out.h"



namespace write_text
{


   text_out_array::text_out_array()
   {

      m_pLastOsData = nullptr;

   }


   text_out_array::~text_out_array()
   {

   }


   ::index text_out_array::hit_test(const ::point_i32 & point, ::user::e_zorder ezorder)
   {

      ::index iFound = -1;

      for (::index iItem = 0; iItem < this->text_out_count(); iItem++)
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


} // namespace write_text



