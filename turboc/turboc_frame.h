#pragma once


namespace turboc
{


   class CLASS_DECL_TURBOC frame :
      virtual public simple_frame_window
   {
   public:


      frame(::particle * pparticle);
      virtual ~frame();


	   // void assert_ok() const override;
	   // void dump(dump_context & dumpcontext) const override;


      virtual ::user::enum_translucency get_translucency(::user::style * pstyle) const override;
      virtual ::experience::frame * frame_experience();


   };


} // namespace turboc












