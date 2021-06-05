#!/bin/bash

MAJOR=1
MINOR=0
COUNT=$(git rev-list --count HEAD)
echo "Version: $MAJOR.$MINOR.$COUNT"

for file in smsdk_config.h
do
    sed -i "s%<Major>.<Minor>.<GitCommit>%$MAJOR.$MINOR.$COUNT%g" $file > output.txt
    rm output.txt
done

EXT_DIR=$(pwd)
mkdir build
cd build
python3 ${EXT_DIR}/configure.py --enable-optimize --mms-path "${EXT_DIR}/metamod-source" --sm-path "${EXT_DIR}/sourcemod" --hl2sdk-root "${EXT_DIR}" --sdk csgo
ambuild