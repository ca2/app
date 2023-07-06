#include "framework.h"
#include "node.h"
#include "document.h"
#include "edit.h"
#include "xml.h"
#include "xmlite.h"
#include "entity.h"
#include "parse_info.h"
#include "disp_option.h"
#include "exception.h"
#include "acme/exception/parsing.h"
#include "acme/platform/system.h"
#include "acme/primitive/string/str.h"
#include "acme/exception/extended_status.h"


// https://www.codeproject.com/Articles/3426/XMLite-simple-XML-parser


namespace xml
{



   //static const char '<'      = ;
   //static const char '>'   = '>';
   //static const char '/'   = '/';
   //static const char '\\' = '\\';   // for m_strValue field escape


   node::node()
   {
      m_iFirstXmlNode = -1;
      m_pxmlnode = this;
      m_pdocument                  = nullptr;
      m_enode                 = ::data::e_node_xml_document;

   }


   node::node(::xml::node * pnodeParent)
   {

      initialize(pnodeParent);

      m_iFirstXmlNode = -1;
      m_pxmlnode = this;
      m_pnodeParent           = pnodeParent;
      m_pdocument                  = pnodeParent->m_pdocument;
      m_enode = ::data::e_node_xml_element;

   }


   node::node(const node & node) 
   {

      operator = (node);

   }


   node::~node()
   {

      close();

   }


   ::xml::document* node::get_xml_document() const
   {

      return nullptr;

   }


   node & node::operator = (const node & node)
   {

      throw unexpected_situation();

      //if(&node == this)
      //   return *this;

      //m_strName   = node.m_strName;
      //m_strValue  = node.m_strValue;
      //m_nodea     = node.m_nodea;
      //m_ppropertyset      = __new(property_node.m_attra;

      return *this;

   }


   //::payload node::attr(const ::scoped_string & scopedstrName)
   //{

   //   return set(pcszName);

   //}


   //bool node::get_attr(const ::scoped_string & scopedstrName, string & strValue)

   //{
   //   if(!m_attra.has_property(pcszName))

   //      return false;
   //   strValue = m_attra[pcszName];

   //   return true;
   //}

   //bool node::get_attr(const ::scoped_string & scopedstrName, i32 & iValue)

   //{
   //   if(!m_attra.has_property(pcszName))

   //      return false;
   //   iValue = m_attra[pcszName];

   //   return true;
   //}

   //bool node::get_attr(const ::scoped_string & scopedstrName, bool & bValue)

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


   property * node::set_attribute(const ::atom & atom, const ::payload & payload)
   {

      auto & property = m_set.get(atom);

      property = payload;

      if(::is_set(m_pdocument))
      {

         if(::is_set(m_pdocument->m_pedit))
         {

            m_pdocument->m_pedit->set_attribute(this, &property);

         }

      }

      return &property;

   }


   index node::find(const ::scoped_string & scopedstrName, const property_set & set, index iStart)
   {

      for(index i = iStart; i < m_nodea.get_count(); i++)
      {

         if (m_nodea[i]->m_strName == scopedstrName && m_nodea[i]->m_set.contains(set))
         {

            return i;

         }

      }

      return -1;

   }


   node * node::get_child_with_attribute(const ::scoped_string & scopedstrName, const ::atom & atom, const ::payload & payload, index iStart)
   {

      for(index i = iStart; i < m_nodea.get_count(); i++)
      {

         if (m_nodea[i]->m_strName == scopedstrName && m_nodea[i]->attribute(atom) == payload)
         {

            return m_nodea[i]->get_xml_node();

         }

      }

      return nullptr;

   }


   index node::find(const ::scoped_string & scopedstrName, index iStart)
   {

      for(index i = iStart; i < m_nodea.get_count(); i++)
      {

         if (m_nodea[i]->m_strName == scopedstrName)
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
   node & node::FindNode(const ::scoped_string & scopedstrName,i32 iPos)

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
      auto pnodeParent = __xml(m_pnodeParent);
      index i = pnodeParent->find(this);
      if (i < 0)
      {

         throw ::parsing_exception("strange: this is not child of this->parent");

      }
      i++;
      if(i >= pnodeParent->get_children_count())
         return nullptr;
      return pnodeParent->child_at(i);
   }


   node * node::first_child()
   {

      if (m_nodea.get_count() <= 0)
      {
      
         return nullptr;

      }

      return child_at(0);

   }


   void node::LoadDocType(::ansi_range & rangeXml, parse_info * pparseinfo)
   {

      auto pxml = acmesystem()->xml();

      if (pparseinfo == nullptr)
      {
      
         pparseinfo = pxml->m_pparseinfoDefault;

      }

      if (rangeXml.m_begin[0] != '<' || rangeXml.m_begin[1] != '!')
      {

         return;

      }

      rangeXml.consume("<!DOCTYPE");
      rangeXml.consume_spaces();
      rangeXml.consume_nc_name();

      rangeXml.consume_spaces(0);
      if(rangeXml.begins_consume("SYSTEM"))
      {
         rangeXml.consume_spaces();
         rangeXml.consume_quoted_value();
      }
      else if(rangeXml.begins_consume("PUBLIC"))
      {
         rangeXml.consume_spaces();
         rangeXml.consume_quoted_value();
         rangeXml.consume_spaces();
         rangeXml.consume_quoted_value();
      }

      rangeXml.consume_spaces(0);

      //markup decl
      if(*rangeXml.m_begin == '[')
      {
         rangeXml.consume("[");

         while(*rangeXml.m_begin != ']')
         {
            if(rangeXml.begins_consume("<!ENTITY"))
            {
               rangeXml.consume_spaces();
               string entity_name;
               entity_name = rangeXml.consume_nc_name();
               rangeXml.consume_spaces();
               string entity_value;
               string ext_entity_value;
               if(rangeXml.begins_consume("SYSTEM"))
               {
                  rangeXml.consume_spaces();
                  ext_entity_value = rangeXml.consume_quoted_value();
               }
               else if (rangeXml.begins_consume("PUBLIC"))
               {
                  rangeXml.consume_spaces();
                  rangeXml.consume_quoted_value();
                  rangeXml.consume_spaces();
                  ext_entity_value = rangeXml.consume_quoted_value();
               }
               else
               {
                  entity_value = rangeXml.consume_quoted_value();
               }
               if(entity_value.has_char())
               {
                  ::__construct(m_pdocument, m_pdocument->m_pentitiesHash);
                  ::__defer_construct(m_pdocument, m_pdocument->m_pentitiesHash);
                  m_pdocument->m_pentitiesHash->set_at(entity_name, entity_value);
               }
               if(ext_entity_value.has_char())
               {
                  ::__defer_construct(m_pdocument, m_pdocument->m_pentitiesExtHash);
                  m_pdocument->m_pentitiesExtHash->set_at(entity_name, ext_entity_value);
               }
            }
            else if(rangeXml.xml_is_comment())
            {
               rangeXml.xml_consume_comment();
            }
            rangeXml.m_begin++;
         }
         rangeXml.consume("]");
         rangeXml.consume_spaces(0);
      }


      rangeXml.consume(">");


      //return (char *) pszXml;
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
   void node::LoadAttributes(::ansi_range & rangeXml, parse_info * pparseinfo)
   {

      if(pparseinfo == nullptr)
      {

         pparseinfo = acmesystem()->xml()->m_pparseinfoDefault;

      }

      while(rangeXml.has_char() && *rangeXml.m_begin != '\0')
      {

         rangeXml.consume_spaces(0);

         if (rangeXml.is_empty())
         {

            break;

         }

         if(*rangeXml.m_begin == '>' || *rangeXml.m_begin == '/')
         {

            return;

         }

         auto pszStart = rangeXml.m_begin;

         rangeXml.consume_until_any_character_in(" =");

         if(rangeXml.is_empty())
         {

            string strError;

            strError.format("<%s> attr has error ", m_strName.c_str());

            throw ::xml::exception(e_parse_error_attr_no_value, strError, pszStart);

            return;

         }

         string strName;

         _SetString({pszStart, rangeXml.m_begin}, &strName);

         auto & property = m_set.get(strName);

         rangeXml.consume_spaces(0);

         if (rangeXml.is_empty())
         {

            break;

         }

         if(rangeXml.begins_consume('='))
         {

            rangeXml.consume_spaces(0);

            if (rangeXml.is_empty())
            {

               break;

            }

            const ::ansi_character * pszStart;

            bool trim = pparseinfo->m_bTrimValue;

            bool bQuote;

            ::ansi_character ansichQuote;

            if(rangeXml.begins_consume(ansichQuote, '"') || rangeXml.begins_consume(ansichQuote, '\''))
            {

               pszStart = rangeXml.m_begin;

               rangeXml.escape_skip_to_character(ansichQuote, pparseinfo->m_chEscape);

               bQuote = true;

            }
            else
            {

               pszStart = rangeXml.m_begin;

               rangeXml.escape_skip_to_first_character_in(" >", pparseinfo->m_chEscape);

               bQuote = false;

            }

            string strValue;

            _SetString({ pszStart, rangeXml.m_begin }, &strValue, trim, pparseinfo->m_chEscape);

            property = strValue;

            if(pparseinfo->m_bEntityValue && pparseinfo->m_pentities)
            {

               property = pparseinfo->m_pentities->ref_to_entity(property.as_string());

            }

            if(bQuote)
            {

               if(rangeXml.is_empty() || *rangeXml.m_begin == '\0')
               {

                  return;

               }
               else
               {

                  rangeXml.m_begin++;

               }

            }

         }

      }

      throw parsing_exception("Not wel-formed tag");

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
   void node::LoadProcessingInstruction(::ansi_range & rangeXml, parse_info * pparseinfo)
   {
      
      if (pparseinfo == nullptr)
      {

         pparseinfo = acmesystem()->xml()->m_pparseinfoDefault;

      }

      auto pszStart = rangeXml.m_begin;

      // find the end of pparseinfo
      rangeXml.escape_case_insensitive_skip_to("?>", pparseinfo ? pparseinfo->m_chEscape : 0 );

      if (rangeXml.is_empty())
      {

         return;

      }

      auto pszEnd = rangeXml.m_begin;

      rangeXml.consume_spaces();

      if (rangeXml.is_empty())
      {

         throw parsing_exception("Not wel-formed Processing Instruction");

      }

      // process pparseinfo
      if( m_pdocument )
      {

         ::pointer<node>pnode = __new(node(this));
         pnode->m_pnodeParent = this;
         pnode->m_pdocument = m_pdocument;
         pnode->m_enode = ::data::e_node_xml_pi;

         const char* pTagEnd = ::ansi_range(pszStart, rangeXml.m_end).find_first_character_in(" ?>");

         _SetString({ pszStart, pTagEnd }, &pnode->m_strName);

         rangeXml.m_begin = pTagEnd;

         pnode->LoadAttributes(rangeXml, pparseinfo);

         m_pdocument->m_nodea.add( pnode );

      }

      rangeXml.m_begin += 2; // "?>";

      //return end;

   }


//   // attr1="value1" attr2='value2' attr3=value3 />
//   //                                            ^- return pointer
//   //========================================================
//   // Name   : LoadAttributes
//   // Desc   : loading attr plain xml text
//   // Param  : pszAttrs - xml of attributes
//   //          pszEnd - last string
//   //          pparseinfo = parser information
//   // Return : advanced string pointer. (error return nullptr)
//   //--------------------------------------------------------
//   // Coder    Date                      Desc
//   // bro      2004-06-14
//   //========================================================
//   void node::LoadAttributes(::ansi_range & rangeXml, parse_info * pparseinfo)
//   {
//      
//      if (pparseinfo == nullptr)
//      {
//
//         pparseinfo = acmesystem()->xml()->m_pparseinfoDefault;
//
//      }
//
//      while(rangeXml.has_char() && *rangeXml.m_begin)
//      {
//
//         rangeXml.consume_spaces(0);
//
//         if (rangeXml.is_empty())
//         {
//
//            // close tag
//            // wel-formed tag
//            return;
//
//         }
//
//         const char * pszStart = rangeXml.m_begin;
//
//         // XML Attr Name
//         auto pszEnd = rangeXml.find_first_character_in(" =");
//
//         if(::not_found(pszEnd))
//         {
//            //// error
//            //if( pparseinfo->m_bErrorOccur == false )
//            //{
//            //   pparseinfo->m_bErrorOccur = true;
//            //   pparseinfo->m_pszErrorPointer = xml;
//            //   pparseinfo->m_eparseerror = e_parse_error_attr_no_value;
//            //   pparseinfo->m_strError.format( "<%s> attr has error ", m_strName.c_str() );
//            //}
//
//            string strError;
//
//            strError.format("<%s> attr has error ", m_strName.c_str());
//
//            throw ::xml::exception(e_parse_error_attr_no_value, strError, rangeXml.m_begin);
//
//            return;
//
//         }
//
//         string strName;
//         // XML Attr Name
//         _SetString({ pszStart, pszEnd }, &strName);
//
//         // add memory_new attr
//         auto & property = m_set.get(strName);
//
//         rangeXml.consume_spaces(0);
//
//         // XML Attr Value
////         if( (xml = _tcsskip( xml )) )
//  //       {
//            //if( xml = strchr( xml, '=' ) )
//         if( *rangeXml.m_begin == '=' )
//         {
//
//            rangeXml.consume_spaces(0);
//            //if( (xml = _tcsskip( ++xml )) )
//            //{
//               // if " or '
//               // or none quote
//               i32 quote = *rangeXml.m_begin;
//
//               pszStart = rangeXml.m_begin;
//
//               if (quote == '"' || quote == '\'')
//               {
//
//                  pszStart++;
//
//                  rangeXml.escape_find_character(quote, pparseinfo->m_chEscape);
//
//               }
//               else
//               {
//                  
//                  //attr= m_strValue>
//                  // none quote mode
//                  //pszEnd = _tcsechr( xml, ' ', '\\' );
//                  ::str::escape_skip_any_character_in(rangeXml, " >", pparseinfo->m_chEscape);
//
//               }
//
//               bool trim = pparseinfo->m_bTrimValue;
//
//               char escape = pparseinfo->m_chEscape;
//
//               //_SetString( xml, pszEnd, &attr->m_strValue, trim, '\\' );
//               
//               _SetString({ pszStart, rangeXml.m_begin }, &property.string_reference(), trim, escape);
//
////               pszStart = pszEnd;
//
//               // ATTRVALUE
//               if (pparseinfo->m_bEntityValue && pparseinfo->m_pentities)
//               {
//
//                  property = pparseinfo->m_pentities->ref_to_entity(property.get_string());
//
//               }
//
//               if (quote == '"' || quote == '\'')
//               {
//
//                  rangeXml.m_begin++;
//
//               }
//
//            }
//         //}
//   //     }
//      }
//
//      // not wel-formed tag
//      //return nullptr;
//
//      throw ::parsing_exception("Not wel-formed tag");
//
//   }

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
   void node::LoadComment(::ansi_range & rangeXml, parse_info * pparseinfo)
   {

      if (pparseinfo == nullptr)
      {

         pparseinfo = acmesystem()->xml()->m_pparseinfoDefault;

      }

      auto pszStart = rangeXml.m_begin;

      // find the end of comment
      rangeXml.escape_case_insensitive_skip_to("-->", pparseinfo ? pparseinfo->m_chEscape : 0 );
      
      if (rangeXml.is_empty())
      {

         throw parsing_exception("Not wel-formed Comment");

      }

      // process comment
      node * pnodeParent = __xml(m_pnodeParent);

      if (::is_null(pnodeParent) && m_pdocument)
      {
      
         pnodeParent = m_pdocument;

      }

      if(pnodeParent)
      {

         //const char * xml =pszXml;
         //xml += 4; // "<!--";

         auto pnode = __new(node(this));
         pnode->m_pnodeParent = pnodeParent;
         pnode->m_pdocument = m_pdocument;
         pnode->m_enode = ::data::e_node_xml_comment;
         pnode->m_strName = "#COMMENT";
         _SetString({ pszStart, rangeXml.m_begin }, &pnode->m_strValue, false);

         pnodeParent->m_nodea.add( pnode );

      }

      rangeXml.m_begin += 3; // "-->"

      //return end;

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
   void node::LoadCDATA(::ansi_range & rangeXml, parse_info * pparseinfo)
   {

      if (pparseinfo == nullptr)
      {

         pparseinfo = acmesystem()->xml()->m_pparseinfoDefault;

      }

      auto pszStart = rangeXml.m_begin;

      // find the end of CDATA
      rangeXml.escape_case_insensitive_skip_to("]]>", pparseinfo ? pparseinfo->m_chEscape : 0 );

      auto pszEnd = rangeXml.m_begin;
      
      if (rangeXml.is_empty())
      {

         throw parsing_exception("Not wel-formed CDATA");

      }

      // process CDATA
      node * pnodeParent = __xml(m_pnodeParent);
      if( m_pnodeParent == nullptr && m_pdocument )
         pnodeParent = (node *)&m_pdocument;
      if( pnodeParent )
      {
         //const char * xml = pszXml;
         //xml += 9;  // "<![CDATA["

         auto pnode = __new(node(this));
         pnode->m_pnodeParent = this;
         pnode->m_pdocument = m_pdocument;
         pnode->m_enode = ::data::e_node_xml_cdata;
         pnode->m_strName = "#CDATA";
         _SetString({pszStart, pszEnd}, &pnode->m_strValue, false );

         pnodeParent->m_nodea.add( pnode );
      }

      rangeXml.m_begin += 3; // "]]>"
      
      //return end;

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
   void node::LoadOtherNodes(bool* pbRet, ansi_range & rangeXml, parse_info * pparseinfo)
   {
      
      if (pparseinfo == nullptr)
      {

         pparseinfo = acmesystem()->xml()->m_pparseinfoDefault;

      }

      auto pszStart = rangeXml.m_begin;

      //const char * xml = pszXml;
      bool do_other_type = true;
      *pbRet = false;

      while( rangeXml.has_char() && do_other_type)
      {
         do_other_type = false;

         rangeXml.consume_spaces(0);
         const char * prev = rangeXml.m_begin;
         // is PI( Processing Instruction ) Node?
         if(rangeXml.begins_consume("<?"))
         {
            // processing instrunction parse
            // return pointer is next node of pparseinfo
            LoadProcessingInstruction(rangeXml, pparseinfo);
            if( rangeXml.is_empty())
               return;
            // restart xml parse
         }

         if( rangeXml.m_begin != prev )
            do_other_type = true;
         rangeXml.consume_spaces(0);
         prev = rangeXml.m_begin;

         //if(m_pnodeParent != nullptr && m_pnodeParent->m_enode == ::data::e_node_xml_document)
         if (m_enode == ::data::e_node_xml_document)
         {
            // is DOCTYPE
            if(rangeXml.case_insensitive_begins_eat("<!DOCTYPE"))
            {
               // processing instrunction parse
               // return pointer is next node of pparseinfo
               LoadDocType( rangeXml, pparseinfo );
               //if( rangeXml.is_empty())
                 // return nullptr;
               // restart xml parse
            }

            if( rangeXml.m_begin != prev )
               do_other_type = true;
            rangeXml.consume_spaces(0);
            prev = rangeXml.m_begin;
         }

         // is comment Node?
         if (rangeXml.begins_consume("<!--"))
         {
            // processing comment parse
            // return pointer is next node of comment
            LoadComment( rangeXml, pparseinfo );
            // comment node is terminal node
            if(m_enode != ::data::e_node_xml_document && rangeXml.m_begin != prev )
            {
               *pbRet = true;
               rangeXml.consume_spaces(0);
               //return xml;
               return;
            }
            // restart xml parse when this node is root m_pdocument node
         }

         if( rangeXml.m_begin != prev )
            do_other_type = true;

         rangeXml.consume_spaces(0);
         prev = rangeXml.m_begin;
         // is CDATA Node?
         if(rangeXml.case_insensitive_begins_eat("<![CDATA["))
         {
            // processing CDATA parse
            // return pointer is next node of CDATA
            LoadCDATA(rangeXml, pparseinfo );
            // CDATA node is terminal node
            if(m_enode != ::data::e_node_xml_document && rangeXml.m_begin != prev )
            {
               *pbRet = true;
               //return xml;

               return;
            }
            // restart xml parse when this node is root m_pdocument node
         }

         if( rangeXml.m_begin != prev )
            do_other_type = true;
      }

      //return xml;
   }

   
   void node::load(const ::string & strXml, parse_info * pparseinfo)
   {

      auto rangeXml = strXml();

      const ::ansi_character * pszNext = nullptr;

      close();

      _load(rangeXml, pparseinfo);

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
   void node::_load(::ansi_range & rangeXml, parse_info * pparseinfo)
   {

      ////// close it
      //close();


      // Changed xmlite node loading...
      // XML does accept only one root one
      // This implementation allow multiple nodes in the root (apart other nodes)



      while (true)
      {

         if (pparseinfo == nullptr)
         {

            pparseinfo = acmesystem()->xml()->m_pparseinfoDefault;

         }

         rangeXml.m_begin = strchr(rangeXml.m_begin, '<');

         if (rangeXml.m_begin == nullptr)
         {

            return;

         }

         //// close Tag
         if (*(rangeXml.m_begin + 1) == '/') // </close
         {

            return;

         }

         //// Load Other Node before <Tag>(Processing Instruction, Comment, CDATA etc)

         bool bRet = false;

         LoadOtherNodes(&bRet, rangeXml, pparseinfo);

         if (bRet)
         {

            return;

         }

         
         ////pnode->_load(xml, xml, pszEndXml, pparseinfo);
         //if (pnode->m_strName.has_char())
         //{
         //   m_nodea.add(pnode);

         //   //                  ::release(pnode);
         //}
         //else
         //{
         //   //delete pnode;
         //   pnode.release();
         //}

         ::pointer<node>pnode = __new(node(this));
         //pnode->m_pnodeParent = this;
         //pnode->m_pdocument = m_pdocument;
         //pnode->m_enode = m_enode;

         // XML Node Tag Name open
         rangeXml.m_begin++;

         auto pszStart = rangeXml.m_begin;

         rangeXml.consume_until_any_character_in(" />\t\r\n");
         _SetString({ pszStart, rangeXml.m_begin }, &pnode->m_strName);
         //rangeXml.m_begin = pTagEnd;
         // Generate XML Attributte List
         //if ((xml = pnode->LoadAttributes(rangeXml, pparseinfo)))
         pnode->LoadAttributes(rangeXml, pparseinfo);
         //{
            // alone tag <TAG ... />

         if (*rangeXml.m_begin == '/')
         {

            auto pszStart = rangeXml.m_begin;

            rangeXml.m_begin++;

            if (*rangeXml.m_begin == '>')
            {

               // wel-formed tag
               rangeXml.m_begin++;

               //return;

            }
            else
            {
               //// error: <TAG ... / >
               //if( pparseinfo->m_bErrorOccur == false )
               //{
               //   pparseinfo->m_bErrorOccur = true;
               //   pparseinfo->m_pszErrorPointer = xml;
               //   pparseinfo->m_eparseerror = e_parse_error_alone_not_closed;
               //   pparseinfo->m_strError = "Element must be closed.";
               //}

               string strError;

               strError = "Element must be closed.";

               throw ::xml::exception(e_parse_error_alone_not_closed, strError, pszStart);

               // not wel-formed tag
               return;

            }

         }
         else if (*rangeXml.m_begin)
            // open/close tag <TAG ..> ... </TAG>
            //                        ^- current pointer
         {
            // if text m_strValue is not exist, then assign m_strValue
            //if( this->m_strValue.is_empty() || this->m_strValue == "" )
            if (::str::trimmed_is_empty(pnode->m_strValue))
            {

               // Text Value
               rangeXml.m_begin++;

               auto pszStart = rangeXml.m_begin;

               rangeXml.escape_skip_to_character('<', '\\');

               if (rangeXml.is_empty())
               {
                  //if( pparseinfo->m_bErrorOccur == false )
                  //{
                  //   pparseinfo->m_bErrorOccur = true;
                  //   pparseinfo->m_pszErrorPointer = xml;
                  //   pparseinfo->m_eparseerror = e_parse_error_not_closed;
                  //   pparseinfo->m_strError.format("%s must be closed with </%s>", m_strName.c_str() );
                  //}

                  string strError;

                  strError.format(" % s must be closed with < / % s>", pnode->m_strName.c_str());

                  throw ::xml::exception(e_parse_error_not_closed, strError, pszStart);

                  // error cos not exist CloseTag </TAG>
                  return;

               }

               bool trim = pparseinfo->m_bTrimValue;
               char escape = pparseinfo->m_chEscape;
               //_SetString( xml, pszEnd, &m_strValue, trim, '\\' );
               //pszEnd = xml;
               //rangeXml.m_begin = strchr(rangeXml.m_begin, '<');
               //while (*pszEnd != '<' && *pszEnd != '\0')
               //{
               //   //   if(pszEnd[0] == '&')
               //   ////   {
               //   ////      pszEnd = m_pdocument->patch_entity_ref((const char * &) pszEnd, true, &xml, nullptr);
               //   ////   }
               //   ////   else
               //   ////   {
               //   unicode_increment(pszEnd);
               //   //   }
               //}
               _SetString({ pszStart, rangeXml.m_begin }, &pnode->m_strValue, trim, escape);
               //xml = pszEnd;

               // TEXTVALUE object
               if (pparseinfo->m_bEntityValue && pparseinfo->m_pentities)
                  pnode->m_strValue = pparseinfo->m_pentities->ref_to_entity(pnode->m_strValue);
            }

            // generate child nodes
            if(rangeXml.has_char() && *rangeXml.m_begin)
            {
               //::pointer<node>pnode = __new(node(this));
               //if (m_pdocument == this)
               //{
               //   if (!m_pdocument->m_pnodeRoot)
               //   {

               //      m_pdocument->m_pnodeRoot = pnode;

               //   }

               //}
               //pnode->m_pnodeParent = this;
               //pnode->m_pdocument = m_pdocument;
               //pnode->m_enode = m_enode;

               pnode->_load(rangeXml, pparseinfo);
               //if (pnode->m_strName.has_char())
               //{
               //   m_nodea.add(pnode);

               //   //                  ::release(pnode);
               //}
               //else
               //{
               //   //delete pnode;
               //   pnode.release();
               //}

               // open/close tag <TAG ..> ... </TAG>
               //                             ^- current pointer
               // CloseTag case
               if (rangeXml.has_char() && *rangeXml.m_begin && *(rangeXml.m_begin + 1) && *rangeXml.m_begin == '<' && *(rangeXml.m_begin + 1) == '/')
               {
                  // </close>
                  rangeXml.m_begin += 2; // C

                  rangeXml.consume_spaces(0);

                  //if ((xml = _tcsskip(xml)))
                  {

                     auto pszStart = rangeXml.m_begin;
                     
                     string closename;

                     const char * pszEnd = rangeXml.find_first_character_in(" >");

                     if (pszEnd == nullptr)
                     {
                        //if( pparseinfo->m_bErrorOccur == false )
                        //{
                        //   pparseinfo->m_bErrorOccur = true;
                        //   pparseinfo->m_pszErrorPointer = xml;
                        //   pparseinfo->m_eparseerror = parse_error_not_closed;
                        //   pparseinfo->m_strError.format("it must be closed with </%s>", m_strName.c_str() );
                        //}
                        //// error

                        string strError;

                        strError.format("it must be closed with </%s>", pnode->m_strName.c_str());

                        throw ::xml::exception(e_parse_error_not_closed, strError, rangeXml.m_begin);

                        return;

                     }

                     _SetString({ pszStart, pszEnd }, & closename);

                     if (closename == pnode->m_strName)
                     {
                        // wel-formed open/close
                        rangeXml.m_begin = pszEnd + 1;
                        // return '>' or ' ' after pointer
                        //return;
                     }
                     else
                     {
                        rangeXml.m_begin = pszEnd + 1;
                        // 2004.6.15 - example <B> alone tag
                        // now it can parse with attr 'force_arse'
                        if (pparseinfo->m_bForceParse == false)
                        {
                           // not welformed open/close
                           //if( pparseinfo->m_bErrorOccur == false )
                           //{
                           //   pparseinfo->m_bErrorOccur = true;
                           //   pparseinfo->m_pszErrorPointer = xml;
                           //   pparseinfo->m_eparseerror = e_parse_error_not_nested;
                           //   pparseinfo->m_strError.format("'<%s> ... </%s>' is not wel-formed.", m_strName.c_str(), closename.c_str() );
                           //}

                           string strError;

                           strError.format("'<%s> ... </%s>' is not wel-formed.", pnode->m_strName.c_str(), closename.c_str());

                           throw ::xml::exception(e_parse_error_not_nested, strError, pszStart);

                           return;

                        }

                     }

                  }

               }
               else if (rangeXml.has_char() && *rangeXml.m_begin)  // Alone child Tag Loaded
                  // else "I wonder if I should or shouldn't"(TranslatedFromKorean).
               {

                  //if( xml && this->m_strValue.is_empty() && *xml !='<' )
                  if (rangeXml.has_char() && ::str::trimmed_is_empty(pnode->m_strValue) && *rangeXml.m_begin != '<')
                  {
                     // Text Value
                     auto pszStart = rangeXml.m_begin;
                     rangeXml.escape_skip_to_character('<', '\\');
                     if (rangeXml.is_empty())
                     {
                        // error cos not exist CloseTag </TAG>
                        //if( pparseinfo->m_bErrorOccur == false )
                        //{
                        //   pparseinfo->m_bErrorOccur = true;
                        //   pparseinfo->m_pszErrorPointer = xml;
                        //   pparseinfo->m_eparseerror = parse_error_not_closed;
                        //   pparseinfo->m_strError.format("it must be closed with </%s>", m_strName.c_str() );
                        //}
                        string strError;

                        strError.format("it must be closed with </%s>", pnode->m_strName.c_str());

                        throw ::xml::exception(e_parse_error_not_closed, strError, pszStart);

                        return;

                     }

                     bool trim = pparseinfo->m_bTrimValue;
                     char escape = pparseinfo->m_chEscape;
                     //_SetString( xml, pszEnd, &m_strValue, trim, '\\' );
                     //pszEnd = xml;
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
                     //if (pszEnd > pszEndXml)
                       // pszEnd = (char *)pszEndXml;
                     _SetString({pszStart, rangeXml.m_begin}, &pnode->m_strValue, trim, escape);
                     //xml = pszEnd;
                     //TEXTVALUE
                     if (pparseinfo->m_bEntityValue && pparseinfo->m_pentities)
                     {

                        pnode->m_strValue = pparseinfo->m_pentities->ref_to_entity(pnode->m_strValue);

                     }

                  }

               }

            }

         }

//         }

         if (pnode->m_strName.has_char())
         {

            m_nodea.add(pnode);

            if (m_iFirstXmlNode < 0)
            {

               m_iFirstXmlNode = m_nodea.get_upper_bound();

            }

         }
         else
         {

            pnode.release();

         }

      }

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

         opt = ((node *) this)->acmesystem()->xml()->m_poptionDefault;

      }

      if( m_enode == ::data::e_node_xml_document )
      {

         for (i32 i = 0; i < m_nodea.get_size(); i++)
         {

            auto pnode = m_nodea[i];

            auto pxmlnode = pnode->get_xml_node();

            ostring += pxmlnode->get_xml(opt);

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

         if (m_enode == ::data::e_node_xml_pi)
         {
            // <?TAG
            ostring += "<?" +m_strName;
            // <?TAG Attr1="Val1"
            if (m_set.has_elements())
            {

               ostring += ' ';
            }

            auto pxml = ((node*)this)->acmesystem()->m_pxml;

            for (auto & pproperty : m_set)
            {
               ostring += pxml->from(pproperty, opt);
            }
            //?>
            ostring += "?>";
            return ostring;
         }
         else if (m_enode == ::data::e_node_xml_comment)
         {
            // <!--comment
            ostring += "<!--" + m_strValue;
            //-->
            ostring += "-->";
            return ostring;
         }
         else if (m_enode == ::data::e_node_xml_cdata)
         {
            // <--comment
            ostring += "<![CDATA[" + m_strValue;
            //-->
            ostring += "]]>";
            return ostring;
         }

      }

      // <TAG
      ostring += '<' + m_strName;

      // <TAG Attr1="Val1"
      //if (m_set.has_elements())
        // ostring += ' ';

      auto pxml = ((node*)this)->acmesystem()->xml();

      for (auto & pproperty : m_set)
      {

         ostring += " ";

         ostring += pxml->from(pproperty, opt);

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
            
            auto pnode = m_nodea[i];
            
            if(!pnode)
            {
               
               continue;
               
            }
            
            auto pxmlnode = pnode->get_xml_node();
            
            string strXml;
            
            strXml = pxmlnode->get_xml(opt);
             
            ostring += strXml;

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

         string strTrimmedValue;
         
         strTrimmedValue = m_strValue;

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

         ostring += "</" + m_strName + ">";

         opt->m_iTabBase--;

      }

      return ostring;

   }


   //==Translated from Korean
   //================================================= ========
   // function name: GetText
   // Description: Returns one node as a text string
   // factor :
   // return value: converted string
   //------------------------------------------------ --------
   // Author Date of creation Reason for creation
   // Cho Gyeong-min 2004-06-15
   //================================================= ========
   string node::get_text( disp_option * opt /*= &optDefault*/ ) const
   {

      string ostring;

      if(opt == nullptr)
      {
         opt = ((node*)this)->acmesystem()->xml()->m_poptionDefault;
      }

      if( m_enode == ::data::e_node_xml_document )
      {
         for( i32 i = 0 ; i < m_nodea.get_size(); i++ )
            ostring += m_nodea[i]->get_xml_node()->get_text( opt );
      }
      else if( m_enode == ::data::e_node_xml_pi )
      {
         // no text
      }
      else if( m_enode == ::data::e_node_xml_comment )
      {
         // no text
      }
      else if( m_enode == ::data::e_node_xml_cdata )
      {
         ostring += m_strValue;
      }
      else if( m_enode == ::data::e_node_xml_element )
      {
         if( m_nodea.is_empty() && m_strValue.is_empty() )
         {
            // no text
         }
         else
         {
            // m_nodea text
            for( i32 i = 0 ; i < m_nodea.get_size(); i++ )
               ostring += m_nodea[i]->get_xml_node()->get_text();

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

      attr_array attra(this);

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
         return m_nodea[i]->get_xml_node();
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
   ::count node::get_children_count(const ::scoped_string & scopedstrName)
   {

      if(scopedstrName.is_empty())
      {

         return get_children_count();

      }

      ::count count = 0;

      for(i32 i = 0; i < m_nodea.get_count(); i++)
      {

         if (m_nodea[i]->m_strName == scopedstrName)
         {

            count++;

         }

      }

      return count;

   }


   ::count node::get_children_count()
   {
      
      return m_nodea.get_count();

   }


   ::count node::get_children_count(const ::scoped_string & scopedstrName, index iDepth)
   {

      if (iDepth == 0)
      {

         return 0;

      }

      ::count count = 0;

      for(index i = 0; i < m_nodea.get_count(); i++)
      {

         if(scopedstrName.is_empty())
         {

            count++;

         }
         else
         {

            if (m_nodea[i]->m_strName == scopedstrName)
            {

               count++;

            }

         }

         if (iDepth < 0)
         {

            count += m_nodea[i]->get_xml_node()->get_children_count(scopedstrName, -1);

         }
         else
         {

            count += m_nodea[i]->get_xml_node()->get_children_count(scopedstrName, iDepth - 1);

         }

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


   node * node::get_node_from_attr_path(const ::file::path & path, const scoped_string & strName, const scoped_string & strAttr)
   {

      string_array stra;

      stra.explode("/", path);

      ::xml::node  * pnode = this;

      if (stra.get_size() <= 0 || (stra.get_size() == 1 && stra[0].length() == 0))
      {

         return this;

      }

      for(i32 i = 0; i < stra.get_size(); i++)
      {

         pnode = pnode->get_child_with_attribute(strName, strAttr, stra[i]);

         if (pnode == nullptr)
         {

            return nullptr;

         }

      }

      return pnode;

   }


   string node::get_child_simple_attr_path(node * pnode, const ::scoped_string & scopedstrAttr)
   {

      string str;

      while(pnode != nullptr && pnode != this)
      {
         str = pnode->attribute(scopedstrAttr) + ::str::has_char(str, "/");
         pnode = pnode->m_pnodeParent->get_xml_node();
      }
      if(pnode == nullptr)
         return "";
      else if(pnode != this)
         return "";
      return str;

   }


   node * node::get_node_from_simple_path(const ::file::path & path)
   {
      string_array stra;
      stra.explode("/", path);
      ::xml::node  * pnode = this;
      if(stra.get_size() <= 0 || (stra.get_size() == 1 && stra[0].length() == 0))
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
         pnode = pnode->m_pnodeParent->get_xml_node();
      }
      if(pnode == nullptr)
         return "";
      else if(pnode != this)
         return "";
      return str;
   }

   void node::get_child_indexed_path(index_array & iaPath, const node * pnode) const
   {

      iaPath.erase_all();
      while(pnode != nullptr && pnode != this)
      {
         iaPath.insert_at(0, pnode->get_index());
         pnode = pnode->m_pnodeParent->get_xml_node();
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
         if(m_nodea[i]->m_strName.order(lpszName) == 0)
            return m_nodea[i]->get_xml_node();
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

   
   string node::get_child_text( const char * lpszName, disp_option * opt /*= &optDefault*/ )
   {
      
      node * node = get_child( lpszName );

      return node != nullptr ? node->get_text(opt).c_str() : "";

   }

   
   property * node::GetChildAttr( const char * lpszName, const char * attrname )
   {

      node * node = get_child(lpszName);

      return node ? node->find_attribute(attrname) : nullptr;

   }


   string node::GetChildAttrValue( const char * lpszName, const char * attrname )
   {
      
      property * attr = GetChildAttr( lpszName, attrname );

      return attr ? attr->as_string() : string("");

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
   node * node::rear_find( const char * lpszName, i32 iDepth)
   {
      index i = 0;
      for( ; i < m_nodea.get_size(); i++)
      {
         if(m_nodea[i]->m_strName == lpszName )
            return m_nodea[i]->get_xml_node();
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
         node * pnodeChild = m_nodea[i]->get_xml_node();

         pnodeChild = pnodeChild->rear_find(lpszName, iDepth);

         if(pnodeChild != nullptr)

            return pnodeChild;

      }
      return nullptr;
   }


   node * node::rear_find(const ::scoped_string & scopedstrName, const property_set & set, index iDepth)
   {

      for (auto & pnode : m_nodea)
      {

         if (pnode->m_strName == scopedstrName && pnode->get_xml_node()->contains(set))
         {

            return pnode->get_xml_node();

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

      for (auto & pnode : m_nodea)
      {

         auto pnodeChild = pnode->get_xml_node()->rear_find(scopedstrName, set, iDepth);

         if (pnodeChild != nullptr)
         {

            return pnodeChild->get_xml_node();

         }

      }

      return nullptr;

   }


   ::index node::find_child_with_name_and_value(const ::scoped_string & scopedstrName, const ::scoped_string & scopedstrValue)
   {
      
      for (::index iNode = 0; iNode < m_nodea.count(); iNode++)
      {
         
         auto pnode = m_nodea[iNode];
         
         if(pnode->m_strName == scopedstrName && pnode->m_strValue == scopedstrValue)
         {
            
            return iNode;
            
         }
         
      }

      return -1;
      
   }


   node * node::child_with_name_and_value(const ::scoped_string & scopedstrName, const ::scoped_string & scopedstrValue)
   {

      auto iIndex = find_child_with_name_and_value(scopedstrName, scopedstrValue);
      
      if(!m_nodea.is_index_ok(iIndex))
      {
         
         return nullptr;
         
      }
      
      auto pnode = m_nodea[iIndex]->get_xml_node();
      
      return pnode;
      
   }


   string node::plist_get(const ::scoped_string & scopedstrKey)
   {
      
      auto iKey = find_child_with_name_and_value("key", scopedstrKey);
      
      if(iKey < 0)
      {
       
         throw ::exception(error_not_found);
         
      }
      
      auto pnode = get_child_at(iKey + 1);
      
      if(!pnode)
      {
       
         throw ::exception(error_parsing);
         
      }
      
      auto str = pnode->value();

      return str;
      
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
   node * node::add_child( const ::string & strName /*= nullptr*/, const ::scoped_string & scopedstrValue /*= nullptr*/ )
   {
      
      auto pnode = __new(node((node *) this));

      pnode->initialize(this);
      
      pnode->m_strName = strName;

      pnode->m_strValue = scopedstrValue;

      m_nodea.add(pnode);

      return pnode;

   }


   node * node::add_child(const ::string & strName, const property_set & set, const ::scoped_string & scopedstrValue)
   {

      auto pnode = __new(node((node *) this));

      pnode->m_strName = strName;

      pnode->m_set = set;

      pnode->m_strValue = scopedstrValue;

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
   // Name   : erase_child
   // Desc   : detach node and delete object
   // Param  :
   // Return :
   //--------------------------------------------------------
   // Coder    Date                      Desc
   // bro      2002-10-29
   //========================================================
   bool node::erase_child( node * pnode )
   {

      if(m_nodea.erase(pnode) > 0)
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
   // Name   : erase_attr
   // Desc   : detach attr and delete object
   // Param  :
   // Return :
   //--------------------------------------------------------
   // Coder    Date                      Desc
   // bro      2002-10-29
   //========================================================
   //bool node::erase_attr(::xml::attr * pproperty )
   //{

   //   if(m_attra.erase_by_name(pproperty->name()) > 0)
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
// /*   attr * node::add_attr( const char * lpszName /*= nullptr*/, /*const ::scoped_string & scopedstrValue /*= nullptr*/ /*)
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
         m_nodea.erase_at(find);
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
            m_attra.m_propertyptra.erase_at(find);
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
      m_enode        = node->m_enode;
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

            pnodeNewChild->get_xml_node()->CopyNode(pnodeChild->get_xml_node());

            add_child(pnodeNewChild);

            pnodeNewChild->get_xml_node()->_CopyBranch(pnodeChild->get_xml_node());

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

   node * node::get_child_at( index iIndex)
   {

      if (iIndex < 0)
         return nullptr;
      if (iIndex >= m_nodea.get_size())
         return nullptr;
      return m_nodea[iIndex]->get_xml_node();

   }


   node * node::get_child_at(const ::scoped_string & scopedstrName, index iIndex, index iDepth)
   {

      if (iDepth == 0)
      {

         return 0;

      }

      if (iIndex < 0)
      {
       
         return nullptr;

      }

      for(i32 i = 0; i < m_nodea.get_size(); i++)
      {
         if(m_nodea[i]->m_strName == scopedstrName)
         {
            if(iIndex <= 0)
               return m_nodea.element_at(i)->get_xml_node();
            iIndex--;
         }
         if(iDepth > 0)
            m_nodea[i]->get_xml_node()->get_child_at(scopedstrName, iIndex, iDepth - 1);
         else if(iDepth < 0)
            m_nodea[i]->get_xml_node()->get_child_at(scopedstrName, iIndex, -1);
      }
      return nullptr;

   }



   node* node::get_child_at_grow(const ::scoped_string & scopedstrName, index iIndex)
   {

      if (iIndex < 0)
      {

         return nullptr;

      }

      for (i32 i = 0; i < m_nodea.get_size(); i++)
      {

         if (m_nodea[i]->m_strName == scopedstrName)
         {

            if (iIndex <= 0)
            {

               return m_nodea.element_at(i)->get_xml_node();

            }

            iIndex--;

         }

      }

      node* pchild = nullptr;

      do
      {

         pchild = add_child(scopedstrName);

         iIndex--;

      } while (iIndex > 0);

      return pchild;

   }


   // iDepth
   // -1 recursive
   // 0 nothing
   // 1 children
   // 2 children and children of children
   ::count node::get_child_attr_value(string_array & stra, const ::scoped_string & scopedstrName, const ::scoped_string & scopedstrAttrName, index iDepth)
   {

      if(iDepth == 0)
         return 0;

      string strValue;
      ::count count = 0;
      for(i32 i = 0; i < m_nodea.get_size(); i++)
      {
         if (!m_nodea[i])
         {

            m_nodea.erase_at(i);
            i--;
            continue;
         }
         if(m_nodea[i]->m_strName == scopedstrName)
         {

            strValue = m_nodea[i]->get_xml_node()->attribute(scopedstrAttrName);
            
            if(strValue.has_char())
            {
               
               count++;
               
               stra.add(strValue);

            }

         }
         if(iDepth > 0)
            count += m_nodea[i]->get_xml_node()->get_child_attr_value(stra, scopedstrName, scopedstrAttrName, iDepth - 1);
         else if(iDepth < 0)
            count += m_nodea[i]->get_xml_node()->get_child_attr_value(stra, scopedstrName, scopedstrAttrName, -1);
      }
      return count;
   }

   // iDepth
   // -1 recursive
   // 0 nothing
   // 1 children
   // 2 children and children of children
   ::count node::erase_child_with_attr(const ::scoped_string & scopedstrName, const ::scoped_string & scopedstrAttrName, index iIndex, ::count iCount, index iDepth)
   {

      ::count nRemoveCount = 0;

      if(iDepth == 0)
         return 0;

      string strValue;
      ::count count = 0;
      for(index i = 0; i < m_nodea.get_size(); )
      {
         if(m_nodea[i]->m_strName == scopedstrName)
         {

            strValue = m_nodea[i]->get_xml_node()->attribute(scopedstrAttrName);

            if(strValue.has_char())
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
                     m_nodea.erase_at(i);
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
            nRemoveCount = m_nodea[i]->get_xml_node()->erase_child_with_attr(scopedstrName, scopedstrAttrName, iIndex, iCount, iDepth - 1);
         else if(iDepth < 0)
            nRemoveCount = m_nodea[i]->get_xml_node()->erase_child_with_attr(scopedstrName, scopedstrAttrName, iIndex, iCount, -1);
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


   node * node::GetChildByAttr(const ::scoped_string & scopedstrName, const ::scoped_string & scopedstrAttrName, const ::scoped_string & scopedstrAttrValue)
   {
      string strValue;
      for(i32 i = 0; i < m_nodea.get_size(); i++)
      {
         if(m_nodea[i]->get_xml_node()->m_strName == scopedstrName)
         {
            
            strValue = m_nodea[i]->get_xml_node()->attribute(scopedstrAttrName);

            if(strValue.has_char() && ansi_compare_ci(strValue, scopedstrAttrValue) == 0)
            {

               return m_nodea[i]->get_xml_node();

            }

         }
      }
      return nullptr;
   }

   node * node::GetChildByAnyAttr(const ::scoped_string & scopedstrName, string_array & straAttrName, string_array & straAttrValue)
   {
      
      string strValue;

      for(i32 i = 0; i < m_nodea.get_size(); i++)
      {

         if(m_nodea[i]->m_strName == scopedstrName)
         {

            for(i32 j = 0; j < straAttrName.get_size(); j++)
            {

               ::string strValue = m_nodea[i]->get_xml_node()->attribute(straAttrName[j]);

               if(strValue.has_char() && ansi_compare_ci(strValue.c_str(), straAttrValue[j]) == 0)
               {

                  return m_nodea[i]->get_xml_node();

               }

            }

         }

      }

      return nullptr;

   }


   node * node::GetChildByAllAttr(const ::scoped_string & scopedstrName, string_array & straAttrName, string_array & straAttrValue)
   {
      
      string strValue;
      
      for(i32 i = 0; i < m_nodea.get_size(); i++)
      {
         
         if(m_nodea[i]->m_strName == scopedstrName)
         {
            
            bool bAll = true;

            for(i32 j = 0; j < straAttrName.get_size(); j++)
            {

               ::string strValue = m_nodea[i]->get_xml_node()->attribute(straAttrName[j]);

               if(strValue.is_empty()  || ansi_compare_ci(strValue, straAttrValue[j]) != 0)
               {

                  bAll = false;

                  break;

               }

            }

            if(bAll)
            {

               return m_nodea[i]->get_xml_node();

            }

         }

      }

      return nullptr;

   }


   void node::close()
   {

      m_nodea.erase_all();

      m_iFirstXmlNode = -1;

      //m_ppropertyset.release();

   }


   bool node::from_row_column_v2(const string2a & str2a)
   {

      m_strName = "row_column_v2";

      if(str2a.get_size() <= 0)
      {

         m_strValue.empty();

         set_attribute("column_count", 0);

         m_nodea.erase_all();

      }
      else
      {
      
         ::count iColCount = str2a.get_count();

         set_attribute("column_count", iColCount);

         ::count iRowCount;

         for(index iCol = 0; iCol < iColCount; iCol++)
         {

            ::pointer<::xml::node>pcol = add_child("ca");

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

      ::count iColCount;

      iColCount = attribute("column_count").as_iptr();

      if(m_nodea.get_count() == 0 ||  iColCount <= 0)
      {

         str2a.erase_all();

         return true;

      }

      str2a.set_size(iColCount);

      ::count iRowCount = 0;

      ::pointer<::xml::node>pheader = m_nodea.element_at(0);

      for(::index iCol = 0; iCol < iColCount; iCol++)
      {

         auto pcol = pheader->m_nodea.element_at(iCol);

         str2a[iCol].set_size(pcol->attribute("row_count").as_i32());

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


   //stream & node::write(::stream & stream) const
   //{

   //   string str;

   //   str = get_xml();

   //   stream.write(str);

   //   return stream;

   //}


   //stream & node::read(::stream & stream)
   //{

   //   string str;

   //   stream.read(str);

   //   load(str);

   //   return stream;

   //}

   

   void node::set_name(const ::string & strName)
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

   void node::set_value(const ::string & strValue)
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


   /*::xml::document* node::get_xml_document() const
   {

      return nullptr;

   }*/


   index node::get_index() const
   {

      if(m_pnodeParent == nullptr)
         return -1;


      for(index iIndex = 0; iIndex < m_pnodeParent->m_nodea.get_count(); iIndex++)
      {

         if(m_pnodeParent->m_nodea.element_at(iIndex)->get_xml_node() == this)
            return iIndex;

      }

      return -1;

   }


} // namespace xml



