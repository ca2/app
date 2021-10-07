#include "framework.h"


namespace multimedia
{


   decoder_plugin::decoder_plugin()
   {

   }


   decoder_plugin::~decoder_plugin()
   {

   }


   decoder * decoder_plugin::NewDecoder()
   {

      ::multimedia::decoder  * pdecoder = m_lpfnNewDecoder();

      if (::is_null(pdecoder))
      {

         m_plibrary->close();

         return nullptr;

      }

      pdecoder->m_pplugin = this;

      auto estatus = pdecoder->initialize(this);

      if(!estatus)
      {

         return nullptr;

      }

      return pdecoder;

   }


   bool decoder_plugin::Load(const char * pszTitle)
   {

#ifdef APPLE_IOS

      m_lpfnNewDecoder = paudio->get_multimedia_decoder_factory(pszTitle);

      if (m_lpfnNewDecoder == nullptr)
      {

         return false;

      }

#else

      //m_plibrary.create(this);

      auto psystem = get_system()->m_paquasystem;

      m_plibrary = psystem->get_library(pszTitle);

      if (m_plibrary.is_null())
      {

         ::e_status estatus = get_last_status();

         INFORMATION("LoadLibrary failed to open library " << pszTitle << estatus << __string(estatus));

         return false;

      }

      string strTitle = ::file::path(pszTitle).title();

      ::str::begins_eat_ci(strTitle, "lib");

      string strFunction = strTitle + "_" + m_strNewDecoder;

      m_lpfnNewDecoder = m_plibrary->get < decoder * (*)() >(strFunction);

      if (m_lpfnNewDecoder != nullptr)
      {

         output_debug_string("Got decoder creator function \"" + strFunction + "\" (" + __string((iptr)m_lpfnNewDecoder) + ")");

      }
      else
      {

         m_lpfnNewDecoder = m_plibrary->get < decoder * (*)() >(m_strNewDecoder);

         if (m_lpfnNewDecoder != nullptr)
         {

            output_debug_string("Got decoder creator function \"" + m_strNewDecoder + "\" (" + __string((iptr)m_lpfnNewDecoder) + ")");

         }
         else
         {

            m_plibrary->close();

            output_debug_string("\"" + m_strNewDecoder + "\" function not found in library " + string(pszTitle));

            return false;

         }

      }

#endif

      m_strTitle = pszTitle;

      return true;

   }


   string decoder_plugin::GetPluginTitle()
   {

      return m_strTitle;

   }


} // namespace multimedia



