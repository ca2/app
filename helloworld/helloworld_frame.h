#pragma once


namespace helloworld
{


   class CLASS_DECL_APP_HELLOWORLD frame :
      virtual public simple_frame_window
   {
   public:


      frame(::object * pobject);
      virtual ~frame();


      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;


      virtual bool get_translucency(::user::e_translucency & etranslucency, ::user::e_element eelement, ::user::style_context * pinteraction) override;


   };


} // namespace helloworld












