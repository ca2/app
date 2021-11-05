#pragma once


#if !defined COLORERMODE || defined NAMED_MATCHES_IN_HASH
#error need (COLORERMODE & !NAMED_MATCHES_IN_HASH) in cregexp
#endif

#define MATCH_NOTHING 0
#define MATCH_RE 1
#define MATCH_SCHEME 2

#define LINE_NEXT 0
#define LINE_REPARSE 1


namespace colorertake5
{


   /** Dynamic parser's list of virtual entries.
   @ingroup colorer_parsers
   */
   class VTList
   {
      VirtualEntryVector *vlist;
      VTList *prev, *next, *last, *shadowlast;
      i32 nodesnum;
   public:
      VTList();
      ~VTList();
      void deltree();
      bool push(SchemeNode *node);
      bool pop();
      scheme_impl *pushvirt(scheme_impl *scheme);
      void popvirt();
      void clear();
      VirtualEntryVector **store();
      bool restore(VirtualEntryVector **store);
   };

   /**
   * Internal parser's cache storage. Each object instance
   * stores parse information about single level of scheme
   * objects. The object always takes more, than a single line,
   * because single-line scheme match doesn't need to be cached.
   *
   * @ingroup colorer_parsers
   */
   class parse_cache
   {
   public:
      /** Start and end lines of this scheme match */
      index sline, eline;
      /** scheme, matched for this cache entry */
      scheme_impl *scheme;
      /** Particular parent block object, caused this scheme to
      * be instantiated.
      */
      SchemeNode *clender;
      /**
      * scheme virtualization cache entry
      */
      VirtualEntryVector **vcache;
      /**
      * RE Match object for start RE of the enwrapped &lt;block> object
      */
      SMatches matchstart;
      /**
      * copy of the line with parent's start RE.
      */
      string backLine;

      /**
      * Tree structure references in parse cache
      */
      parse_cache *children, *next, *parent;
      parse_cache();
      ~parse_cache();
      /**
      * Searched a cache position for the specified line number.
      * @param ln     Line number to search for
      * @param cache  Cache entry, filled with last child cache entry.
      * @return       Cache entry, assigned to the specified line number
      */
      parse_cache *searchLine(index ln, parse_cache **cache);


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
