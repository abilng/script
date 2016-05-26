#!/bin/sh
# Add "use strict" everywhere
# The MIT License (MIT)
# 
# Copyright (c) 2016 Abil N George<mail@abilng.in>
# 
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
# 
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
# 
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.

#require gsed in Mac. Install using `brew install gnu-sed`.

usage() {
    echo "Usage: $0 directory";
    exit;
}

if [[ -z "$1" ]]; then
    usage;
fi

if [[ ! -d $1 ]]; then
    echo "No such directory: $1"
    exit;
fi

case `uname` in
  'Darwin')
    SED=gsed
    ;;
  *)
    SED=sed
    ;;
esac
  

find $1 -name '*.js' |
grep -v '^.*/node_modules' |
while read f;do
  if (head -n3 "$f" | grep -F 'use strict'>/dev/null); then
    echo "[ OK ] $f"
  else
    echo "[FAIL] $f DOES NOT HAVE 'USE STRICT'!!!"
    $SED -i -e "1i \'use strict';\n" "$f";
  fi;
done
