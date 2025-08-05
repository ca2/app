#pragma once


////#include "acme/prototype/prototype/object.h"


namespace experience
{


   /// experience <3tbs
   /// 0123456789 10+10
   class CLASS_DECL_BERG experience :
      virtual public ::object
   {
   public:


      ::pointer<::factory::factory>       m_pfactory;
      ::property_set                      m_set;
      string                              m_strExperience;


      experience();
      ~experience() override;


      void destroy() override;


      // ::berg::application * get_app();
      // ::berg::session * get_session();
      // ::berg::system * get_system();
      // ::base::user * user() override;


      virtual void update();

      virtual void get_frame_list(string_array & stra);

      virtual ::pointer < frame > frame_experience(const ::scoped_string & scopedstrFrameSchema);


   };


} // namespace experience





