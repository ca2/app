#include "framework.h"
#include "ifs_file.h"
//#include "apex/networking/sockets/_sockets.h"
#include "acme/filesystem/file/memory_file.h"
#include "acme/platform/system.h"
#include "acme/primitive/primitive/url.h"
#include "apex/filesystem/filesystem/file_context.h"
#include "apex/platform/context.h"
#include "apex/networking/http/context.h"


ifs_file::ifs_file(::payload payloadFile) :
   m_payloadFile(payloadFile)
{

}


ifs_file::~ifs_file()
{

}


memsize ifs_file::read(const ::block & block)
{

   return m_phttpfile->read(block);

}


void ifs_file::write(const ::block & block)
{

   m_pmemfile->write(block);

}


filesize ifs_file::size() const
{

   if((m_nOpenFlags & ::file::e_open_read) != 0)
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

   if((m_nOpenFlags & ::file::e_open_read) != 0)
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

   auto psystem = acmesystem();

   auto purl = psystem->url();

   strUrl = "http://file.ca2.software/ifs/get?path=" + ::url::encode(m_strPath);

   ::file::e_open eopenAdd;

   if(m_nOpenFlags & ::file::e_open_update_unknown_length_supported)
   {

      eopenAdd |= ::file::e_open_update_unknown_length_supported;

   }

   m_phttpfile->open(strUrl, ::file::e_open_binary | ::file::e_open_read | eopenAdd);

}


void ifs_file::set_file_data()
{

   string strUrl;

   auto psystem = acmesystem();

   auto purl = psystem->url();

   if(m_payloadFile["xmledit"].cast < ::memory_file > () != nullptr)
   {

      strUrl = "http://file.ca2.software/ifs/xmledit?path=" + ::url::encode(m_payloadFile["url"]);

      property_set setRequest;

      setRequest["get_response"] = "";  // touch/create property to get_response

      m_pcontext->m_papexcontext->http().put(strUrl, m_payloadFile["xmledit"].cast < ::memory_file >(), setRequest);

      string strResponse(setRequest["get_response"]);

      property_set set;

      set.parse_network_arguments(strResponse);

      string strMd5Here;

      strMd5Here = ::particle::file()->md5(m_payloadFile["xml"].cast < ::memory_file >());

      string strMd5There;
      
      strMd5There = set["md5"];

      if (strMd5Here == strMd5There)
      {

         return;

      }

      strUrl = "http://file.ca2.software/ifs/set?path=" + ::url::encode(m_payloadFile["url"]);

      property_set setPut;

      m_pcontext->m_papexcontext->http().put(strUrl, m_payloadFile["xml"].cast < ::memory_file >(), setPut);

      return;

   }

   strUrl = "http://file.ca2.software/ifs/set?path=" + ::url::encode(m_strPath);

   property_set setPut;

   m_pcontext->m_papexcontext->http().put(strUrl, m_pmemfile, setPut);

}



