#pragma once


namespace helloworld
{


   class CLASS_DECL_APP_HELLOWORLD main_impact:
      virtual public ::user::split_impact
   {
   public:


      ::userex::top_impact *    m_ptopimpact;
      impact *                  m_pimpact;


      main_impact(::particle * pparticle);
      virtual ~main_impact();


      // void assert_ok() const override;

      // void dump(dump_context & dumpcontext) const override;

      void on_create_split_impact();

      void handle(::topic * ptopic, ::handler_context * phandlercontext) override;

      virtual void handle(::topic * ptopic, ::handler_context * phandlercontext);


      virtual void _001OnNcDraw(::draw2d::graphics_pointer & pgraphics);
      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics);



   };


} // namespace helloworld





