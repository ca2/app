// Injected in acme (camilo) from apex(thomas) by camilo on ThomasMonth19-2021 12:27 BRT
// Merge with control_"topic" by camilo on day after ThomasBirthday2021 10:14
#pragma once


#include "topic.h"
#include "acme/primitive/primitive/object.h"
#include "acme/primitive/datetime/earth_time.h"
#include "acme/primitive/primitive/payload.h"


class CLASS_DECL_ACME extended_topic :
   virtual public ::topic,
   virtual public ::object
{
public:


   ::user::interaction *                  m_ptab;
   u64                                    m_uiEvent;
   enum_timer                             m_etimer;
   u32                                    m_uiVKey;
   u32                                    m_uiFlags;
   ::earth::time                          m_timeOuterBeg;
   ::earth::time                          m_timeOuterEnd;
   ::earth::time                          m_timeBeg;
   ::earth::time                          m_timeEnd;


   ::payload                              m_payload;
   ::i64                                  m_iUpdateSerial;
   bool                                   m_bModified;
   ::duration                             m_durationSleep;

   ::pointer<::property_object>          m_pobjectTopic;
   ::pointer<::file::item>               m_pfileitem;


   extended_topic(const ::atom & atom);
   ~extended_topic() override;


#ifdef _DEBUG

   virtual i64 increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override;
   virtual i64 decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override;
   virtual i64 release(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override;

#endif


   ::extended_topic * _extended_topic() override { return this; }
   const ::extended_topic * _extended_topic() const override { return this; }


};



