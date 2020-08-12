#pragma once


namespace turboc
{


   class CLASS_DECL_TURBOC frame :
      virtual public simple_frame_window
   {
   public:


      frame(::object * pobject);
      virtual ~frame();


	   virtual void assert_valid() const;
	   virtual void dump(dump_context & dumpcontext) const;


      virtual bool get_translucency(::user::e_translucency & etranslucency, ::user::e_element eelement, ::user::style_context * pinteraction) override;
      virtual ::experience::frame * experience_get_frame();


   };


} // namespace turboc












