#pragma once


#include "acme/primitive/collection/bit_array.h"


/** Character classes store implementation.
      - ch_class allows to store enumerations of characters in compact
      form (two-stage bit-field tables).
      - This class supports logical operations over it's instances,
      char category -> enumeration conversion.
      @ingroup unicode
*/
class CLASS_DECL_ACME ch_class
{
private:
   bit_array **infoIndex;
public:
   ch_class();
   ch_class(const ch_class &);
   ~ch_class();

   static ch_class *createCharClass(const char * ccs, strsize pos, strsize *retPos);

   void add_char(const char *);
   void clear_char(const char *);
   void add_range(const char *, const char *);
   void clear_range(const char *, const char *);

   void add_category(ECharCategory);
   void add_category(string);
   void clear_category(ECharCategory);
   void clear_category(string);

   void add_class(const ch_class &);
   void clear_class(const ch_class &);
   void intersect_class(const ch_class &);
   void clear();
   void fill();

   bool in_class(const char *pszUtf8Char) const;


};

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
