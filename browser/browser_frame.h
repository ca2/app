#pragma once


namespace browser
{


   class CLASS_DECL_APP_BROWSER frame :
      virtual public simple_frame_window
   {
   public:


      frame(::object * pobject);
      virtual ~frame();


      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;


      virtual ::user::enum_translucency get_translucency(::user::style * pstyle) const override;


   };


} // namespace browser



