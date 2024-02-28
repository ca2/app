// Created by Camilo on 2023-01-31 05:45 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "../networking.h"
#include "../address.h"
#include "acme/filesystem/filesystem/file_context.h"
#include "acme/primitive/primitive/memory.h"
#include "apex/platform/system.h"
#include <stdio.h>
#include <stdlib.h>
#if defined(__APPLE__)
#define BSD_UNIX 1
#elif defined(FREEBSD)
#define BSD_UNIX 1
#endif


#if !defined(BSD_UNIX)



#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>

#include <linux/netlink.h>
#include <linux/rtnetlink.h>


#define ENTRY(x) {x, #x}
#define STRING_M(x) #x
/* contruct arp cache request */
struct arp_req{
   struct nlmsghdr n;
   struct ndmsg ndm;
   char buf[1024];
};
static int parse_rtattr(struct rtattr *tb[], int max, struct rtattr *rta, int len) {
   /* loop over all rtattributes */
   while (RTA_OK(rta, len) && max--) {
      tb[rta->rta_type] = rta; /* store attribute ptr to the tb array */
      rta = RTA_NEXT(rta, len); /* special rtnetlink.h macro to get next netlink route attribute ptr */
   };
   return 0;
}

template < typename PREDICATE >
int kernel_arp(PREDICATE pred) {
   int status;
   unsigned char *p; //just a ptr

   /* open socket */
   int sd = socket(PF_NETLINK, SOCK_DGRAM, NETLINK_ROUTE);

   arp_req req;

   req.n.nlmsg_len = NLMSG_LENGTH(sizeof(struct ndmsg));
      req.n.nlmsg_flags = NLM_F_REQUEST | NLM_F_ROOT; /* to get all table instead of a single entry */
      req.n.nlmsg_type = RTM_GETNEIGH; /* to get arp cache */
      req.ndm.ndm_family = AF_INET; /* IP protocol family. AF_INET/AF_INET6 */
   ;

   /* send request */
   status = send(sd, &req, req.n.nlmsg_len, 0);

   /* this is buffer to store an answer */
   char buf[16384] = {0};

   /* get an answer */
   status = recv(sd, buf, sizeof(buf), 0);
   int buf_size = status; /* recv will return answer size */
   p = (unsigned char *) buf; /* set p to start of an answer */

   while (buf_size > 0) { /* loop while buffer size is more than 0 */
      struct nlmsghdr *answer = (struct nlmsghdr *) p; /* netlink header structure */

      int len = answer->nlmsg_len; /* netlink message length including header */
      struct ndmsg *msg = NLMSG_DATA(answer); /* macro to get a ptr right after header */
      /* Given the payload length, len, this macro returns the aligned
       * length to store in the nlmsg_len field of the nlmsghdr.
       * */
      int msg_len = NLMSG_LENGTH(sizeof(*msg));
      len -= msg_len; /* count message length left */
      p += msg_len; /* move ptr forward */

      /* rtnetlink route netlink attributes buffer */
      struct rtattr *tb[NDA_MAX + 1] = {0};

      /* this is very first rtnetlink attribute */
      struct rtattr *rta = (struct rtattr *) p;
      memset(tb, 0, sizeof(tb)); /* clear attribute buffer */
      parse_rtattr(tb, NDA_MAX, rta, len); /* fill tb attribute buffer */
      if (tb[NDA_DST]) { /* this is destination address */
         char ip[INET6_ADDRSTRLEN] = {0};
         inet_ntop(msg->ndm_family, RTA_DATA(tb[NDA_DST]), ip, INET6_ADDRSTRLEN);
         fprintf(stderr, "%s ", ip);
         pred(ip);
      }
      if (tb[NDA_LLADDR]) { /* this is hardware mac address */
         const unsigned char *addr = RTA_DATA(tb[NDA_LLADDR]);
         fprintf(stderr, "lladdr: %02X:%02X:%02X:%02X:%02X:%02X\n",
                 addr[0], addr[1], addr[2], addr[3], addr[4], addr[5]);
      } else {
         fprintf(stderr, "lladdr: \n");
      }

      p += len;
      buf_size -= answer->nlmsg_len;
   }

   return 0;
}

namespace networking_bsd
{


//   ::pointer < ::item_array > networking::list_computers()
//   {
//
//      ::pointer < ::item_array > pitema;
//
//      __defer_construct_new(pitema);
//
//      char line[500]; // Read with fgets().
//      char ip_address[500]; // Obviously more space than necessary, just illustrating here.
//      int hw_type;
//      int flags;
//      char mac_address[500];
//      char mask[500];
//      char device[500];
//
//      auto lines = file()->lines("/proc/net/arp");
//
//      lines.erase_at(0);
//
//      for(auto & line : lines)
//      {
//
//         sscanf(line.c_str(), "%s 0x%x 0x%x %s %s %s\n",
//                ip_address,
//                &hw_type,
//                &flags,
//                mac_address,
//                mask,
//                device);
//
//         auto paddress = system()->m_papexsystem->networking()->create_address(ip_address);
//
//         pitema->add(paddress);
//
//      }
//
//      for (::index iItem = 0; iItem < pitema->size(); iItem++)
//      {
//
//         auto pitem = pitema->element_at(iItem);
//
//         pitem->m_item.m_iItem = iItem;
//
//      }
//
//      return pitema;
//
//   }


   ::pointer < ::item_array > networking::list_computers()
   {

      ::pointer < ::item_array > pitema;

      __defer_construct_new(pitema);

//      char line[500]; // Read with fgets().
//      char ip_address[500]; // Obviously more space than necessary, just illustrating here.
//      int hw_type;
//      int flags;
//      char mac_address[500];
//      char mask[500];
//      char device[500];

      //auto lines = file()->lines("/proc/net/arp");

      kernel_arp([this, pitema](auto ip_address)
                 {
                    auto paddress = system()->m_papexsystem->networking()->create_address(ip_address);

                    pitema->add(paddress);



                 });

//      lines.erase_at(0);
//
//      for(auto & line : lines)
//      {

//         sscanf(line.c_str(), "%s 0x%x 0x%x %s %s %s\n",
//                ip_address,
//                &hw_type,
//                &flags,
//                mac_address,
//                mask,
//                device);

//      }

      for (::index iItem = 0; iItem < pitema->size(); iItem++)
      {

         auto pitem = pitema->element_at(iItem);

         pitem->m_item.m_iItem = iItem;

      }

      return pitema;

   }

} // namespace networking_bsd


#endif

