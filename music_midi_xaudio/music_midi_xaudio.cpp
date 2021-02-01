#include "framework.h"


namespace music
{


   namespace midi_mmsystem
   {


      u32 const DefaultTempo = 500000L;

      const u32 grbChanMsgLen[] =
      {
         0,                      /* 0x   not a status byte   */
         0,                      /* 1x   not a status byte   */
         0,                      /* 2x   not a status byte   */
         0,                      /* 3x   not a status byte   */
         0,                      /* 4x   not a status byte   */
         0,                      /* 5x   not a status byte   */
         0,                      /* 6x   not a status byte   */
         0,                      /* 7x   not a status byte   */
         3,                      /* 8x   Note off            */
         3,                      /* 9x   Note on             */
         3,                      /* Ax   Poly pressure       */
         3,                      /* Bx   control change      */
         2,                      /* Cx   Program change      */
         2,                      /* Dx   Chan pressure       */
         3,                      /* Ex   Pitch bend change   */
         0,                      /* Fx   SysEx (see below)   */
      } ;



      const char pitchText[][5]
      =
      {
         "C-2",
         "C#-2",
         "D-2",
         "D#-2",
         "E-2",
         "F-2",
         "F#-2",
         "G-2",
         "G#-2",
         "A-2",
         "A#-2",
         "B-2",

         "C-1",
         "C#-1",
         "D-1",
         "D#-1",
         "E-1",
         "F-1",
         "F#-1",
         "G-1",
         "G#-1",
         "A-1",
         "A#-1",
         "B-1",

         "C0",
         "C#0",
         "D0",
         "D#0",
         "E0",
         "F0",
         "F#0",
         "G0",
         "G#0",
         "A0",
         "A#0",
         "B0",

         "C1",
         "C#1",
         "D1",
         "D#1",
         "E1",
         "F1",
         "F#1",
         "G1",
         "G#1",
         "A1",
         "A#1",
         "B1",

         "C2",
         "C#2",
         "D2",
         "D#2",
         "E2",
         "F2",
         "F#2",
         "G2",
         "G#2",
         "A2",
         "A#2",
         "B2",

         "C3",
         "C#3",
         "D3",
         "D#3",
         "E3",
         "F3",
         "F#3",
         "G3",
         "G#3",
         "A3",
         "A#3",
         "B3",

         "C4",
         "C#4",
         "D4",
         "D#4",
         "E4",
         "F4",
         "F#4",
         "G4",
         "G#4",
         "A4",
         "A#4",
         "B4",

         "C5",
         "C#5",
         "D5",
         "D#5",
         "E5",
         "F5",
         "F#5",
         "G5",
         "G#5",
         "A5",
         "A#5",
         "B5",

         "C6",
         "C#6",
         "D6",
         "D#6",
         "E6",
         "F6",
         "F#6",
         "G6",
         "G#6",
         "A6",
         "A#6",
         "B6",

         "C7",
         "C#7",
         "D7",
         "D#7",
         "E7",
         "F7",
         "F#7",
         "G7",
         "G#7",
         "A7",
         "A#7",
         "B7",

         "C8",
         "C#8",
         "D8",
         "D#8",
         "E8",
         "F8",
         "F#8",
         "G8"
      };


      /*const u32 voiceText[]
      =
      {
      IDS_VOICE_1   ,
      IDS_VOICE_2   ,
      IDS_VOICE_3   ,
      IDS_VOICE_4   ,
      IDS_VOICE_5   ,
      IDS_VOICE_6   ,
      IDS_VOICE_7   ,
      IDS_VOICE_8   ,
      IDS_VOICE_9   ,
      IDS_VOICE_10   ,
      IDS_VOICE_11   ,
      IDS_VOICE_12   ,
      IDS_VOICE_13   ,
      IDS_VOICE_14   ,
      IDS_VOICE_15   ,
      IDS_VOICE_16   ,
      IDS_VOICE_17   ,
      IDS_VOICE_18   ,
      IDS_VOICE_19   ,
      IDS_VOICE_20   ,
      IDS_VOICE_21   ,
      IDS_VOICE_22   ,
      IDS_VOICE_23   ,
      IDS_VOICE_24   ,
      IDS_VOICE_25   ,
      IDS_VOICE_26   ,
      IDS_VOICE_27   ,
      IDS_VOICE_28   ,
      IDS_VOICE_29   ,
      IDS_VOICE_30   ,
      IDS_VOICE_31   ,
      IDS_VOICE_32   ,
      IDS_VOICE_33   ,
      IDS_VOICE_34   ,
      IDS_VOICE_35   ,
      IDS_VOICE_36   ,
      IDS_VOICE_37   ,
      IDS_VOICE_38   ,
      IDS_VOICE_39   ,
      IDS_VOICE_40   ,
      IDS_VOICE_41   ,
      IDS_VOICE_42   ,
      IDS_VOICE_43   ,
      IDS_VOICE_44   ,
      IDS_VOICE_45   ,
      IDS_VOICE_46   ,
      IDS_VOICE_47   ,
      IDS_VOICE_48   ,
      IDS_VOICE_49   ,
      IDS_VOICE_50   ,
      IDS_VOICE_51   ,
      IDS_VOICE_52   ,
      IDS_VOICE_53   ,
      IDS_VOICE_54   ,
      IDS_VOICE_55   ,
      IDS_VOICE_56   ,
      IDS_VOICE_57   ,
      IDS_VOICE_58   ,
      IDS_VOICE_59   ,
      IDS_VOICE_60   ,
      IDS_VOICE_61   ,
      IDS_VOICE_62   ,
      IDS_VOICE_63   ,
      IDS_VOICE_64   ,
      IDS_VOICE_65   ,
      IDS_VOICE_66   ,
      IDS_VOICE_67   ,
      IDS_VOICE_68   ,
      IDS_VOICE_69   ,
      IDS_VOICE_70   ,
      IDS_VOICE_71   ,
      IDS_VOICE_72   ,
      IDS_VOICE_73   ,
      IDS_VOICE_74   ,
      IDS_VOICE_75   ,
      IDS_VOICE_76   ,
      IDS_VOICE_77   ,
      IDS_VOICE_78   ,
      IDS_VOICE_79   ,
      IDS_VOICE_80   ,
      IDS_VOICE_81   ,
      IDS_VOICE_82   ,
      IDS_VOICE_83   ,
      IDS_VOICE_84   ,
      IDS_VOICE_85   ,
      IDS_VOICE_86   ,
      IDS_VOICE_87   ,
      IDS_VOICE_88   ,
      IDS_VOICE_89   ,
      IDS_VOICE_90   ,
      IDS_VOICE_91   ,
      IDS_VOICE_92   ,
      IDS_VOICE_93   ,
      IDS_VOICE_94   ,
      IDS_VOICE_95   ,
      IDS_VOICE_96   ,
      IDS_VOICE_97   ,
      IDS_VOICE_98   ,
      IDS_VOICE_99   ,
      IDS_VOICE_100   ,
      IDS_VOICE_101   ,
      IDS_VOICE_102   ,
      IDS_VOICE_103   ,
      IDS_VOICE_104   ,
      IDS_VOICE_105   ,
      IDS_VOICE_106   ,
      IDS_VOICE_107   ,
      IDS_VOICE_108   ,
      IDS_VOICE_109   ,
      IDS_VOICE_110   ,
      IDS_VOICE_111   ,
      IDS_VOICE_112   ,
      IDS_VOICE_113   ,
      IDS_VOICE_114   ,
      IDS_VOICE_115   ,
      IDS_VOICE_116   ,
      IDS_VOICE_117   ,
      IDS_VOICE_118   ,
      IDS_VOICE_119   ,
      IDS_VOICE_120   ,
      IDS_VOICE_121   ,
      IDS_VOICE_122   ,
      IDS_VOICE_123   ,
      IDS_VOICE_124   ,
      IDS_VOICE_125   ,
      IDS_VOICE_126   ,
      IDS_VOICE_127   ,

      };
      */

      double GetNoteFrequency(double dA3Frequency, byte bNote)
      {

         return dA3Frequency * pow(2.0, (double) (bNote - 69) / 12);

      }

      ::e_status     FillTypeCombo(__pointer(simple_combo_box)lpcombo)
      {
         UNREFERENCED_PARAMETER(lpcombo);
         /*   lpcombo->ResetContent();

         string str;
         str.load_string(IDS_MIDI_NOTEOFF);
         i32 iItem = lpcombo->AddString(str);
         lpcombo->SetItemData(iItem, NoteOff);

         str.load_string(IDS_MIDI_NOTEON);
         iItem = lpcombo->AddString(str);
         lpcombo->SetItemData(iItem, NoteOn);

         //    string str;
         //  str.load_string(IDS_MIDI_KEYPRESSURE);
         //lpcombo->AddString(str);
         //lpcombo->SetItemData(lpcombo->get_count() - 1, K);
         str.load_string(IDS_MIDI_CONTROLCHANGE);
         iItem = lpcombo->AddString(str);
         lpcombo->SetItemData(iItem, control_change);

         str.load_string(IDS_MIDI_PROGRAMCHANGE);
         iItem = lpcombo->AddString(str);
         lpcombo->SetItemData(iItem, ProgramChange);*/

         return ::success;
      }

      ::e_status     FillPitchCombo(__pointer(simple_combo_box)lpcombo)
      {
         UNREFERENCED_PARAMETER(lpcombo);
         /*    lpcombo->ResetContent();

         for(i32 i = 0; i < 128; i++)
         {
         i32 iItem = lpcombo->AddString(pitchText[i]);
         lpcombo->SetItemData(iItem, i);
         }
         */
         return ::success;
      }


      i32 GetMessageLen(byte bEvent)
      {
         return grbChanMsgLen[(bEvent >> 4) & 0x0F];
      }

      // returns the midi stream ::payload dword
      u32 GetVDWord(byte * &hpbMidiStream, u32 dwLeft, u32 &dwValueParam)
      {

         byte                    b;
         u32                   dwUsed  = 0;
         byte * &            hpbImage = hpbMidiStream;
         u32               dwValue;

         ASSERT(hpbImage != nullptr);

         dwValue = 0;

         do
         {
            if (!dwLeft)
            {
               return 0;
            }

            b = *hpbImage++;
            dwLeft--;
            dwUsed++;

            dwValue = (dwValue << 7) | (b & 0x7F);
         }
         while (b&0x80);

         dwValueParam = dwValue;

         return dwUsed;

      }



      /******************************************************************************
      *
      * smfGetStateMaxSize
      *
      * This function returns the maximum sizeof buffer that is needed to
      * hold the state information returned by f smfSeek.
      *
      * pdwSize                   - Gets the size_i32 in bytes that should be allocated
      *                             for the state buffer.
      *
      * Returns the state size_i32 in bytes.
      *
      *****************************************************************************/
      u32 GetStateMaxSize(
      VOID)
      {
         return  3*sizeof(u32) +           /* Tempo                */
                 3*16*sizeof(u32) +        /* Patch changes        */
                 3*16*120*sizeof(u32) +    /* Controller changes   */
                 3*sizeof(u32);            /* time alignment NOP   */
      }


   } // namespace midi_mmsystem


} // namespace music









