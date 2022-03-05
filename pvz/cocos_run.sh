#!/bin/bash

# 运行平台
platform=$1
if [ -z "$platform" ]
then
	platform=linux
fi

# 运行模式
mode=$2
if [ -z "$mode" ]
then
	mode=debug
fi

# 运行项目
cocos run -s . -p $platform -m $mode

