#include "framework.h"
#include "apex/networking/sockets/_sockets.h"
#include "apex/filesystem/fs/_fs.h"
#include "remote_native_file.h"

namespace fs
{


   remote_native_file::remote_native_file(::payload varFile) :
      m_varFile(varFile)
   {

   }


   remote_native_file::~remote_native_file()
   {

   }


   memsize remote_native_file::read(void *pdata, memsize nCount)

   {

      return m_httpfile.read(pdata, nCount);


   }


   void remote_native_file::write(const void * pdata, memsize nCount)

   {

      m_memfile.write(pdata, nCount);


   }


   filesize remote_native_file::get_size() const
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

   filesize remote_native_file::seek(filesize lOff, ::enum_seek eseek)
   {

      if((m_nOpenFlags & ::file::e_open_read) != 0)
      {

         return m_httpfile.translate(lOff, eseek);

      }
      else
      {

         return m_memfile.translate(lOff, eseek);

      }

   }


   void remote_native_file::get_file_data()
   {
      /*if(m_nOpenFlags & ::file::e_open_write)
      {
      __throw(::exception::exception("Cannot open remote_native_file for reading and writing simultaneously due the characteristic of possibility of extreme delayed streaming. The way it is implemented would also not work.\n It is build with this premisse."));
      return;
      }*/

      string strUrl;

      auto psystem = m_psystem;

      auto purl = psystem->url();

      strUrl = "http://fs.veriwell.net/fs/get?path=" + purl->url_encode(purl->get_script(m_strPath))
               + "&server=" + purl->url_encode(purl->get_server(m_strPath));

      ::file::e_open eopenAdd;

      if(m_nOpenFlags & ::file::e_open_update_unknown_length_supported)
      {

         eopenAdd |= ::file::e_open_update_unknown_length_supported;

      }

      m_httpfile.open(strUrl, ::file::e_open_binary | ::file::e_open_read | eopenAdd);

   }


   void remote_native_file::set_file_data()
   {

      string strUrl;

      auto psystem = m_psystem;

      auto purl = psystem->url();

      if(m_varFile["xmledit"].cast < ::memory_file >() != nullptr)
      {

         strUrl = "http://fs.veriwell.net/fs/xmledit?path=" + purl->url_encode(purl->get_script(m_varFile["url"]))
                  + "&server=" + purl->url_encode(purl->get_server(m_varFile["url"]));

         property_set setRequest;

         setRequest["get_response"] = ""; // touch/create property to get_response

         m_pcontext->m_papexcontext->http().put(strUrl,m_varFile["xmledit"].cast < ::memory_file >(),setRequest);

         string strResponse(setRequest["get_response"]);

         property_set set;

         set.parse_url_query(strResponse);

         string strMd5Here;

         strMd5Here = m_pcontext->m_papexcontext->file().md5(m_varFile["xml"].cast < ::memory_file >());

         string strMd5There;
         
         strMd5There = set["md5"];

         if(strMd5Here == strMd5There)
            return;

         strUrl = "http://fs.veriwell.net/fs/set?path=" + purl->url_encode(purl->get_script(m_varFile["url"]))
                  + "&server=" + purl->url_encode(purl->get_server(m_varFile["url"]));

         property_set setPut;

         m_pcontext->m_papexcontext->http().put(strUrl, m_varFile["xml"].cast < ::memory_file >(), setPut);

         return;
      }


      strUrl = "http://fs.veriwell.net/fs/set?path=" + purl->url_encode(purl->get_script(m_strPath))
               + "&server=" + purl->url_encode(purl->get_server(m_strPath));

      property_set set;

      m_pcontext->m_papexcontext->http().put(strUrl, &m_memfile, set);


   }



} // namespace fs



