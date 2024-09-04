#include "framework.h" // previously aura/user/user.h


namespace colorertake5
{


   /////////////////////////////////////////////////////////////////////////
   // parser's cache structures
   parse_cache::parse_cache()
   {
      children = next = parent = nullptr;
      vcache = 0;
   }

   parse_cache::~parse_cache()
   {
      CLR_FORMATTED_TRACE("TPCache", "~parse_cache():%s,%d-%d", scheme->getName().c_str(), sline, eline);
      delete children;
      delete next;
      delete[] vcache;
   }


   parse_cache *parse_cache::searchLine(index ln, parse_cache **cache)
   {

      parse_cache *r1, *r2, *tmp = this;
      *cache = nullptr;
      while(tmp)
      {

         CLR_FORMATTED_TRACE("TPCache", "  searchLine() tmp:%s,%d-%d", tmp->scheme->getName().c_str(), tmp->sline, tmp->eline);

         if (tmp->sline <=ln && tmp->eline >= ln)
         {
            r1 = tmp->children->searchLine(ln, &r2);
            if (r1)
            {
               *cache = r2;
               return r1;
            };
            *cache = r2; // last child
            return tmp;
         }

         if (tmp->sline <= ln)
            *cache = tmp;

         tmp = tmp->next;

      }

      return nullptr;

   }

   /////////////////////////////////////////////////////////////////////////
   // Virtual tables list
   VTList::VTList()
   {
      vlist = nullptr;
      prev = next = nullptr;
      last = this;
      shadowlast = nullptr;
      nodesnum = 0;
   }

   VTList::~VTList()
   {
      //  FAULT(next == this);
      // deletes only from root
      if (!prev && next)
         next->deltree();
   }

   void VTList::deltree()
   {

      if (next)
         next->deltree();

      delete this;

   }

   bool VTList::push(SchemeNode *node)
   {

      VTList *newitem;

      if(!node || node->virtualEntryVector.get_size() == 0)
         return false;

      newitem = new VTList();

      if(last->next)
      {
         last->next->prev = newitem;
         newitem->next = last->next;
      }

      newitem->prev = last;
      last->next = newitem;
      last = last->next;
      last->vlist = &node->virtualEntryVector;
      nodesnum++;

      return true;

   }

   bool VTList::pop()
   {

      VTList *ditem;
      //  FAULT(last == this);
      ditem = last;

      if (ditem->next)
         ditem->next->prev = ditem->prev;

      ditem->prev->next = ditem->next;

      last = ditem->prev;
      delete ditem;
      nodesnum--;

      return true;

   };

   scheme_impl *VTList::pushvirt(scheme_impl *scheme)
   {
      scheme_impl *ret = scheme;
      VTList *curvl = 0;

      for(VTList *vl = last; vl && vl->prev; vl = vl->prev)
      {
         for(::collection::index idx = 0; idx < vl->vlist->get_size(); idx++)
         {
            VirtualEntry *ve = vl->vlist->element_at(idx);
            if (ret == ve->virtScheme && ve->substScheme)
            {
               ret = ve->substScheme;
               curvl = vl;
            }
         }
      }

      if (curvl)
      {
         curvl->shadowlast = last;
         last = curvl->prev;
         return ret;
      }

      return 0;

   }
   void VTList::popvirt()
   {

      VTList *that = last->next;
      //  FAULT(!last->next || !that->shadowlast);
      last = that->shadowlast;
      that->shadowlast = 0;

   }

   void VTList::clear()
   {
      nodesnum = 0;

      if(!prev && next)
      {
         next->deltree();
         next = 0;
      }

      last = this;

   }

   VirtualEntryVector **VTList::store()
   {

      VirtualEntryVector **store;

      ::collection::index i = 0;

      if (!nodesnum || last == this)
         return 0;

      store = __new_array< VirtualEntryVector* >(nodesnum + 1);

      for(VTList *list = this->next; list; list = list->next)
      {

         store[i++] = list->vlist;

         if (list == this->last)
            break;
      }

      store[i] = 0;

      return store;

   }

   bool VTList::restore(VirtualEntryVector **store)
   {

      VTList *prevpos, *pos = this;

      if (next || prev || !store)
         return false;
      //  nodesnum = store[0].shadowlast;
      prevpos = last = 0;

      for(::collection::index i = 0; store[i] != nullptr; i++)
      {

         pos->next = new VTList();
         prevpos = pos;
         pos = pos->next;
         pos->prev = prevpos;
         pos->vlist = store[i];
         nodesnum++;

      }

      last = pos;

      return true;

   }


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
