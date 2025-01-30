#include "framework.h"
#include "incoming_socket.h"
////#include "acme/exception/exception.h"
#include "acme/prototype/prototype/url.h"
#include "acme/prototype/prototype/url_domain.h"
#include "acme/platform/system.h"
#include "acme/prototype/time/_text_stream.h"


namespace netserver
{


   static ::collection::count s_countNetnodeSocket = 0;


   incoming_socket::incoming_socket()
   {

      //m_bSetCookie = true;

      s_countNetnodeSocket++;

   }


   incoming_socket::~incoming_socket()
   {
      s_countNetnodeSocket--;
   }

   //void incoming_socket::send_response()
   //{

   //   on_send_response();

   //   int iStatusCode;

   //   string strStatus;

   //   //auto code123 = ::__spin_namespace::idpool::g_pthis->http_status_code;

   //   if (outattr("http_status_code").is_new() || outattr("http_status").is_new())
   //   {

   //      if (outheaders().has_property("location"))
   //      {

   //         iStatusCode = 303; // 303 (See Other Location)

   //         strStatus = "See Other";

   //      }
   //      else
   //      {

   //         iStatusCode = 200;

   //         strStatus = "OK";

   //      }

   //      outattr("http_status_code") = iStatusCode;

   //      outattr("http_status") = strStatus;

   //   }

   //   outattr("http_version") = "HTTP/1.1";

   //   if (outheader("content-type").begins("image/"))
   //   {

   //      m_bSetCookie = false;

   //   }
   //   else if (outheader("content-type") == "application/javascript")
   //   {

   //      m_bSetCookie = false;

   //   }
   //   else if (outheader("content-type") == "text/css")
   //   {

   //      m_bSetCookie = false;

   //   }

   //   Respond();

   //}


   //void incoming_socket::OnExecute()
   //{

   //   string strUrl = m_request.attr("http_protocol") + "://" + m_request.header("host") + m_request.attr("request_uri");

   //   //informationf("incoming_socket::OnExecute: %s", strUrl.c_str());

   //   string str;

   //   for (auto& pproperty : m_request.headers().propertyptra())
   //   {

   //      ::string strNewHeader;

   //      strNewHeader.formatf("{%s=%s}", pproperty->m_atom.as_string().c_str(), pproperty->as_string().c_str());

   //      if (str.length() + strNewHeader.length() > 80)
   //      {

   //         informationf("Headers %s", str.c_str());

   //         str = strNewHeader;

   //      }
   //      else
   //      {

   //         str += strNewHeader;

   //      }

   //   }

   //   if (str.length() > 0)
   //   {

   //      informationf("Headers %s", str.c_str());

   //   }

   //   auto tickExecuteBeg = ::time::now();

   //   send_response();

   //   auto tickExecuteEnd = ::time::now();

   //   error() <<"====> " << (tickExecuteEnd - tickExecuteBeg).floating_second() << "s";

   //}


   //void incoming_socket::OnResponseComplete()
   //{

   //}


   //void incoming_socket::on_send_response()
   //{


   //}


   ////bool incoming_socket::http_filter_response_header(atom key, string_array & straValue)
   ////{
   ////   
   ////   if (key == "location" && straValue.get_count() >= 1)
   ////   {

   ////      auto psystem = system();

   ////      auto purl = psystem->url();

   ////      for (int i = 0; i < straValue.get_size(); i++)
   ////      {

   ////         url_domain domain;

   ////         domain.create(purl->get_server(straValue[i]));

   ////         if (domain.m_strName == "ca2.software")
   ////         {

   ////            //straValue[i] = "https://" + papp->m_strFontopusServer + purl->get_object(straValue[i]);

   ////         }

   ////      }

   ////   }
   ////   else if (!m_bSetCookie && key == "set-cookie")
   ////   {
   ////      
   ////      return false;

   ////   }

   ////   return true;

   ////}





   ////void incoming_socket::simple_file_server(const ::string & pszPath, bool bMatter)
   ////{

   ////   pointer_array < ::int_array > rangea;

   ////   if (inheader("range").has_character())
   ////   {
   ////      
   ////      string_array straItem;
   ////      
   ////      straItem.explode("=", inheader("range"));

   ////      if (straItem.get_count() == 2)
   ////      {
   ////         
   ////         string strUnit = straItem[0];
   ////         
   ////         string_array stra;
   ////         
   ////         stra.explode(",", straItem[1]);

   ////         for (int i = 0; i < stra.get_count(); i++)
   ////         {
   ////            
   ////            string_array straRange;
   ////            
   ////            straRange.explode("-", stra[i]);

   ////            if (straRange.get_count() == 2)
   ////            {
   ////               
   ////               rangea.add(___new ::int_array ());
   ////               
   ////               rangea.last_ptr()->add(atoi(straRange[0]));
   ////               
   ////               straRange[1].trim();

   ////               if (ansi_len(straRange[1]) == 0)
   ////                  rangea.last_ptr()->add(-1);
   ////               else
   ////                  rangea.last_ptr()->add(atoi(straRange[1]));

   ////            }

   ////         }

   ////      }

   ////   }

   ////   read_file(pszPath, &rangea);

   ////}


   ////void incoming_socket::simple_image_server(const ::string & pszPath, int iMaxWidth, int iMaxHeight)
   ////{

   ////   if (iMaxWidth <= 0 && iMaxHeight <= 0)
   ////   {
   ////      simple_file_server(pszPath);
   ////   }
   ////   else
   ////   {
   ////
   ////      ::image::image_pointer pimage;

   ////      pimage->load_image(pszPath);

   ////      double dRateW = 1.0;

   ////      if (iMaxWidth > 0)
   ////      {
   ////         if (pimage->width() > iMaxWidth)
   ////         {
   ////            dRateW = (double)iMaxWidth / (double)pimage->width();
   ////         }
   ////      }

   ////      double dRateH = 1.0;

   ////      if (iMaxHeight > 0)
   ////      {
   ////         if (pimage->height() > iMaxHeight)
   ////         {
   ////            dRateH = (double)iMaxHeight / (double)pimage->width();
   ////         }
   ////      }

   ////      double dRate = minimum(dRateW, dRateH);

   ////      ::image::image_pointer pimage;

   ////      pimage = create_image({(int)(pimage->width() * dRate),  (int)(pimage->height() * dRate)});

   ////      pimage->stretch_image(pimage);

   ////      ::image::encoding_options encodingoptions;

   ////      savepimage->m_eformat = pimage::e_format_jpeg;
   ////      savepimage->m_iQuality = 50;

   ////      outheader("content-type") = "image/jpeg";


   ////      pimage->save_to_file(&response().file(), encodingoptions);

   ////   }


   ////}


} // namespace netserver




