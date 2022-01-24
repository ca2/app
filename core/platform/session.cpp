#include "framework.h"
#include "acme/platform/static_setup.h"


namespace core
{


   session::session()
   {

      m_pcoresession = this;

   }


   session::~session()
   {

   }


   void session::common_construct()
   {


   }


   void session::initialize(::object * pobject)
   {

      //auto estatus = 
      
      ::base::session::initialize(pobject);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //return estatus;

   }


   void session::on_instantiate_application(::application* papp)
   {

      ::bred::session::on_instantiate_application(papp);

      papp->m_pcoresession = this;
      papp->m_pcoresystem = m_pcoresystem;

   }

   __namespace_session_factory(session);


} // namespace core



