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

         DECL_GEN_SIGNAL(_001OnCreate);
         DECL_GEN_SIGNAL(_001OnDestroy);
         DECL_GEN_SIGNAL(_001OnSetFocus);
         DECL_GEN_SIGNAL(_001OnKillFocus);

      virtual LRESULT _OnCreate(VOID);
      virtual LRESULT _OnDestroy(VOID);
      //LRESULT _OnCommand(::u16, ::u16, HWND);
      virtual LRESULT _OnSetFocus(VOID);
      virtual LRESULT _OnKillFocus(VOID);

      virtual void get_text_composition_area(::rect & r);
      virtual void on_text_composition_done(string str);

      virtual bool edit_undo();

      virtual bool is_text_composition_active();

   };


} // namespace user



