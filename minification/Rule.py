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

class Rule:
    def __init__(self, regex_str="", token_type=""):
        self.regex_str = regex_str
        self.token_type = token_type
        self.result = None
        pass
    
    def matches(self, code):
        self.result = re.match(self.regex_str, code)
        
        if self.result == None: 
            return False
        return True
    
    def lastMatchSize(self):
        if self.result == None: return -1
        
        span = self.result.span()
        return span[1]-span[0]
    
    
