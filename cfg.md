# Linux

系统配置方法


## 配置动态库的默认搜索路径

这样在执行需要动态库的可执行文件时,就只需要执行,不需要格外条件.

**永久配置** : 在/etc/ld.so.conf.d/中包含了默认的搜索路径,包括usr/local/lib 等.

创建(作为root用户)新文件包含, 你的库路径.
` # echo "/path-to-your-libs/" > /etc/ld.so.conf.d/your.conf`
使之生效
`sudo ldconfig`
就可以了

或者

执行一下”ldconfig 目录名”。此命令的功能在于让ldconfig将指定目录下的动态链接库被系统共享起来,意即:在缓存文件/etc/ld.so.cache中追加进指定目录下的共享库。

或者

将库复制到,user/local/lib等处于库默认搜索路径中.
**ldd 可执行文件 可用于查看动态库的调用过程**

**非永久配置** : 
编译链接器会搜寻`LD_LIBRARY_PATH`所指定的目录，那么我们可以将这个环境变量设置成当前目录：
export LD_LIBRARY_PATH=$(pwd)


## 配置登录










