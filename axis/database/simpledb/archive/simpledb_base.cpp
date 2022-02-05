#include "framework.h"


namespace simpledb
{


   database::database(::object * pobject) :
      ::object(pobject),
      m_spfileMeta(pobject),
      m_xmldocumentMeta(pobject)
   {

   }


   i32 database::connect()
   {
      string strMetaPath;

      strMetaPath = pcontext->m_papexcontext->dir().install() / "database" / db/ "meta.xml";

      try
      {
         if(!m_spfileMeta->open(strMetaPath, ::file::e_open_binary | ::file::e_open_read_write | ::file::e_open_share_exclusive))
            return DB_ERROR;
      }
      catch(...)
      {
         strMetaPath = pcontext->m_papexcontext->dir().appdata() / "database" / db / "meta.xml";
         try
         {
            if(!m_spfileMeta->open(strMetaPath, ::file::e_open_binary | ::file::e_open_read_write | ::file::e_open_share_exclusive))
               return DB_ERROR;
         }
         catch(...)
         {
            return DB_ERROR;
         }
      }

      reader is(m_spfileMeta);

      if(!m_xmldocumentMeta.load(is))
         return DB_ERROR;

      return DB_COMMAND_OK;

   }


   table * database::get_table(const ::string & pszName)
   {
      table * ptable = nullptr;
      string strName(pszName);
      strName.make_lower();
      if(!m_mapTable.lookup(strName, ptable))
      {
         ptable = create_table(strName);
         m_mapTable.set_at(strName, ptable);
      }
      return ptable;
   }

   table * database::create_table(const ::string & pszName)
   {
      return new table(this, pszName);
   }

   ::simpledb::dataset * database::create_dataset()
   {
      return new ::simpledb::dataset(const_cast < ::simpledb::database * > (this));
   }


   class ::database::dataset * database::create_dataset()
   {
      return create_dataset();
   }

   i32 database::setErr(i32 err_code)
   {
      m_iErrorCode = err_code;
      return m_iErrorCode;
   }


   long database::nextid(const ::string & sname)
   {
      __UNREFERENCED_PARAMETER(sname);
      if (!active)
         return DB_UNEXPECTED_RESULT;
      /*i32 atom;
      database::result_set res;
      char sqlcmd[512];
      sprintf(sqlcmd,"select nextid from %s where seq_name = '%s'",sequence_table, sname);
      if(last_err = sqlite3_exec((::sqlite3::sqlite3 *) getHandle(),sqlcmd,&callback,&res,nullptr) != SQLITE_OK)
      {
         return DB_UNEXPECTED_RESULT;
      }
      if (res.records.get_size() == 0)
      {
         atom = 1;
         sprintf(sqlcmd,"insert into %s (nextid,seq_name) values (%d,'%s')",sequence_table,atom,sname);
         if (last_err = sqlite3_exec((::sqlite3::sqlite3 *) conn,sqlcmd,nullptr,nullptr,nullptr) != SQLITE_OK) return DB_UNEXPECTED_RESULT;
         return atom;
      }
      else
      {
         atom = res.records[0][0].i32()+1;
         sprintf(sqlcmd,"update %s dataset nextid=%d where seq_name = '%s'",sequence_table,atom,sname);
         if (last_err = sqlite3_exec((::sqlite3::sqlite3 *) conn,sqlcmd,nullptr,nullptr,nullptr) != SQLITE_OK) return DB_UNEXPECTED_RESULT;
         return atom;
      }*/
      return DB_UNEXPECTED_RESULT;
   }

} // namespace simpledb
