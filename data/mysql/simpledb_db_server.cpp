#include "framework.h"
#include "db_str_set.h"


i32 g_idbchange;


db_server::db_server(::layered * pobjectContext) :
   ::object(pobject)
{

   m_pdb                = nullptr;
   m_plongset           = nullptr;
   m_pstrset            = nullptr;
   m_bWorking           = false;
   m_pfilesystemsizeset = nullptr;
   m_bRemote            = true;
   m_pmysqldbUser       = nullptr;

}


db_server::~db_server()
{

   close();

}




bool db_server::initialize_user(mysql::database * pmysqldbUser, const char * pszUser)
{

   if(pmysqldbUser == nullptr)
      return false;

   m_bRemote         = false;

   m_pmysqldbUser    = pmysqldbUser;
   m_strUser         = pszUser;

   m_plongset        = new db_long_set(this);
   m_pstrset         = new db_str_set(this);

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

   m_pdb          = new ::sqlite::database(get_object());

   string str;

   str = Context.dir().userappdata("database.sqlite");

   Context.dir().mk(Context.dir().name(str));

   m_pdb->setDatabase(str);

   m_pdb->connect();

   m_pdb->create_long_set("integertable");

   m_pdb->create_string_set("stringtable");

   m_plongset     = new db_long_set(this);

   m_pstrset      = new db_str_set(this);

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

   if(m_pfilesystemsizeset != nullptr)
   {
      delete m_pfilesystemsizeset;
      m_pfilesystemsizeset = nullptr;
   }


   if(m_pstrset != nullptr)
   {
      delete m_pstrset;
      m_pstrset = nullptr;
   }


   if(m_plongset != nullptr)
   {
      delete m_plongset;
      m_plongset = nullptr;
   }


   if(m_pdb != nullptr)
   {
      m_pdb->disconnect();
      m_pdb.release();
   }

   return true;

}

bool db_server::create_message_queue()
{

   if(!is_window())
   {
      string strName = "::draw2d::account::message_wnd::simpledb::db_server";
      if(!::user::interaction::create_message_queue(strName))
      {
         return false;
      }

      //SetTimer(1258477, 484, nullptr);

      ////MESSAGE_LINK(e_message_timer, m_pimpl, this, &db_server::_001OnTimer);

   }

   return true;


}

bool db_server::destroy_message_queue()
{
   if(is_window())
   {
      return DestroyWindow() != false;
   }
   return true;
}

void db_server::_001OnTimer(::timer * ptimer)
{

   super::_001OnTimer(ptimer);;

   if(ptimer->m_uEvent == 1258477)
   {

   }

}


void db_server::close()
{

   if(m_pstrset != nullptr)
   {
      delete m_pstrset;
      m_pstrset = nullptr;
   }

   if(m_plongset != nullptr)
   {
      delete m_plongset;
      m_plongset = nullptr;
   }

   m_bWorking = false;

}


// bool db_server::data_server_load(::database::client * pclient, ::database::key id, ::file::output_stream & writable, ::update * pupdate)
// {

//    UNREFERENCED_PARAMETER(pobject);

//    if(!load(calc_data_key(pclient,id),writable))
//       return false;

//    return true;

// }


// bool db_server::data_server_save(::database::client * pclient, ::database::key id, ::file::input_stream & readable, ::update * pupdate)
// {

//    UNREFERENCED_PARAMETER(pobject);

//    if(!save(calc_data_key(pclient,id),readable))
//       return false;

//    return true;

// }


// bool db_server::load(const char * lpcszKey, string & str)
// {

//    if(get_db_str_set() == nullptr)
//       return false;

//    return get_db_str_set()->load(lpcszKey, str);

// }



// bool db_server::load(const char * lpKey, ::file::output_stream & ostream)
// {

//    string str;

//    if(!load(lpKey, str))
//    {

//       return false;

//    }

//    ::file::byte_output_stream os(ostream);

//    os.write_from_hex(str);

//    return true;

// }


// bool db_server::save(const char * lpcszKey, const char * lpcsz)
// {

//    if(get_db_str_set() == nullptr)
//       return false;

//    return get_db_str_set()->save(lpcszKey, lpcsz);

// }


// bool db_server::save(const char * lpKey, ::file::input_stream & istream)
// {

//    string str;

//    file::byte_input_stream is(istream);

//    is.seek_to_begin();

//    is.read_to_hex(str);

//    if(!save(lpKey, str))
//       return false;

//    return true;

// }


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




