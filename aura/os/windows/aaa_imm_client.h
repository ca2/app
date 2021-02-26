#pragma once


#define TEXT_COMPOSITION_MESSAGE_UPDATE_CANDIDATE_WINDOW_POSITION 256
#define TEXT_COMPOSITION_MESSAGE_UPDATE_CARET 512


#ifdef WINDOWS_DESKTOP


enum enum_composition_state
{
   e_composition_state_none,
   e_composition_state_composing,
   e_composition_state_selected,
};

class CLASS_DECL_AURA imm_client :
   virtual public ::user::interaction
{
public:


   string                                       m_strImeComposition;
   bool                                         m_bTextCompositionActive;
   bool                                         m_bImeCancelling;


   imm_client();
   virtual ~imm_client();


   virtual void install_message_routing(::channel * pchannel) override;


   DECL_GEN_SIGNAL(_001OnKeyDown);
   DECL_GEN_SIGNAL(_011OnChar);
   DECL_GEN_SIGNAL(_001OnIme);
   DECL_GEN_SIGNAL(_001OnSetFocus);
   DECL_GEN_SIGNAL(_001OnKillFocus);

   virtual int on_text_composition_message(int iMessage) override;

   virtual void on_text_composition_done() override;

   virtual void on_text_composition(string strMessage);

   virtual void insert_text(string str, bool bForceNewStep, const ::action_context & context) override;

   virtual bool is_text_composition_active() const;


};

#endif



