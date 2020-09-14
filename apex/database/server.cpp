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

      if (get_context_application()->is_system() || get_context_application()->is_session())
      {

         m_bRemote = false;

      }
      else
      {

         m_bRemote = true;

      }

      return estatus;

   }


   bool server::_data_server_load(client * pclient, const key & id, get_memory getmemory, ::update * pupdate)
   {

#if MEMDLEAK

      mem.m_strTag = "memory://member=database::server::data_server_load(1)";

#endif

      return true;

   }


   bool server::_data_server_save(client * pclient, const key & id, block block, ::update * pupdate)
   {

      return true;

   }


   bool server::data_pulse_change(client * pclient, const key & id, ::update * pupdate)
   {

      return on_after_data_change(pclient, id, pupdate);

   }


   bool server::on_before_data_change(client * pclient, const key & id, var & var, ::update * pupdate)
   {

      //::database::change_event signal(var);

      //signal.m_pserver = this;
      //signal.m_pclient = pclient;
      //signal.m_datakey = id;
      //signal.m_pupdate = pupdate;

      for(i32 i = 0; i < m_clienta.get_count(); i++)
      {

         bool bOk = m_clienta.element_at(i)->data_on_before_change(pclient, id, var, pupdate);

         if(!bOk)
         {

            return false;

         }

      }

      return true;

   }


   bool server::on_after_data_change(client * pclient, const key & id, const ::var & var, ::update * pupdate)
   {
      //::database::change_event signal;
      //signal.m_pserver       = this;
      //signal.m_pclient     = pclient;
      //signal.m_datakey          = id;
      //signal.m_pupdate = pupdate;

      for(i32 i = 0; i < m_clienta.get_count(); i++)
      {

         m_clienta.element_at(i)->data_on_after_change(pclient, id, var, pupdate);

      }

      return true;

   }


   var server::data_load(client * pclient, const key & id, ::update * pupdate)
   {

      ::memory_stream is;

      {

         if (!_data_server_load(pclient, id, is->memory(), pupdate))
         {

            return ::type_null;

         }

      }

      var var;

      is >> var;

      return var;

   }


   bool server::data_save(client * pclient, const key & id, var & var, ::update * pupdate)
   {

      ::memory_stream writer;

      writer << var;

      {

         if (!_data_server_load(pclient, id, writer->memory(), pupdate))
         {

            return false;

         }

      }

      return true;

   }


} // namespace database



