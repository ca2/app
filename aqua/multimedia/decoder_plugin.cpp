#include "framework.h"
#include "decoder_plugin.h"
#include "decoder.h"
#include "acme/parallelization/happening.h"
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

      auto pdecoder = __øcreate < ::multimedia::decoder >(m_pfactory);

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


   void decoder_plugin::Load(const ::scoped_string & scopedstrTitle)
   {

//#ifdef APPLE_IOS
//
//      m_lpfnNewDecoder = paudio->get_multimedia_decoder_factory(scopedstrTitle);
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

      auto psystem = system();

      m_pfactory = psystem->factory(scopedstrTitle);

      //if (!m_pfactory)
      //{

      //   ::e_status estatus = m_pfactory;

      //   information() << "LoadLibrary failed to open library " << strTitle << estatus << as_string(estatus);

      //   return m_pfactory;

      //}
//
//      string strTitle = ::file::path(scopedstrTitle).title();
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
//         informationf("Got decoder creator function \"" + strFunction + "\" (" + as_string((iptr)m_lpfnNewDecoder) + ")");
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
//            informationf("Got decoder creator function \"" + m_strNewDecoder + "\" (" + as_string((iptr)m_lpfnNewDecoder) + ")");
//
//         }
//         else
//         {
//
//            m_plibrary->close();
//
//            informationf("\"" + m_strNewDecoder + "\" function not found in library " + string(scopedstrTitle));
//
//            return false;
//
//         }
//
//      }
//
//#endif

      m_strTitle = scopedstrTitle;

      //return ::success;

   }


   string decoder_plugin::GetPluginTitle()
   {

      return m_strTitle;

   }


} // namespace multimedia



