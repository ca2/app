// Copyright (C) 2010,2011,2012 GlavSoft LLC.
// Copyright (C) 2010,2011,2012 GlavSoft LLC.
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


//#include "remoting/remoting_common/util/winhdr.h"
//#include "acme/operating_system/windows/subsystem/_common_header.h"

//#include "remoting/remoting_common/thread/LocalMutex.h"
//#include "acme/operating_system/windows/subsystem/node/DynamicLibrary.h"
//#include "acme/SystemException.h"
//#include "log_writer/LogWriter.h"
#include "acme/operating_system/windows/subsystem/_common_header.h"
#include <WtsApi32.h>

namespace windows
{
   typedef DWORD (WINAPI *pWTSGetActiveConsoleSessionId)(void);
   typedef BOOL (WINAPI *pWTSQueryUserToken)(ULONG SessionId, PHANDLE phToken);
   typedef BOOL (WINAPI *pWTSQuerySessionInformationW)(
     HANDLE hServer, DWORD SessionId,
     WTS_INFO_CLASS WTSInfoClass,
     LPWSTR **ppBuffer,
     DWORD *pBytesReturned);
   typedef BOOL (WINAPI *pWTSQuerySessionInformationA)(
     HANDLE hServer, DWORD SessionId,
     WTS_INFO_CLASS WTSInfoClass,
     LPSTR **ppBuffer,
     DWORD *pBytesReturned);
   typedef VOID (WINAPI *pWTSFreeMemory)(void *buffer);
   typedef BOOL(WINAPI *pWTSEnumerateSessionsA)(
     IN HANDLE          hServer,
     IN DWORD           Reserved,
     IN DWORD           Version,
     PWTS_SESSION_INFOA *ppSessionInfo,
     DWORD              *pCount
   );
   typedef BOOL(WINAPI *pWTSEnumerateSessionsW)(
     IN HANDLE          hServer,
     IN DWORD           Reserved,
     IN DWORD           Version,
     PWTS_SESSION_INFOW *ppSessionInfo,
     DWORD              *pCount
     );

#ifdef UNICODE
#define   pWTSQuerySessionInformation pWTSQuerySessionInformationW
#define   pWTSEnumerateSessions pWTSEnumerateSessionsW
#else
#define pWTSQuerySessionInformation pWTSQuerySessionInformationA
#define pWTSEnumerateSessions pWTSEnumerateSessionsA
#endif


   /**
    * Wrapper over WTS WinAPI functions.
    *
    * @author enikey.
    */
   class CLASS_DECL_ACME WTS :
    virtual public ::particle
   {
   public:

       ::pointer < ::windows::subsystem::DynamicLibrary > m_pdynamiclibraryKernel32;
       ::pointer < ::windows::subsystem::DynamicLibrary > m_pdynamiclibraryWtsApi32;
       pWTSGetActiveConsoleSessionId m_WTSGetActiveConsoleSessionId;
       pWTSQueryUserToken m_WTSQueryUserToken;
       pWTSQuerySessionInformation m_WTSQuerySessionInformation;
       pWTSFreeMemory m_WTSFreeMemory;
       pWTSEnumerateSessions m_WTSEnumerateSessions;

      /**
       * Determinates if WTS library was initialized.
       */
       volatile bool m_initialized;

      /**
       * Token of interactive user process in active console session
       * that will be used if WTSQueryToken WinAPI function is unavaliable
       * in queryConsoleUserToken() call.
       */
       HANDLE m_userProcessToken;

      /**
       * Thread-safety.
       */
       critical_section m_mutex;

       WTS();

       ~WTS() override;


      /**
 * Initializes WTS functions.
 */
      virtual void initialize_wts(::subsystem::LogWriter *log);


      /**
       * Gets active console session id.
       * @return active console session id if WTS is avaliable or 0 if
       * WinAPI WTSGetActiveConsoleSessionId function not avaliable.
       */
       virtual DWORD getActiveConsoleSessionId(::subsystem::LogWriter *log);

      /**
      * Gets RDP console session id.
      * @return RDP console session id if WTS is avaliable and RDP console exists or 0 if
      * WinAPI WTSEnumerateSessions function not avaliable or there is no sessions with RDP in name.
      */
       virtual DWORD getRdpSessionId(::subsystem::LogWriter *log);

      /**
      * @return true if sessionId is the RDP console session id.
      */
       virtual bool SessionIsRdpSession(DWORD sessionId, ::subsystem::LogWriter *log);

      /**
       * Queries user token in active console session.
       * @return user token.
       * @throws SystemException on fail.
       * @remark if WTSQueryUserToken is avaliable when it will be used with
       * session id equal to active console session id, if not, then user
       * process id will be used to get user token (this id can be set by using of
       * defineConsoleUserProcessId() method).
       */
       virtual HANDLE queryConsoleUserToken(::subsystem::LogWriter *log);

       HANDLE sessionUserToken(DWORD sessionId, ::subsystem::LogWriter* log);

      /**
       * Defines global (for WTS class) user process that will be used
       * for getting token of user in active console session if WTSQueryUserToken WinAPI function
       * is unavaliable (Windows 2000 case).
       * @param userProcessId user process id.
       */
       virtual void defineConsoleUserProcessId(DWORD userProcessId);

      // This function dupplicate token impersonated to named pipe cliend end.
      // This should work only for win2000 because other windows version have
      // rdp.
       virtual void duplicatePipeClientToken(HANDLE pipeHandle);

       virtual ::string getUserName(DWORD sessionId,::subsystem:: LogWriter *log);
       virtual ::string getCurrentUserName(::subsystem::LogWriter* log);

       virtual bool sessionIsLocked(DWORD sessionId, ::subsystem::LogWriter* log);

       virtual HANDLE duplicateCurrentProcessUserToken(bool rdpEnabled,::subsystem:: LogWriter* log);

       virtual HANDLE duplicateUserImpersonationToken(HANDLE token, DWORD sessionId, ::subsystem::LogWriter* log);

      /**
       * Returns user name for given access token.
       * @param token access or impersonation token.
       */
       virtual ::string getTokenUserName(HANDLE token);

   //private:
      /**
       * Don't allow instanizing of WTS class.
       */
      //WTS();


      // The initialize() function should be already called before use the wtsFreeMemory() function.
       virtual void wtsFreeMemory(void *buffer);


   };


} // namespace windows


