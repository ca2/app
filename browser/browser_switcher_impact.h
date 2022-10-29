#pragma once


namespace browser
{


   class CLASS_DECL_APP_BROWSER switcher_impact:
      virtual public ::user::split_impact
   {
   public:


      ::userex::top_impact *    m_ptopview;
      impact *                  m_pimpact;


      switcher_impact(::particle * pparticle);
      virtual ~switcher_impact();


      // void assert_ok() const override;

      void dump(dump_context & dumpcontext) const override;

      void on_create_split_impact();

      virtual void handle(::topic * ptopic, ::context * pcontext) override;

      virtual void handle(::topic * ptopic, ::context * pcontext);
      virtual void _001OnNcDraw(::draw2d::graphics_pointer & pgraphics);
      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics);

   };


} // namespace browser



