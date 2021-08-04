#pragma once


namespace hi5
{

   /* twitCurl class */
   class CLASS_DECL_SPHERE twit :
      virtual public ::simple_log
   {
   public:

      string      m_strConnectionStatus;
      /* Constants */
      const string TWIT_COLON;
      const char TWIT_EOS;

      /* Miscellaneous data used to build twitter URLs*/
      const string TWIT_SEARCHQUERYSTRING;
      const string TWIT_SCREENNAME;
      const string TWIT_USERID;
      const string TWIT_EXTENSIONFORMAT;
      const string TWIT_TARGETSCREENNAME;
      const string TWIT_TARGETUSERID;

      /* Search URLs */
      const string TWIT_SEARCH_URL;

      /* Status URLs */
      const string TWIT_STATUSUPDATE_URL;
      const string TWIT_STATUSSHOW_URL;
      const string TWIT_STATUDESTROY_URL;

      /* Timeline URLs */
      const string TWIT_PUBLIC_TIMELINE_URL;
      const string TWIT_FEATURED_USERS_URL;
      const string TWIT_FRIENDS_TIMELINE_URL;
      const string TWIT_MENTIONS_URL;
      const string TWIT_USERTIMELINE_URL;

      /* Users URLs */
      const string TWIT_SHOWUSERS_URL;
      const string TWIT_SHOWFRIENDS_URL;
      const string TWIT_SHOWFOLLOWERS_URL;

      /* Direct messages URLs */
      const string TWIT_DIRECTMESSAGES_URL;
      const string TWIT_DIRECTMESSAGENEW_URL;
      const string TWIT_DIRECTMESSAGESSENT_URL;
      const string TWIT_DIRECTMESSAGEDESTROY_URL;

      /* Friendships URLs */
      const string TWIT_FRIENDSHIPSCREATE_URL;
      const string TWIT_FRIENDSHIPSDESTROY_URL;
      const string TWIT_FRIENDSHIPSSHOW_URL;

      /* Social graphs URLs */
      const string TWIT_FRIENDSIDS_URL;
      const string TWIT_FOLLOWERSIDS_URL;

      /* Ac::count URLs */
      const string TWIT_ACCOUNTRATELIMIT_URL;

      /* Favorites URLs */
      const string TWIT_FAVORITESGET_URL;
      const string TWIT_FAVORITECREATE_URL;
      const string TWIT_FAVORITEDESTROY_URL;

      /* Block URLs */
      const string TWIT_BLOCKSCREATE_URL;
      const string TWIT_BLOCKSDESTROY_URL;

      /* Saved Search URLs */
      const string TWIT_SAVEDSEARCHGET_URL;
      const string TWIT_SAVEDSEARCHSHOW_URL;
      const string TWIT_SAVEDSEARCHCREATE_URL;
      const string TWIT_SAVEDSEARCHDESTROY_URL;

      /* Trends URLs */
      const string TWIT_TRENDS_URL;
      const string TWIT_TRENDSDAILY_URL;
      const string TWIT_TRENDSCURRENT_URL;
      const string TWIT_TRENDSWEEKLY_URL;
      const string TWIT_TRENDSAVAILABLE_URL;

   public:


      string   m_strRequest;
      string   m_strError;
      string   m_strResponse;

      /* cURL flags */
      bool m_curlLoginParamsSet;
      property_set m_setHttp;


      /* Twitter data */
      string m_twitterUsername;
      string m_twitterPassword;

      /* OAuth data */
      oauth m_oauth;

      twit(::object * pobject, simple_log * psimplelog = nullptr, index iLogTarget = -1);
      virtual ~twit();

      /* Twitter OAuth authorization methods */
      oauth& get_oauth();
      bool oAuthRequestToken(string & authorizeUrl /* out */);
      bool oAuthAccessToken();

      /* Twitter login APIs, set once and forget */
      string & getTwitterUsername();
      string & getTwitterPassword();
      void setTwitterUsername(string & userName /* in */);
      void setTwitterPassword(string & passWord /* in */);

      /* Twitter search APIs */
      bool search(string & query /* in */);


      string mediaUpload(file_pointer pfile, string strMimeType, string strCategory);
      string mediaUploadInit(int iTotalSize, string strMimeType, string strCategory);
      bool mediaUploadAppend(string strMediaId, index iIndex, file_pointer pfile, int iSize, string strMimeType, string & boundary_is_the_bounday_the_issue_i_e_should_it_be_the_same_across_appends);
      ::payload mediaUploadFinalize(string strMediaId);
      ::payload mediaUploadStatus(string strMediaId);

      /* Twitter status APIs */
      bool statusUpdate(string & newStatus /* in */, string_array straMediaIds = {}, string strReplyStatusId = "");
      bool statusShowById(string & statusId /* in */);
      bool statusDestroyById(string & statusId /* in */);

      /* Twitter timeline APIs */
      bool timelinePublicGet();
      bool timelineFriendsGet();
      bool timelineUserGet(string userInfo = "" /* in */, bool isUserId = false /* in */);
      bool featuredUsersGet();
      bool mentionsGet();

      /* Twitter user APIs */
      bool userGet(string & userInfo /* in */, bool isUserId = false /* in */);
      bool friendsGet(string userInfo = "" /* in */, bool isUserId = false /* in */);
      bool followersGet(string userInfo = "" /* in */, bool isUserId = false /* in */);

      /* Twitter direct message APIs */
      bool directMessageGet();
      bool directMessageSend(string & userInfo /* in */, string & dMsg /* in */, bool isUserId = false /* in */);
      bool directMessageGetSent();
      bool directMessageDestroyById(string & dMsgId /* in */);

      /* Twitter friendships APIs */
      bool friendshipCreate(string & userInfo /* in */, bool isUserId = false /* in */);
      bool friendshipDestroy(string & userInfo /* in */, bool isUserId = false /* in */);
      bool friendshipShow(string & userInfo /* in */, bool isUserId = false /* in */);

      /* Twitter social graphs APIs */
      bool friendsIdsGet(string & userInfo /* in */, bool isUserId = false /* in */);
      bool followersIdsGet(string & userInfo /* in */, bool isUserId = false /* in */);

      /* Twitter ac::count APIs */
      bool accountRateLimitGet();



      /* Twitter favorites APIs */
      bool favoriteGet();
      bool favoriteCreate(string & statusId /* in */);
      bool favoriteDestroy(string & statusId /* in */);

      /* Twitter block APIs */
      bool blockCreate(string & userInfo /* in */);
      bool blockDestroy(string & userInfo /* in */);

      /* Twitter search APIs */
      bool savedSearchGet();
      bool savedSearchCreate(string & query /* in */);
      bool savedSearchShow(string & searchId /* in */);
      bool savedSearchDestroy(string & searchId /* in */);

      /* Twitter trends APIs (JSON) */
      bool trendsGet();
      bool trendsDailyGet();
      bool trendsWeeklyGet();
      bool trendsCurrentGet();
      bool trendsAvailableGet();

      string get_response();

      /* Internal cURL related methods */
      i32 saveLastWebResponse(char*& data, size_t size);



      /* Private methods */
      void prepareCurlUserPass();
      void prepareStandardParams();
      bool performGet(const string & getUrl);
      bool performGet(const string & getUrl, property_set & headers);
      bool performDelete(const string & deleteUrl);
      bool performPost(const string & postUrl, property_set & post);
      bool performMultiPartPost(const string & postUrl, property_set & post, bool bMultiPartPost);
      //bool performPost( const string & postUrl, property_set & headers, property_set & post );

      string build_url(const ::string & baseUrl, const ::string & userInfo, bool isUserId);

      string prepare_basic_authentication(const ::string & inParam1, const ::string & inParam2);


   };


} // namespace aura






