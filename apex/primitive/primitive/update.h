#pragma once


class CLASS_DECL_APEX update :
   virtual public ::context_object
{
public:


   ::u64                                  m_uId; // this 'id' <=== 'update {id}'
   bool                                   m_bRet;
   __pointer(::layered)                   m_psender;
   __pointer(::object)                    m_pobjectTopic;
   ::action_context                       m_actioncontext;
   address_array < ::generic * >          m_handledbya;
   __pointer(::layered)                   m_puserinteraction; // user::interaction
   __pointer(::layered)                   m_pcontrolevent; // user::control_event
   __pointer(::file::item)                m_pfileitem;
   ::user::e_key                          m_ekey;
   ::var                                  m_var;


   update();
   virtual ~update();


   ::update & operator =(::u64 uId) { m_uId = uId; return *this; }
   inline bool operator ==(::u64 uId) const { return m_uId == uId || m_uId == FULL_ID; }


   void set_handled_by(const ::generic * pobject) { m_handledbya.add((::generic *) pobject); }
   bool handled_by(const ::generic * pobject) const { return m_handledbya.has((::generic *) pobject); }


   template < typename CAST >
   __pointer(CAST) cast(const ::id & id) { return operator[](id).cast < CAST >(); }


};


using update_pointer = __pointer(::update);


inline auto new_update() { return __new(::update); }



