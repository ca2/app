#include "framework.h"



#ifdef HAVE_OPENSSL
#include <openssl/ssl.h>
#endif


#if defined(LINUX)
//#include <ctype.h>
#endif


namespace youtube
{


   youtube_socket::youtube_socket(::sockets::socket_handler * h, const string & url_in):
      object(h.get_app()),
      base_socket(h),
      socket(h),
      stream_socket(h),
      tcp_socket(h),
      http_socket(h),
      http_tunnel(h),
      http_client_socket(h, url_in),
      websocket_client(h, url_in),
      m_estate(state_disconnected)
   {
   }


   youtube_socket::~youtube_socket()
   {
   }




   void youtube_socket::OnLine(const string & line)
   {

      if (m_bWebSocket)
      {


      }
      else
      {

         return ::sockets::websocket_client::OnLine(line);

      }

   }
      
      //void youtube_socket::OnLine(const string & line)
      //{
         //string strLine(line);
      //string_array stra;
      //switch(m_estate)
      //{
      //case state_disconnected:
      //   if(strLine.find(m_pcomm->get_nick() + " :>") > 0)
      //   {
      //      m_bTags = false;
      //      m_bMembership = false;
      //      m_bCommands = false;

      //      m_estate = state_cap_ls;
      //      write("CAP LS\r\n");

      //   }
      //   break;
      //case state_cap_ls:
      //{
      //   m_estate = state_cap_req_youtube_membership;
      //   write("CAP REQ :youtube.tv/membership\r\n");
      //}
      //break;
      //case state_cap_req_youtube_membership:
      //   {
      //      if (strLine.case_insensitive_find(" ack ") >= 0)
      //      {

      //         m_bMembership = true;

      //      }

      //      write("CAP REQ :youtube.tv/tags\r\n");
      //      m_estate = state_cap_req_youtube_tags;
      //   }
      //   break;


      //case state_cap_req_youtube_tags:
      //{

      //   if(strLine.case_insensitive_find(" ack ") >= 0)
      //   {
      //      m_bTags = true;
      //   }
      //   
      //   m_estate = state_cap_req_youtube_commands;

      //   write("CAP REQ :youtube.tv/commands\r\n");

      //}
      //break;

      //case state_cap_req_youtube_commands:
      //{

      //   if (strLine.case_insensitive_find(" ack ") >= 0)
      //   {
      //      m_bCommands = true;
      //   }

      //   m_estate = state_cap_list;

      //   write("CAP LIST\r\n");

      //}
      //break;

      //case state_cap_list:
      //{

      //   m_estate = state_joining;

      //   write("JOIN #" + m_pcomm->get_chan() + "\r\n");

      //}
      //break;

      //case state_joining:
      //{
      //   if(string_ends(strLine,"End of /NAMES list"))
      //   {
      //      //msg(".color YellowGreen");
      //      
      //      m_estate = state_connected;
      //      
      //      //write("PRIVMSG #" + m_pcomm->get_chan() + " :Hi!\r\n");

      //   }
      //   else
      //   {
      //      strsize iFind = strLine.rear_find(':');
      //      if (iFind <= 0)
      //      {
      //      }
      //      else
      //      {
      //         string strUser = strLine.substr(iFind+1);
      //         m_pcomm->m_straUser.add(strUser);
      //      }
      //   }

      //}
      //break;
      //case state_connected:
      //{
      //   
      //   process_line(strLine);
      //}
      //   break;
      //default:
      //   break;

      //}
   //}

   void youtube_socket::process_line(string strLine)
   {

      strsize iFind = strLine.find(" ");

      m_pcomm->on_line(strLine);

      //string s = acmefile()->as_string("Z:\\a.txt");

      //acmefile()->put_contents("Z:\\a.txt", s + strLine+"\n");

      if (iFind > 0)
      {

         string strTags;

         if (m_bTags)
         {

            strTags = strLine.left(iFind);

         }

         string_array stra;

         if (strTags.has_char())
         {

            stra.explode(";", strTags);

         }

         string strColor;

         if (stra.has_elements())
         {

            if (stra.find_first_begins_eat_ci(strColor, "@color=") > 0)
            {
               
               strColor.empty();

            }

         }

         string strUser;

         if (strColor.has_char())
         {
            
            stra.find_first_begins_eat_ci(strUser, "display-name=");

         }
         else
         {

            int iColon = strLine.find(':');

            int iExcla = strLine.find('!');

            strUser = strLine.substr(iColon + 1, iExcla - iColon);

         }


         

         if (strColor.has_char())
         {

            auto puser = papp->mainstage().get_user(strUser, "youtube", m_pcomm->m_strRoom, false);

            if (puser != NULL)
            {

               puser->m_color.parse_color(strColor);

               puser->m_color.m_iA = 255;

            }

            iFind = strLine.find(" ", iFind + 1);

            string str1 = strLine.substr(iFind + 1);

            if (str1.begins_eat("PRIVMSG #" + m_pcomm->get_chan() + " :"))
            {

               on_bot(strUser, str1);

            }

         }
         else
         {

            string str1 = strLine.substr(iFind + 1);

            strUser.case_insensitive_ends_eat("!");

            if (str1.begins_eat("JOIN #" + m_pcomm->get_chan()))
            {
            
               
               if (m_pcomm->m_straUser.find_first_ci(strUser) >= 0)
               {
                  m_pcomm->m_straUserAdd.add_unique(strUser);
                  output_debug_string("(already \"pres\") The user got present : \"" + strUser + "\"");
                  if (strUser == m_pcomm->get_chan())
                  {
                     m_pcomm->m_bStarting = false;
                  }
               }
               else if (strUser.case_insensitive_order(m_pcomm->m_strNick) == 0)
               {
                  m_pcomm->m_straUser.add_unique(strUser);
                  output_debug_string("The bot or user got present : \"" + strUser + "\"");
               }
               else if (strUser.case_insensitive_order(m_pcomm->get_chan()) == 0)
               {
                  m_pcomm->m_straUser.add_unique(strUser);
                  output_debug_string("The moderator or user got present : \"" + strUser + "\"");
               }
               else
               {
                  
                  m_pcomm->m_straUser.add_unique(strUser);
                  on_pres(strUser, "");
                  
               }
            }
            else if (str1.begins_eat("PART #" + m_pcomm->get_chan()))
            {

               if (strUser.case_insensitive_order(m_pcomm->m_strNick) == 0)
               {
                  m_pcomm->m_straUser.erase_ci(strUser);
                  output_debug_string("The bot or user got absent : \"" + strUser + "\"");
               }
               else if (strUser.case_insensitive_order(m_pcomm->get_chan()) == 0)
               {
                  m_pcomm->m_straUser.erase_ci(strUser);
                  output_debug_string("The moderator or user got absent : \"" + strUser + "\"");
               }
               else
               {

                  ::fork(get_app(), [=]()
                  {
                     
                     sleep(10000_ms);

                     if (m_pcomm->m_straUserAdd.case_insensitive_contains(strUser))
                     {

                        m_pcomm->m_straUserAdd.erase(strUser);

                     }
                     else
                     {

                        m_pcomm->m_straUser.erase(strUser);

                        on_pres(strUser, "unavailable");

                     }
                  });

               }

            }

         }

      }

   }

   bool youtube_socket::retrieve()
   {
      if(m_pcomm->m_straId.get_size() == 0)
         return false;
      m_pcomm->m_atom = m_pcomm->m_straId[0];
      string strSend;
      strSend.Format("RETR %s\r\n",m_pcomm->m_straIndex[0].c_str());
      write((const ::string &)strSend);
      m_pcomm->m_strHeaders.empty();
      m_pcomm->m_strBody.empty();
      m_pcomm->m_straId.erase_at(0);
      m_pcomm->m_straIndex.erase_at(0);
      return true;
   }


   void youtube_socket::SendPrompt()
   {

   }



   void youtube_socket::on_bot(string strUser, string strText)
   {

      string strResponse = m_pcomm->on_bot(strUser,strText);

      if(strResponse.has_char())
      {

         m_pcomm->msg(strResponse);

      }

   }


   void youtube_socket::on_pres(string strUser,string strType)
   {

      string strResponse = m_pcomm->on_pres(strUser,strType);

      if(strResponse.has_char())
      {

         m_pcomm->msg(strResponse);

      }

   }

   void youtube_socket::on_websocket_data(string str)
   {

      ::payload varJson;

      const char * pszJson = str;

      varJson.parse_network_payload(pszJson);

      if (varJson["type"] == "reply")
      {

         ::youtube::method m;

         if (m_pcomm->m_mapMethod.lookup(varJson["id"], m))
         {

            m_pcomm->on_method_reply(m, varJson["error"], varJson["data"]);

         }

      }
      else if (varJson["type"] == "event")
      {

         m_pcomm->on_event(varJson["event"], varJson["data"]);

      }

   }


} // namespace youtube


