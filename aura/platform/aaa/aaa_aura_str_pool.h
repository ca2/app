#pragma once


class CLASS_DECL_AURA aura_str_pool
{
public:

   const string UifsProtocol = "uifs://";
   const string IfsProtocol = "ifs://";
   const string HttpProtocol = "http://";
   const string HttpsProtocol = "https://";
   const string FsProtocol = "fs://";
   const string Slash = "/";
   const string DoubleBackSlash = "\\\\";
   const string sSystem = "system";
   const string AppCoreDeepfish = "app-core/deepfish_";
   const string ingSysCommand = "syscommand::";
   const string PassthroughUri = "/passthrough/";
   const string MatterUri = "/matter/";
   const string s200Space = "200 ";
   const string WwwDot = "www.";

   const string XMLPIOpen = "<?";
   const string XMLPIClose = "?>";
   const string XMLDOCTYPEOpen = "<!DOCTYPE";
   const string XMLDOCTYPEClose = ">";
   const string XMLCommentOpen = "<!--";
   const string XMLCommentClose = "-->";
   const string XMLCDATAOpen = "<![CDATA[";
   const string XMLCDATAClose = "]]>";

};


namespace aura
{


   extern CLASS_DECL_AURA aura_str_pool* g_paurastrpool;


} // namespace aura


#define astr (*::aura::g_paurastrpool)



