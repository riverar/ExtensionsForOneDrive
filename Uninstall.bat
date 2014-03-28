REM This is temporary.
CLS

SET PATH=%PATH%;%SystemRoot%\Microsoft.NET\Framework\v4.0.30319

regsvr32 /u /s "%~dp0\ExtensionsForOneDrive.Shell.dll"
reg delete /f HKCU\Software\Rafael\ExtensionsForOneDrive

ngen uninstall "%~dp0\ExtensionsForOneDrive.Service.exe" /silent
ngen uninstall "%~dp0\GalaSoft.MvvmLight.Extras.WPF45.dll" /silent
ngen uninstall "%~dp0\GalaSoft.MvvmLight.WPF45.dll" /silent
ngen uninstall "%~dp0\Microsoft.Live.dll" /silent
ngen uninstall "%~dp0\Microsoft.Practices.ServiceLocation.dll" /silent

pause