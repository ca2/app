// Copyright (C) 2009,2010,2011,2012 GlavSoft LLC.
// All rights reserved.
//
//-------------------------------------------------------------------------
// This file is part of the TightVNC software.  Please visit our Web site:
//
//                       http://www.tightvnc.com/
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along
// with this program; if not, w_rite to the Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
//-------------------------------------------------------------------------
//

#pragma once


#include "subsystem/_common_header.h"
//////#include "subsystem/platform/::string.h"
//#include "log_writer/LogWriter.h"
//#include "subsystem/node/Impersonator.h"
//#include "subsystem/node/SystemException.h"


namespace subsystem
{


   /**
   Class for impersonating current process as user that logged on current
   console session.
   @remark: can work only in XP and later cause it uses WTSQueryUserToken function.
   */
   class ImpersonatorInterface :
   virtual public ::Particle
   {
   public:
      //Impersonator(LogWriter *plogwriter);
      ///Impersonator();
      //virtual ~ImpersonatorInterface() = 0 ;


      virtual void initialize_impersonator(LogWriter *plogwriter) = 0;

      /**
      Impersonates calling process as user that logged on current console session.
      @throws SystemException if impersonation fails.
      */
      virtual void impersonateAsLoggedUser() = 0;

      /**
      Impersonates calling process as user with given token.
      @throws SystemException if impersonation fails.
      */
      virtual void impersonateAsCurrentProcessUser(bool rdpEnabled) = 0;

      /**
      Cancels effect of impersonateAsLoggedUser method call.
      @throws SystemException on fail.
      */
      virtual void revertToSelf() = 0;

      virtual bool sessionIsLocked(bool rdpEnabled) = 0;

   //protected:
     // void impersonateAsUser(HANDLE token);

      //HANDLE m_token;
      //HANDLE m_dupToken;

      //LogWriter *m_plogwriter;
   };


    //using ImpersonatorInterface = particle_interface<ImpersonatorInterface>;
   /**
   Class for impersonating current process as user that logged on current
   console session.
   @remark: can work only in XP and later cause it uses WTSQueryUserToken function.
   */
   class CLASS_DECL_SUBSYSTEM ImpersonatorComposite :
   virtual public Composite<ImpersonatorInterface>
   {
   public:

       ImplementCompositeø(Impersonator, impersonator)

      //Impersonator();
      //~Impersonator() override;

          void initialize_impersonator(LogWriter* plogwriter) override
       {

          return m_pimpersonator->initialize_impersonator(plogwriter);

       }

      /**
      Impersonates calling process as user that logged on current console session.
      @throws SystemException if impersonation fails.
      */
       void impersonateAsLoggedUser() override
       {

          m_pimpersonator->impersonateAsLoggedUser();

      }

      /**
      Impersonates calling process as user with given token.
      @throws SystemException if impersonation fails.
      */
       void impersonateAsCurrentProcessUser(bool rdpEnabled) override
       {

          m_pimpersonator->impersonateAsCurrentProcessUser(rdpEnabled);

      }

      /**
      Cancels effect of impersonateAsLoggedUser method call.
      @throws SystemException on fail.
      */
       void revertToSelf() override
       {

          m_pimpersonator->revertToSelf();

      }

       bool sessionIsLocked(bool rdpEnabled) override
       {

          return m_pimpersonator->sessionIsLocked(rdpEnabled);

      }

   //protected:
      //void impersonateAsUser(HANDLE token);

      // HANDLE m_token;
      // HANDLE m_dupToken;
      //
      // LogWriter *m_plogwriter;
   };


    class CLASS_DECL_SUBSYSTEM ImpersonatorAggregate :
    virtual public Aggregate< ImpersonatorComposite >
    {
    public:

        ImplementBaseø(Impersonator);

    };



   class CLASS_DECL_SUBSYSTEM Impersonator :
 virtual public Object < ImpersonatorAggregate >
   {
   public:

      ImplementObjectø(Impersonator)

   };



} // namespace subsystem


