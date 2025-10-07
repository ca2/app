#include "framework.h"



namespace simpledb
{

   session::session(::particle * pparticle) :
      ::object(pparticle)
   {
      m_pserver = nullptr;
   }

   session::~session_parent
   {
   }

   bool session::open(const ::scoped_string & scopedstrDatabase)
   {
      if(m_pserver != nullptr)
         close();
      server * pserver = ___new server(this);
      if(pserver == nullptr)
         return false;
      if(!pserver->open(scopedstrDatabase))
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

   bool session::query(const ::scoped_string & scopedstrQuery, ::payload & payload)
   {
      string_array_base stra;
      ::property_set set;
      set.parse_network_arguments(scopedstrQuery);
      if(set["command"] == "open")
      {
         payload = open(set["database"]);
      }
      else if(set["command"] == "sql")
      {
         if(!m_pserver->sql(scopedstrQuery, payload))
            payload = false;
      }
      else if(set["command"] == "close")
      {
         payload = close();
      }
      return true;
   }


} // namespace simpledb


