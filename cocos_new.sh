#!/bin/bash

# 项目名
proj_name=$1
if [ -z "$proj_name" ]
then
	exit
fi

# 项目存放目录
proj_path=$2
if [ -z "$proj_path" ]
then
	proj_path=.
fi
#echo proj_path: $proj_path

# 创建项目
cocos new $proj_name -p com.dapeng.$proj_name -l cpp -d $proj_path

