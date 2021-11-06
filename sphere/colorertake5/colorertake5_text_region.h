#pragma once

namespace colorertake5
{
/**
 * Contains information about region mapping into textual prefix/suffix.
 * These mappings are stored in HRD files.
 * @ingroup colorer_handlers
 */
class TextRegion : public RegionDefine{
public:

  /**
   * Text wrapping information.
   * Pointers are managed externally.
   */
  string stext, etext, sback, eback;

  /**
   * Initial constructor
   */
  TextRegion(const ::string &_stext, const ::string &_etext,
             const char *_sback, const ::string &_eback){
    stext = _stext;
    etext = _etext;
    sback = _sback;
    eback = _eback;
  }

  TextRegion(){
  }

  /**
   * copy constructor.
   * Clones all values including region object
   */
  TextRegion(const TextRegion &rd){
     RegionDefine::operator=(rd);
  }

  ~TextRegion(){}

  /**
   * Static method, used to cast RegionDefine class into TextRegion class.
   * @__throw( exception If casing is not available.
   */
  static const TextRegion *cast(const RegionDefine *rd){
    if (rd == nullptr) return nullptr;
    const TextRegion *tr = (const TextRegion *)(rd);
    if (tr == nullptr)  __throw(exception(string("Bad type cast exception into TextRegion")));
    return tr;
  }

  /**
   * Assigns region define with it's parent values.
   * All fields are to be replaced, if they are nullptr-ed.
  */
  void assignParent(const RegionDefine *_parent){
    const TextRegion *parent = TextRegion::cast(_parent);
    if (parent == nullptr) return;
    if (stext.is_empty() || etext.is_empty()){
      stext = parent->stext;
      etext = parent->etext;
    }
    if (sback.is_empty() || eback.is_empty()){
      sback = parent->sback;
      eback = parent->eback;
    }
  }

  /**
   * Direct assign of all passed @ca rd values.
   * Do not assign region object.
   */
  void setValues(const RegionDefine *_rd){
    if (_rd == nullptr) return;
    const TextRegion *rd = TextRegion::cast(_rd);
    stext = rd->stext;
    etext = rd->etext;
    sback = rd->sback;
    eback = rd->eback;
  }

  RegionDefine *clone() const{
    RegionDefine *rd = new TextRegion(*this);
    return rd;
  }

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
