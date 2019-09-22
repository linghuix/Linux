/etc/DIR_COLORS 
设定在用 ls  时 ,  各种不同档案型态所用的颜色。在颜色的组成方面 ,  我们常用 RGB  三原色的成份值来组合出各种不同的颜色 .  由 R,G,B  这个 bit  是 0  或是 1  三个值组合出颜色这个道理虽浅显 ,  但假如我们更了解 R,G, B  的加权值分别是1,2,4  的话 ,  那就再也不用翻书查颜色了

/etc/drirc
html文件，记录了驱动driver和对应的应用application，以及每个应用的选项option。驱动程序支持配置基础设施

/etc/hostname
主机名xlh-Lenovo-G50-80。 The /etc/hostname file configures the name of the local system that is set during boot using the sethostname(2) system call.

/etc/X11 : link  到 /var/X11/lib/X11 



/etc/at.deny

/etc/at.allow

记载那些人可以使用 at 指令，那些人不可以使用 at 指令。使用at指令时先查找allow文件，登记的才能用。如果没有allow文件，再查找deny文件，只要不是deny就都能用。

/var/spool/cron/crontabs/root  中有详细记载 ,  每五分钟 run 一次 at

/var/spool/atjobs 当你使用 at  来安排一件工作时 ,  系统会把你目前的环境变数及所要用 at  执行的工作抄一份到这个目录下的档案中 

/var/spool/atspool 使用 at  命令之后所得到的一些讯息 ,  会被
记录在这里 .  可能是 at  所要执行的命令传回的错误讯息 ,  或传回执行成功的讯息 



**/etc/csh.cshrc**

**/etc/csh.login**

自己的 home directory  也有这两个，系统会先去找 /etc  下这两个档 ,  接著才加上自己 home directory  中那两个档的设定 .  当然 ,  有了 .login 也有 .logout,.logout  中可以写一些 message, 或执行一些命令 ,  当你下达 logout  之后 ,.logout  就会被执行 . 



/etc/disktab 

( disk parameter table )  磁盘参数记录



/etc/exports 

这个档案记录著你要给别人 mount  的档案系统 ,  这就是典型 NFS 系统所存在的档案 , TCP/IP for OS/2  若要使用 network file system 而要把自己的 filesystem  让别人 mount  的话 ,  这个档案也是不可或缺的.  比如说 ,  我所在的 domain name  为 dorm10.nctu.edu.tw ,  我要把我 /usr  下的 filesystem  开放给十舍的人 mount ,  那我在 exports  中要这样写 : 
/usr *.dorm10.nctu.edu.tw(ro) 

接著 ,  在 /etc/rc.d/rc.inet2  中 ,  找到下面的段落 ,  这些段落本来
每一列的前面都有 # ,  现在 ,  依照下面的内容 ,  把这些 #  拿掉 .



/etc/fdprm 

一般情况下是不须要更动的 ,  除非你有很奇怪格式的软碟 ,  或者你想做出不符合一般格式的磁碟片



/etc/nologin 

它平常是不存在的 ,  通常会看到这个档的话 ,  那表示系统大概要 shutdown  了 ,  因为系统要 shutdown  了 ,  自然不希望有人又login  进来 ,  所以在我们执行 shutdown  时 , nologin  这个档会自动的被 create ,  里面放著 hutdown message .  实际上 ,  当我们在login  时 ,  系统会去检查有没有这个档 ,  假如有的话 ,  那就会印出这个档案中的 message , 然后不让你 login . 

nologin  也有可能是为了某种理由被制造的 ,  比如说系统在 维护时，暂时不希望有人 login .  可以新建一个nologin的文件，就能实现了。



**/etc/fstab **

 记录开机要 mount  上来的 filesystem,  这个档案相当重要 !  各位可以
在 /etc/rc.d/rc.S  中找到 /sbin/mount -avt nonfs  这一列 ,  当执行
到这一列时 , mount  就依据 /etc/fstab  中的记载 ,  自动的将档案系统
mount  上来 .

文件内容：

要挂上的档案系统 挂在那里 档案系统格式 读写状况

/dev/hdb2 swap swap defaults 
/dev/hdb1 / ext2 defaults 
/dev/sbpcd /mnt/cdrom iso9660 ro 
/dev/hda1 /mnt/dosc msdos rw 
/dev/hda5 /mnt/dosd msdos rw 
/dev/hda6 /mnt/dose msdos rw 
none /proc proc defaults 



/etc/ftpusers 

 这个档案记录那些人不可以 ftp  签入系统 ,  预设值有 root , uucp news .  这些都是为了 security  方面的考量 ,  你可以在这里加入不可 ftp  进来的 user id .

/etc/gateways



/etc/group 

如同 /etc/passwd  列出了系统中所有的使用者名字 , /etc/group 定义系统中所有的 group name  与相关讯息 . 格式为 : roup_name:passwd:GID:user_list 

如 : author::200:jhhsu,emotion,passion 

上面的例子表示 jhhsu,emotion,passion  都是属于 author  这个 group 

 这个档案只能为 superuser  所读写 ,  一个 superuser  可使用 groupadd , groupdel , groupmod  来管理 /etc/group  这个档 , 要手动管理也是可以 .  下面是这三个指令的用法 : 
groupadd [ -g gid [ -o ] ] group_name 
groupdel group_name 
groupmod [ -g gid [ -o ] ] [ -n new_group_name ] group_name 



**/etc/hosts**

记录著 IP address  至 hostname  的 mapping . 

140.113.17.151 oldstock 

如此一来 ,  以后我们 telnet oldstock  就等于 telnet 140.113.17.151

至少会有两列 ,  一列为 loopback ,  这是为了侦错目的而设的 ,  另一列为 local host ,  就是你自己的机器



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

目前 mount  上来的 filesystems。mtab 内容如下 : 
/dev/hdb1 / ext2 rw 0 0 
/dev/hda1 /mnt/dosc msdos rw 0 0 
/dev/hda5 /mnt/dosd msdos rw 0 0 
/dev/hda6 /mnt/dose msdos rw 0 0 

none /proc proc rw 0 0 



/etc/securetty 

 假如你要以 root login  的话 ,  实际上是有限制的 ,  这个档案就列出了 root  可以 login  的 ttys ,  假如你把每一列都 mark  起来那就没有任何一个 terminal  可供 root login  了。

仔细的在这个档案列出可用的 terminal ,  可使从 modem  连的使用者或经由网路来的其它的使用者比较不容易取得 superuser  的权力 . 



/etc/services 

/etc/shell 

里面就记录著可以用的 login shell .  还有一点 ,  那就是这个档的记录会在使用 chsh  时做为参考 ,  唯有被列在这里的 shell ,  使用 chsh  时才会出现这些 shell  可选 



/etc/sudoers 

 在一个不是很复杂的系统中 ,  也许一个 System Administrator  就可以管理所有的事情 .  但一但系统提供的服务变多 ,  系统管理的工作也随之变得沉重 , sudo  可以让一个普通的 user  变成 superuser , 这样一来 ,  一个系统的某些工作 , 就可以分配给这些 superusers 来做  .  以减轻负担 ./etc/sudoers  就是记录著那些人可以用 superuser 的身份来执行一些工作 ,  这个档案的格式如下 :

Cmnd alias specification 

Cmnd_Alias SHUTDOWN=/sbin/halt,/sbin/shutdown 

User specification 

root ALL=ALL 
jhhsu ALL=ALL 
emotion ALL=ALL,!SHUTDOWN 

在这个例子当中 , jhhsu  可以执行 root  所有的命令 , emotion  除了 halt
及 shutdown  不能执行以外 ,  其它 root  能执行的命令他都能执行 . 

这个档案有一个专属的 editor  叫 visudo  可来编辑 /etc/sudoer  这个档案
在编辑完这个档案之后 , jhhsu  就可以用 sudo.bin  这个命令转换成superuser  来做原来只有 superuser  才能做的事 .  而关于使用 sudo.bin 有一个记录档 ,  在 /var/adm/sudo.log ,  里面记录著谁在什么时候利用sudo  下了那些指令 .  顺便一提的是 :  利用下面这个命令可抓出那些人转换成 superuser  但却没有成功



grep "FAILED SU" /var/adm/messages/etc/utmp :  从 utmp  中可以
知道现在有谁正在用系统  .  当使用者 logout  之后 , 
init (  很重要的 process , 以后有时间将为各位介绍 )  就去把 logout 
的使用者从 /etc/utmp  中去掉 . 
实际上 , utmp  每个 record  是像这样的一个结构 : 

```c#
struct utmp { 
short ut_type; /* type of login */ 
pid_t ut_pid; /* pid of process */ 
char ut_line[12]; /* devicename of tty -"/dev/" */ 
char ut_id[2]; /* init id or abbrev. ttyname */ 

time_t ut_time; /* logintime */ 
char ut_user[8]; /* username, not null-term */ 
char ut_host[16]; /* hostname for remote login */ 
long ut_addr; /* IP addr of remote host */ 
}; 
了解这个档案 ,  进而去修改 ,  可以做出许多有趣的事 ......:P 
```



/etc/wtmp 

 wtmp  是一个 login data base ,  有许多的指令会用到这个档 ,  像 last , sessreg , who  等

这个档案格式与 utmp  大致相同 ,  只是多了 shutdown  及 reboot  这
个记录 ,  指出系统的 shutdown  或 reboot ,  及一个空的 user name 
指出在相关 terminal  的 logout .  /etc/wtmp  的记录是慢慢的附加上去的 ,  也就是说 ,  这个档案会越变越大 ,  虽然变大的速度并不会太快 ,  但一但到了某种程度大小的话System Administrator  应该要考虑砍掉部份 .  下面是用 last  这个指令所得到的部份内容 : 

bbs tty1 Tue Nov 29 19:09 - 19:09 (00:00) 
root tty1 Tue Nov 29 19:08 - 19:09 (00:00) 
root tty1 Tue Nov 29 19:07 - 19:07 (00:00) 
runlevel ~ Tue Nov 29 19:07 
reboot ~ Tue Nov 29 19:07 



/etc/zprofile : link  到 /etc/profile 















/etc/rc.d文件夹

It contains scripts to used to control the starting, stopping and restarting of daemons.

rc指run commands
