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

import re
import Rule as Rule
import Token as Token

class GLSLLexer130:
    def __init__(self, source=""):
        self.source = source
        
        self.rules = []
        self.rules += [ Rule.Rule("#version", "VERSION_DIRECTIVE") ]
        self.rules += [ Rule.Rule("#define", "DEFINE_DIRECTIVE") ]
        self.rules += [ Rule.Rule("/\*(.|\n)*\*/", "MULTILINE_COMMENT") ]
        self.rules += [ Rule.Rule("//.*\n", "SINGLELINE_COMMENT") ]
        self.rules += [ Rule.Rule("\n", "CRLF") ]
        self.rules += [ Rule.Rule("\d+", "INTEGER_CONSTANT") ]
        self.rules += [ Rule.Rule("((-?\d+\.\d*)|(-?\d*\.\d+))([eE]([-\+]?)\d+)?", "FLOAT_CONSTANT") ]
        self.rules += [ Rule.Rule("\.([xyzw]+|[rgba]+)", "SWIZZLE") ]
        self.rules += [ Rule.Rule("if", "IF") ]
        self.rules += [ Rule.Rule("else", "ELSE") ]
        self.rules += [ Rule.Rule("for", "FOR") ]
        self.rules += [ Rule.Rule("uniform", "UNIFORM") ]
        self.rules += [ Rule.Rule("const", "CONST") ]
        self.rules += [ Rule.Rule("float", "FLOAT") ]
        self.rules += [ Rule.Rule("int", "INT") ]
        self.rules += [ Rule.Rule("vec2", "VEC2") ]
        self.rules += [ Rule.Rule("vec3", "VEC3") ]
        self.rules += [ Rule.Rule("vec4", "VEC4") ]
        self.rules += [ Rule.Rule("mat2", "MAT2") ]
        self.rules += [ Rule.Rule("mat3", "MAT3") ]
        self.rules += [ Rule.Rule("mat4", "MAT4") ]
        self.rules += [ Rule.Rule("break", "BREAK") ]
        self.rules += [ Rule.Rule("sampler2D", "SAMPLER2D") ]
        self.rules += [ Rule.Rule(";", "SEMICOLON") ]
        self.rules += [ Rule.Rule(":", "COLON") ]
        self.rules += [ Rule.Rule(",", "COMMA") ]
        self.rules += [ Rule.Rule("\?", "QUESTIONMARK") ]
        self.rules += [ Rule.Rule("\.", "DOT") ]
        self.rules += [ Rule.Rule("=", "EQUAL") ]
        self.rules += [ Rule.Rule("<=", "LESSEQUAL") ]
        self.rules += [ Rule.Rule(">=", "GREATEREQUAL") ]
        self.rules += [ Rule.Rule("==", "ISEQUAL") ]
        self.rules += [ Rule.Rule("!=", "NOTEQUAL") ]
        self.rules += [ Rule.Rule("<", "LESSTHAN") ]
        self.rules += [ Rule.Rule(">", "GREATERTHAN") ]
        self.rules += [ Rule.Rule("\+=", "PLUSEQUAL") ]
        self.rules += [ Rule.Rule("\*=", "TIMESEQUAL") ]
        self.rules += [ Rule.Rule("/=", "DIVEQUAL") ]
        self.rules += [ Rule.Rule("-=", "MINUSEQUAL") ]
        self.rules += [ Rule.Rule("\*", "TIMES") ]
        self.rules += [ Rule.Rule("/", "DIVBY") ]
        self.rules += [ Rule.Rule("\+", "PLUS") ]
        self.rules += [ Rule.Rule("-", "MINUS") ]
        self.rules += [ Rule.Rule("\(", "LPAREN") ]
        self.rules += [ Rule.Rule("\)", "RPAREN") ]
        self.rules += [ Rule.Rule("\[", "LBRACKET") ]
        self.rules += [ Rule.Rule("\]", "RBRACKET") ]
        self.rules += [ Rule.Rule("{", "LBRACE") ]
        self.rules += [ Rule.Rule("}", "RBRACE") ]
        self.rules += [ Rule.Rule("[|]{2}", "OR") ]
        self.rules += [ Rule.Rule("[&]{2}", "AND") ]
        self.rules += [ Rule.Rule("gl_FragColor", "GL_FRAGCOLOR") ]
        self.rules += [ Rule.Rule("gl_FragCoord", "GL_FRAGCOORD") ]
        self.rules += [ Rule.Rule("in", "IN_QUALIFIER") ]
        self.rules += [ Rule.Rule("out", "OUT_QUALIFIER") ]
        self.rules += [ Rule.Rule("inout", "INOUT_QUALIFIER") ]
        self.rules += [ Rule.Rule("void", "VOID") ]
        self.rules += [ Rule.Rule("texture", "TEXTURE") ]
        self.rules += [ Rule.Rule("main", "MAIN") ]
        self.rules += [ Rule.Rule("sin", "SIN") ]
        self.rules += [ Rule.Rule("cos", "COS") ]
        self.rules += [ Rule.Rule("tan", "TAN") ]
        self.rules += [ Rule.Rule("asin", "ASIN") ]
        self.rules += [ Rule.Rule("acos", "ACOS") ]
        self.rules += [ Rule.Rule("atan", "ATAN") ]
        self.rules += [ Rule.Rule("sinh", "SINH") ]
        self.rules += [ Rule.Rule("cosh", "COSH") ]
        self.rules += [ Rule.Rule("tanh", "TANH") ]
        self.rules += [ Rule.Rule("asinh", "ASINH") ]
        self.rules += [ Rule.Rule("acosh", "ACOSH") ]
        self.rules += [ Rule.Rule("atanh", "ATANH") ]
        self.rules += [ Rule.Rule("length", "LENGTH") ]
        self.rules += [ Rule.Rule("reflect", "REFLECT") ]
        self.rules += [ Rule.Rule("refract", "REFRACT") ]
        self.rules += [ Rule.Rule("step", "STEP") ]
        self.rules += [ Rule.Rule("smoothstep", "SMOOTHSTEP") ]
        self.rules += [ Rule.Rule("clamp", "CLAMP") ]
        self.rules += [ Rule.Rule("dot", "DOT") ]
        self.rules += [ Rule.Rule("abs", "ABS") ]
        self.rules += [ Rule.Rule("pow", "POW") ]
        self.rules += [ Rule.Rule("mix", "MIX") ]
        self.rules += [ Rule.Rule("floor", "FLOOR") ]
        self.rules += [ Rule.Rule("fract", "FRACT") ]
        self.rules += [ Rule.Rule("round", "ROUND") ]
        self.rules += [ Rule.Rule("ceil", "CEIL") ]
        self.rules += [ Rule.Rule("max", "MAX") ]
        self.rules += [ Rule.Rule("min", "MIN") ]
        self.rules += [ Rule.Rule("mod", "MOD") ]
        self.rules += [ Rule.Rule("sign", "SIGN") ]
        self.rules += [ Rule.Rule("exp", "EXP") ]
        self.rules += [ Rule.Rule("normalize", "NORMALIZE") ]
        self.rules += [ Rule.Rule("cross", "CROSS") ]
        self.rules += [ Rule.Rule("sqrt", "SQRT") ]
        self.rules += [ Rule.Rule("continue", "CONTINUE") ]
        self.rules += [ Rule.Rule("return", "RETURN") ]
        self.rules += [ Rule.Rule("smoothstep", "SMOOTHSTEP") ]
        self.rules += [ Rule.Rule("all", "ALL") ]
        self.rules += [ Rule.Rule("lessThan", "LESSTHAN") ]
        
        self.rules += [ Rule.Rule("[a-zA-Z_]+[a-zA-Z0-9_]*", "IDENTIFIER") ]
        self.index = 0
        self.line = 0
        self.column = 0
        
        pass
    
    def source(self, source):
        self.source = source
        pass
    
    def token(self):
        if self.index == len(self.source)-1: return None
        while self.source[self.index] in [ ' ', '\n', '\t' ]: 
            self.index = min(self.index+1,len(self.source)-1)
            if self.index == len(self.source)-1:
                return None
                
        longestMatchIndex = -1
        longestMatchSize = -1
        for i in range(len(self.rules)):
            rule = self.rules[i]
            if rule.matches(self.source[self.index:]):
                matchsize = rule.lastMatchSize()
                if matchsize > longestMatchSize:
                    longestMatchIndex = i
                    longestMatchSize = matchsize
        
        if longestMatchIndex == -1:
            print("Syntax error at line:", str(self.line))
            return None
        
        tokenName = self.rules[longestMatchIndex].token_type
        tokenData = self.source[self.index:self.index+longestMatchSize]
        
        self.index += longestMatchSize
        
        return Token.Token(tokenName, tokenData)
    
    
