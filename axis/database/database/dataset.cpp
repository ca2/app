#include "framework.h"
#include "dataset.h"
#include "database.h"
#include "field.h"


namespace database
{


   dataset::dataset(database * pdatabase)
   {

      m_pdatabase = pdatabase;
      m_bError = false;
      m_bActive = false;
      m_bAutoCommit = true;

   }


   dataset::~dataset()
   {

   }


   void dataset::set_sql(enum_sql esql, const ::scoped_string & scopedstrSql)
   {

      switch(esql)
      {

      case e_sql_none:
         break;
      case       e_sql_execute:
         m_strSqlExecute = scopedstrSql;
         break;
      case e_sql_select:
         m_strSqlSelect = scopedstrSql;
         break;
      case e_sql_update:
         m_straSqlUpdate.add(scopedstrSql);
         break;
      case e_sql_insert:
         m_straSqlInsert.add(scopedstrSql);
         break;
      case e_sql_delete:
         m_straSqlDelete.add(scopedstrSql);
         break;
      default:
         ASSERT(false);
         break;

      }

   }


   void dataset::clear_sql(enum_sql esql)
   {

      switch (esql)
      {

      case e_sql_none:
         break;
      case       e_sql_execute:
         m_strSqlExecute.empty();
         break;
      case e_sql_select:
         m_strSqlSelect.empty();
         break;
      case e_sql_update:
         m_straSqlUpdate.erase_all();
         break;
      case e_sql_insert:
         m_straSqlInsert.erase_all();
         break;
      case e_sql_delete:
         m_straSqlDelete.erase_all();
         break;
      default:
         ASSERT(false);
         break;

      }

   }

   string dataset::get_sql(enum_sql esql)
   {

      switch (esql)
      {

      case e_sql_none:
         break;
      case       e_sql_execute:
         return m_strSqlExecute;
         break;
      case e_sql_select:
         return m_strSqlSelect;
         break;
      default:
         ASSERT(false);
         break;

      }
      return "";

   }


   void dataset::parse_sql(const ::scoped_string & scopedstrSql)
   {

      string fpattern;

      string by_what;

      //m_parameterlist.set_str(sql);

      //int i;

      //for (i=0; i< m_fielda.get_size(); i++)
      //{
      //   fpattern = ":OLD_" + m_fielda[i].m_properties.name;
      //   by_what = "'" + m_fielda[i].m_value + "'";
      //   //cout << "parsing " << fpattern <<by_what<<"\n\n";
      //   sql = pars.replace(fpattern,by_what);
      //}

      //for (i=0; i< edit_object.get_size(); i++)
      //{
      //   fpattern = ":NEW_" + edit_object[i].m_properties.name;
      //   by_what = "'" + m_rowEdit[i] + "'";
      //   sql = pars.replace(fpattern,by_what);
      //}

      //   string_list_base before_array, after_array;
      //   int tag = 0;
      //   bool eol_reached = false,
      //        was_changed = false,
      //        flag = false;
      //   ExtString which_before, which_after;
      //   ExtString bef, aft, prev_before, right_side, which_field, changed_field, f_value;

      //   before_array.add(":NEW_", tag);
      //   before_array.add(":OLD_", tag);

      //   after_array.add(")", tag);
      //   after_array.add(",", tag);
      //   after_array.add(" ", tag);

      //   sq.squish();
      //   bef = sq.before_arr(before_array, which_before);

      //   while (!(bef == prev_before)) {
      //    right_side = sq.after(which_before, flag);
      //    right_side.squish();

      //    aft = right_side.after_arr(after_array, which_after);
      //         aft.squish();
      //     which_field = right_side.before(which_after);

      //    // checking whather we reach end of line
      //    if ((which_field == "\0") && (which_before != "\0")) {
      //       which_field = right_side;
      //       eol_reached = true;
      //       }

      //    // If ___new field and is in insert or edit mode - looks in edit_object
      //    if ((which_before == ":NEW_") && (which_field != "\0")) {
      //       which_field.squish();
      //                 f_value.assign(fv(which_field.getChars()));
      //       f_value.addslashes();
      //       changed_field.assign("'");
      //       changed_field + f_value + "'";
      //    }
      //    else
      //    // else looking old value in the current result dataset
      //       if ((which_before == ":OLD_") && (which_field != "\0")) {
      //       which_field.squish();
      //                 f_value.assign(f_old(which_field.getChars()));
      //       f_value.addslashes();
      //       changed_field.assign("'");
      //       changed_field + f_value + "'";
      //       }

      //    if (!eol_reached)  {

      //       sq.assign(bef + changed_field + which_after + aft);
      //       }
      //    else {
      //       if (!was_changed && (which_field != "\0")) {

      //          sq.assign(bef + changed_field + which_after + aft);
      //          was_changed = true;
      //          }
      //       }


      //    prev_before = bef;
      //    bef = sq.before_arr(before_array, which_before);

      //   }

   }


   void dataset::close()
   {
      m_bError  = false;
      m_bActive = false;
   }

   void * dataset::get_handle()
   {

      if (::is_null(m_pdatabase))
      {

         return nullptr;

      }

      return m_pdatabase->get_handle();

   }

   void dataset::insert()
   {

      for (int i=0; i<field_count(); i++)
      {

         m_row[i].set_type(::e_type_new);

         m_rowEdit[i].set_type(::e_type_new);

      }

      m_edataset = e_dataset_insert;

   }


   void dataset::edit()
   {

      if (m_edataset != e_dataset_select)
      {

         return;

      }

      m_rowEdit = m_row;

      m_edataset = e_dataset_edit;

   }


   void dataset::post()
   {
      if (m_edataset == e_dataset_insert) make_insert();
      else if (m_edataset == e_dataset_edit) make_edit();
   }


   void dataset::deletion()
   {
      if (m_edataset == e_dataset_select) make_deletion();
   }

   row * dataset::proper_row()
   {

      if (m_edataset == e_dataset_none)
      {

         return nullptr;

      }

      if (m_edataset == e_dataset_edit || m_edataset == e_dataset_insert)
      {

         return &m_rowEdit;

      }

      return &m_row;

   }


   ::payload dataset::field_value_at(::collection::index i)
   {

      auto prow = proper_row();

      if (prow == nullptr)
      {

         return error_dataset_inactive;

      }

      return prow->value_at(i);

   }


   ::collection::index dataset::field_index(const ::scoped_string & scopedstrName)
   {

      for (::collection::index i = 0; i < m_result.m_pfielda->get_count(); i++)
      {

         auto & pfield = m_result.m_pfielda->element_at(i);

         if (pfield->m_strName.case_insensitive_order(scopedstrName) == 0)
         {

            return i;

         }

      }

      return -1;

   }


   field * dataset::field(const ::scoped_string & scopedstrName)
   {

      for (auto & pfield : *m_result.m_pfielda)
      {

         if (pfield->m_strName.case_insensitive_order(scopedstrName) == 0)
         {

            return pfield;

         }

      }

      return nullptr;

   }


   ::payload dataset::field_value(const ::scoped_string & scopedstrName)
   {

      auto pfield = field(scopedstrName);

      if (::is_null(pfield))
      {

         return error_field_not_found;

      }

      return field_value_at(pfield->m_iIndex);

   }


   ::payload dataset::select_field_value(::collection::index iField)
   {

      if (m_edataset == e_dataset_none)
      {

         return error_dataset_inactive;

      }

      return m_row.value_at(iField);

   }

   //const ::payload dataset::f_old(const ::string &f_name)
   //{
   //   if (m_edataset != dataset_none)
   //   {
   //      for (int i=0; i < m_fielda.get_size(); i++)
   //      {
   //         if (m_fielda[i].m_properties.name == f_name)
   //         {
   //            return m_fielda[i].m_value;
   //         }
   //      }
   //   }
   //   return payload();
   //}



   //void dataset::setParamList(const parameter_list &params)
   //{
   //   m_parameterlist = params;
   //}


   //bool dataset::locate()
   //{
   //   bool result;
   //   if (m_parameterlist.is_empty()) return false;

   //   first();
   //   while (!eof())
   //   {
   //      result = true;
   //      for (int i=0; i < m_parameterlist.get_size(); i++)
   //         if (fv(m_parameterlist.GetKey(i)).get_string() == m_parameterlist.GetFieldValue(i).get_string())
   //         {
   //            continue;
   //         }
   //         else {result = false; break;}
   //      if (result) { return result;}
   //      next();
   //   }
   //   return false;
   //}

   //bool dataset::locate(const parameter_list &params)
   //{
   //   m_parameterlist = params;
   //   return locate();
   //}

   //bool dataset::findNext()
   //{
   //   bool result;
   //   if (m_parameterlist.is_empty()) return false;

   //   while (!eof())
   //   {
   //      result = true;
   //      for (int i=0; i< m_parameterlist.get_size(); i++)
   //         if (fv(m_parameterlist.GetKey(i)).get_string() == m_parameterlist.GetFieldValue(i).get_string())
   //         {
   //            continue;
   //         }
   //         else {result = false; break;}
   //      if (result) { return result;}
   //      next();
   //   }
   //   return false;
   //}


   //void dataset::add_update_sql(const ::string &upd_sql)
   //{
   //   string s = upd_sql;
   //   update_sql.add(s);
   //}

   //void dataset::add_insert_sql(const ::string &ins_sql)
   //{
   //   string s = ins_sql;
   //   insert_sql.add(s);
   //}

   //void dataset::add_delete_sql(const ::string &del_sql)
   //{
   //   string s = del_sql;
   //   delete_sql.add(s);
   //}

   //void dataset::clear_update_sql()
   //{
   //   update_sql.erase_all();
   //}

   //void dataset::clear_insert_sql()
   //{
   //   insert_sql.erase_all();
   //}

   //void dataset::clear_delete_sql()
   //{
   //   delete_sql.erase_all();
   //}


   ::collection::count dataset::field_count()
   {

      return m_result.m_pfielda->get_size();

   }


   ::pointer<field>dataset::field_at(::collection::index n)
   {

      if (n < 0 || n >= field_count())
      {

         return nullptr;

      }

      return m_result.m_pfielda->element_at(n);

   }


   //::collection::count dataset::fieldSize(index n)
   //{
   //   if ( n < field_count() && n >= 0)
   //      return m_fielda[n].m_properties.field_len;
   //   else
   //      return 0;
   //}

   //int dataset::fieldIndex(const ::string &fn)
   //{
   //   for (int i=0; i < m_fielda.get_size(); i++)
   //   {
   //      if(m_fielda[i].m_properties.name == fn)
   //         return i;
   //   }
   //   return -1;
   //}

   ::pointer<row_array>dataset::query_rows(const ::scoped_string & scopedstrQuery)
   {

      ::pointer<row_array>rows;

      if (!query_rows(rows, scopedstrQuery))
      {

         return nullptr;

      }

      return rows;

   }


   bool dataset::query_rows(::pointer<row_array>& rows, const ::scoped_string & scopedstrQuery)
   {

      if (!query(scopedstrQuery))
      {

         informationf("database::query_items::query failed");

         return false;

      }

      rows = m_result.m_prowa;

      return true;

   }


   ::pointer<payload_array>dataset::query_items(const ::scoped_string & scopedstrQuery)
   {

      ::pointer<payload_array>items;

      if (!query_items(items, scopedstrQuery))
      {

         return nullptr;

      }

      return items;

   }


   bool dataset::query_items(::pointer<payload_array>& items, const ::scoped_string & scopedstrQuery)
   {

      if (!query(scopedstrQuery))
      {

         informationf("database::query_items::query failed");

         return false;

      }

      for(auto & prow : *m_result.m_prowa)
      {

         items->add(prow->element_at(0));

      }

      return true;

   }


   ::payload dataset::query_item(const ::scoped_string & scopedstrQuery)
   {

      ::payload item;

      if (!query_item(item, scopedstrQuery) || item.failed())
      {

         return false;

      }

      return item;

   }


   bool dataset::query_item(::payload & item, const ::scoped_string & scopedstrQuery)
   {

      if (!query(scopedstrQuery))
      {

         informationf("database::query_items::query failed");

         return false;

      }

      item = field_value_at(0);

      return true;

   }


} // namespace sqlite



