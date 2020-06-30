@echo off

call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Enterprise\VC\Auxiliary\Build\vcvars64.bat"

setlocal
for /f "delims== tokens=1,2" %%a in ('set') do (
    echo ::set-env name=%%a::%%b
)
endlocal