# Hardcyber - PC-64k-Intro by Team210 at Deadline 2k19
# Copyright (C) 2019  Alexander Kraus <nr4@z10.info>
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.

from svgpathtools import Path, Line
from svgpathtools import parse_path

path_string = 'm 65.481273,41.91372 c 0,10.000077 0,20.000158 0,30.000235 6.666603,0 13.333209,0 19.999812,0 0,3.333303 0,6.666603 0,9.999906 -6.666603,0 -13.333209,0 -19.999812,0 0,3.333303 0,6.666603 0,9.999906 9.999906,0 19.999814,0 29.99972,0 0,-9.999906 0,-19.999812 0,-29.999717 -6.666605,0 -13.333208,0 -19.999814,0 0,-3.333475 0,-6.66695 0,-10.000425 6.666606,0 13.333209,0 19.999814,0 0,-3.333303 0,-6.666603 0,-9.999905 -9.999906,0 -19.999814,0 -29.99972,0 z m 35.442277,0 c 0,3.333302 0,6.666602 0,9.999905 6.66661,0 13.33321,0 19.99982,0 0,3.333475 0,6.66695 0,10.000425 3.3333,0 6.6666,0 9.9999,0 0,-6.666778 0,-13.333553 0,-20.00033 -9.9999,0 -19.99981,0 -29.99972,0 z m 19.99982,20.00033 c -3.33331,0 -6.66661,0 -9.99991,0 0,6.666603 0,13.333208 0,19.999811 3.3333,0 6.6666,0 9.99991,0 0,-6.666603 0,-13.333208 0,-19.999811 z m -9.99991,19.999811 c -3.3333,0 -6.6666,0 -9.99991,0 0,3.333303 0,6.666603 0,9.999906 3.33331,0 6.66661,0 9.99991,0 0,-3.333303 0,-6.666603 0,-9.999906 z M 146.36523,41.91372 c 0,3.333302 0,6.666602 0,9.999905 -3.33348,0 -6.66695,0 -10.00043,0 0,3.333475 0,6.66695 0,10.000425 3.33348,0 6.66695,0 10.00043,0 0,6.666603 0,13.333208 0,19.999811 -3.33348,0 -6.66695,0 -10.00043,0 0,3.333303 0,6.666603 0,9.999906 10.00008,0 20.00016,0 30.00024,0 0,-3.333303 0,-6.666603 0,-9.999906 -3.33331,0 -6.66661,0 -9.99991,0 0,-13.33338 0,-26.666761 0,-40.000141 -3.3333,0 -6.6666,0 -9.9999,0 z m 35.44176,0 c 0,3.333302 0,6.666602 0,9.999905 -3.3333,0 -6.66661,0 -9.99991,0 0,3.333475 0,6.66695 0,10.000425 3.3333,0 6.66661,0 9.99991,0 0,6.666603 0,13.333208 0,19.999811 -3.3333,0 -6.66661,0 -9.99991,0 0,3.333303 0,6.666603 0,9.999906 10.00008,0 20.00016,0 30.00024,0 0,-3.333303 0,-6.666603 0,-9.999906 -3.33348,0 -6.66695,0 -10.00043,0 0,-13.33338 0,-26.666761 0,-40.000141 -3.3333,0 -6.6666,0 -9.9999,0 z'

path = parse_path(path_string)

# find dimensions
xmax = -1.e9
xmin = 1.e9
ymax = -1.e9
ymin = 1.e9
for line in path:
    xmax = max(xmax, line.start.real)
    xmax = max(xmax, line.end.real)
    
    xmin = min(xmin, line.start.real)
    xmin = min(xmin, line.end.real)
    
    ymax = max(ymax, line.start.imag)
    ymax = max(ymax, line.end.imag)
    
    ymin = min(ymin, line.start.imag)
    ymin = min(ymin, line.end.imag)

# rescale path
for i in range(len(path)):
    path[i].start -= complex(xmin,ymin)
    path[i].start = complex(path[i].start.real/abs(xmax-xmin), path[i].start.imag/abs(ymax-ymin)/100.*29.)
    path[i].start -= complex(.5,.5*29./100.)
    path[i].start = complex(path[i].start.real,-path[i].start.imag)
    
    path[i].end -= complex(xmin,ymin)
    path[i].end = complex(path[i].end.real/abs(xmax-xmin), path[i].end.imag/abs(ymax-ymin)/100.*29.)
    path[i].end -= complex(.5,.5*29./100.)
    path[i].end = complex(path[i].end.real,-path[i].end.imag)

# sort path
#newpath = [ path[0] ]
#del path[0]
#while len(path) > 1:
    #print(len(path))
    #for j in range(len(path)-1):
        #print(j,"/",len(path))
        #if abs(newpath[-1].end - path[j].start)<5.e-1:
            #newpath += [ path[j] ]
            #del path[j]
            #break
#path = newpath
    
with open('5711.frag', 'wt') as f:
    f.write('const int npts = ' + str(4*len(path)) + ';\n')
    f.write('const float path[npts] = float[npts](')
    
    for i in range(len(path)-1):
        line = path[i]
        f.write('{:.3f}'.format(line.start.real) + ',' + '{:.3f}'.format(line.start.imag) + ',')
        f.write('{:.3f}'.format(line.end.real) + ',' + '{:.3f}'.format(line.end.imag) + ',')
    line = path[-1]
    f.write('{:.3f}'.format(line.start.real) + ',' + '{:.3f}'.format(line.start.imag) + ',')
    f.write('{:.3f}'.format(line.end.real) + ',' + '{:.3f}'.format(line.end.imag))
    f.write(');\n')
    f.close()
