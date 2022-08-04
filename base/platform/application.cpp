#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "base/user/user/_component.h"
#endif


namespace base
{


   void initialize()
   {

      ::factory::add_factory_item< ::base::system, class ::system>();

   }


   application::application()
   {

      ::base::initialize();

      m_pbaseapplication = this;

   }


   void application::initialize(::object * pobject)
   {

      //auto estatus = 
      
      ::axis::application::initialize(pobject);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //estatus =
      
      ::user::document_manager_container::initialize(pobject);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //return estatus;

   }


   application::~application()
   {

   }


   void application::assert_ok() const
   {

      ::axis::application::assert_ok();

   }


   void application::dump(dump_context & dumpcontext) const
   {

      ::axis::application::dump(dumpcontext);

   }


   ::user::document *application::place_hold(::user::interaction * pinteraction)
   {

      return nullptr;

   }


   void application::on_create_split_impact(::user::split_impact* psplit)
   {


   }


   void application::on_change_cur_sel(::user::tab* ptab)
   {


   }


   void application::creatimpact_system()
   {

      //return ::success;

   }


   void application::on_create_impact(::user::impact_data* pimpactdata)
   {


   }


   void application::close(::apex::enum_end eend)
   {

      auto psession = get_session();

      if (psession->m_puser)
      {

         auto puser = psession->user();

         auto pdocumentmanager = puser->document_manager();

         if (pdocumentmanager)
         {

            pdocumentmanager->close_all_documents(eend != ::apex::e_end_close);

         }

      }

      if (document_manager())
      {

         document_manager()->close_all_documents(eend != ::apex::e_end_close);

      }

      ::aura::application::close(eend);

   }


   __pointer(::user::document) application::defer_create_view(string strImpact, ::user::interaction* puiParent, ewindowflag ewindowflag, const ::atom& atom)
   {

      return nullptr;

   }

   
   void application::on_file_manager_open(::filemanager::data* pdata, const ::file::item_array& itema, const ::action_context& action_context)
   {

      auto pcreate = __create_new<create>();

      if (itema.get_size() == 1)
      {

         pcreate->m_payloadFile = itema[0]->user_path();

      }
      else
      {

         string_array stra;

         for (auto& pitem : itema)
         {

            stra.add(pitem->user_path());

         }

         pcreate->m_payloadFile = stra;

      }

      do_request(pcreate);

   }


} // namespace base



