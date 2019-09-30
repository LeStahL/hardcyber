REM Hardcyber - PC-64k-Intro by Team210 at Deadline 2k19
REM Copyright (C) 2019 Alexander Kraus <nr4@z10.info>
REM Copyright (C) 2019 DaDummy <c.anselm@paindevs.com>
REM 
REM This program is free software: you can redistribute it and/or modify
REM it under the terms of the GNU General Public License as published by
REM the Free Software Foundation, either version 3 of the License, or
REM (at your option) any later version.
REM 
REM This program is distributed in the hope that it will be useful,
REM but WITHOUT ANY WARRANTY; without even the implied warranty of
REM MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
REM GNU General Public License for more details.
REM 
REM You should have received a copy of the GNU General Public License
REM along with this program.  If not, see <https://www.gnu.org/licenses/>.

cl fconv.c /out:fconv.obj /I"C:\Program Files (x86)\Windows Kits\10\Include\10.0.16299.0\um" /I"C:\Program Files (x86)\Windows Kits\10\Include\10.0.16299.0\shared" /I"C:\Program Files (x86)\Windows Kits\10\Include\10.0.16299.0\ucrt" /I"C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Tools\MSVC\14.13.26128\include" /I".." /DWIN32 /c /Gy /O1 /fp:fast /GR- /GS- /MT

crinkler.exe fconv.obj /out:fconv.exe /ENTRY:demo /SUBSYSTEM:Windows /LARGEADDRESSAWARE /PROGRESSGUI /COMPMODE:FAST /PRIORITY:NORMAL User32.lib Winmm.lib opengl32.lib Kernel32.lib ucrt.lib Gdi32.lib /LIBPATH:"C:\Program Files (x86)\Windows Kits\10\Lib\10.0.16299.0\um\x86" /LIBPATH:"C:\Program Files (x86)\Windows Kits\10\Lib\10.0.16299.0\ucrt\x86"
