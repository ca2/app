#pragma once


namespace aqua
{

      
   class out;
   class pre_buffer;


   class CLASS_DECL_AQUA media_player_command :
      virtual public object
   {
   public:


      ::aqua::enum_command                            m_ecommand;
      ::pointer < ::aqua::media_item >                m_pmediaitem;
      //array < happening *, happening * >                      m_evptra;
      bool                                            m_bResult;
      bool *                                          m_pbResult;
      bool                                            m_bSeekable;
      class ::time                                      m_time;
      //::pointer<::audio::plugin>                     m_ppluginOpen;
      bool                                            m_bFadeIn;


      media_player_command();
      media_player_command(const media_player_command & command);


      void set_open_media_item(::aqua::media_item * pmediaitem);
      //void SetOpenDecoder(::audio::plugin * pplugin);
      ::aqua::media_item * get_open_media_item() const;
      void SetCommand(::aqua::enum_command ecommand);
      ::aqua::enum_command GetCommand() const;


      //void SetEvents();
      //void AttachEvent(happening * pevent);


      void OpenMediaItem(::aqua::media_item * pmediaitem);

      void Play(const class time & time, bool bFadeIn);
      void Stop();
      void OpenDevice();
      void CloseDevice();

      media_player_command & operator =(const media_player_command & command);

   };


   typedef ::pointer<media_player_command>media_player_command_pointer;


} // namespace wave



