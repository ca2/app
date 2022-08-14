#pragma once


namespace user
{


   class CLASS_DECL_CORE form_list_impact:
      virtual public ::user::form_list,
      virtual public ::user::form_impact,
      virtual public ::user::list_impact
   {
   public:


      form_list_impact();
      virtual ~form_list_impact();


      virtual void initialize(::object * pobject) override;


      inline ::core::application* get_app() const { return m_pcontext ? m_pcontext->m_pcoreapplication : nullptr; }
      inline ::core::session* get_session() const { return m_pcontext ? m_pcontext->m_pcoresession : nullptr; }
      inline ::core::system* get_system() const { return m_psystem ? m_psystem->m_pcoresystem : nullptr; }


      void assert_ok() const override;
      void dump(dump_context & dumpcontext) const override;

      virtual bool pre_create_window(::user::system * pusersystem) override;

      void install_message_routing(::channel * pchannel) override;

      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;
      virtual void _001OnTimer(::timer * ptime) override;

      void route_command(::message::command * pcommand, bool bRouteToKeyDescendant = false) override;
      virtual void on_command(::message::command* pcommand) override;
      virtual void handle(::topic * ptopic, ::context * pcontext) override;

      virtual void set_impactport_offset(::draw2d::graphics_pointer & pgraphics, int, int) override;
      virtual ::point_i32 get_impactport_offset() override;
      virtual ::size_f64 get_total_size() override;

      //virtual void handle(::topic * ptopic, ::context * pcontext) override;

      virtual void OnActivateImpact(bool bActivate, __pointer(::user::impact) pActivateImpact, __pointer(::user::impact) pviewDeactivate) override;

      virtual index _001GetCurItem() override;

      virtual void on_layout(::draw2d::graphics_pointer & pgraphics) override;

   };


} // namespace user




