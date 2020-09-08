#pragma once


class CLASS_DECL_AQUA update :
   virtual public ::context_object
{
public:


   ::u64                                  m_uId; // this 'id' <=== 'update {id}'
   bool                                   m_bRet;
   ::generic_object *                     m_psender;
   ::object *                             m_pobjectTopic;
   ::action_context                       m_actioncontext;
   address_array < ::generic_object * >   m_handledbya;
   __pointer(::user::interaction)         m_puserinteraction;
   ::user::control_event *                m_pcontrolevent;
   __pointer(::file::item)                m_pfileitem;
   ::user::e_key                          m_ekey;


   update();
   virtual ~update();


   ::update & operator =(::u64 uId) { m_uId = uId; return *this; }
   inline bool operator ==(::u64 uId) const { return m_uId == uId || m_uId == FULL_ID; }


   void set_handled_by(const ::generic_object * pobject) { m_handledbya.add((::generic_object *) pobject); }
   bool handled_by(const ::generic_object * pobject) const { return m_handledbya.has((::generic_object *) pobject); }


   template < typename CAST >
   __pointer(CAST) cast(const ::id & id) { return operator[](id).cast < CAST >(); }


};


using update_pointer = __pointer(::update);


inline auto new_update() { return __new(::update); }



