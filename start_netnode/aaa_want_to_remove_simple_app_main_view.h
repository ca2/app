#pragma once


namespace simple_drawing
{


   class CLASS_DECL_APP_SIMPLE_DRAWING main_impact:
      virtual public ::userex::split_view
   {
   public:


      ::userex::top_view *    m_ptopimpact;
      impact *                  m_pimpact;


      main_impact(::particle * pparticle);
      virtual ~main_impact();


      // void assert_ok() const override;

      // void dump(dump_context & dumpcontext) const override;

      void on_create_split_impact() override;

      virtual void handle(::topic * ptopic, ::handler_context * phandlercontext) override;

      virtual bool BaseOnControlEvent(::user::control_event * pevent);


      virtual void _001OnNcDraw(::draw2d::graphics_pointer & pgraphics) override;
      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;



   };


} // namespace simple_drawing





