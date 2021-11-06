#pragma once


namespace colorertake5
{


   /** Defines region position properties.
   These properties are created dynamically during text parsing
   and stores region's position on line and mapping
   of region into the RegionDefine instance.
   @ingroup colorer_handlers
   */
   class LineRegion
   {
   public:
      /** Reference to HRC region, which identifies type of this range */
      class region *region;
      /** Reference to RegionDefine class (it's subclass).
      This object can contain concrete information about region
      extended properties.
      Can be nullptr, if no region mapping were defined.
      */
      RegionDefine *rdef;
      /** Start and End position of region in line */
      index start, end;
      /** Reference to region's HRC scheme */
      const class scheme *scheme;
      /** Previous and next links to ranged region in this line.
      First region of each line contains object to it's last
      region in prev field.
      If @ca next field is nullptr, this is a last region in line.
      */
      LineRegion *next, *prev;
      /** Special meaning marker. Generally this is used to inform
      application about paired regions, which are invisible during
      ordinary text drawing.
      */
      bool special;

      /** Transforms this region's object into styled region define
      and returns new pointer.
      */
      const StyledRegion *styled(){
         return StyledRegion::cast(rdef);
      };
      /** Transforms this region's object into text region define
      and returns new pointer.
      */
      const TextRegion *texted(){
         return TextRegion::cast(rdef);
      };
      /** copy operator */
      LineRegion& operator=(const LineRegion&lr){
         start = lr.start;
         end   = lr.end;
         scheme = lr.scheme;
         region = lr.region;
         special = lr.special;
         rdef = nullptr;
         if (lr.rdef != nullptr) rdef = lr.rdef->clone();
         return *this;
      };
      /** Clears all fields */
      LineRegion(){
         next = prev = nullptr;
         start = end = 0;
         scheme = nullptr;
         region = nullptr;
         rdef = nullptr;
         special = false;
      };
      /** copy constructor.
      Do not copies next and prev pointers.
      */
      LineRegion(const LineRegion &lr){
         //_next = lr._next;
         //_prev = lr._prev;
         operator=(lr);
      };
      ~LineRegion(){
         delete rdef;
      };
   private:

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
