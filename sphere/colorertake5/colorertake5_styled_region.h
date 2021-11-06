#pragma once

namespace colorertake5
{


/**
 * Contains information about region mapping into real colors.
 * These mappings are stored in HRD files and processed
 * by StyledHRDMapper class.
 * @ingroup colorer_handlers
 */
class StyledRegion : public RegionDefine{
public:
  static const i32 RD_BOLD;
  static const i32 RD_ITALIC;
  static const i32 RD_UNDERLINE;
  static const i32 RD_STRIKEOUT;

  /** Is foreground value assigned? */
  bool bfore;
  /** Is background value assigned? */
  bool bback;
  /** Foreground color of region */
  u32 fore;
  /** Background color of region */
  u32 back;
  /** Bit mask of region's style (bold, italic, underline) */
  u32 style;

  /** Common constructor */
  StyledRegion(bool _bfore, bool _bback, u32 _fore, u32 _back, u32 _style){
    bfore = _bfore;
    bback = _bback;
    fore = _fore;
    back = _back;
    style = _style;
  }

  /** Empty constructor */
  StyledRegion(){
    bfore = bback = false;
    fore = back = 0;
    style = 0;
  }

  /** copy constructor.
      Clones all values including region object. */
  StyledRegion(const StyledRegion &rd){
    operator=(rd);
  }

  ~StyledRegion(){}

  /** Static method, used to cast RegionDefine class into
      StyledRegion class.
      @__throw( exception If casing is not available.
  */
  static const StyledRegion *cast(const RegionDefine *rd){
    if (rd == nullptr) return nullptr;
    const StyledRegion *sr = (const StyledRegion *)(rd);
    if (sr == nullptr) __throw(exception(string("Bad type cast exception into StyledRegion")));
    return sr;
  }
  /** Completes region define with it's parent values.
      The values only replaced, are these, which are is_empty
      in this region define. Style is replaced using OR operation.
  */
  void assignParent(const RegionDefine *_parent){
    const StyledRegion *parent = StyledRegion::cast(_parent);
    if (parent == nullptr) return;
    if (!bfore){
      fore = parent->fore;
      bfore = parent->bfore;
    }
    if (!bback){
      back = parent->back;
      bback = parent->bback;
    }
    style = style | parent->style;
  }

  void setValues(const RegionDefine *_rd){
    const StyledRegion *rd = StyledRegion::cast(_rd);
    fore  = rd->fore;
    bfore = rd->bfore;
    back  = rd->back;
    bback = rd->bback;
    style = rd->style;
  }

  RegionDefine *clone() const {
    RegionDefine *rd = new StyledRegion(*this);
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
