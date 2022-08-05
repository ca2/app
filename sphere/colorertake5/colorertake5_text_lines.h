#pragma once


namespace colorertake5
{


   /** Reads array of text lines and
   makes it accessible with line_source interface.
   All lines should be separated with \\r\\n , \\n or \\r characters.

   @ingroup colorer_impacter
   */
   class CLASS_DECL_SPHERE text_lines :
      public line_source
   {
      public:


         string_array lines;


         /** Empty constructor. Does nothing.
         */
         text_lines();
         ~text_lines();

         /** Loads specified file into vector of strings.
         @param fileName File to load.
         @param inputEncoding Input file encoding.
         @param tab2spaces Points, if we have to convert all tabs in file into spaces.
         */
         //  void loadFile(string fileName, string inputEncoding, bool tab2spaces);
         /** Returns loaded file name.
         */
         //string getFileName();
         /** Returns total lines ::count in text. */
         ::count getLineCount();
         string getLine(index lno);

         void replaceTabs(index lno);

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
