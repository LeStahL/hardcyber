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

path_string = 'm 68.868931,100.55248 -1.335154,1.58674 h -6.499881 l -5.629173,-6.297896 -5.434251,6.297896 h -9.369665 l -1.25782,-1.58674 -1.223163,1.58674 H 16.570838 L 3.8892178,87.344133 13.178204,76.558943 h 2.01511 l -9.1488588,10.78519 h 1.3473655 l 9.1706353,-10.78519 h 8.822947 l 4.636736,5.339573 1.575343,-2.03078 h -2.185884 l -3.10447,-3.308793 H 59.9079 l -7.227023,8.646923 H 36.027995 l -0.891232,-1.05695 -2.480948,3.195217 h 19.446876 l 9.155659,-10.78519 h 2.574203 l -9.172222,10.78519 h 0.977972 l 9.223563,-10.78519 h 1.383748 l -3.427297,-4.305137 h 7.011459 l 3.439583,4.305137 21.298964,-0.03341 -2.711737,3.41478 h -7.60743 l 4.339368,5.1859 10.874589,-12.87241 h 7.046877 L 93.635102,87.526446 H 83.77289 l -6.372628,-7.58613 h -1.043956 l 7.009599,8.568812 H 93.99694 l 13.60018,-16.255323 h 2.05238 l -13.07351,16.255323 6.94846,8.205847 H 71.913973 l -1.742139,2.24896 h 28.509319 l 3.311987,3.968745 H 70.819561 Z M 40.398092,92.876792 H 42.8795 l 3.967465,4.560672 4.943105,-5.74928 -10.224519,-0.0693 -10.224519,-0.0692 -1.2694,-1.294125 -1.151746,1.291995 -14.282449,0.1408 6.208276,7.27604 h 16.901466 l -5.400694,-6.087602 h 7.056206 l 5.524542,6.952815 0.486527,-0.714183 z m 29.590889,-1.309128 -9.851383,-0.144 3.513911,-4.10113 h 11.602225 l -6.345616,-7.35267 -9.793968,11.54469 5.384713,6.49272 z m 23.785592,1.90643 -1.455212,-1.91821 H 79.002037 l -1.110817,-1.45522 -2.90159,3.37343 z m -66.675008,-8.26823 h -1.957379 l -4.422421,-5.15937 -6.320201,7.297639 H 25.354581 Z M 50.118554,79.867736 H 38.608941 l -1.507327,1.898538 h 11.646745 z'

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
    
with open('path.frag', 'wt') as f:
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
