#pragma once

namespace colorertake5
{


// Must be not less than MATCHES_NUM in cregexp.h
#define REGIONS_NUM MATCHES_NUM
#define NAMED_REGIONS_NUM NAMED_MATCHES_NUM

   class scheme_impl;
   class file_type_impl;


   /** Information about one parsed keyword.
       Contains keyword, symbol specifier, region context_object
       and internal optimization field.
       @ingroup colorer_parsers
   */
   struct KeywordInfo
   {
      string keyword;
      bool isSymbol;
      class region* region;
      i32  ssShorter;

////#define CNAME "KeywordInfo"
//#include "memory_operator.h"

   };

   /** List of keywords.
       @ingroup colorer_parsers
   */
   class KeywordList
   {
   public:
      i32 num;
      i32 matchCase;
      strsize minKeywordLength;
      ::str::ch_class *firstChar;
      KeywordInfo *kwList;
      KeywordList();
      ~KeywordList();
      void sortList();
      void substrIndex();

//  //#undef CNAME
////#define CNAME "KeywordList"
////#include "aura/ca_memory_operator.h"

   };

   /** One entry of 'inherit' matter virtualization content.
       @ingroup colorer_parsers
   */
   class VirtualEntry
   {
   public:
      scheme_impl *virtScheme, *substScheme;
      string virtSchemeName, substSchemeName;

      VirtualEntry(const char *scheme, const char *subst)
      {
         virtScheme = substScheme = nullptr;
         virtSchemeName = (scheme);
         substSchemeName = (subst);
      };
      ~VirtualEntry()
      {
      };

//  //#undef CNAME
////#define CNAME "VirtualEntry"
////#include "aura/ca_memory_operator.h"

   };

   enum SchemeNodeType { SNT_EMPTY, SNT_RE, SNT_SCHEME, SNT_KEYWORDS, SNT_INHERIT };
   extern const char * schemeNodeTypeNames[];

   typedef address_array < VirtualEntry * > VirtualEntryVector;

   /** scheme node.
       @ingroup colorer_parsers
   */
   class SchemeNode :
      virtual public ::object
   {
   public:
      SchemeNodeType type;

      string schemeName;
      scheme_impl *scheme;

      VirtualEntryVector virtualEntryVector;
      KeywordList *kwList;
      ::str::ch_class *worddiv;

      class region* region;
      class region* regions[REGIONS_NUM];
      class region* regionsn[NAMED_REGIONS_NUM];
      class region* regione[REGIONS_NUM];
      class region* regionen[NAMED_REGIONS_NUM];
      cregexp *start, *end;
      bool innerRegion, lowPriority, lowContentPriority;

////#undef CNAME
////#define CNAME "SchemeNode"
////#include "aura/ca_memory_operator.h"

      SchemeNode();
      ~SchemeNode();
   };


   /** scheme storage implementation.
       Manages the vector of SchemeNode's.
       @ingroup colorer_parsers
   */
   class scheme_impl : public scheme
   {
      friend class HRCParserImpl;
      friend class text_parser_impl;
   public:
      const string getName() const { return schemeName; };
      file_type *getFileType() const { return (file_type*)fileType; };

//#undef CNAME
//#define CNAME "scheme_impl"
//#include "aura/ca_memory_operator.h"

   protected:
      string schemeName;
      address_array < SchemeNode * > nodes;
      file_type_impl *fileType;
   public:
      scheme_impl(const char *sn)
      {
         schemeName = string(sn);
         fileType = nullptr;
      };
      ~scheme_impl()
      {
         for (i32 idx = 0; idx < nodes.get_size(); idx++)
            delete nodes.element_at(idx);
      };
   };


   /** Stores regular expressions of filename and firstline
       elements and helps to detect file type.
       @ingroup colorer_parsers
   */
   class FileTypeChooser
   {
   public:
      /** Creates choose entry.
          @param type If 0 - filename RE, if 1 - firstline RE
          @param prior Priority of this rule
          @param re Associated regular expression
      */
      FileTypeChooser(i32 type, double prior, cregexp *re)
      {
         this->type = type;
         this->prior = prior;
         this->re = re;
      };
      /** Default destructor */
      ~FileTypeChooser()
      {
         delete re;
      };
      /** Returns type of chooser */
      bool isFileName() const { return type == 0; };
      /** Returns type of chooser */
      bool isFileContent() const { return type == 1; };
      /** Returns chooser priority */
      double getPrior() const { return prior; };
      /** Returns associated regular expression */
      cregexp *getRE() const { return re; };
   private:
      i32 type;
      double prior;
      cregexp *re;
   };

} // namespace colorertake5

/* ***** BEGIN LICENSE BLOCK *****
 * Version: MPL 1.1/GPL 2.0/LGPL 2.1
 *
 * The contents of this file are subject to the Mozilla Public License Version
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
