#pragma once

namespace colorertake5
{

   /** Handles parse information, passed from text_parser.
   text_parser class generates calls of this class methods
   sequentially while parsing the text from top to bottom.
   All enterScheme and leaveScheme calls are properly enclosed,
   addRegion calls can inform about regions, overlapped with each other.
   All handler methods are called sequentially. It means, that
   if one of methods is called with some line number, all other calls
   (before endParsing event comes) can inform about events in the same,
   or lower line's numbers. This makes sequential tokens processing.
   @ingroup colorer
   */
   class CLASS_DECL_SPHERE RegionHandler
   {
      protected:


         RegionHandler();


      public:

         virtual ~RegionHandler();

         /** Start of text parsing.
         Called only once, when text_parser starts
         parsing of the specified block of text.
         All other event messages comes between this call and
         endParsing call.
         @param lno Start line number
         */
         virtual void startParsing(index lno);

         /** End of text parsing.
         Called only once, when text_parser stops
         parsing of the specified block of text.
         @param lno End line number
         */
         virtual void endParsing(index lno);

         /** clear line event.
         Called once for each parsed text line, when text_parser starts to parse
         specified line of text. This method is called before any of the region
         information passed, and used often to clear internal handler
         structure of this line before adding new one.
         @param lno Line number
         */
         virtual void clearLine(index lno, const ::string &line);

         /** Informs handler about lexical region in line.
         This is a basic method, wich transfer information from
         parser to application. Positions of different passed regions
         can be overlapped.
         @param lno Current line number
         @param sx Start X position of region in line
         @param ex End X position of region in line
         @param region region information
         */
         virtual void addRegion(index lno, const ::string &line, strsize sx, strsize ex, class region *region) = 0;

         /** Informs handler about entering into specified scheme.
         Parameter <code>region</code> is used to specify
         scheme background region information.
         If text is parsed not from the first line, this method is called
         with fake parameters to compensate required scheme structure.
         @param lno Current line number
         @param sx Start X position of region in line
         @param ex End X position of region in line
         @param region scheme region information (background)
         @param scheme Additional scheme information
         */
         virtual void enterScheme(index lno, const ::string &line, strsize sx, strsize ex, class region *region, class scheme *scheme) = 0;

         /** Informs handler about leaveing specified scheme.
         Parameter <code>region</code> is used to specify
         scheme background region information.
         If text parse process ends, but current schemes stack is not balanced
         (this can happends because of bad balanced structure of source text,
         or partial text parse) this method is <b>not</b> called for unbalanced
         levels.
         @param lno Current line number
         @param sx Start X position of region in line
         @param ex End X position of region in line
         @param region scheme region information (background)
         @param scheme Additional scheme information
         */
         virtual void leaveScheme(index lno, const char  *line, strsize sx, strsize ex, class region *region, class scheme *scheme) = 0;

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
