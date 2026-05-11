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


#include "subsystem/platform/Exception.h"



namespace subsystem
{
   /**
    * Operating System exception.
    *
    * Solves problem with generating formatted message strings width describes
    * user code-space where error occured and windows specific information about WinAPI error.
    */
   class CLASS_DECL_SUBSYSTEM SystemException : public ::subsystem::Exception
   {
   public:
      
      //private:
         /**
          * Description of error from OS.
          */
         ::string m_strSystemMessage;
         /**
          * Windows error code.
          */
         //int m_errcode;
         error_code m_errorcode;
      /**
       * Creates exception with formatted message from system
       * and error code which equals to GetLastError() value.
       */
      SystemException();
      /**
       * Creates exception with formatted message from system
       * and error code.
       * @param errorcode windows error code.
       */
      SystemException(const ::error_code & errorcode);
      /**
       * Creates exception with user message + formatted message from system
       * and error code set to GetLastError() value.
       * @param scopedstrUserMessage user message.
       */
      SystemException(const ::scoped_string & scopedstrUserMessage);
      /**
       * Creates exception with user message + formatted message from system
       * and specified error code.
       * @param scopedstrUserMessage user message.
       * @param errorcode error code.
       */
      SystemException(const ::scoped_string & scopedstrUserMessage, const ::error_code & errorcode);
      /**
       * Destructor, does nothing.
       */
      virtual ~SystemException();
      /**
       * Returns error code.
       * @return windows error code associated with this exception.
       */
      ::error_code getErrorCode() const;
      /**
       * Returns system error description.
       * @return system error description.
       */
      ::string getSystemErrorDescription() const;
   //private:
      /**
       * Creates formatted message for exception.
       * @param scopedstrUserMessage user description about exception reason.
       * @param errorcode error code.
       * @fixme document all special cases.
       */
      void createMessage(const ::scoped_string & scopedstrUserMessage, const ::error_code & errorcode);

   };
}//namespace subsystem
