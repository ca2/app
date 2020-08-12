#include "framework.h"
#include "aura/xml/_.h"
#include "aura/astr.h"

// https://www.codeproject.com/Articles/3426/XMLite-simple-XML-parser

namespace xml
{

   static const CHAR chXMLTagOpen      = '<';
   static const CHAR chXMLTagClose   = '>';
   static const CHAR chXMLTagPre   = '/';
   static const CHAR chXMLEscape = '\\';   // for m_strValue field escape


   node::node()
   {

      m_pnodeParent           = nullptr;
      m_pdocument                  = nullptr;
      m_etype                 = node_document;

   }


   node::node(::xml::node * pnodeParent)
   {

      m_pnodeParent           = pnodeParent;
      m_pdocument                  = pnodeParent->m_pdocument;
      m_etype                 = node_element;

   }


   node::node(const node & node) 
   {

      operator = (node);

   }


   node::~node()
   {

      close();

   }


   node & node::operator = (const node & node)
   {

      __throw(unexpected_situation());

      //if(&node == this)
      //   return *this;

      //m_strName   = node.m_strName;
      //m_strValue  = node.m_strValue;
      //m_nodea     = node.m_nodea;
      //m_pset      = __new(property_node.m_attra;

      return *this;

   }


   //var node::attr(const char * pcszName)
   //{

   //   return set(pcszName);

   //}


   //bool node::get_attr(const char * pcszName, string & strValue)

   //{
   //   if(!m_attra.has_property(pcszName))

   //      return false;
   //   strValue = m_attra[pcszName];

   //   return true;
   //}

   //bool node::get_attr(const char * pcszName, i32 & iValue)

   //{
   //   if(!m_attra.has_property(pcszName))

   //      return false;
   //   iValue = m_attra[pcszName];

   //   return true;
   //}

   //bool node::get_attr(const char * pcszName, bool & bValue)

   //{
   //   if(!m_attra.has_property(pcszName))

   //      return false;
   //   bValue = m_attra[pcszName];

   //   return true;
   //}


   //bool node::contains(const property_set & set) const
   //{

   //   return propset().contains(set);

   //}


   property * node::set_attribute(const ::id & id, const var & var)
   {

      auto & property = m_set.get(id);

      property = var;

      if(::is_set(m_pdocument))
      {

         if(::is_set(m_pdocument->m_pedit))
         {

            m_pdocument->m_pedit->set_attribute(this, &property);

         }

      }

      return &property;

   }


   index node::find(const char * pcszName, const property_set & set, index iStart)
   {

      for(index i = iStart; i < m_nodea.get_count(); i++)
      {

         if (m_nodea[i]->m_strName == pcszName && m_nodea[i]->contains(set))
         {

            return i;

         }

      }

      return -1;

   }


   node * node::get_child_with_attribute(const char * pcszName, const ::id & id, const ::var & var, index iStart)
   {

      for(index i = iStart; i < m_nodea.get_count(); i++)
      {

         if (m_nodea[i]->m_strName == pcszName && m_nodea[i]->attribute(id) == var)
         {

            return m_nodea.element_at(i);

         }

      }

      return nullptr;

   }


   index node::find(const char * pcszName, index iStart)
   {

      for(index i = iStart; i < m_nodea.get_count(); i++)
      {

         if (m_nodea[i]->m_strName == pcszName)
         {

            return i;

         }

      }

      return -1;

   }


   /*
   bool node::Contains(attr_array & attributea)
   {
      return GetAttributeArray().Contains(attributea);
   }
   */
   /*
   node & node::FindNode(const char * pcszName,i32 iPos)

   {
      return GetChildNodeArray().find(pcszName, iPos);

   }
   */
   index node::find(node * pnode)
   {
      return m_nodea.find_first(pnode);
   }

   node * node::get_next_sibling()
   {
      if(m_pnodeParent == nullptr)
         return nullptr;
      index i = m_pnodeParent->find(this);
      if(i < 0)
         __throw(::exception::exception("strange: this is not child of this->parent"));
      i++;
      if(i >= m_pnodeParent->get_children_count())
         return nullptr;
      return m_pnodeParent->child_at(i);
   }

   node * node::first_child()
   {
      if(m_nodea.get_count() <= 0)
         return nullptr;
      return child_at(0);
   }



   const char * node::LoadDocType( const char * pszXml, parse_info * pparseinfo)
   {
      if(pparseinfo == nullptr)
         pparseinfo = System.xml().m_pparseinfoDefault;
      if(pszXml[0] != '<' || pszXml[1] != '!')
         return pszXml;

      ::str::consume(pszXml, "<!DOCTYPE");
      ::str::consume_spaces(pszXml);
      ::str::consume_nc_name(pszXml);

      ::str::consume_spaces(pszXml, 0);
      if(::str::begins_consume(pszXml, "SYSTEM"))
      {
         ::str::consume_spaces(pszXml);
         ::str::consume_quoted_value(pszXml);
      }
      else if(::str::begins_consume(pszXml, "PUBLIC"))
      {
         ::str::consume_spaces(pszXml);
         ::str::consume_quoted_value(pszXml);
         ::str::consume_spaces(pszXml);
         ::str::consume_quoted_value(pszXml);
      }

      ::str::consume_spaces(pszXml, 0);

      //markup decl
      if(*pszXml == '[')
      {
         ::str::consume(pszXml, "[");

         while(*pszXml != ']')
         {
            if(::str::begins_consume(pszXml, "<!ENTITY"))
            {
               ::str::consume_spaces(pszXml);
               string entity_name = ::str::consume_nc_name(pszXml);
               ::str::consume_spaces(pszXml);
               string entity_value;
               string ext_entity_value;
               if(::str::begins_consume(pszXml, "SYSTEM"))
               {
                  ::str::consume_spaces(pszXml);
                  ext_entity_value = ::str::consume_quoted_value(pszXml);
               }
               else if (::str::begins_consume(pszXml, "PUBLIC"))
               {
                  ::str::consume_spaces(pszXml);
                  ::str::consume_quoted_value(pszXml);
                  ::str::consume_spaces(pszXml);
                  ext_entity_value = ::str::consume_quoted_value(pszXml);
               }
               else
               {
                  entity_value = ::str::consume_quoted_value(pszXml);
               }
               if(entity_value.has_char())
               {
                  __defer_fork(m_pdocument->m_pentitiesHash);
                  m_pdocument->m_pentitiesHash->set_at(entity_name, entity_value);
               }
               if(ext_entity_value.has_char())
               {
                  __defer_fork(m_pdocument->m_pentitiesExtHash);
                  m_pdocument->m_pentitiesExtHash->set_at(entity_name, ext_entity_value);
               }
            }
            else if(::str::xml_is_comment(pszXml))
            {
               ::str::xml_consume_comment(pszXml);
            }
            pszXml++;
         }
         ::str::consume(pszXml, "]");
         ::str::consume_spaces(pszXml, 0);
      }


      ::str::consume(pszXml, ">");


      return (char *) pszXml;
   }


   // attr1="value1" attr2='value2' attr3=value3 />
   //                                            ^- return pointer
   //========================================================
   // Name   : LoadAttributes
   // Desc   : loading attr plain xml text
   // Param  : pszAttrs - xml of attributes
   //          pparseinfo = parser information
   // Return : advanced string pointer. (error return nullptr)
   //--------------------------------------------------------
   // Coder    Date                      Desc
   // bro      2002-10-29
   //========================================================
   const char * node::LoadAttributes( const char * pszAttrs, parse_info * pparseinfo)
   {

      if(pparseinfo == nullptr)
      {

         pparseinfo = System.xml().m_pparseinfoDefault;

      }

      const char * xml = pszAttrs;

      while(*xml != '\0')
      {

         if((xml = _tcsskip( xml )) != nullptr)
         {

            // close tag
            if(*xml == chXMLTagClose || *xml == chXMLTagPre)
            {

               // wel-formed tag
               return xml;

            }

            // XML Attr Name
            const CHAR* pszEnd = ansi_scan( xml, " =" );

            if( pszEnd == nullptr )
            {

               // error
               if( pparseinfo->m_bErrorOccur == false )
               {

                  pparseinfo->m_bErrorOccur = true;
                  pparseinfo->m_pszErrorPointer = xml;
                  pparseinfo->m_eparseerror = parse_error_attr_no_value;
                  pparseinfo->m_strError.Format( "<%s> attr has error ", m_strName.c_str() );

               }

               return nullptr;

            }

            string strName;

            // XML Attr Name
            _SetString(xml, pszEnd, &strName);

            //m_pset.defer_create_new();

            // add new attr
            auto & property = m_set.get(strName);

            xml = pszEnd;

            // XML Attr Value
            if( (xml = _tcsskip( xml )) )
            {
               //if( xml = strchr( xml, '=' ) )
               if( *xml == '=' )
               {
                  if( ((xml = _tcsskip( ++xml )) ))
                  {
                     // if " or '
                     // or none quote
                     i32 quote = *xml;
                     if( quote == '"' || quote == '\'' )
                        //pszEnd = _tcsechr( ++xml, quote, chXMLEscape );
                        pszEnd = _tcsechr( ++xml, quote, 0 );
                     else
                     {
                        //attr= m_strValue>
                        // none quote mode
                        //pszEnd = _tcsechr( xml, ' ', '\\' );
                        //pszEnd = _tcsepbrk( xml, " >", chXMLEscape );
                        pszEnd = _tcsepbrk( xml, " >", 0 );
                     }

                     bool trim = pparseinfo->m_bTrimValue;

                     CHAR escape = pparseinfo->m_chEscapeValue;

                     string strValue;

                     _SetString( xml, pszEnd, &strValue, trim, chXMLEscape );

                     property = strValue;

//                     {
//
//                        char * point = xml;
//
//                        while(point != pszEnd && *point != '\0')
//                        {
//
//                           if(point[0] == '&')
//                           {
//
//                              point = m_pdocument->patch_entity_ref((const char * &) point, true, &xml, &pszEnd, nullptr);
//
//                           }
//                           else
//                           {
//
//                              point = (char *) ::str::utf8_inc(point);
//
//                           }
//
//                        }
//
//                        string strValue;
//
//                        _SetString(xml, pszEnd, &strValue, trim, escape);
//
//                        pproperty->set_string(::move(strValue));
//
//                     }

                     xml = pszEnd;
                     // ATTRVALUE
                     if( pparseinfo->m_bEntityValue && pparseinfo->m_pentities )
                     {

                        property = pparseinfo->m_pentities->ref_to_entity(property.get_string());

                     }

                     if( quote == '"' || quote == '\'' )
                     {

                        if(*xml == '\0')
                        {

                           return xml;

                           break;
                           // resilliency
                        }
                        else
                        {
                           xml++;
                        }
                     }
                  }
               }
            }
         }
      }

      // not wel-formed tag
      return nullptr;
   }


   // <?xml version="1.0"?>
   //                      ^- return pointer
   //========================================================
   // Name   : LoadProcessingInstrunction
   // Desc   : loading processing instruction
   // Param  : pszXml - PI string
   //          pparseinfo - parser information
   // Return : advanced string pointer. (error return nullptr)
   //--------------------------------------------------------
   // Coder    Date                      Desc
   // bro      2004-06-14
   //========================================================
   const char * node::LoadProcessingInstruction( const char * pszXml, parse_info * pparseinfo)
   {
      if(pparseinfo == nullptr)
         pparseinfo = System.xml().m_pparseinfoDefault;

      // find the end of pparseinfo
      const char * end = _tcsenistr( pszXml, astr.XMLPIClose, astr.XMLPIClose.get_length(), pparseinfo ? pparseinfo->m_chEscapeValue : 0 );
      if(end == nullptr)
         return nullptr;

      while(*end != '\0' && isspace(*end))
         end++;

      if(*end == '\0')
         return nullptr;

      // process pparseinfo
      if( m_pdocument )
      {
         const char * xml = pszXml;

         __pointer(node) pnode = __new(node(this));
         pnode->m_pnodeParent = this;
         pnode->m_pdocument = m_pdocument;
         pnode->m_etype = node_pi;

         xml += astr.XMLPIOpen.get_length();
         const CHAR* pTagEnd = ansi_scan( xml, " ?>" );
         _SetString( xml, pTagEnd, &pnode->m_strName );
         xml = pTagEnd;

         pnode->LoadAttributes( xml, end, pparseinfo );

         m_pdocument->m_nodea.add( pnode );
      }

      end += astr.XMLPIClose.get_length();
      return end;
   }

   // attr1="value1" attr2='value2' attr3=value3 />
   //                                            ^- return pointer
   //========================================================
   // Name   : LoadAttributes
   // Desc   : loading attr plain xml text
   // Param  : pszAttrs - xml of attributes
   //          pszEnd - last string
   //          pparseinfo = parser information
   // Return : advanced string pointer. (error return nullptr)
   //--------------------------------------------------------
   // Coder    Date                      Desc
   // bro      2004-06-14
   //========================================================
   const char * node::LoadAttributes( const char * pszAttrs, const char * pszEnd, parse_info * pparseinfo)
   {
      if(pparseinfo == nullptr)
         pparseinfo = System.xml().m_pparseinfoDefault;

      const char * xml = pszAttrs;

      while( xml && *xml )
      {
         if( (xml = _tcsskip( xml )) )
         {
            // close tag
            if( xml >= pszEnd )
               // wel-formed tag
               return xml;

            // XML Attr Name
            const CHAR* pszEnd = ansi_scan( xml, " =" );
            if( pszEnd == nullptr )
            {
               // error
               if( pparseinfo->m_bErrorOccur == false )
               {
                  pparseinfo->m_bErrorOccur = true;
                  pparseinfo->m_pszErrorPointer = xml;
                  pparseinfo->m_eparseerror = parse_error_attr_no_value;
                  pparseinfo->m_strError.Format( "<%s> attr has error ", m_strName.c_str() );
               }
               return nullptr;
            }

            string strName;
            // XML Attr Name
            _SetString( xml, pszEnd, &strName );

            // add new attr
            auto & property = m_set.get(strName);

            xml = pszEnd;

            // XML Attr Value
            if( (xml = _tcsskip( xml )) )
            {
               //if( xml = strchr( xml, '=' ) )
               if( *xml == '=' )
               {
                  if( (xml = _tcsskip( ++xml )) )
                  {
                     // if " or '
                     // or none quote
                     i32 quote = *xml;
                     if( quote == '"' || quote == '\'' )
                        pszEnd = _tcsechr( ++xml, quote, chXMLEscape );
                     else
                     {
                        //attr= m_strValue>
                        // none quote mode
                        //pszEnd = _tcsechr( xml, ' ', '\\' );
                        pszEnd = _tcsepbrk( xml, " >", chXMLEscape );
                     }

                     bool trim = pparseinfo->m_bTrimValue;
                     CHAR escape = pparseinfo->m_chEscapeValue;
                     //_SetString( xml, pszEnd, &attr->m_strValue, trim, chXMLEscape );
                     string strValue;
                     _SetString( xml, pszEnd, &strValue, trim, escape );
                     property = strValue;
                     xml = pszEnd;

                     // ATTRVALUE
                     if (pparseinfo->m_bEntityValue && pparseinfo->m_pentities)
                     {

                        property = pparseinfo->m_pentities->ref_to_entity(property.get_string());

                     }
                     if( quote == '"' || quote == '\'' )
                        xml++;
                  }
               }
            }
         }
      }

      // not wel-formed tag
      return nullptr;
   }

   // <!-- comment -->
   //                 ^- return pointer
   //========================================================
   // Name   : LoadComment
   // Desc   : loading comment
   // Param  : pszXml - comment string
   //          pparseinfo - parser information
   // Return : advanced string pointer. (error return nullptr)
   //--------------------------------------------------------
   // Coder    Date                      Desc
   // bro      2004-06-14
   //========================================================
   const char * node::LoadComment( const char * pszXml, parse_info * pparseinfo)
   {
      if(pparseinfo == nullptr)
         pparseinfo = System.xml().m_pparseinfoDefault;

      // find the end of comment
      const char * end = _tcsenistr( pszXml, astr.XMLCommentClose, astr.XMLCommentClose.get_length(), pparseinfo ? pparseinfo->m_chEscapeValue : 0 );
      if( end == nullptr )
         return nullptr;

      // process comment
      node * par = m_pnodeParent;
      if( m_pnodeParent == nullptr && m_pdocument )
         par = m_pdocument;
      if( par )
      {
         const char * xml =pszXml;
         xml += astr.XMLCommentOpen.get_length();

         auto pnode = __new(node(this));
         pnode->m_pnodeParent = par;
         pnode->m_pdocument = m_pdocument;
         pnode->m_etype = node_comment;
         pnode->m_strName = "#COMMENT";
         _SetString( xml, end, &pnode->m_strValue, FALSE );

         par->m_nodea.add( pnode );
      }

      end += astr.XMLCommentClose.get_length();
      return end;
   }

   // <![CDATA[ cdata ]]>
   //                    ^- return pointer
   //========================================================
   // Name   : LoadCDATA
   // Desc   : loading CDATA
   // Param  : pszXml - CDATA string
   //          pparseinfo - parser information
   // Return : advanced string pointer. (error return nullptr)
   //--------------------------------------------------------
   // Coder    Date                      Desc
   // bro      2004-06-14
   //========================================================
   const char * node::LoadCDATA( const char * pszXml, parse_info * pparseinfo)
   {
      if(pparseinfo == nullptr)
         pparseinfo = System.xml().m_pparseinfoDefault;

      // find the end of CDATA
      const char * end = _tcsenistr( pszXml, astr.XMLCDATAClose, astr.XMLCDATAClose.get_length(), pparseinfo ? pparseinfo->m_chEscapeValue : 0 );
      if( end == nullptr )
         return nullptr;

      // process CDATA
      node * pnodeParent = m_pnodeParent;
      if( m_pnodeParent == nullptr && m_pdocument )
         pnodeParent = (node *)&m_pdocument;
      if( pnodeParent )
      {
         const char * xml = pszXml;
         xml += astr.XMLCDATAOpen.get_length();

         auto pnode = __new(node(this));
         pnode->m_pnodeParent = this;
         pnode->m_pdocument = m_pdocument;
         pnode->m_etype = node_cdata;
         pnode->m_strName = "#CDATA";
         _SetString( xml, end, &pnode->m_strValue, FALSE );

         pnodeParent->m_nodea.add( pnode );
      }

      end += astr.XMLCDATAClose.get_length();
      return end;
   }



   //========================================================
   // Name   : LoadOtherNodes
   // Desc   : internal function for loading PI/CDATA/Comment
   // Param  : node - current xml node
   //          pbRet - error occur
   //          pszXml - CDATA string
   //          pparseinfo - parser information
   // Return : advanced string pointer. (error return nullptr)
   //--------------------------------------------------------
   // Coder    Date                      Desc
   // bro      2004-06-14
   //========================================================
   const char * node::LoadOtherNodes(bool* pbRet, const char * pszXml, parse_info * pparseinfo)
   {
      if(pparseinfo == nullptr)
         pparseinfo = System.xml().m_pparseinfoDefault;

      const char * xml = pszXml;
      bool do_other_type = true;
      *pbRet = false;

      while( xml && do_other_type )
      {
         do_other_type = false;

         xml = _tcsskip( xml );
         const char * prev = xml;
         // is PI( Processing Instruction ) Node?
         if(ansi_count_compare_ci( xml, astr.XMLPIOpen, astr.XMLPIOpen.get_length() ) == 0 )
         {
            // processing instrunction parse
            // return pointer is next node of pparseinfo
            xml = LoadProcessingInstruction( xml, pparseinfo );
            //if( xml == nullptr )
            //   return nullptr;
            // restart xml parse
         }

         if( xml != prev )
            do_other_type = true;
         xml = _tcsskip( xml );
         prev = xml;

         if(m_pnodeParent != nullptr && m_pnodeParent->m_etype == node_document)
         {
            // is DOCTYPE
            if(::str::begins(xml, astr.XMLDOCTYPEOpen))
            {
               // processing instrunction parse
               // return pointer is next node of pparseinfo
               xml = LoadDocType( xml, pparseinfo );
               //if( xml == nullptr )
               //   return nullptr;
               // restart xml parse
            }

            if( xml != prev )
               do_other_type = true;
            xml = _tcsskip( xml );
            prev = xml;
         }

         // is comment Node?
         if(ansi_count_compare_ci( xml, astr.XMLCommentOpen, astr.XMLCommentOpen.get_length() ) == 0 )
         {
            // processing comment parse
            // return pointer is next node of comment
            xml = LoadComment( xml, pparseinfo );
            // comment node is terminal node
            if(m_pnodeParent != nullptr && m_pnodeParent->m_etype != node_document
                  && xml != prev )
            {
               *pbRet = true;
               xml = _tcsskip( xml );
               return xml;
            }
            // restart xml parse when this node is root m_pdocument node
         }

         if( xml != prev )
            do_other_type = true;

         xml = _tcsskip( xml );
         prev = xml;
         // is CDATA Node?
         if(ansi_count_compare_ci( xml, astr.XMLCDATAOpen, astr.XMLCDATAOpen.get_length() ) == 0 )
         {
            // processing CDATA parse
            // return pointer is next node of CDATA
            xml = LoadCDATA( xml, pparseinfo );
            // CDATA node is terminal node
            if(m_pnodeParent && m_pnodeParent->m_etype != node_document
                  && xml != prev )
            {
               *pbRet = true;
               return xml;
            }
            // restart xml parse when this node is root m_pdocument node
         }

         if( xml != prev )
            do_other_type = true;
      }

      return xml;
   }

   const char * node::load(const char * pszXml, parse_info * pi)
   {

      return _load(pszXml, pszXml + strlen(pszXml), pi);

   }

   // <TAG attr1="value1" attr2='value2' attr3=value3 >
   // </TAG>
   // or
   // <TAG />
   //        ^- return pointer
   //========================================================
   // Name   : Load
   // Desc   : load xml plain text
   // Param  : pszXml - plain xml text
   //          pparseinfo = parser information
   // Return : advanced string pointer  (error return nullptr)
   //--------------------------------------------------------
   // Coder    Date                      Desc
   // bro      2002-10-29
   //========================================================
   const char * node::_load(const char * pszXml,const char * pszEndXml,parse_info * pparseinfo)
   {

      // close it
      close();

      if(pparseinfo == nullptr)
         pparseinfo = System.xml().m_pparseinfoDefault;

      const char * xml = pszXml;

      xml = strchr( xml, chXMLTagOpen );
      if( xml == nullptr )
         return nullptr;

      // close Tag
      if( *(xml+1) == chXMLTagPre ) // </close
         return xml;

      // Load Other Node before <Tag>(pparseinfo, comment, CDATA etc)
      bool bRet = false;
      const char * ret = nullptr;
      ret = LoadOtherNodes(&bRet, xml, pparseinfo );
      if( ret != nullptr )
         xml = ret;
      if( bRet )
         return xml;

      // XML Node Tag Name open
      xml++;
      //CHAR* pTagEnd = ansi_scan( xml, " />\t\r\n" );
      const CHAR* pTagEnd = end_open_tag_name(xml);
      _SetString( xml, pTagEnd, &m_strName );
      xml = pTagEnd;
      // Generate XML Attributte List
      if( (xml = LoadAttributes( xml, pparseinfo )) )
      {
         // alone tag <TAG ... />
         if(  *xml == chXMLTagPre )
         {
            xml++;
            if( *xml == chXMLTagClose )
               // wel-formed tag
               return ++xml;
            else
            {
               // error: <TAG ... / >
               if( pparseinfo->m_bErrorOccur == false )
               {
                  pparseinfo->m_bErrorOccur = true;
                  pparseinfo->m_pszErrorPointer = xml;
                  pparseinfo->m_eparseerror = parse_error_alone_not_closed;
                  pparseinfo->m_strError = "Element must be closed.";
               }
               // not wel-formed tag
               return nullptr;
            }
         }
         else if(*xml)
            // open/close tag <TAG ..> ... </TAG>
            //                        ^- current pointer
         {
            // if text m_strValue is not exist, then assign m_strValue
            //if( this->m_strValue.is_empty() || this->m_strValue == "" )
            if(::str::trimmed_is_empty(m_strValue))
            {
               // Text Value
               const CHAR* pszEnd = _tcsechr( ++xml, chXMLTagOpen, chXMLEscape );
               if( pszEnd == nullptr )
               {
                  if( pparseinfo->m_bErrorOccur == false )
                  {
                     pparseinfo->m_bErrorOccur = true;
                     pparseinfo->m_pszErrorPointer = xml;
                     pparseinfo->m_eparseerror = parse_error_not_closed;
                     pparseinfo->m_strError.Format("%s must be closed with </%s>", m_strName.c_str() );
                  }
                  // error cos not exist CloseTag </TAG>
                  return nullptr;
               }

               bool trim = pparseinfo->m_bTrimValue;
               CHAR escape = pparseinfo->m_chEscapeValue;
               //_SetString( xml, pszEnd, &m_strValue, trim, chXMLEscape );
               pszEnd = xml;
               while(*pszEnd != '<' && *pszEnd != '\0')
               {
               //   if(pszEnd[0] == '&')
               ////   {
               ////      pszEnd = m_pdocument->patch_entity_ref((const char * &) pszEnd, true, &xml, nullptr);
               ////   }
               ////   else
               ////   {
                   pszEnd = (char *) ::str::utf8_inc(pszEnd);
               //   }
               }
               _SetString( xml, pszEnd, &m_strValue, trim, escape );
               xml = pszEnd;

               // TEXTVALUE context_object
               if( pparseinfo->m_bEntityValue && pparseinfo->m_pentities )
                  m_strValue = pparseinfo->m_pentities->ref_to_entity(m_strValue);
            }

            // generate child nodes
            while( xml && *xml )
            {
               __pointer(node) pnode = __new(node(this));
               pnode->m_pnodeParent = this;
               pnode->m_pdocument = m_pdocument;
               pnode->m_etype = m_etype;

               xml = pnode->load( xml,pparseinfo );
               if(pnode->m_strName.has_char())
               {
                  m_nodea.add(pnode);
//                  ::release(pnode);
               }
               else
               {
                  //delete pnode;
                  pnode.release();
               }

               // open/close tag <TAG ..> ... </TAG>
               //                             ^- current pointer
               // CloseTag case
               if( xml && *xml && *(xml+1) && *xml == chXMLTagOpen && *(xml+1) == chXMLTagPre )
               {
                  // </close>
                  xml+=2; // C

                  if( (xml = _tcsskip( xml )) )
                  {
                     string closename;
                     const  CHAR* pszEnd = ansi_scan( xml, " >" );
                     if( pszEnd == nullptr )
                     {
                        if( pparseinfo->m_bErrorOccur == false )
                        {
                           pparseinfo->m_bErrorOccur = true;
                           pparseinfo->m_pszErrorPointer = xml;
                           pparseinfo->m_eparseerror = parse_error_not_closed;
                           pparseinfo->m_strError.Format("it must be closed with </%s>", m_strName.c_str() );
                        }
                        // error
                        return nullptr;
                     }
                     _SetString( xml, pszEnd, &closename );
                     if( closename == this->m_strName )
                     {
                        // wel-formed open/close
                        xml = pszEnd+1;
                        // return '>' or ' ' after pointer
                        return xml;
                     }
                     else
                     {
                        xml = pszEnd+1;
                        // 2004.6.15 - example <B> alone tag
                        // now it can parse with attr 'force_arse'
                        if( pparseinfo->m_bForceParse == false )
                        {
                           // not welformed open/close
                           if( pparseinfo->m_bErrorOccur == false )
                           {
                              pparseinfo->m_bErrorOccur = true;
                              pparseinfo->m_pszErrorPointer = xml;
                              pparseinfo->m_eparseerror = parse_error_not_nested;
                              pparseinfo->m_strError.Format("'<%s> ... </%s>' is not wel-formed.", m_strName.c_str(), closename.c_str() );
                           }
                           return nullptr;
                        }
                     }
                  }
               }
               else if(xml && *xml)  // Alone child Tag Loaded
                  // else 해야하는지 말아야하는지 의심간다.
               {

                  //if( xml && this->m_strValue.is_empty() && *xml !=chXMLTagOpen )
                  if( xml && ::str::trimmed_is_empty(m_strValue) && *xml !=chXMLTagOpen )
                  {
                     // Text Value
                     const CHAR* pszEnd = _tcsechr( xml, chXMLTagOpen, chXMLEscape );
                     if( pszEnd == nullptr )
                     {
                        // error cos not exist CloseTag </TAG>
                        if( pparseinfo->m_bErrorOccur == false )
                        {
                           pparseinfo->m_bErrorOccur = true;
                           pparseinfo->m_pszErrorPointer = xml;
                           pparseinfo->m_eparseerror = parse_error_not_closed;
                           pparseinfo->m_strError.Format("it must be closed with </%s>", m_strName.c_str() );
                        }
                        return nullptr;
                     }

                     bool trim = pparseinfo->m_bTrimValue;
                     CHAR escape = pparseinfo->m_chEscapeValue;
                     //_SetString( xml, pszEnd, &m_strValue, trim, chXMLEscape );
                     pszEnd = xml;
                     //while(*pszEnd != '<' && *pszEnd != '\0' && pszEnd < pszEndXml)
                     //{
                     //   if(pszEnd[0] == '&')
                     //   {
                     //      pszEnd = m_pdocument->patch_entity_ref((const char * &) pszEnd, true, &xml, nullptr);
                     //   }
                     //   else
                     //   {
                     //      pszEnd = (char *) ::str::__utf8_inc(pszEnd);
                     //   }
                     //}
                     if(pszEnd > pszEndXml)
                        pszEnd = (char *) pszEndXml;
                     _SetString( xml, pszEnd, &m_strValue, trim, escape );
                     xml = pszEnd;
                     //TEXTVALUE
                     if( pparseinfo->m_bEntityValue && pparseinfo->m_pentities )
                        m_strValue = pparseinfo->m_pentities->ref_to_entity(m_strValue);
                  }
               }
            }
         }
      }

      return xml;
   }



   //========================================================
   // Name   : get_xml
   // Desc   : convert plain xml text from parsed xml attirbute
   // Param  :
   // Return : converted plain string
   //--------------------------------------------------------
   // Coder    Date                      Desc
   // bro      2002-10-29
   //========================================================

   //========================================================
   // Name   : get_xml
   // Desc   : convert plain xml text from parsed xml node
   // Param  :
   // Return : converted plain string
   //--------------------------------------------------------
   // Coder    Date                      Desc
   // bro      2002-10-29
   //========================================================
   string node::get_xml( disp_option * opt /*= &optDefault*/ ) const
   {

      string ostring;

      if(opt == nullptr)
      {

         opt = System.xml().m_poptionDefault;

      }

      if( m_etype == node_document )
      {

         for (i32 i = 0; i < m_nodea.get_size(); i++)
         {

            ostring += m_nodea[i]->get_xml(opt);

            if (i >= m_nodea.get_upper_bound())
            {

               break;

            }

            if (opt && opt->m_bNewLine)
            {

               if (opt && opt->m_bNewLine)
               {

                  ostring += "\r\n";

               }
               

            }

         }

         return ostring;

      }
      else
      {

         if (m_etype == node_pi)
         {
            // <?TAG
            ostring += astr.XMLPIOpen + m_strName;
            // <?TAG Attr1="Val1"
            if (m_set.has_elements())
            {

               ostring += ' ';
            }

            for (auto & pproperty : m_set)
            {
               ostring += pproperty->get_xml(opt);
            }
            //?>
            ostring += astr.XMLPIClose;
            return ostring;
         }
         else if (m_etype == node_comment)
         {
            // <--comment
            ostring += astr.XMLCommentOpen + m_strValue;
            //-->
            ostring += astr.XMLCommentClose;
            return ostring;
         }
         else if (m_etype == node_cdata)
         {
            // <--comment
            ostring += astr.XMLCDATAOpen + m_strValue;
            //-->
            ostring += astr.XMLCDATAClose;
            return ostring;
         }

      }

      // <TAG
      ostring += '<' + m_strName;

      // <TAG Attr1="Val1"
      //if (m_set.has_elements())
        // ostring += ' ';

      for (auto & pproperty : m_set)
      {

         ostring += " ";

         ostring += pproperty->get_xml(opt);

      }

      if( m_nodea.is_empty() && m_strValue.is_empty() )
      {
         // <TAG Attr1="Val1"/> alone tag
         ostring += "/>";
      }
      else
      {
         // <TAG Attr1="Val1"> and get child
         ostring += ">";

         opt->m_iTabBase++;

         if (m_nodea.has_elements())
         {

            if (opt && opt->m_bNewLine)
            {

                ostring += "\r\n";

            }

         }

         for (i32 i = 0; i < m_nodea.get_size(); i++)
         {

            if (opt && opt->m_bNewLine)
            {

               for (i32 i = 0; i < opt->m_iTabBase; i++)
               {

                  ostring += '\t';

               }

            }
             
            ostring += m_nodea[i]->get_xml(opt);

            if (i >= m_nodea.get_upper_bound())
            {

               break;

            }

            if (opt && opt->m_bNewLine)
            {

               if (opt && opt->m_bNewLine)
               {

                  ostring += "\r\n";

               }

            }

         }

         string strTrimmedValue = m_strValue;

         strTrimmedValue.trim();
         // Text Value
         if( strTrimmedValue != "" )
         {
            if( opt && opt->m_bNewLine && !m_nodea.is_empty() )
            {
               if( opt && opt->m_bNewLine )
                  ostring += "\r\n";
               for( i32 i = 0 ; i < opt->m_iTabBase ; i++)
                  ostring += '\t';
            }
            ostring += (opt &&opt->m_bReferenceValue&&opt->m_pentities?opt->m_pentities->entity_to_ref(m_strValue):m_strValue);
         }

         // </TAG> CloseTag
         if( opt && opt->m_bNewLine && !m_nodea.is_empty() )
         {
            ostring += "\r\n";
            for( i32 i = 0 ; i < opt->m_iTabBase-1 ; i++)
               ostring += '\t';
         }

         ostring += "</" + m_strName + '>';

         opt->m_iTabBase--;

      }

      return ostring;

   }


   //========================================================
   // 함수명 : GetText
   // 설  명 : 노드 하나를 텍스트 문자열로 반환
   // 인  자 :
   // 리턴값 : 변환된 문자열
   //--------------------------------------------------------
   // 작성자   작성일                 작성이유
   // 조경민   2004-06-15
   //========================================================
   string node::get_text( disp_option * opt /*= &optDefault*/ ) const
   {

      string ostring;

      if(opt == nullptr)
      {
         opt = System.xml().m_poptionDefault;
      }

      if( m_etype == node_document )
      {
         for( i32 i = 0 ; i < m_nodea.get_size(); i++ )
            ostring += m_nodea[i]->get_text( opt );
      }
      else if( m_etype == node_pi )
      {
         // no text
      }
      else if( m_etype == node_comment )
      {
         // no text
      }
      else if( m_etype == node_cdata )
      {
         ostring += m_strValue;
      }
      else if( m_etype == node_element )
      {
         if( m_nodea.is_empty() && m_strValue.is_empty() )
         {
            // no text
         }
         else
         {
            // m_nodea text
            for( i32 i = 0 ; i < m_nodea.get_size(); i++ )
               ostring += m_nodea[i]->get_text();

            // Text Value
            ostring += (opt->m_bReferenceValue&&opt->m_pentities?opt->m_pentities->entity_to_ref(m_strValue):m_strValue);
         }
      }

      return ostring;
   }

   //========================================================
   // Name   : get_attr
   // Desc   : get attr with attr m_strName
   // Param  :
   // Return :
   //--------------------------------------------------------
   // Coder    Date                      Desc
   // bro      2002-10-29
   //========================================================
   //attr * node::find_attr( const char * attrname )
   //{
   //   return m_attra.find(attrname);
   //   /*for( i32 i = 0 ; i < m_attra.get_count(); i++ )
   //   {
   //      ::xml::attr * attr = &m_attra.m_propertyptra[i];
   //      if(attr != nullptr)
   //      {
   //         if(attr->name() == attrname)
   //            return attr;
   //      }
   //   }
   //   return nullptr;*/
   //}

   //========================================================
   // Name   : GetAttrs
   // Desc   : find attributes with attr m_strName, return its list
   // Param  :
   // Return :
   //--------------------------------------------------------
   // Coder    Date                      Desc
   // bro      2002-10-29
   //========================================================
   /*attr_array node::attrs( const char * lpszName )
   {

      attr_array attra(get_object());

      for( i32 i = 0 ; i < m_attra.get_count(); i++ )
      {
         ::xml::attr * attr = &m_attra.m_propertyptra[i];
         if(attr != nullptr)
         {
            if(attr->name() == lpszName)
               attra.m_propertyptra.add(*attr);
         }
      }

      return attra;

   }*/

   //========================================================
   // Name   : get_attr_value
   // Desc   : get attr with attr m_strName, return its m_strValue
   // Param  :
   // Return :
   //--------------------------------------------------------
   // Coder    Date                      Desc
   // bro      2002-10-29
   //========================================================
   /*bool node::get_attr_value( const char * attrname, string & strValue )
   {
      attr * attr = get_attr( attrname );
      if(attr == nullptr)
         return false;
      strValue = attr->m_strValue;
      return true;
   }*/

   node::array & node::children()
   {
      return m_nodea;
   }

   //========================================================
   // Name   : GetChilds
   // Desc   : find m_nodea with m_strName and return m_nodea list
   // Param  :
   // Return :
   //--------------------------------------------------------
   // Coder    Date                      Desc
   // bro      2002-10-29
   //========================================================
   node::array node::children( const char * lpszName )
   {
      
      node::array nodea;

      for(auto & pnode : m_nodea)
      {

         if (pnode->m_strName == lpszName)
         {

            nodea.add(pnode);

         }

      }

      return nodea;

   }

   //========================================================
   // Name   : get_child
   // Desc   : get child node with index
   // Param  :
   // Return : nullptr return if no child.
   //--------------------------------------------------------
   // Coder    Date                      Desc
   // bro      2002-10-29
   //========================================================
   node * node::child_at(index i )
   {
      if( i >= 0 && i < m_nodea.get_size() )
         return m_nodea[i];
      return nullptr;
   }

   //========================================================
   // Name   : GetChildCount
   // Desc   : get child node count
   // Param  :
   // Return : 0 return if no child
   //--------------------------------------------------------
   // Coder    Date                      Desc
   // bro      2002-12-26
   //========================================================
   ::count node::get_children_count(const char * lpszName )
   {
      if(lpszName == nullptr || *lpszName == '\0')
      {
         return get_children_count();
      }
      else
      {
         ::count count = 0;
         for(i32 i = 0; i < m_nodea.get_count(); i++)
         {
            if(m_nodea[i]->m_strName == lpszName)
               count++;
         }
         return count;
      }
   }
   ::count node::get_children_count()
   {
      return m_nodea.get_count();
   }

   ::count node::get_children_count(const char * lpszName, index iDepth)
   {
      if(iDepth == 0)
         return 0;
      ::count count = 0;
      for(index i = 0; i < m_nodea.get_count(); i++)
      {
         if(lpszName == nullptr || *lpszName == '\0')
         {
            count++;
         }
         else
         {
            if(m_nodea[i]->m_strName == lpszName)
               count++;
         }
         if(iDepth < 0)
            count += m_nodea[i]->get_children_count(lpszName, -1);
         else
            count += m_nodea[i]->get_children_count(lpszName, iDepth - 1);
      }
      return count;
   }

   //========================================================
   // Name   : get_child
   // Desc   : find child with m_strName and return child
   // Param  :
   // Return : nullptr return if no child.
   //--------------------------------------------------------
   // Coder    Date                      Desc
   // bro      2002-10-29
   //========================================================
   node * node::get_child(const char * lpszName)
   {
      index iStart = 0;
      return get_child(lpszName, iStart);
   }

   node *        node::get_node_from_attr_path(const char * path, const char * lpszName, const char * pszAttr)
   {
      string_array stra;
      stra.explode("/", path);
      ::xml::node  * pnode = this;
      if(stra.get_size() <= 0 || (stra.get_size() == 1 && stra[0].get_length() == 0))
         return this;
      for(i32 i = 0; i < stra.get_size(); i++)
      {
         pnode = pnode->get_child_with_attribute(lpszName, pszAttr, stra[i]);
         if(pnode == nullptr)
            return nullptr;
      }
      return pnode;
   }

   string                  node::get_child_simple_attr_path(node * pnode, const char * pszAttr)
   {
      string str;
      while(pnode != nullptr && pnode != this)
      {
         str = pnode->attribute(pszAttr).get_string() + ::str::has_char(str, "/");
         pnode = pnode->m_pnodeParent;
      }
      if(pnode == nullptr)
         return "";
      else if(pnode != this)
         return "";
      return str;

   }


   node * node::get_node_from_simple_path(const char * path)
   {
      string_array stra;
      stra.explode("/", path);
      ::xml::node  * pnode = this;
      if(stra.get_size() <= 0 || (stra.get_size() == 1 && stra[0].get_length() == 0))
         return this;
      for(i32 i = 0; i < stra.get_size(); i++)
      {
         pnode = pnode->get_child(stra[i]);
         if(pnode == nullptr)
            return nullptr;
      }
      return pnode;
   }

   node * node::get_node_from_indexed_path(const index_array & iaPath)
   {

      node * pnode = this;

      if(pnode == nullptr)
         return nullptr;

      for(index iLevel = 0; iLevel < iaPath.get_count(); iLevel++)
      {

         index iIndex = iaPath[iLevel];

         if(iIndex < 0)
            return nullptr;

         if(iIndex >= pnode->get_children_count())
            return nullptr;

         pnode = pnode->child_at(iIndex);

         if(pnode == nullptr)
            return nullptr;

      }

      return pnode;
   }

   string node::get_child_simple_path(const node * pnode) const
   {
      string str;
      while(pnode != nullptr && pnode != this)
      {
         str = pnode->m_strName + ::str::has_char(str, "/");
         pnode = pnode->m_pnodeParent;
      }
      if(pnode == nullptr)
         return "";
      else if(pnode != this)
         return "";
      return str;
   }

   void node::get_child_indexed_path(index_array & iaPath, const node * pnode) const
   {

      iaPath.remove_all();
      while(pnode != nullptr && pnode != this)
      {
         iaPath.insert_at(0, pnode->get_index());
         pnode = pnode->m_pnodeParent;
      }

   }

   index_array node::get_child_indexed_path(const node * pnode) const
   {

      index_array iaPath;
      get_child_indexed_path(iaPath, pnode);
      return iaPath;

   }

   node * node::get_child(const char * lpszName, index & iStartPosition)
   {
      for(index i = iStartPosition; i < m_nodea.get_size(); i++ )
      {
         if(m_nodea[i]->m_strName.compare(lpszName) == 0)
            return m_nodea[i];
      }
      return nullptr;
   }


   //========================================================
   // Name   : GetChildValue
   // Desc   : find child with m_strName and return child's m_strValue
   // Param  :
   // Return : nullptr return if no child.
   //--------------------------------------------------------
   // Coder    Date                      Desc
   // bro      2002-10-29
   //========================================================
   string   node::get_child_value( const char * lpszName )
   {
      node * node = get_child( lpszName );
      return (node != nullptr)? (const char *)node->m_strValue : nullptr;
   }

   string   node::get_child_text( const char * lpszName, disp_option * opt /*= &optDefault*/ )
   {
      node * node = get_child( lpszName );
      return (node != nullptr)? node->get_text(opt) : "";
   }

   
   property * node::GetChildAttr( const char * lpszName, const char * attrname )
   {

      node * node = get_child(lpszName);

      return node ? node->find_attribute(attrname) : nullptr;

   }


   string node::GetChildAttrValue( const char * lpszName, const char * attrname )
   {
      
      property * attr = GetChildAttr( lpszName, attrname );

      return attr ? attr->get_string() : string("");

   }


   //========================================================
   // Name   : find
   // Desc   : find node with tag lpszName from it's all m_nodea
   // Param  :
   // Return : nullptr return if no found node.
   //--------------------------------------------------------
   // Coder    Date                      Desc
   // bro      2002-10-29
   //========================================================
   node * node::rfind( const char * lpszName, i32 iDepth)
   {
      index i = 0;
      for( ; i < m_nodea.get_size(); i++)
      {
         if(m_nodea[i]->m_strName == lpszName )
            return m_nodea[i];
      }
      if(iDepth == 0)
         return nullptr;
      if(iDepth > 0)
      {
         iDepth--;
      }
      i = 0;
      for( ; i < m_nodea.get_size(); i++)
      {
         node * pnodeChild = m_nodea[i];

         pnodeChild = pnodeChild->rfind(lpszName, iDepth);

         if(pnodeChild != nullptr)

            return pnodeChild;

      }
      return nullptr;
   }


   node * node::rfind(const char * lpszName, const property_set & set, index iDepth)
   {

      for (auto & pnode : m_nodea.ptra())
      {

         if (pnode->m_strName == lpszName && pnode->contains(set))
         {

            return pnode;

         }

      }

      if (iDepth == 0)
      {

         return nullptr;

      }

      if (iDepth > 0)
      {

         iDepth--;

      }

      for (auto & pnode : m_nodea.ptra())
      {

         auto pnodeChild = pnode->rfind(lpszName, set, iDepth);

         if (pnodeChild != nullptr)
         {

            return pnodeChild;

         }

      }

      return nullptr;

   }


   //========================================================
   // Name   : add_child
   // Desc   : add node
   // Param  :
   // Return :
   //--------------------------------------------------------
   // Coder    Date                      Desc
   // bro      2002-10-29
   //========================================================
   node * node::add_child( const char * lpszName /*= nullptr*/, const char * pszValue /*= nullptr*/ )
   {
      
      auto pnode = __new(node((node *) this));
      
      pnode->m_strName = lpszName;

      pnode->m_strValue = pszValue;

      m_nodea.add(pnode);

      return pnode;

   }


   node * node::add_child(const char * lpszName, const property_set & set, const char * pszValue)
   {

      auto pnode = __new(node((node *) this));

      pnode->m_strName = lpszName;

      pnode->m_set = set;

      pnode->m_strValue = pszValue;

      m_nodea.add(pnode);

      return pnode;

   }


   //========================================================
   // Name   : add_child
   // Desc   : add node
   // Param  :
   // Return :
   //--------------------------------------------------------
   // Coder    Date                      Desc
   // bro      2002-10-29
   //========================================================
   node * node::add_child( node * node )
   {
      node->m_pnodeParent = this;
      node->m_pdocument = m_pdocument;
      m_nodea.add( node );
      return node;
   }

   //========================================================
   // Name   : remove_child
   // Desc   : detach node and delete object
   // Param  :
   // Return :
   //--------------------------------------------------------
   // Coder    Date                      Desc
   // bro      2002-10-29
   //========================================================
   bool node::remove_child( node * pnode )
   {

      if(m_nodea.remove(pnode) > 0)
      {

         //   delete pnode;

         return true;

      }

      return false;

   }


   //========================================================
   // Name   : get_attr
   // Desc   : get attr with index in attr list
   // Param  :
   // Return :
   //--------------------------------------------------------
   // Coder    Date                      Desc
   // bro      2002-10-29
   //========================================================
   //attr * node::attr_at( index i )
   //{

   //   return &m_attra.at(i);

   //}


   //========================================================
   // Name   : add_attr
   // Desc   : add attr
   // Param  :
   // Return :
   //--------------------------------------------------------
   // Coder    Date                      Desc
   // bro      2002-10-29
   //========================================================
   //attr * node::add_attr(const ::xml::attr & attr)
   //{

   //   m_attra[attr.name()].set_string(attr.get_value());

   //   return find_attr(attr.name());

   //}

   //========================================================
   // Name   : remove_attr
   // Desc   : detach attr and delete object
   // Param  :
   // Return :
   //--------------------------------------------------------
   // Coder    Date                      Desc
   // bro      2002-10-29
   //========================================================
   //bool node::remove_attr(::xml::attr * pproperty )
   //{

   //   if(m_attra.remove_by_name(pproperty->name()) > 0)
   //   {

   //      //delete pproperty;

   //      return true;

   //   }

   //   return false;

   //}


   //========================================================
   // Name   : add_attr
   // Desc   : add attr
   // Param  :
   // Return :
   //--------------------------------------------------------
   // Coder    Date                      Desc
   // bro      2002-10-29
   //========================================================
// /*   attr * node::add_attr( const char * lpszName /*= nullptr*/, /*const char * pszValue /*= nullptr*/ /*)
   /* {

       ::xml::attr * pproperty = (::xml::attr *) m_attra.add(lpszName, pszValue);

       if(m_pdocument != nullptr)
       {

          if(m_pdocument->m_pedit != nullptr)
          {

             m_pdocument->m_pedit->add_attr(this, pproperty);

          }

       }

       return pproperty;

    }*/

   //========================================================
   // Name   : detach_child
   // Desc   : no delete object, just detach in list
   // Param  :
   // Return :
   //--------------------------------------------------------
   // Coder    Date                      Desc
   // bro      2002-10-29
   //========================================================
   node * node::detach_child( node * node )
   {
      index find = m_nodea.find_first(node);
      if(find >= 0)
      {
         m_nodea.remove_at(find);
         return node;
      }
      return nullptr;
   }

   //========================================================
   // Name   : detach_attr
   // Desc   : no delete object, just detach in list
   // Param  :
   // Return :
   //--------------------------------------------------------
   // Coder    Date                      Desc
   // bro      2002-10-29
   //========================================================
   /*   attr  node::detach_attr(::xml::attr * attr )
      {
         attr = m_attra.m_propertymap[attr]find_first((property *) attr);
         if(find >= 0)
         {
            a
            m_attra.m_propertyptra.remove_at(find);
            return attr;
         }
         return nullptr;
      }*/

   //========================================================
   // Name   : CopyNode
   // Desc   : copy current level node with own attributes
   // Param  :
   // Return :
   //--------------------------------------------------------
   // Coder    Date                      Desc
   // bro      2002-10-29
   //========================================================
   void node::CopyNode( node * node )
   {

      close();

      m_pdocument         = node->m_pdocument;
      m_pnodeParent  = node->m_pnodeParent;
      m_strName      = node->m_strName;
      m_strValue     = node->m_strValue;
      m_etype        = node->m_etype;
      m_set          = node->m_set;

   }

   //========================================================
   // Name   : _CopyBranch
   // Desc   : recursive internal copy branch
   // Param  :
   // Return :
   //--------------------------------------------------------
   // Coder    Date                      Desc
   // bro      2002-10-29
   //========================================================
   void node::_CopyBranch( node * pnode )
   {

      CopyNode(pnode);

      for(auto & pnodeChild : m_nodea)
      {
         
         if(pnodeChild)
         {

            auto pnodeNewChild = __new(class node);

            pnodeNewChild->CopyNode(pnodeChild);

            add_child(pnodeNewChild);

            pnodeNewChild->_CopyBranch(pnodeChild);

         }

      }

   }

   //========================================================
   // Name   : AppendChildBranch
   // Desc   : add child branch ( deep-copy )
   // Param  :
   // Return :
   //--------------------------------------------------------
   // Coder    Date                      Desc
   // bro      2002-10-29
   //========================================================
   node *   node::AppendChildBranch(node * pnode)
   {

      auto pnodeNewChild =__new(class node);

      pnodeNewChild->CopyBranch(pnode);

      return add_child( pnodeNewChild );

   }


   //========================================================
   // Name   : CopyBranch
   // Desc   : copy branch ( deep-copy )
   // Param  :
   // Return :
   //--------------------------------------------------------
   // Coder    Date                      Desc
   // bro      2002-10-29
   //========================================================
   void node::CopyBranch( node * branch )
   {
      close();

      _CopyBranch( branch );
   }


   node *                  node::get_child_at(const char * lpszName, index iIndex, index iDepth)
   {
      if(iDepth == 0)
         return 0;

      if(iIndex < 0)
         return nullptr;

      for(i32 i = 0; i < m_nodea.get_size(); i++)
      {
         if(m_nodea[i]->m_strName == lpszName)
         {
            if(iIndex <= 0)
               return m_nodea.element_at(i);
            iIndex--;
         }
         if(iDepth > 0)
            m_nodea[i]->get_child_at(lpszName, iIndex, iDepth - 1);
         else if(iDepth < 0)
            m_nodea[i]->get_child_at(lpszName, iIndex, -1);
      }
      return nullptr;

   }

   // iDepth
   // -1 recursive
   // 0 nothing
   // 1 children
   // 2 children and children of children
   ::count node::get_child_attr_value(string_array & stra, const char * lpszName, const char * pszAttrName, index iDepth)
   {

      if(iDepth == 0)
         return 0;

      string strValue;
      ::count count = 0;
      for(i32 i = 0; i < m_nodea.get_size(); i++)
      {
         if (!m_nodea[i])
         {

            m_nodea.remove_at(i);
            i--;
            continue;
         }
         if(m_nodea[i]->m_strName == lpszName)
         {
            if(m_nodea[i]->find_attribute(pszAttrName, strValue))
            {
               count++;
               stra.add(strValue);
            }
         }
         if(iDepth > 0)
            count += m_nodea[i]->get_child_attr_value(stra, lpszName, pszAttrName, iDepth - 1);
         else if(iDepth < 0)
            count += m_nodea[i]->get_child_attr_value(stra, lpszName, pszAttrName, -1);
      }
      return count;
   }

   // iDepth
   // -1 recursive
   // 0 nothing
   // 1 children
   // 2 children and children of children
   ::count node::remove_child_with_attr(const char * lpszName, const char * pszAttrName, index iIndex, ::count iCount, index iDepth)
   {

      ::count nRemoveCount = 0;

      if(iDepth == 0)
         return 0;

      string strValue;
      ::count count = 0;
      for(index i = 0; i < m_nodea.get_size(); )
      {
         if(m_nodea[i]->m_strName == lpszName)
         {
            if(m_nodea[i]->find_attribute(pszAttrName, strValue))
            {
               if(iIndex <= 0)
               {
                  if(iCount <= 0)
                  {
                     return count;
                  }
                  else
                  {
                     iCount--;
                     count++;
                     m_nodea.remove_at(i);
                     continue;
                  }
               }
               else
               {
                  iIndex--;
               }
            }
         }
         if(iDepth > 0)
            nRemoveCount = m_nodea[i]->remove_child_with_attr(lpszName, pszAttrName, iIndex, iCount, iDepth - 1);
         else if(iDepth < 0)
            nRemoveCount = m_nodea[i]->remove_child_with_attr(lpszName, pszAttrName, iIndex, iCount, -1);
         if(nRemoveCount > 0)
         {
            count    += nRemoveCount;
            iCount   -= nRemoveCount;
            iIndex   = 0;
            if(iCount <= 0)
            {
               return count;
            }
         }
         i++;
      }
      return count;
   }

   node * node::GetChildByAttr(const char * lpszName, const char * pszAttrName, const char * pszAttrValue)
   {
      string strValue;
      for(i32 i = 0; i < m_nodea.get_size(); i++)
      {
         if(m_nodea[i]->m_strName == lpszName)
         {
            if(m_nodea[i]->find_attribute(pszAttrName, strValue)
                  && ansi_compare_ci(strValue, pszAttrValue) == 0)
            {
               return m_nodea[i];
            }
         }
      }
      return nullptr;
   }

   node * node::GetChildByAnyAttr(const char * lpszName, string_array & straAttrName, string_array & straAttrValue)
   {
      
      string strValue;

      for(i32 i = 0; i < m_nodea.get_size(); i++)
      {

         if(m_nodea[i]->m_strName == lpszName)
         {

            for(i32 j = 0; j < straAttrName.get_size(); j++)
            {

               if(m_nodea[i]->find_attribute(straAttrName[j], strValue) && ansi_compare_ci(strValue, straAttrValue[j]) == 0)
               {

                  return m_nodea[i];

               }

            }

         }

      }

      return nullptr;

   }


   node * node::GetChildByAllAttr(const char * lpszName, string_array & straAttrName, string_array & straAttrValue)
   {
      
      string strValue;
      
      for(i32 i = 0; i < m_nodea.get_size(); i++)
      {
         
         if(m_nodea[i]->m_strName == lpszName)
         {
            
            bool bAll = true;

            for(i32 j = 0; j < straAttrName.get_size(); j++)
            {

               if(!m_nodea[i]->find_attribute(straAttrName[j], strValue) || ansi_compare_ci(strValue, straAttrValue[j]) != 0)
               {

                  bAll = false;

                  break;

               }

            }

            if(bAll)
            {

               return m_nodea[i];

            }

         }

      }

      return nullptr;

   }


   void node::close()
   {

      m_nodea.remove_all();

      //m_pset.release();

   }


   bool node::from_row_column_v2(const string2a & str2a)
   {

      m_strName = "row_column_v2";

      if(str2a.get_size() <= 0)
      {

         m_strValue.Empty();

         set_attribute("column_count", 0);

         m_nodea.remove_all();

      }
      else
      {
      
         ::count iColCount = str2a.get_count();

         set_attribute("column_count", iColCount);

         ::count iRowCount;

         for(index iCol = 0; iCol < iColCount; iCol++)
         {

            __pointer(::xml::node) pcol = add_child("ca");

            iRowCount = str2a[iCol].get_count();

            pcol->set_attribute("row_count", iRowCount);

            for(i32 iRow = 0; iRow < iRowCount; iRow++)
            {

               if(iRow < str2a[iCol].get_count())
               {

                  pcol->m_strValue = str2a[iCol][iRow];

               }

            }

         }

      }

      return true;

   }


   bool node::to_row_column_v2(string2a & str2a)
   {

      // "this is not a row column v2 xml node";
      if (m_strName != "row_column_v2")
      {

         return false;

      }

      ::count iColCount = attribute("column_count");

      if(m_nodea.get_count() == 0 ||  iColCount <= 0)
      {

         str2a.remove_all();

         return true;

      }

      str2a.set_size(iColCount);

      ::count iRowCount = 0;

      __pointer(::xml::node) pheader = m_nodea.element_at(0);

      for(::index iCol = 0; iCol < iColCount; iCol++)
      {

         __pointer(::xml::node) pcol = pheader->m_nodea.element_at(iCol);

         str2a[iCol].set_size(pcol->attribute("row_count"));

      }

      for(::index iRow = 0; iRow < iRowCount; iRow++)
      {

         for(i32 iCol = 0; iCol < str2a[iCol].get_count(); iCol++)
         {

            if(iRow < str2a[iCol].get_count())
            {

               iRowCount = str2a[iCol].get_count();

            }

         }

      }

      return true;

   }


   stream & node::write(::stream & stream) const
   {

      string str;

      str = get_xml();

      stream.write(str);

      return stream;

   }


   stream & node::read(::stream & stream)
   {

      string str;

      stream.read(str);

      load(str);

      return stream;

   }

   

   void node::set_name(const string & strName)
   {

      m_strName = strName;

      if(m_pdocument != nullptr)
      {

         if(m_pdocument->m_pedit != nullptr)
         {

            m_pdocument->m_pedit->set_name(this);

         }

      }

   }

   void node::set_value(const string & strValue)
   {

      m_strValue = strValue;

      if(m_pdocument != nullptr)
      {

         if(m_pdocument->m_pedit != nullptr)
         {

            m_pdocument->m_pedit->set_value(this);

         }

      }

   }

   string node::get_simple_path() const
   {

      return get_document()->get_child_simple_path(this);

   }

   index_array node::get_indexed_path() const
   {

      return get_document()->get_child_indexed_path(this);

   }

   void node::get_indexed_path(index_array & iaPath) const
   {

      return get_document()->get_child_indexed_path(iaPath, this);

   }

   index node::get_index() const
   {

      if(m_pnodeParent == nullptr)
         return -1;


      for(index iIndex = 0; iIndex < m_pnodeParent->m_nodea.get_count(); iIndex++)
      {

         if(m_pnodeParent->m_nodea.element_at(iIndex) == this)
            return iIndex;

      }

      return -1;

   }


} // namespace xml
