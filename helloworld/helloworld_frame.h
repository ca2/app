#pragma once


namespace helloworld
{


   class CLASS_DECL_APP_HELLOWORLD frame :
      virtual public simple_frame_window
   {
   public:


      frame(::object * pobject);
      virtual ~frame();


      void assert_valid() const override;
      void dump(dump_context & dumpcontext) const override;


      virtual ::user::enum_translucency get_translucency(::user::style * pstyle) const override;


   };


} // namespace helloworld












