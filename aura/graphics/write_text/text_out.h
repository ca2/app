#pragma once


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


      virtual bool hit_test(const ::point_f64& point);


   };


} // namespace write_text



