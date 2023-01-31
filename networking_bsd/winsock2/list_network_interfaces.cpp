// Created by Camilo on 2023-01-31 01:36 <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "../networking.h"
#include "../address.h"
#include <winsock2.h>
#include <iphlpapi.h>
#include <stdio.h>
#include <stdlib.h>

// Link with Iphlpapi.lib
#pragma comment(lib, "IPHLPAPI.lib")

#define WORKING_BUFFER_SIZE 15000
#define MAX_TRIES 3

#define MALLOC(x) HeapAlloc(GetProcessHeap(), 0, (x))
#define FREE(x) HeapFree(GetProcessHeap(), 0, (x))

/* Note: could also use malloc() and free() */

namespace networking_bsd
{


   ::pointer_array < ::networking::address >networking::list_network_interfaces()
   {

      ::pointer_array < ::networking::address > addressa;

      /* Declare and initialize variables */

      DWORD dwSize = 0;
      DWORD dwRetVal = 0;

      unsigned int i = 0;

      // Set the flags to pass to GetAdaptersAddresses
      ULONG flags = GAA_FLAG_INCLUDE_PREFIX;

      // default to unspecified address family (both)
      ULONG family = AF_UNSPEC;

      LPVOID lpMsgBuf = NULL;

      PIP_ADAPTER_ADDRESSES pAddresses = NULL;
      ULONG outBufLen = 0;
      ULONG Iterations = 0;

      PIP_ADAPTER_ADDRESSES pCurrAddresses = NULL;
      PIP_ADAPTER_UNICAST_ADDRESS pUnicast = NULL;
      PIP_ADAPTER_ANYCAST_ADDRESS pAnycast = NULL;
      PIP_ADAPTER_MULTICAST_ADDRESS pMulticast = NULL;
      IP_ADAPTER_DNS_SERVER_ADDRESS * pDnServer = NULL;
      IP_ADAPTER_PREFIX * pPrefix = NULL;

      //if (argc != 2) {
      //   strLog.append_format(" Usage: getadapteraddresses family\n");
      //   strLog.append_format("        getadapteraddresses 4 (for IPv4)\n");
      //   strLog.append_format("        getadapteraddresses 6 (for IPv6)\n");
      //   strLog.append_format("        getadapteraddresses A (for both IPv4 and IPv6)\n");
      //   exit(1);
      //}

      //if (atoi(argv[1]) == 4)
      //   family = AF_INET;
      //else if (atoi(argv[1]) == 6)
      //   family = AF_INET6;

      ::string strLog;

      strLog.append_format("Calling GetAdaptersAddresses function with family = ");
      if (family == AF_INET)
         strLog.append_format("AF_INET\n");
      if (family == AF_INET6)
         strLog.append_format("AF_INET6\n");
      if (family == AF_UNSPEC)
         strLog.append_format("AF_UNSPEC\n\n");

      // Allocate a 15 KB buffer to start with.
      outBufLen = WORKING_BUFFER_SIZE;

      do {

         pAddresses = (IP_ADAPTER_ADDRESSES *)MALLOC(outBufLen);
         if (pAddresses == NULL) {
            strLog.append_format
            ("Memory allocation failed for IP_ADAPTER_ADDRESSES struct\n");
            throw ::exception(error_failed);
         }

         dwRetVal =
            GetAdaptersAddresses(family, flags, NULL, pAddresses, &outBufLen);

         if (dwRetVal == ERROR_BUFFER_OVERFLOW) {
            FREE(pAddresses);
            pAddresses = NULL;
         }
         else {
            break;
         }

         Iterations++;

      } while ((dwRetVal == ERROR_BUFFER_OVERFLOW) && (Iterations < MAX_TRIES));

      if (dwRetVal == NO_ERROR) {
         // If successful, output some information from the data we received
         pCurrAddresses = pAddresses;
         while (pCurrAddresses) {
            strLog.append_format("\tLength of the IP_ADAPTER_ADDRESS struct: %ld\n",
                   pCurrAddresses->Length);
            strLog.append_format("\tIfIndex (IPv4 interface): %u\n", pCurrAddresses->IfIndex);
            strLog.append_format("\tAdapter name: %s\n", pCurrAddresses->AdapterName);

            pUnicast = pCurrAddresses->FirstUnicastAddress;
            if (pUnicast != NULL) {
               for (i = 0; pUnicast != NULL; i++)
               {
                  auto paddress = __create_new<::networking_bsd::address>();

                  auto address = (sockaddr *)pUnicast->Address.lpSockaddr;

                  paddress->set_address(*address);

                  addressa.add(paddress);

                  pUnicast = pUnicast->Next;

               }
               strLog.append_format("\tNumber of Unicast Addresses: %d\n", i);
            }
            else
               strLog.append_format("\tNo Unicast Addresses\n");

            pAnycast = pCurrAddresses->FirstAnycastAddress;
            if (pAnycast) {
               for (i = 0; pAnycast != NULL; i++)
                  pAnycast = pAnycast->Next;
               strLog.append_format("\tNumber of Anycast Addresses: %d\n", i);
            }
            else
               strLog.append_format("\tNo Anycast Addresses\n");

            pMulticast = pCurrAddresses->FirstMulticastAddress;
            if (pMulticast) {
               for (i = 0; pMulticast != NULL; i++)
                  pMulticast = pMulticast->Next;
               strLog.append_format("\tNumber of Multicast Addresses: %d\n", i);
            }
            else
               strLog.append_format("\tNo Multicast Addresses\n");

            pDnServer = pCurrAddresses->FirstDnsServerAddress;
            if (pDnServer) {
               for (i = 0; pDnServer != NULL; i++)
                  pDnServer = pDnServer->Next;
               strLog.append_format("\tNumber of DNS Server Addresses: %d\n", i);
            }
            else
               strLog.append_format("\tNo DNS Server Addresses\n");

            strLog.append_format("\tDNS Suffix: %wS\n", pCurrAddresses->DnsSuffix);
            strLog.append_format("\tDescription: %wS\n", pCurrAddresses->Description);
            strLog.append_format("\tFriendly name: %wS\n", pCurrAddresses->FriendlyName);

            if (pCurrAddresses->PhysicalAddressLength != 0) {
               strLog.append_format("\tPhysical address: ");
               for (i = 0; i < (int)pCurrAddresses->PhysicalAddressLength;
                    i++) {
                  if (i == (pCurrAddresses->PhysicalAddressLength - 1))
                     strLog.append_format("%.2X\n",
                            (int)pCurrAddresses->PhysicalAddress[i]);
                  else
                     strLog.append_format("%.2X-",
                            (int)pCurrAddresses->PhysicalAddress[i]);
               }
            }
            strLog.append_format("\tFlags: %ld\n", pCurrAddresses->Flags);
            strLog.append_format("\tMtu: %lu\n", pCurrAddresses->Mtu);
            strLog.append_format("\tIfType: %ld\n", pCurrAddresses->IfType);
            strLog.append_format("\tOperStatus: %ld\n", pCurrAddresses->OperStatus);
            strLog.append_format("\tIpv6IfIndex (IPv6 interface): %u\n",
                   pCurrAddresses->Ipv6IfIndex);
            strLog.append_format("\tZoneIndices (hex): ");
            for (i = 0; i < 16; i++)
               strLog.append_format("%lx ", pCurrAddresses->ZoneIndices[i]);
            strLog.append_format("\n");

            strLog.append_format("\tTransmit link speed: %I64u\n", pCurrAddresses->TransmitLinkSpeed);
            strLog.append_format("\tReceive link speed: %I64u\n", pCurrAddresses->ReceiveLinkSpeed);

            pPrefix = pCurrAddresses->FirstPrefix;
            if (pPrefix) {
               for (i = 0; pPrefix != NULL; i++)
                  pPrefix = pPrefix->Next;
               strLog.append_format("\tNumber of IP Adapter Prefix entries: %d\n", i);
            }
            else
               strLog.append_format("\tNumber of IP Adapter Prefix entries: 0\n");

            strLog.append_format("\n");

            pCurrAddresses = pCurrAddresses->Next;
         }
      }
      else {
         strLog.append_format("Call to GetAdaptersAddresses failed with error: %d\n",
                dwRetVal);
         if (dwRetVal == ERROR_NO_DATA)
            strLog.append_format("\tNo addresses were found for the requested parameters\n");
         else {

            if (FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER |
               FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
               NULL, dwRetVal, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
               // Default language
               (LPTSTR)&lpMsgBuf, 0, NULL)) {
               strLog.append_format("\tError: %s", lpMsgBuf);
               LocalFree(lpMsgBuf);
               if (pAddresses)
                  FREE(pAddresses);
               //exit(1);
            }
         }
      }

      if (pAddresses) {
         FREE(pAddresses);
      }

      ::output_debug_string(strLog);

      return addressa;

   }


} // namespace networking_bsd



