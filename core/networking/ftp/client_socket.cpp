////////////////////////////////////////////////////////////////////////////////
//
// The official specification of the File Transfer Protocol (FTP) is the RFC 959.
// Most of the documentation are taken from this RFC.
// This is an implementation of an simple FTP client_socket. I have tried to implement
// platform independent. For the communication i used the classes transfer_socket,
// ::networking::address, ... from David J. Kruglinski (Inside Visual C++). These classes are
// only small wrappers for the sockets-API.
// Further I used a smart pointer-implementation from Scott Meyers (Effective C++,
// More Effective C++, Effective STL).
// The implementation of the logon-sequence (with firewall support) was published
// in an article on Codeguru by Phil Anderson.
// The code for the parsing of the different FTP LIST responses is taken from
// D. J. Bernstein (http://color32.yp.to/ftpparse.html). I only wrapped the c-code in
// a class.
// I have tested the code on Windows and Linux (Kubuntu).
//
// Copyright (c) 2004-2012 Thomas Oswald
//
// Permission to copy, use, sell and distribute this software is granted
// provided this copyright notice appears in all copies.
// Permission to modify the code and to distribute modified code is granted
// provided this copyright notice appears in all copies, and a notice
// that the code was modified is included with the copyright notice.
//
// This software is provided "as is" without express or implied warranty,
// and with no claim as to its suitability for any purpose.
//
// History:
// v1.5 released 2007-06-01
//+# TODO
// v1.1 released 2005-12-04
//      - Bug in OpenPassiveDataConnection erased: SendCommand was called before data connection was established.
//      - Bugs in GetSingleResponseLine erased:
//         * Infinite loop if response line doesn't end with CRLF.
//         * Return value of std:string->find must be checked against npos.
//      - Now runs in unicode.
//      - Streams erased.
//      - Explicit detaching of observers are not necessary anymore.
//      - ExecuteDatachannelCommand now accepts an itransfer_notification object.
//        Through this concept there is no need to write the received files to a file.
//        For example the bytes can be written only in memory or an other tcp stream.
//      - Added an interface for the blocking socket (::sockets::transfer_socket).
//        Therefore it is possible to exchange the socket implementation, e.g. for
//        writing unit tests (by simulating an specific scenario of a FTP communication).
//      - Replaced the magic numbers concerning the reply codes by a class.
// v1.0 released 2004-10-25
////////////////////////////////////////////////////////////////////////////////
#include "framework.h"
#include "client_socket.h"
#include "output_stream.h"
#include "file.h"
#include "acme/filesystem/file/memory_file.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/platform/error.h"
#include "apex/networking/sockets/basic/listen_socket.h"
#include "apex/networking/sockets/transfer_socket.h"
#include "apex/networking/sockets/base/socket_handler.h"
#include "apex/platform/system.h"
#include <openssl/x509.h>


namespace ftp
{




   //////////////////////////////////////////////////////////////////////
   // Construction/Destruction
   //////////////////////////////////////////////////////////////////////

   /// constructor
   /// @lparam[in] apSocket Instance of socket class which will be used for
   ///                     communication with the FTP server.
   ///                     client_socket class takes composite of this instance.
   ///                     It will be deleted on destruction of this object.
   ///                     If this pointer is nullptr, the transfer_socket implementation
   ///                     will be used.
   ///                     This gives the ability to set an other socket class.
   ///                     For example a socket class can be implemented which simulates
   ///                     a FTP server (for unit testing).
   /// @lparam[in] uiTimeout Timeout used for socket operation.
   /// @lparam[in] uiBufferSize Size of the buffer used for sending and receiving
   ///                         data via sockets. The size_i32 have an influence on
   ///                         the performance. Through empiric test i come to the
   ///                         conclusion that 2048 is a good size.
   /// @lparam[in] uiResponseWait sleep time between receive calls to socket when getting
   ///                           the response. Sometimes the socket hangs if no wait time
   ///                           is set. Normally not wait time is necessary.
   client_socket::client_socket(
                                const ::duration & durationTimeout/*=10*/,
                                unsigned int uiBufferSize/*=2048*/, const ::duration & durationResponseWait/*=0*/,
                                const string& strRemoteDirectorySeparator/*="/"*/) :
      //::sockets::base_socket(handler),
      //::sockets::socket(handler),
      //::sockets::stream_socket(handler),
      //::sockets::tcp_socket(handler),
      m_durationTimeout(durationTimeout),
      m_durationResponseWait(durationResponseWait),
      mc_strEolCharacterSequence("\r\n"),
      mc_strRemoteDirectorySeparator(strRemoteDirectorySeparator),//+# documentation missing
      m_apFileListParser(__new(file_list_parser())),
      m_fTransferInProgress(false),
      m_fAbortTransfer(false),
      m_fResumeIfPossible(true)
   {

      m_econnectiontype = connection_type_plain;

      defer_create_synchronization();

      m_estate = e_state_initial;

      m_vBuffer.set_size(uiBufferSize);

   }


   /// destructor
   client_socket::~client_socket()
   {
      if (IsTransferringData())
         _abort();

      if (_is_connected())
         Logout();
   }

   /// Attach an observer to the client_socket. You can attach as many observers as you want.
   /// The client_socket send notifications (more precisely the virtual functions are called)
   /// to the observers.
   void client_socket::AttachObserver(client_socket::notification* pObserver)
   {
      ASSERT(pObserver);
      if (pObserver)
         m_setObserver.attach_observer(pObserver);
   }

   /// Detach an observer from the client_socket.
   void client_socket::DetachObserver(client_socket::notification* pObserver)
   {
      ASSERT(pObserver);
      if (pObserver)
         m_setObserver.detach_observer(pObserver);
   }

   /// Sets the file list parser which is used for parsing the results of the LIST command.
   void client_socket::SetFileListParser(::pointer<ifile_list_parser>apFileListParser)
   {
      m_apFileListParser = apFileListParser;
   }

   /// Returns a set of all observers currently attached to the client_socket.
   client_socket::observer_array& client_socket::GetObservers()
   {
      return m_setObserver;
   }

   /// Enables or disables resuming for file transfer operations.
   /// @lparam[in] fEnable True enables resuming, false disables it.
   void client_socket::SetResumeMode(bool fEnable/*=true*/)
   {
      m_fResumeIfPossible = fEnable;
   }

   /// Indicates if the resume mode is set.
   bool client_socket::IsResumeModeEnabled()
   {
      return m_fResumeIfPossible;
   }

   /// Opens the control channel to the FTP server.
   /// @lparam[in] strServerHost IP-::networking::address or name of the server
   /// @lparam[in] iServerPort Port for channel. Usually this is port 21.
   bool client_socket::OpenControlChannel(const string& strServerHost, ::u16 ushServerPort/*=DEFAULT_FTP_PORT*/)
   {

      if (IsConnected() || _is_connected())
      {

         CloseControlChannel();

      }

      SetLineProtocol();

      try
      {

         if (!open(strServerHost, ushServerPort))
         {

            return false;

         }

      }
      catch (::sockets::transfer_socket_exception& blockingException)
      {
         ReportError(blockingException.get_message(), __FILE__, __LINE__);
         SetCloseAndDelete();
         return false;
      }

      socket_handler()->add(this);

      return true;

   }


   /// Returns the connection state of the client_socket.
   bool client_socket::_is_connected()
   {
      //return GetSocket() != INVALID_SOCKET;

      return is_valid();
   }

   /// Returns true if a download/upload is running, otherwise false.
   bool client_socket::IsTransferringData()
   {
      return m_fTransferInProgress;
   }

   /// Closes the control channel to the FTP server.
   void client_socket::CloseControlChannel()
   {
      try
      {
         SetCloseAndDelete();
         m_apCurrentRepresentation.release();
      }
      catch (::sockets::transfer_socket_exception& blockingException)
      {
         blockingException.get_message();
         SetCloseAndDelete();
      }
   }

   /// Analyse the repy code of a FTP server-response.
   /// @lparam[in] Reply Reply of a FTP server.
   /// @retval FTP_OK    All runs perfect.
   /// @retval FTP_ERROR Something went wrong. An other response was expected.
   /// @retval NOT_OK    The command was not accepted.
   int client_socket::SimpleErrorCheck(const reply& Reply)
   {
      if (Reply.Code().IsNegativeReply())
         return FTP_NOTOK;
      else if (Reply.Code().IsPositiveCompletionReply())
         return FTP_OK;

      ASSERT(Reply.Code().IsPositiveReply());

      return FTP_ERROR;
   }

   long client_socket::cert_common_name_check(const ::string & common_name)
   {

      long l = ::sockets::tcp_socket::cert_common_name_check(common_name);

      if (l == X509_V_ERR_DEPTH_ZERO_SELF_SIGNED_CERT)
      {

         return X509_V_OK;

      }

      return l;

   }

   /// Logs on to a FTP server.
   /// @lparam[in] logonInfo Structure with logon information.
   bool client_socket::Login(logon * plogon)
   {
      plogon->m_bFailedBecauseOfSecurityLevelCanUpgrade = false;
      m_plogon = plogon;

      enum
      {
         LO = -2,      ///< Logged On
         ER = -1,      ///< Error
         NUMLOGIN = 9, ///< currently supports 9 different login sequences
      };

      int iLogonSeq[NUMLOGIN][18] =
      {
         // this array stores all of the logon sequences for the various firewalls
         // in blocks of 3 nums.
         // 1st num is command to send,
         // 2nd num is next point_i32 in logon sequence array if 200 series response
         //         is rec'd from server as the result of the command,
         // 3rd num is next point_i32 in logon sequence if 300 series rec'd
         { 0,LO,3,    1,LO, 6,   2,LO,ER }, // no firewall
         { 3, 6,3,    4, 6,ER,   5,ER, 9,   0,LO,12,   1,LO,15,   2,LO,ER }, // SITE hostname
         { 3, 6,3,    4, 6,ER,   6,LO, 9,   1,LO,12,   2,LO,ER }, // USER after logon
         { 7, 3,3,    0,LO, 6,   1,LO, 9,   2,LO,ER }, // proxy OPEN
         { 3, 6,3,    4, 6,ER,   0,LO, 9,   1,LO,12,   2,LO,ER }, // Transparent
         { 6,LO,3,    1,LO, 6,   2,LO,ER }, // USER with no logon
         { 8, 6,3,    4, 6,ER,   0,LO, 9,   1,LO,12,   2,LO,ER }, // USER fireID@remotehost
         { 9,ER,3,    1,LO, 6,   2,LO,ER }, // USER remoteID@remotehost fireID
         { 10,LO,3,   11,LO, 6,   2,LO,ER }  // USER remoteID@fireID@remotehost
      };

      // are we connecting directly to the host (logon type 0) or via a firewall? (logon type>0)
      string   strTemp;
      ::u16    ushPort = 0;

      if (_is_connected())
         Logout();


      if (plogon->FwType() == firewall_type::None())
      {

         if (m_econnectiontype == connection_type_tls_implicit)
         {

            strTemp = plogon->Hostname();
            ushPort = 990;
            EnableSSL();
            set_host(strTemp);

         }
         else
         {

            strTemp = plogon->Hostname();
            ushPort = plogon->Hostport();

         }

      }
      else
      {
         strTemp = plogon->FwHost();
         ushPort = plogon->FwPort();
      }

      string strHostnamePort(plogon->Hostname());
      if (plogon->Hostport() != DEFAULT_FTP_PORT)
         strHostnamePort = plogon->Hostname() + ":" + __string(plogon->Hostport()); // add port to hostname (only if port is not 21)


      if (!OpenControlChannel(strTemp, ushPort))
         return false;

      if (m_econnectiontype == connection_type_tls_implicit)
      {

         // SetCallOnConnect();

      }

      // get initial connect msg off server
      reply Reply;
      if (!GetResponse(Reply) || !Reply.Code().IsPositiveCompletionReply())
         return false;

      int iLogonPoint = 0;

      // go through appropriate logon procedure
      for (; ; )
      {
         // send command, get response
         reply Reply;
         switch (iLogonSeq[plogon->FwType().AsEnum()][iLogonPoint])
         {
         // state                 command           command argument                                                                              success     fail
         case 0:  if (SendCommand(command::USER(), {plogon->Username() }, Reply)) break; else return false;
         case 1:  if (SendCommand(command::PASS(), {plogon->Password() }, Reply)) break; else return false;
         case 2:  if (SendCommand(command::ACCT(), {plogon->Account() }, Reply)) break; else return false;
         case 3:  if (SendCommand(command::USER(), {plogon->FwUsername() }, Reply)) break; else return false;
         case 4:  if (SendCommand(command::PASS(), {plogon->FwPassword() }, Reply)) break; else return false;
         case 5:  if (SendCommand(command::SITE(), {strHostnamePort }, Reply)) break; else return false;
         case 6:  if (SendCommand(command::USER(), {plogon->Username() + "@" + strHostnamePort }, Reply)) break; else return false;
         case 7:  if (SendCommand(command::OPEN(), {strHostnamePort }, Reply)) break; else return false;
         case 8:  if (SendCommand(command::USER(), {plogon->FwUsername() + "@" + strHostnamePort }, Reply)) break; else return false;
         case 9:  if (SendCommand(command::USER(), {plogon->Username() + "@" + strHostnamePort + " " + plogon->FwUsername() }, Reply)) break; else return false;
         case 10: if (SendCommand(command::USER(), {plogon->Username() + "@" + plogon->FwUsername() + "@" + strHostnamePort }, Reply)) break; else return false;
         case 11: if (SendCommand(command::PASS(), {plogon->Password() + "@" + plogon->FwPassword() }, Reply)) break; else return false;
         }

         if (!Reply.Code().IsPositiveCompletionReply() && !Reply.Code().IsPositiveIntermediateReply())
         {

            if (atoi(Reply.Code().Value()) == 530)
            {

               if (m_econnectiontype == connection_type_plain && Reply.Value().find_ci("ftp over tls") >= 0)
               {

                  m_econnectiontype = connection_type_tls_implicit;

                  plogon->m_bFailedBecauseOfSecurityLevelCanUpgrade = true;

                  sleep(1_s);

               }

            }

            return false;

         }

         const unsigned int uiFirstDigitOfReplyCode = ansi_to_i32(Reply.Code().Value()) / 100;
         iLogonPoint = iLogonSeq[plogon->FwType().AsEnum()][iLogonPoint + uiFirstDigitOfReplyCode - 1]; //get next command from array
         switch (iLogonPoint)
         {
         case ER: // ER means somewhat has gone wrong
         {
            ReportError("Logon failed.", __FILE__, __LINE__);
         }
         return false;
         case LO: // LO means we're fully logged on
            if (ChangeWorkingDirectory(mc_strRemoteDirectorySeparator) != FTP_OK)
               return false;
            return true;
         }
      }

//      if (m_econnectiontype == connection_type_tls_implicit)
//      {
//
//         reply Reply;
//         if (!SendCommand(command::PROT(), { "P" }, Reply))
//         {
//
//            return false;
//
//         }
//
//         if (!Reply.Code().IsPositiveCompletionReply() && !Reply.Code().IsPositiveIntermediateReply())
//         {
//
//            return false;
//
//         }
//
//
//      }
      //return false;
   }

   /// Rename a file on the FTP server.
   /// @remarks Can be used for moving the file to another directory.
   /// @lparam[in] strOldName Name of the file to rename.
   /// @lparam[in] strNewName The memory_new name for the file.
   /// @return see return values of client_socket::SimpleErrorCheck
   int client_socket::Rename(const string& strOldName, const string& strNewName)
   {
      reply Reply;
      if (!SendCommand(command::RNFR(), { strOldName }, Reply))
         return FTP_ERROR;

      if (Reply.Code().IsNegativeReply())
         return FTP_NOTOK;
      else if (!Reply.Code().IsPositiveIntermediateReply())
      {
         ASSERT(Reply.Code().IsPositiveCompletionReply() || Reply.Code().IsPositivePreliminaryReply());
         return FTP_ERROR;
      }

      if (!SendCommand(command::RNTO(), { strNewName }, Reply))
         return FTP_ERROR;

      return SimpleErrorCheck(Reply);
   }

   /// Moves a file within the FTP server.
   /// @lparam[in] strFullSourceFilePath Name of the file which should be moved.
   /// @lparam[in] strFullTargetFilePath The destination where the file should be moved to (file name must be also given).
   /// @return see return values of client_socket::SimpleErrorCheck
   int client_socket::Move(const string& strFullSourceFilePath, const string& strFullTargetFilePath)
   {
      return Rename(strFullSourceFilePath, strFullTargetFilePath);
   }

   /// Gets the directory listing of the FTP server. Sends the LIST command to
   /// the FTP server.
   /// @lparam[in] strPath Starting path for the list command.
   /// @lparam[out] vstrFileList Returns a simple list of the files and folders of the specified directory.
   /// @lparam[in] fPasv see documentation of client_socket::Passive
   bool client_socket::List(const string& strPath, string_array& vstrFileList, bool fPasv)
   {
      output_stream outputStream(mc_strEolCharacterSequence, command::LIST().AsString());
      if (!ExecuteDatachannelCommand(command::LIST(), strPath, representation(type::ASCII()), fPasv, 0, outputStream))
         return false;

      vstrFileList.clear();
      string strLine;
      outputStream.SetStartPosition();
      while (outputStream.GetNextLine(strLine))
         vstrFileList.push_back(strPath + strLine);

      return true;
   }

   /// Gets the directory listing of the FTP server. Sends the NLST command to
   /// the FTP server.
   /// @lparam[in] strPath Starting path for the list command.
   /// @lparam[out] vstrFileList Returns a simple list of the files and folders of the specified the directory.
   /// @lparam[in] fPasv see documentation of client_socket::Passive
   bool client_socket::NameList(const string& strPath, string_array& vstrFileList, bool fPasv)
   {
      output_stream outputStream(mc_strEolCharacterSequence, command::NLST().AsString());
      if (!ExecuteDatachannelCommand(command::NLST(), strPath, representation(type::ASCII()), fPasv, 0, outputStream))
         return false;

      vstrFileList.clear();
      string strLine;
      outputStream.SetStartPosition();
      while (outputStream.GetNextLine(strLine))
         vstrFileList.push_back(strPath + strLine);

      return true;
   }

   /// Gets the directory listing of the FTP server. Sends the LIST command to
   /// the FTP server.
   /// @lparam[in] strPath Starting path for the list command.
   /// @lparam[out] vFileList Returns a detailed list of the files and folders of the specified directory.
   ///                       vFileList contains file_status-Objects. These Objects provide a lot of
   ///                       information about the file/folder.
   /// @lparam[in] fPasv see documentation of client_socket::Passive
   bool client_socket::List(const string& strPath, file_status_ptra& vFileList, bool fPasv)
   {
      ASSERT(m_apFileListParser.is_set());

      output_stream outputStream(mc_strEolCharacterSequence, command::LIST().AsString());
      if (!ExecuteDatachannelCommand(command::LIST(), strPath, representation(type::ASCII()), fPasv, 0, outputStream))
         return false;

      vFileList.clear();
      string strLine;
      outputStream.SetStartPosition();
      while (outputStream.GetNextLine(strLine))
      {
         ::pointer<file_status>spFtpFileStatus(__new(file_status));
         if (m_apFileListParser->Parse(*spFtpFileStatus, strLine))
         {
            spFtpFileStatus->m_strPath = strPath;
            vFileList.push_back(spFtpFileStatus);
         }
      }

      return true;
   }

   /// Gets the directory listing of the FTP server. Sends the NLST command to
   /// the FTP server.
   /// @lparam[in] strPath Starting path for the list command.
   /// @lparam[out] vFileList Returns a simple list of the files and folders of the specified directory.
   ///                       vFileList contains file_status-Objects. Normally these Objects provide
   ///                       a lot of information about the file/folder. But the NLST-command provide
   ///                       only a simple list of the directory content (no specific information).
   /// @lparam[in] fPasv see documentation of client_socket::Passive
   bool client_socket::NameList(const string& strPath, file_status_ptra& vFileList, bool fPasv)
   {
      output_stream outputStream(mc_strEolCharacterSequence, command::NLST().AsString());
      if (!ExecuteDatachannelCommand(command::NLST(), strPath, representation(type::ASCII()), fPasv, 0, outputStream))
         return false;

      vFileList.clear();
      string strLine;
      outputStream.SetStartPosition();
      while (outputStream.GetNextLine(strLine))
      {
         ::pointer<file_status>spFtpFileStatus(__new(file_status));
         spFtpFileStatus->m_strPath = strPath;
         spFtpFileStatus->m_strName = strLine;
         vFileList.push_back(spFtpFileStatus);
      }

      return true;
   }

   /// Gets a file from the FTP server.
   /// Uses C functions for file access (very fast).
   /// @lparam[in] strRemoteFile Filename of the sourcefile on the FTP server.
   /// @lparam[in] strLocalFile Filename of the target file on the local computer.
   /// @lparam[in] repType Representation Type (see documentation of representation)
   /// @lparam[in] fPasv see documentation of client_socket::Passive
   bool client_socket::DownloadFile(const string& strRemoteFile, const string& strLocalFile, const representation& repType, bool fPasv)
   {

      ::ftp::file file;

      if (!file.Open(strLocalFile, (m_fResumeIfPossible ? ::file::e_open_no_truncate : ::file::e_open_create) | ::file::e_open_write
                     | ::file::e_open_binary | ::file::e_open_defer_create_directory))
      {
         ReportError(sys_error::GetErrorDescription(), __FILE__, __LINE__);
         return false;
      }
      file.Seek(0, ::e_seek_from_end);

      return DownloadFile(strRemoteFile, file, repType, fPasv);
   }

   /// Gets a file from the FTP server.
   /// Uses C functions for file access (very fast).
   /// @lparam[in] strRemoteFile Filename of the sourcefile on the FTP server.
   /// @lparam[in] Observer Object which receives the transfer notifications.
   /// @lparam[in] repType Representation Type (see documentation of representation)
   /// @lparam[in] fPasv see documentation of client_socket::Passive
   bool client_socket::DownloadFile(const string& strRemoteFile, itransfer_notification& Observer, const representation& repType, bool fPasv)
   {
      long lRemoteFileSize = 0;
      FileSize(strRemoteFile, lRemoteFileSize);

      for (auto * point_i32 : (observer_array &)m_setObserver)
         point_i32->OnPreReceiveFile(strRemoteFile, Observer.GetLocalStreamName(), lRemoteFileSize);

      const bool fRet = ExecuteDatachannelCommand(command::RETR(), strRemoteFile, repType, fPasv,
                        m_fResumeIfPossible ? Observer.GetLocalStreamSize() : 0, Observer);

      for (auto * point_i32 : (observer_array &)m_setObserver)
         point_i32->OnPostReceiveFile(strRemoteFile, Observer.GetLocalStreamName(), lRemoteFileSize);

      return fRet;
   }

   /// Gets a file from the FTP server.
   /// The target file is on an other FTP server (FXP).
   /// NOTICE: The file is directly transferred from one server to the other server.
   /// @lparam[in] strSourceFile File which is on the source FTP server.
   /// @lparam[in] TargetFtpServer The FTP server where the downloaded file will be stored.
   /// @lparam[in] strTargetFile Filename of the target file on the target FTP server.
   /// @lparam[in] repType Representation Type (see documentation of representation)
   /// @lparam[in] fPasv see documentation of client_socket::Passive
   bool client_socket::DownloadFile(const string& strSourceFile, client_socket& TargetFtpServer,
                                    const string& strTargetFile, const representation& repType/*=representation(type::Image())*/,
                                    bool fPasv/*=true*/)
   {
      return TransferFile(*this, strSourceFile, TargetFtpServer, strTargetFile, repType, fPasv);
   }

   /// Puts a file on the FTP server.
   /// Uses C functions for file access (very fast).
   /// @lparam[in] strLocalFile Filename of the the local sourcefile which to put on the FTP server.
   /// @lparam[in] strRemoteFile Filename of the target file on the FTP server.
   /// @lparam[in] fStoreUnique if true, the FTP command STOU is used for saving
   ///                         else the FTP command STOR is used.
   /// @lparam[in] repType Representation Type (see documentation of representation)
   /// @lparam[in] fPasv see documentation of client_socket::Passive
   bool client_socket::UploadFile(const string& strLocalFile, const string& strRemoteFile, bool fStoreUnique, const representation& repType, bool fPasv)
   {
      ::ftp::file file;
      if (!file.Open(strLocalFile, ::file::e_open_read | ::file::e_open_binary))
      {
         ReportError(sys_error::GetErrorDescription(), __FILE__, __LINE__);
         return false;
      }

      return UploadFile(file, strRemoteFile, fStoreUnique, repType, fPasv);
   }

   /// Puts a file on the FTP server.
   /// Uses C functions for file access (very fast).
   /// @lparam[in] Observer Object which receives the transfer notifications for upload requests.
   /// @lparam[in] strRemoteFile Filename of the target file on the FTP server.
   /// @lparam[in] fStoreUnique if true, the FTP command STOU is used for saving
   ///                         else the FTP command STOR is used.
   /// @lparam[in] repType Representation Type (see documentation of representation)
   /// @lparam[in] fPasv see documentation of client_socket::Passive
   bool client_socket::UploadFile(itransfer_notification& Observer, const string& strRemoteFile, bool fStoreUnique, const representation& repType, bool fPasv)
   {
      long lRemoteFileSize = 0;
      if (m_fResumeIfPossible)
         FileSize(strRemoteFile, lRemoteFileSize);

      command cmd(command::STOR());
      if (lRemoteFileSize > 0)
         cmd = command::APPE();
      else if (fStoreUnique)
         cmd = command::STOU();

      const long lLocalFileSize = Observer.GetLocalStreamSize();
      Observer.SetLocalStreamOffset((unsigned int) lRemoteFileSize);

      for (auto * point_i32 : (observer_array &)m_setObserver)
         point_i32->OnPreSendFile(Observer.GetLocalStreamName(), strRemoteFile, lLocalFileSize);

      const bool fRet = ExecuteDatachannelCommand(cmd, strRemoteFile, repType, fPasv, 0, Observer);

      for (auto * point_i32 : (observer_array &)m_setObserver)
         point_i32->OnPostSendFile(Observer.GetLocalStreamName(), strRemoteFile, lLocalFileSize);

      return fRet;
   }

   /// Puts a file on the FTP server.
   /// The source file is on an other FTP server (FXP).
   /// NOTICE: The file is directly transferred from one server to the other server.
   /// @lparam[in] SourceFtpServer A FTP server from which the file is taken for upload ptopic->
   /// @lparam[in] strSourceFile File which is on the source FTP server.
   /// @lparam[in] strTargetFile Filename of the target file on the FTP server.
   /// @lparam[in] repType Representation Type (see documentation of representation)
   /// @lparam[in] fPasv see documentation of client_socket::Passive
   bool client_socket::UploadFile(client_socket& SourceFtpServer, const string& strSourceFile,
                                  const string& strTargetFile, const representation& repType/*=representation(type::Image())*/,
                                  bool fPasv/*=true*/)
   {
      return TransferFile(SourceFtpServer, strSourceFile, *this, strTargetFile, repType, !fPasv);
   }

   /// Transfers a file from a FTP server to another FTP server.
   /// The source file is on an other FTP server (FXP).
   /// NOTICE: The file is directly transferred from one server to the other server.
   /// @lparam[in] SourceFtpServer A FTP server from which the file which is copied.
   /// @lparam[in] strSourceFile Name of the file which is on the source FTP server.
   /// @lparam[in] TargetFtpServer A FTP server to which the file is copied.
   /// @lparam[in] strTargetFile Name of the file on the target FTP server.
   /// @lparam[in] repType Representation Type (see documentation of representation)
   /// @lparam[in] fPasv see documentation of client_socket::Passive
   /*static*/ bool client_socket::TransferFile(client_socket& SourceFtpServer, const string& strSourceFile,
         client_socket& TargetFtpServer, const string& strTargetFile,
         const representation& repType/*=representation(type::Image())*/,
         bool fSourcePasv/*=false*/)
   {
      // transmit representation to server
      if (SourceFtpServer.RepresentationType(repType) != FTP_OK)
         return false;

      if (TargetFtpServer.RepresentationType(repType) != FTP_OK)
         return false;

      client_socket& PassiveServer = fSourcePasv ? SourceFtpServer : TargetFtpServer;
      client_socket& ActiveServer = fSourcePasv ? TargetFtpServer : SourceFtpServer;

      // set one FTP server in passive mode
      // the FTP server opens a port and tell us the socket (ip ::networking::address + port)
      // this socket is used for opening the data connection
      ::u32  ulIP = 0;
      ::u16 ushSock = 0;
      if (PassiveServer.Passive(ulIP, ushSock) != FTP_OK)
      {

         return false;

      }

      auto paddress = SourceFtpServer.acmesystem()->m_papexsystem->networking()->create_ip4_address((i32)ulIP, ushSock);

      // transmit the socket (ip ::networking::address + port) of the first FTP server to the
      // second server
      // the second FTP server establishes then the data connection to the first
      if (ActiveServer.DataPort(paddress->get_display_number(), ushSock) != FTP_OK)
         return false;

      if (!SourceFtpServer.SendCommand(command::RETR(), { strSourceFile }))
         return false;

      reply ReplyTarget;
      if (!TargetFtpServer.SendCommand(command::STOR(), { strTargetFile }, ReplyTarget) ||
            !ReplyTarget.Code().IsPositivePreliminaryReply())
         return false;

      reply ReplySource;
      if (!SourceFtpServer.GetResponse(ReplySource) || !ReplySource.Code().IsPositivePreliminaryReply())
         return false;

      // get response from FTP servers
      if (!SourceFtpServer.GetResponse(ReplySource) || !ReplySource.Code().IsPositiveCompletionReply() ||
            !TargetFtpServer.GetResponse(ReplyTarget) || !ReplyTarget.Code().IsPositiveCompletionReply())
         return false;

      return true;
   }

   /// Executes a commando that result in a communication over the data port.
   /// @lparam[in] crDatachannelCmd Command to be executeted.
   /// @lparam[in] strPath Parameter for the command usually a path.
   /// @lparam[in] representation see documentation of client_socket::representation
   /// @lparam[in] fPasv see documentation of client_socket::Passive
   /// @lparam[in] dwByteOffset Server marker at which file transfer is to be restarted.
   /// @lparam[in] Observer Object for observing the execution of the command.
   bool client_socket::ExecuteDatachannelCommand(const command& crDatachannelCmd, const string& strPath, const representation& representation,
         bool fPasv, ::u32 dwByteOffset, itransfer_notification& Observer)
   {
      if (!crDatachannelCmd.IsDatachannelCommand())
      {
         ASSERT(false);
         return false;
      }

      if (m_fTransferInProgress)
         return false;

      if (!_is_connected())
         return false;

      // transmit representation to server
      if (RepresentationType(representation) != FTP_OK)
         return false;

      bool fTransferOK = false;

      ::pointer<::sockets::base_socket>pbasesocket;

      ::pointer<::sockets::base_socket>pbasesocket2;

      if (fPasv)
      {

         ::pointer<::sockets::transfer_socket>apSckDataConnection;

         if (crDatachannelCmd.IsDatachannelWriteCommand())
         {

            apSckDataConnection = memory_new ::sockets::write_socket();

         }
         else if (crDatachannelCmd.IsDatachannelReadCommand())
         {

            apSckDataConnection = memory_new ::sockets::read_socket();

         }
         else
         {

            return false;

         }

         pbasesocket = apSckDataConnection;

         if (!OpenPassiveDataConnection(*apSckDataConnection, crDatachannelCmd, strPath, dwByteOffset))
            return false;

         fTransferOK = TransferData(crDatachannelCmd, Observer, *apSckDataConnection);

         apSckDataConnection->SetCloseAndDelete();

      }
      else
      {

         ::pointer<::sockets::listen_socket_base>apSckDataConnection;

         if (crDatachannelCmd.IsDatachannelWriteCommand())
         {

            apSckDataConnection = memory_new ::sockets::listen_socket < ::sockets::write_socket >();

         }
         else if (crDatachannelCmd.IsDatachannelReadCommand())
         {

            apSckDataConnection = memory_new ::sockets::listen_socket < ::sockets::read_socket >();

         }
         else
         {

            return false;

         }

         pbasesocket2 = apSckDataConnection;

         pbasesocket2->initialize_socket(socket_handler());

         if (!OpenActiveDataConnection(*apSckDataConnection, crDatachannelCmd, strPath, dwByteOffset))
            return false;

         ::pointer<::sockets::transfer_socket>psocket = apSckDataConnection->m_pbasesocket;

         pbasesocket = psocket;

         fTransferOK = TransferData(crDatachannelCmd, Observer, *psocket);

         if (_is_connected())
         {

            psocket->close();

         }

      }

      //::u32 tickStart= ::duration::now();

      //::u32 nSeconds = 10;

      //if (pbasesocket.is_set() && !pbasesocket->IsDetached())
      //{

      //   try
      //   {

      //      while (pbasesocket->socket_handler()->contains(pbasesocket) && tickStart.elapsed() < nSeconds * 1000)
      //      {

      //         pbasesocket->socket_handler()->select(0, 100 * 1000);

      //      }

      //   }
      //   catch (...)
      //   {

      //   }

      //}

      //if (pbasesocket2.is_set() && !pbasesocket2->IsDetached())
      //{

      //   try
      //   {

      //      while (pbasesocket2->socket_handler()->contains(pbasesocket2) && tickStart.elapsed() < nSeconds * 1000)
      //      {

      //         pbasesocket2->socket_handler()->select(0, 100 * 1000);

      //      }

      //   }
      //   catch (...)
      //   {

      //   }

      //}

      // get response from FTP server
      reply Reply;
      if (!fTransferOK || !GetResponse(Reply) || !Reply.Code().IsPositiveCompletionReply())
         return false;

      return true;

   }


   /// Executes a commando that result in a communication over the data port.
   /// @lparam[in] crDatachannelCmd Command to be executeted.
   /// @lparam[in] Observer Object for observing the execution of the command.
   /// @lparam[in] sckDataConnection Socket which is used for sending/receiving data.
   bool client_socket::TransferData(const command& crDatachannelCmd, itransfer_notification& Observer, ::sockets::transfer_socket & sckDataConnection)
   {

      if (crDatachannelCmd.IsDatachannelWriteCommand())
      {
         if (!SendData(Observer, sckDataConnection))
            return false;
      }
      else if (crDatachannelCmd.IsDatachannelReadCommand())
      {
         if (!ReceiveData(Observer, sckDataConnection))
            return false;
      }
      else
      {
         ASSERT(false);
         return false;
      }
      return true;
   }

   /// Opens an active data connection.
   /// @lparam[out] sckDataConnection
   /// @lparam[in] crDatachannelCmd Command to be executeted.
   /// @lparam[in] strPath Parameter for the command usually a path.
   /// @lparam[in] dwByteOffset Server marker at which file transfer is to be restarted.
   bool client_socket::OpenActiveDataConnection(::sockets::socket & sckDataConnectionParam, const command& crDatachannelCmd, const string& strPath, ::u32 dwByteOffset)
   {
      if (!crDatachannelCmd.IsDatachannelCommand())
      {
         ASSERT(false);
         return false;
      }


      ::sockets::listen_socket_base & sckDataConnection
         = *(dynamic_cast < ::sockets::listen_socket_base * >(&sckDataConnectionParam));

      //ll.m_strCat = m_strCat;
      //ll.m_strCipherList = m_strCipherList;

      sckDataConnection.set_should_detach(true);
      //m_strIp = "127.0.0.1";
      //if (m_iPort == 443)
      //{
      //   ll.EnableSSL();
      //}
      // INADDR_ANY = ip ::networking::address of localhost
      // second parameter "0" means that the WINSOCKAPI ask for a port
      string strIp = "127.0.0.1";
      int iPort = 0;
      if (sckDataConnection.Bind(nullptr, "tcp", 1))
      {
         string strMessage;
         strMessage.format("could not bind to address %s %d", strIp.c_str(), iPort);
         TRACE(strMessage);
         //message_box(nullptr, strMessage);
         return false;
      }

      socket_handler()->add(&sckDataConnection);

      ::u16 ushLocalSock = 0;

      try
      {
         // INADDR_ANY = ip ::networking::address of localhost
         // second parameter "0" means that the WINSOCKAPI ask for a port
         //::networking::address csaAddressTemp(INADDR_ANY, 0);
         //apSckServer->create(SOCK_STREAM);
         //apSckServer->bind(csaAddressTemp);
         //apSckServer->get_socket_address(csaAddressTemp);
         //ushLocalSock = csaAddressTemp.Port();
         //apSckServer->listen();
      }
      catch (::sockets::transfer_socket_exception& blockingException)
      {
         ReportError(blockingException.get_message(), __FILE__, __LINE__);
         sckDataConnection.SetCloseAndDelete();
         return false;
      }

      ::networking::address_pointer paddressTemp;
      //auto paddress = acmesystem()->m_papexsystem->networking()->create_address((i32)ulIP, ushSock);
      //::networking::address csaAddressTemp(INADDR_ANY, 0);
      paddressTemp = sckDataConnection.get_socket_address();
      ushLocalSock = paddressTemp->get_service_number();


      // get own ip ::networking::address
      ::networking::address_pointer paddressLocal;
      paddressLocal = get_socket_address();

      // transmit the socket (ip ::networking::address + port) to the server
      // the FTP server establishes then the data connection
      if (DataPort(paddressLocal->get_display_number(), ushLocalSock) != FTP_OK)
         return false;

      // if resuming is activated then set offset
      if (m_fResumeIfPossible &&
            (crDatachannelCmd == command::STOR() || crDatachannelCmd == command::RETR() || crDatachannelCmd == command::APPE()) &&
            (dwByteOffset != 0 && Restart(dwByteOffset) != FTP_OK))
         return false;

      // send FTP command RETR/STOR/NLST/LIST to the server
      reply Reply;
      if (!SendCommand(crDatachannelCmd, { strPath }, Reply) ||
            !Reply.Code().IsPositivePreliminaryReply())
         return false;

      while (sckDataConnection.m_pbasesocket == nullptr)
      {

         socket_handler()->select(1, 0);

      }

      return sckDataConnection.m_pbasesocket != nullptr;

   }

   /// Opens a passive data connection.
   /// @lparam[out] sckDataConnection
   /// @lparam[in] crDatachannelCmd Command to be executeted.
   /// @lparam[in] strPath Parameter for the command usually a path.
   /// @lparam[in] dwByteOffset Server marker at which file transfer is to be restarted.
   bool client_socket::OpenPassiveDataConnection(::sockets::socket & sckDataConnectionParam, const command& crDatachannelCmd, const string& strPath, ::u32 dwByteOffset)
   {

      if (m_econnectiontype == connection_type_tls_implicit)
      {
         reply Reply;
         if (!SendCommand(command::PROT(), { "P" }, Reply))
            return false;

         if (!Reply.Code().IsPositiveCompletionReply())
            return false;


      }

      if (!crDatachannelCmd.IsDatachannelCommand())
      {
         ASSERT(false);
         return false;
      }
      ::sockets::transfer_socket & sckDataConnection
         = *(dynamic_cast < ::sockets::transfer_socket * >(&sckDataConnectionParam));

      ::u32   ulRemoteHostIP = 0;
      ::u16  ushServerSock = 0;

      if (m_econnectiontype == connection_type_tls_implicit)
      {

         sckDataConnection.EnableSSL();

      }

      // set passive mode
      // the FTP server opens a port and tell us the socket (ip ::networking::address + port)
      // this socket is used for opening the data connection
      if (Passive(ulRemoteHostIP, ushServerSock) != FTP_OK)
         return false;

      // establish connection
      auto paddressTemp = networking()->create_ip4_address((i32)ulRemoteHostIP, ushServerSock);
      try
      {
         if (!sckDataConnection.open(paddressTemp))
         {
            return false;
         }

      }
      catch (::sockets::transfer_socket_exception& blockingException)
      {
         ReportError(blockingException.get_message(), __FILE__, __LINE__);
         sckDataConnection.SetCloseAndDelete();
         return false;
      }

      socket_handler()->add(&sckDataConnection);

      // if resuming is activated then set offset
      if (m_fResumeIfPossible &&
            (crDatachannelCmd == command::STOR() || crDatachannelCmd == command::RETR() || crDatachannelCmd == command::APPE()) &&
            (dwByteOffset != 0 && Restart(dwByteOffset) != FTP_OK))
         return false;


      // send FTP command RETR/STOR/NLST/LIST to the server
      reply Reply;
      if (!SendCommand(crDatachannelCmd, { strPath }, Reply) ||
            !Reply.Code().IsPositivePreliminaryReply())
         return false;

      return true;
   }

   /// Sends data over a socket to the server.
   /// @lparam[in] Observer Object for observing the execution of the command.
   /// @lparam[in] sckDataConnection Socket which is used for the send ptopic->
   bool client_socket::SendData(itransfer_notification& Observer, ::sockets::transfer_socket & sckDataConnection)
   {
      try
      {

         ((client_socket *) this)->m_fTransferInProgress = true;

         int iNumWrite = 0;

         memsize bytesRead = 0;

         Observer.OnPreBytesSend(m_vBuffer.get_data(), (memsize) m_vBuffer.size(), bytesRead);
auto tickStart = ::duration::now();

         while (true)
         {

            if (bytesRead <= 0)
            {

               break;

            }

            if (tickStart.elapsed() > m_durationTimeout)
            {

               break;

            }

            {

               synchronous_lock synchronouslock(sckDataConnection.synchronization());

               sckDataConnection.write(m_vBuffer.get_data(), static_cast<int>(m_vBuffer.size()));

            }


            for (auto * point_i32 : (observer_array &)m_setObserver)
            {

               point_i32->OnBytesSent(m_vBuffer, iNumWrite);

            }

            Observer.OnPreBytesSend(m_vBuffer.get_data(), (memsize)m_vBuffer.size(), bytesRead);
//auto tickStart = ::duration::now();

         }

         ((client_socket *) this)->m_fTransferInProgress = false;

         if (m_fAbortTransfer)
         {

            _abort();

            return false;

         }

      }
      catch (::sockets::transfer_socket_exception& blockingException)
      {

         ((client_socket *) this)->m_fTransferInProgress = false;

         ReportError(blockingException.get_message(), __FILE__, __LINE__);

         sckDataConnection.SetCloseAndDelete();

         return false;

      }

      return true;

   }


   /// Receives data over a socket from the server.
   /// @lparam[in] Observer Object for observing the execution of the command.
   /// @lparam[in] sckDataConnection Socket which is used for receiving the data.
   bool client_socket::ReceiveData(itransfer_notification& Observer, ::sockets::transfer_socket& sckDataConnection)
   {

      try
      {

         ((client_socket *) this)->m_fTransferInProgress = true;

         for (auto * point_i32 : (observer_array &)m_setObserver)
         {

            point_i32->OnBeginReceivingData();

         }

         memsize iNumRead;

         memsize lTotalBytes = 0;
auto tickStart = ::duration::now();

         while (true)
         {

            if (m_fAbortTransfer)
            {

               break;

            }

            if (tickStart.elapsed() > m_durationTimeout)
            {

               break;

            }

            {

               synchronous_lock synchronouslock(this->synchronization());

               iNumRead = sckDataConnection.m_pmemoryfile->erase_begin(m_vBuffer.get_data(), static_cast<int>(m_vBuffer.size()));

               if (!sckDataConnection.is_valid() && iNumRead <= 0)
               {

                  break;

               }

            }

            if (iNumRead > 0)
            {

               lTotalBytes += iNumRead;

               for (auto * point_i32 : (observer_array &)m_setObserver)
               {

                  point_i32->OnBytesReceived(m_vBuffer, (long) iNumRead);

               }

               Observer.OnBytesReceived(m_vBuffer, (long) iNumRead);

            }
            else
            {

               sleep(100_ms);

            }
//auto tickStart = ::duration::now();

         }

         for (auto * point_i32 : (observer_array &)m_setObserver)
         {

            point_i32->OnEndReceivingData((long) lTotalBytes);

         }

         ((client_socket *) this)->m_fTransferInProgress = false;

         if (m_fAbortTransfer)
         {

            _abort();

            return false;

         }

      }
      catch (::sockets::transfer_socket_exception& blockingException)
      {

         ((client_socket *) this)->m_fTransferInProgress = false;

         ReportError(blockingException.get_message(), __FILE__, __LINE__);

         sckDataConnection.SetCloseAndDelete();

         return false;

      }

      return true;

   }


   /// Sends a command to the server.
   /// @lparam[in] Command Command to send.
   bool client_socket::SendCommand(const command& Command, const string_array & Arguments)
   {

      if (!_is_connected())
      {

         return false;

      }

      try
      {
         for (auto * point_i32 : (observer_array &)m_setObserver)
            point_i32->OnSendCommand(Command, Arguments);
         const string strCommand = Command.AsString(Arguments) + "\r\n";
         //write(strCommand, static_cast<int>(strCommand.length()), mc_uiTimeout);
         write(strCommand, static_cast<int>(strCommand.length()));
      }
      catch (::sockets::transfer_socket_exception& blockingException)
      {
         ReportError(blockingException.get_message(), __FILE__, __LINE__);
         const_cast<client_socket*>(this)->SetCloseAndDelete();
         return false;
      }
      sleep(200_ms);
      return true;
   }

   /// Sends a command to the server.
   /// @lparam[in]  Command Command to send.
   /// @lparam[out] Reply The Reply of the server to the sent command.
   bool client_socket::SendCommand(const command& Command, const string_array & Arguments, reply& Reply)
   {
      if (!SendCommand(Command, Arguments))
      {
         return false;
      }
      if(!GetResponse(Reply))
         return false;
      return true;
   }

   /// This function gets the server response.
   /// A server response can exists of more than one line. This function
   /// returns the full response (multiline).
   /// @lparam[out] Reply Reply of the server to a command.
   bool client_socket::GetResponse(reply& Reply)
   {
      string strResponse;
      if (!GetSingleResponseLine(strResponse))
         return false;

      if (strResponse.length() > 3 && strResponse[3] == '-')
      {
         string strSingleLine(strResponse);
         const int iRetCode = atoi(strResponse);
         // handle multi-line server responses
         while (!(strSingleLine.length() > 3 &&
                  strSingleLine[3] == ' ') &&
                  ansi_to_i32(strSingleLine) == iRetCode)
         {
            if (!GetSingleResponseLine(strSingleLine))
               return false;
            strResponse += mc_strEolCharacterSequence + strSingleLine;
         }
      }

      bool fRet = Reply.Set(strResponse);

      for (auto * point_i32 : (observer_array &)m_setObserver)
         point_i32->OnResponse(Reply);

      return fRet;
   }

   void client_socket::OnLine(const ::string & strLine)
   {

      single_lock synchronouslock(this->synchronization());

      m_qResponseBuffer.add_tail(strLine);

   }


   /// Reads a single response line from the server control channel.
   /// @lparam[out] strResponse Response of the server as string.
   bool client_socket::GetSingleResponseLine(string& strResponse)
   {

      if (!_is_connected())
         return false;

      try
      {

         auto tickStart = ::duration::now();

         // xxx yyy zzz
         //while (tickStart.elapsed() < 10 * 1000)
         while (tickStart.elapsed() < 10_s)
         {

            {

               single_lock synchronouslock(this->synchronization());

               if (m_qResponseBuffer.has_elements())
               {

                  break;

               }

            }

            if (IsDetached())
            {

               sleep(100_ms);

            }
            else
            {

               socket_handler()->select(1, 0);

               if (IsSSL())
               {

                  //sleep(200_ms);

               }

            }

            //// internal buffer is empty ==> get response from FTP server
            //int iNum = 0;
            //std::string strTemp;

            //do
            //{
            //   iNum = receive(m_vBuffer.get_data(), static_cast<int>(m_vBuffer.size()) - 1, mc_uiTimeout);
            //   if (mc_uiResponseWait != 0)
            //      sleep(mc_uiResponseWait);
            //   ((memory &)m_vBuffer)[iNum] = '\0';
            //   strTemp += m_vBuffer.to_string();
            //} while (iNum == static_cast<int>(m_vBuffer.size()) - 1);

            //// each line in response is a separate entry in the internal buffer
            //while (strTemp.length())
            //{
            //   memsize iCRLF = strTemp.find('\n');
            //   if (iCRLF != std::string::npos)
            //   {
            //      m_qResponseBuffer.add_tail(strTemp.substr(0, iCRLF + 1));
            //      strTemp.erase(0, iCRLF + 1);
            //   }
            //   else
            //   {
            //      // this is not rfc standard; normally each command must end with CRLF
            //      // in this case it doesn't
            //      m_qResponseBuffer.add_tail(strTemp);
            //      strTemp.clear();
            //   }
            //}

            //if (m_qResponseBuffer.is_empty())
            //   return false;
         }

         if (m_qResponseBuffer.is_empty())
         {

            return false;

         }

         // get first response-line from buffer
         {

            single_lock synchronouslock(this->synchronization());

            strResponse = m_qResponseBuffer.pick_head();

         }

         // erase CrLf if exists (don't use mc_strEolCharacterSequence here)
         strResponse.trim_right();

      }
      catch (::sockets::transfer_socket_exception& blockingException)
      {
         ReportError(blockingException.get_message(), __FILE__, __LINE__);
         const_cast<client_socket*>(this)->SetCloseAndDelete();
         return false;
      }

      return true;
   }

   /// Executes the FTP command CDUP (change to parent directory).
   /// This command is a special case of client_socket::ChangeWorkingDirectory
   /// (CWD), and is  included to simplify the implementation of programs for
   /// transferring directory trees between operating systems having different
   /// syntaxes for naming the parent directory.
   /// @return see return values of client_socket::SimpleErrorCheck
   int client_socket::ChangeToParentDirectory()
   {
      reply Reply;
      if (!SendCommand(command::CDUP(), {}, Reply))
         return FTP_ERROR;
      return SimpleErrorCheck(Reply);
   }

   /// Executes the FTP command QUIT.
   /// This command terminates a USER and if file transfer is not in progress,
   /// the server closes the control connection. If file transfer is in progress,
   /// the connection will remain open for result response and the server will
   /// then close it.
   /// If the user-process is transferring files for several USERs but does not
   /// wish to close and then reopen connections for each, then the REIN command
   /// should be used instead of QUIT.
   /// An unexpected close on the control connection will cause the server to take
   /// the effective action of an abort (ABOR) and a logout.
   /// @return see return values of client_socket::SimpleErrorCheck
   int client_socket::Logout()
   {
      reply Reply;
      if (!SendCommand(command::QUIT(), {}, Reply))
         return FTP_ERROR;

      CloseControlChannel();

      return SimpleErrorCheck(Reply);
   }

   /// Executes the FTP command PASV. Set the passive mode.
   /// This command requests the server-DTP (data transfer process) on a data to
   /// "listen"  port (which is not its default data port) and to wait for a
   /// connection rather than initiate one upon receipt of a transfer command.
   /// The response to this command includes the host and port ::networking::address this
   /// server is listening on.
   /// @lparam[out] ulIpAddress IP ::networking::address the server is listening on.
   /// @lparam[out] ushPort Port the server is listening on.
   /// @return see return values of client_socket::SimpleErrorCheck
   int client_socket::Passive(::u32& ulIpAddress, ::u16& ushPort)
   {
      reply Reply;
      if (!SendCommand(command::PASV(), {}, Reply))
         return FTP_ERROR;

      if (Reply.Code().IsPositiveCompletionReply())
      {
         if (!GetIpAddressFromResponse(Reply.Value(), ulIpAddress, ushPort))
            return FTP_ERROR;
      }

      return SimpleErrorCheck(Reply);
   }

   /// Parses a response string and extracts the ip ::networking::address and port information.
   /// @lparam[in]  strResponse The response string of a FTP server which holds
   ///                         the ip ::networking::address and port information.
   /// @lparam[out] ulIpAddress Buffer for the ip ::networking::address.
   /// @lparam[out] ushPort     Buffer for the port information.
   /// @retval true  Everything went ok.
   /// @retval false An error occurred (invalid format).
   bool client_socket::GetIpAddressFromResponse(const string& strResponse, ::u32& ulIpAddress, ::u16& ushPort)
   {
      // parsing of ip-::networking::address and port implemented with a finite state machine
      // ...(192,168,1,1,3,44)...
      enum T_enState { state0, state1, state2, state3, state4 } enState = state0;

      string strIpAddress, strPort;
      ::u16 ushTempPort = 0;
      ::u32  ulTempIpAddress = 0;
      int iCommaCnt = 4;
      for (strsize i = 0; i < strResponse.get_length(); i++)
      {
         char it = strResponse[i];
         switch (enState)
         {
         case state0:
            if (it == '(')
               enState = state1;
            break;
         case state1:
            if (it == ',')
            {
               if (--iCommaCnt == 0)
               {
                  enState = state2;
                  ulTempIpAddress += atoi(strIpAddress);
               }
               else
               {
                  ulTempIpAddress += atoi(strIpAddress) << 8 * iCommaCnt;
                  strIpAddress.clear();
               }
            }
            else
            {
               if (!ansi_char_isdigit(it))
                  return false;
               strIpAddress += it;
            }
            break;
         case state2:
            if (it == ',')
            {
               ushTempPort = static_cast<::u16>(atoi(strPort) << 8);
               strPort.clear();
               enState = state3;
            }
            else
            {
               if (!ansi_char_isdigit(it))
                  return false;
               strPort += it;
            }
            break;
         case state3:
            if (it == ')')
            {
               // compiler warning if using +=operator
               ushTempPort = ushTempPort + static_cast<::u16>(atoi(strPort));
               enState = state4;
            }
            else
            {
               if (!ansi_char_isdigit(it))
                  return false;
               strPort += it;
            }
            break;
         case state4:
            break; // some compilers complain if not all enumeration values are listet
         }
      }

      if (enState == state4)
      {
         ulIpAddress = ulTempIpAddress;
         ushPort = ushTempPort;
      }

      return enState == state4;
   }

   /// Executes the FTP command ABOR.
   /// This command tells the server to abort the previous FTP service command
   /// and any associated transfer of data.  The abort command may require
   /// "special action", as discussed in the Section on FTP Commands, to force
   /// recognition by the server. No action is to be taken if the previous
   /// command has been completed (including data transfer). The control
   /// connection is not to be closed by the server, but the data connection
   /// must be closed.
   /// There are two cases for the server upon receipt of this command:<BR>
   /// (1) the FTP service command was already completed, or <BR>
   /// (2) the FTP service command is still in progress.<BR>
   /// In the first case, the server closes the data connection (if it is open)
   /// and responds with a 226 reply, indicating that the abort command was
   /// successfully processed.
   /// In the second case, the server aborts the FTP service in progress and
   /// closes the data connection, returning a 426 reply to indicate that the
   /// service request terminated abnormally. The server then sends a 226 reply,
   /// indicating that the abort command was successfully processed.
   /// @return see return values of client_socket::SimpleErrorCheck
   int client_socket::_abort()
   {
      if (m_fTransferInProgress)
      {
         m_fAbortTransfer = true;
         return FTP_OK;
      }

      m_fAbortTransfer = false;
      reply Reply;
      if (!SendCommand(command::ABOR(), {}, Reply))
         return FTP_ERROR;
      return SimpleErrorCheck(Reply);
   }

   /// Executes the FTP command PWD (PRINT WORKING DIRECTORY)
   /// This command causes the name of the current working directory
   /// to be returned in the reply.
   int client_socket::PrintWorkingDirectory()
   {
      reply Reply;
      if (!SendCommand(command::PWD(), {}, Reply))
         return FTP_ERROR;
      return SimpleErrorCheck(Reply);
   }

   /// Executes the FTP command SYST (SYSTEM)
   /// This command is used to find out the type of operating system at the server.
   /// The reply shall have as its first word one of the system names listed in the
   /// current version of the Assigned Numbers document [Reynolds, Joyce, and
   /// Jon Postel, "Assigned Numbers", RFC 943, ISI, April 1985.].
   /// @return see return values of client_socket::SimpleErrorCheck
   int client_socket::system()
   {
      reply Reply;
      if (!SendCommand(command::SYST(), {}, Reply))
         return FTP_ERROR;
      return SimpleErrorCheck(Reply);
   }

   /// Executes the FTP command NOOP
   /// This command does not affect any parameters or previously entered commands.
   /// It specifies no action other than that the server send an FTP_OK reply.
   /// @return see return values of client_socket::SimpleErrorCheck
   int client_socket::Noop()
   {
      reply Reply;
      if (!SendCommand(command::NOOP(), {}, Reply))
         return FTP_ERROR;
      return SimpleErrorCheck(Reply);
   }

   /// Executes the FTP command PORT (DATA PORT)
   /// The argument is a HOST-PORT specification for the data port to be used in data
   /// connection. There are defaults for both the user and server data ports, and
   /// under normal circumstances this command and its reply are not needed.  If
   /// this command is used, the argument is the concatenation of a 32-bit internet
   /// host ::networking::address and a 16-bit TCP port ::networking::address.
   /// @lparam[in] strHostIP IP-::networking::address like xxx.xxx.xxx.xxx
   /// @lparam[in] uiPort 16-bit TCP port ::networking::address.
   /// @return see return values of client_socket::SimpleErrorCheck
   int client_socket::DataPort(const string& strHostIP, ::u16 ushPort)
   {
      string strPortArguments;
      // convert the port number to 2 bytes + add to the local IP
      strPortArguments = strHostIP + "," + __string (ushPort >> 8) + "," + __string (ushPort & 0xFF);

      strPortArguments.find_replace(".", ",");

      reply Reply;
      if (!SendCommand(command::PORT(), { strPortArguments } , Reply))
         return FTP_ERROR;
      return SimpleErrorCheck(Reply);
   }

   /// Executes the FTP command TYPE (REPRESENTATION TYPE)
   /// Caches the representation state if successful.
   /// see Documentation of nsFTP::representation
   /// @lparam[in] representation see Documentation of nsFTP::representation
   /// @lparam[in] iSize Indicates Bytesize for type LocalByte.
   /// @return see return values of client_socket::SimpleErrorCheck
   int client_socket::RepresentationType(const representation& representation, ::u32 dwSize)
   {
      // check representation
      if (m_apCurrentRepresentation.is_set() && representation == *m_apCurrentRepresentation)
         return FTP_OK;

      const int iRet = _RepresentationType(representation, dwSize);

      if (iRet == FTP_OK)
      {
         if (m_apCurrentRepresentation.is_null())
            m_apCurrentRepresentation = __new(::ftp::representation(representation));
         else
            *m_apCurrentRepresentation = representation;
      }
      else
         m_apCurrentRepresentation.release();

      return iRet;
   }

   /// Executes the FTP command TYPE (REPRESENTATION TYPE)
   /// see Documentation of nsFTP::representation
   /// @lparam[in] representation see Documentation of nsFTP::representation
   /// @lparam[in] dwSize Indicates Bytesize for type LocalByte.
   /// @return see return values of client_socket::SimpleErrorCheck
   int client_socket::_RepresentationType(const representation& representation, ::u32 dwSize)
   {
      string_array Arguments({ representation.Type().AsString() });

      switch (representation.Type().AsEnum())
      {
      case type::tyLocalByte:
         Arguments.add(__string((u32) dwSize));
         break;
      case type::tyASCII:
      case type::tyEBCDIC:
      case type::tyImage:
         if (representation.Format().IsValid())
            Arguments.push_back(representation.Format().AsString());
      }

      reply Reply;
      if (!SendCommand(command::TYPE(), Arguments, Reply))
         return FTP_ERROR;
      return SimpleErrorCheck(Reply);
   }

   /// Executes the FTP command CWD (CHANGE WORKING DIRECTORY)
   /// This command allows the user to work with a different directory or dataset
   /// for file storage or retrieval without altering his login or accounting
   /// information. Transfer parameters are similarly unchanged.
   /// @lparam[in] strDirectory Pathname specifying a directory or other system
   ///                         dependent file group designator.
   /// @return see return values of client_socket::SimpleErrorCheck
   int client_socket::ChangeWorkingDirectory(const string& strDirectory)
   {
      ASSERT(strDirectory.has_char());
      reply Reply;
      if (!SendCommand(command::CWD(), { strDirectory }, Reply))
         return FTP_ERROR;
      return SimpleErrorCheck(Reply);
   }

   /// Executes the FTP command MKD (MAKE DIRECTORY)
   /// This command causes the directory specified in the pathname to be created
   /// as a directory (if the pathname is absolute) or as a subdirectory of the
   /// current working directory (if the pathname is relative).
   /// @pararm[in] strDirectory Pathname specifying a directory to be created.
   /// @return see return values of client_socket::SimpleErrorCheck
   int client_socket::MakeDirectory(const string& strDirectory)
   {
      ASSERT(strDirectory.has_char());
      reply Reply;
      if (!SendCommand(command::MKD(), { strDirectory } , Reply))
         return FTP_ERROR;
      return SimpleErrorCheck(Reply);
   }

   /// Executes the FTP command SITE (SITE PARAMETERS)
   /// This command is used by the server to provide services specific to his
   /// system that are essential to file transfer but not sufficiently universal
   /// to be included as commands in the protocol.  The nature of these services
   /// and the specification of their syntax can be stated in a reply to the HELP
   /// SITE command.
   /// @lparam[in] strCmd Command to be executed.
   /// @return see return values of client_socket::SimpleErrorCheck
   int client_socket::SiteParameters(const string& strCmd)
   {
      ASSERT(strCmd.has_char());
      reply Reply;
      if (!SendCommand(command::SITE(), { strCmd }, Reply))
         return FTP_ERROR;
      return SimpleErrorCheck(Reply);
   }

   /// Executes the FTP command HELP
   /// This command shall cause the server to send helpful information regarding
   /// its implementation status over the control connection to the user.
   /// The command may take an argument (e.g., any command name) and return more
   /// specific information as a response.  The reply is type 211 or 214.
   /// It is suggested that HELP be allowed before entering a USER command. The
   /// server may use this reply to specify site-dependent parameters, e.g., in
   /// response to HELP SITE.
   /// @lparam[in] strTopic Topic of the requested help.
   /// @return see return values of client_socket::SimpleErrorCheck
   int client_socket::Help(const string& strTopic)
   {
      reply Reply;
      if (!SendCommand(command::HELP(), { strTopic }, Reply))
         return FTP_ERROR;
      return SimpleErrorCheck(Reply);
   }

   /// Executes the FTP command DELE (DELETE)
   /// This command causes the file specified in the pathname to be deleted at the
   /// server site.  If an extra level of protection is desired (such as the query,
   /// "Do you really wish to delete?", it should be provided by the user-FTP process.
   /// @lparam[in] strFile Pathname of the file to delete.
   /// @return see return values of client_socket::SimpleErrorCheck
   int client_socket::Delete(const string& strFile)
   {
      ASSERT(strFile.has_char());
      reply Reply;
      if (!SendCommand(command::DELE(), { strFile }, Reply))
         return FTP_ERROR;
      return SimpleErrorCheck(Reply);
   }

   /// Executes the FTP command RMD (REMOVE DIRECTORY)
   /// This command causes the directory specified in the pathname to be erased
   /// as a directory (if the pathname is absolute) or as a subdirectory of the
   /// current working directory (if the pathname is relative).
   /// @lparam[in] strDirectory Pathname of the directory to delete.
   /// @return see return values of client_socket::SimpleErrorCheck
   int client_socket::RemoveDirectory(const string& strDirectory)
   {
      ASSERT(strDirectory.has_char());
      reply Reply;
      if (!SendCommand(command::RMD(), { strDirectory } , Reply))
         return FTP_ERROR;
      return SimpleErrorCheck(Reply);
   }

   /// Executes the FTP command STRU (FILE STRUCTURE)
   /// see documentation of nsFTP::structure
   /// The default structure is File.
   /// @lparam[in] crStructure see Documentation of nsFTP::structure
   /// @return see return values of client_socket::SimpleErrorCheck
   int client_socket::FileStructure(const structure& crStructure)
   {
      reply Reply;
      if (!SendCommand(command::STRU(), { crStructure.AsString() } , Reply))
         return FTP_ERROR;
      return SimpleErrorCheck(Reply);
   }

   /// Executes the FTP command MODE (TRANSFER MODE)
   /// see documentation of nsFTP::transfer_mode
   /// The default transfer mode is Stream.
   /// @lparam[in] crTransferMode see Documentation of nsFTP::transfer_mode
   /// @return see return values of client_socket::SimpleErrorCheck
   int client_socket::TransferMode(const transfer_mode& crTransferMode)
   {
      reply Reply;
      if (!SendCommand(command::MODE(), { crTransferMode.AsString() } , Reply))
         return FTP_ERROR;
      return SimpleErrorCheck(Reply);
   }

   /// Executes the FTP command STAT (STATUS)
   /// This command shall cause a status response to be sent over the control
   /// connection in the form of a reply. The command may be sent during a file
   /// transfer (along with the Telnet IP and Synch signals--see the Section on
   /// FTP Commands) in which case the server will respond with the status of the
   /// operation in progress, or it may be sent between file transfers. In the
   /// latter case, the command may have an argument field.
   /// @lparam[in] strPath If the argument is a pathname, the command is analogous
   ///                    to the "list" command except that data shall be transferred
   ///                    over the control connection. If a partial pathname is
   ///                    given, the server may respond with a list of file names or
   ///                    attributes associated with that specification. If no argument
   ///                    is given, the server should return general status information
   ///                    about the server FTP process. This should include current
   ///                    values of all transfer parameters and the status of connections.
   /// @return see return values of client_socket::SimpleErrorCheck
   int client_socket::Status(const string& strPath)
   {
      reply Reply;
      if (!SendCommand(command::STAT(), { strPath } , Reply))
         return FTP_ERROR;
      return SimpleErrorCheck(Reply);
   }

   /// Executes the FTP command ALLO (ALLOCATE)
   /// This command may be required by some servers to reserve sufficient storage
   /// to accommodate the memory_new file to be transferred.
   /// @lparam[in] iReserveBytes The argument shall be a decimal integer representing
   ///                          the number of bytes (using the logical byte size_i32) of
   ///                          storage to be reserved for the file. For files sent
   ///                          with record or page structure a maximum record or page
   ///                          size_i32 (in logical bytes) might also be necessary; this
   ///                          is indicated by a decimal integer in a second argument
   ///                          field of the command.
   /// @pararm[in] piMaxPageOrRecordSize This second argument is optional. This command
   ///                          shall be followed by a STORe or APPEnd command.
   ///                          The ALLO command should be treated as a NOOP (no operation)
   ///                          by those servers which do not require that the maximum
   ///                          size_i32 of the file be declared beforehand, and those servers
   ///                          interested in only the maximum record or page size_i32 should
   ///                          accept a dummy value in the first argument and ignore it.
   /// @return see return values of client_socket::SimpleErrorCheck
   int client_socket::Allocate(int iReserveBytes, const int* piMaxPageOrRecordSize/*=nullptr*/)
   {
      string_array Arguments({ __string(iReserveBytes) });
      if (piMaxPageOrRecordSize != nullptr)
      {
         Arguments.push_back("R");
         Arguments.push_back(__string(*piMaxPageOrRecordSize));
      }

      reply Reply;
      if (!SendCommand(command::ALLO(), Arguments, Reply))
         return FTP_ERROR;
      return SimpleErrorCheck(Reply);
   }

   /// Executes the FTP command SMNT ()
   /// @return see return values of client_socket::SimpleErrorCheck
   int client_socket::StructureMount(const string& strPath)
   {
      reply Reply;
      if (!SendCommand(command::SMNT(), { strPath }, Reply))
         return FTP_ERROR;
      return SimpleErrorCheck(Reply);
   }

   /// Executes the FTP command (STRUCTURE MOUNT)
   /// This command allows the user to mount a different file system data structure
   /// without altering his login or accounting information. Transfer parameters
   /// are similarly unchanged.  The argument is a pathname specifying a directory
   /// or other system dependent file group designator.
   /// @return see return values of client_socket::SimpleErrorCheck
   int client_socket::Reinitialize()
   {
      reply Reply;
      if (!SendCommand(command::REIN(), {}, Reply))
         return FTP_ERROR;

      if (Reply.Code().IsPositiveCompletionReply())
         return FTP_OK;
      else if (Reply.Code().IsPositivePreliminaryReply())
      {
         if (!GetResponse(Reply) || !Reply.Code().IsPositiveCompletionReply())
            return FTP_ERROR;
      }
      else if (Reply.Code().IsNegativeReply())
         return FTP_NOTOK;

      ASSERT(Reply.Code().IsPositiveIntermediateReply());
      return FTP_ERROR;
   }

   /// Executes the FTP command REST (RESTART)
   /// This command does not cause file transfer but skips over the file to the
   /// specified data checkpoint. This command shall be immediately followed
   /// by the appropriate FTP service command which shall cause file transfer
   /// to resume.
   /// @lparam[in] dwPosition Represents the server marker at which file transfer
   ///                       is to be restarted.
   /// @return see return values of client_socket::SimpleErrorCheck
   int client_socket::Restart(::u32 dwPosition)
   {
      reply Reply;
      if (!SendCommand(command::REST(), { __string((u32)dwPosition) }, Reply))
         return FTP_ERROR;

      if (Reply.Code().IsPositiveIntermediateReply())
         return FTP_OK;
      else if (Reply.Code().IsNegativeReply())
         return FTP_NOTOK;

      ASSERT(Reply.Code().IsPositiveReply());

      return FTP_ERROR;
   }

   /// Executes the FTP command const size_i32 &
   /// Return size_i32 of file.
   /// const size_i32 & is not specified in RFC 959.
   /// @lparam[in] Pathname of a file.
   /// @lparam[out] Size of the file specified in pathname.
   /// @return see return values of client_socket::SimpleErrorCheck
   int client_socket::FileSize(const string& strPath, long& lSize)
   {
      reply Reply;
      if (!SendCommand(command::SIZE_I32(), { strPath } , Reply))
         return FTP_ERROR;
      lSize = atoi(Reply.Value().substr(4));
      return SimpleErrorCheck(Reply);
   }

   /// Executes the FTP command MDTM
   /// Show last modification time of file.
   /// MDTM is not specified in RFC 959.
   /// @lparam[in] strPath Pathname of a file.
   /// @lparam[out] strModificationTime Modification time of the file specified in pathname.
   /// @return see return values of client_socket::SimpleErrorCheck
   int client_socket::FileModificationTime(const string& strPath, string& strModificationTime)
   {
      
      strModificationTime.Empty();

      reply Reply;

      if (!SendCommand(command::MDTM(), { strPath }, Reply))
      {

         return FTP_ERROR;

      }

      if (Reply.Value().length() >= 18)
      {
         string strTemp(Reply.Value().substr(4));
         strsize iPos = strTemp.find('.');
         if (iPos >= 0)
            strTemp = strTemp.substr(0, iPos);
         if (strTemp.length() == 14)
            strModificationTime = strTemp;
      }

      if (strModificationTime.is_empty())
         return FTP_ERROR;

      return SimpleErrorCheck(Reply);
   }

   /// Show last modification time of file.
   /// @lparam[in] strPath Pathname of a file.
   /// @lparam[out] tmModificationTime Modification time of the file specified in pathname.
   /// @return see return values of client_socket::SimpleErrorCheck
   int client_socket::FileModificationTime(const string& strPath, tm& tmModificationTime)
   {
      string strTemp;
      const int iRet = FileModificationTime(strPath, strTemp);

      __memset(&tmModificationTime, 0, sizeof(tmModificationTime));
      if (iRet == FTP_OK)
      {
         tmModificationTime.tm_year = atoi(strTemp.substr(0, 4));
         tmModificationTime.tm_mon = atoi(strTemp.substr(4, 2));
         tmModificationTime.tm_mday = atoi(strTemp.substr(6, 2));
         tmModificationTime.tm_hour = atoi(strTemp.substr(8, 2));
         tmModificationTime.tm_min = atoi(strTemp.substr(10, 2));
         tmModificationTime.tm_sec = atoi(strTemp.substr(12));
      }
      return iRet;
   }

   /// Notifies all observers that an error occurred.
   /// @lparam[in] strErrorMsg Error message which is reported to all observers.
   /// @lparam[in] Name of the sourcecode file where the error occurred.
   /// @lparam[in] Line number in th sourcecode file where the error occurred.
   void client_socket::ReportError(const string& strErrorMsg, const string& strFile, ::u32 dwLineNr)
   {
      for (auto * point_i32 : (observer_array &)m_setObserver)
         point_i32->OnInternalError(strErrorMsg, strFile, dwLineNr);
   }


} // namespace ftp





