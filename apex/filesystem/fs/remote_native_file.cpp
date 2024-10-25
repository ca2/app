#include "framework.h"
#include "remote_native_file.h"
#include "acme/filesystem/file/memory_file.h"
#include "acme/filesystem/filesystem/listing.h"
#include "acme/prototype/prototype/url.h"
//#include "apex/networking/sockets/_sockets.h"
#include "acme/filesystem/filesystem/file_context.h"
#include "apex/networking/http/context.h"
#include "apex/platform/context.h"
#include "acme/platform/http.h"
#include "acme/platform/system.h"


namespace fs
{


   remote_native_file::remote_native_file(::payload payloadFile) :
      m_payloadFile(payloadFile)
   {

   }


   remote_native_file::~remote_native_file()
   {

   }


   memsize remote_native_file::read(void * p, ::memsize s)
   {

      return m_phttpfile->read(p, s);

   }


   void remote_native_file::write(const void * p, ::memsize s)
   {

      m_pmemfile->write(p, s);

   }


   filesize remote_native_file::size() const
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


   void remote_native_file::seek(filesize lOff, ::enum_seek eseek)
   {

      if((m_eopen & ::file::e_open_read) != 0)
      {

         return m_phttpfile->translate(lOff, eseek);

      }
      else
      {

         return m_pmemfile->translate(lOff, eseek);

      }

   }


   void remote_native_file::get_file_data()
   {
      /*if(m_nOpenFlags & ::file::e_open_write)
      {
      throw ::exception(::exception("Cannot open remote_native_file for reading and writing simultaneously due the characteristic of possibility of extreme delayed streaming. The way it is implemented would also not work.\n It is build with this premisse."));
      return;
      }*/

      ::url::url url(m_path);

      ::string strUrl;

      strUrl = "http://fs.veriwell.net/fs/get?path=" + ::url::encode(url.request().path())
               + "&host=" + ::url::encode(url.connect().host());

      ::file::e_open eopenAdd;

      if(m_eopen & ::file::e_open_update_unknown_length_supported)
      {

         eopenAdd |= ::file::e_open_update_unknown_length_supported;

      }

      m_phttpfile->open(strUrl, ::file::e_open_binary | ::file::e_open_read | eopenAdd);

   }


   void remote_native_file::set_file_data()
   {

      string strUrl;

      if(m_payloadFile["xmledit"].cast < ::memory_file >() != nullptr)
      {

         ::url::url url(m_payloadFile["url"]);

         strUrl = "http://fs.veriwell.net/fs/xmledit?path=" + ::url::encode(url.request().path())
            + "&host=" + ::url::encode(url.connect().host());

         property_set setRequest;

         setRequest["get_response"] = ""; // touch/create property to get_response

         http()->put(strUrl,m_payloadFile["xmledit"].cast < ::memory_file >(),setRequest);

         string strResponse(setRequest["get_response"].as_string());

         property_set set;

         set.parse_network_arguments(strResponse);

         string strMd5Here;

         strMd5Here = ::particle::file()->md5(m_payloadFile["xml"].cast < ::memory_file >());

         string strMd5There;
         
         strMd5There = set["md5"];

         if(strMd5Here == strMd5There)
            return;

         strUrl = "http://fs.veriwell.net/fs/set?path=" + ::url::encode(url.request().path())
                  + "&host=" + ::url::encode(url.connect().host());

         property_set setPut;

         http()->put(strUrl, m_payloadFile["xml"].cast < ::memory_file >(), setPut);

         return;
      }

      ::url::url url(m_path);

      strUrl = "http://fs.veriwell.net/fs/set?path=" + ::url::encode(url.request().path())
               + "&host=" + ::url::encode(url.connect().host());

      property_set set;

      http()->put(strUrl, m_pmemfile, set);


   }



} // namespace fs



