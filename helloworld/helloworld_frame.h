#pragma once


namespace helloworld
{


   class CLASS_DECL_APP_HELLOWORLD frame :
      virtual public simple_frame_window
   {
   public:


      frame(::particle * pparticle);
      virtual ~frame();


//      // void assert_ok() const override;
//      // void dump(dump_context & dumpcontext) const override;


      virtual ::user::enum_translucency get_translucency(::user::style * pstyle) const override;


   };


} // namespace helloworld












