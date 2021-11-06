#pragma once

namespace colorertake5
{
   /**
   Static service methods of LineRegion output.
   @ingroup colorer_viewer
   */
   class ParsedLineWriter{
   public:


      /** Writes given line of text using list of passed line regions.
      Formats output with class of each token, enclosed in
      \<span class='regionName'>...\</span>
      @param markupWriter writer, used for markup output
      @param textWriter writer, used for text output
      @param line Line of text
      @param lineRegions Linked list of LineRegion structures.
      Only region references are used there.
      */
      static void tokenWrite(stream & markupWriter, stream & textWriter, string_to_string * docLinkHash, const char  *line, LineRegion *lineRegions);

      /** write specified line of text using list of LineRegion's.
      This method uses text fields of LineRegion class to enwrap each line
      region.
      It uses two Writers - @ca markupWriter and @ca textWriter.
      @ca markupWriter is used to write markup elements of LineRegion,
      and @ca textWriter is used to write line content.
      @param markupWriter writer, used for markup output
      @param textWriter writer, used for text output
      @param line Line of text
      @param lineRegions Linked list of LineRegion structures
      */
      static void markupWrite(stream & markupWriter, stream & textWriter, string_to_string *docLinkHash, const ::string &line, LineRegion *lineRegions);


      /** write specified line of text using list of LineRegion's.
      This method uses integer fields of LineRegion class
      to enwrap each line region with generated HTML markup.
      Each region is
      @param markupWriter writer, used for markup output
      @param textWriter writer, used for text output
      @param line Line of text
      @param lineRegions Linked list of LineRegion structures
      */
      static void htmlRGBWrite(stream & markupWriter, stream & textWriter, string_to_string *docLinkHash, const ::string &line, LineRegion *lineRegions);

      static void writeStyle(stream & writer, const StyledRegion *lr);

      /** Puts into stream starting HTML \<span> tag with requested style specification
      */
      static void writeStart(stream & writer, const StyledRegion *lr);

      /** Puts into stream ending HTML \</span> tag
      */
      static void writeEnd(stream & writer, const StyledRegion *lr);

      static void writeHref(stream & writer, string_to_string *docLinkHash, const class scheme *scheme, const string &token, bool start);

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
