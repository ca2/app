// Created by camilo on 2021-06-08 02:49 BRT <3ThomasBorregaardSorensen__!!
#pragma once


//#include "acme/prototype/collection/pointer_array.h"
//#include "acme/prototype/geometry2d/_geometry2d.h"
//#include "acme/prototype/prototype/matter.h"


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
      
      
      virtual ::collection::index hit_test(const ::int_point & point, ::user::e_zorder ezorder);


      virtual bool is_updated(const ::scoped_string & str, void * pOsData) const;


   };


} // namespace write_text



