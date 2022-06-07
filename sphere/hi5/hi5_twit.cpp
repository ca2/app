#include "framework.h"
#include <time.h>
#include "aura/net/sockets/http/sockets_http_post_socket.h"


namespace hi5
{


   string prepare_basic_authentication(::object * pobject, const ::string & inParam1, const ::string & inParam2 );


   namespace oAuthTwitterApiUrls
   {
      /* Twitter OAuth API URLs */
   };

   /* Default values used in twitcurl */
   namespace twit_defaults
   {
   };


   /* Default twitter URLs */
   namespace twitter_defaults
   {


   };


   /*++
   * @method: twit::twit
   *
   * @description: constructor
   *
   * @input: none
   *
   * @output: none
   *
   *--*/
   twit::twit(::object * pobject, simple_log * psimplelog, index iLogTarget) :
      object(pobject),
      simple_log(psimplelog, iLogTarget),
      /* Constants */
      TWIT_COLON(":"),
      TWIT_EOS('\0'),

      /* Miscellaneous data used to build twitter URLs*/
      TWIT_SEARCHQUERYSTRING("?q("),
      TWIT_SCREENNAME("?screen_name("),
      TWIT_USERID("?user_id("),
      TWIT_EXTENSIONFORMAT(".xml"),
      TWIT_TARGETSCREENNAME("?target_screen_name("),
      TWIT_TARGETUSERID("?target_id("),

      /* Search URLs */
      TWIT_SEARCH_URL("http://search.twitter.com/search.atom"),

      /* Status URLs */
      TWIT_STATUSUPDATE_URL("http://twitter.com/statuses/update.xml"),
      TWIT_STATUSSHOW_URL("http://twitter.com/statuses/show/"),
      TWIT_STATUDESTROY_URL("http://twitter.com/statuses/destroy/"),

      /* Timeline URLs */
      TWIT_PUBLIC_TIMELINE_URL("http://twitter.com/statuses/public_timeline.xml"),
      TWIT_FEATURED_USERS_URL("http://twitter.com/statuses/featured.xml"),
      TWIT_FRIENDS_TIMELINE_URL("http://twitter.com/statuses/friends_timeline.xml"),
      TWIT_MENTIONS_URL("http://twitter.com/statuses/mentions.xml"),
      TWIT_USERTIMELINE_URL("http://twitter.com/statuses/user_timeline.xml"),

      /* Users URLs */
      TWIT_SHOWUSERS_URL("http://twitter.com/users/show.xml"),
      TWIT_SHOWFRIENDS_URL("http://twitter.com/statuses/friends.xml"),
      TWIT_SHOWFOLLOWERS_URL("http://twitter.com/statuses/followers.xml"),

      /* Direct messages URLs */
      TWIT_DIRECTMESSAGES_URL("http://twitter.com/direct_messages.xml"),
      TWIT_DIRECTMESSAGENEW_URL("http://twitter.com/direct_messages/new.xml"),
      TWIT_DIRECTMESSAGESSENT_URL("http://twitter.com/direct_messages/sent.xml"),
      TWIT_DIRECTMESSAGEDESTROY_URL("http://twitter.com/direct_messages/destroy/"),

      /* Friendships URLs */
      TWIT_FRIENDSHIPSCREATE_URL("http://twitter.com/friendships/create.xml"),
      TWIT_FRIENDSHIPSDESTROY_URL("http://twitter.com/friendships/destroy.xml"),
      TWIT_FRIENDSHIPSSHOW_URL("http://twitter.com/friendships/show.xml"),

      /* Social graphs URLs */
      TWIT_FRIENDSIDS_URL("http://twitter.com/friends/ids.xml"),
      TWIT_FOLLOWERSIDS_URL("http://twitter.com/followers/ids.xml"),

      /* Ac::count URLs */
      TWIT_ACCOUNTRATELIMIT_URL("http://twitter.com/account/rate_limit_status.xml"),

      /* Favorites URLs */
      TWIT_FAVORITESGET_URL("http://twitter.com/favorites.xml"),
      TWIT_FAVORITECREATE_URL("http://twitter.com/favorites/create/"),
      TWIT_FAVORITEDESTROY_URL("http://twitter.com/favorites/destroy/"),

      /* Block URLs */
      TWIT_BLOCKSCREATE_URL("http://twitter.com/blocks/create/"),
      TWIT_BLOCKSDESTROY_URL("http://twitter.com/blocks/destroy/"),

      /* Saved Search URLs */
      TWIT_SAVEDSEARCHGET_URL("http://twitter.com/saved_searches.xml"),
      TWIT_SAVEDSEARCHSHOW_URL("http://twitter.com/saved_searches/show/"),
      TWIT_SAVEDSEARCHCREATE_URL("http://twitter.com/saved_searches/create.xml"),
      TWIT_SAVEDSEARCHDESTROY_URL("http://twitter.com/saved_searches/destroy/"),

      /* Trends URLs */
      TWIT_TRENDS_URL("http://api.twitter.com/1/trends.network_payload"),
      TWIT_TRENDSDAILY_URL("http://api.twitter.com/1/trends/daily.network_payload"),
      TWIT_TRENDSCURRENT_URL("http://api.twitter.com/1/trends/current.network_payload"),
      TWIT_TRENDSWEEKLY_URL("http://api.twitter.com/1/trends/weekly.network_payload"),
      TWIT_TRENDSAVAILABLE_URL("http://api.twitter.com/1/trends/available.network_payload"),
      m_oauth(pobject, psimplelog, iLogTarget)
   {

      m_setHttp["raw_http"] = true;

      m_setHttp["minimal_headers"] = true;

      m_curlLoginParamsSet = false ;

   }

   /*++
   * @method: twit::~twit
   *
   * @description: destructor
   *
   * @input: none
   *
   * @output: none
   *
   *--*/
   twit::~twit()
   {
   }

   /*++
   * @method: twit::getTwitterUsername
   *
   * @description: method to get stored Twitter username
   *
   * @input: none
   *
   * @output: twitter username
   *
   *--*/
   string & twit::getTwitterUsername()
   {
      return m_twitterUsername;
   }

   /*++
   * @method: twit::getTwitterPassword
   *
   * @description: method to get stored Twitter password
   *
   * @input: none
   *
   * @output: twitter password
   *
   *--*/
   string & twit::getTwitterPassword()
   {
      return m_twitterPassword;
   }

   /*++
   * @method: twit::setTwitterUsername
   *
   * @description: method to set username
   *
   * @input: userName
   *
   * @output: none
   *
   *--*/
   void twit::setTwitterUsername( string & userName )
   {
      if( userName.get_length() )
      {
         m_twitterUsername = userName;
         m_curlLoginParamsSet = false;
      }
   }

   /*++
   * @method: twit::setTwitterPassword
   *
   * @description: method to set password
   *
   * @input: passWord
   *
   * @output: none
   *
   *--*/
   void twit::setTwitterPassword( string & passWord )
   {
      if( passWord.get_length() )
      {
         m_twitterPassword = passWord;
         m_curlLoginParamsSet = false;
      }
   }


   /*++
   * @method: twit::search
   *
   * @description: method to return tweets that match a specified query.
   *
   * @input: query - search query in string format
   *
   * @output: true if GET is success, otherwise false. This does not check http
   *          response by twitter. Use get_response() for that.
   *
   *--*/
   bool twit::search( string & query )
   {
      bool retVal = false;
      /* Prepare URL */
      string strUrl( "" );
      strUrl = TWIT_SEARCH_URL;
      strUrl.append( TWIT_SEARCHQUERYSTRING );
      strUrl.append( query );

      /* Perform GET */
      retVal = performGet( strUrl );
      return retVal;
   }


   string twit::mediaUpload(file_pointer pfile, string strMimeType, string strCategory)
   {

      m_strError = "";

      m_strRequest = "REQUEST: mediaUpload(pfile, \""+strMimeType+"\", \""+strCategory+"\")";

      log_line(m_strRequest);

      i64 iLen = pfile->get_length();

      if (iLen <= 0)
      {

         m_strError = "ERROR: Cannot upload media, it is zero size.";

         log_line(m_strError);

         return m_strError;

      }

      string strMediaId = mediaUploadInit(int (iLen), strMimeType, strCategory);

      if (strMediaId.is_empty())
      {

         m_strError = "ERROR: mediaUploadInit failure (1), " + m_strError;

         log_line(m_strError);

         return m_strError;

      }
      else if (strMediaId.begins_ci("ERROR: "))
      {

         m_strError = "ERROR: mediaUploadInit failure (2), " + strMediaId;

         log_line(m_strError);

         return m_strError;

      }

      i64 iChunkSize = 1024 * 1024;

      i64 iLastChunkSize = iLen % iChunkSize;

      i64 iChunkCount = iLen / iChunkSize;

      if (iLastChunkSize <= 0)
      {

         iLastChunkSize = iChunkSize;

      }
      else
      {

         if (iLastChunkSize < 1024)
         {

            if (iChunkCount > 0)
            {

               iLastChunkSize += iChunkSize;

            }
            else
            {

               iChunkCount++;

            }

         }
         else
         {

            iChunkCount++;

         }

      }

      memory mem;

      string boundary_is_the_bounday_the_issue_i_e_should_it_be_the_same_across_appends;

      pfile->seek_to_begin();

      for (index i = 0; i < iChunkCount; i++)
      {

         i64 iSize;

         if (i >= iChunkCount - 1)
         {

            iSize = iLastChunkSize;

         }
         else
         {

            iSize = iChunkSize;

         }

         //mem.set_size(iSize);

         //memsize uRead;

         //i64 iPos = 0;

         //::u32 tickStart= ::duration::now();

         //while ((uRead = pfile->read(&mem.get_data()[iPos], mem.get_size() - iPos)) > 0)
         //{
         //
         //   iPos += uRead;

         //   if (iPos == mem.get_size())
         //   {

         //      break;

         //   }

         //   sleep(5_ms);

         //   if (tickStart.elapsed() > 60 * 1000)
         //   {

         //      m_strError = "ERROR: timeout reading source file, " + m_strError;

         //      log_line(m_strError);

         //      return m_strError;

         //   }

         //}

         //if (iPos < mem.get_size())
         //{

         //   m_strError = "ERROR: timeout reading Entire source file, " + m_strError;

         //   log_line(m_strError);

         //   return m_strError;

         //}


         if (!mediaUploadAppend(strMediaId, i, pfile, int (iSize), strMimeType, boundary_is_the_bounday_the_issue_i_e_should_it_be_the_same_across_appends))
         {

            m_strError = "ERROR: mediaUploadAppend failed chunk=" + __string(i) + ", " + m_strError;

            log_line(m_strError);

            return m_strError;

         }

      }

      ::payload v = mediaUploadFinalize(strMediaId);

      if (v.is_new())
      {

         m_strError = "ERROR: mediaUploadFinalize general failure, " + m_strError;

         log_line(m_strError);

         return m_strError;

      }

      if (v.has_property("processing_info"))
      {

         while (true)
         {

            string strState = v["processing_info"]["state"];

            if (strState == "pending" || strState == "in_progress")
            {

               string strCheckAfterSecs = v["processing_info"]["check_after_secs"];

               log_line("PROCESSING: check after second = " + strCheckAfterSecs);

               sleep(atoi(strCheckAfterSecs) * 1000);

            }
            else if (strState == "succeeded")
            {

               m_strError = "REPLY: " + strMediaId;

               log_line(m_strError);

               return strMediaId;

            }
            else
            {

               string strErrorMessage;

               strErrorMessage = "ERROR: progress_percent:" + v["processing_info"]["progress_percent"];
               strErrorMessage += "state:" + v["processing_info"]["state"];
               strErrorMessage += "error.code:" + v["processing_info"]["error"]["code"];
               strErrorMessage += "error.name:" + v["processing_info"]["error"]["name"];
               strErrorMessage += "error.message:" + v["processing_info"]["error"]["message"];

               m_strError = strErrorMessage + ", " + m_strError;

               log_line(m_strError);

               return m_strError;

            }

            v = mediaUploadStatus(strMediaId);

         }

      }

      m_strError = "REPLY: " + strMediaId;

      log_line(m_strError);

      return strMediaId;

   }


   string twit::mediaUploadInit(int iTotalSize, string strMimeType, string strCategory)
   {

      m_strRequest = "REQUEST: mediaUploadInit(" + __string(iTotalSize) + ", \"" + strMimeType + "\", \"" + strCategory + "\")";

      log_line(m_strRequest);

      property_set post;

      post["command"] = "INIT";

      post["total_bytes"] = iTotalSize;

      post["media_type"] = strMimeType;

      if (!strMimeType.begins_ci("image/") || strMimeType.compare_ci("image/gif") == 0)
      {

         post["media_category"] = strCategory;

      }

      string strResp = m_strResponse;

      string strUrl("https://upload.twitter.com/1.1/media/upload.network_payload");

      bool bOk = performMultiPartPost(strUrl, post, false);

      ::payload v;

      const char * p = m_strResponse;

      m_strError = m_strResponse;

      try
      {

         v.parse_network_payload(p);

      }
      catch (::exception * pe)
      {

         ::exception_pointer esp(pe);

         m_strError = "EXCEPTION: \"" + pe->get_message() + "\" parsing\"" + m_strResponse + "\"";

         bOk = false;

      }
      catch (...)
      {

         m_strError = "EXCEPTION: ... parsing\"" + m_strResponse + "\"";

         bOk = false;

      }

      if (!bOk)
      {

         m_strError = "ERROR: REPLY: " + m_strError;

         log_line(m_strError);

         return m_strError;

      }

      m_strError = "REPLY: " + m_strError;

      log_line(m_strError);

      return v["media_id_string"];

   }


   bool twit::mediaUploadAppend(string strMediaId, index iIndex, file_pointer pfile, int iSize, string strMimeType, string & boundary_is_the_bounday_the_issue_i_e_should_it_be_the_same_across_appends)
   {

      log_line("mediaUploadAppend(\"" + strMediaId + "\", " + __string(iIndex) + ", memory(size=" + __string(iSize) + "))");

      property_set post;

      ::sockets::multipart multipart(this);

      multipart.m_map["media"].m_spfile = pfile;

      multipart.m_map["media"].m_uiContentLength = iSize;

      multipart.m_map["media"].m_strContentType = strMimeType;

      multipart.m_strOverrideBoundary_is_the_bounday_the_issue_i_e_should_it_be_the_same_across_appends = boundary_is_the_bounday_the_issue_i_e_should_it_be_the_same_across_appends;

      post["multipart"] = &multipart;
      post["post"]["command"] = "APPEND";
      post["post"]["media_id"] = strMediaId;
      post["post"]["segment_index"] = iIndex;

      string strResp = m_strResponse;

      string strUrl("https://upload.twitter.com/1.1/media/upload.network_payload");

      //strUrl += "?command=APPEND&segment_index=" + ::str().from(iIndex);

      bool bOk = performMultiPartPost(strUrl, post, true);

      if (!bOk)
      {

         m_strError = "ERROR: REPLY: " + m_strResponse;

      }
      else
      {

         m_strError = "REPLY: " + m_strResponse;

      }

      boundary_is_the_bounday_the_issue_i_e_should_it_be_the_same_across_appends = multipart.m_strOverrideBoundary_is_the_bounday_the_issue_i_e_should_it_be_the_same_across_appends;

      log_line(m_strError);

      return bOk;

   }


   ::payload twit::mediaUploadFinalize(string strMediaId)
   {

      log_line("mediaUploadFinalize(\"" + strMediaId + "\")");

      property_set post;

      post["command"] = "FINALIZE";

      post["media_id"] = strMediaId;

      string strResp = m_strResponse;

      string strUrl("https://upload.twitter.com/1.1/media/upload.network_payload");

      bool bOk = performMultiPartPost(strUrl, post, false);

      ::payload v;

      const char * p = m_strResponse;

      m_strError = m_strResponse;

      try
      {

         v.parse_network_payload(p);

      }
      catch (::exception * pe)
      {

         ::exception_pointer esp(pe);

         m_strError = "EXCEPTION: \"" + pe->get_message() + "\" parsing\"" + m_strResponse + "\"";

         bOk = false;

      }
      catch (...)
      {

         m_strError = "EXCEPTION: ... parsing\"" + m_strResponse + "\"";

         bOk = false;

      }

      if(!bOk)
      {

         m_strError = "ERROR: REPLY: " + m_strError;

         log_line(m_strError);

         return ::e_type_new;

      }

      m_strError = "REPLY: " + m_strError;

      log_line(m_strError);

      return v;

   }


   ::payload twit::mediaUploadStatus(string strMediaId)
   {

      log_line("mediaUploadFinalize(\"" + strMediaId + "\")");

      property_set post;

      string strUrl("https://upload.twitter.com/1.1/media/upload.network_payload");

      strUrl += "?command=STATUS&media_id=" + strMediaId;

      bool bOk = performGet(strUrl);

      ::payload v;

      const char * p = m_strResponse;

      m_strError = m_strResponse;

      try
      {

         v.parse_network_payload(p);

      }
      catch (::exception * pe)
      {

         ::exception_pointer esp(pe);

         m_strError = "EXCEPTION: \"" + pe->get_message() + "\" parsing\"" + m_strResponse + "\"";

         bOk = false;

      }
      catch (...)
      {

         m_strError = "EXCEPTION: ... parsing\"" + m_strResponse + "\"";

         bOk = false;

      }

      if (!bOk)
      {

         m_strError = "ERROR: REPLY: " + m_strError;

         log_line(m_strError);

         return ::e_type_new;

      }

      m_strError = "REPLY: " + m_strError;

      log_line(m_strError);

      return v;

   }


   /*++
   * @method: twit::statusUpdate
   *
   * @description: method to update new status message in twitter profile
   *
   * @input: newStatus
   *
   * @output: true if POST is success, otherwise false. This does not check http
   *          response by twitter. Use get_response() for that.
   *
   *--*/
   bool twit::statusUpdate( string & newStatus, string_array straMediaIds, string strReplyStatusId)
   {

      m_strRequest = "hi5::twit::statusUpdate(\"" + newStatus + "\", {" + straMediaIds.implode(", ")+"})" ;

      m_strResponse = "";

      m_strError = "";

      log_line(m_strRequest);

      if (newStatus.is_empty() && straMediaIds.is_empty())
      {

         m_strError = "ERROR: hi5:twit::statusUpdate : Won't tweet empty status!!";

         log_line(m_strError);

         return false;

      }

      bool bOk;

      property_set post;

      post["status"] = newStatus;

      string strUrl("https://api.twitter.com/1.1/statuses/update.network_payload");

      int i = 0;

      if (straMediaIds.has_elements())
      {

         strUrl += "?media_ids=" + straMediaIds.implode(",");
         i++;

      }

      if (strReplyStatusId.has_char())
      {

         if (i > 0)
         {
            strUrl += "&";
         }
         else
         {
            strUrl += "?";
         }

         strUrl += "in_reply_to_status_id=" + strReplyStatusId;

      }

      bOk = performPost( strUrl, post );

      if (bOk)
      {

         m_strError = "REPLY: " + m_strResponse;

      }
      else
      {

         m_strError = "ERROR: REPLY: " + m_strResponse;

      }

      log_line(m_strError);

      return bOk;

   }

   /*++
   * @method: twit::statusShowById
   *
   * @description: method to get a status message by its atom
   *
   * @input: statusId - a number in string format
   *
   * @output: true if GET is success, otherwise false. This does not check http
   *          response by twitter. Use get_response() for that.
   *
   *--*/
   bool twit::statusShowById( string & statusId )
   {
      bool retVal = false;
      if( true && statusId.get_length() )
      {
         /* Prepare URL */
         string strUrl( "" );
         strUrl = TWIT_STATUSSHOW_URL;
         strUrl.append( statusId );
         strUrl.append( TWIT_EXTENSIONFORMAT );

         /* Perform GET */
         retVal = performGet( strUrl );
      }
      return retVal;
   }

   /*++
   * @method: twit::statusDestroyById
   *
   * @description: method to delete a status message by its atom
   *
   * @input: statusId - a number in string format
   *
   * @output: true if DELETE is success, otherwise false. This does not check http
   *          response by twitter. Use get_response() for that.
   *
   *--*/
   bool twit::statusDestroyById( string & statusId )
   {
      bool retVal = false;
      if( true && statusId.get_length() )
      {
         /* Prepare URL */
         string strUrl( "" );
         strUrl = TWIT_STATUDESTROY_URL;
         strUrl.append( statusId );
         strUrl.append( TWIT_EXTENSIONFORMAT );

         /* Perform DELETE */
         retVal = performDelete( strUrl );
      }
      return retVal;
   }

   /*++
   * @method: twit::timelinePublicGet
   *
   * @description: method to get public timeline
   *
   * @input: none
   *
   * @output: true if GET is success, otherwise false. This does not check http
   *          response by twitter. Use get_response() for that.
   *
   *--*/
   bool twit::timelinePublicGet()
   {
      bool retVal = false;
      if( true )
      {
         /* Perform GET */
         retVal = performGet( TWIT_PUBLIC_TIMELINE_URL );
      }
      return retVal;
   }

   /*++
   * @method: twit::featuredUsersGet
   *
   * @description: method to get featured users
   *
   * @input: none
   *
   * @output: true if GET is success, otherwise false. This does not check http
   *          response by twitter. Use get_response() for that.
   *
   *--*/
   bool twit::featuredUsersGet()
   {
      bool retVal = false;
      if( true )
      {
         /* Perform GET */
         retVal = performGet( TWIT_FEATURED_USERS_URL );
      }
      return retVal;
   }

   /*++
   * @method: twit::timelineFriendsGet
   *
   * @description: method to get friends timeline
   *
   * @input: none
   *
   * @output: true if GET is success, otherwise false. This does not check http
   *          response by twitter. Use get_response() for that.
   *
   *--*/
   bool twit::timelineFriendsGet()
   {
      bool retVal = false;
      if( true )
      {
         /* Perform GET */
         retVal = performGet( TWIT_FRIENDS_TIMELINE_URL );
      }
      return retVal;
   }

   /*++
   * @method: twit::mentionsGet
   *
   * @description: method to get mentions
   *
   * @input: none
   *
   * @output: true if GET is success, otherwise false. This does not check http
   *          response by twitter. Use get_response() for that.
   *
   *--*/
   bool twit::mentionsGet()
   {
      bool retVal = false;
      if( true )
      {
         /* Perform GET */
         retVal = performGet( TWIT_MENTIONS_URL );
      }
      return retVal;
   }

   /*++
   * @method: twit::timelineUserGet
   *
   * @description: method to get mentions
   *
   * @input: userInfo - screen name or user atom in string format,
   *         isUserId - true if userInfo contains an atom
   *
   * @output: true if GET is success, otherwise false. This does not check http
   *          response by twitter. Use get_response() for that.
   *
   *--*/
   bool twit::timelineUserGet( string userInfo, bool isUserId )
   {
      bool retVal = false;
      if( true )
      {
         /* Prepare URL */
         string strUrl( "" );
         strUrl = build_url(TWIT_USERTIMELINE_URL, userInfo, isUserId );

         /* Perform GET */
         retVal = performGet( strUrl );
      }
      return retVal;
   }

   /*++
   * @method: twit::userGet
   *
   * @description: method to get a user's profile
   *
   * @input: userInfo - screen name or user atom in string format,
   *         isUserId - true if userInfo contains an atom
   *
   * @output: true if GET is success, otherwise false. This does not check http
   *          response by twitter. Use get_response() for that.
   *
   *--*/
   bool twit::userGet( string & userInfo, bool isUserId )
   {
      bool retVal = false;
      if( true && userInfo.get_length() )
      {
         /* set URL */
         string strUrl( "" );
         strUrl = build_url(TWIT_SHOWUSERS_URL, userInfo, isUserId );

         /* Perform GET */
         retVal = performGet( strUrl );
      }
      return retVal;
   }

   /*++
   * @method: twit::friendsGet
   *
   * @description: method to get a user's friends
   *
   * @input: userInfo - screen name or user atom in string format,
   *         isUserId - true if userInfo contains an atom
   *
   * @output: true if GET is success, otherwise false. This does not check http
   *          response by twitter. Use get_response() for that.
   *
   *--*/
   bool twit::friendsGet( string userInfo, bool isUserId )
   {
      bool retVal = false;
      if( true )
      {
         /* set URL */
         string strUrl( "" );
         strUrl = build_url(TWIT_SHOWFRIENDS_URL, userInfo, isUserId );

         /* Perform GET */
         retVal = performGet( strUrl );
      }
      return retVal;
   }

   /*++
   * @method: twit::followersGet
   *
   * @description: method to get a user's followers
   *
   * @input: userInfo - screen name or user atom in string format,
   *         isUserId - true if userInfo contains an atom
   *
   * @output: true if GET is success, otherwise false. This does not check http
   *          response by twitter. Use get_response() for that.
   *
   *--*/
   bool twit::followersGet( string userInfo, bool isUserId )
   {
      bool retVal = false;
      if( true )
      {
         /* Prepare URL */
         string strUrl( "" );
         strUrl = build_url(TWIT_SHOWFOLLOWERS_URL, userInfo, isUserId );

         /* Perform GET */
         retVal = performGet( strUrl );
      }
      return retVal;
   }

   /*++
   * @method: twit::directMessageGet
   *
   * @description: method to get direct messages
   *
   * @input: none
   *
   * @output: true if GET is success, otherwise false. This does not check http
   *          response by twitter. Use get_response() for that.
   *
   *--*/
   bool twit::directMessageGet()
   {
      bool retVal = false;
      if( true )
      {
         /* Perform GET */
         retVal = performGet( TWIT_DIRECTMESSAGES_URL );
      }
      return retVal;
   }

   /*++
   * @method: twit::directMessageSend
   *
   * @description: method to send direct message to a user
   *
   * @input: userInfo - screen name or user atom of a user to whom message needs to be sent,
   *         dMsg - message
   *         isUserId - true if userInfo contains target user's atom
   *
   * @output: true if POST is success, otherwise false. This does not check http
   *          response by twitter. Use get_response() for that.
   *
   *--*/
   bool twit::directMessageSend( string & userInfo, string & dMsg, bool isUserId )
   {
      bool retVal = false;
      if( true && userInfo.get_length() && dMsg.get_length() )
      {
         /* Prepare new direct message */
         property_set post;
         post["text"] = dMsg;

         /* Prepare URL */
         string strUrl( "" );
         strUrl = build_url(TWIT_DIRECTMESSAGENEW_URL, userInfo, isUserId );

         /* Perform POST */
         retVal = performPost( strUrl, post );
      }
      return retVal;
   }

   /*++
   * @method: twit::directMessageGetSent
   *
   * @description: method to get sent direct messages
   *
   * @input: none
   *
   * @output: true if GET is success, otherwise false. This does not check http
   *          response by twitter. Use get_response() for that.
   *
   *--*/
   bool twit::directMessageGetSent()
   {
      bool retVal = false;
      if( true )
      {
         /* Perform GET */
         retVal = performGet( TWIT_DIRECTMESSAGESSENT_URL );
      }
      return retVal;
   }

   /*++
   * @method: twit::directMessageDestroyById
   *
   * @description: method to delete direct messages by its atom
   *
   * @input: dMsgId - atom of direct message in string format
   *
   * @output: true if DELETE is success, otherwise false. This does not check http
   *          response by twitter. Use get_response() for that.
   *
   *--*/
   bool twit::directMessageDestroyById( string & dMsgId )
   {
      bool retVal = false;
      if( true && dMsgId.get_length() )
      {
         /* Prepare URL */
         string strUrl( "" );
         strUrl = TWIT_DIRECTMESSAGEDESTROY_URL;
         strUrl.append( dMsgId );
         strUrl.append( TWIT_EXTENSIONFORMAT );

         /* Perform DELETE */
         retVal = performDelete( strUrl );
      }
      return retVal;
   }

   /*++
   * @method: twit::friendshipCreate
   *
   * @description: method to add a twitter user as friend (follow a user)
   *
   * @input: userInfo - user atom or screen name of a user
   *         isUserId - true if userInfo contains a user atom instead of screen name
   *
   * @output: true if POST is success, otherwise false. This does not check http
   *          response by twitter. Use get_response() for that.
   *
   *--*/
   bool twit::friendshipCreate( string & userInfo, bool isUserId )
   {
      bool retVal = false;
      if( true && userInfo.get_length() )
      {
         /* Prepare URL */
         string strUrl( "" );
         strUrl = build_url(TWIT_FRIENDSHIPSCREATE_URL, userInfo, isUserId );

         /* Send some dummy data in POST */
         property_set post;
         post["text"] = "dummy";

         /* Perform POST */
         retVal = performPost( strUrl, post );
      }
      return retVal;
   }

   /*++
   * @method: twit::friendshipDestroy
   *
   * @description: method to delete a twitter user from friend list (unfollow a user)
   *
   * @input: userInfo - user atom or screen name of a user
   *         isUserId - true if userInfo contains a user atom instead of screen name
   *
   * @output: true if DELETE is success, otherwise false. This does not check http
   *          response by twitter. Use get_response() for that.
   *
   *--*/
   bool twit::friendshipDestroy( string & userInfo, bool isUserId )
   {
      bool retVal = false;
      if( true && userInfo.get_length() )
      {
         /* Prepare URL */
         string strUrl( "" );
         strUrl = build_url(TWIT_FRIENDSHIPSDESTROY_URL, userInfo, isUserId );

         /* Perform DELETE */
         retVal = performDelete( strUrl );
      }
      return retVal;
   }

   /*++
   * @method: twit::friendshipShow
   *
   * @description: method to show all friends
   *
   * @input: userInfo - user atom or screen name of a user of whom friends need to be shown
   *         isUserId - true if userInfo contains a user atom instead of screen name
   *
   * @output: true if GET is success, otherwise false. This does not check http
   *          response by twitter. Use get_response() for that.
   *
   *--*/
   bool twit::friendshipShow( string & userInfo, bool isUserId )
   {
      bool retVal = false;
      if( true )
      {
         /* Prepare URL */
         string strUrl( "" );
         strUrl = TWIT_FRIENDSHIPSSHOW_URL;
         if( userInfo.get_length() )
         {
            /* Append username to the URL */
            if( isUserId )
            {
               strUrl.append( TWIT_TARGETUSERID );
            }
            else
            {
               strUrl.append( TWIT_TARGETSCREENNAME );
            }
            strUrl.append( userInfo );
         }

         /* Perform GET */
         retVal = performGet( strUrl );
      }
      return retVal;
   }

   /*++
   * @method: twit::friendsIdsGet
   *
   * @description: method to show IDs of all friends of a twitter user
   *
   * @input: userInfo - user atom or screen name of a user
   *         isUserId - true if userInfo contains a user atom instead of screen name
   *
   * @output: true if GET is success, otherwise false. This does not check http
   *          response by twitter. Use get_response() for that.
   *
   *--*/
   bool twit::friendsIdsGet( string & userInfo, bool isUserId )
   {
      bool retVal = false;
      if( true )
      {
         /* Prepare URL */
         string strUrl( "" );
         strUrl = build_url(TWIT_FRIENDSIDS_URL, userInfo, isUserId );

         /* Perform GET */
         retVal = performGet( strUrl );
      }
      return retVal;
   }

   /*++
   * @method: twit::followersIdsGet
   *
   * @description: method to show IDs of all followers of a twitter user
   *
   * @input: userInfo - user atom or screen name of a user
   *         isUserId - true if userInfo contains a user atom instead of screen name
   *
   * @output: true if GET is success, otherwise false. This does not check http
   *          response by twitter. Use get_response() for that.
   *
   *--*/
   bool twit::followersIdsGet( string & userInfo, bool isUserId )
   {
      bool retVal = false;
      if( true )
      {
         /* Prepare URL */
         string strUrl( "" );
         strUrl = build_url(TWIT_FOLLOWERSIDS_URL, userInfo, isUserId );

         /* Perform GET */
         retVal = performGet( strUrl );
      }
      return retVal;
   }

   /*++
   * @method: twit::accountRateLimitGet
   *
   * @description: method to get API rate limit of current user
   *
   * @input: none
   *
   * @output: true if GET is success, otherwise false. This does not check http
   *          response by twitter. Use get_response() for that.
   *
   *--*/
   bool twit::accountRateLimitGet()
   {
      bool retVal = false;
      if( true )
      {
         /* Perform GET */
         retVal = performGet( TWIT_ACCOUNTRATELIMIT_URL );
      }
      return retVal;
   }

   /*++
   * @method: twit::favoriteGet
   *
   * @description: method to get favorite users' statuses
   *
   * @input: none
   *
   * @output: true if GET is success, otherwise false. This does not check http
   *          response by twitter. Use get_response() for that.
   *
   *--*/
   bool twit::favoriteGet()
   {
      bool retVal = false;
      if( true )
      {
         /* Perform GET */
         retVal = performGet( TWIT_FAVORITESGET_URL );
      }
      return retVal;
   }

   /*++
   * @method: twit::favoriteCreate
   *
   * @description: method to favorite a status message
   *
   * @input: statusId - atom in string format of the status to be favorited
   *
   * @output: true if POST is success, otherwise false. This does not check http
   *          response by twitter. Use get_response() for that.
   *
   *--*/
   bool twit::favoriteCreate( string & statusId )
   {
      bool retVal = false;
      if( true )
      {
         /* Prepare URL */
         string strUrl( "" );
         strUrl = TWIT_FAVORITECREATE_URL;
         strUrl.append( statusId );
         strUrl.append( TWIT_EXTENSIONFORMAT );

         /* Send some dummy data in POST */
         property_set post;
         post["text"] = "dummy";

         /* Perform POST */
         retVal = performPost( strUrl, post );
      }
      return retVal;
   }

   /*++
   * @method: twit::favoriteDestroy
   *
   * @description: method to delete a favorited the status
   *
   * @input: statusId - atom in string format of the favorite status to be deleted
   *
   * @output: true if DELETE is success, otherwise false. This does not check http
   *          response by twitter. Use get_response() for that.
   *
   *--*/
   bool twit::favoriteDestroy( string & statusId )
   {
      bool retVal = false;
      if( true )
      {
         /* Prepare URL */
         string strUrl( "" );
         strUrl = TWIT_FAVORITEDESTROY_URL;
         strUrl.append( statusId );
         strUrl.append( TWIT_EXTENSIONFORMAT );

         /* Perform DELETE */
         retVal = performDelete( strUrl );
      }
      return retVal;
   }

   /*++
   * @method: twit::blockCreate
   *
   * @description: method to block a user
   *
   * @input: userInfo - user atom or screen name
   *
   * @output: true if POST is success, otherwise false. This does not check http
   *          response by twitter. Use get_response() for that.
   *
   *--*/
   bool twit::blockCreate( string & userInfo )
   {
      bool retVal = false;
      if( true )
      {
         /* Prepare URL */
         string strUrl( "" );
         strUrl = TWIT_BLOCKSCREATE_URL;
         strUrl.append( userInfo );
         strUrl.append( TWIT_EXTENSIONFORMAT );

         /* Send some dummy data in POST */
         property_set post;
         post["text"] = "dummy";

         /* Perform POST */
         retVal = performPost( strUrl, post );
      }
      return retVal;
   }

   /*++
   * @method: twit::blockDestroy
   *
   * @description: method to unblock a user
   *
   * @input: userInfo - user atom or screen name
   *
   * @output: true if DELETE is success, otherwise false. This does not check http
   *          response by twitter. Use get_response() for that.
   *
   *--*/
   bool twit::blockDestroy( string & userInfo )
   {
      bool retVal = false;
      if( true )
      {
         /* Prepare URL */
         string strUrl( "" );
         strUrl = TWIT_BLOCKSDESTROY_URL;
         strUrl.append( userInfo );
         strUrl.append( TWIT_EXTENSIONFORMAT );

         /* Perform DELETE */
         retVal = performDelete( strUrl );
      }
      return retVal;
   }

   /*++
   * @method: twit::savedSearchGet
   *
   * @description: gets authenticated user's saved search queries.
   *
   * @input: none
   *
   * @output: true if GET is success, otherwise false. This does not check http
   *          response by twitter. Use get_response() for that.
   *
   *--*/
   bool twit::savedSearchGet( )
   {
      bool retVal = false;
      if( true )
      {
         /* Perform GET */
         retVal = performGet( TWIT_SAVEDSEARCHGET_URL );
      }
      return retVal;
   }

   /*++
   * @method: twit::savedSearchShow
   *
   * @description: method to retrieve the data for a saved search owned by the authenticating user
   *               specified by the given atom.
   *
   * @input: searchId - atom in string format of the search to be displayed
   *
   * @output: true if GET is success, otherwise false. This does not check http
   *          response by twitter. Use get_response() for that.
   *
   *--*/
   bool twit::savedSearchShow( string & searchId )
   {
      bool retVal = false;
      if( true )
      {
         /* Prepare URL */
         string strUrl( "" );
         strUrl = TWIT_SAVEDSEARCHSHOW_URL;
         strUrl.append( searchId );
         strUrl.append( TWIT_EXTENSIONFORMAT );

         /* Perform GET */
         retVal = performGet( strUrl );
      }
      return retVal;
   }

   /*++
   * @method: twit::savedSearchCreate
   *
   * @description: creates a saved search for the authenticated user
   *
   * @input: query - the query of the search the user would like to save
   *
   * @output: true if POST is success, otherwise false. This does not check http
   *          response by twitter. Use get_response() for that.
   *
   *--*/
   bool twit::savedSearchCreate( string & query )
   {
      bool retVal = false;
      if( true )
      {
         /* Prepare URL */
         string strUrl( "" );
         strUrl = TWIT_SAVEDSEARCHCREATE_URL;

         /* Send some dummy data in POST */
         property_set post;
         post["query"] = query;

         /* Perform POST */
         retVal = performPost( strUrl, post );
      }
      return retVal;
   }


   /*++
   * @method: twit::savedSearchDestroy
   *
   * @description: method to destroy a saved search for the authenticated user. The search specified
   *               by atom must be owned by the authenticating user.
   *
   * @input: searchId - search atom of item to be deleted
   *
   * @output: true if DELETE is success, otherwise false. This does not check http
   *          response by twitter. Use get_response() for that.
   *
   *--*/
   bool twit::savedSearchDestroy( string & searchId )
   {
      bool retVal = false;
      if( true )
      {
         /* Prepare URL */
         string strUrl( "" );
         strUrl = TWIT_SAVEDSEARCHDESTROY_URL;
         strUrl.append( searchId );
         strUrl.append( TWIT_EXTENSIONFORMAT );

         /* Perform DELETE */
         retVal = performDelete( strUrl );
      }
      return retVal;
   }


   /*++
   * @method: twit::trendsGet()
   *
   * @description: gets trends.
   *
   * @input: none
   *
   * @output: true if GET is success, otherwise false. This does not check http
   *          response by twitter. Use get_response() for that.
   *
   *--*/
   bool twit::trendsGet()
   {
      bool retVal = false;
      if( true )
      {
         /* Perform GET */
         retVal = performGet( TWIT_TRENDS_URL );
      }
      return retVal;
   }


   /*++
   * @method: twit::trendsDailyGet()
   *
   * @description: gets daily trends.
   *
   * @input: none
   *
   * @output: true if GET is success, otherwise false. This does not check http
   *          response by twitter. Use get_response() for that.
   *
   *--*/
   bool twit::trendsDailyGet()
   {
      bool retVal = false;
      if( true )
      {
         /* Perform GET */
         retVal = performGet( TWIT_TRENDSDAILY_URL );
      }
      return retVal;
   }

   /*++
   * @method: twit::trendsWeeklyGet()
   *
   * @description: gets weekly trends.
   *
   * @input: none
   *
   * @output: true if GET is success, otherwise false. This does not check http
   *          response by twitter. Use get_response() for that.
   *
   *--*/
   bool twit::trendsWeeklyGet()
   {
      bool retVal = false;
      if( true )
      {
         /* Perform GET */
         retVal = performGet( TWIT_TRENDSWEEKLY_URL );
      }
      return retVal;
   }

   /*++
   * @method: twit::trendsCurrentGet()
   *
   * @description: gets current trends.
   *
   * @input: none
   *
   * @output: true if GET is success, otherwise false. This does not check http
   *          response by twitter. Use get_response() for that.
   *
   *--*/
   bool twit::trendsCurrentGet()
   {
      bool retVal = false;
      if( true )
      {
         /* Perform GET */
         retVal = performGet( TWIT_TRENDSCURRENT_URL );
      }
      return retVal;
   }

   /*++
   * @method: twit::trendsAvailableGet()
   *
   * @description: gets available trends.
   *
   * @input: none
   *
   * @output: true if GET is success, otherwise false. This does not check http
   *          response by twitter. Use get_response() for that.
   *
   *--*/
   bool twit::trendsAvailableGet()
   {
      bool retVal = false;
      if( true )
      {
         /* Perform GET */
         retVal = performGet( TWIT_TRENDSAVAILABLE_URL );
      }
      return retVal;
   }

   /*++
   * @method: twit::get_response
   *
   * @description: method to get http response for the most recent request sent.
   *               twitcurl users need to call this method and parse the XML
   *               data returned by twitter to see what has happened.
   *
   * @input: outWebResp - string in which twitter's response is supplied back to caller
   *
   * @output: none
   *
   *--*/
   string twit::get_response()
   {
      return m_strResponse;
   }



   /*++
   * @method: twit::prepareCurlUserPass
   *
   * @description: method to set twitter credentials into cURL. this is an internal method.
   *               twitcurl users should not use this method, instead use setTwitterXxx
   *               methods to set twitter username and password.
   *
   * @input: none
   *
   * @output: none
   *
   * @remarks: internal method
   *
   *--*/
   void twit::prepareCurlUserPass()
   {

      if( !m_curlLoginParamsSet )
      {

         /* set username and password */
         m_setHttp["basic_authentication"] = prepare_basic_authentication(getTwitterUsername(), getTwitterPassword());

         /* set the flag to true indicating that twitter credentials are set in cURL */
         m_curlLoginParamsSet = true;

      }

   }

   /*++
   * @method: twit::prepareStandardParams
   *
   * @description: method to set standard params into cURL. this is an internal method.
   *               twitcurl users should not use this method.
   *
   * @input: none
   *
   * @output: none
   *
   * @remarks: internal method
   *
   *--*/
   void twit::prepareStandardParams()
   {
      /* Restore any custom request we may have */
      //       curl_easy_setopt( m_curlHandle, CURLOPT_CUSTOMREQUEST, nullptr );


      /* Prepare username and password for twitter */
      prepareCurlUserPass();
   }

   /*++
   * @method: twit::performGet
   *
   * @description: method to send http GET request. this is an internal method.
   *               twitcurl users should not use this method.
   *
   * @input: getUrl - url
   *
   * @output: none
   *
   * @remarks: internal method
   *
   *--*/
   bool twit::performGet( const string & getUrl )
   {

      property_set set;

      /* set OAuth header */
      m_oauth.getOAuthHeader(eOAuthHttpGet, getUrl, set);

      set.merge(m_setHttp);

      /* Send http request */
      bool bOk = pcontext->m_papexcontext->http().get(getUrl, m_strResponse, set);

      string m_strConnectionStatus = ::http::conn_status(set);

      log_line(m_strConnectionStatus);

      return bOk;

   }


   /*++
   * @method: twit::performGet
   *
   * @description: method to send http GET request. this is an internal method.
   *               twitcurl users should not use this method.
   *
   * @input: const string & getUrl, const string & oAuthHttpHeader
   *
   * @output: none
   *
   * @remarks: internal method
   *
   *--*/
   bool twit::performGet( const string & getUrl, property_set & headers)
   {

      string dataStrDummy( "" );

      property_set set;

      set["headers"] = headers;

      /* Send http request */
      bool bOk = pcontext->m_papexcontext->http().get(getUrl, m_strResponse, set);

      string m_strConnectionStatus = ::http::conn_status(set);

      log_line(m_strConnectionStatus);

      return bOk;

   }


//   bool twit::performPost( const string & getUrl, property_set & headers, property_set & post)
//      {
//
//         string dataStrDummy( "" );
//
//         property_set set;
//
//         if (headers.m_propertya.get_count() > 0)
//         {
//
//            set["headers"] = headers;
//
//         }
//
//         set["post"] = post;
//
//         set["http_method"] = "POST";
//
//         // Send http request
////      bool bOk = pcontext->m_papexcontext->http().get(getUrl, m_strResponse, set);
////
////      headers = set["get_headers"].propset();
////
////      return bOk;
//
//   }

   /*++
   * @method: twit::performDelete
   *
   * @description: method to send http DELETE request. this is an internal method.
   *               twitcurl users should not use this method.
   *
   * @input: deleteUrl - url
   *
   * @output: none
   *
   * @remarks: internal method
   *
   *--*/
   bool twit::performDelete( const string & deleteUrl )
   {

      property_set set;

      /* set OAuth header */
      m_oauth.getOAuthHeader(eOAuthHttpDelete, deleteUrl, set);

      set.merge(m_setHttp);

      set["http_method"] = "DELETE";

      /* Send http request */
      bool bOk = pcontext->m_papexcontext->http().get(deleteUrl, m_strResponse, set);

      string m_strConnectionStatus = ::http::conn_status(set);

      log_line(m_strConnectionStatus);

      return bOk;

   }

   /*++
   * @method: twit::performPost
   *
   * @description: method to send http POST request. this is an internal method.
   *               twitcurl users should not use this method.
   *
   * @input: postUrl - url,
   *         dataStr - data to be posted
   *
   * @output: none
   *
   * @remarks: internal method
   *
   *--*/
   bool twit::performPost( const string & postUrl, property_set & set)
   {

      bool bOk = false;

      if (set.has_property("headers"))
      {

         set.merge(m_setHttp);

         if (set.has_property("post"))
         {

            set["http_method"] = "POST";

         }

         bOk = pcontext->m_papexcontext->http().get(postUrl, m_strResponse, set);

         string m_strConnectionStatus = ::http::conn_status(set);

         log_line(m_strConnectionStatus);

         return bOk;
      }
      else
      {

         property_set setHttp;

         setHttp["post"] = set;

         /* set OAuth header */
         m_oauth.getOAuthHeader(eOAuthHttpPost, postUrl, setHttp);

         setHttp.merge(m_setHttp);

         setHttp["http_method"] = "POST";

         bOk = pcontext->m_papexcontext->http().get(postUrl, m_strResponse, setHttp) && setHttp["get_status"].estatus() == ::success;

         string m_strConnectionStatus = ::http::conn_status(setHttp);

         log_line(m_strConnectionStatus);

         return bOk;

      }



   }

   bool twit::performMultiPartPost(const string & postUrl, property_set & set, bool bMultiPartPost)
   {

      bool bOk = false;

      if (set.has_property("headers"))
      {

         set.merge(m_setHttp);

         if (set.has_property("post"))
         {

            set["http_method"] = "POST";

         }

         bOk = pcontext->m_papexcontext->http().get(postUrl, m_strResponse, set);

         string m_strConnectionStatus = ::http::conn_status(set);

         log_line(m_strConnectionStatus);

         return bOk;
      }
      else
      {

         property_set setHttp;

         if (!bMultiPartPost)
         {

            setHttp["post"] = set;

         }

         m_oauth.getOAuthHeader(eOAuthHttpPost, postUrl, setHttp);

         setHttp.merge(m_setHttp);

         setHttp["http_method"] = "POST";

         if (bMultiPartPost)
         {

            setHttp["post"] = set["post"];
            setHttp["multipart"] = set["multipart"];

         }

         bOk = pcontext->m_papexcontext->http().get(postUrl, m_strResponse, setHttp) && setHttp["get_status"].estatus() == ::success;

         string m_strConnectionStatus = ::http::conn_status(setHttp);

         log_line(m_strConnectionStatus);

         return bOk;

      }



   }

   /*++
   * @method: utilMakeCurlParams
   *
   * @description: utility function to build parameter strings in the format
   *               required by cURL ("param1:param2"). twitcurl users should
   *               not use this function.
   *
   * @input: inParam1 - first parameter,
   *         inParam2 - second parameter
   *
   * @output: outStr - built parameter
   *
   * @remarks: internal method
   *
   *--*/
   string twit::prepare_basic_authentication(const ::string & inParam1, const ::string & inParam2)
   {
      string outStr = inParam1;
      outStr += TWIT_COLON;
      outStr += inParam2;
      return outStr;
   }

   /*++
   * @method: utilMakeUrlForUser
   *
   * @description: utility function to build url compatible to twitter. twitcurl
   *               users should not use this function.
   *
   * @input: baseUrl - base twitter url,
   *         userInfo - user name,
   *         isUserId - indicates if userInfo contains a user atom or scree name
   *
   * @output: outUrl - built url
   *
   * @remarks: internal method
   *
   *--*/
   string twit::build_url( const char * baseUrl, const ::string & userInfo, bool isUserId )
   {
      /* Copy base URL */
      string outUrl = baseUrl;

      if(userInfo != nullptr && strlen(userInfo)  > 0)
      {
         /* Append username to the URL */
         if( isUserId )
         {
            outUrl +=  TWIT_USERID ;
         }
         else
         {
            outUrl +=  TWIT_SCREENNAME ;
         }
         outUrl +=  userInfo ;
      }
      return outUrl;
   }

   /*++
   * @method: twit::getOAuth
   *
   * @description: method to get a object to oAuth object.
   *
   * @input: none
   *
   * @output: object to oAuth object
   *
   *--*/
   oauth & twit::get_oauth()
   {
      return m_oauth;
   }

   /*++
   * @method: twit::oAuthRequestToken
   *
   * @description: method to get a request token key and secret. this token
   *               will be used to get authorize user and get PIN from twitter
   *
   * @input: authorizeUrl is an output parameter. this method will set the url
   *         in this string. user should visit this link and get PIN from that page.
   *
   * @output: true if everything went sucessfully, otherwise false
   *
   *--*/
   bool twit::oAuthRequestToken( string & authorizeUrl /* out */ )
   {
      bool retVal = false;

      authorizeUrl = "" ;

      if( true )
      {
         /* Get OAuth header for request token */
         property_set set;
         i64 iTime = ::time(nullptr);
         if (m_oauth.getOAuthHeader(eOAuthHttpPost, "https://twitter.com/oauth/request_token", set))
         {
            if (performPost("https://twitter.com/oauth/request_token", set))
            {
               string strAuth = set["get_headers"]["Authorization"];
               string strDate = set["get_headers"]["date"];
               ::earth::time time(iTime);
               string strDateHere = pdatetime->international().get_gmt_date_time(time);
               /* Tell OAuth object to save access token and secret from web response */
               m_oauth.extractOAuthTokenKeySecret(get_response());

               /* Get access token and secret from OAuth object */
               string oAuthTokenKey("");
               m_oauth.getOAuthTokenKey( oAuthTokenKey );

               /* Build authorize url so that user can visit in browser and get PIN */
               authorizeUrl = m_oauth.OAUTHLIB_TWITTER_AUTHORIZE_URL;
               authorizeUrl += oAuthTokenKey;

               retVal = true;
            }
         }
      }
      return retVal;
   }

   /*++
   * @method: twit::oAuthAccessToken
   *
   * @description: method to exchange request token with access token
   *
   * @input: none
   *
   * @output: true if everything went sucessfully, otherwise false
   *
   *--*/
   bool twit::oAuthAccessToken()
   {
      bool retVal = false;

      if( true )
      {
         /* Get OAuth header for access token */
         property_set set;
         if(m_oauth.getOAuthHeader( eOAuthHttpGet, m_oauth.OAUTHLIB_TWITTER_ACCESS_TOKEN_URL, set, true))
         {
            if (performGet(m_oauth.OAUTHLIB_TWITTER_ACCESS_TOKEN_URL, set["headers"].propset()))
            {
               /* Tell OAuth object to save access token and secret from web response */
               string twitterResp( "" );
               twitterResp = get_response();
               m_oauth.extractOAuthTokenKeySecret( twitterResp );

               retVal = true;
            }
         }
      }
      return retVal;
   }


} // namespace hi5




