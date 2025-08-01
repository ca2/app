#include "framework.h"
#include "document.h"
#include "xml.h"
#include "exception.h"
#include "acme/exception/interface_only.h"
#include "acme/exception/parsing.h"
#include "acme/prototype/string/str.h"
#include "apex/platform/context.h"
#include "acme/filesystem/filesystem/file_context.h"


namespace xml
{


   static const char chXMLTagOpen = '<';
   static const char chXMLTagClose = '>';
   static const char chXMLTagPre = '/';
   static const char chXMLEscape = '\\';   // for m_strValue field escape


   document::document(parse_info * pparseinfo, string_to_string * pentitiesHash)
      //m_pparseinfo(pparseinfo),
      //m_pentitiesHash
   {

      m_pdocument            = this;
//      m_pparseinfo      = ::is_set(pparseinfo) ? pparseinfo : system()->m_pxml->m_pparseinfoDefault.m_p;
//      m_pentitiesHash   = ::is_set(pentitiesHash) ? pentitiesHash : system()->m_pxml->m_pentitiesHashDefault.m_p;
      //m_pedit           = nullptr;

   }


   document::~document()
   {

   }


   document & document::operator = (const document & document)
   {

      throw ::interface_only();

      return *this;

      //if (this == &document)
      //{

      //   return *this;
      //*get_root() = *document.get_root();
      //return *this;

   }


   //void document::load_location(const ::ansi_character * psz)
   //{

   //   m_pathLocation = psz;
   //   
   //   string str;

   //   auto psystem = system();

   //   str = file()->as_string(scopedstr);

   //   load(str);

   //}

   
   //void document::parse_xml_text(stream & s)
   //{

   //   memory memory;

   //   s.read(memory);

   //   string str;

   //   str = memory.get_string();

   //   load(str);

   //}


   void document::create_root(const ::scoped_string & scopedstrName)
   {

      create_root();

      root()->set_name(scopedstrName);

   }


   void document::initialize(::particle * pparticle)
   {

      //auto estatus = 
      
      node::initialize(pparticle);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //estatus = 
      
      //node::initialize_matter(pparticle);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //if (root())
      //{

      //   root()->initialize_matter(this);

      //}

      //return estatus;

   }

//   // <TAG attr1="value1" attr2='value2' attr3=value3 >
//// </TAG>
//// or
//// <TAG />
////        ^- return pointer
////========================================================
//// Name   : Load
//// Desc   : load xml plain text
//// Param  : pszXml - plain xml text
////          pparseinfo = parser information
//// Return : advanced string pointer  (error return nullptr)
////--------------------------------------------------------
//// Coder    Date                      Desc
//// bro      2002-10-29
////========================================================
//   void document::_load(const_char_pointer  & xml, const ::ansi_character * pszXml, const ::ansi_character * pszEndXml, parse_info * pparseinfo)
//   {
//
//      // close it
//      close();
//
//      if (pparseinfo == nullptr)
//      {
//
//         pparseinfo = system()->xml()->m_pparseinfoDefault;
//
//      }
//
//      xml = pszXml;
//
//      xml = strchr(xml, chXMLTagOpen);
//      if (xml == nullptr)
//         return;
//
//      // close Tag
//      if (*(xml + 1) == chXMLTagPre) // </close
//         return;
//
//      // Load Other Node before <Tag>(pparseinfo, comment, CDATA etc)
//      bool bRet = false;
//      const_char_pointer  ret = nullptr;
//      ret = LoadOtherNodes(&bRet, xml, pparseinfo);
//      if (ret != nullptr)
//         xml = ret;
//      if (bRet)
//      {
//       
//         return;
//
//      }
//
//      create_root();
//
//      root()->_load(xml, xml, pszEndXml, pparseinfo);
//
//   }


   void document::ensure_root()
   {

      if (!root())
      {

         create_root();

      }

   }


   void document::create_root()
   {

      if (root())
      {

         return;

      }

      auto pnode = __allocate class node ((node *) this);

      m_nodea.add(pnode);

      m_iFirstXmlNode = m_nodea.get_upper_bound();

      //root()->initialize_matter(this);


   }


   void document::set_name(const ::scoped_string & scopedstrName)
   {

      ensure_root();

      root()->set_name(scopedstrName);


   }


   //// <?xml version='1.0'?>
   //// <TAG attr1="value1" attr2='value2' attr3=value3 >
   //// </TAG>
   //// or
   //// <TAG />
   ////        ^- return pointer
   ////========================================================
   //// Name   : Load
   //// Desc   : load xml plain text for xml document
   //// Param  : pszXml - plain xml text
   ////          pparseinfo = parser information
   //// Return : advanced string pointer  (error return nullptr)
   ////--------------------------------------------------------
   //// Coder    Date                      Desc
   //// bro      2002-10-29
   ////========================================================
   //void document::parse_xml_text(const ::ansi_character * pszXmlText)
   //{

   //   m_nodea.erase_all();

   //   m_strData1 = pszXmlText;

   //   m_memoryData.assign(m_strData1.c_str(), m_strData1.get_length_in_bytes_with_null_terminator());

   //   const ::ansi_character * pszXml = (const_char_pointer ) m_memoryData.data();

   //   ensure_root();

   //   const ::ansi_character * pszNext = pszXml;

   //   // Load Other Node after </Tag>(pparseinfo, comment, CDATA etc)
   //   const ::ansi_character * pszRet;

   //   bool bRet = false;

   //   pszRet = LoadOtherNodes(&bRet, pszNext, m_pparseinfo);

   //   if (scopedstrRet != nullptr)
   //   {

   //      pszNext = pszRet;

   //   }

   //   if((scopedstrNext = root()->_load(scopedstrNext, m_pparseinfo )) == nullptr)
   //   {

   //      m_nodea.erase_all();

   //      //root().release();

   //      throw ::exception(error_parsing);

   //      //return false;

   //      return;

   //   }

   //   // Load Other Node after </Tag>(pparseinfo, comment, CDATA etc)
   //   //const_char_pointer  ret;

   //   //bool bRet = false;

   //   pszRet = LoadOtherNodes(&bRet, pszNext, m_pparseinfo);

   //   if (scopedstrRet != nullptr)
   //   {

   //      pszNext = pszRet;

   //   }

   //   //return true;

   //}


   //node * document::get_root() const
   //{

   //   if (!root())
   //   {

   //      // Not found: create one.
   //      auto pnodeRoot = __allocate ::xml::node((document *)this);

   //      pnodeRoot->set_name("root");
   //      pnodeRoot->m_pnodeParent = (node *)this;
   //      pnodeRoot->m_etype = node_element;
   //      pnodeRoot->m_pdocument = ((document *)this);

   //      ((document *)this)->root() = pnodeRoot;

   //   }

   //   return root();

   //}


   string document::consume_entity_ref(::ansi_range & rangeXmlParam, string & strName, bool useExtEnt, bool & bExt, ::platform::context * pacmecontext)
   {

      auto rangeXml = rangeXmlParam;

      if(*rangeXml.m_begin == '\0' || rangeXml.is_empty())
      {

         throw ::parsing_exception("No Entity");

      }

      rangeXml.consume("&");

      //strName.empty();

      auto pszStart = rangeXml.m_begin;

      while(*rangeXml.m_begin != ';')
      {

         if(*rangeXml.m_begin == '\0'
            || rangeXml.is_empty()
               || *rangeXml.m_begin == '<'
               || *rangeXml.m_begin == '>'
               || *rangeXml.m_begin == ' '
               || *rangeXml.m_begin == '\n'
               || *rangeXml.m_begin == '\r'
               || *rangeXml.m_begin == ','
               || *rangeXml.m_begin == '.'
               || *rangeXml.m_begin == '=')
         {

            throw ::parsing_exception("Not expected character on Entity Reference");

         }

         unicode_increment(rangeXml.m_begin);

      }

      strName.assign(pszStart, rangeXml.m_begin - pszStart);

      rangeXml.m_begin++;

      string ent = (*m_pentitiesHash)[strName];

      string extEnt;

      if (useExtEnt)
      {

         extEnt = (*m_pentitiesExtHash)[strName];

      }

      if(ent.is_empty() && extEnt.is_empty() && (strName.is_empty() || strName[0] != '#'))
      {

         throw ::parsing_exception("Undefined Entity Reference");

      }

      if(ent.has_character())
      {

         bExt = false;

         //pszXmlParam = pszXml;

         return ent;

      }

      if(extEnt.has_character())
      {

         bExt = true;

         //pszXmlParam = pszXml;

         return pacmecontext->file()->as_string(m_pathLocation.sibling(extEnt));

      }

      string strEntityReference(rangeXmlParam.m_begin, rangeXml.m_begin - rangeXmlParam.m_begin);

      if(strEntityReference.case_insensitive_begins_eat("&#"))
      {

         int i = atoi(strEntityReference);

         wchar_t wsz[2];

         wsz[0] = i;
         wsz[1] = L'\0';

         strEntityReference = wsz;

      }

      rangeXmlParam.m_begin = rangeXml.m_begin;

      return strEntityReference;

   }


   // the additional parameter must end with , nullptr
   // the parameters are pointers based on m_strData that should be offset because m_strData will be edited by entity ref patch
   char * document::patch_entity_ref(::ansi_range & rangeXml, int bUseExtEnt, ::platform::context * pacmecontext)
   {

      // pszXml must be a valid portion of and int_point to an entity ref in:
      // m_strData of this document

      const ::ansi_character * pszOldData = (const_char_pointer ) m_memoryData.data();

      character_count iPos = rangeXml.m_begin - pszOldData;

      ASSERT(iPos < m_memoryData.size() - 1 && iPos >= 0);

      string strName;

      bool bExt = false;

      string strValue = rangeXml.m_begin[0];

      try
      {

         strValue = consume_entity_ref(rangeXml, strName, bUseExtEnt, bExt, pacmecontext);

      }
      catch(...)
      {

         rangeXml.m_begin++;

      }

      auto iDiff = strValue.length() - (strName.length() + 2);

      m_memoryData.allocate_add_up(iDiff);

      auto iRight = iPos + strName.length() + 2;

      char * pszRight = (char *)m_memoryData.data() + iRight;

      memory_transfer(pszRight + iDiff, pszRight, m_memoryData.size() - iRight - iDiff);

      memory_copy(m_memoryData.data() + iPos, strValue, strValue.length_in_bytes());

      //m_strData = m_strData.left(iPos) + strValue + m_strData.substr(iPos + strName.length() + 2);

      return pszRight + iDiff;

   }


   //::stream& document::write(::stream& stream) const
   //{

   //   return node::write(stream);

   //}


   //::stream& document::read(::stream& stream)
   //{

   //   return node::read(stream);

   //}


} // namespace xml



