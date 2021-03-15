//
//  real_time_midi.cpp
//  music_midi_core_midi
//
//  Created by Camilo Sasuke Tsumanuma on 20/05/19.
//  Copyright © 2019 ca2 Desenvolvimento de Sofware Ltda. All rights reserved.
//
#include "framework.h"



//namespace music
//{
//
//
//   namespace midi
//   {
//
//
//      namespace core_midi
//      {
//
//
//         midi::midi(::context_object * pcontextobject) :
//         ::object(pobject),
//         department(pobject),
//         ::music::midi::object(pobject),
//         ::music::midi::midi(pobject)
//         {
//
//
//         }
//
//
//         midi::~midi()
//         {
//
//         }
//
//
//         __pointer(message_out) midi::get_message_out(index iPort)
//         {
//
//            auto & pmessageout = m_mapMessageOut[iPort];
//
//            if(!pmessageout)
//            {
//
//               pmessageout = __new(message_out(this, iPort));
//
//            }
//
//            return pmessageout;
//
//         }
//
//
//         bool midi::Initialize()
//         {
//
//            if(!::music::midi::midi::Initialize())
//            {
//
//               return false;
//
//            }
//
//
//            return true;
//
//         }
//
//
//         void midi::enumerate_midi_out_devices()
//         {
//
////            m_iPortStart = varaDevice.get_size();
//
//            m_cPortCount = MIDIGetNumberOfDestinations();
//
//            for(index iDestination = 0; iDestination < m_cPortCount; iDestination++)
//            {
//
//               char name[2048];
//
//               MIDIEndpointRef endpoint = MIDIGetDestination(iDestination);
//
//               CFStringRef nameRef = ::music::midi::core_midi::ConnectedEndpointName(endpoint);
//
//               CFStringGetCString(nameRef, name, sizeof(name), CFStringGetSystemEncoding());
//
//               CFRelease(nameRef);
//
//               string strName = name;
//
//               add_midi_out_device(strName + " (core_midi)", m_strName);
//
//            }
//
//         }
//
//
//         __pointer(::music::midi::sequencer) midi::create_midi_sequencer(::music::midi::sequence * psequence, const string& strDevice)
//         {
//
//
//             return __news(sequencer(psequence, strDevice));
//
//
//         }
//
//      } // namespace core_midi
//
//
//   } // namespace midi
//
//   
//} // namespace music


::music::midi::midi * music_midi_core_midi_new_midi()
{
   
   return new ::music::midi::core_midi::midi();
   
}



