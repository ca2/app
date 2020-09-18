#pragma once


namespace helloworld
{


   class CLASS_DECL_APP_HELLOWORLD frame :
      virtual public simple_frame_window
   {
   public:


      frame(::layered * pobjectContext);
      virtual ~frame();


      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;


      virtual ::user::e_translucency get_translucency(::user::style * pstyle) const override;


   };


} // namespace helloworld












