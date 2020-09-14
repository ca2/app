#pragma once


namespace turboc
{


   class CLASS_DECL_TURBOC top_view:
      virtual public ::user::split_view
   {
   public:


      edit_view *             m_peditview;
      toggle_view *           m_ptoggleview;
      view *                  m_pview;


      top_view(::layered * pobjectContext);
      virtual ~top_view();


      virtual void assert_valid() const;

      virtual void dump(dump_context & dumpcontext) const;

      void on_create_split_impact();

      virtual void on_update(::aura::impact * pSender,e_update eupdate,object* pHint);


   };


} // namespace turboc







