#pragma once

#ifndef NOMINMAX
#define NOMINMAX
#endif

#include <Windows.h>

#include <chrono>
#include <limits>
#include <system_error>
#include <utility>

namespace threading
{
   

class win32_unique_lock
{
public:

   explicit win32_unique_lock(win32_mutex &mutex) noexcept : m_pmutex(&mutex) { lock(); }

   win32_unique_lock(win32_mutex &mutex, std::defer_lock_t) noexcept : m_pmutex(&mutex) {}

   win32_unique_lock(win32_mutex &mutex, std::adopt_lock_t) noexcept : m_pmutex(&mutex), m_bOwnsLock(true) {}

   win32_unique_lock(const win32_unique_lock &) = delete;
   win32_unique_lock &operator=(const win32_unique_lock &) = delete;

   win32_unique_lock(win32_unique_lock &&other) noexcept : m_pmutex(other.m_pmutex), m_bOwnsLock(other.m_bOwnsLock)
   {
      other.m_pmutex = nullptr;
      other.m_bOwnsLock = false;
   }

   win32_unique_lock &operator=(win32_unique_lock &&other) noexcept
   {
      if (this != &other)
      {
         if (m_bOwnsLock)
         {
            unlock();
         }

         m_pmutex = other.m_pmutex;
         m_bOwnsLock = other.m_bOwnsLock;

         other.m_pmutex = nullptr;
         other.m_bOwnsLock = false;
      }

      return *this;
   }

   ~win32_unique_lock()
   {
      if (m_bOwnsLock)
      {
         unlock();
      }
   }

   void lock()
   {
      if (m_pmutex == nullptr)
      {
         throw std::system_error(std::make_error_code(std::errc::operation_not_permitted));
      }

      if (m_bOwnsLock)
      {
         throw std::system_error(std::make_error_code(std::errc::resource_deadlock_would_occur));
      }

      m_pmutex->lock();
      m_bOwnsLock = true;
   }

   bool try_lock()
   {
      if (m_pmutex == nullptr)
      {
         throw std::system_error(std::make_error_code(std::errc::operation_not_permitted));
      }

      if (m_bOwnsLock)
      {
         throw std::system_error(std::make_error_code(std::errc::resource_deadlock_would_occur));
      }

      m_bOwnsLock = m_pmutex->try_lock();

      return m_bOwnsLock;
   }

   void unlock()
   {
      if (m_pmutex == nullptr || !m_bOwnsLock)
      {
         throw std::system_error(std::make_error_code(std::errc::operation_not_permitted));
      }

      m_pmutex->unlock();
      m_bOwnsLock = false;
   }

   [[nodiscard]]
   bool owns_lock() const noexcept
   {
      return m_bOwnsLock;
   }

   explicit operator bool() const noexcept { return owns_lock(); }

   [[nodiscard]]
   win32_mutex *mutex() const noexcept
   {
      return m_pmutex;
   }

private:

   friend class win32_condition_variable;

   win32_mutex *m_pmutex{};
   bool m_bOwnsLock{};
};
