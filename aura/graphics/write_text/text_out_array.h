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
      ::i32_rectangle m_rectangleLast;
      ::e_align       m_ealignLast;
      ::enum_text_wrap m_etextwrapLast;
      bool            m_bHasLayoutContext;


      DECLARE_ARRAY_OF(text_out_array, text_out, text_out);


      text_out_array();
      ~text_out_array() override;
      
      
      virtual ::collection::index hit_test(const ::i32_point & point, ::user::e_zorder ezorder);


      virtual bool is_updated(const ::scoped_string & str, void * pOsData) const;
      virtual bool is_updated(const ::scoped_string & str, void * pOsData,
         const ::i32_rectangle & rectangle, const ::e_align & ealign,
         const ::enum_text_wrap & etextwrap) const;


   };


} // namespace write_text



