REM This is temporary.
CLS

cd build\debug\
rmdir /q /s package
mkdir package
copy *.dll package\
copy *.exe package\
copy ..\..\Install.bat package\
copy ..\..\Uninstall.bat package\
pause