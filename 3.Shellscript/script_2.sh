#!/bin/bash 

#使用 _DEBUG=on script_2.sh 可以显示传入d的参数,
#不使用该命令的话是不会执行该命令的

function d()
{
[ "$_DEBUG" == "on" ] && $@ || :  # :表示什么也不做
}

for i in {1..10}
do 
d echo "调试信息 $i"
echo $i
done
