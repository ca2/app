#include "framework.h"
#include "decoder_plugin.h"
#include "decoder.h"
#include "acme/parallelization/event.h"
#include "aqua/platform/system.h"


namespace multimedia
{


   decoder_plugin::decoder_plugin()
   {

   }


   decoder_plugin::~decoder_plugin()
   {

   }


   ::pointer<decoder>decoder_plugin::NewDecoder()
   {

      auto pdecoder = m_pfactory->create < ::multimedia::decoder >();

      if (!pdecoder)
      {

         //m_plibrary->close();

         return pdecoder;

      }

      pdecoder->m_pplugin = this;

      //auto estatus =
      
      pdecoder->initialize(this);

 /*     if(!estatus)
      {

         return estatus;

      }*/

      return pdecoder;

   }


   void decoder_plugin::Load(const ::string & strTitle)
   {

//#ifdef APPLE_IOS
//
//      m_lpfnNewDecoder = paudio->get_multimedia_decoder_factory(pszTitle);
//
//      if (m_lpfnNewDecoder == nullptr)
//      {
//
//         return false;
//
//      }
//
//#else
//
      //m_plibrary.create(this);

      auto psystem = acmesystem()->m_paquasystem;

      m_pfactory = psystem->factory(strTitle);

      //if (!m_pfactory)
      //{

      //   ::e_status estatus = m_pfactory;

      //   information() << "LoadLibrary failed to open library " << strTitle << estatus << as_string(estatus);

      //   return m_pfactory;

      //}
//
//      string strTitle = ::file::path(pszTitle).title();
//
//      strTitle.case_insensitive_begins_eat("lib");
//
//      string strFunction = strTitle + "_" + m_strNewDecoder;
//
//      m_lpfnNewDecoder = m_plibrary->get < decoder * (*)() >(strFunction);
//
//      if (m_lpfnNewDecoder != nullptr)
//      {
//
//         output_debug_string("Got decoder creator function \"" + strFunction + "\" (" + as_string((iptr)m_lpfnNewDecoder) + ")");
//
//      }
//      else
//      {
//
//         m_lpfnNewDecoder = m_plibrary->get < decoder * (*)() >(m_strNewDecoder);
//
//         if (m_lpfnNewDecoder != nullptr)
//         {
//
//            output_debug_string("Got decoder creator function \"" + m_strNewDecoder + "\" (" + as_string((iptr)m_lpfnNewDecoder) + ")");
//
//         }
//         else
//         {
//
//            m_plibrary->close();
//
//            output_debug_string("\"" + m_strNewDecoder + "\" function not found in library " + string(pszTitle));
//
//            return false;
//
//         }
//
//      }
//
//#endif

      m_strTitle = strTitle;

      //return ::success;

   }


   string decoder_plugin::GetPluginTitle()
   {

      return m_strTitle;

   }


} // namespace multimedia



