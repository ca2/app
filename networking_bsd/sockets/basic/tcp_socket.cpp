#include "framework.h"
#include "tcp_socket.h"
#include "networking_bsd/address.h"
#include "networking_bsd/networking.h"
#include "socket_handler.h"
#include "acme/operating_system/shared_posix/c_error_number.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/crypto/crypto.h"
#include "apex/platform/system.h"
#include "acme/filesystem/filesystem/file_context.h"
#include "networking_bsd/sockets/ssl/context.h"
#include "networking_bsd/sockets/ssl/client_context.h"
#include "networking_bsd/sockets/ssl/client_context_map.h"
#if OPENSSL_VERSION_NUMBER >= 0x30000000
#include <openssl/core_names.h>
#endif
//#define OPENSSL_VERSION_NUMBER 123

//::std::strong_ordering memory_order(const void * m1, const void * m2, memsize s);


#if defined(LINUX) || defined(__BSD__)
#undef USE_MISC
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#endif


#include <fcntl.h>
//#include <assert.h>

static int SSL_app_data2_idx = -1;
static int SSL_app_data3_idx = -1;


int networking_last_error();


void SSL_init_app_data2_3_idx(void)
{
   int i;

   if (SSL_app_data2_idx > -1)
   {
      return;
   }

   /* we _do_ need to call this twice */
   for (i = 0; i <= 1; i++)
   {
      SSL_app_data2_idx =
         SSL_get_ex_new_index(0,
            (void*)"Second papp Data for SSL",
            nullptr, nullptr, nullptr);
   }

   if (SSL_app_data3_idx > -1)
   {
      return;
   }

   SSL_app_data3_idx =
      SSL_get_ex_new_index(0,
         (void*)"Third papp Data for SSL",
         nullptr, nullptr, nullptr);

}
void* SSL_get_app_data2(SSL* ssl)
{
   return (void*)SSL_get_ex_data(ssl, SSL_app_data2_idx);
}

void SSL_set_app_data2(SSL* ssl, void* arg)
{
   SSL_set_ex_data(ssl, SSL_app_data2_idx, (char*)arg);
   return;
}





int current_session_key(::sockets_bsd::tcp_socket* c, ssl_ticket_key* key)
{
   int result = false;
   _synchronous_lock synchronouslock(c->synchronization());
   if (c->m_ticketkeya.has_elements())
   {
      *key = c->m_ticketkeya.first();
      result = true;
   }
   //apr_thread_rwlock_unlock(c->::pointer < ::mutex >);
   return result;
}


int find_session_key(::sockets_bsd::tcp_socket* c, unsigned char key_name[16], ssl_ticket_key* key, int* is_current_key)
{

   int result = false;
   _synchronous_lock synchronouslock(c->synchronization());
   for (auto& ticketkey : c->m_ticketkeya)
   {
      // Check if we have a match for tickets.
      if (memory_order(ticketkey.key_name, key_name, 16) == 0)
      {
         *key = ticketkey;
         result = true;
         *is_current_key = &c->m_ticketkeya.first() == &ticketkey;
         break;
      }
   }
   return result;
}

#if OPENSSL_VERSION_NUMBER >= 0x30000000

static int ssl_tlsext_ticket_key_evp_cb(SSL* ssl, unsigned char key_name[16],
   unsigned char iv[EVP_MAX_IV_LENGTH],
   EVP_CIPHER_CTX* ctx, EVP_MAC_CTX* hctx, int enc)
{

   ::sockets_bsd::tcp_socket* c = (::sockets_bsd::tcp_socket*)SSL_get_app_data2(ssl);

   _synchronous_lock synchronouslock(c->synchronization());
   //auto conn = static_cast<Connection*>(SSL_get_app_data(ssl));
   //auto handler = static_cast<ClientHandler*>(conn->data);
   //auto worker = handler->get_worker();
   //auto ticket_keys = worker->get_ticket_keys();

   if (c->m_ticketkeya.is_empty()) {
      // No ticket keys available.
      return -1;
   }

   //auto& keys = ticket_keys->keys;
   //assert(!keys.empty());

   if (enc) {
      if (RAND_bytes(iv, EVP_MAX_IV_LENGTH) == 0) {
         //if (LOG_ENABLED(INFO)) {
         //   CLOG(INFO, handler) << "session ticket key: RAND_bytes failed";
         //}
         return -1;
      }

      auto& key = c->m_ticketkeya[0];

      /*     if (LOG_ENABLED(INFO)) {
              CLOG(INFO, handler) << "encrypt session ticket key: "
                 << util::format_hex(key.data.name);
           }*/

      strncpy((char*)key_name, (char*)key.key_name, 16);

      //EVP_EncryptInit_ex(ctx, EVP_aes_128_cbc(), nullptr,
      EVP_EncryptInit_ex(ctx, key.cipher, nullptr,
         key.aes_key, iv);

      //EVP_EncryptInit_ex(ctx, get_config()->tls.ticket.cipher, nullptr,
        // key.data.enc_key.data(), iv);
#if OPENSSL_VERSION_NUMBER >= 0x30000000
      OSSL_PARAM params[] = {
          OSSL_PARAM_construct_octet_string(
              OSSL_MAC_PARAM_KEY, key.hmac_key, key.hmac_key_len),
          OSSL_PARAM_construct_utf8_string(
              OSSL_MAC_PARAM_DIGEST,
              const_cast<char*>(EVP_MD_get0_name(key.hmac)), 0),
          OSSL_PARAM_construct_end(),
      };
      if (!EVP_MAC_CTX_set_params(hctx, params))
      {
         //if (LOG_ENABLED(INFO)) {
            //CLOG(INFO, handler) << "EVP_MAC_CTX_set_params failed";
         //}
         return -1;
      }
#else  // !OPENSSL_3_0_0_API
      HMAC_Init_ex(hctx, key.hmac_key, key.hmac_keylen, key.hmac,
         nullptr);
#endif // !OPENSSL_3_0_0_API
      return 1;
   }

   ::collection::index i;
   for (i = 0; i < c->m_ticketkeya.get_size(); ++i) {
      auto& key = c->m_ticketkeya[i];
      if (strncmp((const_char_pointer )key.key_name, (const_char_pointer )key_name, 16))
      {
         break;
      }
   }

   if (i == c->m_ticketkeya.size()) {
      //if (LOG_ENABLED(INFO)) {
      //   CLOG(INFO, handler) << "session ticket key "
      //      << util::format_hex(key_name, 16) << " not found";
      //}
      return 0;
   }

   //if (LOG_ENABLED(INFO)) {
   //   CLOG(INFO, handler) << "decrypt session ticket key: "
   //      << util::format_hex(key_name, 16);
   //}

   auto& key = c->m_ticketkeya[i];
#if OPENSSL_VERSION_NUMBER >= 0x30000000
   OSSL_PARAM params[] = {
       OSSL_PARAM_construct_octet_string(
           OSSL_MAC_PARAM_KEY, key.hmac_key, key.hmac_key_len),
       OSSL_PARAM_construct_utf8_string(
           OSSL_MAC_PARAM_DIGEST, const_cast<char*>(EVP_MD_get0_name(key.hmac)),
           0),
       OSSL_PARAM_construct_end(),
   };
   if (!EVP_MAC_CTX_set_params(hctx, params)) {
      //if (LOG_ENABLED(INFO)) {
      //   CLOG(INFO, handler) << "EVP_MAC_CTX_set_params failed";
      //}
      return -1;
   }
#else  // !OPENSSL_3_0_0_API
   HMAC_Init_ex(hctx, key.data.hmac_key.data(), key.hmac_keylen, key.hmac,
      nullptr);
#endif // !OPENSSL_3_0_0_API
   EVP_DecryptInit_ex(ctx, key.cipher, nullptr, key.aes_key, iv);

#ifdef TLS1_3_VERSION
   // If ticket_key_cb is not set, OpenSSL always renew ticket for
   // TLSv1.3.
   if (SSL_version(ssl) == TLS1_3_VERSION) {
      return 2;
   }
#endif // TLS1_3_VERSION

   return i == 0 ? 1 : 2;
}

//   struct tls_keys_ref* ref;
//   union tls_sess_key* keys;
//   struct connection* conn;
//   int head;
//   int i;
//   int ret = -1; /* error by default */
//
//   conn = SSL_get_ex_data(s, ssl_app_data_index);
//   ref = __objt_listener(conn->target)->bind_conf->keys_ref;
//   HA_RWLOCK_RDLOCK(TLSKEYS_REF_LOCK, &ref->lock);
//
//   keys = ref->tlskeys;
//   head = ref->tls_ticket_enc_index;
//
//   if (enc) {
//      ::memory_copy(key_name, keys[head].name, 16);
//
//      if (!RAND_pseudo_bytes(iv, EVP_MAX_IV_LENGTH))
//         goto end;
//
//      if (ref->key_size_bits == 128) {
//
//         if (!EVP_EncryptInit_ex(ectx, EVP_aes_128_cbc(), NULL, keys[head].key_128.aes_key, iv))
//            goto end;
//
//         if (ssl_hmac_init(hctx, keys[head].key_128.hmac_key, 16, TLS_TICKET_HASH_FUNCT()) < 0)
//            goto end;
//         ret = 1;
//      }
//      else if (ref->key_size_bits == 256) {
//
//         if (!EVP_EncryptInit_ex(ectx, EVP_aes_256_cbc(), NULL, keys[head].key_256.aes_key, iv))
//            goto end;
//
//         if (ssl_hmac_init(hctx, keys[head].key_256.hmac_key, 32, TLS_TICKET_HASH_FUNCT()) < 0)
//            goto end;
//         ret = 1;
//      }
//   }
//   else {
//      for (i = 0; i < TLS_TICKETS_NO; i++) {
//         if (!memcmp(key_name, keys[(head + i) % TLS_TICKETS_NO].name, 16))
//            goto found;
//      }
//      ret = 0;
//      goto end;
//
//   found:
//      if (ref->key_size_bits == 128) {
//         if (ssl_hmac_init(hctx, keys[(head + i) % TLS_TICKETS_NO].key_128.hmac_key, 16, TLS_TICKET_HASH_FUNCT()) < 0)
//            goto end;
//         if (!EVP_DecryptInit_ex(ectx, EVP_aes_128_cbc(), NULL, keys[(head + i) % TLS_TICKETS_NO].key_128.aes_key, iv))
//            goto end;
//         /* 2 for key renewal, 1 if current key is still valid */
//         ret = i ? 2 : 1;
//      }
//      else if (ref->key_size_bits == 256) {
//         if (ssl_hmac_init(hctx, keys[(head + i) % TLS_TICKETS_NO].key_256.hmac_key, 32, TLS_TICKET_HASH_FUNCT()) < 0)
//            goto end;
//         if (!EVP_DecryptInit_ex(ectx, EVP_aes_256_cbc(), NULL, keys[(head + i) % TLS_TICKETS_NO].key_256.aes_key, iv))
//            goto end;
//         /* 2 for key renewal, 1 if current key is still valid */
//         ret = i ? 2 : 1;
//      }
//   }
//
//end:
//   HA_RWLOCK_RDUNLOCK(TLSKEYS_REF_LOCK, &ref->lock);
//
//
//   //ssl_ticket_key key;
//   //int is_current_key;
//   //if (enc)   /* create ___new session */
//   //{
//   //   if (current_session_key(c, &key))
//   //   {
//   //      if (RAND_bytes(iv, EVP_MAX_IV_LENGTH) <= 0)
//   //      {
//   //         return -1; /* insufficient random */
//   //      }
//   //      ::memory_copy(key_name, key.key_name, 16);
//   //      EVP_EncryptInit_ex(ctx, EVP_aes_128_cbc(), nullptr, key.aes_key, iv);
//   //      //auto mac = EVP_MAC_fetch(0, "sha256", 0);
//   //      //auto macctx = EVP_MAC_CTX_new(mac)
//   //      OSSL_PARAM params[] = {
//   //         OSSL_PARAM_construct_utf8_string("digest", (char*)EVP_MD_get0_name(EVP_sha256()), 0),
//   //         OSSL_PARAM_construct_end() };
//
//   //      EVP_MAC_init(hctx, (const unsigned char*)key.hmac_key, 16, params);
//   //      //HMAC_Init_ex(hctx, key.hmac_key, 16, EVP_sha256(), nullptr);
//   //      return 1;
//   //   }
//   //   // No ticket configured
//   //   return 0;
//   //}
//   //else   /* retrieve session */
//   //{
//   //   if (find_session_key(c, key_name, &key, &is_current_key))
//   //   {
//   //      //EVP_MAC_init(hctx, key.hmac_key, 16, EVP_sha256(), nullptr);
//   //      EVP_MAC_init(hctx, (const unsigned char*)key.hmac_key, 16, 0);
//   //      EVP_DecryptInit_ex(ctx, EVP_aes_128_cbc(), nullptr, key.aes_key, iv);
//   //      if (!is_current_key)
//   //      {
//   //         return 2;
//   //      }
//   //      return 1;
//   //   }
//   //   // No ticket
//   //   return 0;
//   //}
//}
#else
static int ssl_tlsext_ticket_key_cb(SSL* s, unsigned char key_name[16], unsigned char* iv, EVP_CIPHER_CTX* ctx, HMAC_CTX* hctx, int enc)
{
   ::sockets_bsd::tcp_socket* c = (::sockets_bsd::tcp_socket*)SSL_get_app_data2(s);
   ssl_ticket_key key;
   int is_current_key;
   if (enc)   /* create ___new session */
   {
      if (current_session_key(c, &key))
      {
         if (RAND_bytes(iv, EVP_MAX_IV_LENGTH) <= 0)
         {
            return -1; /* insufficient random */
         }
         ::memory_copy(key_name, key.key_name, 16);
         EVP_EncryptInit_ex(ctx, EVP_aes_128_cbc(), nullptr, key.aes_key, iv);
         HMAC_Init_ex(hctx, key.hmac_key, 16, EVP_sha256(), nullptr);
         return 1;
      }
      // No ticket configured
      return 0;
   }
   else   /* retrieve session */
   {
      if (find_session_key(c, key_name, &key, &is_current_key))
      {
         HMAC_Init_ex(hctx, key.hmac_key, 16, EVP_sha256(), nullptr);
         EVP_DecryptInit_ex(ctx, EVP_aes_128_cbc(), nullptr, key.aes_key, iv);
         if (!is_current_key)
         {
            return 2;
         }
         return 1;
      }
      // No ticket
      return 0;
   }
}


#endif

#ifndef ETIMEDOUT
#define ETIMEDOUT       138
#endif

#if defined(LINUX)
#include <signal.h>
#undef USE_MISC

#endif


namespace sockets_bsd
{


#ifdef MACOS
   bool tcp_socket::s_bReuseSession = false;
#else
   bool tcp_socket::s_bReuseSession = true;
#endif

#ifdef LINUX
   // ssl_sigpipe_handle ---------------------------------------------------------
   void ssl_sigpipe_handle(int x);
#endif

   //
   //#define DEB(x) x
   //#else
   //#define DEB(x)
   //#endif


   // statics
#ifdef HAVE_OPENSSL
   //SSLInitializer tcp_socket::m_ssl_init;
#endif


// thanks, q
#ifdef _MSC_VER
#pragma warning(disable:4355)
#endif
   tcp_socket::tcp_socket() :
      //::object(&h),
      //base_socket(h),
      //socket(h),
      //stream_socket(h)
      //,
      m_ibuf(TCP_BUFSIZE_READ)
      , m_b_input_buffer_disabled(false)
      , m_bytes_sent(0)
      , m_bytes_received(0)
      , m_transfer_limit(0)
      , m_output_length(0)
      , m_socks4_state(0)
      , m_resolver_id(0)
      , m_bReconnect(false)
      , m_bTryingReconnect(false)
   {
      m_bReuseSession = s_bReuseSession;
      SSL_init_app_data2_3_idx();
      m_bClientSessionSet = false;
      m_memRead.set_size(TCP_BUFSIZE_READ + 1);
      m_bCertCommonNameCheckEnabled = true;
      //m_pmutexSslCtx = nullptr;
   }
#ifdef _MSC_VER
#pragma warning(default:4355)
#endif


#ifdef _MSC_VER
#pragma warning(disable:4355)
#endif
   tcp_socket::tcp_socket(memsize isize, memsize osize) :
      //::object(&h),
  //    base_socket(h),
//      socket(h),
//      stream_socket(h),
m_ibuf(isize)
, m_b_input_buffer_disabled(false)
, m_bytes_sent(0)
, m_bytes_received(0)
, m_transfer_limit(0)
, m_output_length(0)
, m_socks4_state(0)
, m_resolver_id(0)
, m_bReconnect(false)
, m_bTryingReconnect(false)
   {
      m_bReuseSession = s_bReuseSession;
      SSL_init_app_data2_3_idx();
      m_bClientSessionSet = false;
      m_memRead.set_size(TCP_BUFSIZE_READ + 1);
      m_bCertCommonNameCheckEnabled = true;
      //m_pmutexSslCtx = nullptr;
      __UNREFERENCED_PARAMETER(osize);
   }
#ifdef _MSC_VER
#pragma warning(default:4355)
#endif


   tcp_socket::~tcp_socket()
   {

      if (m_socketid != INVALID_SOCKET) // this could happen
      {

         close();

      }


   }


   void tcp_socket::initialize(::particle* pparticle)
   {

      stream_socket::initialize(pparticle);

      defer_create_synchronization();

   }


   /*
   bool tcp_socket::open(in_addr ip,::networking::port_t port,bool skip_socks)
   {
      address ad(get_app(), ip, port);
      address local(this);
      return open(ad, local, skip_socks);
   }


   bool tcp_socket::open(in6_addr ip,::networking::port_t port,bool skip_socks)
   {
      address ad(get_app(), ip, port);
      return open(ad, skip_socks);
   }
   */


   bool tcp_socket::open(::networking::address* paddress, bool skip_socks)
   {

      ::pointer < ::networking_bsd::address > paddress2 = paddress;

      auto paddressBind2 = __allocate::networking_bsd::address();

      paddressBind2->set_family(paddress2->get_family());

      return open(paddress2, paddressBind2.m_p, skip_socks);

   }


   bool tcp_socket::open(::networking::address* paddress, ::networking::address* paddressBind, bool skip_socks)
   {

      string strIp = paddress->get_display_number();

      int iPort = paddress->get_service_number();

      information() << "open address = " << strIp << ":" << iPort;

      if (!paddress->is_valid())
      {

         fatal() << "open Invalid ::networking::address";

         SetCloseAndDelete();

         return false;

      }

      //      if(__Handler(socket_handler())->get_count() >= FD_SETSIZE)
      //      {
      //
      //
      //         fatal() <<log_this, "open",0,"no space left in fd_set";
      //
      //         SetCloseAndDelete();
      //         return false;
      //
      //      }

      set_connecting(false);

      //SetSocks4(false);

//      if(__Handler(socket_handler())->PoolEnabled())
//      {
//
//         ::pointer<base_socket_handler::pool_socket>ppoolsocket = __Handler(socket_handler())->FindConnection(SOCK_STREAM,"tcp",ad);
//
//         if(ppoolsocket)
//         {
//
//            CopyConnection(ppoolsocket);
//
//            SetIsClient();
//
//            SetCallOnConnect(); // base_socket_handler must call OnConnect
//
//            (*this)["from_pool"] = true;
//
//            INFO(log_this, "SetCallOnConnect",0,"Found pooled connection");
//
//            return true;
//
//         }
//
//      }

      ::pointer < ::networking_bsd::address > pnetworkingbsdaddress = paddress;

      ::pointer < ::networking_bsd::address > pnetworkingbsdaddressBind = paddressBind;

      // if not, create ___new connection
      SOCKET s = CreateSocket(pnetworkingbsdaddress->get_family(), SOCK_STREAM, "tcp");

      if (s == INVALID_SOCKET)
      {

         return false;

      }

      // socket must be nonblocking for async connect
      if (!SetNonblocking(true, s))
      {

         SetCloseAndDelete();

         ::closesocket(s);

         return false;

      }

      SetIsClient(); // client because we connect

      SetClientRemoteAddress(paddress);

      int n = 0;

      if (paddressBind->get_service_number() != 0)
      {

         bind(s, pnetworkingbsdaddressBind->sa(), pnetworkingbsdaddressBind->sa_len());

      }

      auto addrSocks4 = GetSocks4Host();

      if (!skip_socks && addrSocks4.has_character() && GetSocks4Port())
      {

         auto paddressSocks4 = system()->networking()->create_address(addrSocks4);

         ::pointer < ::networking_bsd::address > pnetworkingbsdaddressSocks4 = paddressSocks4;

         if (pnetworkingbsdaddressSocks4 && pnetworkingbsdaddressSocks4->is_ip4())
         {



            //auto paddressSocks4_2 = __Address(paddressSocks4);

            //{
            //   
            //   string sockshost;

            //   auto paddressdepartment = ::networking::address_department();

            //   paddressdepartment->convert(sockshost,GetSocks4Host());

            //   information() << "open: is_connecting to socks4 server @ " << sockshost << ":" << GetSocks4Port();

            //}

            SetSocks4();

            n = connect(s, pnetworkingbsdaddressSocks4->sa(), pnetworkingbsdaddressSocks4->sa_len());

            SetRemoteHostname(paddress);

         }

      }
      else
      {

         n = connect(s, pnetworkingbsdaddress->sa(), pnetworkingbsdaddress->sa_len());

         SetRemoteHostname(paddress);

      }

      if (n == -1)
      {
#ifdef _WIN32
         // check error code that means a connect is in progress
         int iError = ::WSAGetLastError();
         if (iError == WSAEWOULDBLOCK || iError == 0)
#else
         int iError = networking_last_error();
         if (iError == EINPROGRESS)
#endif
         {

            print_line("Connecting...");

            attach(s);

            set_connecting(true); // this flag will control fd_set's

         }
         else if (Socks4() && ::pointer < sockets_bsd::socket_handler >(socket_handler())->Socks4TryDirect()) // retry
         {
            ::closesocket(s);
            return open(paddress, true);
         }
         else if (Reconnect())
         {
            string strError = bsd_socket_error(iError);

            information() << "connect: failed, reconnect pending " << iError << bsd_socket_error(iError);

            attach(s);
            set_connecting(true); // this flag will control fd_set's
         }
         else
         {
            string strError = bsd_socket_error(iError);

            fatal() << "connect: failed " << iError << bsd_socket_error(iError);

            SetCloseAndDelete();
            ::closesocket(s);
            return false;
         }
      }
      else
      {
         attach(s);
         SetCallOnConnect(); // base_socket_handler must call OnConnect
      }

      set_connection_start_time();

      //m_timeLastRead.Now();
      //m_timeLastWrite.Now();
      //m_psocketParent->m_timeLastRead = m_timeLastRead;
      //m_psocketParent->m_timeLastWrite = m_timeLastWrite;
      // 'true' means connected or connecting(not yet connected)
      // 'false' means something failed
      return true; //!is_connecting();
   }


   bool tcp_socket::open(const ::scoped_string & scopedstrHost, ::networking::port_t port)
   {

      auto pnetworking = system()->networking();

      ::networking::enum_address_type eaddresstype = ::networking::e_address_type_none;

      ::networking::address_pointer paddress;

      while (eaddresstype != ::networking::e_address_type_ipv4)
      {

         SetCloseAndDelete(false);

         if (IsIpv6() && eaddresstype == ::networking::e_address_type_none)
         {

            print_line("::networking_bsd::tcp_socket::open IsIpv6() true");

            //if(!__Handler(socket_handler())->ResolverEnabled() || paddressdepartment->isipv6(host))
            //if (!pnetworking2->is_ip6(host))
            //{

            //   SetCloseAndDelete();

            //   return false;

            //}

            eaddresstype = ::networking::e_address_type_ipv6;

            paddress = pnetworking->create_ip6_address(scopedstrHost, port);

            //if(!paddressdepartment->convert(a,host))
            if (!paddress)
            {

               SetCloseAndDelete();

               return false;

            }

         }
         else
         {

            print_line("::networking_bsd::tcp_socket::open IsIpv6() false");

            ////if(!__Handler(socket_handler())->ResolverEnabled() || paddressdepartment->isipv4(host))
            //if (!pnetworking2->is_ip4(host))
            //{

            //   SetCloseAndDelete();

            //   return false;

            //}

            if (eaddresstype == ::networking::e_address_type_none)
            {

               eaddresstype = preferred_address_type();

            }
            else
            {

               eaddresstype = ::networking::e_address_type_ipv4;

            }

            paddress = pnetworking->create_address(scopedstrHost, eaddresstype, port);

            //paddress = pnetworking->create_address(host, port);

            //if(!paddressdepartment->convert(a,host))
            if (!paddress)
            {

               SetCloseAndDelete();

               return false;

            }

         }

         ::pointer < ::networking_bsd::address > pnetworkingbsdaddress = paddress;

         auto paddressLocal = __allocate::networking_bsd::address();

         paddressLocal->set_family(pnetworkingbsdaddress->get_family());

         if (open(paddress, paddressLocal))
         {

            return true;

         }

         //return true;

         //}

         ////m_resolver_id = Resolve6(host,port);

         //return true;

         //}

         //auto paddressdepartment = ::networking::address_department();



         ////if(!__Handler(socket_handler())->ResolverEnabled() || paddressdepartment->isipv4(host))
         /////if( paddressdepartment->isipv4(host))
         //{

         //   in_addr l;

         //   if (!paddress)
         //   {
         //
         //      warning() <<"paddressdepartment->convert failed";
         //
         //      SetCloseAndDelete();
         //
         //      return false;

         //   }
         //
         //   ::networking::address ad(l, port);
         //
         //   ::networking::address addrLocal;

         //   if (!open(ad, addrLocal))
         //   {

         //      return false;

         //   }

         //   return true;

         //}

         // resolve using async resolver thread

         //m_resolver_id = Resolve(host,port);


      }

      return false;


   }


   void tcp_socket::set_host(const ::scoped_string & scopedstrHost)
   {

      m_strHost = scopedstrHost;

   }


   ::string tcp_socket::get_host() const
   {

      return m_strHost;

   }


   void tcp_socket::set_tls_hostname(const ::scoped_string & scopedstrTlsHostname)
   {

      m_strTlsHostName = scopedstrTlsHostname;

   }


   void tcp_socket::set_connect_host(const ::scoped_string & scopedstrConnectHost)
   {

      m_strConnectHost = scopedstrConnectHost;

   }


   ::string tcp_socket::get_connect_host() const
   {

      return m_strConnectHost;

   }


   void tcp_socket::set_connect_port(const ::networking::port_t portConnect)
   {

      m_iConnectPort = portConnect;

   }


   ::networking::port_t tcp_socket::get_connect_port() const
   {

      return m_iConnectPort;

   }


   void tcp_socket::set_url(const ::scoped_string & scopedstrUrl)
   {

      m_strUrl = scopedstrUrl;

   }


   string tcp_socket::get_url() const
   {

      return m_strUrl;

   }

   //   void tcp_socket::OnResolved(int atom,::networking::address * a)
   //   {
   //
   //      auto paddressdepartment = ::networking::address_department();
   //
   //      informationf("OnResolved atom %d addr %s port %d\n",atom,paddressdepartment->canonical_name(a).c_str(),a.u.s.m_port);
   //
   //      if(atom == m_resolver_id)
   //      {
   //         if(a.is_valid() && a.u.s.m_port)
   //         {
   //            ::networking::address addrLocal;
   //            if(open(a,addrLocal))
   //            {
   //               if(!__Handler(socket_handler())->Valid(this))
   //               {
   //                  __Handler(socket_handler())->add(this);
   //               }
   //            }
   //         }
   //         else
   //         {
   //
   //            fatal() <<log_this, "OnResolved",0,"Resolver failed";
   //
   //            SetCloseAndDelete();
   //         }
   //      }
   //      else
   //      {
   //
   //         fatal() <<log_this, "OnResolved",atom,"Resolver returned wrong job atom";
   //
   //         SetCloseAndDelete();
   //      }
   //   }




   int tcp_socket::recv(void* buf, int nBufSize)
   {

      int n = nBufSize;

#ifdef HAVE_OPENSSL

      if (IsSSL())
      {

         try
         {

            if (!Ready())
            {

               information() << "tcp_socket::recv not ready";

               return 0;

            }

            if (m_psslcontext->m_ssl == nullptr)
            {

               error() << "tcp_socket::recv(ssl)" << (int)n << "SSL context is nullptr";

               information() << "tcp_socket::recv ssl SSL context is nullptr(0)";

               OnDisconnect();
               SetCloseAndDelete(true);
               SetFlushBeforeClose(false);
               SetLost();

            }
            else
            {

               n = SSL_read(m_psslcontext->m_ssl, buf, (int)nBufSize);

               if (n <= 0)
               {
                  n = SSL_get_error(m_psslcontext->m_ssl, (int)n);
                  switch (n)
                  {
                  case SSL_ERROR_NONE:
                  case SSL_ERROR_WANT_READ:
                  case SSL_ERROR_WANT_WRITE:
                     break;
                  case SSL_ERROR_ZERO_RETURN:
                     //if(SSL_m_psslcontext->m_pclientcontext->m_psslsession)
                     information() << "SSL_read() returns zero - closing socket";
                     OnDisconnect();
                     SetCloseAndDelete(true);
                     SetFlushBeforeClose(false);
                     SetLost();
                     break;
                  case SSL_ERROR_SYSCALL:
                     informationf("SSL read problem, errcode = %d (SSL_FORMATTED_ERROR_SYSCALL) errno = %d ", n, errno);
                     OnDisconnect();
                     SetCloseAndDelete(true);
                     SetFlushBeforeClose(false);
                     SetLost();
                     break;
                  default:
                     informationf("SSL read problem, errcode = %d", n);
                     OnDisconnect();
                     SetCloseAndDelete(true);
                     SetFlushBeforeClose(false);
                     SetLost();
                  }
                  information() << "tcp_socket::recv ssl error(1)";
               }
               //else if (!n)
               //{
               //   OnDisconnect();
               //   SetCloseAndDelete(true);
               //   SetFlushBeforeClose(false);
               //   SetLost();
               //   SetShutdownStatus(SHUT_WR);
               //   //informationf("tcp_socket::recv ssl disconnect(2)");

               //}
               else if (n > 0 && n <= nBufSize)
               {

                  set_connection_last_read_time();

                  return n;
               }
               else
               {



                  error() << "tcp_socket::recv(ssl) " << (int)n << " abnormal value from SSL_read";



                  information() << "tcp_socket::recv ssl abnormal value from SSL_read(3)";

               }

            }

         }
         catch (...)
         {

            OnDisconnect();
            SetCloseAndDelete(true);
            SetFlushBeforeClose(false);
            SetLost();

         }

      }
      else
#endif // HAVE_OPENSSL
      {

#if defined(MSG_NOSIGNAL) || defined(SOLARIS)
         
         auto nRecv = ::recv(GetSocketId(), (char*)buf, (int)nBufSize, MSG_NOSIGNAL);
         
         n = (int) nRecv;

#else

         n = (int) ::recv(GetSocketId(), buf, nBufSize, 0);
         
#endif

         if (n == -1)
         {

            fatal() << "recv " << networking_last_error() << bsd_socket_error(networking_last_error());

            OnDisconnect();
            SetCloseAndDelete(true);
            SetFlushBeforeClose(false);
            SetLost();
            information() << "tcp_socket::recv (B1) recv errorf(" << bsd_socket_error(networking_last_error()) << ")";
         }
         else if (!n)
         {
            //            int iError = get_error();
            //            #ifdef WINDOWS
            //            if (iError == WSAEWOULDBLOCK)
            //            #else
            //            #endif
            //            {
            //               informationf("tcp_socket::recv 0 No Error or WOULD BLOCK");
            //            }
            //            else
            {
               information() << "tcp_socket::recv (B2) recv disconnect";
               OnDisconnect();
               SetCloseAndDelete(true);
               SetFlushBeforeClose(false);
               SetLost();
               SetShutdownStatus(SHUT_WR);
            }

         }
         else if (n > 0 && n <= nBufSize)
         {

            set_connection_last_read_time();

            return n;

         }
         else
         {



            error() << "tcp_socket::recv " << (int)n << " abnormal value from recv";



            information() << "tcp_socket::recv (B3) recv abnormal value from recv";

         }

      }

      return n;

   }


   int tcp_socket::read(void* buf, int nBufSize)
   {

      int n = (int)nBufSize;

      n = recv(buf, nBufSize);

      if (n > 0 && n <= nBufSize)
      {

         m_bytes_received += n;

         m_timeLastRead.Now();

         if (GetTrafficMonitor())
         {

            GetTrafficMonitor()->write({ buf,n });

         }

         if (!m_b_input_buffer_disabled)
         {

            try
            {


               m_ibuf.write(buf, n);

            }
            catch (...)
            {


               warning() << "tcp_socket::read : ibuf overflow";


            }
         }

      }
      else if (n < 0)
      {

         error() << "tcp_socket::read " << (int)n << " abnormal value from rcv";

      }

      return n;

   }


   void tcp_socket::OnRead()
   {

      char* buf = (char*)m_memRead.data();

      int n = 0;

      try
      {

         n = read(buf, TCP_BUFSIZE_READ);

      }
      catch (...)
      {

         return;

      }

      on_read(buf, n);

   }


   void tcp_socket::on_read(const void* buf, memsize n)
   {

      // unbuffered
      if (n > 0)
      {

         set_connection_last_read_time();

         stream_socket::on_read(buf, n);

      }

      if (m_b_input_buffer_disabled)
      {

         return;

      }


      // further processing: socks4
      if (Socks4())
      {

         bool need_more = false;

         while (GetInputLength() && !need_more && !IsCloseAndDelete())
         {

            need_more = OnSocks4Read();

         }

      }

   }


   void tcp_socket::OnWriteComplete()
   {
   }


   void tcp_socket::OnWrite()
   {

      if (is_true("from_pool") && CallOnConnect())
      {

         SetCallOnConnect(false);
         SetConnected(true);
         OnConnect();

         return;
      }
      if (is_connecting())
      {
         int err = SoError();

         // don't reset connecting flag on error here, we want the OnConnectFailed timeout later on
         if (!err) // ok
         {
            set(!IsDisableRead(), false);
            set_connecting(false);
            SetCallOnConnect();
            return;
         }

         fatal() << "tcp: connect failed " << err << bsd_socket_error(err);

         set(false, false); // no more monitoring because connection failed

         // failed
         if (Socks4())
         {
            // %! leave 'is_connecting' flag set?
            OnSocks4ConnectFailed();
            return;
         }

         if (GetMaximumConnectionRetryCount() == -1 ||
            (GetMaximumConnectionRetryCount() && GetConnectionRetryCount() < GetMaximumConnectionRetryCount()))
         {
            // even though the connection failed at once, only retry after
            // the connection timeout.
            // should we even try to connect again, when CheckConnect returns
            // false it's because of a connection error - not a timeout...
            return;
         }
         set_connecting(false);
         SetCloseAndDelete(true);
         /// \todo state reason why connect failed
         OnConnectFailed();
         return;
      }
      // try send next block in buffer
      // if full block is sent, repeat
      // if all blocks are sent, reset m_wfds

      bool repeat = false;

      memsize sz = m_transfer_limit ? GetOutputLength() : 0;

      do
      {

         auto it = m_obuf.begin();

         if (!it)
         {

            return;

         }

         auto& poutput = *it;

         repeat = false;

         int n = (int)try_write(poutput->Buf(), poutput->Len());

         if (n > 0)
         {

            memsize left = poutput->erase(n);

            m_output_length -= n;

            if (!left)
            {

               m_obuf.erase(it);

               if (!m_obuf.get_size())
               {

                  OnWriteComplete();

               }
               else
               {

                  repeat = true;

               }

            }

         }

      } while (repeat);

      if (m_transfer_limit && sz > m_transfer_limit && GetOutputLength() < m_transfer_limit)
      {

         OnTransferLimit();

      }

      // check output buffer set, set/reset m_wfds accordingly
      if (m_obuf.get_size())
      {

         m_iSelectWrite = 1;

      }
      else
      {

         m_iSelectWrite = 0;

      }

   }






   int tcp_socket::_try_write(const void* buf, int len)
   {

      ::iptr n = 0;

      const_char_pointer psz = (const_char_pointer )buf;


#ifdef HAVE_OPENSSL

      if (IsSSL())
      {

         n = SSL_write(m_psslcontext->m_ssl, psz, (int)len);

         if (get_request_url_string() == "https://xn--thomasborregaardsrensen-1mc.com/")
         {

            print_line("Testing Response for https://xn--thomasborregaardsrensen-1mc.com/");

         }

         if (n == -1)
         {

            int errnr = SSL_get_error(m_psslcontext->m_ssl, (int)n);

            if (errnr != SSL_ERROR_WANT_READ && errnr != SSL_ERROR_WANT_WRITE)
            {

               if (errnr == SSL_ERROR_SYSCALL)
               {

                  auto cerrornumber = c_error_number();

                  auto strError = cerrornumber.get_error_description();

                  information() << "SSL_ERROR_SYSCALL errno : " << strError;

#ifdef WINDOWS

                  int iWsaError = ::WSAGetLastError();

                  information() << "SSL_ERROR_SYSCALL WSAGetLastError : " << iWsaError;

#endif

               }

               OnDisconnect();

               SetCloseAndDelete(true);

               SetFlushBeforeClose(false);

               SetLost();

               const_char_pointer errbuf = ERR_error_string(errnr, nullptr);

               fatal() << "OnWrite / SSL_write " << errnr << " " << errbuf;

               //throw ::exception(io_exception(errbuf));

            }

            //return 0;

         }
         else if (!n)
         {
            OnDisconnect();
            SetCloseAndDelete(true);
            SetFlushBeforeClose(false);
            SetLost();
            int errnr = SSL_get_error(m_psslcontext->m_ssl, (int)n);
            const_char_pointer errbuf = ERR_error_string(errnr, nullptr);
            information() << "SSL_write() returns 0: " << errnr << ", " << errbuf;
            //throw ::exception(io_exception(errbuf));
         }

      }
      else
#endif // HAVE_OPENSSL
      {
         //         retry:
//#if defined(__APPLE__)
//         int iSocket = GetSocketId();
//         n = (int)(::send(iSocket, buf, len, SO_NOSIGPIPE));
//#elif defined(SOLARIS)
//         n = ::send(GetSocketId(), (const_char_pointer )buf, (int)len, 0);
//#else

#if defined(MSG_NOSIGNAL)

         n = ::send(GetSocketId(), (const_char_pointer )buf, (int)len, MSG_NOSIGNAL);
         
#else

         n = ::send(GetSocketId(), (const_char_pointer )buf, (int)len, 0);
         
#endif

         ///#endif
         if (n == -1)
         {
            int iError = networking_last_error();
            // normal error codes:
            // WSAEWOULDBLOCK
            //       EAGAIN or EWOULDBLOCK
#ifdef _WIN32
            if (iError != WSAEWOULDBLOCK) // 10035L
#else
            if (iError != EWOULDBLOCK)
#endif
            {

               fatal() << "send " << networking_last_error() << bsd_socket_error(networking_last_error());

               OnDisconnect();
               SetCloseAndDelete(true);
               SetFlushBeforeClose(false);
               SetLost();
               //throw ::exception(io_exception(bsd_socket_error(networking_last_error())));
            }
            //else
            //{
            //   fd_set w;
            //   fd_set e;
            //   FD_ZERO(&e);
            //   FD_ZERO(&w);
            //   FD_SET(GetSocketId(), &e);
            //   FD_SET(GetSocketId(), &w);
            //   struct timeval tv;
            //   tv.tv_sec = 1;
            //   tv.tv_usec = 0;
            //   ::select((int) (GetSocketId() + 1), nullptr, &w, &e, &tv);
            //   goto retry;
            //}

            //return 0;
         }

      }

      if (n > 0)
      {

         m_bytes_sent += n;

         m_timeLastWrite.Now();

         if (GetTrafficMonitor())
         {

            GetTrafficMonitor()->write({ buf,n });

         }

         set_connection_last_write_time();

      }

      return (int)n;

   }


   void tcp_socket::buffer(const void* pdata, int len)
   {

      const_char_pointer buf = (const_char_pointer )pdata;

      memsize ptr = 0;

      m_output_length += len;

      while (::comparison::lt(ptr, len))
      {
         // buf/len => pbuf/sz
         int space = 0;

         if (m_obuf_top && (space = m_obuf_top->Space()) > 0)
         {
            const_char_pointer pbuf = buf + ptr;
            int sz = (int)(len - ptr);
            if (space >= sz)
            {
               m_obuf_top->add(pbuf, sz);
               ptr += sz;
            }
            else
            {
               m_obuf_top->add(pbuf, space);
               ptr += space;
            }
         }
         else
         {

            if (m_obuf_top)
            {

               m_obuf.add_tail(m_obuf_top);

            }

            m_obuf_top = __allocate output(TCP_OUTPUT_CAPACITY);

         }

      }

   }


   /*
      void tcp_socket::write(const ::scoped_string & scopedstr)
      {
         write(str,  (int) str.length());
      }
   */


   int tcp_socket::try_write(const void* buf, int len)
   {

      return _try_write(buf, len);

      //auto poutput = ::place(::new output(len));

      //poutput->m_memory.assign(buf, len);

      //m_obuf.add_tail(poutput);

      //return len;

   }


   void tcp_socket::write(const void* p, ::memsize s)
   {

      const unsigned char* buf = (const unsigned char*)p;

      if (!Ready() && !is_connecting())
      {

         warning() << "write: Attempt to write to a non-ready socket"; // warning

         if (GetSocketId() == INVALID_SOCKET)
         {

            information() << "write: * GetSocketId() == INVALID_SOCKET";


         }
         if (is_connecting())
         {


            information() << "write: * is_connecting()";

         }
         if (IsCloseAndDelete())
         {


            information() << "write: * IsCloseAndDelete()";



         }
         return;
      }
      if (!IsConnected())
      {

         warning() << "write: Attempt to write to a non-connected socket, will be sent on connect"; // warning

         buffer(buf, (int)s);

         return;

      }

      if (m_obuf_top)
      {

         buffer(buf, (int)s);

         return;

      }
      else
      {

         int n = (int)try_write(buf, (int)s);

         if (n >= 0 && n < (int)s)
         {

            buffer(buf + n, (int)(s - n));

         }

      }
      // if ( data in buffer || !IsConnected )
      // {
      //   add to buffer
      // }
      // else
      // try_send
      // if any data is unsent, buffer it and set m_wfds

      // check output buffer set, set/reset m_wfds accordingly

      if (m_obuf.get_size())
      {

         m_iSelectWrite = 1;

      }
      else
      {

         m_iSelectWrite = 0;

      }

   }


   void tcp_socket::OnLine(const ::scoped_string & scopedstr)
   {

      m_ptcpsocketInterface->OnLine(scopedstr);

   }



   void tcp_socket::OnSocks4Connect()
   {
      char request[1000];
      memory_set(request, 0, sizeof(request));
      request[0] = 4; // socks v4
      request[1] = 1; // command code: CONNECT
      {
         auto paddress = GetClientRemoteAddress();
         ::pointer < ::networking_bsd::address > paddress2 = paddress;
         if (paddress2->is_valid())
         {
            struct sockaddr* psockaddr = (struct sockaddr*)paddress2->sa();
            struct sockaddr_in* psockaddrin = (struct sockaddr_in*)psockaddr;
            if (psockaddrin->sin_family == AF_INET)
            {
               ::memory_copy(request + 2, &psockaddrin->sin_port, 2); // nwbo is ok here
               ::memory_copy(request + 4, &psockaddrin->sin_addr, sizeof(struct in_addr));
            }
            else
            {
               /// \todo warn
            }
         }
         else
         {
            /// \todo warn
         }
      }

      ansi_cpy(request + 8, GetSocks4Userid());

      ::collection::count length = GetSocks4Userid().length() + 8 + 1;

      write({ request,length });

      m_socks4_state = 0;

   }


   void tcp_socket::OnSocks4ConnectFailed()
   {

      warning() << "OnSocks4ConnectFailed: connection to socks4 server failed, trying direct connection";

      if (!::pointer < sockets_bsd::socket_handler >(socket_handler())->Socks4TryDirect())
      {

         set_connecting(false);

         SetCloseAndDelete();

         OnConnectFailed(); // just in case

      }
      else
      {

         SetRetryClientConnect();

      }

   }


   bool tcp_socket::OnSocks4Read()
   {

      switch (m_socks4_state)
      {
      case 0:
         m_ibuf.read(&m_socks4_vn, 1);
         m_socks4_state = 1;
         break;
      case 1:
         m_ibuf.read(&m_socks4_cd, 1);
         m_socks4_state = 2;
         break;
      case 2:
         if (GetInputLength() > 1)
         {
            m_ibuf.read((char*)&m_socks4_dstport, 2);
            m_socks4_state = 3;
         }
         else
         {
            return true;
         }
         break;
      case 3:
         if (GetInputLength() > 3)
         {
            m_ibuf.read((char*)&m_socks4_dstip, 4);
            SetSocks4(false);

            switch (m_socks4_cd)
            {
            case 90:
               OnConnect();


               information() << "OnSocks4Read: Connection established";

               break;
            case 91:
            case 92:
            case 93:


               fatal() << "OnSocks4Read: socks4 server reports connect failed";

               set_connecting(false);
               SetCloseAndDelete();
               OnConnectFailed();
               break;
            default:


               fatal() << "OnSocks4Read: socks4 server unrecognized response";

               SetCloseAndDelete();
               break;
            }
         }
         else
         {
            return true;
         }
         break;
      }
      return false;
   }




   void tcp_socket::OnSSLConnect()
   {

      //SetNonblocking(true);

      SetNonblocking(false);

      //synchronous_lock slMap(pnetworking2->m_clientcontextmap.m_pmutex);

      if (is_true("from_pool"))
         return;

      //{

      //   if(m_ssl_ctx)
      //   {

      //      informationf("SSL Context already initialized - closing socket");

      //      SetCloseAndDelete(true);

      //      return;

      //   }

      //   InitSSLClient();

      //}

//      if(!m_ssl_ctx)
      //    {

      //int iError = 0;

//retry_init_ssl_client:

      InitSSLClient();

      //  }

      //slMap.unlock();

      if (m_psslcontext->m_pclientcontext.is_set()
         && m_psslcontext->m_pclientcontext->m_psslcontext != nullptr)
      {

         /* Connect the SSL socket */

         m_psslcontext->m_ssl = SSL_new(m_psslcontext->m_pclientcontext->m_psslcontext);

         if (!m_psslcontext->m_ssl)
         {

            information() << "m_ssl is nullptr";

            SetCloseAndDelete(true);

            return;

         }

         if (m_bClientSessionSet || m_psslcontext->m_pclientcontext->m_psslsession == nullptr)
         {

            if (m_strTlsHostName.has_character())
            {

               SSL_set_tlsext_host_name(m_psslcontext->m_ssl, (char*)(const_char_pointer )m_strTlsHostName);

            }

            //SSL_set_mode(m_ssl, SSL_MODE_AUTO_RETRY);

         }

         m_psslcontext->m_sbio = BIO_new_socket((int)GetSocketId(), BIO_NOCLOSE);

         if (!m_psslcontext->m_sbio)
         {

            information() << "m_sbio is nullptr";

            SetCloseAndDelete(true);

            return;

         }

         SSL_set_bio(m_psslcontext->m_ssl, m_psslcontext->m_sbio, m_psslcontext->m_sbio);


         if (!SSLNegotiate())
         {

            SetSSLNegotiate();

         }

      }
      else
      {

         SetCloseAndDelete();

      }

   }


   void tcp_socket::OnSSLAccept()
   {

      //SetNonblocking(true);

      SetNonblocking(false);

      //synchronous_lock slMap(pnetworking2->m_servercontextmap.m_pmutex);

      {
         if (m_psslcontext.is_set()
            && m_psslcontext->m_pclientcontext.is_set()
            && m_psslcontext->m_pclientcontext->m_psslcontext != nullptr)
         {
            information() << "SSL Context already initialized - closing socket";
            SetCloseAndDelete(true);
            return;
         }
         InitSSLServer();
         SetSSLServer();
      }


      //synchronous_lock synchronouslock(m_pmutexSslCtx);

      //slMap.unlock();


      if (m_psslcontext->m_pclientcontext->m_psslcontext)
      {
         auto pssl = SSL_new(m_psslcontext->m_pclientcontext->m_psslcontext);
         m_psslcontext->m_ssl = pssl;
         if (!pssl)
         {
            information() << "m_ssl is nullptr";
            SetCloseAndDelete(true);
            return;
         }
         SSL_set_app_data2(pssl, this);
         //         SSL_set_mode(pssl, SSL_MODE_AUTO_RETRY);
         //SSL_set_msg_callback(pssl, SSL_trace);

         //SSL_set_msg_callback_arg(pssl, BIO_new_fp(stdout, 0));

         printf("---------------------------------\n");
         printf("tcp_socket::OnSSLAccept\n");
         printf("tcp_socket::OnSSLAccept\n");
         printf("tcp_socket::OnSSLAccept\n");
         printf("tcp_socket::OnSSLAccept\n");
         printf("tcp_socket::OnSSLAccept\n");
         printf("tcp_socket::OnSSLAccept\n");
         printf("tcp_socket::OnSSLAccept\n");
         printf("---------------------------------\n");

         m_psslcontext->m_sbio = BIO_new_socket((int)GetSocketId(), BIO_NOCLOSE);
         if (!m_psslcontext->m_sbio)
         {
            information() << "m_sbio is nullptr";
            SetCloseAndDelete(true);
            return;
         }
         SSL_set_bio(m_psslcontext->m_ssl, m_psslcontext->m_sbio, m_psslcontext->m_sbio);
         //      if (!SSLNegotiate())
         {
            SetSSLNegotiate();
         }
      }
   }


   bool tcp_socket::SSLNegotiate()
   {

      if (IsSSLServer())
      {

         return SSLNegotiate_Server();

      }
      else
      {

         return SSLNegotiate_Client();

      }

   }


   bool tcp_socket::SSLNegotiate_Client()
   {

      //information() << "SSLNegotiate: SSL_connect";

      if (m_bReuseSession && !m_bClientSessionSet && m_psslcontext->m_pclientcontext->m_psslsession != nullptr)
      {

         SSL_set_session(m_psslcontext->m_ssl, m_psslcontext->m_pclientcontext->m_psslsession);

         m_bClientSessionSet = true;

      }

      //SSL_set_min_proto_version(m_psslcontext->m_ssl, TLS1_3_VERSION);

      //SSL_set_max_proto_version(m_psslcontext->m_ssl, TLS1_1_VERSION);

      //TLS1_1_VERSION

      int r = SSL_connect(m_psslcontext->m_ssl);

      if (r > 0)
      {

         SetSSLNegotiate(false);

         if (SSL_session_reused(m_psslcontext->m_ssl))
         {

            information() << "REUSED SESSION";

         }
         else
         {

            information() << "NEW SESSION";

         }

         long x509_err = cert_common_name_check(m_strHost);

         if (x509_err != X509_V_OK
            && x509_err != X509_V_ERR_SELF_SIGNED_CERT_IN_CHAIN
            && x509_err != X509_V_ERR_UNABLE_TO_GET_ISSUER_CERT_LOCALLY
            && x509_err != X509_V_ERR_APPLICATION_VERIFICATION)
         {


            information() << "SSLNegotiate/cert_common_name_check: cert_common_name_check failed (error=" << x509_err << ",url=" << m_strUrl << ")";

            SetSSLNegotiate(false);
            SetCloseAndDelete();
            OnSSLConnectFailed();
            return false;

         }

         if (m_bReuseSession)
         {

            if (m_psslcontext && m_psslcontext->m_pclientcontext && m_psslcontext->m_pclientcontext->m_psslsession)
            {

               destroy_ssl_session();

            }

            if (!m_psslcontext || !m_psslcontext->m_pclientcontext || !m_psslcontext->m_pclientcontext->m_psslsession)
            {

               get_ssl_session();

            }

         }

         /// \todo: resurrect certificate check... client
         //         CheckCertificateChain( "");//ServerHOST);
         //SetNonblocking(false);
         //
         {
            SetConnected();
            if (GetOutputLength())
            {
               OnWrite();
            }
         }
         if (IsReconnect())
            OnReconnect();
         else
         {
            OnConnect();
         }


         //information() << "SSLNegotiate/SSL_connect: Connection established";

         return true;

      }
      else if (!r)
      {

         long error = ERR_get_error();
         const_char_pointer error_str = ERR_error_string(error, nullptr);
         warning() << "could not SSL_connect: " << error_str;

         int iErrorSsl = SSL_get_error(m_psslcontext->m_ssl, r);

         //if(m_spsslclientcontext.is_set() &&
         if (m_psslcontext->m_pclientcontext->m_psslcontext != nullptr &&
            iErrorSsl == SSL_ERROR_ZERO_RETURN
            && (m_psslcontext->m_pclientcontext->m_psslmethod == TLS_client_method()))
         {

            warning() << "ssl_error_zero_return";

         }

         else
         {

            if (m_bReuseSession)
            {

               if (m_psslcontext->m_pclientcontext->m_psslsession != nullptr)
               {

                  if (m_psslcontext->m_iSslCtxRetry == 0)
                  {

                     m_psslcontext->m_iSslCtxRetry = 1;

                     destroy_ssl_session();

                     SSL_clear(m_psslcontext->m_ssl);

                  }
                  else
                  {

                     m_psslcontext->m_iSslCtxRetry = 0;

                  }

               }

            }

            if (m_psslcontext->m_iSslCtxRetry == 0)
            {

               information() << "SSLNegotiate/SSL_connect: Connection failed";

               SetSSLNegotiate(false);
               SetCloseAndDelete();
               OnSSLConnectFailed();

            }

         }

      }
      else
      {
         int iErrorSSL = SSL_get_error(m_psslcontext->m_ssl, r);
         if (iErrorSSL == SSL_ERROR_WANT_READ || iErrorSSL == SSL_ERROR_WANT_WRITE)
         {
         }
         else if (iErrorSSL == SSL_ERROR_WANT_CONNECT || iErrorSSL == SSL_ERROR_WANT_ACCEPT)
         {
         }
         else
         {

            char msg[1024];

            auto uError = ERR_get_error();

            ERR_error_string_n(uError, msg, sizeof(msg));

            if (iErrorSSL == SSL_ERROR_SYSCALL)
            {

               //                  auto last_error = networking_last_error();

                              // informationf("");

            }


            information() << "SSLNegotiate: SSL_connect() failed: " << msg;

            SetSSLNegotiate(false);
            SetCloseAndDelete(true);
            OnSSLConnectFailed();
         }
      }

      return false;

   }


   bool tcp_socket::SSLNegotiate_Server()
   {

      int r = SSL_accept(m_psslcontext->m_ssl);
      int iError = networking_last_error();
      if (r > 0)
      {
         SetSSLNegotiate(false);
         /// \todo: resurrect certificate check... server
         //         CheckCertificateChain( "");//ClientHOST);
         SetNonblocking(false);
         //
         {
            SetConnected();
            if (GetOutputLength())
            {
               OnWrite();
            }
         }
         OnAccept();


         //information() << "SSLNegotiate/SSL_accept: Connection established";

         return true;

      }
      else if (!r)
      {


         information() << "SSLNegotiate/SSL_accept: Connection failed";

         SetSSLNegotiate(false);
         SetCloseAndDelete();
         OnSSLAcceptFailed();
      }
      else
      {

         r = SSL_get_error(m_psslcontext->m_ssl, r);

         if (r == SSL_ERROR_WANT_READ)
         {

            information() << "SSL_accept return code is SSL_ERROR_WANT_READ";

         }
         else if (r == SSL_ERROR_WANT_WRITE)
         {

            information() << "SSL_accept return code is SSL_ERROR_WANT_WRITE";

         }
         else if (r == SSL_ERROR_WANT_CONNECT)
         {

            information() << "SSL_accept return code is SSL_ERROR_WANT_CONNECT";

         }
         else if (r == SSL_ERROR_WANT_ACCEPT)
         {

            information() << "SSL_accept return code is SSL_ERROR_WANT_ACCEPT";

         }
         else
         {

            if (r == SSL_ERROR_SYSCALL)
            {

               error() << "SSLNegotiate SSL_ERROR_SYSCALL networking_last_error() = " << iError;

            }
            else
            {

               information() << "SSLNegotiate SSL_accept() failed with : " << r << " network error = : " << iError;

            }

            SetSSLNegotiate(false);

            SetCloseAndDelete(true);

            OnSSLAcceptFailed();

         }

      }

      return false;

   }


   void tcp_socket::InitSSLClient()
   {
      //InitializeContext(m_strInitSSLClientContext,SSLv23_method());
      //InitializeContext(m_strInitSSLClientContext,TLSv1_client_method());

      //InitializeContext(m_strInitSSLClientContext,TLS_client_method());

      InitializeContext(m_strInitSSLClientContext, TLS_client_method());
   }


   void tcp_socket::set_init_ssl_client_context(const ::scoped_string & scopedstrInitSSLClientContext)
   {

      m_strInitSSLClientContext = scopedstrInitSSLClientContext;

   }


   void tcp_socket::InitSSLServer()
   {

      m_ptcpsocketInterface->InitSSLServer();

      //fatal() <<"InitSSLServer: You MUST implement your own InitSSLServer method";

      //SetCloseAndDelete();
   }


   void tcp_socket::_001InitSSLServer()
   {

      // here's the server.pem file we just created above
   // %! remember to machine the password to the one you used for your server key
   //InitializeContext(m_strCat, m_strCat, "", SSLv23_server_method());

      string strId = m_strCat;

      auto psystem = system();

      if (strId.case_insensitive_begins("cat://"))
      {

         //auto pcrypto = psystem->crypto();

         strId = "cat://" + psystem->crypto()->md5(strId);

      }
      InitializeContext(strId, m_strCat, "", TLS_server_method());

      string strCipherList = m_strCipherList;

      if (strCipherList.is_empty())
      {

         strCipherList = "ECDHE-RSA-AES256-SHA384:ECDHE-RSA-AES256-SHA:ECDHE-RSA-AES128-SHA:ECDHE-RSA-RC4-SHA:DHE-RSA-AES256-SHA:DHE-RSA-AES128-SHA:RSA:SHA:3DES:!aNULL:!eNULL:!EXP:!LOW:!MD5:@STRENGTH";

      }

      //if (strCipherList.find("DH") >= 0)
      //{

      //   ::int_array ia;

      //   ia.add(512);
      //   ia.add(1024);
      //   ia.add(2048);
      //   ia.add(4096);

      //   for (::collection::index i = 0; i < ia.get_count(); i++)
      //   {

      //      int keylength = ia[i];

      //      if (get_dh(keylength) == nullptr)
      //      {

      //         string strTitle = ::file::path(m_strCat).name();

      //         if (strTitle.case_insensitive_find(".") >= 0)
      //         {

      //            strTitle = strTitle.left(strTitle.rear_find("."));

      //         }

      //         string strFile = ::file::path(m_strCat).sibling(strTitle) + ".dh" + as_string(keylength) + ".pem";

      //         FILE * paramfile = fopen(strFile, "r");

      //         if (paramfile)
      //         {

      //            DH * pdh = PEM_read_DHparams(paramfile, nullptr, nullptr, nullptr);

      //            set_dh(keylength, pdh);

      //            fclose(paramfile);

      //         }

      //      }

      //   }

      //   SSL_CTX_set_tmp_dh_callback(m_psslcontext->m_pclientcontext->m_psslcontext, &tmp_dh_callback);

      //}


      //int nid = OBJ_sn2nid(ECDHE_CURVE);

      if (strCipherList.contains("ECDH"))
      {

         //EVP_PKEY_CTX_new_from_name(nullptr, )

         //EC_KEY *ecdh = EC_KEY_new_by_curve_name(NID_secp384r1);

         //SSL_CTX_set_tmp_ecdh(m_psslcontext->m_pclientcontext->m_psslcontext, ecdh);

         int_array iaCurves;
         //int* curves_new;
         //char* cs = NULL;
         //char* p, * q;
         //int rv = -1;
         //int nid;


#define TLS_ECDHE_CURVES	"X25519,P-256,P-384"
         //const_char_pointer curves = NID_secp384r1;

         //free(config->ecdhecurves);
         //config->ecdhecurves = NULL;
         //config->ecdhecurves_len = 0;

         //if (curves == NULL || strcasecmp(curves, "default") == 0)
         //   curves = TLS_ECDHE_CURVES;

         iaCurves.add(NID_X25519);
         iaCurves.add(NID_secp256k1);
         iaCurves.add(NID_secp384r1);
         // iaCurves.add(NID_secp521r1);

         if (!SSL_CTX_set1_groups(m_psslcontext->m_pclientcontext->m_psslcontext, iaCurves.get_data(), (long)iaCurves.get_size()))
         {

            warning() << "failed to set ecdhe curves";

         }

      }

      //if (strCipherList.find("DH") >= 0)
      //{

      //   SSL_CTX_set_options(m_psslcontext->m_pclientcontext->m_psslcontext, SSL_CTX_get_options(m_psslcontext->m_pclientcontext->m_psslcontext) | SSL_OP_SINGLE_DH_USE | SSL_OP_CIPHER_SERVER_PREFERENCE);

      //}
      //else
      {

         //SSL_CTX_set_options(m_psslcontext->m_pclientcontext->m_psslcontext, SSL_CTX_get_options(m_psslcontext->m_pclientcontext->m_psslcontext) | SSL_OP_CIPHER_SERVER_PREFERENCE);

      }

      if (!SSL_CTX_set_cipher_list(m_psslcontext->m_pclientcontext->m_psslcontext, strCipherList))
      {

         warning() << "failed to set cipher_list";

      }

   }


   void tcp_socket::InitializeContext(const string& context, const SSL_METHOD* pmethod)
   {

      auto pnetworking2 = __SystemNetworking(system());

      ssl_client_context_map& clientcontextmap = pnetworking2->m_clientcontextmap;

      ::pointer<ssl_client_context>psslclientcontext = clientcontextmap.get_context(context, pmethod);

      m_psslcontext = __allocate ssl_context();

      m_psslcontext->m_pclientcontext = psslclientcontext;

   }


   void tcp_socket::InitializeContext(const string& context, const string& keyfile, const string& password, const SSL_METHOD* meth_in)
   {

      if (m_psslcontext.is_null())
      {

         m_psslcontext = __allocate ssl_context();

      }

      if (m_psslcontext->m_pclientcontext.is_null())
      {

         m_psslcontext->m_pclientcontext = __allocate ssl_client_context(meth_in != nullptr ? meth_in : TLS_server_method());

         m_psslcontext->m_pclientcontext->initialize(this);

      }

      //m_psslcontext->m_pclientcontext->m_psslcontext = SSL_CTX_new(m_psslcontext->m_pclientcontext->m_psslmethod);
      SSL_CTX_set_mode(m_psslcontext->m_pclientcontext->m_psslcontext, SSL_MODE_AUTO_RETRY | SSL_MODE_RELEASE_BUFFERS);
      SSL_CTX_set_options(m_psslcontext->m_pclientcontext->m_psslcontext, SSL_OP_NO_COMPRESSION | SSL_CTX_get_options(m_psslcontext->m_pclientcontext->m_psslcontext));
      // session atom
      //int iSetSessionResult = -1;
      unsigned int uSessionIdMaxLen = SSL_MAX_SSL_SESSION_ID_LENGTH;

      auto strContextMd5 = crypto()->md5(context);

      //int iLenMd5 = strContextMd5.length();

      if (context.length())
      {
         //iSetSessionResult = SSL_CTX_set_session_id_context(m_psslcontext->m_pclientcontext->m_psslcontext,
         //                                                   (const uchar *) (const_char_pointer )context,
         //                                                   minimum((unsigned int) context.length(), uSessionIdMaxLen));

         SSL_CTX_set_session_id_context(m_psslcontext->m_pclientcontext->m_psslcontext,
            (const uchar*)(const_char_pointer )strContextMd5,
            minimum((unsigned int)strContextMd5.length(), uSessionIdMaxLen));
      }
      else
      {

         // iSetSessionResult =

         SSL_CTX_set_session_id_context(m_psslcontext->m_pclientcontext->m_psslcontext,
            (const uchar*)"--is_empty--", 9);
      }

      if (keyfile.case_insensitive_begins("cat://") || keyfile.case_insensitive_ends(".cat"))
      {

         ::cast < ::networking_bsd::networking > pnetworkingbsd = networking();

         auto pcert = pnetworkingbsd->get_cert(keyfile);

         if (password.has_character())
         {

            SSL_CTX_set_default_passwd_cb(m_psslcontext->m_pclientcontext->m_psslcontext, tcp_socket_SSL_password_cb);

            SSL_CTX_set_default_passwd_cb_userdata(m_psslcontext->m_pclientcontext->m_psslcontext, (socket*)this);

         }


#if OPENSSL_VERSION_NUMBER >= 0x10101000L  && !defined(LIBRESSL_VERSION_NUMBER)


         if (!SSL_CTX_use_cert_and_key(m_psslcontext->m_pclientcontext->m_psslcontext, pcert->m_pcertificate, pcert->m_pkey, pcert->m_pchain, 1))
         {

            fatal() << "tcp_socket InitializeContext,-1,Couldn't read certificate string " << keyfile;

         }


#else


         if (!SSL_CTX_use_certificate(m_psslcontext->m_pclientcontext->m_psslcontext, pcert->m_pcertificate))
         {

            fatal() << "tcp_socket InitializeContext: Couldn't read certificate string " << keyfile;

         }


         if (!SSL_CTX_use_PrivateKey(m_psslcontext->m_pclientcontext->m_psslcontext, pcert->m_pkey))
         {

            fatal() << "tcp_socket InitializeContext: Couldn't read certificate string " << keyfile;

         }
         

		 for(int i = 0; i < sk_X509_num(pcert->m_pchain); i++)
         //for (auto x : xa)
         {

            if (!SSL_CTX_add_extra_chain_cert(m_psslcontext->m_pclientcontext->m_psslcontext, sk_X509_value(pcert->m_pchain, i)))
            {

               fatal() << "tcp_socket InitializeContext: Couldn't read certificate string " + keyfile;

            }

         }

#endif


         //         }

      }
      else
      {

         if (!SSL_CTX_use_certificate_chain_file(m_psslcontext->m_pclientcontext->m_psslcontext, keyfile))
         {
            /* Load our keys and certificates*/
            if (!(SSL_CTX_use_certificate_file(m_psslcontext->m_pclientcontext->m_psslcontext, keyfile, SSL_FILETYPE_PEM)))
            {
               fatal() << "tcp_socket InitializeContext: Couldn't read certificate file " << keyfile;
            }
         }
         m_password = password;
         SSL_CTX_set_default_passwd_cb(m_psslcontext->m_pclientcontext->m_psslcontext, tcp_socket_SSL_password_cb);
         SSL_CTX_set_default_passwd_cb_userdata(m_psslcontext->m_pclientcontext->m_psslcontext, (socket*)this);

         if (!(SSL_CTX_use_PrivateKey_file(m_psslcontext->m_pclientcontext->m_psslcontext, keyfile, SSL_FILETYPE_PEM)))
         {

            fatalf("tcp_socket InitializeContext: Couldn't read private key file %s ", keyfile.c_str());

         }

      }


      {
         synchronous_lock synchronouslock(this->synchronization());
         int i;

         //auto psystem = system();

         auto pnetworking2 = __SystemNetworking(system());


         int cnt = sizeof(pnetworking2->m_baTicketKey) / SSL_SESSION_TICKET_KEY_SIZE;
         m_ticketkeya.set_size(cnt);
         int j;
         for (i = 0; i < cnt; ++i)
         {
            j = (SSL_SESSION_TICKET_KEY_SIZE * i);
            ::memory_copy(m_ticketkeya[i].key_name, pnetworking2->m_baTicketKey + j, 16);
            ::memory_copy(m_ticketkeya[i].hmac_key, pnetworking2->m_baTicketKey + j + 16, 16);
            ::memory_copy(m_ticketkeya[i].aes_key, pnetworking2->m_baTicketKey + j + 32, 16);
         }
      }

#if OPENSSL_VERSION_NUMBER >= 0x30000000L

      SSL_CTX_set_tlsext_ticket_key_evp_cb(m_psslcontext->m_pclientcontext->m_psslcontext, &ssl_tlsext_ticket_key_evp_cb);

#else

      SSL_CTX_set_tlsext_ticket_key_cb(m_psslcontext->m_pclientcontext->m_psslcontext, ssl_tlsext_ticket_key_cb);

#endif

   }


   void tcp_socket::InitializeContext(const string& context, const string& certfile, const string& keyfile, const string& password, const SSL_METHOD* meth_in)
   {

      /* create our context*/
      m_psslcontext->m_pclientcontext->m_psslmethod = meth_in != nullptr ? meth_in : TLS_client_method();
      m_psslcontext->m_pclientcontext->m_psslcontext = SSL_CTX_new(m_psslcontext->m_pclientcontext->m_psslmethod);
      SSL_CTX_set_mode(m_psslcontext->m_pclientcontext->m_psslcontext, SSL_MODE_AUTO_RETRY | SSL_MODE_RELEASE_BUFFERS);
      SSL_CTX_set_options(m_psslcontext->m_pclientcontext->m_psslcontext, SSL_OP_NO_COMPRESSION | SSL_CTX_get_options(m_psslcontext->m_pclientcontext->m_psslcontext));
      // session atom
      if (context.length())
         SSL_CTX_set_session_id_context(m_psslcontext->m_pclientcontext->m_psslcontext, (const uchar*)(const  char*)context, (unsigned int)context.length());
      else
         SSL_CTX_set_session_id_context(m_psslcontext->m_pclientcontext->m_psslcontext, (const uchar*)"--is_empty--", 9);

      /* Load our keys and certificates*/
      if (!(SSL_CTX_use_certificate_file(m_psslcontext->m_pclientcontext->m_psslcontext, certfile, SSL_FILETYPE_PEM)))
      {
         fatal() << "InitializeContext: Couldn't read certificate file " << keyfile;
      }

      m_password = password;
      SSL_CTX_set_default_passwd_cb(m_psslcontext->m_pclientcontext->m_psslcontext, tcp_socket_SSL_password_cb);
      SSL_CTX_set_default_passwd_cb_userdata(m_psslcontext->m_pclientcontext->m_psslcontext, (socket*)this);
      if (!(SSL_CTX_use_PrivateKey_file(m_psslcontext->m_pclientcontext->m_psslcontext, keyfile, SSL_FILETYPE_PEM)))
      {
         fatal() << "InitializeContext: Couldn't read private key file " << keyfile;
         //information(string("tcp_socket InitializeContext(2),0,Couldn't read private key file ") + keyfile + string("e_trace_level_fatal"));
      }

   }


   int tcp_socket_SSL_password_cb(char* buf, int num, int rwflag, void* userdata)
   {

      __UNREFERENCED_PARAMETER(rwflag);

      socket* psocket = static_cast<socket*>(userdata);

      tcp_socket* ptcpsocket = dynamic_cast<tcp_socket*>(psocket);

      string strPassword = ptcpsocket ? ptcpsocket->GetPassword().c_str() : "";

      if (num < strPassword.length() + 1)
      {

         return 0;

      }

      ansi_cpy(buf, strPassword);

      return (int)strPassword.length();

   }


   void tcp_socket::close()
   {

      if (GetSocketId() == INVALID_SOCKET) // this could happen
      {


         warning() << "socket::close: file descriptor invalid";

         return;

      }
      
#ifdef HAVE_OPENSSL

      m_psslcontext.release();

#endif

      int n;

      SetNonblocking(true);

      if (!Lost() && IsConnected() && !(GetShutdownStatus() & SHUT_WR))
      {

         if (shutdown(GetSocketId(), SHUT_WR) == -1)
         {

            // failed...


            error() << "shutdown " << networking_last_error() << bsd_socket_error(networking_last_error());



         }

      }

      char tmp[1000];

      if (!Lost() && (n = (int) ::recv(GetSocketId(), tmp, 1000, 0)) >= 0)
      {

         if (n)
         {


            warning() << "read() after shutdown: bytes read";

         }

      }

      socket::close();

   }



#ifdef HAVE_OPENSSL
   SSL_CTX* tcp_socket::GetSslContext()
   {
      if (!m_psslcontext->m_pclientcontext->m_psslcontext)
      {


         warning() << "GetSslContext: SSL Context is nullptr; check InitSSLServer/InitSSLClient";

      }
      return m_psslcontext->m_pclientcontext->m_psslcontext;
   }

   SSL* tcp_socket::GetSsl()
   {
      if (!m_psslcontext->m_ssl)
      {


         warning() << "GetSsl: SSL is nullptr; check InitSSLServer/InitSSLClient";

      }
      return m_psslcontext->m_ssl;
   }
#endif


   void tcp_socket::SetReconnect(bool bReconnect)
   {
      m_bReconnect = bReconnect;
   }


   void tcp_socket::OnRawData(char* buf_in, memsize len)
   {

      socket::OnRawData(buf_in, len);

   }


   memsize tcp_socket::GetInputLength()
   {
      return (memsize)m_ibuf.get_length();
   }


   memsize tcp_socket::GetOutputLength()
   {
      return m_output_length;
   }


   unsigned long long tcp_socket::GetBytesReceived(bool clear)
   {
      unsigned long long z = m_bytes_received;
      if (clear)
         m_bytes_received = 0;
      return z;
   }


   unsigned long long tcp_socket::GetBytesSent(bool clear)
   {
      unsigned long long z = m_bytes_sent;
      if (clear)
         m_bytes_sent = 0;
      return z;
   }


   tcp_socket::output* tcp_socket::top_output_buffer()
   {

      return m_obuf_top;

   }


   bool tcp_socket::Reconnect()
   {
      return m_bReconnect;
   }


   void tcp_socket::SetIsReconnect(bool bTryingReconnect)
   {

      m_bTryingReconnect = bTryingReconnect;

   }


   bool tcp_socket::IsReconnect()
   {

      return m_bTryingReconnect;

   }


   string tcp_socket::GetPassword()
   {

      return m_password;

   }


   void tcp_socket::DisableInputBuffer(bool x)
   {

      m_b_input_buffer_disabled = x;

   }


   void tcp_socket::OnOptions(int family, int type, int protocol, SOCKET s)
   {

      __UNREFERENCED_PARAMETER(family);
      __UNREFERENCED_PARAMETER(type);
      __UNREFERENCED_PARAMETER(protocol);

      //informationf("socket::OnOptions()");
      
#ifdef SO_NOSIGPIPE

      _SetSoNosigpipe(s, true);
      
      printf_line("_SetSoNosigpipe for socket %d", s);
      
      preempt(5_s);

#endif

      _SetSoReuseaddr(s, true);
      _SetSoKeepalive(s, true);

   }


   void tcp_socket::SetLineProtocol(bool x)
   {
      stream_socket::SetLineProtocol(x);
      DisableInputBuffer(x);
   }


   bool tcp_socket::SetTcpNodelay(bool x)
   {
#ifdef TCP_NODELAY
      int optval = x ? 1 : 0;
      if (setsockopt(GetSocketId(), IPPROTO_TCP, TCP_NODELAY, (char*)&optval, sizeof(optval)) == -1)
      {


         fatal() << "setsockopt(IPPROTO_TCP, TCP_NODELAY) " << networking_last_error() << bsd_socket_error(networking_last_error());

         return false;
      }
      return true;
#else

      information() << "socket option not available: TCP_NODELAY";

      return false;
#endif
   }


   void tcp_socket::on_connection_timeout()
   {

      //m_ptcpsocketInterface->on_connection_timeout();

      fatal() << "connect: connect timeout";

      m_estatus = error_connection_timed_out;

      if (Socks4())
      {

         OnSocks4ConnectFailed();
         // retry direct connection
      }
      else if (GetMaximumConnectionRetryCount() == -1 ||
         (GetMaximumConnectionRetryCount() && GetConnectionRetryCount() < GetMaximumConnectionRetryCount()))
      {

         IncrementConnectionRetryCount();

         // ask socket via OnConnectRetry callback if we should continue trying
         if (OnConnectRetry())
         {

            SetRetryClientConnect();

         }
         else
         {

            SetCloseAndDelete(true);

            /// \todo state reason why connect failed
            OnConnectFailed();

         }

      }
      else
      {

         SetCloseAndDelete(true);
         /// \todo state reason why connect failed
         OnConnectFailed();

      }

      set_connecting(false);

   }


#ifdef _WIN32


   void tcp_socket::OnException()
   {

      m_ptcpsocketInterface->OnException();

      if (is_connecting())
      {

         int iError = ::pointer < ::sockets_bsd::socket_handler >(socket_handler())->m_iSelectErrno;

         if (iError == ETIMEDOUT)
         {

            m_estatus = error_connection_timed_out;

         }
         else
         {
            //m_estatus = status_failed;
         }

         int iGetConnectionRetry = GetMaximumConnectionRetryCount();

         int iGetConnectionRetries = GetConnectionRetryCount();

         if (Socks4())
         {

            OnSocks4ConnectFailed();

         }
         else if (iGetConnectionRetry == -1 ||
            (iGetConnectionRetry &&
               iGetConnectionRetries < iGetConnectionRetry))
         {

            const int nBufSize = 1024;

            char buf[nBufSize];

            SOCKET iGetSocket = GetSocketId();

            int n = ::recv(iGetSocket, (char*)buf, (int)nBufSize, MSG_OOB);

            information() << "got " << n << " bytes of Out of Band Data";

            // even though the connection failed at once, only retry after
            // the connection timeout
            // should we even try to connect again, when CheckConnect returns
            // false it's because of a connection error - not a timeout...
         }
         else
         {
            set_connecting(false); // tnx snibbe
            SetCloseAndDelete();
            OnConnectFailed();
         }
         return;
      }
      // %! exception doesn't always mean something bad happened, this code should be reworked
      // errno valid here?
      int err = SoError();

      fatal() << "exception on select " << err << bsd_socket_error(err);

      SetCloseAndDelete();
   }


#endif // _WIN32


   int tcp_socket::protocol()
   {

      return m_ptcpsocketInterface->protocol();

   }


   void tcp_socket::SetTransferLimit(memsize sz)
   {

      //m_transfer_limit = sz;

      m_ptcpsocketInterface->SetTransferLimit(sz);

   }


   void tcp_socket::OnTransferLimit()
   {

      m_ptcpsocketInterface->OnTransferLimit();

   }


   string tcp_socket::get_url()
   {

      return m_strUrl;

   }


   string tcp_socket::get_short_description()
   {

      return get_url();

   }


   long tcp_socket::cert_common_name_check(const ::string& common_name)
   {

      if (!m_bCertCommonNameCheckEnabled)
      {

         return X509_V_OK;

      }

      ::X509* cert = nullptr;

      ::X509_name_st* topic = nullptr;

#if OPENSSL_VERSION_NUMBER >= 0x30000000L

      cert = SSL_get1_peer_certificate(m_psslcontext->m_ssl);

#else

      cert = SSL_get_peer_certificate(m_psslcontext->m_ssl);

#endif

      bool ok = false;

      if (cert != nullptr && ansi_len(common_name) > 0)
      {

         char data[256];

         if ((topic = X509_get_subject_name(cert)) != nullptr && X509_NAME_get_text_by_NID(topic, NID_commonName, data, 256) > 0)
         {

            data[255] = 0;

            if (case_insensitive_ansi_count_compare(data, common_name, 255) == 0)
            {

               ok = true;

            }
            else
            {

               string str = data;

               if (str.begins_eat("*."))
               {

                  string strCommon = common_name;

                  if (strCommon == str)
                  {

                     ok = true;

                  }
                  else
                  {

                     auto pFind = strCommon.find('.');

                     if (::is_set(pFind))
                     {

                        if (str == strCommon(pFind + 1))
                        {

                           ok = true;

                        }

                     }

                  }

               }

            }

         }

         if (!ok)
         {

            int i;

            int san_names_nb = -1;

            STACK_OF(GENERAL_NAME)* san_names = nullptr;

            // Try to extract the names within the SAN extension from the certificate
            san_names = (STACK_OF(GENERAL_NAME)*) X509_get_ext_d2i((X509*)cert, NID_subject_alt_name, nullptr, nullptr);

            if (san_names == nullptr)
            {

            }
            else
            {

               san_names_nb = sk_GENERAL_NAME_num(san_names);

               // Check each name within the extension
               for (i = 0; i < san_names_nb; i++)
               {

                  const GENERAL_NAME* current_name = sk_GENERAL_NAME_value(san_names, i);

                  if (current_name->type == GEN_DNS)
                  {
                     // Current name is a DNS name, let's check it

#if (defined(LINUX)) && (OPENSSL_API_COMPAT < 0x10100000L)

                     string strDnsName((const_char_pointer )ASN1_STRING_data(current_name->d.dNSName), ASN1_STRING_length(current_name->d.dNSName));

#else

                     string strDnsName((const_char_pointer )ASN1_STRING_get0_data(current_name->d.dNSName), ASN1_STRING_length(current_name->d.dNSName));

#endif

                     if (strDnsName.case_insensitive_order(common_name) == 0)
                     {

                        ok = true;

                        break;

                     }
                     else
                     {

                        string str = strDnsName;

                        if (str.begins_eat("*."))
                        {

                           string strCommon = common_name;

                           if (strCommon == str)
                           {

                              ok = true;

                              break;

                           }
                           else
                           {

                              auto pFind = strCommon.find('.');

                              if (::is_set(pFind))

                              {
                                 if (str == strCommon(pFind + 1))
                                 {

                                    ok = true;

                                    break;

                                 }

                              }

                           }

                        }

                     }

                  }

               }

               sk_GENERAL_NAME_pop_free(san_names, GENERAL_NAME_free);

            }

         }

      }

      if (cert)
      {

         X509_free(cert);

      }

      if (ok)
      {

         return SSL_get_verify_result(m_psslcontext->m_ssl);

      }

      return X509_V_ERR_APPLICATION_VERIFICATION;

   }


   void tcp_socket::enable_cert_common_name_check(bool bEnable)
   {

      m_bCertCommonNameCheckEnabled = bEnable;

   }


   string tcp_socket::get_connect_host()
   {

      return m_strConnectHost;

   }


   ::networking::port_t tcp_socket::get_connect_port()
   {

      return m_iConnectPort;

   }


   void tcp_socket::InitializeContextTLSClientMethod()
   {

#if defined(HAVE_OPENSSL)

      InitializeContext("", TLS_client_method());

#endif

   }


   void tcp_socket::destroy()
   {

      m_ticketkeya.clear();
      m_ibuf.clear();
      m_pmutexSslCtx.release();
      m_obuf_top.release();

      ::sockets_bsd::stream_socket::destroy();

      ::sockets::tcp_socket::destroy();

   }


   void tcp_socket::on_set_parent_socket()
   {

      base_socket_interface()->on_set_parent_socket();

   }


} // namespace sockets_bsd

