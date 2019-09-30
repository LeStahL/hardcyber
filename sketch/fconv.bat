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

python ..\symbolize.py ..\gfx.frag -o ..\gfx.h
python ..\symbolize.py ..\sfx.frag -o ..\sfx.h

"C:/Program Files (x86)/Microsoft Visual Studio/2017/Community/VC/Tools/MSVC/14.16.27023/bin/Hostx86/x86/cl.exe" ..\nswv.c /out:nswv.obj /I"C:\Program Files (x86)\Windows Kits\10\Include\10.0.17763.0\um" /I"C:\Program Files (x86)\Windows Kits\10\Include\10.0.17763.0\shared" /I"C:\Program Files (x86)\Windows Kits\10\Include\10.0.17763.0\ucrt" /I"C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Tools\MSVC\14.16.27023\include" /I".." /DWIN32 /c /Gy /O1 /fp:fast /GR- /GS- /MT
