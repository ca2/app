#pragma once


#define MAX_RECURSION_LEVEL 100


namespace colorertake5
{


   /**
   * Implementation of text_parser interface.
   * This is the aura Colorer syntax parser, which
   * works with parsed internal HRC structure and colorisez
   * text in a target editor system.
   * @ingroup colorer_parsers
   */
   class text_parser_impl : 
      public text_parser
   {
   public:


      text_parser_impl();
      ~text_parser_impl();

      void setFileType(file_type *type);

      void setLineSource(line_source *lh);
      void setRegionHandler(RegionHandler *rh);

      index  parse(index from, ::count num, TextParseMode mode);
      void breakParse();
      void clearCache();

   private:

      string str;
      index stackLevel;
      index gx, gy, gy2, len;
      SMatchHash schemeStart;
      index clearLine, endLine;
      scheme_impl *baseScheme;

      bool breakParsing;
      bool first, invisibleSchemesFilled;
      bool drawing, updateCache;
      class region *picked;

      parse_cache *cache;
      parse_cache *parent, *forward;

      index cachedLineNo;
      parse_cache *cachedParent,*cachedForward;

      SMatches matchend;
      VTList *vtlist;

      line_source *lineSource;
      RegionHandler *regionHandler;

      void fillInvisibleSchemes(parse_cache *cache);
      void addRegion(index lno, strsize sx, strsize ex, class region* region);
      void enterScheme(index lno, strsize sx, strsize ex, class region* region);
      void leaveScheme(index lno, strsize sx, strsize ex, class region* region);
      void enterScheme(index lno, SMatches *match, SchemeNode *schemeNode);
      void leaveScheme(index lno, SMatches *match, SchemeNode *schemeNode);

      index searchKW(const SchemeNode *node, index no, index lowLen, index hiLen);
      index searchRE(scheme_impl *cscheme, index no, index lowLen, index hiLen);
      bool colorize(cregexp *root_end_re, bool lowContentPriority);


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
