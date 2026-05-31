//
//  key_happening.h
//  apex
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 2026-05-12 21:22
//  <3ThomasBorregaardSørensen!!
//  Copyright © 2026 ca2 Software Development. All rights reserved.
//
#pragma once


namespace user
{

   DECLARE_ENUMERATION(e_message, enum_message);

struct key_happening
{
   
   ::user::e_message m_emessage;
   ::user::e_key m_euserkey;
   bool m_bDown;
   bool m_bExtendedKey;
   
};

} // namespace user
