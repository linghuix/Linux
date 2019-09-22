#!/bin/bash
#Filename:sleep.sh
#延迟5秒

echo -n Count
tput sc

count=0;
while true
do
if [ $count -lt 5 ]
then let count++;
sleep 1
tput rc
tput ed
echo -n " $count";
else 
echo ""		#结尾自动添加回车
exit 0;
fi
done
