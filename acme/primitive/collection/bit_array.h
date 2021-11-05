#pragma once



/** Bit Array field.
    Creates and manages bit array objects.
    @ingroup unicode
*/
class CLASS_DECL_ACME bit_array
{
public:
  /** Creates bit array with specified number of stored bitfields.
  */
  bit_array();
  ~bit_array();

  /** Sets bit at position @ca pos */
  void set_bit(i32 pos);
  /** Clears bit at position @ca pos */
  void clear_bit(i32 pos);
  /** Sets bit range */
  void add_range(i32 s, i32 e);
  /** Clears bit range */
  void clear_range(i32 s, i32 e);
  /** Sets bits to 1, whose corresponding values
      in passed bit array are also 1 (bitwize OR) */
  void add_bit_array(bit_array &);
  /** Sets bits to 0, whose corresponding values
      in passed bit array are also 1 */
  void clear_bit_array(bit_array &);
  /** Makes intersection of current and
      the passed bit array (bitwize AND) */
  void intersect_bit_array(bit_array &);
  /** Adds bit array from the passed byte stream. */
  void add_bit_array(char*, i32);
  /** Clears bit array from the passed byte stream. */
  void clear_bit_array(char*, i32);
  /** Returns bit value at position @ca pos. */
  bool get_bit(i32 pos) const;




  void ensure_size(i32 iSize, bool bSet = false);
  void set_size(i32 iBitCount, bool set = false);
  i32 get_size();

private:
  i32 * m_pdata;
  i32 m_iDataCount;
  i32 m_iBitCount;

};

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



