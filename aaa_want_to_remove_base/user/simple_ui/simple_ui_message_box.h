#pragma once


namespace simple_ui
{


   class CLASS_DECL_BASE message_box :
      virtual public ::simple_ui::top
   {
   public:


      string_array                 m_stra;
      __pointer_array(tap)                m_tapaA;
      __pointer_array(tap)                m_tapaB;
      i32                 m_iResult;
      u32                m_uiFlags;
      string                  m_strMessage;
      string                  m_strTitle;
      manual_reset_event      m_evReady;


      message_box(::object * pobject,const char * pszMessage,const char * pszCaption,u32 uiFlags);
      virtual ~message_box();


      i32 show();

      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;

      virtual void on_layout(::draw2d::graphics_pointer & pgraphics) override;

      bool on_action(const char * pszId) override;

      virtual void create_a_button(id id,const char * pszText);
      virtual void create_b_button(id id,const char * pszText);
      virtual void create_button(__pointer_array(tap) & tapa, id id,const char * pszText);


      virtual void pre_translate_message(::message::message * pmessage) override;

      //virtual void EndModalLoop(id nResult);

      virtual bool has_pending_graphical_update() override;


//      virtual void on_select_user_style() override;

      //virtual i64 add_ref(OBJ_REF_DBG_PARAMS) override;
      //virtual i64 dec_ref(OBJ_REF_DBG_PARAMS) override;
      

   };


} // namespace simple_ui



CLASS_DECL_BASE i32 simple_ui_message_box(oswindow interaction_impl, const char * pText,const char * lpCaption, u32 uiFlags);







