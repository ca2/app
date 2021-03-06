#pragma once


namespace user
{


   class CLASS_DECL_BASE split_view :
      virtual public ::user::impact_host,
      virtual public ::user::show < split_layout >
   {
   public:


      split_view();
      virtual ~split_view();


      virtual void assert_valid() const override;
      virtual void dump(dump_context & dumpcontext) const override;

      virtual void install_message_routing(::channel * pchannel) override;
      virtual bool pre_create_window(::user::system * pusersystem) override;

      virtual void _001OnNcDraw(::draw2d::graphics_pointer & pgraphics) override;
      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;

      virtual void on_subject(::subject::subject * psubject, ::subject::context * pcontext) override;
      virtual bool create_split_impact();
      virtual void on_create_split_impact();

      DECLARE_MESSAGE_HANDLER(on_message_create);
      DECLARE_MESSAGE_HANDLER(on_message_size);
      DECLARE_MESSAGE_HANDLER(on_message_show_window);

      template < class VIEW >
      inline __pointer(VIEW) create_pane_view(index iPane, id id = ::id(), ::user::interaction * pviewLast = nullptr);

      virtual bool on_prepare_impact_data(::user::impact_data* pimpactdata) override;
      

   };


} // namespace user



