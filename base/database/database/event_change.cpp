#include "framework.h"


namespace database
{

   change_event::change_event() :
      m_pvar(nullptr)
   {
      m_pserver = nullptr;
      m_pupdate = nullptr;
      m_bOk = true;
   }

   change_event::change_event(var & var) :
      m_pvar(&var)
   {
      m_pserver = nullptr;
      m_pupdate = nullptr;
      m_bOk = true;
   }

   bool change_event::_data_get(var & var)
   {

      if(m_pserver != nullptr)
      {

         return m_pclient->data_get(m_datakey, var);

      }

      return false;

   }


} // namespace database

