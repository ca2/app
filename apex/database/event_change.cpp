#include "framework.h"
#include "change_event.h"
#include "client.h"


namespace database
{

   change_event::change_event() :
      m_ppayload(nullptr)
   {
      m_pserver = nullptr;
      m_pupdate = nullptr;
      m_bOk = true;
   }

   change_event::change_event(::payload & payload) :
      m_ppayload(&payload)
   {
      m_pserver = nullptr;
      m_pupdate = nullptr;
      m_bOk = true;
   }


   bool change_event::_data_get(::payload & payload)
   {

      if(m_pserver != nullptr)
      {

         return m_pclient->data_get_payload(m_strDataKey, payload);

      }

      return false;

   }


} // namespace database

