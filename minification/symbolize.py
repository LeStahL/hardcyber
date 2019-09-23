# Hardcyber - PC-64k-Intro by Team210 at Deadline 2k19
# Copyright (C) 2019  Alexander Kraus <nr4@z10.info>
# Copyright (C) 2019  DaDummy <c.anselm@paindevs.com>
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

src_path = os.path.dirname(os.path.abspath(__file__))

Rule = SourceFileLoader("Rule", src_path + "/Rule.py").load_module()
Token = SourceFileLoader("Token", src_path + "/Token.py").load_module()
GLSLLexer130 = SourceFileLoader("GLSLLexer130", src_path + "/GLSLLexer130.py").load_module()
Compressor = SourceFileLoader("Compressor", src_path + "/Compressor.py").load_module()

# Parse command line args
parser = argparse.ArgumentParser(description='Team210 symbol packer.')
parser.add_argument('-o', '--output', dest='out')
parser.add_argument('-s', '--symbols', dest='symbols')
args, rest = parser.parse_known_args()

if rest == []:
    print("Error: No input files passed on commandline.")
    exit()

print("Packing: ",rest)

# Get available symbols
symbol_files = os.listdir(args.symbols)

# Remove all files that do not have ".frag" ending
symbol_files = [ f for f in symbol_files if f.endswith('.frag') ]
symbol_names = [ f.replace('.frag', '') for f in symbol_files ]

# Read all symbol code from symbol files
symbol_codes = []
for symbol_file in symbol_files:
    symbol_code = ""
    with open(args.symbols+"/"+symbol_file, "rt") as f:
        symbol_code = f.read()
        f.close()
    symbol_codes += [ Compressor.compress(symbol_code).replace('\"','\\\"').replace('\n', '\\n\"\n\"').replace('#version 130', '#version 130\\n')]

# Generate compilation header
header_source = "//Generated with Symbolize (c) 2019 Alexander Kraus <nr4@z10.info>, DaDummy <c.anselm@paindevs.com>.\n#ifndef "
if args.out == None:
    header_source += "SYMBOLIZE_H" + "\n#define " + "SYMBOLIZE_H" + "\n"
else:
    header_name = args.out.split("/")[-1].upper().replace(".", "_")
    header_source += header_name + "\n#define " + header_name + "\n"
symbol_list = []
scene_names = []
scene_sources = []
scene_symbol_lists = []
scene_uniform_lists = []
for inputfile in rest:
    scene_names += [ inputfile.replace(".frag", "").replace("/", "_") ]
    
    input_source_lines = None
    input_source = ""
    with open(inputfile, "rt") as f:
        input_source = f.read()
        f.close()
    #print(input_source)
    scene_sources += [ Compressor.compress(input_source).replace('\"','\\\"').replace('\n', '\\n\"\n\"').replace('#version 130', '#version 130\\n') ]
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
    print("Contained uniforms: ",scene_uniform_list)

# Remove unused symbols
symIdx = 0
while symIdx < len(symbol_names):
    is_symbol_used = False
    for scnIdx in range(len(scene_names)):
        if symbol_names[symIdx] in (scene_symbol_lists[scnIdx]):
            is_symbol_used = True
    if is_symbol_used:
        symIdx += 1
    else:
        del symbol_names[symIdx]
        del symbol_codes[symIdx]
        del symbol_files[symIdx]


# Write out all remaining symbols and all scenes into a continous array for simple loading
header_source += "static struct ShaderSymbol shader_symbols[] = {\n"
for i in range(len(symbol_codes)):
    header_source += "    {0, GL_FRAGMENT_SHADER, \"" + symbol_codes[i] + "\"},\n"
for i in range(len(scene_sources)):
    header_source += "    {0, GL_FRAGMENT_SHADER, \"" + scene_sources[i] + "\"},\n"
header_source += "};\n\n"

# Write out control structure for scene load and information regarding uniforms
for i in range(len(scene_names)):
    header_source += "static unsigned short shader_" + scene_names[i] + "_symbols[] = { "
    header_source += str(len(symbol_names) + i) + ","
    for symbol in scene_symbol_lists[i]:
        header_source += str(symbol_names.index(symbol)) + ","
    header_source += " };\n"
    header_source += "static struct Uniform shader_" + scene_names[i] + "_uniforms[] = {\n"
    for j in range(len(scene_uniform_lists[i])):
        header_source += "    { 0, \"" + scene_uniform_lists[i][j] + "\" },\n"
    header_source += "};\n"
    for j in range(len(scene_uniform_lists[i])):
        header_source += "#define shader_uniform_" + scene_names[i] + "_" + scene_uniform_lists[i][j] + " (shader_" + scene_names[i] + "_uniforms[" + str(j) + "].location)\n"
    header_source += "static struct ShaderProgram shader_program_" + scene_names[i] + " = { 0, ARRAYSIZE(shader_" + scene_names[i] + "_symbols), ARRAYSIZE(shader_" + scene_names[i] + "_uniforms), shader_" + scene_names[i] + "_symbols, shader_" + scene_names[i] + "_uniforms };\n"
    header_source += "\n"

header_source += "#endif\n"

# Write output to file or stdout
if args.out == None:
    print(header_source)
else:
    with open(args.out, "wt", newline='\n') as f:
        f.write(header_source)
        f.close()
