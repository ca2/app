#include "framework.h"
#include "base/user/user/_user.h"


namespace base
{


   application::application()
   {

      m_pbaseapplication = this;

   }


   ::e_status application::initialize(::object * pobject)
   {

      auto estatus = ::axis::application::initialize(pobject);

      if (!estatus)
      {

         return estatus;

      }

      estatus = ::user::document_manager_container::initialize(pobject);

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   application::~application()
   {

   }


   void application::assert_valid() const
   {

      ::axis::application::assert_valid();

   }


   void application::dump(dump_context & dumpcontext) const
   {

      ::axis::application::dump(dumpcontext);

   }


   ::user::document *application::place_hold(::user::interaction * pinteraction)
   {

      return nullptr;

   }


   void application::on_create_split_view(::user::split_view* psplit)
   {


   }


   void application::on_change_cur_sel(::user::tab* ptab)
   {


   }


   ::e_status application::create_impact_system()
   {

      return ::success;

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


   __pointer(::user::document) application::defer_create_view(string strView, ::user::interaction* puiParent, ewindowflag ewindowflag, const ::id& id)
   {

      return nullptr;

   }

   
   void application::on_file_manager_open(::filemanager::data* pdata, const ::file::item_array& itema, const ::action_context& action_context)
   {

      auto pcreate = __create_new<create>();

      if (itema.get_size() == 1)
      {

         pcreate->m_varFile = itema[0]->get_final_path();

      }
      else
      {

         string_array stra;

         for (auto& pitem : itema)
         {

            stra.add(pitem->get_final_path());

         }

         pcreate->m_varFile = stra;

      }

      do_request(pcreate);

   }


} // namespace base



