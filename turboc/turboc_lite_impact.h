#pragma once


namespace turboc
{


   class CLASS_DECL_TURBOC lite_impact:
      virtual public impact
   {
   public:


      lite_impact(::particle * pparticle);
      virtual ~lite_impact();

      // void assert_ok() const override;

      void dump(dump_context & dumpcontext) const override;

      virtual void install_message_handling(::message::dispatch * pdispatch);

      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics);

      virtual void on_update(::aura::impact * pSender,e_update eupdate,object* pHint);

      virtual void turboc_render(::draw2d::graphics * pdcFull);

      DECLARE_MESSAGE_HANDLER(on_message_create);

      virtual i64 increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS);

      virtual i64 decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS);

   };


} // namespace turboc












