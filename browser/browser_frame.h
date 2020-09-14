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


      virtual bool get_translucency(::user::e_translucency & etranslucency, ::user::e_element eelement, ::user::style_context * pinteraction) override;


   };


} // namespace browser



