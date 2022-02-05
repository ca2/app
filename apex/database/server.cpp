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


   void server::initialize(::object * pobject)
   {

      /*auto estatus = */ ::object::initialize(pobject);

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


   bool server::_data_server_load(client * pclient, const key & atom, get_memory getmemory, ::topic * ptopic)
   {

#if MEMDLEAK

      mem.m_strTag = "memory://member=database::server::data_server_load(1)";

#endif

      return true;

   }


   void server::_data_server_save(client * pclient, const key & atom, block block, ::topic * ptopic)
   {

      //return true;

   }


   void server::data_pulse_change(client * pclient, const key & atom, ::topic * ptopic)
   {

      on_after_data_change(pclient, atom, ptopic);

   }


   void server::on_before_data_change(client * pclient, const key & atom, ::payload & payload, ::topic * ptopic)
   {

      //::database::change_event signal(payload);

      //signal.m_pserver = this;
      //signal.m_pclient = pclient;
      //signal.m_datakey = atom;
      //signal.m_pupdate = pchange;

      for(i32 i = 0; i < m_clienta.get_count(); i++)
      {

         //bool bOk = 
         m_clienta.element_at(i)->data_on_before_change(pclient, atom, payload, ptopic);

         //if(!bOk)
         //{

         //   return false;

         //}

      }

//      return true;

   }


   void server::on_after_data_change(client * pclient, const key & atom, const ::payload & payload, ::topic * ptopic)
   {

      //::database::change_event signal;
      //signal.m_pserver       = this;
      //signal.m_pclient     = pclient;
      //signal.m_datakey          = atom;
      //signal.m_pupdate = pchange;

      for(i32 i = 0; i < m_clienta.get_count(); i++)
      {

         if (::is_set(ptopic))
         {

            ptopic->m_pextendedtopic->m_pmatter = m_clienta.element_at(i);

         }

         m_clienta.element_at(i)->data_on_after_change(pclient, atom, payload, ptopic);

      }

      //return true;

   }


   ::payload server::data_load(client * pclient, const key & atom, ::topic * ptopic)
   {

      ::memory_stream is;

      {

         if (!_data_server_load(pclient, atom, is->memory(), ptopic))
         {

            return ::e_type_null;

         }

      }

      ::payload payload;

      is >> payload;

      return payload;

   }


   void server::data_save(client * pclient, const key & atom, ::payload & payload, ::topic * ptopic)
   {

      ::memory_stream writer;

      writer << payload;

      _data_server_save(pclient, atom, writer->memory(), ptopic);

   }


} // namespace database



