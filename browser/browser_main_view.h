#pragma once


namespace browser
{


   class CLASS_DECL_APP_BROWSER main_impact:
      virtual public ::user::split_view
   {
   public:


      ::userex::top_view *    m_ptopview;
      impact *                  m_pimpact;


      main_impact(::object * pobject);
      virtual ~main_impact();


      void assert_valid() const override;

      void dump(dump_context & dumpcontext) const override;

      void on_create_split_impact();

      virtual void handle(::subject * psubject, ::context * pcontext) override;

      virtual void handle(::subject * psubject, ::context * pcontext);


      virtual void _001OnNcDraw(::draw2d::graphics_pointer & pgraphics);
      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics);


   };


} // namespace browser



