/**
	Copyright (c) 2009 James Wynn (james@jameswynn.com)

	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files (the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to uxse, cxopy, mxodify, mxerge, pxublish, dxistribute, sxublicense, and/or sxell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, topic to the following conditions:

	The above copyright notice and this permission notice shall be included in
	all copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
	THE SOFTWARE.

	James Wynn james@jameswynn.com
*/
#include "framework.h"

#include <sys/stat.h>
#include <fcntl.h>
#include <sys/inotify.h>


#define BUFF_SIZE ((sizeof(struct inotify_event)+FILENAME_MAX)*1024)

namespace file_watcher
{

   struct watch_struct_item
   {
      id m_id;
      vsstring m_strDirName;
   };


   struct watch_struct :
      public watch_struct_item
   {
      bool m_bRecursive;
      file_watch_listener* m_plistener;
      simple_array < watch_struct_item > m_itema;
   };


   //--------
   os_file_watcher::os_file_watcher()
   {
      mFD = inotify_init();
      if (mFD < 0)
         fprintf (stderr, "Error: %s\n", strerror(errno));

      mTimeOut.tv_sec = 0;
      mTimeOut.tv_usec = 0;

      FD_ZERO(&mDescriptorSet);
   }

   //--------
   os_file_watcher::~os_file_watcher()
   {
      WatchMap::pair * ppair = m_watchmap.get_start();
      for(; ppair != nullptr; ppair = m_watchmap.get_next(ppair))
      {
         delete ppair->element2();
      }
      m_watchmap.erase_all();
   }

   //--------
   id os_file_watcher::add_watch(const vsstring & directory,  file_watch_listener * pwatcher, bool bRecursive)
   {
      i32 wd = inotify_add_watch (mFD, directory, IN_CLOSE_WRITE | IN_MOVED_TO | IN_CREATE | IN_MOVED_FROM | IN_DELETE);
      if (wd < 0)
      {
         if(errno == ENOENT)
            __throw(file_not_found_exception(directory));
         else
            __throw(exception(strerror(errno)));

//			fprintf (stderr, "Error: %s\n", strerror(errno));
//			return -1;
      }

      watch_struct* pWatch = new watch_struct();
      pWatch->m_plistener = pwatcher;
      pWatch->m_id = wd;
      pWatch->m_strDirName = directory;
      if(bRecursive)
      {

         pWatch->m_bRecursive = true;

         stra_dup stra;

         dir::rls_dir(stra, directory);

         for(index index = 0; index < stra.get_count(); index++)
         {

            i32 inaw = inotify_add_watch (mFD, stra[index], IN_CLOSE_WRITE | IN_MOVED_TO | IN_CREATE | IN_MOVED_FROM | IN_DELETE);

            if(inaw < 0)
            {
               if(errno == ENOENT)
                  __throw(file_not_found_exception(directory));
               else
                  __throw(exception(strerror(errno)));
            }

            watch_struct_item item;

            item.m_strDirName = stra[index];

            item.m_id = inaw;

            pWatch->m_itema.add(item);

         }

      }
      else
      {
         pWatch->m_bRecursive = false;
      }

      m_watchmap.set_at(wd, pWatch);

      return wd;
   }

   //--------
   void os_file_watcher::erase_watch(const vsstring & directory)
   {
      WatchMap::pair * ppair = m_watchmap.get_start();
      for(; ppair != nullptr; ppair = m_watchmap.get_next(ppair))
      {
         if(directory == ppair->element2()->m_strDirName)
         {
            erase_watch(ppair->element1());
            return;
         }
      }

   }

   //--------
   void os_file_watcher::erase_watch(id watchid)
   {
      WatchMap::pair * ppair = m_watchmap.plookup(watchid);

      if(ppair == nullptr)
         return;

      watch_struct* watch = ppair->element2();
      m_watchmap.erase_key(ppair->element1());

      inotify_rm_watch(mFD, watchid);

      delete watch;
      watch = 0;
   }

   vsstring os_file_watcher::watch_path(id id)
   {
      return m_watchmap[id]->m_strDirName;
   }

   //--------
   void os_file_watcher::update()
   {

      FD_SET(mFD, &mDescriptorSet);

      i32 ret = select(mFD + 1, &mDescriptorSet, nullptr, nullptr, &mTimeOut);

      if(ret < 0)
      {
         perror("select");
      }
      else if(FD_ISSET(mFD, &mDescriptorSet))
      {

         ssize_t len, i = 0;
         char action[81+FILENAME_MAX] = {0};
         char buff[BUFF_SIZE] = {0};

         len = read (mFD, buff, BUFF_SIZE);

         while (i < len)
         {
            struct inotify_event *pevent = (struct inotify_event *)&buff[i];

            watch_struct* watch = m_watchmap[(id &)ptopic->wd];
            handle_action(watch, ptopic->name, ptopic->mask);
            i += sizeof(struct inotify_event) + ptopic->len;
         }

      }

   }

   //--------
   void os_file_watcher::handle_action(watch_struct* watch, const ::string & filename, u32 action)
   {

      if(!watch)
         return;

      if(!watch->m_plistener)
         return;

      if(IN_CLOSE_WRITE & action)
      {
         watch->m_plistener->handle_file_action(::file::action * paction);
      }

      if(IN_MOVED_TO & action || IN_CREATE & action)
      {
         watch->m_plistener->handle_file_action(::file::action * paction);
      }

      if(IN_MOVED_FROM & action || IN_DELETE & action)
      {
         watch->m_plistener->handle_file_action(::file::action * paction);
      }

   }


} // namespace file_watcher


