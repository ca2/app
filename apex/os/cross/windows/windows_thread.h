//
//  windows_thread.h
//  apex
//
//  Created by Camilo Sasuke Tsumanuma on 16/09/20.
//  Copyright © 2020 Camilo Sasuke Tsumanuma. All rights reserved.
//
#pragma once


CLASS_DECL_ACME ::u32 WINAPI ResumeThread(HTHREAD hThread);
CLASS_DECL_ACME int_bool WINAPI SetThreadPriority(HTHREAD hThread, i32 nPriority);
CLASS_DECL_ACME i32 WINAPI GetThreadPriority(HTHREAD hThread);



