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

      ::matter::assert_valid();

   }


   void data::dump(dump_context & dumpcontext) const
   {

      ::matter::dump(dumpcontext);

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

      call_method(CREATE_METHOD);

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


   void data::on_apply(::action * paction)
   {

      if (m_pdatacontainerbase)
      {

         m_pdatacontainerbase->apply(paction);

      }

   }


   void data::on_update_data(i32 iHint)
   {

      for(i32 i = 0; i < m_listenera.get_count(); i++)
      {

         m_listenera[i]->on_update_data(this, iHint);

      }

   }


} // namespace data



