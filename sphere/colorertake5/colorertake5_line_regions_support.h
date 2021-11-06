#pragma once


namespace colorertake5
{


   /** region store implementation of RegionHandler.
   @ingroup colorer_handlers
   */
   class LineRegionsSupport : public RegionHandler
   {
   protected:


      address_array < LineRegion * > lineRegions;
      address_array < LineRegion * > schemeStack;

      RegionMapper *regionMapper;
      LineRegion *flowBackground;
      class region *special;

      LineRegion background;
      index firstLineNo;
      ::count lineCount;


   public:


      LineRegionsSupport();
      ~LineRegionsSupport();

      /**
      * Resizes structures to mantain regions for @ca lineCount lines.
      */
      void resize(::count lineCount);

      /**
      * Return current this->get_size of this line regions structure
      */
      ::count get_size();

      /**
      * Drops all internal structures
      */
      void clear();

      /**
      * Sets start line position of line structures.
      * This position tells, that first line structure refers
      * not to first line of text, but to @ca first parameter value.
      */
      void setFirstLine(index first);

      /**
      * Returns first line position, installed in this line structures.
      */
      index getFirstLine();

      /**
      * Background region define, which is used to
      * fill transparent regions. If background is @ca nullptr,
      * then regions with transparent fields would leave these fields unfilled
      */
      void setBackground(RegionDefine* back);

      /**
      * Tells handler to mark with special field
      * all Regions with specified ancestor.
      */
      void setSpecialRegion(class region *special);

      /**
      * Choose the source of RegionDefine definitions.
      * This source returns information about mapping
      * region objects into RegionDefine objects.
      */
      void setRegionMapper(RegionMapper* rds);

      /**
      * Returns LineRegion object for @ca lno line number.
      * This object is linked with all other stored @ca LineRegion objects
      */
      LineRegion *getLineRegions(index lno) const;

      /**
      * RegionHandler implementation
      */
      void startParsing(index lno);
      void clearLine(index lno, const ::string & line);
      void addRegion(index lno, const ::string & line, strsize sx, strsize ex, class region *region);
      void enterScheme(index lno, const ::string &line, strsize sx, strsize ex, class region *region, class scheme *scheme);
      void leaveScheme(index lno, const ::string &line, strsize sx, strsize ex, class region *region, class scheme *scheme);
   protected:
      /**
      * Behaviour is redefined in derived classes
      */
      virtual void addLineRegion(index lno, LineRegion *lr);
      index getLineIndex(index lno) const;
      bool checkLine(index index) const;

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
