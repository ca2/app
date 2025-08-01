#pragma once


#include "acme/platform/department.h"
#include "acme/user/user/e_window_flag.h"
//#include "acme/prototype/collection/string_array.h"


namespace aqua
{


   class CLASS_DECL_AQUA multimedia :
      virtual public ::acme::department
   {
   public:


      ::multimedia::multimedia *                m_pmultimediaThis;
      ::veriwell::multimedia::multimedia *      m_pveriwellmultimediaThis;


//#ifdef WINDOWS
//      ::pointer<::windows::media_foundation>          m_pmediafoundation;
//#endif

      
      multimedia();
      ~multimedia() override;


      virtual void initialize_multimedia(::particle * pparticle);

      virtual void on_song_added(const ::scoped_string & scopedstrId);

      virtual string get_media_call_title(const ::scoped_string & scopedstr);

      virtual void on_decoder_fill_title_info(::multimedia::decoder * pdecoder, string_array & straTitle, string_array_array & straaTitle);

      virtual ::pointer<::user::controller>defer_create_impact(::particle * pparticle, const ::scoped_string & scopedstrImpact, ::user::interaction* puiParent, e_window_flag ewindowflag = e_window_flag_none, const ::atom& atom = nullptr);

      virtual void exit_application();

      virtual void on_command(::message::command* pcommand);

      string_array detect_language(const ::scoped_string & scopedstr);


      virtual void get_file_information(::file::file* pfile, ::multimedia::information& information);

//#ifdef WINDOWS
//    ::windows::media_foundation * mediafoundation();
//#endif


   };


} // namespace aqua


extern "C"
typedef ::aqua::multimedia * GET_NEW_MULTIMEDIA();


typedef GET_NEW_MULTIMEDIA * PFUNCTION_GET_NEW_MULTIMEDIA;


CLASS_DECL_AQUA void set_get_new_multimedia(PFUNCTION_GET_NEW_MULTIMEDIA pfunction);


extern "C"
CLASS_DECL_AQUA ::aqua::multimedia * get_get_new_multimedia();


CLASS_DECL_AQUA ::aqua::multimedia * get_context_multimedia(::particle * pparticle);


CLASS_DECL_AQUA bool has_multimedia();


