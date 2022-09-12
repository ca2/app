#pragma once


namespace experience
{


   /// experience <3tbs
   /// 0123456789 10+10
   class CLASS_DECL_BASE experience :
      virtual public ::object
   {
   public:


      __pointer(::factory::factory)       m_pfactory;
      property_set                        m_set;
      string                              m_strExperience;


      experience();
      ~experience() override;


      ::base::application * get_app() const;
      ::base::session * get_session() const;
      ::base::system * get_system() const;
      ::base::user * user() const;


      virtual void update();

      virtual void get_frame_list(string_array & stra);

      virtual frame * frame_experience(const ::string & strFrameSchema);


   };


} // namespace experience





