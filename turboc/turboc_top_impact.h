#pragma once


namespace turboc
{


   class CLASS_DECL_TURBOC top_impact:
      virtual public ::user::split_impact
   {
   public:


      edit_impact *             m_peditview;
      toggle_impact *           m_ptoggleview;
      impact *                  m_pimpact;


      top_impact(::object * pobject);
      virtual ~top_impact();


      void assert_ok() const override;

      void dump(dump_context & dumpcontext) const override;

      void on_create_split_impact();

      virtual void on_update(::aura::impact * pSender,e_update eupdate,object* pHint);


   };


} // namespace turboc







