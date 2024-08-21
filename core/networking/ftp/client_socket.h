////////////////////////////////////////////////////////////////////////////////
//
// The official specification of the File Transfer Protocol (FTP) is the RFC 959.
// Most of the documentation are taken from this RFC.
// This is an implementation of an simple FTP client. I have tried to implement
// platform independent. For the communication i used the classes blocking_socket,
// address, ... from David J. Kruglinski (Inside Visual C++). These classes are
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
////////////////////////////////////////////////////////////////////////////////

#pragma once


#include "apex/networking/sockets/_sockets.h"
#include "acme/primitive/collection/string_list.h"
#include "acme/primitive/primitive/util.h"

#include "data_types.h"

#include "file_list_parser.h"

#include "file_status.h"

#include "transfer_notification.h"

#include "apex/networking/sockets/basic/tcp_socket.h"

struct tm;

namespace sockets
{

   class transfer_socket;

} // namespace sockets

////////////////////////////////////////////////////////////////////////////////
/// Namespace for all FTP-related classes.
////////////////////////////////////////////////////////////////////////////////
namespace ftp
{

   /// @brief FTP client class
   ///
   /// Use this class for all the FTP client stuff such as
   /// - logon server
   /// - send and receive data
   /// - get directory listing
   /// - File eXchange Protocol (FXP) - uses FTP to transfer data directly from one remote server to another.
   /// - ...
   ///
   class CLASS_DECL_CORE client_socket :
      virtual public ::sockets::tcp_socket
   {
   public:
      class notification;

      class observer_array :
         virtual public ::observer < notification, observer_array>
      {
      public:

      };

      enum enum_state
      {

         e_state_initial,
         state_logged

      };

      e_connection_type                      m_econnectiontype;
      // data members
      //const unsigned int                     mc_uiTimeout;               ///< timeout for socket-functions
      //const unsigned int                     mc_uiResponseWait;          ///< sleep time between receive calls to socket when getting the response
      class ::time                                m_timeTimeout;
      class ::time                                m_timeResponseWait;
      const string                          mc_strEolCharacterSequence; ///< end-of-line sequence of current operating system
      const string                          mc_strRemoteDirectorySeparator; ///< directory separator character which is used on the FTP server

      memory                     m_vBuffer;                  ///< buffer for sending and receiving
      string_list                m_qResponseBuffer;          ///< buffer for server-responses
      ::pointer<representation>        m_apCurrentRepresentation;  ///< representation currently set

      //this class is now a tcp_socket and it is this control connection socket
      //::pointer<::sockets::blocking_socket>        m_apSckControlConnection;   ///< socket for connection to FTP server
      ::pointer<ifile_list_parser>     m_apFileListParser;         ///< object which is used for parsing the result of the LIST command
      bool                       m_fTransferInProgress;      ///< if true, a file transfer is in progress
      bool                       m_fAbortTransfer;           ///< indicates that a running filetransfer should be canceled
      bool                       m_fResumeIfPossible;        ///< try to resume download/upload if possible
      observer_array             m_setObserver;              ///< list of observers, which are notified about particular actions
      ::pointer<logon>          m_plogon;            ///< logon-info, which was used at the last call of login

      enum_state                    m_estate;




      client_socket(
                    const class time & timeTimeout = 10_s, unsigned int uiBufferSize = 2048,
                    const class time & timeResponseWait = 0_s, const string& strRemoteDirectorySeparator = "/");
      virtual ~client_socket();

      virtual long cert_common_name_check(const ::string & common_name) override;

      void AttachObserver(notification* pObserver);
      void DetachObserver(notification* pObserver);
      void SetFileListParser(::pointer<ifile_list_parser>apFileListParser);

      bool _is_connected();
      bool IsTransferringData();
      bool IsResumeModeEnabled();
      void SetResumeMode(bool fEnable = true);

      bool Login(logon * plogon);
      int  Logout();
      const logon * get_logon() const { return m_plogon; }

      bool List(const string& strPath, string_array& vstrFileList, bool fPasv = false);
      bool NameList(const string& strPath, string_array& vstrFileList, bool fPasv = false);

      bool List(const string& strPath, file_status_ptra& vFileList, bool fPasv = false);
      bool NameList(const string& strPath, file_status_ptra& vFileList, bool fPasv = false);

      int  Delete(const string& strFile);
      int  Rename(const string& strOldName, const string& strNewName);
      int  Move(const string& strFullSourceFilePath, const string& strFullTargetFilePath);

      bool DownloadFile(const string& strRemoteFile, itransfer_notification& Observer,
                        const representation& repType = representation(type::Image()), bool fPasv = false);
      bool DownloadFile(const string& strRemoteFile, const string& strLocalFile,
                        const representation& repType = representation(type::Image()), bool fPasv = false);
      bool DownloadFile(const string& strSourceFile, client_socket& TargetFtpServer,
                        const string& strTargetFile, const representation& repType = representation(type::Image()),
                        bool fPasv = true);

      bool UploadFile(itransfer_notification& Observer, const string& strRemoteFile, bool fStoreUnique = false,
                      const representation& repType = representation(type::Image()), bool fPasv = false);
      bool UploadFile(const string& strLocalFile, const string& strRemoteFile, bool fStoreUnique = false,
                      const representation& repType = representation(type::Image()), bool fPasv = false);
      bool UploadFile(client_socket& SourceFtpServer, const string& strSourceFile,
                      const string& strTargetFile, const representation& repType = representation(type::Image()),
                      bool fPasv = true);

      static bool TransferFile(client_socket& SourceFtpServer, const string& strSourceFile,
                               client_socket& TargetFtpServer, const string& strTargetFile,
                               const representation& repType = representation(type::Image()), bool fSourcePasv = false);

      int remove_directory(const string& strDirectory);
      int make_directory(const string& strDirectory);

      int PrintWorkingDirectory();
      int ChangeToParentDirectory();
      int ChangeWorkingDirectory(const string& strDirectory);

      int Passive(::u32& ulIpAddress, ::u16& ushPort);
      int DataPort(const string& strHostIP, ::u16 ushPort);
      int _abort();
      int system();
      int Noop();
      int RepresentationType(const representation& repType, ::u32 dwSize = 0);
      int FileStructure(const structure& crStructure);
      int TransferMode(const transfer_mode& crTransferMode);
      int Allocate(int iReserveBytes, const int* piMaxPageOrRecordSize = nullptr);
      int StructureMount(const string& strPath);
      int SiteParameters(const string& strCmd);
      int Status(const string& strPath);
      int Help(const string& strTopic);

      int Reinitialize();
      int Restart(::u32 dwPosition);

      int FileSize(const string& strPath, long& lSize);
      int FileModificationTime(const string& strPath, struct ::tm& tmModificationTime);
      int FileModificationTime(const string& strPath, string& strModificationTime);

      bool ExecuteDatachannelCommand(const command& crDatachannelCmd, const string& strPath, const representation& representation,
                                     bool fPasv, ::u32 dwByteOffset, itransfer_notification& Observer);

      observer_array& GetObservers();

      int _RepresentationType(const representation& repType, ::u32 dwSize = 0);
      bool TransferData(const command& crDatachannelCmd, itransfer_notification& Observer, ::sockets::transfer_socket & sckDataConnection);
      bool OpenActiveDataConnection(::sockets::socket & sckDataConnection, const command& crDatachannelCmd, const string& strPath, ::u32 dwByteOffset);
      bool OpenPassiveDataConnection(::sockets::socket & sckDataConnection, const command& crDatachannelCmd, const string& strPath, ::u32 dwByteOffset);
      bool SendData(itransfer_notification& Observer, ::sockets::transfer_socket& sckDataConnection);
      bool ReceiveData(itransfer_notification& Observer, ::sockets::transfer_socket& sckDataConnection);

      int  SimpleErrorCheck(const reply& Reply);

      bool SendCommand(const command& Command, const string_array & Arguments);
      bool SendCommand(const command& Command, const string_array & Arguments, reply& Reply);
      bool GetResponse(reply& Reply);
      bool GetSingleResponseLine(string& strResponse);
      void OnLine(const ::string & strLine) override;

      bool OpenControlChannel(const string& strServerHost, ::u16 ushServerPort = DEFAULT_FTP_PORT);
      void CloseControlChannel();

      void ReportError(const string& strErrorMsg, const string& strFile, ::u32 dwLineNr);
      bool GetIpAddressFromResponse(const string& strResponse, ::u32& ulIpAddress, ::u16& ushPort);

   };

   /// @brief interface for notification
   ///
   /// Derive your class from this base-class and register this class on client.
   /// For example you can use this for logging the sended and received commands.
   class client_socket::notification :
      virtual public ::observer < client_socket::observer_array, client_socket::notification>
   {
   public:
      virtual ~notification() {}
      virtual void OnInternalError(const string& /*strErrorMsg*/, const string& /*strFileName*/, ::u32 /*dwLineNr*/) {}

      virtual void OnBeginReceivingData() {}
      virtual void OnEndReceivingData(long /*lReceivedBytes*/) {}
      virtual void OnBytesReceived(const ::memory& /*vBuffer*/, long /*lReceivedBytes*/) {}
      virtual void OnBytesSent(const ::memory& /*vBuffer*/, long /*lSentBytes*/) {}

      virtual void OnPreReceiveFile(const string& /*strSourceFile*/, const string& /*strTargetFile*/, long /*lFileSize*/) {}
      virtual void OnPreSendFile(const string& /*strSourceFile*/, const string& /*strTargetFile*/, long /*lFileSize*/) {}
      virtual void OnPostReceiveFile(const string& /*strSourceFile*/, const string& /*strTargetFile*/, long /*lFileSize*/) {}
      virtual void OnPostSendFile(const string& /*strSourceFile*/, const string& /*strTargetFile*/, long /*lFileSize*/) {}

      virtual void OnSendCommand(const command& /*Command*/, const string_array& /*Arguments*/) {}
      virtual void OnResponse(const reply& /*Reply*/) {}
   };




} // namespace ftp



// FTP commands - Overview

// simple commands
//   CDUP <CRLF>
//   QUIT <CRLF>
//   REIN <CRLF>
//   PASV <CRLF>
//   STOU <CRLF>
//   ABOR <CRLF>
//   PWD  <CRLF>
//   SYST <CRLF>
//   NOOP <CRLF>
//   PORT <SP> <host-port> <CRLF>
//   TYPE <SP> <type-code> <CRLF>
//   CWD  <SP> <pathname> <CRLF>
//   MKD  <SP> <pathname> <CRLF>
//   SITE <SP> <string> <CRLF>
//   HELP [<SP> <string>] <CRLF>
//   DELE <SP> <pathname> <CRLF>
//   RMD  <SP> <pathname> <CRLF>
//   STRU <SP> <structure-code> <CRLF>
//   MODE <SP> <mode-code> <CRLF>
//   STAT [<SP> <pathname>] <CRLF>
//   ALLO <SP> <decimal-integer>
//       [<SP> R <SP> <decimal-integer>] <CRLF>
//   SMNT <SP> <pathname> <CRLF>

// commands for logon sequence
//   USER <SP> <username> <CRLF>
//   PASS <SP> <password> <CRLF>
//   ACCT <SP> <account-information> <CRLF>

// commands for renaming
//   RNFR <SP> <pathname> <CRLF>
//   RNTO <SP> <pathname> <CRLF>

//   RETR <SP> <pathname> <CRLF>
//   STOR <SP> <pathname> <CRLF>
//   APPE <SP> <pathname> <CRLF>
//   REST <SP> <marker> <CRLF>
//   LIST [<SP> <pathname>] <CRLF>
//   NLST [<SP> <pathname>] <CRLF>

// non RFC-Commands
//   const size_i32 & <SP> <pathname> <CRLF>
//   MDTM <SP> <pathname> <CRLF>

/** \class nsFTP::structure
In addition to different representation types, FTP allows the
structure of a file to be specified.  Three file structures are
defined in FTP:

- file-structure,     where there is no internal structure and
the file is considered to be a
continuous sequence of data bytes,

- record-structure,   where the file is made up of sequential
records,

- and page-structure, where the file is made up of independent
indexed pages.

File-structure is the default to be assumed if the STRUcture
command has not been used but both file and record structures
must be accepted for "text" files (i.e., files with TYPE ASCII
or EBCDIC) by all FTP implementations.  The structure of a file
will affect both the transfer mode of a file (see the Section
on Transmission Modes) and the interpretation and storage of
the file.

The "natural" structure of a file will depend on which host
stores the file.  A source-code file will usually be stored on
an IBM Mainframe in fixed length records but on a DEC TOPS-20
as a stream of characters partitioned into lines, for example
by <CRLF>.  If the transfer of files between such disparate
sites is to be useful, there must be some way for one site to
recognize the other's assumptions about the file.

With some sites being naturally file-oriented and others
naturally record-oriented there may be problems if a file with
one structure is sent to a host oriented to the other.  If a
text file is sent with record-structure to a host which is file
oriented, then that host should apply an internal
transformation to the file based on the record structure.
Obviously, this transformation should be useful, but it must
also be invertible so that an identical file may be retrieved
using record structure.

In the case of a file being sent with file-structure to a
record-oriented host, there exists the question of what
criteria the host should use to divide the file into records
which can be processed locally.  If this division is necessary,
the FTP implementation should use the end-of-line sequence,

<CRLF> for ASCII, or <NL> for EBCDIC text files, as the
delimiter.  If a FTP implementation adopts this technique, it
must be prepared to reverse the transformation if the file is
retrieved with file-structure.
*/

/** \fn static const structure nsFTP::structure::File()
File structure is the default to be assumed if the STRUcture
command has not been used.
In file-structure there is no internal structure and the
file is considered to be a continuous sequence of data
bytes.
*/
/** \fn static const structure nsFTP::structure::Record()
Record structures must be accepted for "text" files (i.e.,
files with TYPE ASCII or EBCDIC) by all FTP implementations.
In record-structure the file is made up of sequential
records.
*/
/** \fn static const structure nsFTP::structure::Page()
To transmit files that are discontinuous, FTP defines a page
structure.  Files of this type are sometimes known as
"random access files" or even as "holey files".  In these
files there is sometimes other information associated with
the file as a whole (e.g., a file descriptor), or with a
section of the file (e.g., page access controls), or both.
In FTP, the sections of the file are called pages.

To provide for various page sizes and associated
information, each page is sent with a page header.  The page
header has the following defined fields:

- Header Length\n
The number of logical bytes in the page header
including this ::u8.  The minimum header length is 4.

- Page Index\n
The logical page number of this section of the file.
This is not the transmission sequence number of this
page, but the index used to identify this page of the
file.

- Data Length\n
The number of logical bytes in the page data.  The
minimum data length is 0.

- Page Type\n
The type of page this is.  The following page types
are defined:

<PRE>         0 = Last Page
This is used to indicate the end of a paged
structured transmission.  The header length must
be 4, and the data length must be 0.

1 = Simple Page
This is the normal type for simple paged files
with no page level associated control
information.  The header length must be 4.

2 = Descriptor Page
This type is used to transmit the descriptive
information for the file as a whole.

3 = Access Controlled Page
This type includes an additional header field
for paged files with page level access control
information.  The header length must be 5.</PRE>

- Optional Fields\n
Further header fields may be used to supply per page
control information, for example, per page access
control.

All fields are one logical ::u8 in length.  The logical ::u8
size_i32 is specified by the TYPE command.  See Appendix I for
further details and a specific case at the page structure.

A note of caution about parameters:  a file must be stored and
retrieved with the same parameters if the retrieved version is to

be identical to the version originally transmitted.  Conversely,
FTP implementations must return a file identical to the original
if the parameters used to store and retrieve a file are the same.
*/

/** \class nsFTP::transfer_mode
The next consideration in transferring data is choosing the
appropriate transmission mode.  There are three modes: one which
formats the data and allows for restart procedures; one which also
compresses the data for efficient transfer; and one which passes
the data with little or no processing.  In this last case the mode
interacts with the structure attribute to determine the type of
processing.  In the compressed mode, the representation type
determines the filler ::u8.

All data transfers must be completed with an end-of-file (EOF)
which may be explicitly stated or implied by the closing of the
data connection.  For files with record structure, all the
end-of-record markers (EOR) are explicit, including the final one.
For files transmitted in page structure a "last-page" page type is
used.

NOTE:  In the rest of this section, ::u8 means "transfer ::u8"
except where explicitly stated otherwise.

For the purpose of standardized transfer, the sending host will
translate its internal end of line or end of record denotation
into the representation prescribed by the transfer mode and file
structure, and the receiving host will perform the inverse
translation to its internal denotation.  An IBM Mainframe record
count field may not be recognized at another host, so the
end-of-record information may be transferred as a two ::u8 control
code in Stream mode or as a flagged bit in a Block or Compressed
mode descriptor.  End-of-line in an ASCII or EBCDIC file with no
record structure should be indicated by <CRLF> or <NL>,
respectively.  Since these transformations imply extra work for
some systems, identical systems transferring non-record structured
text files might wish to use a binary representation and stream
mode for the transfer.
*/

/** \fn static const transfer_mode nsFTP::transfer_mode::Stream()
The data is transmitted as a stream of bytes.  There is no
restriction on the representation type used; record structures
are allowed.

In a record structured file EOR and EOF will each be indicated
by a two-::u8 control code.  The first ::u8 of the control code
will be all ones, the escape character.  The second ::u8 will
have the low order bit on and zeros elsewhere for EOR and the
second low order bit on for EOF; that is, the ::u8 will have
value 1 for EOR and value 2 for EOF.  EOR and EOF may be
indicated together on the last ::u8 transmitted by turning both
low order bits on (i.e., the value 3).  If a ::u8 of all ones
was intended to be sent as data, it should be repeated in the
second ::u8 of the control code.

If the structure is a file structure, the EOF is indicated by
the sending host closing the data connection and all bytes are
data bytes.
*/

/** \fn static const transfer_mode nsFTP::transfer_mode::Block()
The file is transmitted as a series of data blocks preceded by
one or more header bytes.  The header bytes contain a count
field, and descriptor code.  The count field indicates the
total length of the data block in bytes, thus marking the
beginning of the next data block (there are no filler bits).
The descriptor code defines:  last block in the file (EOF) last
block in the record (EOR), restart marker (see the Section on
Error Recovery and Restart) or suspect data (i.e., the data
being transferred is suspected of errors and is not reliable).
This last code is NOT intended for error control within FTP.
It is motivated by the desire of sites exchanging certain types
of data (e.g., seismic or weather data) to send and receive all
the data despite local errors (such as "magnetic tape read
errors"), but to indicate in the transmission that certain
portions are suspect).  Record structures are allowed in this
mode, and any representation type may be used.

The header consists of the three bytes.  Of the 24 bits of
header information, the 16 low order bits shall represent ::u8
count, and the 8 high order bits shall represent descriptor
codes as shown below.

Block Header
<PRE>
+----------------+----------------+----------------+
| Descriptor     |    Byte Count                   |
|         8 bits |                      16 bits    |
+----------------+----------------+----------------+
</PRE>
The descriptor codes are indicated by bit flags in the
descriptor ::u8.  Four codes have been assigned, where each
code number is the decimal value of the corresponding bit in
the ::u8.
<PRE>
Code     Meaning

128     End of data block is EOR
64     End of data block is EOF
32     Suspected errors in data block
16     Data block is a restart marker
</PRE>
With this encoding, more than one descriptor coded condition
may exist for a particular block.  As many bits as necessary
may be flagged.

The restart marker is embedded in the data stream as an
integral number of 8-bit bytes representing printable
characters in the language being used over the control
connection (e.g., default--NVT-ASCII).  <SP> (Space, in the
appropriate language) must not be used WITHIN a restart marker.

For example, to transmit a six-character marker, the following
would be sent:
<PRE>
+--------+--------+--------+
|Descrptr|  Byte count     |
|code= 16|             = 6 |
+--------+--------+--------+

+--------+--------+--------+
| Marker | Marker | Marker |
| 8 bits | 8 bits | 8 bits |
+--------+--------+--------+

+--------+--------+--------+
| Marker | Marker | Marker |
| 8 bits | 8 bits | 8 bits |
+--------+--------+--------+
</PRE>
*/

/** \fn static const transfer_mode nsFTP::transfer_mode::Compressed()
There are three kinds of information to be sent:  regular data,
sent in a ::u8 string; compressed data, consisting of
replications or filler; and control information, sent in a
two-::u8 escape sequence.  If n>0 bytes (up to 127) of regular
data are sent, these n bytes are preceded by a ::u8 with the
left-most bit set to 0 and the right-most 7 bits containing the
number n.

Byte string:
<PRE>
1       7                8                     8
+-+-+-+-+-+-+-+-+ +-+-+-+-+-+-+-+-+     +-+-+-+-+-+-+-+-+
|0|       n     | |    d(1)       | ... |      d(n)     |
+-+-+-+-+-+-+-+-+ +-+-+-+-+-+-+-+-+     +-+-+-+-+-+-+-+-+
^             ^
|---n bytes---|
of data
</PRE>
String of n data bytes d(1),..., d(n)
Count n must be positive.

To compress a string of n replications of the data ::u8 d, the
following 2 bytes are sent:

Replicated Byte:
<PRE>
2       6               8
+-+-+-+-+-+-+-+-+ +-+-+-+-+-+-+-+-+
|1 0|     n     | |       d       |
+-+-+-+-+-+-+-+-+ +-+-+-+-+-+-+-+-+
</PRE>
A string of n filler bytes can be compressed into a single
::u8, where the filler ::u8 varies with the representation
type.  If the type is ASCII or EBCDIC the filler ::u8 is <SP>
(Space, ASCII code 32, EBCDIC code 64).  If the type is Image
or Local ::u8 the filler is a zero ::u8.

Filler String:
<PRE>
2       6
+-+-+-+-+-+-+-+-+
|1 1|     n     |
+-+-+-+-+-+-+-+-+
</PRE>
The escape sequence is a double ::u8, the first of which is the
escape ::u8 (all zeros) and the second of which contains
descriptor codes as defined in Block mode.  The descriptor
codes have the same meaning as in Block mode and apply to the
succeeding string of bytes.

Compressed mode is useful for obtaining increased bandwidth on
very large network transmissions at a little extra CPU cost.
It can be most effectively used to reduce the size_i32 of printer
files such as those generated by RJE hosts.
*/

/** \class nsFTP::representation
DATA REPRESENTATION AND STORAGE

Data is transferred from a storage device in the sending host to a
storage device in the receiving host.  Often it is necessary to
perform certain transformations on the data because data storage
representations in the two systems are different.  For example,
NVT-ASCII has different data storage representations in different
systems.  DEC TOPS-20s's generally store NVT-ASCII as five 7-bit
ASCII characters, left-justified in a 36-bit word. IBM Mainframe's
store NVT-ASCII as 8-bit EBCDIC codes.  Multics stores NVT-ASCII
as four 9-bit characters in a 36-bit word.  It is desirable to
convert characters into the standard NVT-ASCII representation when
transmitting text between dissimilar systems.  The sending and
receiving sites would have to perform the necessary
transformations between the standard representation and their
internal representations.

A different problem in representation arises when transmitting
binary data (not character codes) between host systems with
different word lengths.  It is not always clear how the sender
should send data, and the receiver store it.  For example, when
transmitting 32-bit bytes from a 32-bit word-length system to a
36-bit word-length system, it may be desirable (for reasons of
efficiency and usefulness) to store the 32-bit bytes
right-justified in a 36-bit word in the latter system.  In any
case, the user should have the option of specifying data
representation and transformation functions.  It should be noted

that FTP provides for very limited data type representations.
Transformations desired beyond this limited capability should be
performed by the user directly.

Several types take a second parameter. The first parameter is
denoted by a single Telnet character, as is the second
Format parameter for ASCII and EBCDIC; the second parameter
for local ::u8 is a decimal integer to indicate Bytesize.
The parameters are separated by a <SP> (Space, ASCII code
32).

The following codes are assigned for type:
<PRE>
\    /
A - ASCII |    | N - Non-print
|-><-| T - Telnet format effectors
E - EBCDIC|    | C - Carriage Control (ASA)
/    \
I - Image

L <::u8 size_i32> - Local ::u8 Byte size_i32
</PRE>
The default representation type is ASCII Non-print.  If the
Format parameter is changed, and later just the first
argument is changed, Format then returns to the Non-print
default.
*/

/** \class nsFTP::type
Objects of this class are only used in conjunction with representation.

DATA TYPES

Data representations are handled in FTP by a user specifying a
representation type.  This type may implicitly (as in ASCII or
EBCDIC) or explicitly (as in Local ::u8) define a ::u8 size_i32 for
interpretation which is referred to as the "logical ::u8 size."
Note that this has nothing to do with the ::u8 size_i32 used for
transmission over the data connection, called the "transfer
::u8 size_i32", and the two should not be confused.  For example,
NVT-ASCII has a logical ::u8 size_i32 of 8 bits.  If the type is
Local ::u8, then the TYPE command has an obligatory second
parameter specifying the logical ::u8 size.  The transfer ::u8
size_i32 is always 8 bits.
*/

/** \fn static const type nsFTP::type::ASCII()
This is the default type and must be accepted by all FTP
implementations.  It is intended primarily for the transfer
of text files, except when both hosts would find the EBCDIC
type more convenient.

The sender converts the data from an internal character
representation to the standard 8-bit NVT-ASCII
representation (see the Telnet specification).  The receiver
will convert the data from the standard form to his own
internal form.

In accordance with the NVT standard, the <CRLF> sequence
should be used where necessary to denote the end of a line
of text.  (See the discussion of file structure at the end
of the Section on Data Representation and Storage.)

Using the standard NVT-ASCII representation means that data
must be interpreted as 8-bit bytes.

The Format parameter for ASCII and EBCDIC types is discussed
below.
*/

/** \fn static const type nsFTP::type::EBCDIC()
This type is intended for efficient transfer between hosts
which use EBCDIC for their internal character
representation.

For transmission, the data are represented as 8-bit EBCDIC
characters.  The character code is the only difference
between the functional specifications of EBCDIC and ASCII
types.

End-of-line (as opposed to end-of-record--see the discussion
of structure) will probably be rarely used with EBCDIC type
for purposes of denoting structure, but where it is
necessary the <NL> character should be used.
*/

/** \fn static const type nsFTP::type::Image()
The data are sent as contiguous bits which, for transfer,
are packed into the 8-bit transfer bytes.  The receiving
site must store the data as contiguous bits.  The structure
of the storage system might necessitate the padding of the
file (or of each record, for a record-structured file) to
some convenient boundary (::u8, word or block).  This
padding, which must be all zeros, may occur only at the end
of the file (or at the end of each record) and there must be
a way of identifying the padding bits so that they may be
stripped off if the file is retrieved.  The padding
transformation should be well publicized to enable a user to
process a file at the storage site.

Image type is intended for the efficient storage and
retrieval of files and for the transfer of binary data.  It
is recommended that this type be accepted by all FTP
implementations.
*/

/** \fn static const type nsFTP::type::LocalByte()
The data is transferred in logical bytes of the size_i32
specified by the obligatory second parameter, Byte size.
The value of Byte size_i32 must be a decimal integer; there is
no default value.  The logical ::u8 size_i32 is not necessarily
the same as the transfer ::u8 size.  If there is a
difference in ::u8 sizes, then the logical bytes should be
packed contiguously, disregarding transfer ::u8 boundaries
and with any necessary padding at the end.

When the data reaches the receiving host, it will be
transformed in a manner dependent on the logical ::u8 size_i32
and the particular host.  This transformation must be
invertible (i.e., an identical file can be retrieved if the
same parameters are used) and should be well publicized by
the FTP implementors.

For example, a user sending 36-bit floating-point_i32 numbers to
a host with a 32-bit word could send that data as Local ::u8
with a logical ::u8 size_i32 of 36.  The receiving host would
then be expected to store the logical bytes so that they
could be easily manipulated; in this example putting the
36-bit logical bytes into 64-bit double words should
suffice.

In another example, a pair of hosts with a 36-bit word size_i32
may send data to one another in words by using TYPE L 36.
The data would be sent in the 8-bit transmission bytes
packed so that 9 transmission bytes carried two host words.
*/

/** \class nsFTP::CTypeFormat
Objects of this class are only used in conjunction with representation.

FORMAT CONTROL

The types ASCII and EBCDIC also take a second (optional)
parameter; this is to indicate what kind of vertical format
control, if any, is associated with a file.  The following
data representation types are defined in FTP:

A character file may be transferred to a host for one of
three purposes: for printing, for storage and later
retrieval, or for processing.  If a file is sent for
printing, the receiving host must know how the vertical
format control is represented.  In the second case, it must
be possible to store a file at a host and then retrieve it
later in exactly the same form.  Finally, it should be
possible to transfer a file from one host to another and process
the file at the second host without undue trouble.  A single
ASCII or EBCDIC format does not satisfy all these
conditions.  Therefore, these types have a second parameter
specifying one of the following three formats:
*/

/** \fn static const CTypeFormat nsFTP::CTypeFormat::NonPrint()
NON PRINT

This is the default format to be used if the second
(format) parameter is omitted.  Non-print format must be
accepted by all FTP implementations.

The file need contain no vertical format information.  If
it is passed to a printer process, this process may
assume standard values for spacing and margins.

Normally, this format will be used with files destined
for processing or just storage.
*/

/** \fn static const CTypeFormat nsFTP::CTypeFormat::TelnetFormat()
TELNET FORMAT CONTROLS

The file contains ASCII/EBCDIC vertical format controls
(i.e., <CR>, <LF>, <NL>, <VT>, <FF>) which the printer
process will interpret appropriately.  <CRLF>, in exactly
this sequence, also denotes end-of-line.
*/

/** \fn static const CTypeFormat nsFTP::CTypeFormat::CarriageControl()
CARRIAGE CONTROL (ASA)

The file contains ASA (FORTRAN) vertical format control
characters.  (See RFC 740 Appendix C; and Communications
of the ACM, Vol. 7, No. 10, point. 606, October 1964.)  In a
line or a record formatted according to the ASA Standard,
the first character is not to be printed.  Instead, it
should be used to determine the vertical movement of the
paper which should take place before the rest of the
record is printed.

The ASA Standard specifies the following control
characters:

Character     Vertical Spacing

blank         Move paper up one line
0             Move paper up two lines
1             Move paper to top of next page
+             No movement, i.e., overprint

Clearly there must be some way for a printer process to
distinguish the end of the structural entity.  If a file
has record structure (see below) this is no problem;
records will be explicitly marked during transfer and
storage.  If the file has no record structure, the <CRLF>
end-of-line sequence is used to separate printing lines,
but these format effectors are overridden by the ASA
controls.
*/

