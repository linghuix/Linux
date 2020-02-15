
# vim

> 基于命令行的,界面舒适的，可自定义的超级强大编辑器

## 基本功能

1. 配置目录

```
vim的配置文件
/etc/vim/vimrc

插件安装目录
下载的文件放入sr/share/vim/vim80相应的文件夹就行了

```

2. 基本工作模式 

> 普通模式, 插入模式(编辑模式), 命令行模式
> 普通模式一般用于浏览文件, 执行一些快捷键定义的功能;
> 插入模式, 是最常用的模式, 用于输入文字, 编写代码;
> 命令行模式, 用于执行命令, 配置vim的运行环境, 保存文件等功能

打开文件命令
vim filename1,filename2,...

默认进入普通模式。
按"i"进入插入模式。在插入模式中按Esc可以回到普通模式。
按":"进入命令行模式, 命令执行完毕后自动返回普通模式。

3. 普通模式下的基本功能

光标 : kjhl 上下左右, NG 跳转到N行, 方向键 上下左右, shfit+方向键 横向沿单词移动 纵向翻页, w/b 使光标向前/后跳过一个单词
黏贴 : p, ctrl+V
剪切 : Ndd 剪切包括光标所在行以下的N行，Ndw 剪切N个单词yank N words, x 剪切一个字符, d$ 光标所在处到行尾的所有字符 d=delete
复制 : Nyy, Nyw
撤销 : u 可以撤销上一步的操作，
恢复 : Ctrl+r 可恢复上一步被撤销的操作;
插入字符并切换到插入模式 : i,a----在光标的前,后插入字符命令(i=insert,a=append),cw 进入插入模式同时删除光标所处单词 (c=change) 
多屏切换 : Ctrl+w+w

4. 命令行模式下的基本功能

: set nu 显示行号 
：q!退出，强制退出
：w写入保存
：x 保存退出
：set showcmd 显示输入的部分命令
:!cmd 执行外部shell命令. 
: 上下方向键  调出历史命令

> 分屏功能是我青睐 vim 的理由之一, 可以无限分屏, 使用非常方便

横向分屏 : split filename 无文件名,默认分屏当前打开并激活的文件; 文件名不存在,则新建一个文件并打开
竖向分屏 : vsplit filename 同上,只是分屏方向不同
分屏窗口切换 : ctrl+w+w(普通模式下)

> 不同文件的窗口切换比较复杂
> vim 多文件处理编辑涉及到的概念：window、buffer、tab（不常用）

buffer 即为文件加载的缓存区，修改后保存到磁盘就可以实现文件的修改操作
ctrl+w+w(普通模式下) 按顺序依次切换
:buf 2 选择第二个文件缓存区
:bn 下一个 buffer
:bp 上一个 buffer
:bd 关闭当前 buffer, 需要先保存文件

> 解决乱码问题
:set fileencoding   查看现在文本的编码
:set fenc=编码      以指定的编码格式保存文本
:set enc=编码       以指定的编码显示文本
:edit ++enc=编码    重新以cp936的编码方式加载文件

解决fileencoding为latin1 简体Windows所使用（代码页cp936）的乱码问题
:edit ++enc=cp936 重新以cp936的编码方式加载文件.
:set fileencoding 查看编码方式是否改变
:set fenc=utf-8 以utf-8编码，下次打开就不需要这么麻烦了


## 高级功能描述

### 查找命令 普通模式

1. 直接输入/string, ?string -----从光标所在处向后/向前查找相应的字符串的命令

执行上述命令一次后，再按n/N可以实现再次查找
按下/后按上下键意识调出历史命令

2. 正则表达式

命令模式中
：%s/oldstring/newstring 在整个文章中用新的字符串替换旧的字符串
：10,20s/oldstring/newstring/g 从10行到20行实现字符串替换

在输入/后，可以输入正则表达式进行字符串查找，为了区分string与正则表达式，需要在某些符号前加\转义字符
一直要写\就会很麻烦，所以vim提供了多种模式。
\m，magic，除了$ . * ^ 之外其他元字符都要加反斜杠
\v，verymagic不需要在符号前加\，比如{}，()，$ . * ^这些符号.但是d表示数字时还是要用\d

对匹配行操作(g表示全局,command有:d 删除 m 移动 t 拷贝 s 替换)     :[range]g/pattern/command
对未匹配的行操作                                        :[range]g！/pattern/command
对匹配的行作字符串替换                                  :[range]/pattern/newstring

举例：
查找回车                                                    `/\v\n`
`L"_LPAR"->wstring(L"_LPAR")                                 :%s/\v(L".{-}")/wstring(\1)/g`
删除m-n行内的空白行(g表示全局,d 删除 m 移动 t 拷贝 s 替换)  :m,ng/\v^$/d
空白行替换为d                                               `:m,ns/\v^$/d`
删除69-74行首的`//`      `:69,74s/\v^\/\//`
行首添加`//`			     `:69,74s/\v^/\/\/`

### 折叠方式
set fdm=XXX
manual          手工定义折叠
indent           更多的缩进表示更高级别的折叠
expr              用表达式来定义折叠
syntax           用语法高亮来定义折叠
diff                对没有更改的文本进行折叠
marker           对文中的标志折叠

zc      折叠
zC     对所在范围内所有嵌套的折叠点进行折叠
zo      展开折叠
zO     对所在范围内所有嵌套的折叠点展开
[z       到当前打开的折叠的开始处。
]z       到当前打开的折叠的末尾处。
zj       向下移动。到达下一个折叠的开始处。关闭的折叠也被计入。
zk      向上移动到前一折叠的结束处。关闭的折叠也被计入。

zf      创建折叠，比如在marker方式下：                  
         zf56G，创建从当前行起到56行的代码折叠；                  
         10zf或10zf+或zf10↓，创建从当前行起到后10行的代码折叠。                  
         10zf-或zf10↑，创建从当前行起到之前10行的代码折叠。                  
         在括号处zf%，创建从当前行起到对应的匹配的括号上去（（），{}，[]，<>等）。
 
zd      删除 (delete) 在光标下的折叠。
         仅当 'foldmethod' 设为 "manual" 或 "marker" 时有效。
 
zD     循环删除 (Delete) 光标下的折叠，即嵌套删除折叠。
         仅当 'foldmethod' 设为 "manual" 或 "marker" 时有效。
 
zE      除去 (Eliminate) 窗口里“所有”的折叠。
         仅当 'foldmethod' 设为 "manual" 或 "marker" 时有效。

### 配置文件设置
let Tlist_Show_One_File=1
let Tlist_Exit_OnlyWindow=1
let Tlist_Auto_Open=1
"let Tlist_Ctags_Cmd='/usr/bin/ctags'
"set foldcolumn=0
"set foldmethod=indent 
"set foldlevel=3 
"set foldenable              " 开始折叠
" 不要使用vi的键盘模式，而是vim自己的
set nocompatible
" 语法高亮
set syntax=on
" 去掉输入错误的提示声音
set noeb
" 在处理未保存或只读文件的时候，弹出确认
set confirm
" 自动缩进
set autoindent
set cindent
" Tab键的宽度
set tabstop=4
" 统一缩进为4
set softtabstop=4
set shiftwidth=4
" 不要用空格代替制表符
set noexpandtab
" 在行和段开始处使用制表符
set smarttab
" 显示行号
set number
" 历史记录数
set history=1000
"禁止生成临时文件
set nobackup
set noswapfile
"搜索忽略大小写
set ignorecase
"搜索逐字符高亮
set hlsearch
set incsearch
"行内替换
set gdefault
"编码设置
set enc=utf-8
set fencs=utf-8,ucs-bom,shift-jis,gb18030,gbk,gb2312,cp936
"语言设置
set langmenu=zh_CN.UTF-8
set helplang=cn
" 我的状态行显示的内容（包括文件类型和解码）
"set statusline=%F%m%r%h%w\ [FORMAT=%{&ff}]\ [TYPE=%Y]\ [POS=%l,%v][%p%%]\ %{strftime(\"%d/%m/%y\ -\ %H:%M\")}
"set statusline=[%F]%y%r%m%*%=[Line:%l/%L,Column:%c][%p%%]
" 总是显示状态行
set laststatus=2
" 命令行（在状态行下）的高度，默认为1，这里是2
set cmdheight=2
" 侦测文件类型
filetype on
" 载入文件类型插件
filetype plugin on
" 为特定文件类型载入相关缩进文件
filetype indent on
" 保存全局变量
set viminfo+=!
" 带有如下符号的单词不要被换行分割
set iskeyword+=_,$,@,%,#,-
" 字符间插入的像素行数目
set linespace=0
" 增强模式中的命令行自动完成操作
set wildmenu
" 使回格键（backspace）正常处理indent, eol, start等
set backspace=2
" 允许backspace和光标键跨越行边界
set whichwrap+=<,>,h,l
" 可以在buffer的任何地方使用鼠标（类似office中在工作区双击鼠标定位）
""set mouse=a
""set selection=exclusive
""set selectmode=mouse,key
" 通过使用: commands命令，告诉我们文件的哪一行被改变过
set report=0
" 在被分割的窗口间显示空白，便于阅读
set fillchars=vert:\ ,stl:\ ,stlnc:\
" 高亮显示匹配的括号
set showmatch
" 匹配括号高亮的时间（单位是十分之一秒）
set matchtime=1
" 光标移动到buffer的顶部和底部时保持3行距离
set scrolloff=3
" 为C程序提供自动缩进
set smartindent
" 高亮显示普通txt文件（需要txt.vim脚本）
au BufRead,BufNewFile *  setfiletype txt
set bg=dark

### 自定义快捷键
> vim 强大功能之一
> 可实现 自动插入代码段, 自动补全括号 等功能
:ino[remap] {lhs} {rhs}         mapmode-i             :ino :inoremap    insert 模式下的快捷键, nore表示没有递归 no recursion
:ln[oremap] {lhs} {rhs}         mapmode-l             :ln  :lnoremap    
:cno[remap] {lhs} {rhs}         mapmode-c             :cno :cnoremap    
                    Map the key sequence {lhs} to {rhs} for the modes
                    where the map command applies.  Disallow mapping of
                    {rhs}, to avoid nested and recursive mappings.  Often
                    used to redefine a command.  {not in Vi}

inoremap就只在插入(insert)模式下生效
vnoremap只在visual模式下生效
nnoremap就在normal模式下(狂按esc后的模式)生效

## 实用插件
> vim 强大功能之一

### autocomplete——自动补全

### taglist —— 显示函数跳转，需要先安装ctag

### omnicppcomplete —— C语言自动补全

### ctags

> 查看代码神器,匹敌source insight   
> 参考资料: 
>    https://linuxhint.com/vim_ctags/
>    https://www.cnblogs.com/feisky/archive/2012/02/07/2341932.html

ctags   sudo apt-get install ctags
1).Select Program Folder                选择代码目录
2).Create tags (ctags -R *)             生成tags文件
3).Configure Ctags (set tags=tags;/)    在vim中设定tags文件所在的目录
4).Searching tag by pattern             使用跳转快捷键

跳转方法:
ctrl+]
ctrl+T
:ts 显示有多个对应项 tags list

需要注意的是,必须在tags所在目录,或者子目录中打开文件,即执行vim命令的时候必须在上述所说的目录,否则vim是找不到对应的tags文件的

