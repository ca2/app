//
// Created by camilo on 2026-07-16 17:16 <3ThomasBorregaardSørensen!! Mummi!! Bilbo!!
//
#include "framework.h"
#include "termination_handler.h"

#include <signal.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <cstdint>

bool termination_handler::initialize()
{
   if (::pipe(m_pipe) != 0)
   {
      return false;
   }

   for (int fd : m_pipe)
   {
      int flags = ::fcntl(fd, F_GETFL, 0);

      if (flags < 0 ||
          ::fcntl(fd, F_SETFL, flags | O_NONBLOCK) != 0)
      {
         return false;
      }

      int fdFlags = ::fcntl(fd, F_GETFD, 0);

      if (fdFlags >= 0)
      {
         ::fcntl(fd, F_SETFD, fdFlags | FD_CLOEXEC);
      }
   }

   struct sigaction action{};
   action.sa_handler = &termination_handler::signal_handler;
   sigemptyset(&action.sa_mask);

   // Usually omit SA_RESTART if you want blocking calls to wake up.
   action.sa_flags = 0;

   return ::sigaction(SIGTERM, &action, nullptr) == 0 &&
          ::sigaction(SIGINT,  &action, nullptr) == 0;
}

int termination_handler::notification_fd()
{
   return m_pipe[0];
}

bool termination_handler::consume()
{
   std::uint8_t buffer[64];
   bool received = false;

   for (;;)
   {
      ssize_t count = ::read(m_pipe[0], buffer, sizeof(buffer));

      if (count > 0)
      {
         received = true;
         continue;
      }

      if (count < 0 && errno == EINTR)
      {
         continue;
      }

      break;
   }

   return received;
}

void termination_handler::signal_handler(int signalNumber)
{
   int savedErrno = errno;

   std::uint8_t byte = static_cast<std::uint8_t>(signalNumber);

   // write() is async-signal-safe. Ignore EAGAIN: a pending byte already
   // provides the shutdown notification.
   (void) ::write(m_pipe[1], &byte, sizeof(byte));

   errno = savedErrno;
}
