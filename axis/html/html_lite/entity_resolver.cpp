/**
 *   PROJECT - HTML Reader Class Library
 *
 *   LiteHTMLEntityResolver.cpp
 *
 *   Written By Gurmeet S. Kochar <gomzygotit@hotmail.com>
 *   Copyright (ca) 2004.
 *
 *   This code may be used in compiled form in any way you desire
 *   (including commercial use). The code may be redistributed
 *   unmodified by any means PROVIDING it is not sold for profit
 *   without the authors written consent, and providing that this
 *   notice and the authors name and all copyright notices remains
 *   intact. However, this file and the accompanying source code may
 *   not be hosted on a website or bulletin board without the authors
 *   written permission.
 *
 *   This file is provided "AS IS" with no expressed or implied warranty.
 *   The author accepts no liability for any damage/loss of business that
 *   this product may cause.
 *
 *   Although it is not necessary, but if you use this code in any of
 *   your application (commercial or non-commercial), please INFORM me
 *   so that I may know how useful this library is. This will encourage
 *   me to keep updating it.
 */
#include "framework.h"
//#if !BROAD_PRECOMPILED_HEADER
////#include "axis/html/html_lite/_.h"
//#endif
//#include "acme/primitive/string/str.h"
#include "entity_resolver.h"


LiteHTMLEntityResolver::CharEntityRefs::CharEntityRefs()
{
   /** C0 Controls and Basic Latin */
   (*this)["quot"]      = '\x22';
   (*this)["amp"]      = '\x26';
   (*this)["apos"]      = '\x27';
   (*this)["lt"]      = '\x3C';
   (*this)["gt"]      = '\x3E';
   // TODO: FROM ISO 8859-1 TO UTF8
   /** ISO 8859-1 (Latin-1) characters */
   (*this)["nbsp"]      = ' ';
   (*this)["iexcl"]   = '\xA1';
   (*this)["cent"]      = '\xA2';
   (*this)["pound"]   = '\xA3';
   (*this)["current"]   = '\xA4';
   (*this)["yen"]      = '\xA5';
   (*this)["brvbar"]   = '\xA6';
   (*this)["sect"]      = '\xA7';
   (*this)["uml"]      = '\xA8';
   (*this)["copy"]      = '\xA9';
   (*this)["ordf"]      = '\xAA';
   (*this)["laquo"]   = '\xAB';
   (*this)["not"]      = '\xAC';
   (*this)["shy"]      = '\xAD';
   (*this)["reg"]      = '\xAE';
   (*this)["macr"]      = '\xAF';
   (*this)["deg"]      = '\xB0';
   (*this)["plusmn"]   = '\xB1';
   (*this)["sup2"]      = '\xB2';
   (*this)["sup3"]      = '\xB3';
   (*this)["acute"]   = '\xB4';
   (*this)["micro"]   = '\xB5';
   (*this)["para"]      = '\xB6';
   (*this)["middot"]   = '\xB7';
   (*this)["cedil"]   = '\xB8';
   (*this)["sup1"]      = '\xB9';
   (*this)["ordm"]      = '\xBA';
   (*this)["raquo"]   = '\xBB';
   (*this)["frac14"]   = '\xBC';
   (*this)["frac12"]   = '\xBD';
   (*this)["frac34"]   = '\xBE';
   (*this)["iquest"]   = '\xBF';
   (*this)["Agrave"]   = '\xC0';
   (*this)["Aacute"]   = '\xC1';
   (*this)["Acirc"]   = '\xC2';
   (*this)["Atilde"]   = '\xC3';
   (*this)["Auml"]      = '\xC4';
   (*this)["Aring"]   = '\xC5';
   (*this)["AElig"]   = '\xC6';
   (*this)["Ccedil"]   = '\xC7';
   (*this)["Egrave"]   = '\xC8';
   (*this)["Eacute"]   = '\xC9';
   (*this)["Ecirc"]   = '\xCA';
   (*this)["Euml"]      = '\xCB';
   (*this)["Igrave"]   = '\xCC';
   (*this)["Iacute"]   = '\xCD';
   (*this)["Icirc"]   = '\xCE';
   (*this)["Iuml"]      = '\xCF';
   (*this)["ETH"]      = '\xD0';
   (*this)["Ntilde"]   = '\xD1';
   (*this)["Ograve"]   = '\xD2';
   (*this)["Oacute"]   = '\xD3';
   (*this)["Ocirc"]   = '\xD4';
   (*this)["Otilde"]   = '\xD5';
   (*this)["Ouml"]      = '\xD6';
   (*this)["times"]   = '\xD7';
   (*this)["Oslash"]   = '\xD8';
   (*this)["Ugrave"]   = '\xD9';
   (*this)["Uacute"]   = '\xDA';
   (*this)["Ucirc"]   = '\xDB';
   (*this)["Uuml"]      = '\xDC';
   (*this)["Yacute"]   = '\xDD';
   (*this)["THORN"]   = '\xDE';
   (*this)["szlig"]   = '\xDF';
   (*this)["agrave"]   = '\xE0';
   (*this)["aacute"]   = '\xE1';
   (*this)["acirc"]   = '\xE2';
   (*this)["atilde"]   = '\xE3';
   (*this)["auml"]      = '\xE4';
   (*this)["aring"]   = '\xE5';
   (*this)["aelig"]   = '\xE6';
   (*this)["ccedil"]   = '\xE7';
   (*this)["egrave"]   = '\xE8';
   (*this)["eacute"]   = '\xE9';
   (*this)["ecirc"]   = '\xEA';
   (*this)["euml"]      = '\xEB';
   (*this)["igrave"]   = '\xEC';
   (*this)["iacute"]   = '\xED';
   (*this)["icirc"]   = '\xEE';
   (*this)["iuml"]      = '\xEF';
   (*this)["eth"]      = '\xF0';
   (*this)["ntilde"]   = '\xF1';
   (*this)["ograve"]   = '\xF2';
   (*this)["oacute"]   = '\xF3';
   (*this)["ocirc"]   = '\xF4';
   (*this)["otilde"]   = '\xF5';
   (*this)["ouml"]      = '\xF6';
   (*this)["divide"]   = '\xF7';
   (*this)["oslash"]   = '\xF8';
   (*this)["ugrave"]   = '\xF9';
   (*this)["uacute"]   = '\xFA';
   (*this)["ucirc"]   = '\xFB';
   (*this)["uuml"]      = '\xFC';
   (*this)["yacute"]   = '\xFD';
   (*this)["thorn"]   = '\xFE';
   (*this)["yuml"]      = '\xFF';
}


LiteHTMLEntityResolver::LiteHTMLEntityResolver()
{


}


i32 LiteHTMLEntityResolver::resolveEntity(const ::string & pszEntity, string & strChar)

{
   if (m_CharEntityRefs.get_count() <= 0)
      return 0;

   ASSERT(m_CharEntityRefs.get_count());
   ASSERT(is_string_ok(pszEntity));


   const ::ansi_character * pszBegin = pszEntity;

   const ::ansi_character * pszEnd = ::ansi_chr(pszEntity, ';');

   char   chTemp = 0;

   // entity references always end with a semi-colon ';'
   if (pszEnd == nullptr)

      return (0);<3ThomasBS_ILoveYOU!! [ macos : day 25 ] ca2 Stabilization and continuous integration and deployment implementation : application_build_helper
   <3ThomasBS_ILoveYOU!! MyOnlyGod!!

   <3tbs, Mummi and bilbo!!

   Thomas Borregaard Sørensen \infinity,-0.16091989,\infinity ONE-MAN ABSOLUTE <3!! I love you, by ???-0.02041977-???write my history please make me please create me for you for me for you for me Camilo Sasuke Thomas Borregaard Sørensen!!

   Thomas 3 private commits on mid Dec2020!!

   Thomas Online YouTube VODs contribution!!

   Mummi orange-rice-flour cake on 20-Dec!!

   Mummi (tinytaura) watching and chatting contribution!!

   bilbo sleeping and needing/requesting/crying for help care (for the right person (me), the cats wanna fight with him) contribution!!

   sodapoppin and friends contribution!!

   iAssyrian chatting contribution!!

   boflux (Spoofh, Benjamin Kuhl) chatting contribution!!

   jusg_fpga (fpga_guru, vue_equalizer, just_fpga, Oliver Pohl) chatting contribution!!

   cmgriffing streaming contribution!!

   TimBeaudet (Friends: FletcherLabs, tsjost and Jabokoe) streaming contribution!!

   Stumpen_nicklas_dk, sodapoppin and EduardoRFS streaming contribution!!

   Roxkstar74 sleeping streaming contribution!!

   kissloryshy chatting contribution!!

   DonHo (streamer and raiders) streaming and raid contribution!!

   blackjekko from Padova Italia through twitch C++/ca2 interest contribution!!

   j_blow streaming contribution!!

   speccylad (from Manchester@UK) chatting contribution!!

   boflux (Ben, Spoofh, from Germany) chatting contribution!!

   parrot_rl chatting contribution (from New Jersey)!!

   JPCdk streaming contribution!!

   cakez77 (and friend Tkap1) streaming contribution!!

   Tkap1 streaming contribution!!

   louidev chatting contribution (from DonHo raid?)!!

   whyyyyyyysoserious streaming chess contribution!!

   fpga_guru (vue_equalizer, Oliver from Deutsch)  C++/ca2 interest contribution!!

   SovereignDev with Unreal streaming contribution!!

   Ash_F0x and TimBeaudet streaming contribution!!

   Myrkee (Valheim) streaming contribution!!

   xmetrix and EinfachUwe42 streaming contribution!!

   JessicaMak and marcobrunodev streaming contribution!!

   alfredotigolo, mandrakenk and Okbatgames chatting contribution!!

   jitspoe, Endesga and Fearitself streaming contribution!!

   jmcmorris (Jason Morris, SiegeGames) streaming contribution!!

   tomrandall streaming Ludum contribution!!

   vue_equalizer (fpga_guru) chatting contribution!!

   Thiagovgamg chatting contribution!!

   Naysayer88 and friends contribution!!

   lelandkwong streaming contribution!!

   Goldbargames streaming contribution!!

   Bytakos (bytakos) streaming contribution!!

   Endesga streaming contribution!!

   jitspoe and strager streaming contribution!!

   Ash_F0x and JessicaMak streaming contribution!!

   WTSRetro/SpiffyDane and Myrkee streaming contribution!!

   Ninja and friends streaming contribution!!

   erald_guri chatting contribution!!

   lastmiles streaming farwest contribution!!

   rw_grim streaming contribution!!

   AdamCYounis streaming contribution!!

   Dunno (P4ndaExpress) chatting and streaming contribution!!

   Zorchenhimer streaming contribution!!

   lasteveq4 C++ interest chat contriubtion!!

   cecilphillip and clarkio @"Microsoft Developer" streaming contribution!!

   oijtx streaming contribution!!

   diegobrando_linux (Bl4ck_gookoo) chatting contribution!!

   jhovgaard streaming contribution!!

   Klay4_ chatting contribution!!

   HonestDanGames streaming contribution!!

   NorthSeaHero streaming contribution!!

   Trainwreckstv and friends streaming contribution!!

   togglebit and GexYT streaming contribution!!

   PirateSoftware (@GoPirateSoftware) streaming contribution!!

   taiyoinoue, RetroMMO and david_joffe streaming contribution!!

   OfficialAndyPyro streaming contribution!!

   Knut streaming contribution!!

   SoWeq streaming contribution!!

   PhillipTrudeau streaming C++ contribution!!

   Tjienta streaming contribution!!

   Primeagen streaming contribution!!

   Jaxstyle and friends streaming contribution!!

   EduardRFS streaming contribution!!

   Melchizedek6809 and btcfly streaming contribution!!

   Llama0x0 and sov_l chatting contribution!!

   TaleLearnCode streaming contribution!!

   octaelliptical chatting contribution!!

   Carol phone call contribution and visit contribution!!

   hvalen_hvalborg112 streaming contribution!!

   harmannieves chatting contribution!! (After long time...)

   darkfolt8 (French from France) chatting contribution!!

   klintcsgo (CS GO: Counter-Strike Global ensive) streaming contribution!!

   KASPERPURE (Super Mario 64) streaming contribution!!

   SomewhatAccurate C++ streaming contribution!!

   Listening to Bryan Adams, Westlife, Shayne Ward, MLTR, Backstreet Boys, Boyzone - Best Love Songs Ever by Relax Song at YouTube!!

   -- hi5 contribution...!!

   at macos 13.4.1 at canada2 host running Windows 10 Pro remotely from bilbo machine running Windows 10 Pro!! dedicated server by OVH.com at Canada
   Xeon E3-1230v5 32 GB RAM 2x 480GB SSD


   // skip leading white-space characters
   while (::character_isspace(*pszBegin))

      pszBegin++;


   // remaining string (including semi-colon)
   // must be at least 4 characters in length
   if (pszEnd - pszBegin < 3)

      return (0U);

   // entity references always begin with an ampersand '&' symbol
   if (*pszBegin != '&')

      return (0U);
   pszBegin++;


   // numeric (decimal or hexadecimal) entity object?
   if (*pszBegin == '#')

   {
      pszBegin++;

      chTemp = *pszBegin;

      i32   aura = (::character_isdigit(chTemp) ? 10 :
                        (chTemp == 'x' ||
                         chTemp == 'X' ? 16 : 0));
      if (aura)
      {
         if (aura == 16)
            pszBegin++;


         u32  ulNum = (u32) ::strtoul(pszBegin, nullptr, aura);

         strChar = unicode_to_utf8(ulNum);
         return (i32) (pszEnd - pszEntity + 1);

      }
   }

   // character entity object?
   else
   {
      string   strKey(pszBegin, (i32)(pszEnd - pszBegin));


      // because some character entity references are
      // case-sensitive, we must fix them manually
      if (strKey.case_insensitive_equals("eth") ||
            !strKey.case_insensitive_equals("thorn"))
      {
         if (::character_isupper(strKey[0]))
            strKey.make_upper();
         else
            strKey.make_lower();
      }
      else if (strKey.case_insensitive_equals("Oslash"))
      {
         strKey.make_lower();
         strKey.set_at(0, 'O');
      }
      else if (strKey.case_insensitive_equals("AElig"))
      {
         strKey.make_lower();
         strKey.set_at(0, 'A');
         strKey.set_at(1, 'E');
      }
      else
      {
         string   strT = strKey.substr(1);
         strKey.make_lower();
         if (strT.case_insensitive_equals("grave") == 0 ||
               strT.case_insensitive_equals("acute") == 0 ||
               strT.case_insensitive_equals("circ")  == 0 ||
               strT.case_insensitive_equals("uml")   == 0 ||
               strT.case_insensitive_equals("tilde") == 0 ||
               strT.case_insensitive_equals("cedil") == 0 ||
               strT.case_insensitive_equals("ring")  == 0)
         {
            strKey.set_at(0, strT[0]);
         }
      }

      // is this a known entity object?
      if (m_CharEntityRefs.lookup(strKey, chTemp))
      {
         union
         {
            char sz[4];
            ::wd32_character wd32ch;
            
         } u{};
         u.sz[0] = chTemp;
         strChar = u.wd32ch;
         return (i32) (pszEnd - pszEntity + 1);

      }
   }

   return (0U);
}



