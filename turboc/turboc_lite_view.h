#pragma once


namespace turboc
{


   class CLASS_DECL_TURBOC lite_view:
      virtual public view
   {
   public:


      lite_view(::layered * pobjectContext);
      virtual ~lite_view();

      virtual void assert_valid() const;

      virtual void dump(dump_context & dumpcontext) const;

      virtual void install_message_handling(::message::dispatch * pdispatch);

      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics);

      virtual void on_update(::aura::impact * pSender,e_update eupdate,object* pHint);

      virtual void turboc_render(::draw2d::graphics * pdcFull);

      DECL_GEN_SIGNAL(on_message_create);

      virtual i64 add_ref(OBJ_REF_DBG_PARAMS);

      virtual i64 dec_ref(OBJ_REF_DBG_PARAMS);

   };


} // namespace turboc












