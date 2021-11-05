#pragma once


namespace turboc
{


   class CLASS_DECL_TURBOC frame :
      virtual public simple_frame_window
   {
   public:


      frame(::object * pobject);
      virtual ~frame();


	   void assert_valid() const override;
	   void dump(dump_context & dumpcontext) const override;


      virtual ::user::enum_translucency get_translucency(::user::style * pstyle) const override;
      virtual ::experience::frame * experience_get_frame();


   };


} // namespace turboc












