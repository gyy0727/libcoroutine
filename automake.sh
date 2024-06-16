##########################################################################
# File Name: automake.sh
# Author: muqiu0614
# mail: 3155833132@qq.com
# Created Time: Sun 09 Jun 2024 05:27:25 PM CST
#########################################################################
#!/bin/zsh
PATH=/home/edison/bin:/home/edison/.local/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin:/work/tools/gcc-3.4.5-glibc-2.3.6/bin
export PATH
mkdir build
cd build
cmake ..
make
cd ..
rm build -rf

rm ./libco
