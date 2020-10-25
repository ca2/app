////////////////////////////////////////////////////////////////////////////////
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
////////////////////////////////////////////////////////////////////////////////

#include "framework.h"
#include "_.h"


namespace ftp
{

   string structure::AsString() const
   {
      switch (m_enStructure)
      {
      case type_file:   return _T("F");
      case type_record: return _T("R");
      case type_page:   return _T("P");
      }
      ASSERT(false);
      return _T("");
   }

   string transfer_mode::AsString() const
   {
      string strMode;
      switch (m_etransfermode)
      {
      case transfer_mode_stream:      return _T("S");
      case transfer_mode_block:       return _T("B");
      case transfer_mode_compressed:  return _T("C");
      }
      ASSERT(false);
      return _T("");
   }

   string type::AsString() const
   {
      switch (m_etype)
      {
      case tyASCII:     return _T("A");
      case tyEBCDIC:    return _T("E");
      case tyImage:     return _T("I");
      case tyLocalByte: return _T("L");
      }
      ASSERT(false);
      return _T("");
   }

   string format::AsString() const
   {
      switch (m_eformat)
      {
      case format_non_print:        return _T("N");
      case format_telnet:    return _T("T");
      case format_carriage_control: return _T("C");
      case format_invalid:         break;
      }
      ASSERT(false);
      return _T("");
   }

   /// returns the string which is used for display
   string firewall_type::AsDisplayString() const
   {
      switch (m_etype)
      {
      case type_none:                              return _T("no firewall");
      case type_host_name:                      return _T("SITE hostname");
      case type_user_after_logon:                    return _T("USER after logon");
      case type_proxy_open:                         return _T("proxy OPEN");
      case type_transparent:                       return _T("Transparent");
      case type_user_with_no_logon:                   return _T("USER with no logon");
      case type_user_fire_id_at_remote_host:            return _T("USER fireID@remotehost");
      case type_user_remote_id_at_remote_host_fire_id:    return _T("USER remoteID@remotehost fireID");
      case type_user_remote_id_at_fire_id_at_remote_host:  return _T("USER remoteID@fireID@remotehost");
      }
      ASSERT(false);
      return _T("");
   }

   /// return the string which is used for storage (e.g. in an XML- or INI-file)
   string firewall_type::AsStorageString() const
   {
      switch (m_etype)
      {
      case type_none:                              return _T("NO_FIREWALL");
      case type_host_name:                      return _T("SITE_HOSTNAME");
      case type_user_after_logon:                    return _T("USER_AFTER_LOGON");
      case type_proxy_open:                         return _T("PROXY_OPEN");
      case type_transparent:                       return _T("TRANSPARENT");
      case type_user_with_no_logon:                   return _T("USER_WITH_NO_LOGON");
      case type_user_fire_id_at_remote_host:            return _T("USER_FIREID@REMOTEHOST");
      case type_user_remote_id_at_remote_host_fire_id:    return _T("USER_REMOTEID@REMOTEHOST_FIREID");
      case type_user_remote_id_at_fire_id_at_remote_host:  return _T("USER_REMOTEID@FIREID@REMOTEHOST");
      }
      ASSERT(false);
      return _T("");
   }

   /// returns all available firewall types
   void firewall_type::GetAllTypes(TFirewallTypeVector& vTypes)
   {
      vTypes.resize(9);
      vTypes[0] = type_none;
      vTypes[1] = type_host_name;
      vTypes[2] = type_user_after_logon;
      vTypes[3] = type_proxy_open;
      vTypes[4] = type_transparent;
      vTypes[5] = type_user_with_no_logon;
      vTypes[6] = type_user_fire_id_at_remote_host;
      vTypes[7] = type_user_remote_id_at_remote_host_fire_id;
      vTypes[8] = type_user_remote_id_at_fire_id_at_remote_host;
   }

   logon::logon() :
      //storage_client(Sess(pobject).account()->storage()),
      //::account::credentials(__new(::account::user(this)), Sess(pobject).account()->storage()),
      m_ushHostport(DEFAULT_FTP_PORT),
      m_ushFwPort(DEFAULT_FTP_PORT),
      m_FwType(firewall_type::None())
   {
      m_puser->m_strLogin = ANONYMOUS_USER;
   }

   logon::logon(const string& strHostname, WINUSHORT ushHostport, const string& strUsername,
                const string& strPassword, const string& strAccount) :
      //storage_client(Sess(pobject).account()->storage()),
      //::account::credentials(__new(::account::user(this)), Sess(pobject).account()->storage()),
      m_strHostname(strHostname),
      m_ushHostport(ushHostport),
      m_strAccount(strAccount),
      m_ushFwPort(DEFAULT_FTP_PORT),
      m_FwType(firewall_type::None())
   {
      m_puser->m_strLogin = strUsername;
      m_strPassword = strPassword;
   }

   logon::logon( const string& strHostname, WINUSHORT ushHostport, const string& strUsername, const string& strPassword,
                const string& strAccount, const string& strFwHostname, const string& strFwUsername,
                const string& strFwPassword, WINUSHORT ushFwPort, const firewall_type& crFwType) :
      //storage_client(Sess(pobject).account()->storage()),
      //::account::credentials(__new(::account::user(this)), Sess(pobject).account()->storage()),
      m_strHostname(strHostname),
      m_ushHostport(ushHostport),
      m_strAccount(strAccount),
      m_strFwHostname(strFwHostname),
      m_strFwUsername(strFwUsername),
      m_strFwPassword(strFwPassword),
      m_ushFwPort(ushFwPort),
      m_FwType(crFwType)
   {
      m_puser->m_strLogin = strUsername;
      m_strPassword = strPassword;

   }

   void logon::SetHost(const string& strHostname, WINUSHORT ushHostport, const string& strUsername,
                       const string& strPassword, const string& strAccount)
   {
      m_strHostname = strHostname;
      m_ushHostport = ushHostport;
      m_puser->m_strLogin = strUsername;
      m_strPassword = strPassword;
      m_strAccount = strAccount;
   }

   void logon::SetFirewall(const string& strFwHostname, const string& strFwUsername, const string& strFwPassword,
                           WINUSHORT ushFwPort, const firewall_type& crFwType)
   {
      m_strFwHostname = strFwHostname;
      m_strFwUsername = strFwUsername;
      m_strFwPassword = strFwPassword;
      m_ushFwPort = ushFwPort;
      m_FwType = crFwType;
   }



   command::info2 * command::info2::g_pTheOneAndOnly = nullptr;

   void command::info2::insert(enum_command enCommand, const string& strServerString, const string& strCompleteServerStringSyntax, UINT uiNumberOfParameters,
                               UINT uiNumberOfOptionalParameters, TSpecificationEnum enSpecification, enum_type enType)
   {
      set_at(enCommand, __new(extended_info(strServerString, strCompleteServerStringSyntax, uiNumberOfParameters,
                                uiNumberOfOptionalParameters, enSpecification, enType)));
   }


   command::info2::info2()
   {
      insert(cmdABOR, _T("ABOR"), _T("ABOR <CRLF>"), 0, 0, RFC959, NonDatachannel);
      insert(cmdACCT, _T("ACCT"), _T("ACCT <SP> <account-information> <CRLF>"), 1, 0, RFC959, NonDatachannel);
      insert(cmdALLO, _T("ALLO"), _T("ALLO <SP> <decimal-integer> [<SP> R <SP> <decimal-integer>] <CRLF>"), 3, 2, RFC959, NonDatachannel);
      insert(cmdAPPE, _T("APPE"), _T("APPE <SP> <pathname> <CRLF>"), 1, 0, RFC959, DatachannelWrite);
      insert(cmdCDUP, _T("CDUP"), _T("CDUP <CRLF>"), 0, 0, RFC959, NonDatachannel);
      insert(cmdCWD, _T("CWD"), _T("CWD <SP> <pathname> <CRLF>"), 1, 0, RFC959, NonDatachannel);
      insert(cmdDELE, _T("DELE"), _T("DELE <SP> <pathname> <CRLF>"), 1, 0, RFC959, NonDatachannel);
      insert(cmdHELP, _T("HELP"), _T("HELP [<SP> <string>] <CRLF>"), 1, 1, RFC959, NonDatachannel);
      insert(cmdLIST, _T("LIST"), _T("LIST [<SP> <pathname>] <CRLF>"), 1, 1, RFC959, DatachannelRead);
      insert(cmdMDTM, _T("MDTM"), _T("MDTM <SP> <pathname> <CRLF>"), 1, 0, RFC3659, NonDatachannel);
      insert(cmdMKD, _T("MKD"), _T("MKD <SP> <pathname> <CRLF>"), 1, 0, RFC959, NonDatachannel);
      insert(cmdMODE, _T("MODE"), _T("MODE <SP> <mode-code> <CRLF>"), 1, 0, RFC959, NonDatachannel);
      insert(cmdNLST, _T("NLST"), _T("NLST [<SP> <pathname>] <CRLF>"), 1, 1, RFC959, DatachannelRead);
      insert(cmdNOOP, _T("NOOP"), _T("NOOP <CRLF>"), 0, 0, RFC959, NonDatachannel);
      insert(cmdOPEN, _T("OPEN"), _T("OPEN <SP> <string> <CRLF>"), 1, 0, Unknown, NonDatachannel);
      insert(cmdPASS, _T("PASS"), _T("PASS <SP> <password> <CRLF>"), 1, 0, RFC959, NonDatachannel);
      insert(cmdPASV, _T("PASV"), _T("PASV <CRLF>"), 0, 0, RFC959, NonDatachannel);
      insert(cmdPORT, _T("PORT"), _T("PORT <SP> <host-port> <CRLF>"), 1, 0, RFC959, NonDatachannel);
      insert(cmdPWD, _T("PWD"), _T("PWD <CRLF>"), 0, 0, RFC959, NonDatachannel);
      insert(cmdQUIT, _T("QUIT"), _T("QUIT <CRLF>"), 0, 0, RFC959, NonDatachannel);
      insert(cmdREIN, _T("REIN"), _T("REIN <CRLF>"), 0, 0, RFC959, NonDatachannel);
      insert(cmdREST, _T("REST"), _T("REST <SP> <marker> <CRLF>"), 1, 0, RFC959, NonDatachannel);
      insert(cmdRETR, _T("RETR"), _T("RETR <SP> <pathname> <CRLF>"), 1, 0, RFC959, DatachannelRead);
      insert(cmdRMD, _T("RMD"), _T("RMD <SP> <pathname> <CRLF>"), 1, 0, RFC959, NonDatachannel);
      insert(cmdRNFR, _T("RNFR"), _T("RNFR <SP> <pathname> <CRLF>"), 1, 0, RFC959, NonDatachannel);
      insert(cmdRNTO, _T("RNTO"), _T("RNTO <SP> <pathname> <CRLF>"), 1, 0, RFC959, NonDatachannel);
      insert(cmdSITE, _T("SITE"), _T("SITE <SP> <string> <CRLF>"), 1, 0, RFC959, NonDatachannel);
      insert(cmdSIZE, _T("const size &"), _T("const size & <SP> <pathname> <CRLF>"), 1, 0, RFC3659, NonDatachannel);
      insert(cmdSMNT, _T("SMNT"), _T("SMNT <SP> <pathname> <CRLF>"), 1, 0, RFC959, NonDatachannel);
      insert(cmdSTAT, _T("STAT"), _T("STAT [<SP> <pathname>] <CRLF>"), 1, 1, RFC959, NonDatachannel);
      insert(cmdSTOR, _T("STOR"), _T("STOR <SP> <pathname> <CRLF>"), 1, 0, RFC959, DatachannelWrite);
      insert(cmdSTOU, _T("STOU"), _T("STOU <CRLF>"), 0, 0, RFC959, DatachannelWrite);
      insert(cmdSTRU, _T("STRU"), _T("STRU <SP> <structure-code> <CRLF>"), 1, 0, RFC959, NonDatachannel);
      insert(cmdSYST, _T("SYST"), _T("SYST <CRLF>"), 0, 0, RFC959, NonDatachannel);
      insert(cmdTYPE, _T("TYPE"), _T("TYPE <SP> <type-code> <CRLF>"), 1, 0, RFC959, NonDatachannel);
      insert(cmdUSER, _T("USER"), _T("USER <SP> <username> <CRLF>"), 1, 0, RFC959, NonDatachannel);
      insert(cmdPROT, _T("PROT"), _T("PROT <SP> <prot level> <CRLF>"), 1, 0, RFC959, NonDatachannel);
   }

   const command::iextended_info& command::info2::Get(enum_command enCommand)
   {
      auto it = GetInstance().find(enCommand);
      ASSERT(it);
      return *it->element2();
   }

   bool command::IsDatachannelReadCommand() const
   {
      return info2::Get(m_enCommand).GetType() == DatachannelRead;
   }

   bool command::IsDatachannelWriteCommand() const
   {
      return info2::Get(m_enCommand).GetType() == DatachannelWrite;
   }

   bool command::IsDatachannelCommand() const
   {
      return IsDatachannelReadCommand() || IsDatachannelWriteCommand();
   }

   string command::AsString() const
   {
      return info2::Get(m_enCommand).GetServerString();
   }

   /// Returns the command string.
   /// @lparam[in] strArgument Parameter which have to be added to the command.
   string command::AsString(const string_array & Arguments) const
   {

      if (Arguments.empty())
      {

         return AsString();

      }

      return AsString() + " " + Arguments.implode(" ");

   }


   const command::iextended_info& command::GetExtendedInfo() const
   {
      return info2::Get(m_enCommand);
   }



} // namespace ftp




