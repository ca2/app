#include "framework.h"
#include "data.h"
#include "listener.h"
#include "container.h"
#include "acme/constant/id.h"
////#include "acme/exception/exception.h"


namespace data
{


   data::data()
   {

      //m_bModified = false;
      m_bNew = true;

   }


   data::~data()
   {

      listener_array listenera = m_listenera;

      for(int i = 0; i < listenera.get_count(); i++)
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


   void data::initialize_data()
   {

      ///*auto estatus = */::object::initialize(pdatacontainerbase);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //m_pdatacontainerbase = pdatacontainerbase;

      //if (!m_pdatacontainerbase)
      //{

      //   throw ::exception(::error_failed);

      //}

      //run_property(id_create);

      //call_procedures(CREATE_ROUTINE);

      //return ::success;

   }


   //::data::data_container_base* data::get_data_container()
   //{

   //   return m_pdatacontainerbase.get();

   //}


   ::collection::count data::get_data_bound_impact_count() const
   {

      return  0;

   }


   ::user::element *  data::get_data_bound_impact(::collection::index iImpact)
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


   void data::handle(::topic * ptopic, ::handler_context * phandlercontext)
   {

      //if (m_pdatacontainerbase)
      //{

      //   m_pdatacontainerbase->process(ptopic);

      //}

   }


   void data::on_update_data(int iHint)
   {

      for(int i = 0; i < m_listenera.get_count(); i++)
      {

         m_listenera[i]->on_update_data(this, iHint);

      }

   }


   bool data::is_new_data() const
   {

      return m_bNew;

   }


   bool data::on_new_data()
   {

      m_bNew = true;

      return true;

   }


   void data::write_data(::binary_stream & binarystream, const ::scoped_string & scopedstrFormat)
   {

   }


   void data::read_data(::binary_stream & binarystream, const ::scoped_string & scopedstrFormat)
   {

   }


} // namespace data



