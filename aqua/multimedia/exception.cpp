#include "framework.h"


namespace multimedia
{


   exception::exception(e_exception eexception, const ::e_status & estatus, const char * pszMessage) :
      ::exception::exception(estatus, pszMessage)
   {

      m_eexception = eexception;
      //m_estatusSecond = error_none;

   }


   //exception::exception(e_exception eexception, const ::e_status & estatus, ::e_status     estatusSecond, const char * pszMessage) :
   //   ::exception::exception(pszMessage, estatus)
   //{

   //   m_eexception = eexception;
   //   m_estatusSecond = estatusSecond;

   //}


   exception::~exception()
   {

   }


   string exception::get_message() const
   {

      string str;

      string strMultimediaMessage = ::exception::exception::get_message();

      if (m_eexception == exception_undefined)
      {

         str = "Multimedia Undefined Error";

      }
      else if (m_eexception == exception_multimedia)
      {

         str = "Multimedia ::aqua::get_system() Error";

      }
      else if (m_eexception == exception_midi)
      {

         str = "Midi File Format Error";

      }
      else if (m_eexception == exception_music)
      {

         str = "Music Error";

      }

      if (strMultimediaMessage.has_char())
      {

         str += ", " + strMultimediaMessage;

      }

      str += ".";

      return str;

   }


   //   ::e_status     ::e_status     smfrc
   //   {
   //
   //      ::e_status     rc = ::multimedia::result_midi_error;
   //
   //      switch(smfrc)
   //      {
   //      case success:
   //         rc = ::success;
   //         break;
   //
   //      case error_no_memory:
   //         rc = ::multimedia::result_no_memory;
   //         break;
   //
   //      case error_invalid_file:
   //      case EOpenFailed:
   //      case EInvalidTrack:
   //         rc = ::multimedia::result_bad_format;
   //         break;
   //
   //      default:
   //         rc = ::multimedia::result_midi_error;
   //         break;
   //
   //      };
   //
   ////         default:
   //      //          return MCIERR_UNSUPPORTED_FUNCTION;
   //      //     }
   //
   //      return rc;
   //
      //}

} // namespace multimedia





