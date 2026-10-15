#pragma once
#if defined(__REACTOS__)
#include <winsock2.h>
#include <ws2tcpip.h>
#include <string.h>
#include <errno.h>

inline int ca2_inet_pton(int family, const char *text, void *address)
{
   if (family != AF_INET && family != AF_INET6)
   {
      errno = EAFNOSUPPORT;
      return -1;
   }
   if (!text || !address || !*text || strlen(text) >= 64)
      return 0;
   if (family == AF_INET)
   {
      unsigned char bytes[4]{};
      const char *cursor = text;
      for (int i = 0; i < 4; ++i)
      {
         unsigned value = 0;
         int digits = 0;
         while (*cursor >= '0' && *cursor <= '9')
         {
            value = value * 10 + (*cursor++ - '0');
            if (++digits > 3 || value > 255)
               return 0;
         }
         if (!digits || (i < 3 ? *cursor++ != '.' : *cursor != 0))
            return 0;
         bytes[i] = static_cast<unsigned char>(value);
      }
      memcpy(address, bytes, sizeof(bytes));
      return 1;
   }
   for (const char *cursor = text; *cursor; ++cursor)
      if (!((*cursor >= '0' && *cursor <= '9') || (*cursor >= 'a' && *cursor <= 'f') ||
            (*cursor >= 'A' && *cursor <= 'F') || *cursor == ':' || *cursor == '.'))
         return 0;
   char input[64];
   strcpy(input, text);
   sockaddr_in6 socketAddress{};
   int length = sizeof(socketAddress);
   if (WSAStringToAddressA(input, AF_INET6, nullptr, reinterpret_cast<sockaddr *>(&socketAddress), &length))
      return 0;
   memcpy(address, &socketAddress.sin6_addr, sizeof(socketAddress.sin6_addr));
   return 1;
}

inline const char *ca2_inet_ntop(int family, const void *address, char *text, size_t size)
{
   if (family != AF_INET && family != AF_INET6)
   {
      errno = EAFNOSUPPORT;
      return nullptr;
   }
   sockaddr_storage storage{};
   storage.ss_family = static_cast<ADDRESS_FAMILY>(family);
   int length;
   if (family == AF_INET)
   {
      auto ipv4 = reinterpret_cast<sockaddr_in *>(&storage);
      memcpy(&ipv4->sin_addr, address, sizeof(ipv4->sin_addr));
      length = sizeof(*ipv4);
   }
   else
   {
      auto ipv6 = reinterpret_cast<sockaddr_in6 *>(&storage);
      memcpy(&ipv6->sin6_addr, address, sizeof(ipv6->sin6_addr));
      length = sizeof(*ipv6);
   }
   char buffer[64]{};
   DWORD capacity = sizeof(buffer);
   if (WSAAddressToStringA(reinterpret_cast<sockaddr *>(&storage), length, nullptr, buffer, &capacity))
      return nullptr;
   if (strlen(buffer) + 1 > size)
   {
      errno = ENOSPC;
      return nullptr;
   }
   strcpy(text, buffer);
   return text;
}
#else
#define ca2_inet_pton inet_pton
#define ca2_inet_ntop inet_ntop
#endif
