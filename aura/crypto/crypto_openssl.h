#pragma once


#include <openssl/md5.h>
#include <openssl/whrlpool.h>


namespace str
{


    CLASS_DECL_AURA void from(string & str, const MD5_CTX & ctx);

    CLASS_DECL_AURA void from(string & str, const WHIRLPOOL_CTX & ctx);


} // namespace str



