#include "framework.h"


namespace simpledb
{


   session::session(::object * pobject) :
      ::object(pobject)
   {

      m_pserver = nullptr;

   }


   session::~session()
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
      property_set dataset;
      dataset.parse_network_arguments(pszQuery);
      if(dataset["command"] == "open")
      {
         payload = open(dataset["database"]);
      }
      else if(dataset["command"] == "sql")
      {
         if(!m_pserver->sql(pszQuery, payload))
            payload = false;
      }
      else if(dataset["command"] == "close")
      {
         payload = close();
      }
      return true;
   }


} // namespace simpledb


