 @echo off
 for /f "usebackq tokens=3" %%i in (`findstr REV patchlevel.h`) do set TCSH_REV=%%i
 for /f "usebackq tokens=3" %%j in (`findstr VERS patchlevel.h`) do set TCSH_VERS=%%j
 for /f "usebackq tokens=3" %%k in (`findstr PATCHLEVEL patchlevel.h`) do set TCSH_PATCHLEVEL=%%k

 for /f "tokens=*" %%l in (win32\manifest.template) do (
	 if %%l==version="1.2.3.4" (
	   echo version="0.%TCSH_REV%.%TCSH_VERS%.%TCSH_PATCHLEVEL%"
	   ) else (
		 if %%l==processorArchitecture="x86" (
		   echo processorArchitecture="%PROCESSOR_ARCHITECTURE%" 
		 ) else (
		   echo %%l
		 )
	   )
	 )
