#include "framework.h" // previously aura/user/user.h



namespace colorertake5
{


   RegionDefine *RegionMapperImpl::getRegionDefine(class region *region)
   {
      if (region == nullptr) return nullptr;
      RegionDefine *rd = nullptr;
      if (region->getID() < regionDefinesVector.get_size())
         rd = regionDefinesVector.element_at(region->getID());
      if (rd != nullptr) return rd;

      if (regionDefinesVector.get_size() < region->getID()+1)
         regionDefinesVector.allocate(region->getID()*2);

      RegionDefine *rd_new = regionDefines[region->getName()];
      if (rd_new != nullptr)
      {
         regionDefinesVector.set_at(region->getID(), rd_new);
         return rd_new;
      };

      if (region->getParent())
      {
         rd = getRegionDefine(region->getParent());
         regionDefinesVector.set_at(region->getID(), rd);
      };
      return rd;
   };

   /** Returns region mapping by it's full qualified name.
   */
   RegionDefine *RegionMapperImpl::getRegionDefine(const char * name)
   {
      return regionDefines[name];
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
