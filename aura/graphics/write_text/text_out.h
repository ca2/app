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
      
      
      virtual ::rectangle_f64 get_rectangle() const
      { return { m_point, m_size }; }


      virtual bool hit_test(const ::point_f64& point);


      virtual bool contains(const ::point_f64 & point);

      
      virtual void expand_bounding_box(point_f64 & top_left, point_f64 &  bottom_right) const
      {
         
         get_rectangle().expand_bounding_box(top_left, bottom_right);
         
      }
      

   };


} // namespace write_text




template < primitive_number NUMBER >
void expand_bounding_box(::rectangle_type < NUMBER > & rectangle, const ::write_text::text_out & textout)
{

   ::expand_bounding_box(rectangle, textout.m_point);
   ::expand_bounding_box(rectangle, textout.m_point + textout.m_size);

}



