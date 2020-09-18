#pragma once


namespace browser
{


   class CLASS_DECL_APP_BROWSER frame :
      virtual public simple_frame_window
   {
   public:


      frame(::layered * pobjectContext);
      virtual ~frame();


      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;


      virtual ::user::e_translucency get_translucency(::user::style * pstyle) const override;


   };


} // namespace browser



