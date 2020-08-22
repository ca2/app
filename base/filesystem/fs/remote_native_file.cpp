#include "framework.h"
#include "aura/net/sockets/_.h"
#include "aura/filesystem/fs/_fs.h"
#include "remote_native_file.h"

namespace fs
{


   remote_native_file::remote_native_file(var varFile) :
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
      if((m_nOpenFlags & ::file::mode_read) != 0)
      {
         return m_httpfile.get_size();
      }
      else
      {
         return m_memfile.get_size();
      }
   }

   filesize remote_native_file::seek(filesize lOff, ::file::e_seek nFrom)
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


   void remote_native_file::get_file_data()
   {
      /*if(m_nOpenFlags & ::file::mode_write)
      {
      __throw(::exception::exception("Cannot open remote_native_file for reading and writing simultaneously due the characteristic of possibility of extreme delayed streaming. The way it is implemented would also not work.\n It is build with this premisse."));
      return;
      }*/

      string strUrl;

      strUrl = "http://fs.veriwell.net/fs/get?path=" + System.url().url_encode(System.url().get_script(m_strPath))
               + "&server=" + System.url().url_encode(System.url().get_server(m_strPath));

      u32 dwAdd = 0;

      if(m_nOpenFlags & ::file::update_unknown_length_supported)
      {
         dwAdd |= ::file::update_unknown_length_supported;
      }

      m_httpfile.open(strUrl, ::file::type_binary | ::file::mode_read | dwAdd);

   }


   void remote_native_file::set_file_data()
   {
      string strUrl;


      if(m_varFile["xmledit"].cast < ::memory_file >() != nullptr)
      {

         strUrl = "http://fs.veriwell.net/fs/xmledit?path=" + System.url().url_encode(System.url().get_script(m_varFile["url"]))
                  + "&server=" + System.url().url_encode(System.url().get_server(m_varFile["url"]));

         property_set setRequest;

         setRequest["get_response"] = ""; // touch/create property to get_response

         Context.http().put(strUrl,m_varFile["xmledit"].cast < ::memory_file >(),setRequest);

         string strResponse(setRequest["get_response"]);

         property_set set;

         set.parse_url_query(strResponse);

         string strMd5Here;

         strMd5Here = Context.file().md5(m_varFile["xml"].cast < ::memory_file >());

         string strMd5There = set["md5"];

         if(strMd5Here == strMd5There)
            return;

         strUrl = "http://fs.veriwell.net/fs/set?path=" + System.url().url_encode(System.url().get_script(m_varFile["url"]))
                  + "&server=" + System.url().url_encode(System.url().get_server(m_varFile["url"]));

         property_set setPut;

         Context.http().put(strUrl, m_varFile["xml"].cast < ::memory_file >(), setPut);

         return;
      }


      strUrl = "http://fs.veriwell.net/fs/set?path=" + System.url().url_encode(System.url().get_script(m_strPath))
               + "&server=" + System.url().url_encode(System.url().get_server(m_strPath));

      property_set set;

      Context.http().put(strUrl, &m_memfile, set);


   }



} // namespace fs



