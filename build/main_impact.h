#pragma once


namespace app_core_build
{


   class CLASS_DECL_APP_CORE_BUILD main_impact:
      virtual public ::app_consumer < application, ::user::split_impact >
   {
   public:


      ::userex::top_impact *                      m_ptopview;
      ::app_core_build::impact *      m_pimpact;
      string                                    m_strImpactId;


      main_impact();
      ~main_impact() override;


      // void assert_ok() const override;

      // void dump(dump_context & dumpcontext) const override;

      void on_create_split_impact() override;

      void handle(::topic * ptopic, ::context * pcontext) override;

      //void handle(::topic * ptopic, ::context * pcontext) override;


      virtual void _001OnNcDraw(::draw2d::graphics_pointer & pgraphics) override;
      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;


      document * get_document();


   };


} // namespace app_core_build



