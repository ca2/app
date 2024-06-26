//
// Created by camilo on 2024-06-02 19:54 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "acme/primitive/primitive/particle.h"


namespace nano
{


   namespace account
   {


      class user :
         virtual public ::particle
      {
      public:


         ::string       m_strName;       /* username */
         ::string       m_strPasswd;     /* user password */
         ::u64          m_uUserid;       /* user ID */
         ::u64          m_uGroupid;      /* group ID */
         ::string       m_strGecos;      /* user information */
         ::string       m_strDir;        /* home directory */
         ::string       m_strShell;      /* shell program */


         user();
         ~user() override;


      };


   } // namespace account


} // namespace nano



