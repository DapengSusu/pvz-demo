#!/bin/bash

# 编译平台
platform=$1
if [ -z "$platform" ]
then
	platform=linux
fi

# 编译模式
mode=$2
if [ -z "$mode" ]
then
	mode=debug
fi

# 编译项目
cocos compile -s . -p $platform -m $mode -j 4 -o bin

