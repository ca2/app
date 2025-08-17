#include "framework.h"
#include "multimedia.h"


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


   void multimedia::initialize_multimedia(::particle * pparticle)
   {

      //auto estatus = 
      initialize(pparticle);

      //if (!estatus)
      //{

      //   return estatus;

      //}

//#ifdef WINDOWS
//
//      estatus = øconstruct_new(m_pmediafoundation);
//
//      if (!estatus)
//      {
//
//         return estatus;
//
//      }
//
//#endif

      //return estatus;

   }


   void multimedia::on_song_added(const ::scoped_string & scopedstrId)
   {

   }


   string multimedia::get_media_call_title(const ::scoped_string & scopedstr)
   {

      return scopedstr;

   }


   void multimedia::on_decoder_fill_title_info(::multimedia::decoder * pdecoder, string_array_base & straTitle, string_array_array_base & straaTitle)
   {


   }


   ::pointer<::user::controller>multimedia::defer_create_impact(::particle * pparticle, const ::scoped_string & scopedstrImpact, ::user::interaction* puiParent, e_window_flag ewindowflag, const ::atom& atom)
   {

      return nullptr;

   }


   void multimedia::exit_application()
   {

      //return ::success;

   }


   void multimedia::on_command(::message::command* pcommand)
   {


   }


   string_array_base multimedia::detect_language(const ::scoped_string & scopedstr)
   {

      string_array_base stra;

      return stra;

   }


   void multimedia::get_file_information(::file::file* pfile, ::multimedia::information& information)
   {

      //return ::error_failed;

   }


//#ifdef WINDOWS
//
//
//   ::windows::media_foundation * multimedia::mediafoundation()
//   {
//
//      if (!m_pmediafoundation)
//      {
//
//         auto estatus = øconstruct(m_pmediafoundation);
//
//         if (!estatus)
//         {
//
//            return nullptr;
//
//         }
//
//      }
//
//      return m_pmediafoundation;
//
//   }
//
//
//#endif


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


//CLASS_DECL_AQUA ::aqua::multimedia * get_context_multimedia(::particle * pparticle)
//{
//
//   return system()->defer_get_multimedia();
//
//}


//CLASS_DECL_AQUA bool has_multimedia()
//{
//
//   return ::is_set(system()->m_pmultimedia);
//
//}



