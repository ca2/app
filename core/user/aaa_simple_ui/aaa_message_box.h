#pragma once


namespace simple_ui
{


   class CLASS_DECL_CORE message_box :
      virtual public ::simple_ui::top
   {
   public:


      string_array                     m_stra;
      __pointer_array(tap)             m_tapaA;
      __pointer_array(tap)             m_tapaB;
      i32                              m_iResult;
      string                           m_strMessage;
      string                           m_strTitle;
      ::e_message_box                  m_emessagebox;
      ::duration                       m_durationTimeout;
      callback                         m_callback;
      manual_reset_event               m_evReady;


      message_box(::object * pobject, const ::string & pszMessage, const ::string & pszTitle, const ::e_message_box & emessagebox, ::duration durationTimeout);
      virtual ~message_box();


      i32 show();

      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;

      virtual void on_layout(::draw2d::graphics_pointer & pgraphics) override;

      bool on_action(const ::string & pszId) override;

      virtual void create_a_button(id id, const ::string & pszText);
      virtual void create_b_button(id id, const ::string & pszText);
      virtual void create_button(__pointer_array(tap) & tapa, id id, const ::string & pszText);


      virtual void pre_translate_message(::message::message * pmessage) override;

      //virtual void EndModalLoop(id nResult);

      virtual bool has_pending_graphical_update() override;


//      virtual void on_select_user_style() override;

      //virtual i64 increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override;
      //virtual i64 decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override;
      

   };


} // namespace simple_ui



CLASS_DECL_CORE i32 simple_ui_message_box(oswindow interaction_impl, const ::string & pText, const ::string & lpCaption, u32 uFlags);







