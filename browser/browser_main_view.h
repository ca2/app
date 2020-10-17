#pragma once


namespace browser
{


   class CLASS_DECL_APP_BROWSER main_view:
      virtual public ::user::split_view
   {
   public:


      ::userex::top_view *    m_ptopview;
      view *                  m_pview;


      main_view(::layered * pobjectContext);
      virtual ~main_view();


      virtual void assert_valid() const;

      virtual void dump(dump_context & dumpcontext) const;

      void on_create_split_impact();

      virtual void on_apply(::action * paction) override;

      virtual void on_control_event(::user::control_event * pevent);


      virtual void _001OnNcDraw(::draw2d::graphics_pointer & pgraphics);
      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics);


   };


} // namespace browser



