#include "framework.h"
#include "server.h"
#include "acme/filesystem/file/binary_stream.h"
#include "acme/filesystem/file/memory_file.h"
#include "acme/parallelization/event.h"
#include "apex/platform/context.h"


namespace database
{


   server::server()
   {


      defer_create_synchronization();

   }


   server::~server()
   {

   }


   void server::initialize(::particle * pparticle)
   {

      /*auto estatus = */ ::object::initialize(pparticle);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      if (m_pcontext->m_papexcontext->is_system() || m_pcontext->m_papexcontext->is_session())
      {

         m_bRemote = false;

      }
      else
      {

         m_bRemote = true;

      }

      //return estatus;

   }


   bool server::_data_server_load(client * pclient, const ::scoped_string & scopedstr, get_memory getmemory, ::topic * ptopic)
   {

#if MEMDLEAK

      mem.m_strTag = "memory://member=database::server::data_server_load(1)";

#endif

      return true;

   }


   void server::_data_server_save(client * pclient, const ::scoped_string & scopedstr, block block, ::topic * ptopic)
   {

      //return true;

   }


   void server::data_pulse_change(client * pclient, const ::scoped_string & scopedstr, ::topic * ptopic)
   {

      on_after_data_change(pclient, scopedstr, ptopic);

   }


   void server::on_before_data_change(client * pclient, const ::scoped_string & scopedstr, ::payload & payload, ::topic * ptopic)
   {

      //::database::change_event signal(payload);

      //signal.m_pserver = this;
      //signal.m_pclient = pclient;
      //signal.m_strDataKey = atom;
      //signal.m_pupdate = pchange;

      for(i32 i = 0; i < m_clienta.get_count(); i++)
      {

         //bool bOk = 
         m_clienta.element_at(i)->data_on_before_change(pclient, scopedstr, payload, ptopic);

         //if(!bOk)
         //{

         //   return false;

         //}

      }

//      return true;

   }


   void server::on_after_data_change(client * pclient, const ::scoped_string & scopedstr, const ::payload & payload, ::topic * ptopic)
   {

      //::database::change_event signal;
      //signal.m_pserver       = this;
      //signal.m_pclient     = pclient;
      //signal.m_strDataKey          = atom;
      //signal.m_pupdate = pchange;

      for(i32 i = 0; i < m_clienta.get_count(); i++)
      {

         if (::is_set(ptopic))
         {

            ptopic->m_pparticle = m_clienta.element_at(i);

         }

         m_clienta.element_at(i)->data_on_after_change(pclient, scopedstr, payload, ptopic);

      }

      //return true;

   }


   ::payload server::data_load(client * pclient, const ::scoped_string & scopedstr, ::topic * ptopic)
   {

      auto pmemoryfile = create_memory_file();

      if (!_data_server_load(pclient, scopedstr, pmemoryfile->memory(), ptopic))
      {

         return ::e_type_null;

      }

      binary_stream stream(pmemoryfile);

      ::payload payload;

      stream >> payload;

      return payload;

   }


   void server::data_save(client * pclient, const ::scoped_string & scopedstr, ::payload & payload, ::topic * ptopic)
   {

      auto pmemoryfile = create_memory_file();

      binary_stream stream(pmemoryfile);

      stream << payload;

      _data_server_save(pclient, scopedstr, pmemoryfile->memory(), ptopic);

   }


} // namespace database



