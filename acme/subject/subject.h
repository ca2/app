// Injected in acme (camilo) from apex(thomas) by camilo on ThomasMonth19-2021 12:27 BRT
// Merge with control_"subject" by camilo on day after ThomasBirthday2021 10:14
#pragma once


class CLASS_DECL_ACME subject :
   virtual public object
{
public:


   ::user::interaction *                  m_ptab;
   ::user::interaction *                  m_pform;
   u64                                    m_uiEvent;
   enum_timer                             m_etimer;
   ::action_context                       m_actioncontext;
   u32                                    m_uiVKey;
   u32                                    m_uiFlags;
   bool                                   m_bRet;
   bool                                   m_bOk;
   ::datetime::time                       m_timeOuterBeg;
   ::datetime::time                       m_timeOuterEnd;
   ::datetime::time                       m_timeBeg;
   ::datetime::time                       m_timeEnd;
   item                                   m_item;


   ::user::enum_key                       m_ekey;
   ::payload                              m_payload;
   ::i64                                  m_iUpdateSerial;
   bool                                   m_bModified;
   ::duration                               m_durationSleep;

   enum_subject                           m_esubject;
   __pointer(::matter)                    m_pmatter;
   __pointer(::property_object)           m_pobjectTopic;
   //::action_context                     m_actioncontext;
   __pointer(::property_object)           m_psender;
   __pointer(::user::element)             m_puserelement; // user::interaction
   //__pointer(::property_object)         m_pcontrolevent; // user::control_event
   __pointer(::file::item)                m_pfileitem;
   //bool                                   m_bRet;


   subject(const ::id & id = e_type_null) :
      ::material_object(id),
      ::property_object(id),
      ::object(id)
   {

      m_bOk = true;
      m_bRet = false;
      m_puserelement = nullptr;
      m_ptab = nullptr;
      m_esubject = e_subject_handle;
      m_bRet = false;

   }

   ~subject() override;


#ifdef _DEBUG

   virtual i64 increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override;
   virtual i64 decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override;
   virtual i64 release(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override;

#endif


   ::subject & operator=(const ::id & id)
   {

      m_id = id;

      return *this;

   }


   inline bool operator==(const ::id & id) const { return m_id == id || m_id == FULL_ID; }

   operator subject *() { return this; }

   operator const subject *() const { return this; }

   inline ::id &id() { return m_id; }

   inline const ::id &id() const { return m_id; }

   void Ret();
   void Ok();
   void Nok();


   ::id user_element_id() const;


   virtual ::user::form * get_form();
   virtual ::user::form * get_parent_form();
   virtual ::user::interaction * user_interaction();



};

