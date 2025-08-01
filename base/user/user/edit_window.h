#pragma once


namespace user
{


   class CLASS_DECL_BASE edit_window :
      virtual public ::user::interaction
   {
   public:

      edit_window();
         virtual ~edit_window();


         virtual void install_edit_window_message_routing(channel * pchannel);

         DECLARE_MESSAGE_HANDLER(on_message_create);
         DECLARE_MESSAGE_HANDLER(on_message_destroy);
         DECLARE_MESSAGE_HANDLER(on_message_set_focus);
         DECLARE_MESSAGE_HANDLER(on_message_kill_focus);

      virtual LRESULT _OnCreate(VOID);
      virtual LRESULT _OnDestroy(VOID);
      //LRESULT _OnCommand(unsigned short, unsigned short, HWND);
      virtual LRESULT _OnSetFocus(VOID);
      virtual LRESULT _OnKillFocus(VOID);

      virtual void get_text_composition_area(::int_rectangle & r);
      virtual void on_text_composition_done(const ::scoped_string & scopedstr);

      virtual bool edit_undo();

      virtual bool is_text_composition_active();

   };


} // namespace user



