///**
//   Copyright (c) 2009 James Wynn (james@jameswynn.com)
//
//   Permission is hereby granted, free of charge, to any person obtaining a copy
//   of this software and associated documentation files (the "Software"), to deal
//   in the Software without restriction, including without limitation the rights
//   to uxse, cxopy, mxodify, mxerge, pxublish, dxistribute, sxublicense, and/or sxell
//   copies of the Software, and to permit persons to whom the Software is
//   furnished to do so, subject to the following conditions:
//
//   The above copyright notice and this permission notice shall be included in
//   all copies or substantial portions of the Software.
//
//   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//   THE SOFTWARE.
//
//   James Wynn james@jameswynn.com
//*/
//#include "framework.h"
//
//#include <sys/stat.h>
//#include <fcntl.h>
//#include <sys/inotify.h>
//
//
//#define BUFF_SIZE ((sizeof(struct inotify_event)+FILENAME_MAX)*1024)
//
//namespace file
//{
//
//
//
//
//   os_watcher::os_watcher()
//   {
//
//      //mDescriptorSet = new fd_set;
//
//      mFD = inotify_init();
//
//      if (mFD < 0)
//      {
//
//         fprintf(stderr, "Error: %s\n", strerror(errno));
//
//      }
//
//      mTimeOut.tv_sec = 0;
//
//      mTimeOut.tv_usec = 300 * 1000;
//
//      FD_ZERO(&mDescriptorSet);
//
//
//   }
//
//
//   os_watcher::~os_watcher()
//   {
//
//      parallelization::post_quit_and_wait(seconds(15));
//
//      //for()
//
//      //for(; ppair != nullptr; ppair = m_watchmap.get_next(ppair))
//      //{
//
//      //   delete ppair->element2();
//
//      //}
//
//      m_watchmap.erase_all();
//
//      //delete (fd_mDescriptorSet;
//
//   }
//
//
//   watch_id os_watcher::add_watch(const ::file::path & directory,  listener * pwatcher, bool bRecursive)
//   {
//
//      synchronous_lock synchronouslock(mutex());
//
//      i32 wd = inotify_add_watch (mFD, directory, IN_CLOSE_WRITE | IN_MOVED_TO | IN_CREATE | IN_MOVED_FROM | IN_DELETE);
//
//      if (wd < 0)
//      {
//
//         return -1;
//
//         //if (errno == ENOENT)
//         //{
//
//         //   __throw(file_not_found_exception(directory));
//
//         //}
//         //else
//         //{
//
//         //   __throw(exception(strerror(errno)));
//
//         //}
//
//      }
//
//      __pointer(os_watch) pWatch = new os_watch();
//
//      pWatch->m_listenera.add(pwatcher);
//      pWatch->m_id = wd;
//      pWatch->m_pathFolder = directory;
//      //pWatch->m_bOwn = bOwn;
//      pWatch->m_pwatcher = this;
//
//      if(bRecursive)
//      {
//
//         pWatch->m_bRecursive = true;
//
//         ::file::patha stra;
//
//         dir::rls_dir(stra, directory);
//
//         for(index index = 0; index < stra.get_count(); index++)
//         {
//
//            i32 inaw = inotify_add_watch (mFD, stra[index], IN_CLOSE_WRITE | IN_MOVED_TO | IN_CREATE | IN_MOVED_FROM | IN_DELETE);
//
//            if(inaw < 0)
//            {
//               if(errno == ENOENT)
//                  ::file::throw_status(error_file_not_found, errno, stra[index]);
//               else
//                  __throw(exception(strerror(errno)));
//            }
//
//            watch_item item;
//
//            item.m_strDirName = stra[index];
//
//            item.m_id = inaw;
//
//            pWatch->m_itema.add(item);
//
//         }
//
//      }
//      else
//      {
//
//         pWatch->m_bRecursive = false;
//
//      }
//
//      return wd;
//
//   }
//
//
//   void os_file_watcher::erase_watch(const string & directory)
//   {
//
//      synchronous_lock synchronouslock(mutex());
//
//      WatchMap::pair * ppair = m_watchmap.get_start();
//
//      for(; ppair != nullptr; ppair = m_watchmap.get_next(ppair))
//      {
//
//         if(directory == ppair->element2()->m_strDirName)
//         {
//
//            erase_watch(ppair->element1());
//
//            return;
//
//         }
//
//      }
//
//   }
//
//
//   void os_file_watcher::erase_watch(id watchid)
//   {
//
//      synchronous_lock synchronouslock(mutex());
//
//      WatchMap::pair * ppair = m_watchmap.plookup(watchid);
//
//      if (ppair == nullptr)
//      {
//
//         return;
//
//      }
//
//      m_watchmap.erase_key(ppair->element1());
//
//      inotify_rm_watch(mFD, watchid);
//
//   }
//
//
//   string os_file_watcher::watch_path(id id)
//   {
//
//      synchronous_lock synchronouslock(mutex());
//
//      return m_watchmap[id]->m_strDirName;
//
//   }
//
//
//   void os_file_watcher::run()
//   {
//
//      while (task_get_run())
//      {
//
//         select();
//
//      }
//
//   }
//
//
//   bool os_file_watcher::select()
//   {
//
//      synchronous_lock synchronouslock(mutex());
//
//      FD_SET(mFD, (fd_set *) m_pDescriptorSet);
//
//      i32 ret = ::select(mFD + 1,(fd_set *)m_pDescriptorSet,nullptr,nullptr,&mTimeOut);
//
//      if(ret < 0)
//      {
//
//         perror("select");
//
//         return false;
//
//      }
//      else if (ret == 0)
//      {
//
//         return false;
//
//      }
//      else if(FD_ISSET(mFD, (fd_set *) m_pDescriptorSet))
//      {
//
//         ssize_t len, i = 0;
//
//         char action[81+FILENAME_MAX] = {0};
//
//         char buff[BUFF_SIZE] = {0};
//
//         len = read (mFD, buff, BUFF_SIZE);
//
//         file_watcher_impl::action a;
//
//         struct inotify_event *pevent = nullptr;
//
//         while (i < len)
//         {
//
//            pevent = (struct inotify_event *)&buff[i];
//
//            a.m_strFilename = psubject->name;
//
//            a.m_pwatch = m_watchmap[(id &)psubject->wd];
//
//            a.m_ulOsAction = psubject->mask;
//
//            handle_action(&a);
//
//            i += sizeof(struct inotify_event) + psubject->len;
//
//         }
//
//      }
//
//      return true;
//
//   }
//
//
//   void os_file_watcher::handle_action(action * psubject)
//   {
//
//      if (!psubject->m_pwatch)
//      {
//
//         return;
//
//      }
//
//      if (!psubject->m_pwatch->m_plistener)
//      {
//
//         return;
//
//      }
//
//      if (IN_CLOSE_WRITE & psubject->m_ulOsAction)
//      {
//
//         psubject->m_pwatch->m_plistener->handle_file_action(::file::action * paction);
//
//      }
//
//      if (IN_MOVED_TO & psubject->m_ulOsAction || IN_CREATE & psubject->m_ulOsAction)
//      {
//
//         psubject->m_pwatch->m_plistener->handle_file_action(::file::action * paction);
//
//      }
//
//      if (IN_MOVED_FROM & psubject->m_ulOsAction || IN_DELETE & psubject->m_ulOsAction)
//      {
//
//         psubject->m_pwatch->m_plistener->handle_file_action(::file::action * paction);
//
//      }
//
//
//   }
//
//
//} // namespace file_watcher
//
//
//
