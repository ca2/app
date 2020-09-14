#include "framework.h"


namespace simpledb
{

   session::session(::layered * pobjectContext) :
      ::object(pobject)
   {
      m_pserver = nullptr;
   }

   session::~session_parent
   {
   }

   bool session::open(const char * pszDatabase)
   {
      if(m_pserver != nullptr)
         close();
      server * pserver = new server(get_object());
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

   bool session::query(const char * pszQuery, var & var)
   {
      string_array stra;
      property_set set;
      set.parse_url_query(pszQuery);
      if(set["command"] == "open")
      {
         var = open(set["database"]);
      }
      else if(set["command"] == "sql")
      {
         if(!m_pserver->sql(pszQuery, var))
            var = false;
      }
      else if(set["command"] == "close")
      {
         var = close();
      }
      return true;
   }


} // namespace simpledb


