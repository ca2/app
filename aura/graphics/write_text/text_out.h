#pragma once


#include "text.h"
#include "acme/prototype/geometry2d/rectangle.h"


namespace write_text
{


   class CLASS_DECL_AURA text_out :
      virtual public text
   {
   public:


      ::f64_point                        m_point;
      ::f64_size                         m_size;

      text_out();
      ~text_out() override;


      virtual void offset(const ::f64_point & point);
      
      
      virtual ::f64_rectangle get_rectangle() const
      { return { m_point, m_size }; }


      virtual bool hit_test(const ::f64_point& point);


      virtual bool contains(const ::f64_point & point);

      
      virtual void expand_bounding_box(::f64_point & top_left, ::f64_point &  bottom_right) const
      {
         
         get_rectangle().expand_bounding_box(top_left, bottom_right);
         
      }
      

   };


} // namespace write_text




template < prototype_number NUMBER >
void expand_bounding_box(::rectangle_type < NUMBER > & rectangle, const ::write_text::text_out & textout)
{

   ::expand_bounding_box(rectangle, textout.m_point);
   ::expand_bounding_box(rectangle, textout.m_point + textout.m_size);

}



