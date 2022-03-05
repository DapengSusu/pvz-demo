#!/bin/bash

# 发布平台
platform=$1
if [ -z "$platform" ]
then
	platform=linux
fi

# 发布模式
mode=$2
if [ -z "$mode" ]
then
	mode=release
fi

# 发布项目
cocos deploy -s . -p $platform -m $mode

