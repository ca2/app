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
#include "data_types.h"


namespace ftp
{

   string structure::AsString() const
   {
      switch (m_enStructure)
      {
      case type_file:   return "F";
      case type_record: return "R";
      case type_page:   return "P";
      }
      ASSERT(false);
      return "";
   }

   string transfer_mode::AsString() const
   {
      string strMode;
      switch (m_etransfermode)
      {
      case transfer_mode_stream:      return "S";
      case transfer_mode_block:       return "B";
      case transfer_mode_compressed:  return "C";
      }
      ASSERT(false);
      return "";
   }

   string type::AsString() const
   {
      switch (m_etype)
      {
      case tyASCII:     return "A";
      case tyEBCDIC:    return "E";
      case tyImage:     return "I";
      case tyLocalByte: return "L";
      }
      ASSERT(false);
      return "";
   }

   string format::AsString() const
   {
      switch (m_eformat)
      {
      case format_non_print:           return "N";
      case format_telnet:              return "T";
      case format_carriage_control:    return "C";
      case format_invalid:             break;
      }
      ASSERT(false);
      return "";
   }

   /// returns the string which is used for display
   string firewall_type::AsDisplayString() const
   {
      switch (m_etype)
      {
      case type_none:                              return "no firewall";
      case type_host_name:                      return "SITE hostname";
      case type_user_after_logon:                    return "USER after logon";
      case type_proxy_open:                         return "proxy OPEN";
      case type_transparent:                       return "Transparent";
      case type_user_with_no_logon:                   return "USER with no logon";
      case type_user_fire_id_at_remote_host:            return "USER fireID@remotehost";
      case type_user_remote_id_at_remote_host_fire_id:    return "USER remoteID@remotehost fireID";
      case type_user_remote_id_at_fire_id_at_remote_host:  return "USER remoteID@fireID@remotehost";
      }
      ASSERT(false);
      return "";
   }

   /// return the string which is used for storage (e.g. in an XML- or INI-file)
   string firewall_type::AsStorageString() const
   {
      switch (m_etype)
      {
      case type_none:                              return "NO_FIREWALL";
      case type_host_name:                      return "SITE_HOSTNAME";
      case type_user_after_logon:                    return "USER_AFTER_LOGON";
      case type_proxy_open:                         return "PROXY_OPEN";
      case type_transparent:                       return "TRANSPARENT";
      case type_user_with_no_logon:                   return "USER_WITH_NO_LOGON";
      case type_user_fire_id_at_remote_host:            return "USER_FIREID@REMOTEHOST";
      case type_user_remote_id_at_remote_host_fire_id:    return "USER_REMOTEID@REMOTEHOST_FIREID";
      case type_user_remote_id_at_fire_id_at_remote_host:  return "USER_REMOTEID@FIREID@REMOTEHOST";
      }
      ASSERT(false);
      return "";
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
      //storage_client(Sess(pparticle).account()->storage()),
      //::account::credentials(__initialize_new ::account::user(this))), Sess(pparticle).account()->storage(,
      m_ushHostport(DEFAULT_FTP_PORT),
      m_ushFwPort(DEFAULT_FTP_PORT),
      m_FwType(firewall_type::None())
   {
      m_puser->m_strLogin = ANONYMOUS_USER;
   }

   logon::logon(const ::scoped_string & scopedstrHostname, unsigned short ushHostport, const ::scoped_string & scopedstrUsername,
                const ::scoped_string & scopedstrPassword, const ::scoped_string & scopedstrAccount) :
      //storage_client(Sess(pparticle).account()->storage()),
      //::account::credentials(__initialize_new ::account::user(this))), Sess(pparticle).account()->storage(,
      m_strHostname(scopedstrHostname),
      m_ushHostport(ushHostport),
      m_strAccount(scopedstrAccount),
      m_ushFwPort(DEFAULT_FTP_PORT),
      m_FwType(firewall_type::None())
   {
      m_puser->m_strLogin = scopedstrUsername;
      m_strPassword = scopedstrPassword;
   }

   logon::logon( const ::scoped_string & scopedstrHostname, unsigned short ushHostport, const ::scoped_string & scopedstrUsername, const ::scoped_string & scopedstrPassword,
                const ::scoped_string & scopedstrAccount, const ::scoped_string & scopedstrFwHostname, const ::scoped_string & scopedstrFwUsername,
                const ::scoped_string & scopedstrFwPassword, unsigned short ushFwPort, const firewall_type& crFwType) :
      //storage_client(Sess(pparticle).account()->storage()),
      //::account::credentials(__initialize_new ::account::user(this))), Sess(pparticle).account()->storage(,
      m_strHostname(scopedstrHostname),
      m_ushHostport(ushHostport),
      m_strAccount(scopedstrAccount),
      m_strFwHostname(scopedstrFwHostname),
      m_strFwUsername(scopedstrFwUsername),
      m_strFwPassword(scopedstrFwPassword),
      m_ushFwPort(ushFwPort),
      m_FwType(crFwType)
   {
      m_puser->m_strLogin =scopedstrUsername;
      m_strPassword = scopedstrPassword;

   }

   void logon::SetHost(const ::scoped_string & scopedstrHostname, unsigned short ushHostport, const ::scoped_string & scopedstrUsername,
                       const ::scoped_string & scopedstrPassword, const ::scoped_string & scopedstrAccount)
   {
      m_strHostname = scopedstrHostname;
      m_ushHostport = ushHostport;
      m_puser->m_strLogin = scopedstrUsername;
      m_strPassword = scopedstrPassword;
      m_strAccount = scopedstrAccount;
   }

   void logon::SetFirewall(const ::scoped_string & scopedstrFwHostname, const ::scoped_string & scopedstrFwUsername, const ::scoped_string & scopedstrFwPassword,
                           unsigned short ushFwPort, const firewall_type& crFwType)
   {
      m_strFwHostname = scopedstrFwHostname;
      m_strFwUsername = scopedstrFwUsername;
      m_strFwPassword = scopedstrFwPassword;
      m_ushFwPort = ushFwPort;
      m_FwType = crFwType;
   }



   command::info2 * command::info2::g_pTheOneAndOnly = nullptr;

   void command::info2::insert(enum_command enCommand, const ::scoped_string & scopedstrServerString, const ::scoped_string & scopedstrCompleteServerStringSyntax, unsigned int uNumberOfParameters,
                               unsigned int uNumberOfOptionalParameters, TSpecificationEnum enSpecification, enum_type enType)
   {
      set_at(enCommand, ___new  extended_info (scopedstrServerString, scopedstrCompleteServerStringSyntax, uNumberOfParameters,
                                uNumberOfOptionalParameters, enSpecification, enType));
   }


   command::info2::info2()
   {
      insert(cmdABOR, "ABOR", "ABOR <CRLF>", 0, 0, RFC959, NonDatachannel);
      insert(cmdACCT, "ACCT", "ACCT <SP> <account-information> <CRLF>", 1, 0, RFC959, NonDatachannel);
      insert(cmdALLO, "ALLO", "ALLO <SP> <decimal-integer> [<SP> R <SP> <decimal-integer>] <CRLF>", 3, 2, RFC959, NonDatachannel);
      insert(cmdAPPE, "APPE", "APPE <SP> <pathname> <CRLF>", 1, 0, RFC959, DatachannelWrite);
      insert(cmdCDUP, "CDUP", "CDUP <CRLF>", 0, 0, RFC959, NonDatachannel);
      insert(cmdCWD, "CWD", "CWD <SP> <pathname> <CRLF>", 1, 0, RFC959, NonDatachannel);
      insert(cmdDELE, "DELE", "DELE <SP> <pathname> <CRLF>", 1, 0, RFC959, NonDatachannel);
      insert(cmdHELP, "HELP", "HELP [<SP> <string>] <CRLF>", 1, 1, RFC959, NonDatachannel);
      insert(cmdLIST, "LIST", "LIST [<SP> <pathname>] <CRLF>", 1, 1, RFC959, DatachannelRead);
      insert(cmdMDTM, "MDTM", "MDTM <SP> <pathname> <CRLF>", 1, 0, RFC3659, NonDatachannel);
      insert(cmdMKD, "MKD", "MKD <SP> <pathname> <CRLF>", 1, 0, RFC959, NonDatachannel);
      insert(cmdMODE, "MODE", "MODE <SP> <mode-code> <CRLF>", 1, 0, RFC959, NonDatachannel);
      insert(cmdNLST, "NLST", "NLST [<SP> <pathname>] <CRLF>", 1, 1, RFC959, DatachannelRead);
      insert(cmdNOOP, "NOOP", "NOOP <CRLF>", 0, 0, RFC959, NonDatachannel);
      insert(cmdOPEN, "OPEN", "OPEN <SP> <string> <CRLF>", 1, 0, Unknown, NonDatachannel);
      insert(cmdPASS, "PASS", "PASS <SP> <password> <CRLF>", 1, 0, RFC959, NonDatachannel);
      insert(cmdPASV, "PASV", "PASV <CRLF>", 0, 0, RFC959, NonDatachannel);
      insert(cmdPORT, "PORT", "PORT <SP> <host-port> <CRLF>", 1, 0, RFC959, NonDatachannel);
      insert(cmdPWD, "PWD", "PWD <CRLF>", 0, 0, RFC959, NonDatachannel);
      insert(cmdQUIT, "QUIT", "QUIT <CRLF>", 0, 0, RFC959, NonDatachannel);
      insert(cmdREIN, "REIN", "REIN <CRLF>", 0, 0, RFC959, NonDatachannel);
      insert(cmdREST, "REST", "REST <SP> <marker> <CRLF>", 1, 0, RFC959, NonDatachannel);
      insert(cmdRETR, "RETR", "RETR <SP> <pathname> <CRLF>", 1, 0, RFC959, DatachannelRead);
      insert(cmdRMD, "RMD", "RMD <SP> <pathname> <CRLF>", 1, 0, RFC959, NonDatachannel);
      insert(cmdRNFR, "RNFR", "RNFR <SP> <pathname> <CRLF>", 1, 0, RFC959, NonDatachannel);
      insert(cmdRNTO, "RNTO", "RNTO <SP> <pathname> <CRLF>", 1, 0, RFC959, NonDatachannel);
      insert(cmdSITE, "SITE", "SITE <SP> <string> <CRLF>", 1, 0, RFC959, NonDatachannel);
      insert(cmdSIZE, "const int_size &", "const int_size & <SP> <pathname> <CRLF>", 1, 0, RFC3659, NonDatachannel);
      insert(cmdSMNT, "SMNT", "SMNT <SP> <pathname> <CRLF>", 1, 0, RFC959, NonDatachannel);
      insert(cmdSTAT, "STAT", "STAT [<SP> <pathname>] <CRLF>", 1, 1, RFC959, NonDatachannel);
      insert(cmdSTOR, "STOR", "STOR <SP> <pathname> <CRLF>", 1, 0, RFC959, DatachannelWrite);
      insert(cmdSTOU, "STOU", "STOU <CRLF>", 0, 0, RFC959, DatachannelWrite);
      insert(cmdSTRU, "STRU", "STRU <SP> <structure-code> <CRLF>", 1, 0, RFC959, NonDatachannel);
      insert(cmdSYST, "SYST", "SYST <CRLF>", 0, 0, RFC959, NonDatachannel);
      insert(cmdTYPE, "TYPE", "TYPE <SP> <type-code> <CRLF>", 1, 0, RFC959, NonDatachannel);
      insert(cmdUSER, "USER", "USER <SP> <username> <CRLF>", 1, 0, RFC959, NonDatachannel);
      insert(cmdPROT, "PROT", "PROT <SP> <prot level> <CRLF>", 1, 0, RFC959, NonDatachannel);
   }

   const command::iextended_info& command::info2::Get(enum_command enCommand)
   {
      auto p = GetInstance().find_item(enCommand);
      ASSERT(p);
      return *p->element2();
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




