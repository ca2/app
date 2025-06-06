#include "framework.h"
#include "ifs_file.h"
//#include "apex/networking/sockets/_sockets.h"
#include "acme/filesystem/file/memory_file.h"
#include "acme/platform/system.h"
#include "acme/prototype/prototype/url.h"
#include "acme/filesystem/filesystem/file_context.h"
#include "acme/platform/http.h"
#include "apex/platform/context.h"
#include "apex/networking/http/context.h"


ifs_file::ifs_file(::payload payloadFile) :
   m_payloadFile(payloadFile)
{

}


ifs_file::~ifs_file()
{

}


memsize ifs_file::read(void * p, ::memsize s)
{

   return m_phttpfile->read(p, s);

}


void ifs_file::write(const void * p, ::memsize s)
{

   m_pmemfile->write(p, s);

}


filesize ifs_file::size() const
{

   if((m_eopen & ::file::e_open_read) != 0)
   {

      return m_phttpfile->size();

   }
   else
   {

      return m_pmemfile->size();

   }

}


void ifs_file::translate(filesize offset, ::enum_seek eseek)
{

   if((m_eopen & ::file::e_open_read) != 0)
   {

      m_phttpfile->translate(offset, eseek);

   }
   else
   {

      m_pmemfile->translate(offset, eseek);

   }

}


void ifs_file::get_file_data()
{

   string strUrl;

   strUrl = "http://file.ca2.network/ifs/get?path=" + ::url::encode(m_path);

   ::file::e_open eopenAdd;

   if(m_eopen & ::file::e_open_update_unknown_length_supported)
   {

      eopenAdd |= ::file::e_open_update_unknown_length_supported;

   }

   m_phttpfile->open(strUrl, ::file::e_open_binary | ::file::e_open_read | eopenAdd);

}


void ifs_file::set_file_data()
{

   string strUrl;

   if(m_payloadFile["xmledit"].cast < ::memory_file > () != nullptr)
   {

      strUrl = "http://file.ca2.network/ifs/xmledit?path=" + ::url::encode(m_payloadFile["url"].as_string());

      ::property_set setRequest;

      setRequest["get_response"] = "";  // touch/create property to get_response

      http()->put(strUrl, m_payloadFile["xmledit"].cast < ::memory_file >(), setRequest);

      string strResponse(setRequest["get_response"].as_string());

      ::property_set set;

      set.parse_network_arguments(strResponse);

      string strMd5Here;

      strMd5Here = ::particle::file()->md5(m_payloadFile["xml"].cast < ::memory_file >());

      string strMd5There;
      
      strMd5There = set["md5"];

      if (strMd5Here == strMd5There)
      {

         return;

      }

      strUrl = "http://file.ca2.network/ifs/set?path=" + ::url::encode(m_payloadFile["url"].as_string());

      ::property_set setPut;

      http()->put(strUrl, m_payloadFile["xml"].cast < ::memory_file >(), setPut);

      return;

   }

   strUrl = "http://file.ca2.network/ifs/set?path=" + ::url::encode(m_path);

   ::property_set setPut;

   http()->put(strUrl, m_pmemfile, setPut);

}



