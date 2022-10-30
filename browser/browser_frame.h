#pragma once


namespace browser
{


   class CLASS_DECL_APP_BROWSER frame :
      virtual public simple_frame_window
   {
   public:


      frame(::particle * pparticle);
      virtual ~frame();


//      // void assert_ok() const override;
//      // void dump(dump_context & dumpcontext) const override;


      virtual ::user::enum_translucency get_translucency(::user::style * pstyle) const override;


   };


} // namespace browser



