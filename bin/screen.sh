#!/bin/bash

# echo "正在执行蓝屏脚本..."

dir=$(dirname $(readlink -f "$0"))

/usr/bin/java -jar ${dir}/bscreen.jar
