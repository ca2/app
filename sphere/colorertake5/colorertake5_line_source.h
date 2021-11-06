#pragma once


namespace colorertake5
{


   /**
    * Interface for editor line information requests.
    * Basic data source interface, used in text_parser processing.
    * @note Methods startJob and endJob are optional, and
    * could be implemented or not depending on system archtecture.
    * @ingroup colorer
    */
   class CLASS_DECL_SPHERE line_source
   {
      protected:


         line_source();
         virtual ~line_source();


      public:

         /**
          * Called by parser, when it starts text parsing.
          * @param lno Line number, which will be used as
          * initial position of all subsequend parsing.
          */
         virtual void startJob(index lno);

         /**
          * Called by parser, when it has finished text parsing.
          * Could be used to cleanup objects, allocated by last
          * #getLine() call.
          */
         virtual void endJob(index lno);

         /**
          * Returns line of text with specified number.
          * Returns string class pointer, which incapsulates information
          * about line with number <code>lno</code>.
          * @note Returned pointer must be valid until next getLine method call.
          *       If requested line can't be returned, fe there is no line with the passed
          *       index, method must return nullptr.
          * @param lno Requested line number
          * @return Unicode string, enwrapped into string class.
          */
         virtual string getLine(index lno) = 0;


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
