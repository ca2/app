#include "framework.h"
#include "base/net/net_sockets.h"
#include "db_str_set.h"


class CLASS_DECL_AURA db_str_set_item
{
public:


   ::time m_timeTimeout;
   string            m_str;


};


class CLASS_DECL_AURA db_str_set_queue_item:
   virtual public matter
{
public:

   string            m_strKey;
   ::time m_timeTimeout;
   string            m_str;


   db_str_set_queue_item() {}
   db_str_set_queue_item(const db_str_set_queue_item & item){ operator =(item); }
   virtual ~db_str_set_queue_item() {  }


   db_str_set_queue_item & operator = (const db_str_set_queue_item & item)
   {
      if(this != &item)
      {
         m_strKey = item.m_strKey;
         m_timeTimeout = item.m_timeTimeout;
         m_str = item.m_str;
      }
      return *this;
   }



};


class CLASS_DECL_AURA db_str_set_core:
   virtual public ::db_set
{
public:


   ::pointer < ::mutex >                                        m_pmutex;
   sockets::socket_handler                      m_handler;
   sockets::http_session *                      m_phttpsession;
   string_map < db_str_set_item >               m_map;
   bool                                         m_bIndexed;
   ::mysql::database *                          m_pmysqldbUser;
   string                                       m_strUser;

   class db_str_sync_queue *                    m_pqueue;




   db_str_set_core(db_server * pserver):
      matter(pserver->get_app()),
      db_set(pserver,"stringtable"),
      m_handler(this),
      
      m_phttpsession(nullptr),
      m_pqueue(nullptr),
      m_pmysqldbUser(pserver->m_pmysqldbUser),
      m_strUser(pserver->m_strUser)
   {


   }

   ~db_str_set_core()
   {

   }


};


class CLASS_DECL_AURA db_str_sync_queue:
   public ::thread
{
public:

   ::pointer < ::mutex >                                              m_pmutex;
   db_str_set *                                       m_ppropertyset;
   sockets::socket_handler                            m_handler;
   sockets::http_session *                            m_phttpsession;

   pointer_array < db_str_set_queue_item >      m_itema;


   db_str_sync_queue(::particle * pparticle):
      ::object(pparticle),
      thread(pparticle),
      ::thread(pparticle),
      m_handler(pparticle),
      
      m_phttpsession(nullptr)
   { }

   virtual ~db_str_sync_queue() {}


   virtual i32 run();

   void queue(const ::string & pszKey, const ::string & psz);

};






i32 db_str_sync_queue::run()
{

   single_lock synchronouslock(m_pmutex, false);

   m_bRun = true;

   try
   {

      while(task_get_run())
      {

repeat:;

      if(!task_get_run())
         break;
       {

          synchronouslock.lock();

          if(m_itema.get_size() <= 0)
          {
             synchronouslock.unlock();
             sleep(2000_ms);
             goto repeat;
          }

          if(psession->account()->m_puser == nullptr)
          {
             synchronouslock.unlock();
             sleep(5000_ms);
             goto repeat;
          }

          for(i32 i = 1; i < m_itema.get_size(); i++)
          {
             if(m_itema[i]->m_strKey == m_itema[0]->m_strKey)
             {
                m_itema.erase_at(0);
                synchronouslock.unlock();
                goto repeat;
             }
          }

          try
          {


             property_set set;

             string strUrl;

             set["interactive_user"] = true;




             strUrl = "https://" + dir()->get_api_cc() + "/account/str_set_save?key=";
             strUrl += ::url::encode(m_itema[0]->m_strKey);
             strUrl += "&value=";
             strUrl += ::url::encode(m_itema[0]->m_str);

             m_itema.erase_at(0);

             synchronouslock.unlock();

             set["user"] = psession->account()->get_user();

             m_phttpsession = pcontext->m_papexcontext->http().request(m_phttpsession, strUrl, set);

             if(m_phttpsession == nullptr || ::http::status_failed(set["get_status"]))
             {
                sleep(2000_ms);
                dir()->m_strApiCc = "";
                goto repeat;
             }

          }
          catch(...)
          {
          }

          synchronouslock.unlock();

       }


      }
   }
   catch(...)
   {
   }
   m_ppropertyset->m_pcore->m_pqueue = nullptr;
   return 0;
}


void db_str_sync_queue::queue(const ::string & pszKey, const ::string & psz)
{

   single_lock synchronouslock(m_pmutex, true);

   ::pointer<db_str_set_queue_item>item(memory_new db_str_set_queue_item);

   item->m_strKey = pszKey;
   item->m_str = psz;

   m_itema.add(item);

}


db_str_set::db_str_set(db_server * pserver):
matter(pserver->get_app()),
m_pmutex(pserver->get_app())
{

   m_pcore = memory_new db_str_set_core(pserver);

}

db_str_set::~db_str_set()
{

   ::acme::del(m_pcore);

}




// true if deleted
bool db_str_set::erase(const ::string & lpKey)
{
   __UNREFERENCED_PARAMETER(lpKey);
   return false;
}

bool db_str_set::load(const ::string & lpKey, string & strValue)
{

   if(m_pcore->m_pdataserver == nullptr)
      return false;

   if(m_pcore->m_pdataserver->m_bRemote && string(lpKey).find("&data_source=local&") < 0)
   {

      papp->assert_user_logged_in();

      synchronous_lock synchronouslock(m_pmutex);

      if(m_pcore->m_phttpsession == nullptr)
      {

         m_pcore->m_phttpsession = psession->account()->m_mapFontopusSession[psession->account()->m_strFirstFontopusServer];

      }

      db_str_set_item stritem;

      if(m_pcore->m_map.lookup(lpKey,stritem) && stritem.m_timeTimeout > ::get_tick())
      {
         strValue = stritem.m_str;
         return true;
      }

      single_lock slDatabase(m_pcore->db()->get_database()->mutex(),true);

      property_set set;

      set["interactive_user"] = true;

      string strUrl;

      strUrl = "https://" + dir()->get_api_cc() + "/account/str_set_load?key=";

      strUrl += ::url::encode(lpKey);

      set["user"] = psession->account()->get_user();

      set["get_response"] = "";

      m_pcore->m_phttpsession = pcontext->m_papexcontext->http().request(m_pcore->m_phttpsession,strUrl,set);

      if(m_pcore->m_phttpsession == nullptr || ::http::status_failed(set["get_status"]))
      {
         return false;
      }

      strValue = set["get_response"];

      stritem.m_timeTimeout= ::time::now() + 23 * (5000);
      stritem.m_str = strValue;

      m_pcore->m_map.set_at(lpKey,stritem);


   }
#ifndef UNIVERSAL_WINDOWS
   else if(m_pcore->m_pmysqldbUser != nullptr)
   {

      try
      {

         strValue = m_pcore->m_pmysqldbUser->query_item("SELECT `value` FROM fun_user_str_set WHERE user = '" + m_pcore->m_strUser + "' AND `key` = '" + m_pcore->m_pmysqldbUser->escape(lpKey) + "'");

         return true;

      }
      catch(...)
      {
      }

      return false;

   }
#endif
   else
   {
      single_lock slDatabase(m_pcore->db()->get_database()->mutex());

      string strKey;
      strKey = lpKey;
      strKey.replace("'", "''");

      string strSql;
      strSql.format(
         "select value FROM stringtable WHERE atom = '%s';",
         strKey);


      slDatabase.lock();
      try
      {
         m_pcore->m_pdataset->query(strSql);
      }
      catch(...)
      {
         return false;
      }

      if(m_pcore->m_pdataset->num_rows() <= 0)
         return false;

      strValue = m_pcore->m_pdataset->fv("value");

   }

   return true;
}

bool db_str_set::save(const ::string & lpKey, const ::string & lpcsz)
{

   if(m_pcore->m_pdataserver == nullptr)
      return false;

   if(!m_pcore->m_pdataserver->m_bRemote || string(lpKey).find("&data_source=local&") >= 0)
   {
      if(m_pcore->db() == nullptr)
         return false;
      single_lock slDatabase(m_pcore->db()->get_database()->mutex());

      string strKey;
      strKey = lpKey;
      strKey.replace("'", "''");

      string strValue(lpcsz);
      strValue.replace("'", "''");

      ::pointer<::sqlite::database>pdb   = m_pcore->db()->get_database();
      string strSql;
      string str;
      slDatabase.lock();
      if(load(lpKey, str))
      {
         strSql.format(
            "UPDATE stringtable SET value = '%s' WHERE atom = '%s';",
            strValue,
            strKey);

         pdb->start_transaction();
         if(!m_pcore->m_pdataset->exec(strSql))
         {
            pdb->rollback_transaction();
            return false;
         }
         pdb->commit_transaction();
      }
      else
      {

         strSql.format(
            "INSERT INTO stringtable (atom, value) values ('%s', '%s');",
            strKey,
            strValue);

         pdb->start_transaction();
         if(!m_pcore->m_pdataset->exec(strSql))
         {
            pdb->rollback_transaction();
            return false;
         }
         pdb->commit_transaction();
      }
      return true;
   }
#ifdef HAVE_MYSQL
   else if(m_pcore->m_pmysqldbUser != nullptr)
   {

      string strSql = "REPLACE INTO fun_user_str_set PAYLOAD('" + m_pcore->m_strUser + "', '" + m_pcore->m_pmysqldbUser->escape(lpKey) + "', '" + m_pcore->m_pmysqldbUser->escape(lpcsz) + "')";

      information(strSql);

      return m_pcore->m_pmysqldbUser->query(strSql) != nullptr;

   }
#endif
   else
   {


      if(m_pcore->m_pqueue == nullptr)
      {

         m_pcore->m_pqueue = memory_new db_str_sync_queue(this);
         m_pcore->m_pqueue->m_ppropertyset = this;
         m_pcore->m_pqueue->begin();

      }


      m_pcore->m_pqueue->queue(lpKey,lpcsz);

      db_str_set_item stritem;

      stritem.m_timeTimeout= ::time::now() + 23 * (5000);
      stritem.m_str = lpcsz;

      m_pcore->m_map.set_at(lpKey,stritem);


      return true;

   }

}
