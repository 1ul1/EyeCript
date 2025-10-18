#!/bin/bash
cd "$(dirname $(dirname $(realpath $0)))"
make -C ./EyeCript build
afplay /System/Library/Sounds/Glass.aiff &
./EyeCript/build/EC.out dec
# osascript ./EyeCript/utils/apple_scripts/options.applescript