#pragma once


namespace browser
{


   class CLASS_DECL_APP_BROWSER switcher_view:
      virtual public ::user::split_view
   {
   public:


      ::userex::top_view *    m_ptopview;
      impact *                  m_pimpact;


      switcher_view(::object * pobject);
      virtual ~switcher_view();


      virtual void assert_valid() const;

      virtual void dump(dump_context & dumpcontext) const;

      void on_create_split_impact();

      virtual void handle(::subject * psubject, ::context * pcontext) override;

      virtual void handle(::subject * psubject, ::context * pcontext);
      virtual void _001OnNcDraw(::draw2d::graphics_pointer & pgraphics);
      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics);

   };


} // namespace browser



