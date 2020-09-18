#include "framework.h"
#include <stdio.h>
#include <time.h>
#undef HMAC_SHA1


namespace hi5
{
  

   namespace oAuthLibDefaults
   {
      /* Constants */
      const i32 OAUTHLIB_BUFFSIZE = 1024;
//       const i32 OAUTHLIB_BUFFSIZE_LARGE = 1024;


   };


   string char2hex( char dec )
   {
      char dig1 = (dec&0xF0)>>4;
      char dig2 = (dec&0x0F);
      if ( 0<= dig1 && dig1<= 9) dig1+='0';    //0,48 in ascii
      if (10<= dig1 && dig1<=15) dig1+='A'-10; //A,65 in ascii
      if ( 0<= dig2 && dig2<= 9) dig2+='0';
      if (10<= dig2 && dig2<=15) dig2+='A'-10;

      string str;
      str.append( &dig1, 1);
      str.append( &dig2, 1);
      return str;
   }

   string urlencode( const string &ca )
   {

      string escaped;
      ::count max = ca.get_length();
      for(i32 i=0; i<max; i++)
      {
         if ( (48 <= ca[i] && ca[i] <= 57) ||//0-9
               (65 <= ca[i] && ca[i] <= 90) ||//ABC...XYZ
               (97 <= ca[i] && ca[i] <= 122) || //abc...xyz
               (ca[i]=='~' || ca[i]=='-' || ca[i]=='_' || ca[i]=='.')
            )
         {
            escaped += ca[i];
         }
         else
         {
            escaped.append("%");
            escaped.append( char2hex(ca[i]) );//converts char 255 to string "FF"
         }
      }
      return escaped;
   }
   /*++
   * @method: oauth::oauth
   *
   * @description: constructor
   *
   * @input: none
   *
   * @output: none
   *
   *--*/
   oauth::oauth(::object * pobject, simple_log * psimplelog, index iLogTarget) :
      object(pobject),
      simple_log(psimplelog, iLogTarget),
      OAUTHLIB_CONSUMERKEY_KEY("oauth_consumer_key"),
      OAUTHLIB_CALLBACK_KEY("oauth_callback"),
      OAUTHLIB_VERSION_KEY("oauth_version"),
      OAUTHLIB_SIGNATUREMETHOD_KEY("oauth_signature_method"),
      OAUTHLIB_SIGNATURE_KEY("oauth_signature"),
      OAUTHLIB_TIMESTAMP_KEY("oauth_timestamp"),
      OAUTHLIB_NONCE_KEY("oauth_nonce"),
      OAUTHLIB_TOKEN_KEY("oauth_token"),
      OAUTHLIB_TOKENSECRET_KEY("oauth_token_secret"),
      OAUTHLIB_VERIFIER_KEY("oauth_verifier"),
      OAUTHLIB_SCREENNAME_KEY("screen_name"),


      OAUTHLIB_TWITTER_REQUEST_TOKEN_URL("http://twitter.com/oauth/request_token"),
      OAUTHLIB_TWITTER_AUTHORIZE_URL("http://twitter.com/oauth/authorize?oauth_token="),
      OAUTHLIB_TWITTER_ACCESS_TOKEN_URL("https://twitter.com/oauth/access_token"),

      m_consumerKey(""),
      m_consumerSecret( "" ),
      m_oAuthTokenKey( "" ),
      m_oAuthTokenSecret( "" ),
      m_oAuthPin( "" ),
      m_nonce( "" ),
      m_timeStamp( "" ),
      m_oAuthScreenName( "" )
   {
   }

   /*++
   * @method: oauth::~oauth
   *
   * @description: destructor
   *
   * @input: none
   *
   * @output: none
   *
   *--*/
   oauth::~oauth()
   {
   }

   /*++
   * @method: oauth::getConsumerKey
   *
   * @description: this method gives consumer key that is being used currently
   *
   * @input: none
   *
   * @output: consumer key
   *
   *--*/
   void oauth::getConsumerKey(string & consumerKey )
   {
      consumerKey = m_consumerKey;
   }

   /*++
   * @method: oauth::setConsumerKey
   *
   * @description: this method saves consumer key that should be used
   *
   * @input: consumer key
   *
   * @output: none
   *
   *--*/
   void oauth::setConsumerKey(const string & consumerKey )
   {
      m_consumerKey = consumerKey;
   }

   /*++
   * @method: oauth::getConsumerSecret
   *
   * @description: this method gives consumer secret that is being used currently
   *
   * @input: none
   *
   * @output: consumer secret
   *
   *--*/
   void oauth::getConsumerSecret(string & consumerSecret )
   {
      consumerSecret = m_consumerSecret;
   }

   /*++
   * @method: oauth::setConsumerSecret
   *
   * @description: this method saves consumer secret that should be used
   *
   * @input: consumer secret
   *
   * @output: none
   *
   *--*/
   void oauth::setConsumerSecret(const string & consumerSecret )
   {
      m_consumerSecret = consumerSecret;
   }

   /*++
   * @method: oauth::getOAuthTokenKey
   *
   * @description: this method gives OAuth token (also called access token) that is being used currently
   *
   * @input: none
   *
   * @output: OAuth token
   *
   *--*/
   void oauth::getOAuthTokenKey(string & oAuthTokenKey )
   {
      oAuthTokenKey = m_oAuthTokenKey;
   }

   /*++
   * @method: oauth::setOAuthTokenKey
   *
   * @description: this method saves OAuth token that should be used
   *
   * @input: OAuth token
   *
   * @output: none
   *
   *--*/
   void oauth::setOAuthTokenKey(const string & oAuthTokenKey )
   {
      m_oAuthTokenKey = oAuthTokenKey;
   }

   /*++
   * @method: oauth::getOAuthTokenSecret
   *
   * @description: this method gives OAuth token secret that is being used currently
   *
   * @input: none
   *
   * @output: OAuth token secret
   *
   *--*/
   void oauth::getOAuthTokenSecret(string & oAuthTokenSecret )
   {
      oAuthTokenSecret = m_oAuthTokenSecret;
   }

   /*++
   * @method: oauth::setOAuthTokenSecret
   *
   * @description: this method saves OAuth token that should be used
   *
   * @input: OAuth token secret
   *
   * @output: none
   *
   *--*/
   void oauth::setOAuthTokenSecret(const string & oAuthTokenSecret )
   {
      m_oAuthTokenSecret = oAuthTokenSecret;
   }

   /*++
   * @method: oauth::getOAuthScreenName
   *
   * @description: this method gives authorized user's screenname
   *
   * @input: none
   *
   * @output: screen name
   *
   *--*/
   void oauth::getOAuthScreenName(string & oAuthScreenName )
   {
      oAuthScreenName = m_oAuthScreenName;
   }

   /*++
   * @method: oauth::setOAuthScreenName
   *
   * @description: this method sets authorized user's screenname
   *
   * @input: screen name
   *
   * @output: none
   *
   *--*/
   void oauth::setOAuthScreenName(const string & oAuthScreenName )
   {
      m_oAuthScreenName = oAuthScreenName;
   }

   /*++
   * @method: oauth::getOAuthPin
   *
   * @description: this method gives OAuth verifier PIN
   *
   * @input: none
   *
   * @output: OAuth verifier PIN
   *
   *--*/
   void oauth::getOAuthPin(string & oAuthPin )
   {
      oAuthPin = m_oAuthPin;
   }

   /*++
   * @method: oauth::setOAuthPin
   *
   * @description: this method sets OAuth verifier PIN
   *
   * @input: OAuth verifier PIN
   *
   * @output: none
   *
   *--*/
   void oauth::setOAuthPin(const string & oAuthPin )
   {
      m_oAuthPin = oAuthPin;
   }

   /*++
   * @method: oauth::generateNonceTimeStamp
   *
   * @description: this method generates nonce and timestamp for OAuth header
   *
   * @input: none
   *
   * @output: none
   *
   * @remarks: internal method
   *
   *--*/
   void oauth::generateNonceTimeStamp()
   {

      if (m_nonce.has_char() && m_timeStamp.has_char())
         return;

      char szTime[oAuthLibDefaults::OAUTHLIB_BUFFSIZE];
      char szRand[oAuthLibDefaults::OAUTHLIB_BUFFSIZE];
      __memset( szTime, 0, oAuthLibDefaults::OAUTHLIB_BUFFSIZE );
      __memset( szRand, 0, oAuthLibDefaults::OAUTHLIB_BUFFSIZE );
      srand((UINT) time( nullptr ) );
      sprintf( szRand, "%x", rand()%1000 );
#ifdef WINDOWS
      sprintf( szTime, "%ld", (i32) time( nullptr ) );
#elif defined __LP64
      sprintf( szTime, "%ld", (i64) time( nullptr ) );
#else
      sprintf( szTime, "%d", (i32) time( nullptr ) );
#endif

      m_nonce = szTime;
      m_nonce += szRand;
      m_timeStamp = szTime;
   }

   /*++
   * @method: oauth::buildOAuthTokenKeyValuePairs
   *
   * @description: this method prepares key-value pairs required for OAuth header
   *               and signature generation.
   *
   * @input: includeOAuthVerifierPin - flag to indicate whether oauth_verifer key-value
   *                                   pair needs to be included. oauth_verifer is only
   *                                   used during exchanging request token with access token.
   *         rawData - url encoded data. this is used during signature generation.
   *         oauthSignature - base64 and url encoded OAuth signature.
   *
   * @output: keyValueMap - map in which key-value pairs are populated
   *
   * @remarks: internal method
   *
   *--*/
   bool oauth::buildOAuthTokenKeyValuePairs( const bool includeOAuthVerifierPin,
         oAuthKeyValuePairs & rawData,
         const string & oauthSignature,
         oAuthKeyValuePairs& keyValueMap )
   {
      UNREFERENCED_PARAMETER(rawData);
      /* Generate nonce and timestamp if required */
      generateNonceTimeStamp();

      /* Nonce key and its value */
      keyValueMap[OAUTHLIB_NONCE_KEY] = m_nonce;

      /* Signature method, only HMAC-SHA1 as of now */
      keyValueMap[OAUTHLIB_SIGNATUREMETHOD_KEY] = string( "HMAC-SHA1" );

      /* Timestamp */
      keyValueMap[OAUTHLIB_TIMESTAMP_KEY] = m_timeStamp;

      /* Consumer key and its value */
      keyValueMap[OAUTHLIB_CONSUMERKEY_KEY] = m_consumerKey;

      /* Signature if supplied */
      if( oauthSignature.get_length() > 0 )
      {
         keyValueMap[OAUTHLIB_SIGNATURE_KEY] = oauthSignature;
      }

      /* Token */
      if( m_oAuthTokenKey.get_length() > 0 )
      {
         keyValueMap[OAUTHLIB_TOKEN_KEY] = m_oAuthTokenKey;
      }

      /* Verifier */
      if( includeOAuthVerifierPin && ( m_oAuthPin.get_length() > 0 ) )
      {
         keyValueMap[OAUTHLIB_VERIFIER_KEY] = m_oAuthPin;
      }

      /* Version */
      keyValueMap[OAUTHLIB_VERSION_KEY] = string( "1.0" );

      //keyValueMap |= rawData;

      return ( keyValueMap.get_count() > 0 ) ? true : false;
   }

   /*++
   * @method: oauth::getSignature
   *
   * @description: this method calculates HMAC-SHA1 signature of OAuth header
   *
   * @input: eType - HTTP request type
   *         rawUrl - raw url of the HTTP request
   *         rawKeyValuePairs - key-value pairs containing OAuth headers and HTTP data
   *
   * @output: oAuthSignature - base64 and url encoded signature
   *
   * @remarks: internal method
   *
   *--*/
   bool oauth::getSignature( const eOAuthHttpRequestType eType,
                             const string & rawUrl,
                             const oAuthKeyValuePairs& rawKeyValuePairs,
                             string & oAuthSignature )
   {
      string rawParams( "" );
      string paramsSeperator( "" );
      string sigBase( "" );

      /* Initially empty signature */
      oAuthSignature = "";

      /* Build a string using key-value pairs */
      paramsSeperator = "&";
      getStringFromOAuthKeyValuePairs( rawKeyValuePairs, rawParams, paramsSeperator );

      /* Start constructing base signature string. Refer http://dev.twitter.com/auth#intro */
      switch( eType )
      {
      case eOAuthHttpGet:
      {
         sigBase = "GET&" ;
      }
      break;

      case eOAuthHttpPost:
      {
         sigBase = "POST&" ;
      }
      break;

      case eOAuthHttpDelete:
      {
         sigBase = "DELETE&" ;
      }
      break;

      default:
      {
         return false;
      }
      break;
      }
      sigBase.append(urlencode( rawUrl ) );
      sigBase.append("&");
      sigBase.append(urlencode(rawParams));

      /* Now, hash the signature base string using HMAC_SHA1 class */
      string secretSigningKey;

      /* Signing key is composed of consumer_secret&token_secret */
      secretSigningKey = m_consumerSecret;
      secretSigningKey += "&" ;
      if( m_oAuthTokenSecret.has_char())
      {
         secretSigningKey += m_oAuthTokenSecret;
      }

      //secretSigningKey ="MCD8BKwGdgPHvAuvgvz4EQpqDAtx89grbuNMRd7Eh98&J6zix3FfA9LofH0awS24M3HcBYXO5nI1iYe8EfBA";

      /* SHA 1 digest is 160 bits */
      memory memKey;
      memKey.from_hex(secretSigningKey);



      memory memHmac;
      memHmac.set_size(1024 * 16);

      //hmac_context context;
      System.crypto().hmac(memHmac, sigBase, secretSigningKey);
      //context.digest(memHmac.get_data(), sigBase, secretSigningKey);


      //string strHmac;
      //System.memory_to_hex(strHmac, memHmac);

      /* Do a base64 encode of signature */
      string base64Str = System.base64().encode(memHmac.get_data(), 20);

      /* Do an url encode */
      oAuthSignature = urlencode( base64Str );

      return ( oAuthSignature.get_length() > 0 ) ? true : false;
   }

   /*++
   * @method: oauth::getOAuthHeader
   *
   * @description: this method builds OAuth header that should be used in HTTP requests to twitter
   *
   * @input: eType - HTTP request type
   *         rawUrl - raw url of the HTTP request
   *         rawData - HTTP data
   *         includeOAuthVerifierPin - flag to indicate whether or not oauth_verifier needs to included
   *                                   in OAuth header
   *
   * @output: oAuthHttpHeader - OAuth header
   *
   *--*/
   bool oauth::getOAuthHeader(const eOAuthHttpRequestType eType, const string & rawUrl, property_set & set, const bool includeOAuthVerifierPin)
   {
      property_set setHeader;
      property_set setSignature;
      string rawParams( "" );
      string oauthSignature( "" );
      string paramsSeperator( "" );
      string pureUrl;
      property_set post;

      m_nonce.Empty();
      m_timeStamp.Empty();

      if (set.has_property("post") || eType == eOAuthHttpPost)
      {
         post = set["post"].propset();
      }

      /* If URL itself contains ?key=value, then extract and put them in map */

      index nPos = rawUrl.find( "?" );
      if(nPos >= 0)
      {
         /* Get only URL */
         pureUrl = rawUrl.Mid( 0, nPos );

         /* Get only key=value data part */
         string dataPart = rawUrl.Mid( nPos + 1 );

         property_set setUrl;
         setUrl.parse_url_query(dataPart);

         setSignature.merge(setUrl);

      }
      else
      {
         pureUrl = rawUrl;
      }

      /* Build key-value pairs needed for OAuth request token, without signature */
      buildOAuthTokenKeyValuePairs(includeOAuthVerifierPin, post, string( "" ), setSignature);


      setSignature.merge(post);

      /* Get url encoded base64 signature using request type, url and parameters */
      getSignature(eType, pureUrl, setSignature, oauthSignature);

      ::hi5::oAuthKeyValuePairs pairs(get_object());
      /* Now, again build key-value pairs with signature this time */
      buildOAuthTokenKeyValuePairs(includeOAuthVerifierPin, pairs, oauthSignature, setHeader);

      /* Get OAuth header in string format */
      paramsSeperator = ", ";
      getStringFromOAuthKeyValuePairs(setHeader, rawParams, paramsSeperator);

      //const string OAUTHLIB_AUTHHEADER_STRING = "Authorization: OAuth ";
      /* Build authorization header */
      set["headers"]["Authorization"] = "OAuth " + rawParams;


      return set["headers"].propset().get_count() > 0 ? true : false;
   }

   /*++
   * @method: oauth::getStringFromOAuthKeyValuePairs
   *
   * @description: this method builds a sorted string from key-value pairs
   *
   * @input: rawParamMap - key-value pairs map
   *         paramsSeperator - sepearator, either & or ,
   *
   * @output: rawParams - sorted string of OAuth parameters
   *
   * @remarks: internal method
   *
   *--*/
   bool oauth::getStringFromOAuthKeyValuePairs( const oAuthKeyValuePairs& rawParamMap,
         string & rawParams,
         const char * pszSeparator )
   {
      string strSeparator(pszSeparator);
      rawParams =  "";
      if( rawParamMap.get_count() )
      {
         oAuthKeyValueList keyValueList;
         string str( "" );

         /* Push key-value pairs to a list of strings */
         keyValueList.remove_all();

         for(auto property : rawParamMap)
         {
            string key = property.name();
            string value = property.get_value();
            str = key ;
            str +=  "=" ;
            if( strSeparator == ", " )
            {
               str+= "\"" ;
            }
            str +=  value;
            if( strSeparator == ", " )
            {
               str += "\"" ;
            }
            keyValueList.add( str );
         }

         /* Sort key-value pairs based on key name */
         if( strSeparator == "&" )
         {

            keyValueList.sort();

            for(i32 i = 0; i < keyValueList.get_count(); i++)
            {

               index iFind = keyValueList[i].find("=");

               if(iFind >= 0)
               {

                  str = urlencode(keyValueList[i].Left(iFind)) + "=" + urlencode(keyValueList[i].Mid(iFind+ 1));

                  keyValueList[i] = str;

               }

            }

         }

         /* Now, form a string */
         rawParams =  keyValueList.implode(pszSeparator);

      }

      return ( rawParams.get_length() > 0 ) ? true : false;

   }

   /*++
   * @method: oauth::extractOAuthTokenKeySecret
   *
   * @description: this method extracts oauth token key and secret from
   *               twitter's HTTP response
   *
   * @input: requestTokenResponse - response from twitter
   *
   * @output: none
   *
   *--*/
   bool oauth::extractOAuthTokenKeySecret(const string & requestTokenResponse )
   {

      if( requestTokenResponse.get_length() > 0 )
      {

         index nPos = -1;

         string strDummy( "" );

         /* Get oauth_token key */
         nPos = requestTokenResponse.find(OAUTHLIB_TOKEN_KEY);

         if(nPos >=0)
         {

            nPos = nPos + OAUTHLIB_TOKEN_KEY.get_length() + strlen( "=" );

            strDummy = requestTokenResponse.Mid( nPos );

            nPos = strDummy.find( "&" );

            if( nPos >= 0)
            {

               m_oAuthTokenKey = strDummy.Mid( 0, nPos );

            }

         }

         /* Get oauth_token_secret */

         nPos = requestTokenResponse.find(OAUTHLIB_TOKENSECRET_KEY );

         if( nPos >= 0 )
         {

            nPos = nPos + OAUTHLIB_TOKENSECRET_KEY.get_length() + strlen( "=" );

            strDummy = requestTokenResponse.Mid( nPos );

            nPos = strDummy.find( "&" );

            if( nPos >= 0 )
            {

               m_oAuthTokenSecret = strDummy.Mid( 0, nPos );

            }

         }

         /* Get screen_name */
         nPos = requestTokenResponse.find(OAUTHLIB_SCREENNAME_KEY );

         if( nPos >= 0 )
         {

            nPos = nPos + OAUTHLIB_SCREENNAME_KEY.get_length() + strlen( "=" );

            strDummy = requestTokenResponse.Mid( nPos );

            m_oAuthScreenName = strDummy;

         }

      }

      return true;

   }


} // namespace aura

