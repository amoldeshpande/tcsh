@echo off
for /f "usebackq tokens=2 delims='" %%i in (`findstr PACKAGE_VERSION= configure`) do set PCKG_VER=%%i
for /f "usebackq tokens=2 delims==" %%i in (`findstr /c:"PACKAGE_DATE=" configure`) do set PCKG_DATE=%%i
for /f "tokens=1-4 delims=." %%i in ("%PCKG_VER%") do (
  set A=%%i 
  set B=%%j 
  set C=%%k 
)
for /f "tokens=* usebackq" %%j IN (`hostname`) do set source=%%j

echo. > patchlevel.h

for /f "tokens=*" %%l in (patchlevel.h.in) do (
	if "'%%l'"=="'#define ORIGIN "@PACKAGE_ORIGIN@"'" (
		echo #define ORIGIN "%source%" >> patchlevel.h
	) else (
	  if "%%l"=="#define REV @PACKAGE_REV@" (
		echo #define REV %A% >> patchlevel.h
	  ) else (
		if "%%l"=="#define VERS @PACKAGE_VERS@" (
			echo #define VERS %B% >> patchlevel.h
		) else (
		  	if "%%l"=="#define PATCHLEVEL @PACKAGE_PATCHLEVEL@" (
			   echo #define PATCHLEVEL %C% >> patchlevel.h
			) else (
			  if "'%%l'"=="'#define DATE "@PACKAGE_DATE@"'" (
			   echo #define DATE "%PCKG_DATE%" >> patchlevel.h
				) else echo %%l >> patchlevel.h
			)
		)
	  )
	)
)
)
