#include "framework.h"
//#include "db_str_set.h"


i32 g_idbchange;


#define new ACME_NEW


db_server::db_server(::layered * pobjectContext) :
   ::object(pobject),
   server(pobject)
{

   m_pdb                = nullptr;
   m_pstrset            = nullptr;
   m_bWorking           = false;
   m_pfilesystemsizeset = nullptr;
   m_bRemote            = true;
   m_psimpledbUser      = nullptr;

}


db_server::~db_server()
{

   close();

   finalize();

}


::database::key db_server::calc_data_key(::database::client * pclient,  ::database::key & key)
{

   if(pclient != nullptr)
   {

      return pclient->calc_data_key(key);

   }
   else
   {

      return key;

   }

}


bool db_server::initialize_user(::simpledb::database * pmysqldbUser, const char * pszUser)
{

   if(pmysqldbUser == nullptr)
      return false;

   m_bRemote         = false;

   m_psimpledbUser    = pmysqldbUser;
   m_strUser         = pszUser;

//   m_plongset        = __new(db_long_set(this));
   m_pstrset         = __new(db_str_set(this));

   if(!create_message_queue())
      return false;

   m_bWorking = true;

   return true;

}


bool db_server::initialize()
{

   if(System.m_varTopicQuery["app"] == "app-core/netnodelite"
         || System.m_varTopicQuery["app"] == "app-core/netnode_dynamic_web_server"
         || System.m_varTopicQuery["app"] == "app-core/netnode_dynamic_web_server_cfg"
         || System.m_varTopicQuery["app"] == "app-core/netnodecfg"
         || System.m_varTopicQuery["app"] == "app-core/mydns"
         || System.m_varTopicQuery["app"] == "app-gtech/sensible_netnode"
         || System.m_varTopicQuery["app"] == "app-gtech/sensible_service"
         || System.has_property("no_remote_simpledb"))
   {

      m_bRemote = false;

   }

   m_pdb          = __new(::sqlite::database(get_object()));

   __pointer(::handler) phandler = System.handler();

   __pointer(command_line) pcommandline = phandler->m_spcommandline;

   string strAppName;

   if(pcommandline.is_null())
   {

      strAppName = System.m_strAppId;

   }
   else
   {

      strAppName = pcommandline->m_strApp;

   }

   ::file::path str;

   //str = ::dir::system() / "database.sqlite";

   if (Application.is_system())
   {

      str = Context.dir().appdata() / "system.sqlite";

   }
   else if (Application.is_session())
   {

      str = Context.dir().appdata() / "session.sqlite";

   }
   else
   {

      str = Context.dir().appdata() / "app.sqlite";

   }

   if(!Context.dir().mk(str.folder()))
   {

      return false;

   }

   m_pdb->setDatabase(str);

   m_pdb->connect();

   m_pdb->create_long_set("integertable");

   m_pdb->create_string_set("stringtable");

//   m_plongset     = __new(db_long_set(this));

   m_pstrset      = __new(db_str_set(this));

   i32 iBufferSize = 128 * 1024;

   __pointer(::handler) commandthread = System.handler();

   if(commandthread->has_property("filesizebuffer"))
   {

      iBufferSize = commandthread->m_varTopicQuery["filesizebuffer"] * 1024 * 1024;

   }

#if !defined(_UWP) && !defined(APPLEOS)

   if(!create_message_queue())
      return false;

#endif

   m_bWorking = true;

   return true;

}


bool db_server::finalize()
{

   m_bWorking = false;

   destroy_message_queue();

   //if(m_pfilesystemsizeset != nullptr)
   //{
   //   delete m_pfilesystemsizeset;
   //   m_pfilesystemsizeset = nullptr;
   //}


   m_pstrset.release();

//   m_plongset.release();

   if(m_pdb != nullptr)
   {

      m_pdb->disconnect();

      m_pdb.release();

   }

   return true;

}


bool db_server::create_message_queue()
{

   //if(!is_window())
   //{
   //   string strName = "::draw2d::account::message_wnd::simpledb::db_server";
   //   if(!::user::interaction::create_message_queue(strName))
   //   {
   //      return false;
   //   }

   //   //SetTimer(1258477, 484, nullptr);

   //   ////MESSAGE_LINK(e_message_timer, m_pimpl, this, &db_server::_001OnTimer);

   //}

   return true;


}

bool db_server::destroy_message_queue()
{
   //if(is_window())
   //{
   //   return DestroyWindow() != FALSE;
   //}
   return true;
}

void db_server::_001OnTimer(::timer * ptimer)
{

   //super::_001OnTimer(ptimer);;
   //
   //if(ptimer->m_uEvent == 1258477)
   //{

   //}

}


void db_server::close()
{

   m_pstrset.release();

//   m_plongset.release();

   m_bWorking = false;

}


bool db_server::data_server_load(::database::client * pclient, ::database::key key, memory & memory, ::update * pupdate)
{

   UNREFERENCED_PARAMETER(pobject);

   if (!load(calc_data_key(pclient, key), memory))
   {

      return false;

   }

   return true;

}


bool db_server::data_server_save(::database::client * pclient, ::database::key key, memory & memory, ::update * pupdate)
{

   sync_lock sl(mutex());

   UNREFERENCED_PARAMETER(pobject);

   if (!save(calc_data_key(pclient, key), memory))
   {

      return false;

   }

   return true;

}


bool db_server::load(const ::database::key & key, string & str)
{

   if(get_db_str_set() == nullptr)
   {

      return false;

   }

   return get_db_str_set()->load(key, str);

}



bool db_server::load(const ::database::key & key, memory & mem)
{

   string str;

   if(!load(key, str))
   {

      return false;

   }

   try
   {

      mem.from_base64(str);

   }
   catch (...)
   {

      return false;

   }

   return true;

}


bool db_server::save(const ::database::key & key, const char * pcsz)

{

   sync_lock sl(mutex());

   if(get_db_str_set() == nullptr)
   {

      return false;

   }

   return get_db_str_set()->save(key, pcsz);


}


bool db_server::save(const ::database::key & key, memory & mem)
{

   sync_lock sl(mutex());

   string str;

   mem.to_base64(str);

   if(!save(key, str))
   {

      return false;

   }

   return true;

}


__pointer(::sqlite::database) db_server::get_database()
{

   return m_pdb;

}


bool db_server::data_pulse_change(::database::client * pclient, ::database::key id, ::update * pupdate)
{

   return ::database::server::data_pulse_change(pclient, id, pupdate);

}


void db_server::assert_valid() const
{

   // return void HAHAHAHAHAHA

}


void db_server::dump(dump_context &) const
{

   // return void HAHAHAHAHAHA

}


db_str_set * db_server::get_db_str_set()
{

   return m_pstrset;

}




