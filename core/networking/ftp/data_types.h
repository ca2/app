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
#pragma once


namespace ftp
{

   enum e_connection_type
   {

      connection_type_plain,
      connection_type_tls_implicit,
      connection_type_tls_explicit,

   };

   // constants
   const char ANONYMOUS_USER[] = "anonymous";
   enum T_enConstants
   {
      DEFAULT_FTP_PORT = 21, ///< The default port that an FTP service listens to on a remote host
      FTP_ERROR  = -1,
      FTP_OK     =  0,
      FTP_NOTOK  =  1,
   };

   /// Data Structure
   class CLASS_DECL_CORE structure
   {
   public:
      enum enum_type { type_file, type_record, type_page };

      structure(const structure& structure) :
         m_enStructure(structure.AsEnum()) {}

      bool operator==(const enum_type& rhs) const { return m_enStructure==rhs; }
      bool operator!=(const enum_type& rhs) const { return !operator==(rhs); }
      bool operator==(const structure& rhs) const { return m_enStructure==rhs.m_enStructure; }
      bool operator!=(const structure& rhs) const { return !operator==(rhs); }

      structure& operator=(const structure& rhs) { m_enStructure = rhs.AsEnum(); return *this; }

      enum_type AsEnum() const { return m_enStructure; }
      string AsString() const;

      static const structure File()   { return type_file;   }
      static const structure Record() { return type_record; }
      static const structure Page()   { return type_page;   }

   private:
      structure(enum_type enStructure) : m_enStructure(enStructure) {}
      enum_type m_enStructure;
   };

   /// Transmission Modes
   class CLASS_DECL_CORE transfer_mode
   {
   public:
      enum e_transfer_mode { transfer_mode_stream, transfer_mode_block, transfer_mode_compressed };

      transfer_mode(e_transfer_mode enTransferMode) : m_etransfermode(enTransferMode) {}
      e_transfer_mode m_etransfermode;
      transfer_mode(const transfer_mode& transferMode) :
         m_etransfermode(transferMode.AsEnum()) {}

      bool operator==(const e_transfer_mode& rhs) const { return m_etransfermode==rhs; }
      bool operator!=(const e_transfer_mode& rhs) const { return !operator==(rhs); }
      bool operator==(const transfer_mode& rhs) const { return m_etransfermode==rhs.m_etransfermode; }
      bool operator!=(const transfer_mode& rhs) const { return !operator==(rhs); }

      transfer_mode& operator=(const transfer_mode& rhs) { m_etransfermode = rhs.AsEnum(); return *this; }

      e_transfer_mode AsEnum() const { return m_etransfermode; }
      string AsString() const;

      static const transfer_mode Stream()     { return transfer_mode_stream;     }
      static const transfer_mode Block()      { return transfer_mode_block;      }
      static const transfer_mode Compressed() { return transfer_mode_compressed; }

   };

   class firewall_type;
   typedef array<firewall_type> TFirewallTypeVector;

   /// Firewall Type
   class CLASS_DECL_CORE firewall_type
   {
   public:
      // don't change order of enumeration
      enum enum_type
      {
         type_none, type_host_name, type_user_after_logon, type_proxy_open, type_transparent,
         type_user_with_no_logon, type_user_fire_id_at_remote_host, type_user_remote_id_at_remote_host_fire_id,
         type_user_remote_id_at_fire_id_at_remote_host
      };


      enum_type m_etype;


      firewall_type() : m_etype(type_none) {}
      firewall_type(enum_type enFirewallType) : m_etype(enFirewallType) {}
      firewall_type(const firewall_type& firewallType) :
         m_etype(firewallType.AsEnum()) {}

      bool operator==(const enum_type& rhs) const { return m_etype==rhs; }
      bool operator!=(const enum_type& rhs) const { return !operator==(rhs); }
      bool operator==(const firewall_type& rhs) const { return m_etype==rhs.m_etype; }
      bool operator!=(const firewall_type& rhs) const { return !operator==(rhs); }

      firewall_type& operator=(const firewall_type& rhs) { m_etype = rhs.AsEnum(); return *this; }

      enum_type AsEnum() const { return m_etype; }

      string AsDisplayString() const;
      string AsStorageString() const;
      static void GetAllTypes(TFirewallTypeVector& vTypes);

      static const firewall_type None()                             { return type_none;                             }
      static const firewall_type SiteHostName()                     { return type_host_name;                     }
      static const firewall_type UserAfterLogon()                   { return type_user_after_logon;                   }
      static const firewall_type ProxyOpen()                        { return type_proxy_open;                        }
      static const firewall_type Transparent()                      { return type_transparent;                      }
      static const firewall_type UserWithNoLogon()                  { return type_user_with_no_logon;                  }
      static const firewall_type UserFireIDatRemotehost()           { return type_user_fire_id_at_remote_host;           }
      static const firewall_type UserRemoteIDatRemoteHostFireID()   { return type_user_remote_id_at_remote_host_fire_id;   }
      static const firewall_type UserRemoteIDatFireIDatRemoteHost() { return type_user_remote_id_at_fire_id_at_remote_host; }

   };

   /// @brief Representation Type - 1st lparam (see representation)
   class CLASS_DECL_CORE type
   {
   public:
      enum enum_type { tyASCII, tyEBCDIC, tyImage, tyLocalByte };

      type(const type& type) :
         m_etype(type.AsEnum()) {}

      bool operator==(const enum_type& rhs) const { return m_etype==rhs; }
      bool operator!=(const enum_type& rhs) const { return !operator==(rhs); }
      bool operator==(const type& rhs) const { return m_etype==rhs.m_etype; }
      bool operator!=(const type& rhs) const { return !operator==(rhs); }

      type& operator=(const type& rhs) { m_etype = rhs.AsEnum(); return *this; }

      enum_type AsEnum() const { return m_etype; }
      string AsString() const;

      static const type ASCII()     { return tyASCII;     }
      static const type EBCDIC()    { return tyEBCDIC;    }
      static const type Image()     { return tyImage;     }
      static const type LocalByte() { return tyLocalByte; }

      type(enum_type enType) : m_etype(enType) {}
      enum_type m_etype;
   };

   /// @brief Representation Type - 2nd lparam (see representation)
   class CLASS_DECL_CORE format
   {
   public:
      enum enum_format { format_invalid, format_non_print, format_telnet, format_carriage_control };

      format() : m_eformat(format_invalid) {}
      format(const format& format) :
         m_eformat(format.AsEnum()) {}

      bool operator==(const enum_format& rhs) const { return m_eformat==rhs; }
      bool operator!=(const enum_format& rhs) const { return !operator==(rhs); }
      bool operator==(const format& rhs) const { return m_eformat==rhs.m_eformat; }
      bool operator!=(const format& rhs) const { return !operator==(rhs); }

      format& operator=(const format& rhs) { m_eformat = rhs.AsEnum(); return *this; }

      enum_format AsEnum() const { return m_eformat; }
      string AsString() const;
      bool IsValid() const { return m_eformat != format_invalid; }

      static const format NonPrint()        { return format_non_print;        }
      static const format TelnetFormat()    { return format_telnet;    }
      static const format CarriageControl() { return format_carriage_control; }

      format(enum_format enTypeFormat) : m_eformat(enTypeFormat) {}
      enum_format m_eformat;
   };

   /// Representation Type (see also type and format)
   class CLASS_DECL_CORE representation :
      virtual public ::object
   {
   public:
      representation(class type Type) : m_Type(Type) {}
      representation(class type Type, format Format) : m_Type(Type), m_Format(Format) {}

      bool operator==(const representation& rhs) const { return rhs.m_Type == m_Type && rhs.m_Format == m_Format; }
      bool operator!=(const representation& rhs) const { return !operator==(rhs); }
      representation& operator=(const representation& rhs)
      {
         m_Type = rhs.m_Type;
         m_Format = rhs.m_Format;
         return *this;
      }

      const class type&       Type()   const { return m_Type; }
      const format& Format() const { return m_Format; }

      class type       m_Type;
      format m_Format;
   };

   //class args : public string_array
   //{
   //public:
   //   args() {}
   //   args(const string& strArgument) { push_back(strArgument); }
   //   args(const string& strFirstArgument, const string& strSecondArgument) { push_back(strFirstArgument); push_back(strSecondArgument); }
   //   args(const string& strFirstArgument, const string& strSecondArgument, const string& strThirdArgument) { push_back(strFirstArgument); push_back(strSecondArgument); push_back(strThirdArgument); }
   //};

   class CLASS_DECL_CORE command
   {
   public:
      enum enum_command { cmdABOR, cmdACCT, cmdALLO, cmdAPPE, cmdCDUP, cmdCWD, cmdDELE, cmdHELP, cmdLIST, cmdMDTM, cmdMKD, cmdMODE, cmdNLST, cmdNOOP, cmdOPEN, cmdPASS, cmdPASV, cmdPORT, cmdPWD, cmdQUIT, cmdREIN, cmdREST, cmdRETR, cmdRMD, cmdRNFR, cmdRNTO, cmdSITE, cmdSIZE, cmdSMNT, cmdSTAT, cmdSTOR, cmdSTOU, cmdSTRU, cmdSYST, cmdTYPE, cmdUSER, cmdPROT};
      enum TSpecificationEnum { Unknown, RFC959, RFC3659, };
      enum enum_type { DatachannelRead, DatachannelWrite, NonDatachannel, };

      class iextended_info : public iinterface
      {
      public:
         virtual ~iextended_info() {}
         virtual const string& GetServerString() const = 0;
         virtual const string& GetCompleteServerStringSyntax() const = 0;
         virtual ::u32 GetNumberOfParameters() const = 0;
         virtual ::u32 GetNumberOfOptionalParameters() const = 0;
         virtual TSpecificationEnum GetSpecification() const = 0;
         virtual enum_type GetType() const = 0;
      };

      command(const command& datachannelCmd) :
         m_enCommand(datachannelCmd.AsEnum()) {}

      bool operator==(enum_command rhs) const { return m_enCommand==rhs; }
      bool operator!=(enum_command rhs) const { return !operator==(rhs); }

      bool operator==(const command& rhs) const { return m_enCommand==rhs.m_enCommand; }
      bool operator!=(const command& rhs) const { return !operator==(rhs); }

      command& operator=(const command& rhs)
      {
         m_enCommand = rhs.AsEnum();
         return *this;
      }

      enum_command AsEnum() const { return m_enCommand; }
      string AsString() const;
      string AsString(const string_array & Arguments) const;
      const iextended_info& GetExtendedInfo() const;

      bool IsDatachannelReadCommand() const;
      bool IsDatachannelWriteCommand() const;
      bool IsDatachannelCommand() const;

      static const command ABOR() { return cmdABOR; }
      static const command ACCT() { return cmdACCT; }
      static const command ALLO() { return cmdALLO; }
      static const command APPE() { return cmdAPPE; }
      static const command CDUP() { return cmdCDUP; }
      static const command CWD()  { return cmdCWD;  }
      static const command DELE() { return cmdDELE; }
      static const command HELP() { return cmdHELP; }
      static const command LIST() { return cmdLIST; }
      static const command MDTM() { return cmdMDTM; }
      static const command MKD()  { return cmdMKD;  }
      static const command MODE() { return cmdMODE; }
      static const command NLST() { return cmdNLST; }
      static const command NOOP() { return cmdNOOP; }
      static const command OPEN() { return cmdOPEN; }
      static const command PASS() { return cmdPASS; }
      static const command PASV() { return cmdPASV; }
      static const command PORT() { return cmdPORT; }
      static const command PWD()  { return cmdPWD;  }
      static const command QUIT() { return cmdQUIT; }
      static const command REIN() { return cmdREIN; }
      static const command REST() { return cmdREST; }
      static const command RETR() { return cmdRETR; }
      static const command RMD()  { return cmdRMD;  }
      static const command RNFR() { return cmdRNFR; }
      static const command RNTO() { return cmdRNTO; }
      static const command SITE() { return cmdSITE; }
      static const command SIZE_I32() { return cmdSIZE; }
      static const command SMNT() { return cmdSMNT; }
      static const command STAT() { return cmdSTAT; }
      static const command STOR() { return cmdSTOR; }
      static const command STOU() { return cmdSTOU; }
      static const command STRU() { return cmdSTRU; }
      static const command SYST() { return cmdSYST; }
      static const command TYPE() { return cmdTYPE; }
      static const command USER() { return cmdUSER; }
      static const command PROT() { return cmdPROT; }

      class extended_info;
      class info2;
      command(enum_command enDatachannelCmd) : m_enCommand(enDatachannelCmd) {}
      enum_command m_enCommand;
   };


   class command::extended_info : public command::iextended_info
   {
      typedef command::TSpecificationEnum TSpecificationEnum;
      typedef command::enum_type enum_type;
   public:
      extended_info(const string& strServerString, const string& strCompleteServerStringSyntax, ::u32 uNumberOfParameters,
                    ::u32 uNumberOfOptionalParameters, TSpecificationEnum enSpecification, enum_type enType) :
         m_strServerString(strServerString),
         m_strCompleteServerStringSyntax(strCompleteServerStringSyntax),
         m_uNumberOfParameters(uNumberOfParameters),
         m_uNumberOfOptionalParameters(uNumberOfOptionalParameters),
         m_enSpecification(enSpecification),
         m_etype(enType)
      {}

      extended_info(const extended_info& src) :
         m_strServerString(src.m_strServerString),
         m_strCompleteServerStringSyntax(src.m_strCompleteServerStringSyntax),
         m_uNumberOfParameters(src.m_uNumberOfParameters),
         m_uNumberOfOptionalParameters(src.m_uNumberOfOptionalParameters),
         m_enSpecification(src.m_enSpecification),
         m_etype(src.m_etype)
      {
      }

      virtual const string& GetServerString() const override { return m_strServerString; }
      virtual const string& GetCompleteServerStringSyntax() const override { return m_strCompleteServerStringSyntax; }
      virtual ::u32 GetNumberOfParameters() const override { return m_uNumberOfParameters; }
      virtual ::u32 GetNumberOfOptionalParameters() const override { return m_uNumberOfOptionalParameters; }
      virtual TSpecificationEnum GetSpecification() const override { return m_enSpecification; }
      virtual enum_type GetType() const override { return m_etype; }

      const string            m_strServerString;
      const string            m_strCompleteServerStringSyntax;
      const ::u32               m_uNumberOfParameters;
      const ::u32               m_uNumberOfOptionalParameters;
      const TSpecificationEnum m_enSpecification;
      const enum_type          m_etype;

   };


   class CLASS_DECL_CORE command::info2 : private map<enum_command, __pointer(extended_info) >
   {
   public:

      static info2 * g_pTheOneAndOnly;

      info2();

      void insert(enum_command enCommand, const string& strServerString, const string& strCompleteServerStringSyntax, ::u32 uNumberOfParameters,
                  ::u32 uNumberOfOptionalParameters, TSpecificationEnum enSpecification, enum_type enType);

      static info2& GetInstance() { if (g_pTheOneAndOnly == nullptr) g_pTheOneAndOnly = new info2(); return *g_pTheOneAndOnly; }

      static const iextended_info& Get(enum_command enCommand);

   };


   /// @brief Structure for logon information.
   ///
   /// Holds all necessary parameters for logging on a ftp-server.
   /// Includes also the parameters which are needed for firewall logon.
   class CLASS_DECL_CORE logon :
      virtual public ::account::credentials
   {
   public:
      logon();
      logon(const string& strHostname, ::u16 ushHostport=DEFAULT_FTP_PORT, const string& strUsername=ANONYMOUS_USER,
            const string& strPassword="anonymous@user.com", const string& strAccount="");
      logon(const string& strHostname, ::u16 ushHostport, const string& strUsername, const string& strPassword,
            const string& strAccount, const string& strFwHostname, const string& strFwUsername, const string& strFwPassword,
            ::u16 ushFwPort, const firewall_type& crFwType);

      void SetHost(const string& strHostname, ::u16 ushHostport=DEFAULT_FTP_PORT, const string& strUsername=ANONYMOUS_USER,
                   const string& strPassword="anonymous@user.com", const string& strAccount="");

      void SetFirewall(const string& strFwHostname, const string& strFwUsername, const string& strFwPassword,
                       ::u16 ushFwPort, const firewall_type& crFwType);

      void DisableFirewall() { m_FwType = firewall_type::None(); }

      string&       Hostname()    { return m_strHostname;    }
      ::u16               Hostport()   const  { return m_ushHostport;    }
      string&       Username()    { return m_puser->m_strLogin;    }
      string&       Password()    { return m_strPassword;    }
      const string&       Account()    const  { return m_strAccount;     }
      const string&       FwHost()     const  { return m_strFwHostname;  }
      const string&       FwUsername() const  { return m_strFwUsername;  }
      const string&       FwPassword() const  { return m_strFwPassword;  }
      ::u16               FwPort()     const  { return m_ushFwPort;      }
      const firewall_type& FwType()     const  { return m_FwType;         }
      bool           m_bFailedBecauseOfSecurityLevelCanUpgrade;
   private:
      string        m_strHostname;   ///< name or ip-address of the ftp-server
      ::u16         m_ushHostport;   ///< port of the ftp-server
//      string        m_strUsername;   ///< username for ftp-server
//      string        m_strPassword;   ///< password for ftp-server
      string        m_strAccount;    ///< account mostly needed on ftp-servers running on unix/linux
      string        m_strFwHostname; ///< name or ip-address of the firewall
      string        m_strFwUsername; ///< username for firewall
      string        m_strFwPassword; ///< password for firewall
      ::u16         m_ushFwPort;     ///< port of the firewall
      firewall_type  m_FwType;        ///< type of firewall
   };

   /// Holds a response of a ftp-server.
   class CLASS_DECL_CORE reply
   {
      string m_strResponse;

      /// Holds the reply code.
      class code
      {
         char m_szCode[4];
      public:
         code()
         {
            __zero(m_szCode);
         }
         const char * Value() const { return m_szCode; }
         bool Set(const string& strCode)
         {
            if( strCode.length()!=3 ||
                  strCode[0]<'1' || strCode[0]>'5' ||
                  strCode[1]<'0' || strCode[1]>'5' )
            {
               __zero(m_szCode);
               return false;
            }
            strcpy(m_szCode, strCode);
            return true;
         }

         bool IsPositiveReply() const { return IsPositivePreliminaryReply() || IsPositiveCompletionReply() || IsPositiveIntermediateReply(); }
         bool IsNegativeReply() const { return IsTransientNegativeCompletionReply() || IsPermanentNegativeCompletionReply(); }

         bool IsPositivePreliminaryReply() const         { return m_szCode[0] == '1'; }
         bool IsPositiveCompletionReply() const          { return m_szCode[0] == '2'; }
         bool IsPositiveIntermediateReply() const        { return m_szCode[0] == '3'; }
         bool IsTransientNegativeCompletionReply() const { return m_szCode[0] == '4'; }
         bool IsPermanentNegativeCompletionReply() const { return m_szCode[0] == '5'; }

         bool IsRefferingToSyntax() const                      { return m_szCode[1] == '0'; }
         bool IsRefferingToInformation() const                 { return m_szCode[1] == '1'; }
         bool IsRefferingToConnections() const                 { return m_szCode[1] == '2'; }
         bool IsRefferingToAuthenticationAndAccounting() const { return m_szCode[1] == '3'; }
         bool IsRefferingToUnspecified() const                 { return m_szCode[1] == '4'; }
         bool IsRefferingToFileSystem() const                  { return m_szCode[1] == '5'; }
      } m_Code;
   public:
      bool Set(const string& strResponse)
      {
         m_strResponse = strResponse;
         if( m_strResponse.length()>2 )
            return m_Code.Set(m_strResponse.substr(0, 3));
         return false;
      }
      const string& Value() const { return m_strResponse; }
      const code& Code() const { return m_Code; }
   };



} // namespace ftp








