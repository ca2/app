//
//  account_credentials.cpp
//  aura
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 12/12/18.
//
#include "framework.h"
#include "credentials.h"
#include "interactive.h"
#include "user.h"
#include "acme/prototype/mathematics/mathematics.h"
////#include "acme/exception/exception.h"
//#include "acme/prototype/string/hex.h"
//#include "acme/prototype/time/integral/operator.h"
#include "acme/crypto/crypto.h"
#include "apex/networking/http/context.h"
#include "apex/platform/context.h"
#include "axis/networking/email_department.h"
#include "axis/platform/application.h"
#include "axis/platform/system.h"


namespace account
{


   credentials::credentials()
   {

   }


   void credentials::initialize_account_credentials(const credentials & credentials)
   {

      initialize_account_storage_client(credentials.m_pstorage);

      m_puser = credentials.m_puser;

      m_iPasswordOriginalLength = credentials.m_iPasswordOriginalLength;

      m_strToken = credentials.m_strToken;

      m_strTitle = credentials.m_strTitle;

      m_pinteractive = credentials.m_pinteractive;

      m_strSecret = credentials.m_strSecret;

      m_estatus = credentials.m_estatus;

      m_strLabel_user = credentials.m_strLabel_user;
      m_strLabel_pass = credentials.m_strLabel_pass;
      m_strLabel_open = credentials.m_strLabel_open;

      m_strResponse = credentials.m_strResponse;

      m_strModHash = credentials.m_strModHash;
      m_strKeyHash = credentials.m_strKeyHash;
      m_strCa2Hash = credentials.m_strCa2Hash;

      m_strRsa = credentials.m_strRsa;
      m_strSecret = credentials.m_strSecret;

      m_strPassword = credentials.m_strPassword;
      m_strPasshash = credentials.m_strPasshash;

      m_rectangleDialog = credentials.m_rectangleDialog;

      m_estatusHttp = credentials.m_estatusHttp;

   }


   void credentials::initialize_account_credentials(::account::user * puser, storage * pstorage) 
   {

      initialize_account_storage_client(pstorage);

      m_puser = puser;

      m_iPasswordOriginalLength = -1;

      m_strToken = "ca2";

      m_strTitle = "ca2";

      m_pinteractive = nullptr;

      string strFormat;

      for(i32 i = 0; i < 64; i += 2)
      {

         char iDigit = mathematics()->random_char();

         strFormat = ::hex::lower_case_padded_from<2>(iDigit);

         m_strSecret += strFormat;

      }

      m_estatus = error_none;

   }


   credentials::~credentials()
   {

   }


   void credentials::get_credentials()
   {

      m_estatus = error_none;

      ::e_status estatus = load_from_storage();

      if(estatus == ::success_credentials || estatus == ::success_authenticated)
      {

         return;

      }

      interactive_credentials();

   }


   /// input
   /// m_strToken
   /// m_strTitle
   /// m_rectangleDialog
   /// m_pinteractive (optionally?)
   ///
   /// output
   /// m_strUsername
   /// m_strPassword
   void credentials::interactive_credentials()
   {

      m_estatus = error_none;

      if(!m_bInteractive)
      {

         throw ::exception(error_credentials_no_valid_cached_credentials);

      }

      m_iPasswordOriginalLength = -1;
      m_strPassword.empty();

      ASSERT(m_strToken.has_char());
      ASSERT(m_strTitle.has_char());

      if(m_pinteractive != nullptr)
      {

         m_pinteractive->interactive_credentials(this);

      }

      ::pointer<::axis::application>papp = get_app();

      papp->interactive_credentials(this);

      //return m_estatus;

   }


   /// input
   /// m_strToken
   ///
   /// output
   /// m_strUsername
   /// m_strPassword
   ::e_status credentials::load_from_storage(::collection::count cTry)
   {

      if (cTry <= 0)
      {

         cTry = 1;

      }
      
      string strOpen;

      string strOlen;

      ::collection::index iTry = 0;

      while(true)
      {

         bool bOk = true;

         string strUser;

         if (bOk && !get("user", strUser))
         {

            bOk = false;

         }

         string strHash;

         if (bOk && !get("hash", strHash))
         {

            bOk = false;

         }

         if (bOk && !get("olen", strOlen))
         {

            bOk = false;

         }

         if (bOk && !get("open", strOpen))
         {

            bOk = false;

         }

         auto psystem = system()->m_paxissystem;

         bool bBadUser = strUser.is_empty()
            || !psystem->email().is_valid_public_address(strUser);

         bool bBadHash = strHash.length() < 80
            || strOlen.is_empty()
            || atoi(strOlen) < 4;

         bool bBadOpen = strOpen.is_empty();

         if (bBadUser || bBadHash || bBadOpen)
         {

            if (bBadUser)
            {

               m_puser->m_strLogin.empty();

            }

            if (bBadUser || bBadHash)
            {

               m_strPasshash.empty();

               m_strPassword.empty();

               m_iPasswordOriginalLength = -1;

            }

            return error_not_found;

         }

         if (bOk)
         {

            auto estatus = (::e_status) ::ansi_to_i64(strOpen);

            if (estatus == ::success_credentials || estatus == ::success_authenticated)
            {

               m_puser->m_strLogin = strUser;

               m_strPasshash = strHash;

               m_iPasswordOriginalLength = ansi_to_i32(strOlen);

               return ::success_credentials;

            }
            else
            {

               return error_failed;

            }

         }

         if (iTry >= cTry)
         {

            return error_timeout;

         }

         if (!task_sleep(40_ms * iTry))
         {

            return error_cancelled;

         }

         iTry++;

      }

      return error_io;

   }


   void credentials::save_status_to_storage(const ::e_status & estatus)
   {

      string strStatus = as_string(estatus.as_i64());

      set("open", strStatus);

   }


   bool credentials::is_ok()
   {

      if(m_puser->m_strLogin.length() <= 3)
      {

         m_estatus = error_credentials_invalid_login;

         return false;

      }

      if((m_strPassword.length() < 5
         && m_strPasshash.length() < 80)
            || m_iPasswordOriginalLength < 5)
      {

         m_estatus = error_credentials_invalid_password;

         return false;

      }

      return true;

   }


   void credentials::save_to_storage()
   {

      if(m_puser->m_strLogin.is_empty()
            || m_strPassword.is_empty()
            || m_iPasswordOriginalLength <= 0)
      {

         string strOpenResult = as_string((int) error_authentication);

         set("open", strOpenResult);

         throw ::exception(error_authentication);

      }

      ::account::user userPrevious;

      userPrevious.initialize(this);

      credentials credentialsPrevious;
      
      credentialsPrevious.initialize_account_credentials(&userPrevious, m_pstorage);

      credentialsPrevious.load_from_storage();

      if(userPrevious.m_strLogin != m_puser->m_strLogin
            || credentialsPrevious.m_strPassword != m_strPassword
            || credentialsPrevious.m_iPasswordOriginalLength != m_iPasswordOriginalLength)
      {

         set("user", m_puser->m_strLogin);

         set("hash", m_strPasshash);

         string strPasswordOriginalLength;

         strPasswordOriginalLength = as_string(m_iPasswordOriginalLength);

         set("olen", strPasswordOriginalLength);

      }

      //return estatus;

   }


   void credentials::get_mod(string_array & straHash,string_array & straSource)
   {

      straHash.erase_all();
      straSource.erase_all();

   }


   string credentials::calc_mod_hash()
   {

      if(m_strModHash.has_char())
      {

         return m_strModHash;

      }

      string_array straHash;

      string_array straSource;

      get_mod(straHash,straSource);

      auto psystem = system()->m_paxissystem;

      m_strModHash = psystem->crypto()->md5(straHash.implode(";"));

      return m_strModHash;

   }


   string credentials::calc_key_hash()
   {

      if(m_strKeyHash.has_char())
      {

         return m_strKeyHash;

      }

      m_strKeyHash = "ca2_12n";

      return "ca2_12n";

   }


   string credentials::calc_ca2_hash()
   {

      if(m_strCa2Hash.has_char())
      {

         return m_strCa2Hash;

      }

      m_strCa2Hash = "ca2_12n";

      return m_strCa2Hash;

   }


   /// return hash and check if hash is valid
   bool credentials::check_ca2_hash()
   {

      string strUrl("https://api.ca2.software/account/check_hash");

      property_set set;

      string strResponse;

      string_array straHash;

      string_array straSource;

      get_mod(straHash,straSource);

      straHash.insert_at(0, m_strPasshash);

      straHash.insert_at(0, m_puser->m_strLogin);

      set["post"]["hash"] = straHash.implode(";");

      set["post"]["source"] = straHash.implode(";");

      for(i32 i = 0; i < 3; i++)
      {

         try
         {

            http()->get(strUrl, strResponse, set);

            break;

         }
         catch (const ::exception& exception)
         {

            error() <<"check_ca2_hash " << exception.m_estatus.as_i64();

         }

      }

      if(strResponse != "OK")
      {

         return false;

      }

      return true;

   }


} // namespace account



