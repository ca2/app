#include "framework.h"
#ifdef WINDOWS
#include "aqua/node/windows_common/media_foundation.h"
#endif


namespace aqua
{


   multimedia::multimedia()
   {

      //m_pmultimedia = nullptr;

      //m_pveriwellmultimedia = nullptr;

   }


   multimedia::~multimedia()
   {


   }


   ::e_status multimedia::initialize_multimedia(::object * pobject)
   {

      auto estatus = initialize(pobject);

      if (!estatus)
      {

         return estatus;

      }

#ifdef WINDOWS

      estatus = __compose_new(m_pmediafoundation);

      if (!estatus)
      {

         return estatus;

      }

#endif

      return estatus;

   }


   void multimedia::on_song_added(const string& strId)
   {

   }


   string multimedia::get_media_call_title(const string & str)
   {

      return str;

   }


   void multimedia::on_decoder_fill_title_info(::multimedia::decoder * pdecoder, string_array & straTitle, string2a & str2aTitle)
   {


   }


   __pointer(::user::controller) multimedia::defer_create_view(::object* pobject, const string& strView, ::user::interaction* puiParent, ewindowflag ewindowflag, const ::id& id)
   {

      return nullptr;

   }


   ::e_status multimedia::exit_application()
   {

      return ::success;

   }


   void multimedia::on_command(::message::command* pcommand)
   {


   }


   string_array multimedia::detect_language(const string& str)
   {

      string_array stra;

      return stra;

   }


   ::e_status multimedia::get_file_information(::file::file* pfile, ::multimedia::information& information)
   {

      return ::error_failed;

   }


#ifdef WINDOWS


   ::windows::media_foundation * multimedia::mediafoundation()
   {

      if (!m_pmediafoundation)
      {

         auto estatus = __compose(m_pmediafoundation);

         if (!estatus)
         {

            return nullptr;

         }

      }

      return m_pmediafoundation;

   }


#endif


} // namespace aqua


//static PFUNCTION_GET_NEW_MULTIMEDIA g_pgetnewmultimedia = nullptr;
//
//
//CLASS_DECL_AQUA void set_get_new_multimedia(PFUNCTION_GET_NEW_MULTIMEDIA pgetnewmultimedia)
//{
//
//   g_pgetnewmultimedia = pgetnewmultimedia;
//
//}
//
//
//CLASS_DECL_AQUA ::aqua::multimedia * get_new_multimedia()
//{
//
//   if ((iptr) g_pgetnewmultimedia < 65536)
//   {
//
//      return nullptr;
//
//   }
//
//   return g_pgetnewmultimedia();
//
//}


//CLASS_DECL_AQUA ::aqua::multimedia * get_context_multimedia(::object * pobject)
//{
//
//   return get_system()->defer_get_multimedia();
//
//}


//CLASS_DECL_AQUA bool has_multimedia()
//{
//
//   return ::is_set(get_system()->m_pmultimedia);
//
//}



