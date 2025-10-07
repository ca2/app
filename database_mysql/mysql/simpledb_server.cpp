#include "framework.h"



namespace simpledb
{

   server::server(::particle * pparticle) :
      ::object(pparticle)
   {
      m_pbase = nullptr;
   }

   server::~server()
   {
   }

   bool server::open(const ::scoped_string & scopedstrDatabase)
   {
      if(m_pbase != nullptr)
         close();
      class base * pusermessage = ___new class base (this);
      if(pusermessage == nullptr)
         return false;
      pusermessage->setDatabase(scopedstrDatabase);
      if(pusermessage->connect())
      {
         delete pusermessage;
         return false;
      }
      m_pbase = pusermessage;
      return true;
   }

   bool server::close()
   {
      if(m_pbase == nullptr)
         return true;
      m_pbase->disconnect();
      delete m_pbase;
      m_pbase = nullptr;
      return true;
   }

   bool server::sql(const ::scoped_string & scopedstrQuery, ::payload & payload)
   {
      if(m_pbase == nullptr)
         return false;
      class ::simpledb::set * pset     = m_pbase->create_dataset();
      pset->exec(scopedstrQuery);
      payload.propset()["::database::result_set"] = &pset->m_resultset;
      return true;
   }


} // namespace simpledb


