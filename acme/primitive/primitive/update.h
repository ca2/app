#pragma once


class CLASS_DECL_ACME update :
   virtual public ::context_object
{
public:


   ::id                                   m_id;
   bool                                   m_bRet;
   __pointer(::layered)                   m_psender;
   __pointer(::layered)                   m_pobjectTopic;
   ::action_context                       m_actioncontext;
   address_array < ::element * >          m_handledbya;
   __pointer(::layered)                   m_puserinteraction; // user::interaction
   __pointer(::layered)                   m_pcontrolevent; // user::control_event
   __pointer(::file::item)                m_pfileitem;
   ::user::e_key                          m_ekey;
   ::var                                  m_var;


   update();
   virtual ~update();


   ::update & operator =(::i64 iId) { m_id = iId; return *this; }
   inline bool operator ==(::i64 iId) const { return m_id == iId || m_id == FULL_ID; }


   void set_handled_by(const ::element * pobject) { m_handledbya.add((::element *) pobject); }
   bool handled_by(const ::element * pobject) const { return m_handledbya.has((::element *) pobject); }



};


using update_pointer = __pointer(::update);


inline auto new_update() { return __new(::update); }

