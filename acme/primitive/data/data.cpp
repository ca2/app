#include "framework.h"
#include "data.h"
#include "listener.h"
#include "container.h"
#include "acme/constant/id.h"
#include "acme/exception/exception.h"


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

   
//   void data::assert_ok() const
//   {
//
//      ::matter::assert_ok();
//
//   }
//
//
//   void data::dump(dump_context & dumpcontext) const
//   {
//
//      ::matter::dump(dumpcontext);
//
//      //dumpcontext << "m_strTitle = " << m_strTitle;
//      //dumpcontext << "\nm_path = " << m_path;
//      //dumpcontext << "\nm_bModified = " << m_bModified;
//
//   }


   void data::initialize_data(::data::data_container_base * pdatacontainerbase)
   {

      /*auto estatus = */::object::initialize(pdatacontainerbase);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      m_pdatacontainerbase = pdatacontainerbase;

      if (!m_pdatacontainerbase)
      {

         throw ::exception(::error_failed);

      }

      //run_property(ID_CREATE);

      //call_procedures(CREATE_ROUTINE);

      //return ::success;

   }


   ::data::data_container_base* data::get_data_container()
   {

      return m_pdatacontainerbase.get();

   }


   ::count data::get_data_bound_impact_count() const
   {

      return  0;

   }


   ::user::primitive *  data::get_data_bound_impact(index iImpact)
   {

      return nullptr;

   }


   //void data::signal(::signal * psignal)
   //{

   //  //if (m_pdatacontainerbase)
   //  //{

   //  //   m_pdatacontainerbase->process(ptopic);

   //  //}

   //}


   void data::handle(::topic * ptopic, ::context * pcontext)
   {

      //if (m_pdatacontainerbase)
      //{

      //   m_pdatacontainerbase->process(ptopic);

      //}

   }


   void data::on_update_data(i32 iHint)
   {

      for(i32 i = 0; i < m_listenera.get_count(); i++)
      {

         m_listenera[i]->on_update_data(this, iHint);

      }

   }


} // namespace data



