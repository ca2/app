#pragma once

#include "acme/parallelization/task.h"

// Native modal loops dispatch timer callbacks, but do not run ca2's outer
// task_iteration. Keep posted UI procedures moving on their owning thread.
namespace windows
{
   class modal_task_pump
   {
      inline static thread_local modal_task_pump *s_current = nullptr;
      modal_task_pump *m_previous = nullptr;
      UINT_PTR m_timer = 0;
      bool m_pumping = false;

      static void CALLBACK on_timer(HWND, UINT, UINT_PTR timer, DWORD)
      {
         auto pump = s_current;
         if (!pump || pump->m_timer != timer || pump->m_pumping)
            return;
         pump->m_pumping = true;
         try
         {
            auto task = ::get_task();
            if (task)
               task->handle_posted_procedures();
         }
         catch (...)
         {
            // No C++ exception may cross the native timer callback boundary.
         }
         pump->m_pumping = false;
      }

   public:
      modal_task_pump()
      {
         m_previous = s_current;
         m_timer = ::SetTimer(nullptr, 0, 16, &on_timer);
         if (m_timer)
            s_current = this;
      }
      ~modal_task_pump()
      {
         if (m_timer)
         {
            ::KillTimer(nullptr, m_timer);
            s_current = m_previous;
         }
      }
      bool is_active() const { return m_timer != 0; }
      modal_task_pump(const modal_task_pump &) = delete;
      modal_task_pump &operator=(const modal_task_pump &) = delete;
   };
}
