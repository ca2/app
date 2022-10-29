// Created by camilo on 2021-06-08 02:49 BRT <3ThomasBorregaardS�rensen__!!
#pragma once


#include "acme/primitive/primitive/matter.h"
#include "acme/primitive/collection/pointer_array.h"


namespace write_text
{


   class CLASS_DECL_AURA text_out_array :
      virtual public ::matter
   {
   public:


      DECLARE_ARRAY_OF(text_out_array, text_out, text_out);


      text_out_array();
      ~text_out_array() override;
      
      
      virtual ::index hit_test(const ::point_i32& point);


   };


} // namespace write_text



