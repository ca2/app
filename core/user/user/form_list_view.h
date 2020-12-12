#pragma once


namespace user
{


   class CLASS_DECL_CORE form_list_view:
      virtual public ::user::form_list,
      virtual public ::user::form_view,
      virtual public ::user::list_view
   {
   public:


      form_list_view();
      virtual ~form_list_view();


      virtual ::estatus initialize(::layered * pobjectContext) override;


      virtual void assert_valid() const override;
      virtual void dump(dump_context & dumpcontext) const override;

      virtual bool pre_create_window(::user::create_struct * pcreatestruct) override;

      virtual void install_message_routing(::channel * pchannel) override;

      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;
      virtual void _001OnTimer(::timer * ptime) override;

      virtual void route_command_message(::user::command * pcommand) override;
      virtual void on_command(::user::command* pcommand) override;
      virtual void on_subject(::promise::subject * psubject, ::promise::context * pcontext) override;

      virtual void set_viewport_offset(int, int) override;
      virtual ::point get_viewport_offset() override;
      virtual ::sized get_total_size() override;

      virtual void on_control_event(::user::control_event * pevent) override;

      virtual void OnActivateView(bool bActivate, __pointer(::user::impact) pActivateView, __pointer(::user::impact) pviewDeactivate) override;

      virtual index _001GetCurItem() override;

      virtual void on_layout(::draw2d::graphics_pointer & pgraphics) override;

   };


} // namespace user





