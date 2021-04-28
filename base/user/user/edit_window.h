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
         DECLARE_MESSAGE_HANDLER(_001OnDestroy);
         DECLARE_MESSAGE_HANDLER(_001OnSetFocus);
         DECLARE_MESSAGE_HANDLER(_001OnKillFocus);

      virtual LRESULT _OnCreate(VOID);
      virtual LRESULT _OnDestroy(VOID);
      //LRESULT _OnCommand(::u16, ::u16, HWND);
      virtual LRESULT _OnSetFocus(VOID);
      virtual LRESULT _OnKillFocus(VOID);

      virtual void get_text_composition_area(::rectangle_i32 & r);
      virtual void on_text_composition_done(string str);

      virtual bool edit_undo();

      virtual bool is_text_composition_active();

   };


} // namespace user



