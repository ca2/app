#pragma once


namespace turboc
{


   class CLASS_DECL_TURBOC top_view:
      virtual public ::user::split_view
   {
   public:


      edit_view *             m_peditview;
      toggle_view *           m_ptoggleview;
      impact *                  m_pimpact;


      top_view(::object * pobject);
      virtual ~top_view();


      void assert_valid() const override;

      void dump(dump_context & dumpcontext) const override;

      void on_create_split_impact();

      virtual void on_update(::aura::impact * pSender,e_update eupdate,object* pHint);


   };


} // namespace turboc







