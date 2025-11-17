#pragma once


#include "acme/handler/topic.h"


class CLASS_DECL_ACME handler_context :
   virtual public ::subparticle
{
public:


   // 0 update serial is not ok
   unsigned long long       m_uUpdateSerial;


   handler_context() { m_uUpdateSerial = 0; }
   ~handler_context() override;


   virtual void start_task();


   virtual void set_up_to_date(const ::topic * ptopic);

   inline bool is_up_to_date(const ::topic * ptopic) const
   {

      if (!m_uUpdateSerial)
      {

         return false;

      }
      
      if (!ptopic->m_uUpdateSerial)
      {

         return false;

      }

      return m_uUpdateSerial == ptopic->m_uUpdateSerial;

   }

};


using handler_context_pointer = ::pointer<handler_context>;





