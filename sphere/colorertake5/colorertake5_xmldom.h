#pragma once

/**
 * If true, traces line/column of an errors in the document
 */
#ifndef XMLDOM_FEATURE_POSITION_TRACE
  #define XMLDOM_FEATURE_POSITION_TRACE 0
#endif

/**
 * @addtogroup xml XMLDOM Parser
 * Simple DOM-based XML Parser.
 * Please refer to the w3c DOM API specification
 * for API review.
 */

namespace colorertak5
{

   class xml::node;
   class Document;
   class xml::node;
   class ProcessingInstruction;
   class CharacterData;
   class Comment;
   class Text;

   class BinaryXMLWriter;

   /**
    * Basic XML Parser exception class
    * Contains information about exception and position of the
    * error in the text.
    * @ingroup xml
    */
   class ParseException : public colorertake5::Exception
   {
   public:
     ParseException(const string &msg)
     {
       message += msg;
     }

     ParseException(const string &msg, int line, int pos)
     {
       message += "ParseException: " + msg;
       if (line > -1)
       {
          message += " at line: " + as_string(line);
       }
       if (pos > -1)
       {
          message += ", pos: " + as_string(pos);
       }
     };
   protected:
   };

   /**
    * Entity resolver, used to resolve addresses of the external entities
    * @ingroup xml
    */
   class EntityResolver
   {
   public:
      virtual colorertake5::input_source *resolveEntity(const string *publicId, const string *systemId) = 0;
   };

   /**
    * Default entity resolver class, uses input_source object rules
    * to resolve relative addresses of the entities.
    * @ingroup xml
    */
   class DefaultEntityResolver : public EntityResolver
   {
   public:
      DefaultEntityResolver(colorertake5::input_source *_is) : is(_is){};
      colorertake5::input_source *resolveEntity(const string *publicId, const string *systemId){
       return is->createRelative(systemId);
     }
   private:
     colorertake5::input_source *is;
   };

   /**
    * Document factory_item, used to build xml document tree from input stream.
    * Contains parser settings, can be used to generate multiple DOM trees.
    * Should not be used simultaneously from several threads.
    * @ingroup xml
    */
   class DocumentBuilder
   {
   public:
     DocumentBuilder() : ignoreComments(true), whitespace(true),
              er(nullptr), inputSource(nullptr) {}

     /**
      * Setups this builder to ignore and not to include in DOM tree
      * XML comments
      */
     void setIgnoringComments(bool _ignoreComments){
       ignoreComments = _ignoreComments;
     }
     /**
      * Returns current Ignoring Comments status.
      */
     inline bool isIgnoringComments(){
       return ignoreComments;
     }
     /**
      * Ignores is_empty matter's text content (content with only
      * spaces, tabs, CR/LF).
      */
     void setIgnoringElementContentWhitespace(bool _whitespace)
     {
       whitespace = _whitespace;
     }
     /**
      * Retrieves whitespace ignore state.
      */
     inline bool isIgnoringElementContentWhitespace()
     {
       return whitespace;
     }

     /**
      * Changes entity resolver, used while parsing external entity references.
      */
     void setEntityResolver(EntityResolver *_er){
       er = er;
     }

     /**
      * Allocates  document object.
      */
     Document *newDocument();

     /**
      * Parses input stream and creates DOM tree.
      */
     Document *parse(colorertake5::input_source *is, const ::string &codepage = 0);

     /**
      * Parses input bytes in specified encoding and creates DOM tree.
      */
     Document *parse(const unsigned char *bytes, int get_length, const ::string &codepage = 0);

     /**
      * Deletes all DOM tree structure.
      */
     void free(Document *doc);

   protected:
     bool ignoreComments;
     bool whitespace;
//     Hashtable<const string*> entitiesHash;
  //   Hashtable<const string*> extEntitiesHash;
   private:
     int ppos, opos;
     string src;
     int src_length;
     string *src_overflow;
     Document *doc;
     EntityResolver *er;
     input_source *inputSource;

     static bool getXMLNumber(const ::scoped_string & scopedstr, int *res);

     void consumeDocument();
     void consumeXmlDecl();
     void consumeDTD();
     bool isElement();
     void consumeElement(::pointer<::xml::node>oot);
     void consumeContent(::pointer<::xml::node>oot);

     void appendToLastTextNode(::pointer<::xml::node>oot, string *stext);
     bool isCDataSection();
     void consumeCDataSection(::pointer<::xml::node>oot);
     void consumeText(::pointer<::xml::node>oot);
     bool isCharRef();
     unichar consumeCharRef();
     bool isEntityRef();
     string *consumeEntityRef(bool useExtEnt);

     void consumeSpaces(int mins = 0);
     string *consumeQoutedValue();
     string *consumeAttributeValue();
     string *consumeNCName();
     string *consumeName();
     bool isComment();
     void consumeComment(::pointer<::xml::node>oot);
     bool isPI();
     void consumePI(::pointer<::xml::node>oot);
     void consumeMisc(::pointer<::xml::node>oot);
     void consume(string &s);
     void consume(char *s, int len = -1);
     void incDocumentLine();
     void setDocumentPos(int pos);
     void incDocumentPos();

     inline int peek(int offset = 0){
       if (src_overflow){
         if (opos+offset < src_overflow->get_length()){
           return (*src_overflow)[opos+offset];
         }else{
           offset -= (src_overflow->get_length() - opos);
         }
       }
       if (ppos+offset >= src_length) return -1;
       return src[ppos+offset];
     }

     inline unichar get(){
       if (src_overflow){
         if (opos == src_overflow->get_length()){
           delete src_overflow;
           src_overflow = nullptr;
           opos = 0;
         }else{
           return (*src_overflow)[opos++];
         }
       }
       if (ppos >= src_length){
         throw ::exception(ParseException(string("End of stream is reached")));
       }
   #if XMLDOM_FEATURE_POSITION_TRACE
       if (src[ppos] == '\n'){
         incDocumentLine();
         setDocumentPos(0);
       }
       incDocumentPos();
   #endif
       return src[ppos++];
     }

     ::pointer<::xml::node>ext;
   };

   /**
    * Abstract DOM tree node.
    * @ingroup xml
    */
   class xml::node
   {
   public:
     static const short COMMENT_NODE;
     static const short DOCUMENT_NODE;
     static const short ELEMENT_NODE;
     static const short PROCESSING_INSTRUCTION_NODE;
     static const short TEXT_NODE;

     bool hasChildNodes()
     {
       return firstChild != nullptr;
     }

     ::pointer<::xml::node>etFirstChild()
     {
       return firstChild;
     }

     ::pointer<::xml::node>etLastChild()
     {
       if (firstChild == nullptr){
         return nullptr;
       }else{
         return firstChild->prev;
       }
     }

     ::pointer<::xml::node>etParent()
     {
       return parent;
     }

     ::pointer<::xml::node>etNextSibling()
     {
       if (parent == nullptr) return nullptr;
       return next != parent->firstChild ? next : nullptr;
     }

     ::pointer<::xml::node>etPrevSibling()
     {
       if (parent == nullptr) return nullptr;
       return this != parent->firstChild ? prev : nullptr;
     }

     const string *getNodeName()
     {
       return name;
     }

     virtual const Vector<const string*> *getAttributes()
     {
       return nullptr;
     };

     short getNodeType()
     {
       return type;
     }

     Document *getOwnerDocument()
     {
       return ownerDocument;
     }

     virtual ::pointer<::xml::node>ppendChild(::pointer<::xml::node>wChild);

     //virtual ::pointer<::xml::node>loneNode(bool deep) = 0;

     virtual ~xml::node()
     {
       delete name;
     };
   protected:
     int type;
     ::pointer<::xml::node>ext, *prev;
     ::pointer<::xml::node>arent, *firstChild;
     const string *name;
     Document *ownerDocument;
     xml::node(int _type, const string *_name): type(_type), name(_name),
          next(nullptr), prev(nullptr), parent(nullptr), firstChild(nullptr) {};
   };


   /**
    * Document node.
    * @ingroup xml
    */
   class Document : public xml::node
   {
   public:
     ::pointer<::xml::node>etDocumentElement()
     {
       return documentElement;
     }

     ::pointer<::xml::node>ppendChild(::pointer<::xml::node>wChild){
       if (newChild->getNodeType() == xml::node::ELEMENT_NODE)
       {
         if (documentElement != nullptr)
         {
           throw ::exception(ParseException(string("Invalid document root content"), line, pos));
         }
         documentElement = (xml::node*)newChild;
       };
       xml::node::appendChild(newChild);
       return newChild;
     }

     ::pointer<::xml::node>reateElement(const string *tagName);
     Text *createTextNode(const string *data);
     Comment *createComment(const string *data);
     ProcessingInstruction *createProcessingInstruction(const string *target, const string *data);

   protected:
     int line, pos;
     ::pointer<::xml::node>ocumentElement;
     Document() : xml::node(xml::node::DOCUMENT_NODE, __allocate< string("#document")), documentElement >(nullptr) {};
     friend class DocumentBuilder;
   };


   /**
    * xml::node node.
    * @ingroup xml
    */
   class xml::node : public xml::node
   {
   public:

     const string getAttribute(const string &name)
     {
       return attributesHash.get(&name);
     }
     const string getAttribute(const string*name)
     {
       return attributesHash.get(name);
     }

     const Vector<const string*> *getAttributes()
     {
       return &attributes;
     };

     void setAttribute(const string *name, const string *value);

   protected:
     // TODO: static tagName index
     Vector<const string*> attributes;
     Hashtable<const string*> attributesHash;

     xml::node(const string *_tagName): xml::node(xml::node::ELEMENT_NODE, _tagName){};

     ~xml::node()
     {
       for(int idx = 0; idx < attributes.size(); idx++)
       {
         delete attributes.elementAt(idx);
       }
       for (const string* st = attributesHash.enumerate(); st != nullptr; st = attributesHash.next())
       {
         delete st;
       }
     }

     friend class Document;
   };

   /**
    * Processing Instruction node.
    * @ingroup xml
    */
   class ProcessingInstruction : public xml::node
   {
   public:
     const string *getData()
     {
       return data;
     }

     const string *getTarget()
     {
       return target;
     }

   protected:

     const string *data;
     const string *target;

     ProcessingInstruction(const string *_target, const string *_data):
           xml::node(xml::node::PROCESSING_INSTRUCTION_NODE, ___new string("#pi")),
           target(_target), data(_data) {}

     ~ProcessingInstruction()
     {
       delete data;
       delete target;
     };

     friend class Document;
   };

   /**
    * Abstract Text Data department node.
    * @ingroup xml
    */
   class CharacterData : public xml::node
   {
   public:
     const string *getData()
     {
       return data;
     }

     int getLength()
     {
       return data->get_length();
     }

   protected:

     const string *data;

     CharacterData(int type, const string *_data): xml::node(type, __allocate< string("#cdata")), data >(_data) {};
     ~CharacterData(){ delete data; };
     friend class Document;
   };

   /**
    * XML Comment node.
    * @ingroup xml
    */
   class Comment : public CharacterData
   {
   public:
   protected:
     Comment(const string *data): CharacterData(xml::node::COMMENT_NODE, data){};
     friend class Document;
   };

   /**
    * XML Text / CDATA node.
    * @ingroup xml
    */
   class Text : public CharacterData
   {
   public:
   protected:
     Text(const string *data): CharacterData(xml::node::TEXT_NODE, data){};
     friend class Document;
   };

} // namespace colorertake5

/* ***** BEGIN LICENSE BLOCK *****
 * Version: MPL 1.1/GPL 2.0/LGPL 2.1
 *
 * The contents of this file are topic to the Mozilla Public License Version
 * 1.1 (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 * http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 * for the specific language governing rights and limitations under the
 * License.
 *
 * The Original Code is the Colorer Library.
 *
 * The Initial Developer of the Original Code is
 * Cail Lomecb <cail@nm.ru>.
 * Portions created by the Initial Developer are Copyright (C) 1999-2005
 * the Initial Developer.
 *
 * Contributor(s):
 *
 * Alternatively, the contents of this file may be used under the terms of
 * either the GNU General Public License Version 2 or later (the "GPL"), or
 * the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
 * in which case the provisions of the GPL or the LGPL are applicable instead
 * of those above. If you wish to allow use of your version of this file only
 * under the terms of either the GPL or the LGPL, and not to allow others to
 * use your version of this file under the terms of the MPL, indicate your
 * decision by deleting the provisions above and replace them with the notice
 * and other provisions required by the GPL or the LGPL. If you do not delete
 * the provisions above, a recipient may use your version of this file under
 * the terms of any one of the MPL, the GPL or the LGPL.
 *
 * ***** END LICENSE BLOCK ***** */
