#include "framework.h"
#include "post_socket.h"
#include "apex/filesystem/filesystem/file_context.h"
#include "apex/platform/context.h"


namespace sockets
{


   http_post_socket::http_post_socket() //:
      //::object(&h),
      //base_socket(h),
      //socket(h),
      //stream_socket(h),
      //tcp_socket(h),
      //http_socket(h),
      //http_tunnel(h),
      //http_client_socket(h)
   {

      m_emethod = http_method_post;

   }



   http_post_socket::~http_post_socket()
   {
   }

   void http_post_socket::initialize_http_post_socket(const string & url_in)
      //::object(&h),
      //base_socket(h),
      //socket(h),
      //stream_socket(h),
      //tcp_socket(h),
      //http_socket(h),
      //http_tunnel(h),
      //http_client_socket(h, url_in)
   {

      initialize_http_client_socket(url_in);

      m_emethod = http_method_post;


   }


   void http_post_socket::AddField(const string & name, const string & value)
   {
      m_fields[name] = value;
   }


   void http_post_socket::AddMultilineField(const string & name, string_array & value)
   {
      m_fields[name] = value;
   }


   void http_post_socket::AddFile(const string & name,const string & filename,const string & type)
   {

      if (m_pcontext->m_papexcontext->file().exists(filename))
      {

         if (m_pmultipart == nullptr)
         {

            m_pmultipart = __new(multipart(this));

         }
         m_pmultipart->m_map[name].m_spfile = m_pcontext->m_papexcontext->file().get_file(filename, ::file::e_open_binary | ::file::e_open_read | ::file::e_open_share_deny_none);
         //m_mapFiles[name]              = filename;
         m_pmultipart->m_map[name].m_uiContentLength = m_pmultipart->m_map[name].m_spfile->get_size();
         m_pmultipart->m_map[name].m_strContentType = type;
         //m_mapContentLength[filename]  = m_pcontext->m_papexcontext->file().length(filename);
         //m_mapContentType[filename]    = type;
         //m_bMultipart                  = true;

      }
      else
      {

//#ifdef BSD_STYLE_SOCKETS
//
//         FATAL("AddFile " << Errno << bsd_socket_error(Errno));
//
//#endif

         SetCloseAndDelete();

      }

   }


   bool http_post_socket::step()
   {

      if (m_pmultipart != nullptr)
      {

         DoMultipartPost();

      }
      else
      {

         string strBody;

         if (m_fields.has_property("raw_text"))
         {

            strBody = m_fields["raw_text"];

            string strContentType = m_fields["raw_text_content_type"];

            inheader(__id(content_type)) = strContentType;

         }
         else if (m_fields.has_property("network_payload"))
         {

            auto & payload = m_fields["network_payload"];

            if (payload.get_type() == ::e_type_property_set)
            {

               payload.propset().get_network_payload(strBody);

               INFORMATION("JSON BODY: " << strBody);

               string strContentType = inheader(__id(content_type)).string();

               if (strContentType.find_ci("application/json") < 0)
               {

                  inheader(__id(content_type)) = "application/json" + ::str().has_char(strContentType, ";", strContentType);

               }

            }

         }
         else if (m_fields.has_property("xml") && m_fields["xml"].get_type() == ::e_type_element)
         {

            throw ::exception(todo, "xml");

            //::xml::node * pnode = m_fields["xml"].cast < ::xml::node >();
            //body = pnode->get_xml();
            //body.trim();
            //if(inheader(__id(content_type)).string().find_ci("application/xml") < 0)
            //{
            //   inheader(__id(content_type)) = "application/xml; " + inheader(__id(content_type)).string();
            //}

         }
         else
         {

            m_fields.get_network_arguments(strBody);

            if (inheader(__id(content_type)).string().find_ci("application/x-www-form-urlencoded") < 0)
            {

               inheader(__id(content_type)) = "application/x-www-form-urlencoded" + ::str().has_char(inheader(__id(content_type)).string(), "; ");

            }

         }

         m_request.attr(__id(http_method)) = "POST";

         m_request.attr(__id(http_version)) = "HTTP/1.1";

         string strHost = GetUrlHost();

         inheader(__id(host)) = strHost; // oops - this is actually a request header that we're adding..

         string strUserAgent = MyUseragent();

         if (m_request.attr("minimal_headers").is_false())
         {

            inheader(__id(user_agent)) = "ca2_netnode";

            if (inheader(__id(accept)).is_empty())
            {

               inheader(__id(accept)) = "text/html, text/plain, application/xml, */*;q=0.01";

            }
            //inheader(__id(connection)) = "close";

         }

         auto content_length = strBody.length();

         inheader(__id(content_length)) = content_length;

#ifdef WINRT_SOCKETS

         m_bExpectResponse = true;

         m_bExpectRequest = false;

#endif

         SendRequest();

         if (strBody.has_char())
         {
            
            // send body
            print(strBody);

         }

      }

      return ::success;

   }


   void http_post_socket::DoMultipartPost()
   {

      u64 length = 0; // calculate content_length of our post body

      string tmp;

      if (m_pmultipart->m_strOverrideBoundary_is_the_bounday_the_issue_i_e_should_it_be_the_same_across_appends.has_char())
      {

         m_boundary = m_pmultipart->m_strOverrideBoundary_is_the_bounday_the_issue_i_e_should_it_be_the_same_across_appends;

      }
      else
      {

         // Thanks Mummi for letting me program till dawn...
         // Thanks Alfredo Plays and mates from Twitch for keeping the vibe up...
         // And Denis for sticking on details and being so patient with so stuborn person like me and a software like ca2...

         m_pmultipart->m_strOverrideBoundary_is_the_bounday_the_issue_i_e_should_it_be_the_same_across_appends = m_boundary;

      }

      string strFields;

      {

         for(auto & pproperty : m_fields)
         {

            atom & atom = pproperty->m_atom;

            ::payload & payload = *pproperty;

            strFields += "--" + m_boundary + "\r\nContent-Disposition: form-data; name=\"" + atom + "\"\r\n\r\n";

            string value = payload.string();

            strFields += value + "\r\n";

         }

         length += (long)strFields.get_length();

      }

      {

         for (auto & pair : m_pmultipart->m_map)
         {

            string & name = pair.element1();

            u64 content_length = pair.element2().m_uiContentLength;

            string filename;

            if (pair.element2().m_spfile->get_file_path().has_char())
            {

               filename = "; filename=\"" + string(::file::path(pair.element2().m_spfile->get_file_path()).name()) + "\"";

            }

            string content_type;

            if (pair.element2().m_strContentType.has_char())
            {

               content_type = "Content-Type: " + pair.element2().m_strContentType + "\r\n";

            }

            string strContentLength;

            strContentLength = "Content-Length: " + __string(content_length) + "\r\n";

            tmp = "--" + m_boundary + "\r\nContent-Disposition: form-data; name=\"" + name + "\""+ filename + "\r\n"
                  + content_type + strContentLength + "\r\n";

            length += (long)tmp.get_length();

            length += content_length;

            length += 2; // crlf after file

         }
         //POSITION pos = m_mapFiles.get_start_position();

         //for(; pos != nullptr; )
         //{
         //
         //   string name;
         //
         //   string filename;
         //
         //   m_mapFiles.get_next_assoc(pos, name, filename);
         //
         //   u64 content_length = m_mapContentLength[filename];

         //   string content_type = m_mapContentType[filename];

         //   tmp = "--" + m_boundary + "\r\n"
         //      "content-disposition: form-data; name=\"" + name + "\"; filename=\"" + filename + "\"\r\n"
         //      "content-type: " + content_type + "\r\n"
         //      "\r\n";

         //   length += (long)tmp.get_length();

         //   length += content_length;

         //   length += 2; // crlf after file

         //}

      }

      // end
      tmp = "--" + m_boundary + "--\r\n";

      length += (long)tmp.get_length();

      // build header, send body
      m_request.attr(__id(http_method)) = "POST";

      m_request.attr(__id(http_version)) = "HTTP/1.1";

      string strHost = GetUrlHost();

      inheader(__id(host)) = strHost; // oops - this is actually a request header that we're adding..

      inheader(__id(user_agent)) = MyUseragent();

      inheader(__id(accept)) = "text/html, text/plain, */*;q=0.01";

      //inheader(__id(connection)) = "close";

      inheader(__id(content_type)) = "multipart/form-data; boundary=" + m_boundary;

      inheader(__id(content_length)) = (i64) length;

#ifdef WINRT_SOCKETS

      m_bExpectResponse = true;

      m_bExpectRequest = false;

#endif

      SendRequest();

      // send fields
      {
         //tmp = "";
         //for(auto & property : m_fields)
         //{
         //   atom & atom = property.element1();
         //   ::payload & payload = property.element2();
         //   tmp += "--" + m_boundary + "\r\nContent-Disposition: form-data; name=\"" + atom.to_string() + "\"\r\n\r\n";
         //   string value = payload.string();
         //   tmp += value + "\r\n";
         //   //for(int j = 0; j < payload.get_count(); j++)
         //   //{
         //     // string value = payload[j].string();
         //      //tmp += value + "\r\n";
         //   //}
         //}

         if (strFields.has_char())
         {

            print(strFields);

         }

      }

      // send files
      {

         for (auto & pair : m_pmultipart->m_map)
         {

            string & name = pair.element1();

            u64 content_length = pair.element2().m_uiContentLength;

            string filename;

            if (pair.element2().m_spfile->get_file_path().has_char())
            {

               filename = "; filename=\"" + string(::file::path(pair.element2().m_spfile->get_file_path()).name()) + "\"";

            }

            string content_type;

            if (pair.element2().m_strContentType.has_char())
            {

               content_type = "Content-Type: " + pair.element2().m_strContentType + "\r\n";

            }

            string strContentLength;

            strContentLength = "Content-Length: " + __string(content_length) + "\r\n";

            tmp = "--" + m_boundary + "\r\nContent-Disposition: form-data; name=\"" + name + "\"" + filename + "\r\n"
                  + content_type + strContentLength + "\r\n";

            print( tmp );
            //{
            //file_pointer spfile(e_create);
            //if(spfile->open(filename, ::file::e_open_binary | ::file::e_open_read).succeeded())
            //{

            memory m;

            m.set_size((u32) (content_length));

            pair.element2().m_spfile->read(m.get_data(), m.get_size());

            write(m.get_data(), m.get_size());

            //transfer_from(*pair.element2().m_spfile, content_length);
            //}
            //}
            print("\r\n");
         }
         //POSITION pos = m_mapFiles.get_start_position();
         //for (; pos != nullptr;)
         //{
         //   string name;
         //   string filename;
         //   m_mapFiles.get_next_assoc(pos, name, filename);
         //   string content_type = m_mapContentType[filename];
         //   tmp = "--" + m_boundary + "\r\n"
         //      "content-disposition: form-data; name=\"" + name + "\"; filename=\"" + filename + "\"\r\n"
         //      "content-type: " + content_type + "\r\n"
         //      "\r\n";
         //   write(tmp);
         //   {
         //      file_pointer spfile(e_create);
         //      if (spfile->open(filename, ::file::e_open_binary | ::file::e_open_read).succeeded())
         //      {
         //         transfer_from(*spfile);
         //      }
         //   }
         //   write("\r\n");
         //}
      }

      // end of send
      print("--" + m_boundary + "--\r\n");

   }


   //void http_post_socket::SetMultipart()
   //{
   //   m_pmulbMultipart = true;
   //}


}



