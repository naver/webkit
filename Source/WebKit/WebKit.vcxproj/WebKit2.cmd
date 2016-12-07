@echo off
set WEBKIT_SOURCE=%CD%\..\..
set WEBKIT_LIBRARIES=%CD%\..\..\..\WebKitLibraries\win
set WEBKIT_OUTPUTDIR=%CD%\..\..\..\WebKitBuild
set PATH=%WEBKIT_LIBRARIES%\bin32;%PATH%
start "C:\Program Files (x86)\Microsoft Visual Studio 12.0\Common7\IDE\VCExpress.exe" WebKit.sln
