// Created by camilo on 2021-06-08 02:50 BRT <3ThomasBorregaardSørensen__!!
#include "framework.h"


namespace write_text
{


   text_out_array::text_out_array()
   {

   }

   text_out_array::~text_out_array()
   {

   }

   ::index text_out_array::hit_test(const ::point_i32& point)
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


} // namespace write_text



