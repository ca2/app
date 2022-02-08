#pragma once


namespace user
{


   //class draw_list_item;


   //class CLASS_DECL_BASE control :
   //   virtual public ::user::box
   //{
   //public:


   //   ::aura::draw_context *              m_pdrawcontext;
   //   __pointer(::user::interaction)      m_puserinteractionCustomWindowProc;
   //   bool                                m_bCustomWindowProc;
   //   index                               m_iEditItem;
   //   bool                                m_bControlExCommandEnabled;
   //   ::user::interaction *               m_puiLabel;
   //   bool                                m_bIdBound;


   //   control();
   //   virtual ~control();


   //   void install_message_routing(::channel * pchannel) override;

   //   /// if you (developer) don't know how to create a control,
   //   /// you should be able (control developer pay attention now),
   //   /// to build a default control with a default constructed
   //   /// ::user::control_descriptor.
   //   virtual bool create_interaction(::user::interaction * pinteractionParent, const ::atom & atom) override;


   //   virtual estate get_state() const override;

   //   bool _003IsCustomMessage();
   //   ::user::primitive * _003GetCustomMessageWnd();


   //   virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;


   //   void route_command(::message::command * pcommand, bool bRouteToKeyDescendant = false) override;

   //   virtual bool has_function(enum_control_function econtrolfunction) const;
   //   virtual enum_control_type get_control_type() const override;

   //   virtual void _003CallCustomDraw(::draw2d::graphics_pointer & pgraphics, ::aura::draw_context * pitem);
   //   virtual bool _003CallCustomWindowProc(__pointer(::user::interaction) puserinteraction, const ::atom & atom, wparam wparam, lparam lparam, LRESULT & lresult);

   //   virtual void _003OnCustomDraw(::draw2d::graphics_pointer & pgraphics, ::aura::draw_context * pitem);
   //   virtual void _003CustomWindowProc(::message::message * pmessage);

   //   //virtual form_list * get_form_list();
   //   virtual bool _001IsPointInside(::point_i32 point) override;

   //   control null() { return control(); }
   //   bool Validate(string & str);
   //   bool get_data(__pointer(::user::interaction) puserinteraction, ::payload & payload);
   //   void SetEditItem(index iItem);
   //   void SetEditSubItem(index iItem);
   //   index GetEditSubItem();
   //   index GetEditItem();

   //   //virtual ::user::interaction * ControlExGetWnd();

   //   //using ::user::box::get_client_rect;
   //   //virtual bool get_client_rect(RECTANGLE_I32 * prectangle) override;
   //   //using ::user::box::get_window_rect;
   //   //virtual bool get_window_rect(RECTANGLE_I32 * prectangle) override;



   //   bool operator == (const class ::user::control_descriptor & descriptor) const;
   //   bool operator == (const class control & control) const;


   //   virtual bool IsControlCommandEnabled();
   //   virtual void EnableControlCommand(bool bEnable);

   //   //virtual void BaseControlExOnMouseMove(::u32 nFlags, const ::point_i32 & point);

   //   //virtual void on_hit_test(::item & item) override;

   //   DECLARE_MESSAGE_HANDLER(on_message_create);
   //   //DECLARE_MESSAGE_HANDLER(on_message_mouse_move);
   //   //DECLARE_MESSAGE_HANDLER(on_message_mouse_leave);
   //   DECLARE_MESSAGE_HANDLER(on_message_key_down);
   //   DECLARE_MESSAGE_HANDLER(_001OnEnable);
   //   DECLARE_MESSAGE_HANDLER(_001OnSetFocus);
   //   DECLARE_MESSAGE_HANDLER(_001OnKillFocus);

   //   virtual void route(::topic * ptopic, ::context * pcontext) override;

   //   virtual void on_notify_control_event(control_event* pevent) override;

   //   virtual void handle(::topic * ptopic, ::context * pcontext) override;

   //   //virtual bool simple_on_control_event(::message::message * pmessage, ::enum_topic etopic) override;

   //   //virtual void walk_pre_translate_tree(::message::message * pmessage,__pointer(::user::interaction) puiStop);




   //   virtual bool get_element_rect(RECTANGLE_I32 * prectangle, enum_element eelement);

   //   virtual void get_simple_drop_down_open_arrow_polygon(point_i32_array & pointa);


   //};


   //class control_cmd_ui : public ::message::command
   //{
   //public:


   //   id_to_id      m_mapControlCommand;


   //   control_cmd_ui();


   //   virtual void enable(bool bOn);
   //   virtual void SetCheck(i32 nCheck);
   //   virtual void SetText(const ::string & pszText);

   //   atom GetControlCommand(atom atom);

   //};


   //class control_view_impl :
   //   virtual public ::object
   //{
   //public:

   //   control_view_impl();

   //   virtual LRESULT BaseControlExOnIdleUpdateCmdUI(WPARAM wParam, LPARAM);
   //   virtual void BaseControlExOnUpdateCmdUI(__pointer(::user::frame_window) pTarget, bool bDisableIfNoHndler);
   //   virtual bool BaseControlExOnCommand(WPARAM wParam, LPARAM lParam) ;
   //   virtual __pointer(::user::interaction) get_window();

   //   control_cmd_ui  m_commandui; // ::message::command derived class used to update
   //                                 // base_controlex derived controls
   //   list<oswindow, oswindow> m_listwndptrBlackList;
   //};



} // namespace user
