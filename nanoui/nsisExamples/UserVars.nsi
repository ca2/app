; UserVars.nsi
;
; This script shows you how to declare and user variables.

;--------------------------------

  Name "User Variables Text"
  OutFile "UserVars.exe"
  
  InstallDir "$PROGRAMFILES\User Variables Test"
  
  RequestExecutionLevel admin
  
;--------------------------------

  ;Pages
  Page directory
  Page instfiles
  
  UninstPage uninstConfirm
  UninstPage instfiles

;--------------------------------
; Declaration of user variables (Var command), allowed charaters for variables names : [a-z][A-Z][0-9] and '_'

  Var "Name"
  Var "serial"
  Var "Info"

;--------------------------------
; Installer

Section "Dummy Section" SecDummy

     StrCpy $0 "Admin"
     StrCpy "$Name" $0
     StrCpy "$serial" "12345"
     MessageBox e_message_box_ok "User Name: $Name $\n$\nSerial Number: $serial"

     CreateDirectory $INSTDIR
     WriteUninstaller "$INSTDIR\Uninst.exe"
     
SectionEnd

Section "Another Section"

     Var /GLOBAL "AnotherVar"

     StrCpy $AnotherVar "test"

SectionEnd

;--------------------------------
; Uninstaller

Section "Uninstall"

     StrCpy $Info "User variables test uninstalled successfully."
     Delete "$INSTDIR\Uninst.exe"
     RmDir $INSTDIR

SectionEnd

Function un.OnUninstSuccess

     HideWindow
     MessageBox e_message_box_ok "$Info"
     
FunctionEnd
