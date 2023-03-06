// Created by camilo on 2021-06-08 02:49 BRT <3ThomasBorregaardS�rensen__!!
#pragma once


//#include "acme/primitive/collection/pointer_array.h"
#include "acme/primitive/geometry2d/_geometry2d.h"
//#include "acme/primitive/primitive/matter.h"


namespace write_text
{


   class CLASS_DECL_AURA text_out_array :
      virtual public ::matter
   {
   public:


      ::string       m_strLast;
      void *         m_pLastOsData;


      DECLARE_ARRAY_OF(text_out_array, text_out, text_out);


      text_out_array();
      ~text_out_array() override;
      
      
      virtual ::index hit_test(const ::point_i32& point);


      virtual bool is_updated(const ::scoped_string & str, void * pOsData) const;


   };


} // namespace write_text



