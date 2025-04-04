// Injected in acme (camilo) from apex(thomas) by camilo on ThomasMonth19-2021 12:27 BRT
// Merge with control_"topic" by camilo on day after ThomasBirthday2021 10:14
#pragma once


#include "acme/handler/topic.h"
////#include "acme/prototype/prototype/object.h"
////#include "acme/prototype/datetime/earth_time.h"
//#include "acme/prototype/prototype/payload.h"


class CLASS_DECL_ACME extended_topic :
   virtual public ::topic/*,
   virtual public ::object*/
{
public:


   ::user::interaction *                  m_ptab;
   unsigned long long                                    m_uiEvent;
   enum_timer                             m_etimer;
   unsigned int                                    m_uiVKey;
   unsigned int                                    m_uiFlags;
   ::earth::time                          m_timeOuterBeg;
   ::earth::time                          m_timeOuterEnd;
   ::earth::time                          m_timeBeg;
   ::earth::time                          m_timeEnd;


   ::payload                              m_payload;
   bool                                   m_bModified;
   class ::time                             m_timeSleep;

   ::pointer<::property_object>          m_pobjectTopic;
   ::pointer<::file::item>               m_pfileitem;


   extended_topic(const ::atom & atom);
   ~extended_topic() override;


#ifdef _DEBUG

   long long increment_reference_count() override;
   long long decrement_reference_count() override;
   long long release() override;

#endif


   ::extended_topic * _extended_topic() override { return this; }
   const ::extended_topic * _extended_topic() const override { return this; }


};



