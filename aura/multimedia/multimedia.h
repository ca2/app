#pragma once


namespace multimedia
{


   class CLASS_DECL_AURA information
   {
   public:


      string      m_strName;
      string      m_strAlbum;
      string      m_strArtist;


   };


}


namespace aura
{


   class CLASS_DECL_AURA multimedia :
      virtual public ::object
      // virtual public ::aura::department
   {
   public:

      


      multimedia();
      virtual ~multimedia();


      virtual ::estatus initialize_multimedia(::object* pobjectContext);

      virtual void on_song_added(const string& strId);

      virtual string get_media_call_title(const string& str);

      virtual void on_decoder_fill_title_info(::multimedia::decoder * pdecoder, string_array & straTitle, string2a & str2aTitle);

      virtual __pointer(::user::document) defer_create_view(::object* pobjectContext, const string & strView, ::user::interaction* puiParent, ewindowflag ewindowflag = window_flag_none, const ::id& id = nullptr);

      virtual void _001OnFranceExit();

      virtual void on_command(::user::command* pcommand);

      string_array detect_language(const string& str);


      virtual ::estatus get_file_information(::file::file* pfile, ::multimedia::information& information);


   };


} // namespace aura


extern "C"
typedef ::aura::multimedia * GET_NEW_MULTIMEDIA();


typedef GET_NEW_MULTIMEDIA * PFUNCTION_GET_NEW_MULTIMEDIA;


CLASS_DECL_AURA void set_get_new_multimedia(PFUNCTION_GET_NEW_MULTIMEDIA pfunction);


extern "C"
CLASS_DECL_AURA::aura::multimedia * get_get_new_multimedia();


CLASS_DECL_AURA::aura::multimedia * get_context_multimedia(::object * pobjectContext);


CLASS_DECL_AURA bool has_multimedia();


