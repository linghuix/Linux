etc 配置文件


/etc/drirc
html文件，记录了驱动driver和对应的应用application，以及每个应用的选项option。驱动程序支持配置基础设施

/etc/hostname
主机名xlh-Lenovo-G50-80。 
The /etc/hostname file configures the name of the local system that is set during boot using the sethostname(2) system call.

/etc/X11 : link  到 /var/X11/lib/X11 


**/etc/nologin**
它平常是不存在的,通常会看到这个档的话,那表示系统大概要 shutdown 了, 因为系统要 shutdown  了 ,  自然不希望有人又login  进来 ,  所以在我们执行 shutdown  时 , nologin  这个档会自动的被 create ,  里面放著 hutdown message. 实际上, 当我们在login  时 ,  系统会去检查有没有这个档 ,  假如有的话 ,  那就会印出这个档案中的 message , 然后不让你 login . 

nologin  也有可能是为了某种理由被制造的 ,  比如说系统在 维护时，暂时不希望有人 login .  可以新建一个nologin的文件，就能实现了。

If the file /etc/nologin exists and is readable, login(1) will allow access only to root.  Other users will be shown the contents of this file and their logins will be refused.  This provides a simple way of temporarily disabling all unprivileged logins.

**/etc/passwd**
password file. 记录了可登陆该系统的所有账户. 所有账户可读，但是只有superuser可以修改
name:password:User_ID:group_ID:comment:Home_directory:shell_toLogin

password一般是加密的或者是"*"和"x"
root的User_ID = 0;
shell_toLogin如果是空的，那么使用/bin/sh，如果写入的shell不存在，那么该用户无法登陆。

默认开机root密码是不定的，所以可以按如下方式设置root密码
sudo passwd root 
[sudo] password for you

**shadow:  shadowed password  普通用户无法读写**
**shadow-：shadow的备份**
包含系统账户的密码信息
1.login name:2.encryted pswd:3.last pswd change time:4.min pswd age:5.max pswd age:6.pswd warning period:7.pswd inactivity period:8.account expriation date:9.reserved field

last passwd change time 是从1970.1.1开始计算的天数
min pswd age 账号密码改变的最小间隔天数
max pswd age 账号密码最长维持天数，超过密码就会过期
pswd warning period 警告用户修改密码的时间点，为失效前的天数
pswd inactivity period 密码失效后，还可以用这个密码登录的天数(超过该时间后，只能联系管理员)
account expriation date 用于警告账号过期的时间点，从1970.1.1开始计算。空表示不会过期
reserved field 用于未来扩展使用
**gshadow :group的密码和群主，成员信息**


**/etc/fstab**

记录开机要挂载上来的文件系统,  这个档案相当重要 !  各位可以在 /etc/rc.d/rc.S  中找到 /sbin/mount -avt nonfs 这一列, 当执行到这一列时 , mount  就依据 /etc/fstab  中的记载 ,  自动的**按顺序**把文件系统挂载上来.因此，这个文档的顺序十分重要！

文件内容：
UUID mount_point file_type  mount_options dump_or_not  check_order

* mount_options包含是否自动挂载，是否允许用户挂载，是否允许设备主人挂载，如果不存在是否报错等等选项
* dump_or_not 默认为0（不dump），与命令dump有关，1表示每天转储，2表示隔一天转储
* check_order 开机过程中文件系统使用fsck命令的检查顺序，root为1，其余为2，如果为空 默认为0，不检查 

1-mesa-glx:amd64 (18.0.5-0ubuntu0~18.04.1) over (18.0.5-0ubuntu0~16.04.1) ...
dpkg: warning: unable to delete old directory '/usr/lib/x86_64-linux-gnu/xorg': Directory not empty
Unpacking at-spi2-core (2.28.0-1) over (2.18.3-4ubuntu1) ...
dpkg: warning: unable to delete old directory '/etc/at-spi2': Directory not empty


**/etc/group** 

如同 /etc/passwd  列出了系统中所有的使用者名字 , /etc/group 定义系统中所有的 group name  与相关讯息 . 格式为 : group_name:passwd:Group_ID:usermembers_list 

如 : author::200:xlh,tom,zxy 
     sudo:x:27:xlh

这个档案只能为 superuser  所读写 ,  一个 superuser  可使用 groupadd ,groupdel , groupmod  来管理 /etc/group  这个档 , 要手动管理也是可以 .  下面是这三个指令的用法 : 
groupadd [ -g gid [ -o ] ] group_name 
groupdel group_name 
groupmod [ -g gid [ -o ] ] [ -n new_group_name ] group_name 



**/etc/hosts**

记录著 IP address  至 hostname  的 mapping . 

127.0.0.1       localhost
127.0.1.1       xlh-Lenovo-G50-80

如此一来 ,  以后我们 telnet xlh-Lenovo-G50-80  就等于 127.0.1.1

至少会有两列 ,  一列为 loopback,这是为了侦错目的而设的 ,  另一列为 local host ,  就是你自己的机器

***修改hosts进行翻墙***
cd ~/Downloads
wget https://raw.githubusercontent.com/racaljk/hosts/master/hosts -O hosts
sed -i "s/localhost/localhost $(hostname)/g" hosts
sed -i "s/broadcasthost/broadcasthost $(hostname)/g" hosts
#cp /etc/hosts /etc/hosts.bak #对将要更改的原文件做个备份是个好习惯。
mv hosts /etc/hosts #用下载来的最新hosts替换本机的
sudo systemctl restart NetworkManager # 重启网络，新的hosts生效

可以访问 https://scholar.google.com
可以做成shell脚本，实现每周运行一次


/etc/hosts.equiv 

在里面可以设定一些 remote machine ,  而从这些 remote machine  利用 rsh  或 rlogin  连回 local machine  的话便不用输入密码同样的东西也可以在 .rhosts  见到



/etc/ld.so.conf 

记录一些 library  所在的目录



/etc/magic 

这个档案记载了许多档案格式的识别字串或方法。

file  这个指令的命令格式为 : 
file [ -c ] [ -z ] [ -L ] [ -f namefile ] [ -m magicfile ] file 
file  这个指令非常有趣 ,  它可以告诉你某一个档案的格式 ,  如它是一个text  档,  或是一个 shell script  或 DOS  可执行档等 ......  而 file 这个指令 ,  就是去参考 /etc/magic  这个资料库 .  假如你知道某一档案的识别字 ,  而原来 magic  这个资料库没有记录 ,  那你可以把识别方法加到资料库中 ,  或乾脆建立自己的资料库算了 



/etc/motd

message of the day 的意思 ,  里面可以写一些message , 而这些 message 会在 login shell  之前被显示出来 . 通常都是 system administrator  要告知 user  的一些讯息 



/etc/mtab 

目前 mount  上来的 filesystems.mtab 内容如下 : 
/dev/hdb1 / ext2 rw 0 0 
/dev/hda1 /mnt/dosc msdos rw 0 0 
/dev/hda5 /mnt/dosd msdos rw 0 0 
/dev/hda6 /mnt/dose msdos rw 0 0 

none /proc proc rw 0 0 



/etc/securetty 

 假如你要以 root login  的话 ,  实际上是有限制的 ,  这个档案就列出了 root  可以 login  的 ttys ,  假如你把每一列都 mark  起来那就没有任何一个 terminal  可供 root login  了。

仔细的在这个档案列出可用的 terminal ,  可使从 modem  连的使用者或经由网路来的其它的使用者比较不容易取得 superuser  的权力 . 



/etc/services 

/etc/shells

里面就记录著可以用的 login shell .  还有一点 ,  那就是这个档的记录会在使用 chsh  时做为参考 ,  唯有被列在这里的 shell ,  使用 chsh  时才会出现这些 shell  可选 



/etc/sudoers 

在一个不是很复杂的系统中 ,  也许一个 System Administrator  就可以管理所有的事情 .  但一但系统提供的服务变多 ,  系统管理的工作也随之变得沉重 , sudo  可以让一个普通的 user  变成 superuser , 这样一来 ,  一个系统的某些工作 , 就可以分配给这些 superusers 来做  .  以减轻负担 ./etc/sudoers  就是记录著那些人可以用 superuser 的身份来执行一些工作 ,  这个档案的格式如下 :


```python
#定义命令的alias
Cmnd_Alias SHUTDOWN=/sbin/halt,/sbin/shutdown 

root ALL=ALL 
jhhsu ALL=ALL 
emotion ALL=ALL,!SHUTDOWN 
```


在这个例子当中 , jhhsu  可以执行 root  所有的命令 , emotion  除了halt及 shutdown  不能执行以外 ,  其它 root  能执行的命令他都能执行 . 

在最后一行添加 用户名 ALL=(ALL:ALL) NOPASSWD:ALL 
可以实现sudo不需要密码，su - 转换成root也不需要密码

root ：能使用sudo命令的用户

ALL=(ALL:ALL) NOPASSWD:ALL
%sudo   ALL=(xlh) NOPASSWD:ALL

%sudo 表示sudo这个用户组 见/etc/group
第一个ALL，表示允许使用sudo的主机，这里为所有的主机
第二个括号里的ALL为使用sudo后以什么身份来执行命令（如果改为xlh，那么即使使用了sudo也无法执行特殊指令。改成root可以）
第三个ALL：为以sudo命令允许执行的命令，ALL为所有命令
NOPASSWD 表示使用sudo不需要密码，不用这个选型则sudo需要输入使用者的密码。

test ALL =(root)/usr/sbin/useradd
意思是允许test从某个主机登陆，以root的来执行/usr/sbin/useradd命令。当然执行方法必须调用sudo useradd



这个档案有一个专属的 editor叫 visudo 可来编辑/etc/sudoer ，直接输入visudo就可以编辑, jhhsu就可以用su - 这个命令转换成superuser 来做原来只有superuser 才能做的事 .  而关于使用 sudo.bin 有一个记录档 ,  在 /var/adm/sudo.log ,  里面记录著谁在什么时候利用sudo  下了那些指令 .  顺便一提的是 :  利用下面这个命令可抓出那些人转换成 superuser  但却没有成功


```
# xlh能够不输入密码就可以执行特殊命令，test无法执行特殊命令
# See the man page for details on how to write a sudoers file.
Defaults        env_reset
Defaults        mail_badpass
Defaults        secure_path="/usr/local/sbin:/usr/local/bin:/usr/sbi$
# Host alias specification
Host_Alias M = ALL
# User alias specification
User_Alias OWNER = xlh
# User privilege specification
root    ALL=(ALL:ALL) ALL
OWNER   M=(root) NOPASSWD:ALL
test    M=(test) ALL
```

**/etc/rc.d文件夹**

It contains scripts to used to control the starting, stopping and restarting of daemons.

rc指run commands


etc/vim/vimrc
vim配置文件
