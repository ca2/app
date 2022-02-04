#pragma once


namespace turboc
{


   class CLASS_DECL_TURBOC main_impact:
      virtual public ::user::split_view
   {
   public:


      top_view *              m_ptopview;
      impact *                  m_pimpact;


      main_impact(::object * pobject);
      virtual ~main_impact();


      void assert_valid() const override;

      void dump(dump_context & dumpcontext) const override;

      void on_create_split_impact();

      virtual void on_update(::aura::impact * pSender,e_update eupdate,object* pHint);

      virtual void handle(::topic * psubject, ::context * pcontext);


   };


} // namespace turboc





