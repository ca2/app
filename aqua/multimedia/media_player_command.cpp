#include "framework.h"
#include "media_item.h"
#include "media_player_command.h"
#include "acme/filesystem/file/file.h"
#include "acme/parallelization/happening.h"
//#include "audio/audio/plugin/plugin.h"


namespace aqua
{


   media_player_command::media_player_command()
   {

      m_pbResult = nullptr;

      m_bSeekable = true;

   }


   media_player_command::media_player_command(const media_player_command & command) :
      ::object(command)
   {

      operator =(command);

   }


   media_player_command & media_player_command::operator =(const media_player_command & command)
   {

      SetCommand(command.GetCommand());
      set_open_media_item(command.get_open_media_item());
      //SetOpenDecoder(command.m_ppluginOpen);
      m_bResult = command.m_bResult;
      m_pbResult = command.m_pbResult;
      //m_evptra = command.m_evptra;
      m_bSeekable = command.m_bSeekable;
      m_time = command.m_time;
      m_bFadeIn = command.m_bFadeIn;

      return *this;

   }


   enum_command media_player_command::GetCommand() const
   {

      return m_ecommand;

   }


   void media_player_command::SetCommand(enum_command ecommand)
   {

      m_ecommand = ecommand;

   }


   ::aqua::media_item * media_player_command::get_open_media_item() const
   {

      return m_pmediaitem;

   }


   void media_player_command::set_open_media_item(::aqua::media_item * pmediaitem)
   {

      m_pmediaitem = pmediaitem;

   }


//   void media_player_command::SetOpenDecoder(::audio::plugin * pplugin)
//   {
//
//      m_ppluginOpen = pplugin;
//
//   }
//
//
//   void media_player_command::OpenDecoder(::audio::plugin * pplugin)
//   {
//
//      SetCommand(command_open_plugin);
//
//      SetOpenDecoder(pplugin);
//
//   }


void media_player_command::OpenMediaItem(::aqua::media_item * pmediaitem)
{

   SetCommand(command_open_media_item);

   set_open_media_item(pmediaitem);

}

//   void media_player_command::OpenRtpFile(::file::file * pfile)
//   {
//
//      SetCommand(command_open_file_rtp);
//
//      set_open_file(pfile);
//
//   }
//
//
//   void media_player_command::OpenMp3File(::file::file * pfile)
//   {
//
//      SetCommand(command_open_file_mp3);
//
//      set_open_file(pfile);
//
//   }
//
//
//   void media_player_command::OpenAiffFile(::file::file * pfile)
//   {
//
//      SetCommand(command_open_file_aiff);
//
//      set_open_file(pfile);
//
//   }
//
//
//   void media_player_command::OpenCdaFile(::file::file * pfile)
//   {
//
//      SetCommand(command_open_file_cda);
//
//      set_open_file(pfile);
//
//   }
//
//
//   void media_player_command::OpenVqfFile(::file::file * pfile)
//   {
//
//      SetCommand(command_open_file_vqf);
//
//      set_open_file(pfile);
//
//   }
//
//
//   void media_player_command::OpenWmFile(::file::file * pfile)
//   {
//
//      SetCommand(command_open_file_wm);
//
//      set_open_file(pfile);
//
//   }
//
//
//   void media_player_command::OpenWavFile(::file::file * pfile)
//   {
//
//      SetCommand(command_open_file_wav);
//
//      set_open_file(pfile);
//
//   }
//
//
//   void media_player_command::OpenFile(::file::file * pfile, bool bSeekable)
//   {
//
//      SetCommand(command_open_file);
//
//      set_open_file(pfile);
//
//      m_bSeekable = bSeekable;
//
//   }


   void media_player_command::Play(const class time & time, bool bFadeIn)
   {

      SetCommand(command_execute_play);

      m_time = time;

      m_bFadeIn = bFadeIn;

   }


//   void media_player_command::AttachEvent(happening *phappening)
//   {
//
//      m_evptra.add(phappening);
//
//   }
//
//
//   void media_player_command::SetEvents()
//   {
//      for (int i = 0; i < m_evptra.get_size(); i++)
//      {
//         m_evptra[i]->set_happening();
//      }
//   }

   void media_player_command::Stop()
   {
      SetCommand(command_execute_stop);
   }

   void media_player_command::CloseDevice()
   {
      SetCommand(command_close_device);
   }


   void media_player_command::OpenDevice()
   {

      SetCommand(command_open_device);

   }


} // namespace wave


