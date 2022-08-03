#pragma once


namespace turboc
{


   class CLASS_DECL_TURBOC full_view:
      virtual public impact
   {
   public:


      full_view(::object * pobject);
      virtual ~full_view();


      void assert_ok() const override;

      void dump(dump_context & dumpcontext) const override;

      virtual void install_message_handling(::message::dispatch * pdispatch);

      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics);

      virtual void on_update(::aura::impact * pSender,e_update eupdate,object* pHint);

      virtual void turboc_render(::draw2d::graphics * pdcFull);

      DECLARE_MESSAGE_HANDLER(on_message_create);

   };


} // namespace turboc






