@echo off

@cd %~dp0

@dir *.png /b > png.txt

@for /f "tokens=*" %%m in (png.txt) do "c:/FE-Tools/EventAssembler/Tools/Png2Dmp" %%m

@del png.txt

echo Done!

pause