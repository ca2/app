#include "framework.h"
#include "aura/net/sockets/_.h"
#include "aura/filesystem/fs/_fs.h"
#include "ifs_file.h"


ifs_file::ifs_file(var varFile) :
   m_varFile(varFile)
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

   if((m_nOpenFlags & ::file::mode_read) != 0)
   {

      return m_httpfile.get_size();

   }
   else
   {

      return m_memfile.get_size();

   }

}


filesize ifs_file::seek(filesize lOff, ::file::e_seek nFrom)
{

   if((m_nOpenFlags & ::file::mode_read) != 0)
   {

      return m_httpfile.seek(lOff, nFrom);

   }
   else
   {

      return m_memfile.seek(lOff, nFrom);

   }

}


void ifs_file::get_file_data()
{

   string strUrl;

   strUrl = "http://file.ca2.cc/ifs/get?path=" + System.url().url_encode(m_strPath);

   u32 dwAdd = 0;

   if(m_nOpenFlags & ::file::update_unknown_length_supported)
   {

      dwAdd |= ::file::update_unknown_length_supported;

   }

   m_httpfile.open(strUrl, ::file::type_binary | ::file::mode_read | dwAdd);

}


void ifs_file::set_file_data()
{

   string strUrl;

   if(m_varFile["xmledit"].cast < ::memory_file > () != nullptr)
   {

      strUrl = "http://file.ca2.cc/ifs/xmledit?path=" + System.url().url_encode(m_varFile["url"]);

      property_set setRequest;

      setRequest["get_response"] = "";  // touch/create property to get_response

      Context.http().put(strUrl, m_varFile["xmledit"].cast < ::memory_file >(), setRequest);

      string strResponse(setRequest["get_response"]);

      property_set set;

      set.parse_url_query(strResponse);

      string strMd5Here;

      strMd5Here = Context.file().md5(m_varFile["xml"].cast < ::memory_file >());

      string strMd5There = set["md5"];

      if (strMd5Here == strMd5There)
      {

         return;

      }

      strUrl = "http://file.ca2.cc/ifs/set?path=" + System.url().url_encode(m_varFile["url"]);

      property_set setPut;

      Context.http().put(strUrl, m_varFile["xml"].cast < ::memory_file >(), setPut);

      return;

   }

   strUrl = "http://file.ca2.cc/ifs/set?path=" + System.url().url_encode(m_strPath);

   property_set setPut;

   Context.http().put(strUrl, &m_memfile, setPut);

}



