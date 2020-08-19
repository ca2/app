#include "framework.h"



namespace aura
{


   multimedia::multimedia()
   {


   }


   multimedia::~multimedia()
   {


   }

   
   ::estatus multimedia::initialize_multimedia(::object* pobjectContext)
   {

      auto estatus = initialize(pobjectContext);

      if (!estatus)
      {

         return estatus;

      }
      
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


   __pointer(::user::document) multimedia::defer_create_view(::object* pobjectContext, const string& strView, ::user::interaction* puiParent, ewindowflag ewindowflag, const ::id& id)
   {

      return nullptr;

   }



   void multimedia::_001OnFranceExit()
   {


   }


   void multimedia::on_command(::user::command* pcommand)
   {


   }


   string_array multimedia::detect_language(const string& str)
   {

      string_array stra;

      return stra;

   }

   
   ::estatus multimedia::get_file_information(::file::file* pfile, ::multimedia::information& information)
   {

      /*

      property_set set = id3_set(file);

      m_strName = set["name"];

      m_strAlbum = set["album"];

      m_strArtist = set["artist"];

      */

      return ::error_failed;

   }


} // namespace aura


static PFUNCTION_GET_NEW_MULTIMEDIA g_pgetnewmultimedia = nullptr;


CLASS_DECL_AURA void set_get_new_multimedia(PFUNCTION_GET_NEW_MULTIMEDIA pgetnewmultimedia)
{

   g_pgetnewmultimedia = pgetnewmultimedia;

}


CLASS_DECL_AURA::aura::multimedia * get_new_multimedia()
{

   if ((iptr) g_pgetnewmultimedia < 65536)
   {

      return nullptr;

   }

   return g_pgetnewmultimedia();

}


CLASS_DECL_AURA::aura::multimedia * get_context_multimedia(::object * pobjectContext)
{

   return Sys(pobjectContext).defer_get_multimedia();

}


CLASS_DECL_AURA bool has_multimedia()
{

   return ::is_set(::get_context_system()->m_pmultimedia);

}


