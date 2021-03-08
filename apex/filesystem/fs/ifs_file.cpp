#include "framework.h"
#include "apex/net/sockets/_sockets.h"
#include "apex/filesystem/fs/_fs.h"
#include "ifs_file.h"


ifs_file::ifs_file(::payload varFile) :
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

   if((m_nOpenFlags & ::file::e_open_read) != 0)
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

   if((m_nOpenFlags & ::file::e_open_read) != 0)
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

   strUrl = "http://file.ca2.cc/ifs/get?path=" + ::apex::get_system()->url().url_encode(m_strPath);

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

   if(m_varFile["xmledit"].cast < ::memory_file > () != nullptr)
   {

      strUrl = "http://file.ca2.cc/ifs/xmledit?path=" + ::apex::get_system()->url().url_encode(m_varFile["url"]);

      property_set setRequest;

      setRequest["get_response"] = "";  // touch/create property to get_response

      get_context()->http().put(strUrl, m_varFile["xmledit"].cast < ::memory_file >(), setRequest);

      string strResponse(setRequest["get_response"]);

      property_set set;

      set.parse_url_query(strResponse);

      string strMd5Here;

      strMd5Here = get_context()->file().md5(m_varFile["xml"].cast < ::memory_file >());

      string strMd5There;
      
      strMd5There = set["md5"];

      if (strMd5Here == strMd5There)
      {

         return;

      }

      strUrl = "http://file.ca2.cc/ifs/set?path=" + ::apex::get_system()->url().url_encode(m_varFile["url"]);

      property_set setPut;

      get_context()->http().put(strUrl, m_varFile["xml"].cast < ::memory_file >(), setPut);

      return;

   }

   strUrl = "http://file.ca2.cc/ifs/set?path=" + ::apex::get_system()->url().url_encode(m_strPath);

   property_set setPut;

   get_context()->http().put(strUrl, &m_memfile, setPut);

}



