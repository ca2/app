#pragma once


namespace simple_ui
{


   class CLASS_DECL_CORE message_box :
      virtual public ::simple_ui::top
   {
   public:


      string_array_base                     m_stra;
      pointer_array < tap >             m_tapaA;
      pointer_array < tap >             m_tapaB;
      int                              m_iResult;
      string                           m_strMessage;
      string                           m_strTitle;
      ::e_message_box                  m_emessagebox;
      ::duration                       m_durationTimeout;
      callback                         m_callback;
      manual_reset_happening               m_happeningReady;


      message_box(::particle * pparticle, const ::scoped_string & scopedstrMessage, const ::scoped_string & scopedstrTitle, const ::e_message_box & emessagebox, ::duration durationTimeout);
      virtual ~message_box();


      int show();

      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;

      virtual void on_layout(::draw2d::graphics_pointer & pgraphics) override;

      bool on_action(const ::scoped_string & scopedstrId) override;

      virtual void create_a_button(atom atom, const ::scoped_string & scopedstrText);
      virtual void create_b_button(atom atom, const ::scoped_string & scopedstrText);
      virtual void create_button(pointer_array < tap > & tapa, atom atom, const ::scoped_string & scopedstrText);


      virtual void pre_translate_message(::message::message * pmessage) override;

      //virtual void EndModalLoop(atom nResult);

      virtual bool has_pending_graphical_update() override;


//      virtual void on_select_user_style() override;

      //virtual long long increment_reference_count() override;
      //virtual long long decrement_reference_count() override;
      

   };


} // namespace simple_ui



CLASS_DECL_CORE int simple_ui_message_box(oswindow interaction_impl, const ::string & pText, const ::string & lpCaption, unsigned int uFlags);







