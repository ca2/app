#include "framework.h"


im_post::im_post(db_server * pserver) :
   db_set(pserver, "im_post")
{

   ::pointer<::sqlite::database>pdb = db()->get_database();

   single_lock slDatabase(pdb->mutex());

   ::pointer<::sqlite::dataset> pds = (::pointer<::sqlite::dataset>pdb->create_dataset();

   pdb->start_transaction();

   pds->query("select * from sqlite_master where type like 'table' and name like 'im_post'");

   if (pds->num_rows()==0)
   {

      if(!pds->exec("create table im_post (sender integer, recipient integer, `name` text, sent integer, send_time text, `index` integer, message text, PRIMARY KEY (sender, send_time, `index`))"))
      {

         pdb->rollback_transaction();

         return;

      }

      pdb->commit_transaction();

   }

   m_pdataset = pds;

}


im_post::~im_post()
{
}

bool im_post::write(::payload rec)
{

   ::pointer<::sqlite::database>pdb = db()->get_database();

   single_lock slDatabase(pdb->mutex());

   string strMessage;

   strMessage = rec["message"];

   strMessage.replace("'", "''");

   string strSql;

   strSql.format("insert into im_post (`sender`, `recipient`, `name`, `sent`, `send_time`, `index`, `message`) VALUES ('%s', '%s','%s', '%s', '%s', '%s', '%s');",
                 rec["sender"].get_string(),
                 rec["recipient"].get_string(),
                 rec["name"].get_string(),
                 rec["sent"].get_string(),
                 rec["send_time"].get_string(),
                 rec["index"].get_string(),
                 strMessage);

   slDatabase.lock();

   pdb->start_transaction();

   if(!m_pdataset->exec(strSql))
   {

      pdb->rollback_transaction();

      return false;

   }

   pdb->commit_transaction();

   return true;

}


::payload im_post::get_since(::payload rec)
{

   ::pointer<::sqlite::database>pdb = db()->get_database();

   single_lock slDatabase(pdb->mutex());

   string strSql;

   strSql.format(
   "select * FROM im_post WHERE ((sender = '%s' AND recipient = '%s') OR (sender = '%s' AND recipient = '%s')) AND ((send_time > '%s') OR ((send_time == '%s') AND ('index' > '%s'))) ORDER BY `send_time` ASC, `index` ASC",
   rec["sender"].get_string(),
   rec["recipient"].get_string(),
   rec["recipient"].get_string(),
   rec["sender"].get_string(),
   rec["send_time"].get_string(),
   rec["send_time"].get_string(),
   rec["index"].get_string());

   slDatabase.lock();

   try
   {

      m_pdataset->query(strSql);

   }
   catch(...)
   {

      return false;

   }

   ::count iNumRows = m_pdataset->num_rows();

   if(iNumRows <= 0)
      return false;

   class ::payload payload;

   while(!m_pdataset->eof())
   {

      payload.payloada().add(current());

      m_pdataset->next();

   }

   return ::payload;

}

::payload im_post::last(::payload user1, ::payload user2)
{

   if(m_pdataserver == nullptr)
      return false;

   ::pointer<::sqlite::database>pdb = db()->get_database();

   single_lock slDatabase(pdb->mutex());

   string strSql;

   strSql.format(
   "select * FROM im_post WHERE ((sender = '%s' AND recipient = '%s') OR (sender = '%s' AND recipient = '%s')) ORDER BY `send_time` DESC, `index` DESC LIMIT 1",
   user1.get_string(),
   user2.get_string(),
   user2.get_string(),
   user1.get_string());

   slDatabase.lock();

   try
   {

      m_pdataset->query(strSql);

   }
   catch(...)
   {

      return false;

   }

   if(m_pdataset->num_rows() <= 0)
      return false;

   m_pdataset->first();

   return current();

}


::payload im_post::current()
{

   ::payload ret;

   ret.set_type(::e_type_property_set);
   ret["sender"]     = m_pdataset->fv("sender");
   ret["recipient"]  = m_pdataset->fv("recipient");
   ret["sent"]       = m_pdataset->fv("sent");
   ret["send_time"]  = m_pdataset->fv("send_time");
   ret["index"]      = m_pdataset->fv("index");
   string strMessage = m_pdataset->fv("message");
   ret["message"]    = strMessage;

   return ret;

}













































