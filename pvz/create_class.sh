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
    path=Classes/
fi

# 生成模板
template=$3
if [ -z "$template" ]
then
	template=Classes/HelloWorldScene
fi

# 创建指定类
cp $template.h ${path}${class_name}.h
cp $template.cpp ${path}${class_name}.cpp

# 提示
echo "new class: ${path}${class_name}.h, ${path}${class_name}.cpp"
echo "copy from $template.h, $template.cpp"

