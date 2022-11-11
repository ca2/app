#pragma once


namespace turboc
{


   class CLASS_DECL_TURBOC switcher_impact:
      virtual public ::user::split_impact
   {
   public:


      top_impact *              m_ptopview;
      impact *                  m_pimpact;


      switcher_impact(::particle * pparticle);
      virtual ~switcher_impact();


      // void assert_ok() const override;

      // void dump(dump_context & dumpcontext) const override;

      void on_create_split_impact();

      virtual void on_update(::aura::impact * pSender,e_update eupdate,object* pHint);

      virtual void handle(::topic * ptopic, ::context * pcontext);


   };


} // namespace turboc





