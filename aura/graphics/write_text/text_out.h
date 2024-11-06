#pragma once


#include "text.h"
#include "acme/prototype/geometry2d/rectangle.h"


namespace write_text
{


   class CLASS_DECL_AURA text_out :
      virtual public text
   {
   public:


      double_point                        m_point;
      double_size                         m_size;

      text_out();
      ~text_out() override;


      virtual void offset(const ::double_point & point);
      
      
      virtual ::double_rectangle get_rectangle() const
      { return { m_point, m_size }; }


      virtual bool hit_test(const ::double_point& point);


      virtual bool contains(const ::double_point & point);

      
      virtual void expand_bounding_box(double_point & top_left, double_point &  bottom_right) const
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



