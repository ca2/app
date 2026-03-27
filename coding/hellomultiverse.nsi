; example2.nsi
;
; This script is based on example1.nsi, but it remember the directory, 
; has uninstall support and (optionally) installs start menu shortcuts.
;
; It will install example2.nsi into a directory that the user selects,

;--------------------------------

; The name of the installer
Name "Hello Multiverse!!"

; The default installation directory
InstallDir "$PROGRAMFILES\app_core_build"

; The file to write
OutFile "C:\ca2\time\HelloMultiverseInstaller.exe"


; Registry key to check for directory (so if you install again, it will 
; overwrite the old one automatically)
InstallDirRegKey HKLM "Software\ca2\app-core\hellomultiverse" "Install_Dir"

; Request application privileges for Windows Vista
RequestExecutionLevel admin

;--------------------------------

; Pages

Page directory
Page instfiles

UninstPage uninstConfirm
UninstPage instfiles

;--------------------------------

; The stuff to install
Section "HelloMultiverse (required)"

  SectionIn RO

  ; Set output path to the installation directory.
  SetOutPath "$INSTDIR\app\appmatter\main"
  
  ; Put file there
  File /r "C:\ca2\app\appmatter\main\"
  
  ; Set output path to the installation directory.
  SetOutPath "$INSTDIR\app-core\appmatter\hellomultiverse"
  
  ; Put file there
  File /r "C:\ca2\app-core\appmatter\hellomultiverse\"

  ; Set output path to the installation directory.
  SetOutPath "$INSTDIR\time\x64\stage"
  
  ; Put file there
  File "C:\ca2\time\x64\stage\ace.dll"
  File "C:\ca2\time\x64\stage\aqua.dll"
  File "C:\ca2\time\x64\stage\aura.dll"
  File "C:\ca2\time\x64\stage\axis.dll"
  File "C:\ca2\time\x64\stage\base.dll"
  File "C:\ca2\time\x64\stage\aura.dll"
  File "C:\ca2\time\x64\stage\draw2d_gdiplus.dll"
  File "C:\ca2\time\x64\stage\experience_lite.dll"
  File "C:\ca2\time\x64\stage\axisfreeimage.dll"
  File "C:\ca2\time\x64\stage\image_decode_png.dll"
  File "C:\ca2\time\x64\stage\image_decode_jpeg.dll"
  File "C:\ca2\time\x64\stage\gcom.dll"
  File "C:\ca2\time\x64\stage\png.dll"
  File "C:\ca2\time\x64\stage\jpeg.dll"
  File "C:\ca2\time\x64\stage\libcrypto-1_1-x64.dll"
  File "C:\ca2\time\x64\stage\libssl-1_1-x64.dll"
  File "C:\ca2\time\x64\stage\pcre.dll"
  File "C:\ca2\time\x64\stage\sqlite.dll"
  File "C:\ca2\time\x64\stage\zlib.dll"
  File "C:\ca2\time\x64\stage\bzip2.dll"
  File "C:\ca2\time\x64\stage\app_core.dll"
  File "C:\ca2\time\x64\stage\app_core_build.dll"
  File "C:\ca2\time\x64\stage\app_core_build.exe"
  
  
  ExecWait '"$INSTDIR\time\x64\stage\app_core_build.exe" : install' $0
  
  ; Write the installation path into the registry
  WriteRegStr HKLM "SOFTWARE\ca2\app-core\hellomultiverse" "Install_Dir" "$INSTDIR"
  
  ; Write the uninstall keys for Windows
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\app_core_build" "DisplayName" "Hello Multiverse!!"
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\app_core_build" "UninstallString" '"$INSTDIR\uninstall.exe"'
  WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\app_core_build" "NoModify" 1
  WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\app_core_build" "NoRepair" 1
  WriteUninstaller "uninstall.exe"
  
SectionEnd

; Optional section (can be disabled by the user)
Section "Start Menu Shortcuts"

  CreateDirectory "$SMPROGRAMS\Hello Multiverse!!"
  CreateShortcut "$SMPROGRAMS\Hello Multiverse!!\Uninstall.lnk" "$INSTDIR\uninstall.exe" "" "$INSTDIR\uninstall.exe" 0
  CreateShortcut "$SMPROGRAMS\Hello Multiverse!!\Hello Multiverse!!.lnk" "$INSTDIR\time\x64\stage\app_core_build.exe" "" "$INSTDIR\time\x64\stage\app_core_build.exe" 0
  
SectionEnd

;--------------------------------

; Uninstaller

Section "Uninstall"
  
  ; Remove registry keys
  DeleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\app_core_build"
  DeleteRegKey HKLM "SOFTWARE\ca2\app-core\hellomultiverse"

  ; Remove files and uninstaller
  Delete "$INSTDIR\app_core_build.nsi"
  Delete "$INSTDIR\uninstall.exe"

  ; Remove shortcuts, if any
  Delete "$SMPROGRAMS\app_core_build\*.*"

  ; Remove directories used
  RMDir "$SMPROGRAMS\app_core_build"
  RMDir /r "$INSTDIR/time"
  RMDir "$INSTDIR"

SectionEnd
