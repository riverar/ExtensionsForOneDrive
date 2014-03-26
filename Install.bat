REM This is temporary.
CLS

SET PATH=%PATH%;%SystemRoot%\Microsoft.NET\Framework\v4.0.30319

regsvr32 /s "%~dp0\ExtensionsForOneDrive.Shell.dll"
ngen install "%~dp0\ExtensionsForOneDrive.Service.exe" /silent
ngen install "%~dp0\GalaSoft.MvvmLight.Extras.WPF45.dll" /silent
ngen install "%~dp0\GalaSoft.MvvmLight.WPF45.dll" /silent
ngen install "%~dp0\Microsoft.Live.dll" /silent
ngen install "%~dp0\Microsoft.Practices.ServiceLocation.dll" /silent
ngen install "%~dp0\System.Windows.Interactivity.dll" /silent

pause