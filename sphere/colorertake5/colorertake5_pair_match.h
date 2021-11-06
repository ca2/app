#pragma once


namespace colorertake5
{


   /**
   * Representation of pair match in text.
   * Contains information about two regions on two lines.
   * @ingroup colorer_editor
   */
   class PairMatch
   {
   public:
      /**
      * region's start position as a cloned LineRegion object.
      */
      LineRegion *start;
      /**
      * region's end position as a cloned LineRegion object.
      */
      LineRegion *end;
      /**
      * Starting Line of pair
      */
      index sline;
      /**
      * Ending Line of pair
      */
      index eline;
      /**
      * Identifies initial position of cursor in pair
      */
      bool topPosition;
      /**
      * Internal pair search counter
      */
      i32 pairBalance;

      /**
      * Default constructor.
      * Clears all fields
      */
      PairMatch(LineRegion *startRef, index lineNo, bool topPosition)
      {
         start = end = nullptr;
         this->startRef = startRef;
         sline = lineNo;
         pairBalance = -1;
         this->topPosition = false;
         if (topPosition){
            pairBalance = 1;
            this->topPosition = true;
         };
         eline = -1;
      }

      virtual ~PairMatch(){
         delete start;
         delete end;
      }


      LineRegion *getStartRef(){
         return startRef;
      }

      /**
      * Sets a start region properties. Passed object is cloned to keep
      * pair match properties consistent between parse stages
      */
      void setStart(LineRegion *pair){
         if (start != nullptr){
            delete start;
         }
         if (pair != nullptr){
            start = new LineRegion(*pair);
         }
      }

      /**
      * Sets an end region properties. Passed object is cloned to keep
      * pair match properties consistent between parse stages
      */
      void setEnd(LineRegion *pair){
         if (end != nullptr){
            delete end;
         }
         if (pair != nullptr){
            end = new LineRegion(*pair);
         }
      }
   private:
      /**
      * region's start position as a object to inparse sequence.
      */
      LineRegion *startRef;

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
