# Tunguska by Team210 - 64k intro by Team210 at Solskogen 2k19
# Copyright (C) 2018  Alexander Kraus <nr4@z10.info>
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

from importlib.machinery import SourceFileLoader

Rule = SourceFileLoader("Rule", "../minification/Rule.py").load_module()
Token = SourceFileLoader("Token", "../minification/Token.py").load_module()
GLSLLexer130 = SourceFileLoader("GLSLLexer130", "../minification/GLSLLexer130.py").load_module()
Compress = SourceFileLoader("Compress", "../minification/Compress.py").load_module()

code = ""
with open("../gfx/symbols/normal.frag", "rt") as f:
    code = f.read()
    f.close()
    
lexer = GLSLLexer130.GLSLLexer130(code)
token = lexer.token()
while token != None:
    print("name=", token.tokenName, "; data=", token.tokenData)
    token = lexer.token()
