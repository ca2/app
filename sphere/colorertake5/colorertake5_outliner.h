#pragma once


namespace colorertake5
{


   /**
    * Used to create, store and maintain list or tree of different special regions.
    * These can include functions, methods, fields, classes, errors and so on.
    * Works as a filter on input editor stream.
    *
    * @ingroup colorer_editor
    */
   class Outliner :
      public RegionHandler,
      public EditorListener
   {
   public:
      /**
       * Creates outliner object, that searches stream for
       * the specified type of region. Outliner is deattached
       * on its explicit destruction psubject->
       *
       * @param baseEditor Editor to attach this Outliner to.
       * @param searchRegion region type to search in parser's stream
       */
      Outliner(base_editor *baseEditor, class region *searchRegion);
      ~Outliner();

      /**
       * Returns context_object to item with specified ordinal
       * index in list of currently generated outline items.
       * Note, that the returned pointer is vaild only between
       * subsequent parser invocations.
       */
      OutlineItem *getItem(index idx);

      /**
       * Static service method to make easy tree reconstruction
       * from created list of outline items. This list contains
       * unpacked level indexed of item's enclosure in scheme.
       * @param treeStack external array of integer, storing
       *        temporary tree structure. Must not be changed
       *        externally.
       * @param newLevel Unpacked level of item to be added into
       *        the tree. This index is converted into packed one
       *        and returned.
       * @return Packed index of item, which could be used to
       *         reconstruct tree of outlined items.
       */
      static index manageTree(index_array & treeStack, index newLevel);

      /**
       * Total number of currently available outline items
       */
      ::count itemCount();

      void startParsing(index lno);
      void endParsing(index lno);
      void clearLine(index lno, const char *line);
      void addRegion(index lno, const char *line, strsize sx, strsize ex, class region *region);
      void enterScheme(index lno, const char *line, strsize sx, strsize ex, class region *region, class scheme *scheme);
      void leaveScheme(index lno, const char *line, strsize sx, strsize ex, class region *region, class scheme *scheme);
      void modifyEvent(index topLine);

   protected:
      bool isOutlined(class region*region);

      base_editor *baseEditor;
      class region *searchRegion;
      address_array < OutlineItem * > outline;
      bool lineIsEmpty;
      index curLevel;
      index modifiedLine;

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
