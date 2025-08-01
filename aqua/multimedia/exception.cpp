#include "framework.h"
#include "exception.h"


namespace multimedia
{


   exception::exception(enum_exception eexception, const ::e_status & estatus, const ::scoped_string & scopedstrMessage) :
      ::exception(estatus, scopedstrMessage)
   {

      m_eexception = eexception;
      //m_estatusSecond = error_none;

   }


   //::exception(e_exception eexception, const ::e_status & estatus, void     estatusSecond, const ::scoped_string & scopedstrMessage) :
   //   ::exception(scopedstrMessage, estatus)
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

      string strMultimediaMessage = ::exception::get_message();

      if (m_eexception == e_exception_undefined)
      {

         str = "Multimedia Undefined Error";

      }
      else if (m_eexception == e_exception_multimedia)
      {

         str = "Multimedia system() Error";

      }
      else if (m_eexception == e_exception_midi)
      {

         str = "Midi File Format Error";

      }
      else if (m_eexception == e_exception_music)
      {

         str = "Music Error";

      }

      if (strMultimediaMessage.has_character())
      {

         str += ", " + strMultimediaMessage;

      }

      str += ".";

      return str;

   }


   //   void     void     smfrc
   //   {
   //
   //      void     rc = ::multimedia::result_midi_error;
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





