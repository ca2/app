#include "framework.h"


namespace database
{


   server::server()
   {


      defer_create_mutex();

   }


   server::~server()
   {

   }


   ::estatus server::initialize(::layered * pobjectContext)
   {

      auto estatus = ::object::initialize(pobjectContext);

      if (!estatus)
      {

         return estatus;

      }

      if (get_context()->is_system() || get_context()->is_session())
      {

         m_bRemote = false;

      }
      else
      {

         m_bRemote = true;

      }

      return estatus;

   }


   bool server::_data_server_load(client * pclient, const key & id, get_memory getmemory, ::subject * paction)
   {

#if MEMDLEAK

      mem.m_strTag = "memory://member=database::server::data_server_load(1)";

#endif

      return true;

   }


   bool server::_data_server_save(client * pclient, const key & id, block block, ::subject * paction)
   {

      return true;

   }


   bool server::data_pulse_change(client * pclient, const key & id, ::subject * paction)
   {

      return on_after_data_change(pclient, id, paction);

   }


   bool server::on_before_data_change(client * pclient, const key & id, payload & payload, ::subject * paction)
   {

      //::database::change_event signal(payload);

      //signal.m_pserver = this;
      //signal.m_pclient = pclient;
      //signal.m_datakey = id;
      //signal.m_pupdate = pchange;

      for(i32 i = 0; i < m_clienta.get_count(); i++)
      {

         bool bOk = m_clienta.element_at(i)->data_on_before_change(pclient, id, payload, paction);

         if(!bOk)
         {

            return false;

         }

      }

      return true;

   }


   bool server::on_after_data_change(client * pclient, const key & id, const ::payload & payload, ::subject * paction)
   {

      //::database::change_event signal;
      //signal.m_pserver       = this;
      //signal.m_pclient     = pclient;
      //signal.m_datakey          = id;
      //signal.m_pupdate = pchange;

      for(i32 i = 0; i < m_clienta.get_count(); i++)
      {

         if (::is_set(paction))
         {

            paction->m_pmatter = m_clienta.element_at(i);

         }

         m_clienta.element_at(i)->data_on_after_change(pclient, id, payload, paction);

      }

      return true;

   }


   payload server::data_load(client * pclient, const key & id, ::subject * paction)
   {

      ::memory_stream is;

      {

         if (!_data_server_load(pclient, id, is->memory(), paction))
         {

            return ::e_type_null;

         }

      }

      payload payload;

      is >> payload;

      return payload;

   }


   bool server::data_save(client * pclient, const key & id, payload & payload, ::subject * paction)
   {

      ::memory_stream writer;

      writer << payload;

      {

         if (!_data_server_load(pclient, id, writer->memory(), paction))
         {

            return false;

         }

      }

      return true;

   }


} // namespace database



