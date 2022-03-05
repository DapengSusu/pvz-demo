#!/bin/bash

# 类名
class_name=$1
if [ -z "$class_name" ]
then
	echo "Specify a valid class name."
    exit
fi

# 路径
path=$2
if [ -z "$path" ]
then
    path=Classes
fi

# 创建指定类
touch $path/$class_name.h
touch $path/$class_name.cpp

# 提示
echo "new class: $path/$class_name.h, $path/$class_name.cpp"

