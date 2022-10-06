#include "framework.h"
#include "document.h"
#include "xml.h"
#include "exception.h"


namespace xml
{


   static const char chXMLTagOpen = '<';
   static const char chXMLTagClose = '>';
   static const char chXMLTagPre = '/';
   static const char chXMLEscape = '\\';   // for m_strValue field escape


   document::document(parse_info * pparseinfo, string_to_string * pentitiesHash)
   {

      //m_pdocument            = this;
//      m_pparseinfo      = ::is_set(pparseinfo) ? pparseinfo : get_system()->m_pxml->m_pparseinfoDefault.m_p;
//      m_pentitiesHash   = ::is_set(pentitiesHash) ? pentitiesHash : get_system()->m_pxml->m_pentitiesHashDefault.m_p;
      m_pedit           = nullptr;

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


   //void document::load_location(const char * psz)
   //{

   //   m_pathLocation = psz;
   //   
   //   string str;

   //   auto psystem = m_psystem->m_paurasystem;

   //   str = m_pcontext->m_papexcontext->file().as_string(psz);

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


   void document::create_root(const ::string & strName)
   {

      create_root();

      m_pnodeRoot->set_name(strName);

   }


   void document::initialize(::object * pobject)
   {

      //auto estatus = 
      
      ::object::initialize(pobject);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //estatus = 
      
      node::initialize_matter(pobject);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      if (m_pnodeRoot)
      {

         m_pnodeRoot->initialize_matter(this);

      }

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
//   void document::_load(const char * & xml, const char * pszXml, const char * pszEndXml, parse_info * pparseinfo)
//   {
//
//      // close it
//      close();
//
//      if (pparseinfo == nullptr)
//      {
//
//         pparseinfo = get_system()->xml()->m_pparseinfoDefault;
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
//      const char * ret = nullptr;
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
//      m_pnodeRoot->_load(xml, xml, pszEndXml, pparseinfo);
//
//   }


   void document::ensure_root()
   {

      if (!m_pnodeRoot)
      {

         create_root();

      }

   }


   void document::create_root()
   {

      if (m_pnodeRoot)
      {

         return;

      }

      m_pnodeRoot = __new(class node((node *) this));

      m_pnodeRoot->initialize_matter(this);

      m_nodea.add(m_pnodeRoot.m_p);

   }


   void document::set_name(const ::string & strName)
   {

      ensure_root();

      m_pnodeRoot->set_name(strName);


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
   //void document::parse_xml_text(const char * pszXmlText)
   //{

   //   m_nodea.erase_all();

   //   m_strData1 = pszXmlText;

   //   m_memoryData.assign(m_strData1.c_str(), m_strData1.get_length_in_bytes_with_null_terminator());

   //   const char * pszXml = (const char *) m_memoryData.get_data();

   //   ensure_root();

   //   const char * pszNext = pszXml;

   //   // Load Other Node after </Tag>(pparseinfo, comment, CDATA etc)
   //   const char * pszRet;

   //   bool bRet = false;

   //   pszRet = LoadOtherNodes(&bRet, pszNext, m_pparseinfo);

   //   if (pszRet != nullptr)
   //   {

   //      pszNext = pszRet;

   //   }

   //   if((pszNext = m_pnodeRoot->_load(pszNext, m_pparseinfo )) == nullptr)
   //   {

   //      m_nodea.erase_all();

   //      //m_pnodeRoot.release();

   //      throw ::exception(error_parsing);

   //      //return false;

   //      return;

   //   }

   //   // Load Other Node after </Tag>(pparseinfo, comment, CDATA etc)
   //   //const char * ret;

   //   //bool bRet = false;

   //   pszRet = LoadOtherNodes(&bRet, pszNext, m_pparseinfo);

   //   if (pszRet != nullptr)
   //   {

   //      pszNext = pszRet;

   //   }

   //   //return true;

   //}


   //node * document::get_root() const
   //{

   //   if (!m_pnodeRoot)
   //   {

   //      // Not found: create one.
   //      auto pnodeRoot = __new(::xml::node((document *)this));

   //      pnodeRoot->set_name("root");
   //      pnodeRoot->m_pnodeParent = (node *)this;
   //      pnodeRoot->m_etype = node_element;
   //      pnodeRoot->m_pdocument = ((document *)this);

   //      ((document *)this)->m_pnodeRoot = pnodeRoot;

   //   }

   //   return m_pnodeRoot;

   //}


   string document::consume_entity_ref(const char * & pszXmlParam, string & strName, bool useExtEnt, bool & bExt)
   {

      const char * pszXml = pszXmlParam;

      if(*pszXml == '\0')
      {

         throw ::exception(error_parsing, "No Entity");

      }

      ::str().consume(pszXml, "&");

      strName.Empty();

      while(*pszXml != ';')
      {

         if(*pszXml == '\0'
               || *pszXml == '<'
               || *pszXml == '>'
               || *pszXml == ' '
               || *pszXml == '\n'
               || *pszXml == '\r'
               || *pszXml == ','
               || *pszXml == '.'
               || *pszXml == '=')
         {

            throw ::exception(error_parsing, "Not expected character on Entity Reference");

         }

         strName += *pszXml;

         ::str().increment(pszXml);

      }

      pszXml++;

      string ent = (*m_pentitiesHash)[strName];

      string extEnt;

      if (useExtEnt)
      {

         extEnt = (*m_pentitiesExtHash)[strName];

      }

      if(ent.is_empty() && extEnt.is_empty() && (strName.is_empty() || strName[0] != '#'))
      {

         throw ::exception(error_parsing, "Undefined Entity Reference");

      }

      if(ent.has_char())
      {

         bExt = false;

         pszXmlParam = pszXml;

         return ent;

      }

      if(extEnt.has_char())
      {

         bExt = true;

         pszXmlParam = pszXml;

         return m_pcontext->m_papexcontext->file().as_string(m_pathLocation.sibling(extEnt));

      }

      string strEntityReference(pszXmlParam, pszXml - pszXmlParam);

      if(::str().begins_eat_ci(strEntityReference, "&#"))
      {

         int i = atoi(strEntityReference);

         wchar_t wsz[2];

         wsz[0] = i;
         wsz[1] = L'\0';

         strEntityReference = wsz;

      }

      pszXmlParam = pszXml;

      return strEntityReference;

   }


   // the additional parameter must end with , nullptr
   // the parameters are pointers based on m_strData that should be offset because m_strData will be edited by entity ref patch
   char * document::patch_entity_ref(const char * & pszXml, int bUseExtEnt)
   {

      // pszXml must be a valid portion of and point_i32 to an entity ref in:
      // m_strData of this document

      const char * pszOldData = (const char *) m_memoryData.get_data();

      strsize iPos = pszXml - pszOldData;

      ASSERT(iPos < m_memoryData.get_size() - 1 && iPos >= 0);

      string strName;

      bool bExt = false;

      string strValue = pszXml[0];

      try
      {

         strValue = consume_entity_ref(pszXml, strName, bUseExtEnt, bExt);

      }
      catch(...)
      {

         pszXml++;

      }

      auto iDiff = strValue.get_length() - (strName.get_length() + 2);

      m_memoryData.allocate_add_up(iDiff);

      auto iRight = iPos + strName.get_length() + 2;

      char * pszRight = (char *)m_memoryData.get_data() + iRight;

      memmove(pszRight + iDiff, pszRight, m_memoryData.get_size() - iRight - iDiff);

      memcpy(m_memoryData.get_data() + iPos, strValue, strValue.get_length_in_bytes());

      //m_strData = m_strData.Left(iPos) + strValue + m_strData.Mid(iPos + strName.get_length() + 2);

      return pszRight + iDiff;

   }


   ::stream& document::write(::stream& stream) const
   {

      return node::write(stream);

   }


   ::stream& document::read(::stream& stream)
   {

      return node::read(stream);

   }


} // namespace xml



