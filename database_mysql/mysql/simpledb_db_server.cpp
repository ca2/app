#include "framework.h"

#include "db_str_set.h"


int g_idbchange;


db_server::db_server(::particle * pparticle) :
   ::object(pparticle)
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




bool db_server::initialize_user(mysql::database * pmysqldbUser, const ::scoped_string & scopedstrUser)
{

   if(pmysqldbUser == nullptr)
      return false;

   m_bRemote         = false;

   m_pmysqldbUser    = pmysqldbUser;
   m_strUser         = pszUser;

   m_plongset        = ___new db_long_set(this);
   m_pstrset         = ___new db_str_set(this);

   if(!create_message_queue())
      return false;

   m_bWorking = true;

   return true;

}


bool db_server::initialize()
{

   if(psystem->m_varTopicQuery["app"] == "app-core/netnode_desktop"
   || psystem->m_varTopicQuery["app"] == "app-core/netnode_dynamic_web_server"
   || psystem->m_varTopicQuery["app"] == "app-core/netnode_dynamic_web_server_cfg"
   || psystem->m_varTopicQuery["app"] == "app-core/netnodecfg"
   || psystem->m_varTopicQuery["app"] == "app-core/mydns"
   || psystem->m_varTopicQuery["app"] == "app-gtech/sensible_netnode"
   || psystem->m_varTopicQuery["app"] == "app-gtech/sensible_service"
   || psystem->has_property("no_remote_simpledb"))
   {

      m_bRemote = false;

   }

   m_pdb          = ___new ::sqlite::database (this);

   string str;

   str = directory()->userappdata("database.sqlite");

   directory()->create(directory()->name(str));

   m_pdb->setDatabase(str);

   m_pdb->connect();

   m_pdb->create_long_set("integertable");

   m_pdb->create_string_set("stringtable");

   m_plongset     = ___new db_long_set(this);

   m_pstrset      = ___new db_str_set(this);

   int iBufferSize = 128 * 1024;

   ::pointer<::handler>commandthread = psystem->handler();

   if(commandthread->has_property("filesizebuffer"))
   {

      iBufferSize = commandthread->m_varTopicQuery["filesizebuffer"] * 1024 * 1024;

   }

#if !defined(UNIVERSAL_WINDOWS) && !defined(APPLEOS)

   if(!create_message_queue())
      return false;

#endif

   m_bWorking = true;

   return true;

}


bool db_server::destroy()
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

      //set_timer(1258477, 484, nullptr);

      ////MESSAGE_LINK(e_message_timer, m_pimpl, this, &db_server::on_timer);

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

void db_server::on_timer(::timer * ptimer)
{

   super::on_timer(ptimer);;

   if(ptimer->m_uTimer == 1258477)
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


// bool db_server::data_server_load(::database::client * pclient, ::database::key atom, ::file::output_stream & writable, ::update * pupdate)
// {

//    __UNREFERENCED_PARAMETER(pparticle);

//    if(!load(calc_data_key(pclient,atom),writable))
//       return false;

//    return true;

// }


// bool db_server::data_server_save(::database::client * pclient, ::database::key atom, ::file::input_stream & readable, ::update * pupdate)
// {

//    __UNREFERENCED_PARAMETER(pparticle);

//    if(!save(calc_data_key(pclient,atom),readable))
//       return false;

//    return true;

// }


// bool db_server::load(const ::scoped_string & scopedstrKey, string & str)
// {

//    if(get_db_str_set() == nullptr)
//       return false;

//    return get_db_str_set()->load(lpcszKey, str);

// }



// bool db_server::load(const ::string & lpKey, ::file::output_stream & ostream)
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


// bool db_server::save(const ::scoped_string & scopedstrKey, const ::scoped_string & scopedstr)
// {

//    if(get_db_str_set() == nullptr)
//       return false;

//    return get_db_str_set()->save(lpcszKey, lpcsz);

// }


// bool db_server::save(const ::string & lpKey, ::file::input_stream & istream)
// {

//    string str;

//    file::byte_input_stream is(istream);

//    is.seek_to_begin();

//    is.read_to_hex(str);

//    if(!save(lpKey, str))
//       return false;

//    return true;

// }


::pointer<::sqlite::database>db_server::get_database()
{

   return m_pdb;

}


bool db_server::data_pulse_change(::database::client * pclient, ::database::key atom, ::update * pupdate)
{

   return ::database::server::data_pulse_change(pclient, atom, pupdate);

}


void db_server::assert_ok() const
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




