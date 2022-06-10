#include "framework.h"
#include "base/net/net_sockets.h"


class CLASS_DECL_AURA db_long_set_item
{
public:

   ::duration m_durationTimeout;
   i64        m_l;

};

class CLASS_DECL_AURA db_long_set_queue_item:
   virtual public matter
{
public:

   string         m_strKey;
   ::duration m_durationTimeout;
   i64        m_l;

   db_long_set_queue_item() {}
   db_long_set_queue_item(const db_long_set_queue_item & item){ operator =(item); }
   virtual ~db_long_set_queue_item() {}


   db_long_set_queue_item & operator = (const db_long_set_queue_item & item)
   {
      if(this != &item)
      {
         m_strKey = item.m_strKey;
         m_durationTimeout = item.m_durationTimeout;
         m_l = item.m_l;
      }
      return *this;
   }

};



class CLASS_DECL_AURA db_long_set_core:
   public db_set
{
public:


   ::mutex                                     m_mutex;
   sockets::socket_handler                   m_handler;
   sockets::http_session *                   m_phttpsession;


   string_map < db_long_set_item >           m_map;
   bool                                      m_bIndexed;

   ::mysql::database *                       m_pmysqldbUser;
   string                                    m_strUser;

   class db_long_sync_queue *                m_pqueue;

   db_long_set_core(db_server * pserver):
      matter(pserver->get_app()),
      db_set(pserver,"integertable"),
      m_handler(this),
      
      m_phttpsession(nullptr),
      m_pqueue(nullptr),
      m_pmysqldbUser(pserver->m_pmysqldbUser),
      m_strUser(pserver->m_strUser)
   {



   }

   virtual ~db_long_set_core() {}

};


class CLASS_DECL_AURA db_long_sync_queue:
   public ::thread
{
public:


   ::mutex                                                    m_mutex;
   db_long_set *                                            m_ppropertyset;
   sockets::socket_handler                                  m_handler;
   sockets::http_session *                                  m_phttpsession;

   pointer_array < db_long_set_queue_item >           m_itema;

   db_long_sync_queue(::object * pobject):
      ::object(pobject),
      thread(pobject),
      ::thread(pobject),
      m_handler(pobject),
      
      m_phttpsession(nullptr)
   {}

   virtual ~db_long_sync_queue() {}



   virtual i32 run();


   void queue(const ::string & pszKey,i64 l);

};


i32 db_long_sync_queue::run()
{

   while(true)
   {

repeat:;

       {

          single_lock synchronouslock(&m_mutex);

          if(m_itema.get_size() <= 0)
          {
             sleep(2000_ms);
             goto repeat;
          }

          for(i32 i = 1; i < m_itema.get_size(); i++)
          {
             if(m_itema[i]->m_strKey == m_itema[0]->m_strKey)
             {
                m_itema.erase_at(0);
                goto repeat;
             }
          }


          property_set set;

          string strUrl;

          set["interactive_user"] = true;

          strUrl = "https://" + pcontext->m_papexcontext->dir().get_api_cc() + "/account/long_set_save?key=";
          strUrl += purl->url_encode(m_itema[0]->m_strKey);
          strUrl += "&value=";
          strUrl += __string(m_itema[0]->m_l);

          m_itema.erase_at(0);

          synchronouslock.unlock();

          set["user"] = psession->account()->get_user();

          m_phttpsession = pcontext->m_papexcontext->http().request( m_phttpsession, strUrl, set);

          if(m_phttpsession == nullptr || ::http::status_failed(set["get_status"]))
          {
             sleep(2000_ms);
             goto repeat;
          }


       }


   }

}

void db_long_sync_queue::queue(const ::string & pszKey,i64 l)
{

   single_lock synchronouslock(&m_mutex, true);

   db_long_set_queue_item item;

   item.m_strKey = pszKey;
   item.m_l = l;

   m_itema.add(new db_long_set_queue_item(item));

}


db_long_set::db_long_set(db_server * pserver):
matter(pserver->get_app())
{

   m_pcore = new db_long_set_core(pserver);

}

db_long_set::~db_long_set()
{

   ::acme::del(m_pcore);

}

// Adiciona na matriz System nomes dos diretrios de imagens.
bool db_long_set::load(const ::string & lpKey, i64 * plValue)
{

   if(m_pcore->m_pdataserver->m_bRemote)
   {

      db_long_set_item longitem;

      if(m_pcore->m_map.lookup(lpKey,longitem) && longitem.m_durationTimeout > ::get_tick())
      {
         *plValue = longitem.m_l;
         return true;
      }




      property_set set;

      string strUrl;

      set["interactive_user"] = true;

      strUrl = "https://" + pcontext->m_papexcontext->dir().get_api_cc() + "/account/long_set_load?key=";
      strUrl += purl->url_encode(lpKey);

      //m_phttpsession = pcontext->m_papexcontext->http().request(m_handler, m_phttpsession, strUrl, post, headers, set, nullptr, psession->account()->get_user(), nullptr, &estatus);
      m_pcore-> m_phttpsession = pcontext->m_papexcontext->http().request(m_pcore->m_phttpsession,strUrl,set);

      if(m_pcore->m_phttpsession == nullptr || ::http::status_failed(set["get_status"]))
      {
         return false;
      }

      *plValue = ::str().to_i64(string((const ::string &)m_pcore->m_phttpsession->m_memoryfile.get_memory()->get_data(),m_pcore->m_phttpsession->m_memoryfile.get_memory()->get_size()));

      longitem.m_durationTimeout= ::duration::now() + 23 * (5000);
      longitem.m_l = *plValue;

      m_pcore->m_map.set_at(lpKey,longitem);
      return true;

   }
#ifndef _UWP
   else if(m_pcore->m_pmysqldbUser != nullptr)
   {

      try
      {

         *plValue = m_pcore->m_pmysqldbUser->query_item("SELECT `value` FROM fun_user_str_set WHERE user = '" + m_pcore->m_strUser + "' AND `key` = '" + m_pcore->m_pmysqldbUser->escape(lpKey) + "'").int32();

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
         "select value FROM integertable WHERE atom = '%s';",
         strKey);


      slDatabase.lock();
      //try
      {
         m_pcore->m_pdataset->query(strSql);
      }
      //catch(...)
      {
         // return false;
      }

      if(m_pcore->m_pdataset->num_rows() <= 0)
         return false;

      *plValue = m_pcore->m_pdataset->fv("value");

      return true;

   }


}

bool db_long_set::save(const ::string & lpKey, i64 lValue)
{

   if(m_pcore->m_pdataserver->m_bRemote)
   {

      if(m_pcore->m_pqueue == nullptr)
      {

         m_pcore->m_pqueue = new db_long_sync_queue(this);
         m_pcore->m_pqueue->m_ppropertyset = this;
         m_pcore->m_pqueue->begin();

      }

      m_pcore->m_pqueue->queue(lpKey,lValue);

      db_long_set_item longitem;

      longitem.m_durationTimeout= ::duration::now() + 23 * (5000);
      longitem.m_l = lValue;

      m_pcore->m_map.set_at(lpKey,longitem);

      return true;

   }
#ifndef _UWP
   else if(m_pcore->m_pmysqldbUser != nullptr)
   {

      string strSql = "REPLACE INTO fun_user_long_set VALUE('" + m_pcore->m_strUser + "', '" + m_pcore->m_pmysqldbUser->escape(lpKey) + "', " + __string(lValue) + ")";

      TRACE(strSql);

      return m_pcore->m_pmysqldbUser->query(strSql) != nullptr;

   }
#endif
   else
   {
      single_lock slDatabase(m_pcore->db()->get_database()->mutex());
      string strKey;
      strKey = lpKey;
      strKey.replace("'", "''");


      __pointer(::sqlite::database) pdb   = m_pcore->db()->get_database();
      string strSql;
      i64 l;
      slDatabase.lock();
      if(load(lpKey, &l))
      {
         strSql.format(
            "UPDATE integertable SET value = '%d' WHERE atom = '%s';",
            lValue,
            strKey);

         try
         {
            pdb->start_transaction();
            m_pcore->m_pdataset->exec(strSql);
            pdb->commit_transaction();
         }
         catch(...)
         {
            pdb->rollback_transaction();
            return false;
         }
      }
      else
      {

         strSql.format(
            "INSERT INTO integertable (atom, value) values ('%s', '%d');",
            strKey,
            lValue);



         try
         {
            pdb->start_transaction();
            m_pcore->m_pdataset->exec(strSql);
            pdb->commit_transaction();
         }
         catch(...)
         {
            pdb->rollback_transaction();
            return false;
         }
      }

      return true;
   }

}

bool db_long_set::find(const ::string & lpKey)
{
   __UNREFERENCED_PARAMETER(lpKey);
   /*    single_lock synchronouslock(&m_CriticalSection, true);
   HRESULT hr;
   if(m_bIndexed)
   {
   //         TRACE("CSongsSet::FindKey Seeking\n");
   string strSection(lpSection);
   string strKey(lpKey);
   if(FAILED(hr = MoveFirst()))
   {
   AddOLEDBException(m_spCommand, IID_IRowsetChange);
   }
   if(hr == DB_S_ENDOFROWSET)
   {
   return false;
   }
   if(FAILED(get_data(0)))
   {
   AddOLEDBException(m_spCommand, IID_IRowsetChange);
   }
   if(strSection.compare_ci(m_Section) == 0 &&
   strKey.compare_ci(m_Key) == 0)
   {
   return true;
   }
   CDBLongRow l;
   _tcscpy(l.m_Section , lpSection);
   _tcscpy(l.m_Key , lpKey);
   ReleaseRows();
   hr = m_spRowsetIndex->seek(
   m_pAccessor->GetHAccessor(0),
   2,
   &l,
   DBSEEK_FIRSTEQ);
   if(FAILED(hr))
   return false;
   HROW* phRow = &m_hRow;
   ULONG ulRowsFetched = 0;
   hr = m_spRowset->GetNextRows(nullptr, 0, 1, &ulRowsFetched, &phRow);
   if (hr != S_OK)
   return false;
   hr = get_data();
   if(FAILED(hr))
   return false;
   return true;
   }
   else
   {
   string strSection(lpSection);
   string strKey(lpKey);
   if(FAILED(hr = MoveFirst()))
   {
   AddOLEDBException(m_spCommand, IID_IRowsetChange);
   }
   if(hr == DB_S_ENDOFROWSET)
   {
   return false;
   }
   while(true)
   {
   if(FAILED(get_data(0)))
   {
   AddOLEDBException(m_spCommand, IID_IRowsetChange);
   }
   if(strSection.compare_ci(m_Section) == 0 &&
   strKey.compare_ci(m_Key) == 0)
   {
   return true;
   }
   if(FAILED(hr = MoveNext()))
   {
   AddOLEDBException(m_spCommand, IID_IRowsetChange);
   }
   if(hr == DB_S_ENDOFROWSET)
   {
   return false;
   }
   }
   }*/
   return false;
}


bool db_long_set::load(const ::string & lpKey, RECTANGLE_I32 * lpRect)
{

   ::rectangle_i32 rectangle;

   string strKey = lpKey;

   if(!load(strKey + ".left", rectangle.left))
      return false;

   if(!load(strKey + ".top", rectangle.top))
      return false;

   if(!load(strKey + ".right", rectangle.right))
      return false;

   if(!load(strKey + ".bottom", rectangle.bottom))
      return false;

   *lpRect = rectangle;

   return true;

}

//////////////////////////////
//
// Output:
// 'false' if one or more save operations has failed.
// 'true' otherwise

bool db_long_set::save(const ::string & lpKey, const RECTANGLE_I32 * lpRect)
{

   string strKey = lpKey;

   if(!save(strKey + ".left", lpRect->left))
      return false;

   if(!save(strKey + ".top", lpRect->top))
      return false;

   if(!save(strKey + ".right", lpRect->right))
      return false;

   if(!save(strKey + ".bottom", lpRect->bottom))
      return false;

   return true;

}


bool db_long_set::MoveWindow_(const ::string & lpKey, ::user::interaction_impl * pwindow)
{

   ::rectangle_i32 rectangle;

   if(!load(lpKey, &rectangle))
      return false;

   pwindow->SetPlacement(rectangle);

   return true;

}


bool db_long_set::SaveWindowRect_(const ::string & lpKey, ::user::interaction_impl * pwindow)
{

#ifdef WINDOWS_DESKTOP

   WINDOWPLACEMENT wp;
   pwindow->GetWindowPlacement(&wp);
   return save(lpKey , &wp.rcNormalPosition);

#else

   throw ::exception(todo);

#endif

}

/*HRESULT db_long_set::OpenQuery(CDataSource *pdb, const ::string & lpcszSql)
{
CSession   session;
//      HRESULT      hr;
/*       if(m_spRowset != nullptr)
close();
if(m_spRowsetIndex != nullptr)
m_spRowsetIndex.Release();
m_bIndexed = false;

hr = session.open(*pdb);
if (FAILED(hr))
return hr;

CDBPropSet   propset(DBPROPSET_ROWSET);
propset.add_property(DBPROP_BOOKMARKS, true);
propset.add_property(DBPROP_CANFETCHBACKWARDS, true);
propset.add_property(DBPROP_IRowsetScroll, true);
propset.add_property(DBPROP_IRowsetChange, true);
propset.add_property(DBPROP_UPDATABILITY, DBPROPVAL_UP_CHANGE | DBPROPVAL_UP_INSERT | DBPROPVAL_UP_DELETE );
m_CriticalSection.lock();
hr = CCommand<CAccessor<CDBLongRow> >::open(session, lpcszSql, &propset);
m_CriticalSection.unlock();
if (FAILED(hr))
{
AddOLEDBException(session.m_spOpenRowset, IID_ICommandPrepare);
//         AddOLEDBException(session.m_spOpenRowset, IID_IRowsetChange);
}

return MoveNext(); */
/*    return S_OK;

}*/

/*HRESULT db_long_set::OpenIndexed(CDataSource *pdb)
{
//    HRESULT hr;
CSession session;
/*       if(m_spRowset != nullptr)
close();
if(m_spRowsetIndex != nullptr)
m_spRowsetIndex.Release();
try
{

hr = session.open(*pdb);
if (FAILED(hr))
{
AddOLEDBException(pdb->m_spInit, IID_IOpenRowset);
}
} catch(COLEDBException *e)
{
CDBErrorDialog dlg;
dlg.Init(e->m_spUnk, e->m_iid);
dlg.DoModal();
e->Delete();
return hr;
}
DBID    dbIdIndex;
DBID   dbIdTable;

dbIdTable.eKind = DBKIND_NAME;
dbIdTable.uName.pwszName = OLESTR("Long");

dbIdIndex.eKind = DBKIND_NAME;
dbIdIndex.uName.pwszName = OLESTR("PrimaryKey");

CDBPropSet   propset(DBPROPSET_ROWSET);
propset.add_property(DBPROP_BOOKMARKS, true);
propset.add_property(DBPROP_CANFETCHBACKWARDS, true);
propset.add_property(DBPROP_IRowsetScroll, true);
propset.add_property(DBPROP_IRowsetChange, true);
propset.add_property(DBPROP_IRowsetIndex, true);
propset.add_property(DBPROP_IRowset, true);
//        propset.add_property(DBPROP_OTHERUPDATEDELETE, true);
//        propset.add_property(DBPROP_OTHERINSERT, true);
propset.add_property(DBPROP_UPDATABILITY, DBPROPVAL_UP_CHANGE | DBPROPVAL_UP_INSERT | DBPROPVAL_UP_DELETE );


// open the Index with default properties and default interfaces. (IRowsetIndex,
// IAccessor, IRowset, IColumnsInfo, IRowsetInfo).
//CComPtr<IRowsetIndex> spIndex ;
try
{

hr = session.m_spOpenRowset->OpenRowset(
nullptr,
&dbIdTable,
&dbIdIndex,
IID_IRowset,
1,
&propset,
(IUnknown**) &m_spRowset);
if (FAILED(hr))
{
AddOLEDBException(session.m_spOpenRowset, IID_IOpenRowset);
return hr;
}
hr = Bind();
if(FAILED(hr))
return hr;
CComPtr<IRowsetIndex> spRowsetIndex;
hr = m_spRowset->QueryInterface(&spRowsetIndex);
if(FAILED(hr))
return hr;
// Sets the range to the entire index.
hr = spRowsetIndex->SetRange(
m_pAccessor->GetHAccessor(0),
0,
nullptr,
0,
nullptr,
0);
if(FAILED(hr))
return hr;
SetupOptionalRowsetInterfaces();
hr = m_spRowset->QueryInterface(&m_spRowsetIndex);
if(FAILED(hr))
return hr;

m_bIndexed = true;

} catch(COLEDBException *e)
{
CDBErrorDialog dlg;
dlg.Init(e->m_spUnk, e->m_iid);
dlg.DoModal();
e->Delete();
return hr;
}*/

//return MoveNext();
//  return S_OK;

//}

bool db_long_set::SetWindowPlacement(const ::string & lpKey, ::user::interaction_impl * pwindow)
{

#ifdef WINDOWS_DESKTOP

   WINDOWPLACEMENT wp;
   if(!load(lpKey , &wp.rcNormalPosition))
      return false;

   string strKey;
   strKey = lpKey;
   strKey += ".ptMinPosition";
   if(!load(strKey, &wp.ptMinPosition))
      return false;
   strKey = lpKey;
   strKey += ".ptMaxPosition";
   if(!load(strKey, &wp.ptMaxPosition))
      return false;
   strKey = lpKey;
   strKey += ".showCmd";
   if(!load(strKey, (i32 &) wp.showCmd))
      return false;
   strKey = lpKey;
   strKey += ".flags";
   if(!load(strKey, (i32 &) wp.flags))
      return false;
   pwindow->SetWindowPlacement(&wp);
   return true;

#else

   throw ::exception(todo);

#endif

}

bool db_long_set::SaveWindowPlacement(const ::string & lpKey, ::user::interaction_impl * pwindow)
{

#ifdef WINDOWS_DESKTOP

   WINDOWPLACEMENT wp;
   pwindow->GetWindowPlacement(&wp);
   if(!save(lpKey , &wp.rcNormalPosition))
      return false;
   string strKey;
   strKey = lpKey;
   strKey += ".ptMinPosition";
   if(!save(strKey, &wp.ptMinPosition))
      return false;
   strKey = lpKey;
   strKey += ".ptMaxPosition";
   if(!save(strKey, &wp.ptMaxPosition))
      return false;
   strKey = lpKey;
   strKey += ".showCmd";
   if(!save(strKey, (i32) wp.showCmd))
      return false;
   strKey = lpKey;
   strKey += ".flags";
   if(!save(strKey, (i32) wp.flags))
      return false;

   return true;

#else

   throw ::exception(todo);

#endif

}


#ifdef WINDOWS_DESKTOP


bool db_long_set::save(const ::string & lpKey, WINDOWPLACEMENT & wp)
{

   if(!save(lpKey , &wp.rcNormalPosition))
      return false;
   string strKey;
   strKey = lpKey;
   strKey += ".ptMinPosition";
   if(!save(strKey, &wp.ptMinPosition))
      return false;
   strKey = lpKey;
   strKey += ".ptMaxPosition";
   if(!save(strKey, &wp.ptMaxPosition))
      return false;
   strKey = lpKey;
   strKey += ".showCmd";
   if(!save(strKey, (i32) wp.showCmd))
      return false;
   strKey = lpKey;
   strKey += ".flags";
   if(!save(strKey, (i32) wp.flags))
      return false;

   return true;

}

bool db_long_set::load(const ::string & lpKey, WINDOWPLACEMENT & wp)
{

   load(lpKey , &wp.rcNormalPosition);

   string strKey;
   strKey = lpKey;
   strKey += ".ptMinPosition";
   load(strKey, &wp.ptMinPosition);
   strKey = lpKey;
   strKey += ".ptMaxPosition";
   load(strKey, &wp.ptMaxPosition);
   strKey = lpKey;
   strKey += ".showCmd";
   load(strKey, (i32 &) wp.showCmd);
   strKey = lpKey;
   strKey += ".flags";
   load(strKey, (i32 &) wp.flags);

   return true;
}


#endif



bool db_long_set::load(const ::string & lpKey, POINT_I32 * lpPoint)
{

   ::point_i32 point;

   string strKey = lpKey;

   if(!load(strKey + ".x", point.x))
      return false;

   if(!load(strKey + ".y", point.y))
      return false;

   *lpPoint = point;

   return true;

}

bool db_long_set::save(const ::string & lpKey, POINT_I32 * lpPoint)
{

   string strKey = lpKey;

   if(!save(strKey + ".x", lpPoint->x))
      return false;

   if(!save(strKey + ".y", lpPoint->y))
      return false;

   return true;

}


