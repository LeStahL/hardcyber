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

import os
import argparse

from importlib.machinery import SourceFileLoader

Rule = SourceFileLoader("Rule", "../minification/Rule.py").load_module()
Token = SourceFileLoader("Token", "../minification/Token.py").load_module()
GLSLLexer130 = SourceFileLoader("GLSLLexer130", "../minification/GLSLLexer130.py").load_module()
Compressor = SourceFileLoader("Compressor", "../minification/Compressor.py").load_module()

# Get available symbols
symbol_files = os.listdir("symbols")

# Remove all files that do not have ".frag" ending
symbol_files = [ f for f in symbol_files if f.endswith('.frag') ] 
symbol_names = [ f.replace('.frag', '') for f in symbol_files ]

# Read all symbol code from symbol files
symbol_codes = []
for symbol_file in symbol_files:
    symbol_code = ""
    with open("symbols/"+symbol_file, "rt") as f:
        symbol_code = f.read()
        f.close()
    symbol_codes += [ Compressor.compress(symbol_code).replace('\"','\\\"').replace('\n', '\\n\"\n\"').replace('#version 130', '#version 130\\n')  + "\\0"]

# Parse command line args
parser = argparse.ArgumentParser(description='Team210 symbol packer.')
parser.add_argument('-o', '--output', dest='out')
args, rest = parser.parse_known_args()

if rest == []:
    print("Error: No input files present.")
    exit()

# Generate compilation header
header_source = "//Generated with Symbolize (c) 2019 Alexander Kraus <nr4@z10.info>.\n#ifndef "
header_source += "SYMBOLIZE_H" + "\n#define " + "SYMBOLIZE_H" + "\n\nextern float progress;" 
symbol_list = []
scene_names = []
scene_sources = []
scene_symbol_lists = []
scene_uniform_lists = []
for inputfile in rest:
    scene_names += [ inputfile.replace(".frag", "") ]
    
    input_source_lines = None
    input_source = ""
    with open(inputfile, "rt") as f:
        input_source = f.read()
        f.close()
    #print(input_source)
    scene_sources += [ Compressor.compress(input_source).replace('\"','\\\"').replace('\n', '\\n\"\n\"').replace('#version 130', '#version 130\\n') + "\\0" ]
    input_source_lines = input_source.split('\n')
    input_source_lines = [ l + "\n" for l in input_source_lines ]
    #print(input_source_lines)
    
    # Extract symbol list from source file
    scene_symbol_list = []
    for line in input_source_lines:
        if 'void' in line and ';' in line:
            s = line.split()
            symbol_name = s[s.index('void') + 1].split('(')[0]
            if not symbol_name in symbol_list: 
                symbol_list += [ symbol_name ]
            scene_symbol_list += [ symbol_name ]
    scene_symbol_lists += [ scene_symbol_list ]

    # Extract uniform list from source file
    scene_uniform_list = []
    for line in input_source_lines:
        if 'uniform' in line:
            types_list = [ 'float', 'int', 'vec2', 'vec3', 'vec4', 'sampler2D', 'sampler1D', 'sampler3D', 'bool', 'uniform' ]
            modified_line = line.replace(',', ' ').replace(';','')
            for types in types_list:
                modified_line = modified_line.replace(types, '')
            scene_uniform_list += modified_line.split()
    scene_uniform_lists += [ scene_uniform_list ]
    print(scene_uniform_list)
    
header_source += "int "
for i in range(len(symbol_list)-1):
    header_source += symbol_list[i] + "_handle, ";
header_source += symbol_list[-1] + "_handle;\n"
header_source += "const int nsymbols = " + str(len(symbol_list)) + ";\n"
for i in range(len(symbol_list)):
    header_source += "const char *" + symbol_list[i]+"_source = \"" + symbol_codes[symbol_names.index(symbol_list[i])] + "\";\n"
for i in range(len(scene_names)):
    header_source += "const char *" + scene_names[i] + "_source = \"" + scene_sources[i] + "\";\n"
for i in range(len(symbol_list)):
    header_source += "void Load" + symbol_list[i] + "()\n{\n    int " + symbol_list[i] + "_size"
    header_source += " = strlen(" + symbol_list[i]+"_source);\n    "
    header_source += symbol_list[i]+"_handle = glCreateShader(GL_FRAGMENT_SHADER);\n"
    header_source += "    glShaderSource(" + symbol_list[i] + "_handle, 1, (GLchar **)&"
    header_source += symbol_list[i] + "_source, &"  + symbol_list[i] + "_size);\n"
    header_source += "    glCompileShader(" + symbol_list[i] + "_handle);\n"
    header_source += "#ifdef DEBUG\n    printf(\"---> " + symbol_list[i] + " Shader:\\n\");\n"
    header_source += "    debug(" + symbol_list[i] + "_handle);\n    printf(\">>>>\\n\");\n#endif\n"
    header_source += "    progress += .2/(float)nsymbols;\n}\n"

# Add symbol loader
header_source += "\nvoid LoadSymbols()\n{\n"
for symbol in symbol_list:
    header_source += "    Load" + symbol + "();\n"
    header_source += "    updateBar();\n"
header_source += "}\n"

# Add program variables
header_source += "int "
for scene_name in scene_names[:-1]:
    header_source += scene_name + "_program, " + scene_name + "_handle, "
header_source += scene_names[-1] + "_program, " + scene_names[-1] + "_handle;\n"

# Add uniform variables
for i in range(len(scene_names)):
    header_source += "int "
    scene_name = scene_names[i]
    for j in range(len(scene_uniform_lists[i])-1):
        header_source += scene_name + "_" + scene_uniform_lists[i][j] + "_location,"
    header_source += scene_name + "_" + scene_uniform_lists[i][-1] + "_location;\n"

# Add program loader
nprograms = len(scene_names)
header_source += "const int nprograms = " +str(nprograms) + ";\n"
for i in range(len(scene_names)):
    scene_name = scene_names[i]
    header_source += "\nvoid Load" + scene_name + "()\n{\n"
    # Shader
    header_source += "    int " + scene_name + "_size"
    header_source += " = strlen(" + scene_name+"_source);\n    "
    header_source += scene_name+"_handle = glCreateShader(GL_FRAGMENT_SHADER);\n"
    header_source += "    glShaderSource(" + scene_name + "_handle, 1, (GLchar **)&"
    header_source += scene_name + "_source, &"  + scene_name + "_size);\n"
    header_source += "    glCompileShader(" + scene_name + "_handle);\n"
    header_source += "#ifdef DEBUG\n    printf(\"---> " + scene_name + " Shader:\\n\");\n"
    header_source += "    debug(" + scene_name + "_handle);\n    printf(\">>>>\\n\");\n#endif\n"
    # Program
    header_source += "    " + scene_name + "_program = glCreateProgram();\n"
    header_source += "    glAttachShader(" + scene_name + "_program," + scene_name + "_handle);\n"
    for symbol in scene_symbol_lists[i]:
        header_source += "    glAttachShader(" + scene_name + "_program," + symbol + "_handle);\n"
    header_source += "    glLinkProgram(" + scene_name + "_program);\n"
    header_source += "#ifdef DEBUG\n    printf(\"---> " + scene_name + " Program:\\n\");\n"
    header_source += "    debugp(" + scene_name + "_program);\n    printf(\">>>>\\n\");\n#endif\n"
    header_source += "    glUseProgram(" + scene_name + "_program);\n"
    for uniform_name in scene_uniform_lists[i]:
        header_source += "    " + scene_name + "_" + uniform_name + "_location = glGetUniformLocation(" + scene_name + "_program, \"" + uniform_name + "\");\n"
    header_source += "    progress += .2/(float)nprograms;\n}\n"

# Add program loader
header_source += "\nvoid LoadPrograms()\n{\n"
for scene_name in scene_names:
    header_source += "    Load" + scene_name + "();\n"
    header_source += "    updateBar();\n"
header_source += "}\n"

header_source += "#endif\n"

# Write output to file or stdout
if args.out == None:
    print(header_source)
else:
    with open(args.out, "wt", newline='\n') as f:
        f.write(header_source)
        f.close()
