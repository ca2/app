#pragma once



#include "text.h"


namespace write_text
{


   class CLASS_DECL_AURA text_out :
      virtual public text
   {
   public:


      point_f64                        m_point;
      size_f64                         m_size;

      text_out();
      ~text_out() override;


      virtual void offset(const ::point_f64 & point);


      virtual bool hit_test(const ::point_f64& point);


      virtual bool contains(const ::point_f64 & point);


   };


} // namespace write_text




template < primitive_number NUMBER >
void expand_bounding_box(::rectangle_type < NUMBER > & rectangle, const ::write_text::text_out & textout)
{

   ::expand_bounding_box(rectangle, textout.m_point);
   ::expand_bounding_box(rectangle, textout.m_point + textout.m_size);

}



