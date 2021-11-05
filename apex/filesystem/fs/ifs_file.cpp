#include "framework.h"
#include "apex/networking/sockets/_sockets.h"
#include "apex/filesystem/fs/_fs.h"
#include "ifs_file.h"


ifs_file::ifs_file(::payload payloadFile) :
   m_varFile(payloadFile)
{

}


ifs_file::~ifs_file()
{

}


memsize ifs_file::read(void *pdata, memsize nCount)
{

   return m_httpfile.read(pdata, nCount);

}


void ifs_file::write(const void * pdata, memsize nCount)
{

   m_memfile.write(pdata, nCount);


}


filesize ifs_file::get_size() const
{

   if((m_nOpenFlags & ::file::e_open_read) != 0)
   {

      return m_httpfile.get_size();

   }
   else
   {

      return m_memfile.get_size();

   }

}


filesize ifs_file::translate(filesize offset, ::enum_seek eseek)
{

   if((m_nOpenFlags & ::file::e_open_read) != 0)
   {

      return m_httpfile.translate(offset, eseek);

   }
   else
   {

      return m_memfile.translate(offset, eseek);

   }

}


void ifs_file::get_file_data()
{

   string strUrl;

   auto psystem = m_psystem;

   auto purl = psystem->url();

   strUrl = "http://file.ca2.software/ifs/get?path=" + purl->url_encode(m_strPath);

   ::file::e_open eopenAdd;

   if(m_nOpenFlags & ::file::e_open_update_unknown_length_supported)
   {

      eopenAdd |= ::file::e_open_update_unknown_length_supported;

   }

   m_httpfile.open(strUrl, ::file::e_open_binary | ::file::e_open_read | eopenAdd);

}


void ifs_file::set_file_data()
{

   string strUrl;

   auto psystem = m_psystem;

   auto purl = psystem->url();

   if(m_varFile["xmledit"].cast < ::memory_file > () != nullptr)
   {

      strUrl = "http://file.ca2.software/ifs/xmledit?path=" + purl->url_encode(m_varFile["url"]);

      property_set setRequest;

      setRequest["get_response"] = "";  // touch/create property to get_response

      m_pcontext->m_papexcontext->http().put(strUrl, m_varFile["xmledit"].cast < ::memory_file >(), setRequest);

      string strResponse(setRequest["get_response"].get_string());

      property_set set;

      set.parse_url_query(strResponse);

      string strMd5Here;

      strMd5Here = m_pcontext->m_papexcontext->file().md5(m_varFile["xml"].cast < ::memory_file >());

      string strMd5There;
      
      strMd5There = set["md5"];

      if (strMd5Here == strMd5There)
      {

         return;

      }

      strUrl = "http://file.ca2.software/ifs/set?path=" + purl->url_encode(m_varFile["url"]);

      property_set setPut;

      m_pcontext->m_papexcontext->http().put(strUrl, m_varFile["xml"].cast < ::memory_file >(), setPut);

      return;

   }

   strUrl = "http://file.ca2.software/ifs/set?path=" + purl->url_encode(m_strPath);

   property_set setPut;

   m_pcontext->m_papexcontext->http().put(strUrl, &m_memfile, setPut);

}



