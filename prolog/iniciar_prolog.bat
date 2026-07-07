@echo off
setlocal
cd /d "%~dp0"
start "SWI-Prolog" "C:\Program Files\swipl\bin\swipl.exe" -g "consult('swish.pl')."
