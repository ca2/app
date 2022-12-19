#pragma once


namespace hi5
{


   CLASS_DECL_SPHERE string char2hex( char dec );
   CLASS_DECL_SPHERE string urlencode( const string &ca );


   typedef enum _eOAuthHttpRequestType
   {
      eOAuthHttpInvalid = 0,
      eOAuthHttpGet,
      eOAuthHttpPost,
      eOAuthHttpDelete
   } eOAuthHttpRequestType;

   typedef string_array oAuthKeyValueList;
   typedef property_set oAuthKeyValuePairs;

   class CLASS_DECL_SPHERE oauth :
      virtual public ::simple_log
   {
   public:

      const string OAUTHLIB_CONSUMERKEY_KEY;
      const string OAUTHLIB_CALLBACK_KEY;
      const string OAUTHLIB_VERSION_KEY;
      const string OAUTHLIB_SIGNATUREMETHOD_KEY;
      const string OAUTHLIB_SIGNATURE_KEY;
      const string OAUTHLIB_TIMESTAMP_KEY;
      const string OAUTHLIB_NONCE_KEY;
      const string OAUTHLIB_TOKEN_KEY;
      const string OAUTHLIB_TOKENSECRET_KEY;
      const string OAUTHLIB_VERIFIER_KEY;
      const string OAUTHLIB_SCREENNAME_KEY;


      const string OAUTHLIB_TWITTER_REQUEST_TOKEN_URL;
      const string OAUTHLIB_TWITTER_AUTHORIZE_URL;
      const string OAUTHLIB_TWITTER_ACCESS_TOKEN_URL;


      oauth(::particle * pparticle, simple_log * psimplelog, index iLogTarget);
      virtual ~oauth();

      /* OAuth public methods used by twitCurl */
      void getConsumerKey( string& consumerKey /* out */ );
      void setConsumerKey( const string& consumerKey /* in */ );

      void getConsumerSecret( string& consumerSecret /* out */ );
      void setConsumerSecret( const string& consumerSecret /* in */ );

      void getOAuthTokenKey( string& oAuthTokenKey /* out */ );
      void setOAuthTokenKey( const string& oAuthTokenKey /* in */ );

      void getOAuthTokenSecret( string& oAuthTokenSecret /* out */ );
      void setOAuthTokenSecret( const string& oAuthTokenSecret /* in */ );

      void getOAuthScreenName( string& oAuthScreenName /* out */ );
      void setOAuthScreenName( const string& oAuthScreenName /* in */ );

      void getOAuthPin( string& oAuthPin /* out */ );
      void setOAuthPin( const string& oAuthPin /* in */ );

      bool getOAuthHeader(const eOAuthHttpRequestType eType, /* in */
                          const string & rawUrl, /* in */
                          property_set & set, /* in(set["post"])/out(set["headers"]) */
                          const bool includeOAuthVerifierPin = false /* in */);

      bool extractOAuthTokenKeySecret( const string& requestTokenResponse /* in */ );

   private:

      /* OAuth data */
      string m_consumerKey;
      string m_consumerSecret;
      string m_oAuthTokenKey;
      string m_oAuthTokenSecret;
      string m_oAuthPin;
      string m_nonce;
      string m_timeStamp;
      string m_oAuthScreenName;

      /* OAuth twitter related utility methods */
      bool buildOAuthTokenKeyValuePairs( const bool includeOAuthVerifierPin, /* in */
                                         oAuthKeyValuePairs & rawData, /* in */
                                         const string& oauthSignature, /* in */
                                         oAuthKeyValuePairs& keyValueMap /* out */ );

      bool getStringFromOAuthKeyValuePairs( const oAuthKeyValuePairs& rawParamMap, /* in */
                                            string& rawParams, /* out */
                                            const scoped_string & strSeparator /* in */ );

      bool getSignature( const eOAuthHttpRequestType eType, /* in */
                         const string& rawUrl, /* in */
                         const oAuthKeyValuePairs& rawKeyValuePairs, /* in */
                         string& oAuthSignature /* out */ );

      void generateNonceTimeStamp();


   };


} // namespace hi5







