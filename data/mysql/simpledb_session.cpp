#include "framework.h"


namespace simpledb
{

   session::session(::object * pobject) :
      ::object(pobject)
   {
      m_pserver = nullptr;
   }

   session::~session_parent
   {
   }

   bool session::open(const ::string & pszDatabase)
   {
      if(m_pserver != nullptr)
         close();
      server * pserver = new server(this);
      if(pserver == nullptr)
         return false;
      if(!pserver->open(pszDatabase))
      {
         delete pserver;
         return false;
      }
      m_pserver = pserver;
      return true;
   }

   bool session::close()
   {
      if(m_pserver == nullptr)
         return true;
      delete m_pserver;
      m_pserver = nullptr;
      return true;
   }

   bool session::query(const ::string & pszQuery, ::payload & payload)
   {
      string_array stra;
      property_set set;
      set.parse_url_query(pszQuery);
      if(set["command"] == "open")
      {
         payload = open(set["database"]);
      }
      else if(set["command"] == "sql")
      {
         if(!m_pserver->sql(pszQuery, payload))
            payload = false;
      }
      else if(set["command"] == "close")
      {
         payload = close();
      }
      return true;
   }


} // namespace simpledb


