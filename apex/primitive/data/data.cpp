#include "framework.h"
#include "acme/id.h"


namespace data
{


   data::data()
   {

      //m_bModified = false;
      //m_bNew = true;

   }


   data::~data()
   {

      listener_array listenera = m_listenera;

      for(i32 i = 0; i < listenera.get_count(); i++)
      {

         listenera[i]->listen(this, false);

      }

   }

   
   void data::assert_valid() const
   {

      ::generic::assert_valid();

   }


   void data::dump(dump_context & dumpcontext) const
   {

      ::generic::dump(dumpcontext);

      //dumpcontext << "m_strTitle = " << m_strTitle;
      //dumpcontext << "\nm_path = " << m_path;
      //dumpcontext << "\nm_bModified = " << m_bModified;

   }


   ::estatus data::initialize_data(::data::data_container_base * pdatacontainerbase)
   {

      auto estatus = ::object::initialize(pdatacontainerbase);

      if (!estatus)
      {

         return estatus;

      }

      m_pdatacontainerbase = pdatacontainerbase;

      if (!m_pdatacontainerbase)
      {

         return ::error_failed;

      }

      //run_property("on_create");

      runall(CREATE_PROCEDURE);

      return ::success;

   }


   ::data::data_container_base* data::get_data_container()
   {

      return m_pdatacontainerbase.get();

   }


   ::count data::get_data_bound_view_count() const
   {

      return  0;

   }


   ::user::primitive *  data::get_data_bound_view(index iView)
   {

      return nullptr;

   }


   void data::update(::update * pupdate)
   {

      if (m_pdatacontainerbase)
      {

         m_pdatacontainerbase->call_update(pupdate);

      }

   }


//   bool data::is_locked() const
//   {
//      return ::data::simple_data::is_locked() || (m_spdataParentLock.is_set() && m_spdataParentLock->is_locked());
//   }

   void data::on_update_data(i32 iHint)
   {
      for(i32 i = 0; i < m_listenera.get_count(); i++)
      {
         m_listenera[i]->on_update_data(this, iHint);
      }
   }

   //void data::edit(base_edit * pbaseedit)
   //{

   //   UNREFERENCED_PARAMETER(pbaseedit);

   //}


} // namespace data





