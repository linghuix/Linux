# git-usage

> [] - 根据情况改变

## 定义用户

```
git config --global user.email "linghui10@foxmail.com"
git config --global user.name "linghuix"
```

## 本地仓库基本操作

```
git init
git status 
git log --graph 
git branch [branch name]
```

### Work direatory to Stage

```
git diff [file]               比较这两个地方的文件的不同
git add [file]
git rm [file]
git checkout -- [file]      to un Work direatory 
git reset HEAD <file>..."   to unstage
```

### Stage to Repository

```
git commit -m [message]     to commit
```

##  Repository to Repository 版本回退

```
git reset [commit-id] --hard      工作区文件全部变为两一个版本的
git reset [commit-id] --soft      工作区文件不变,所有改动的文件都待commit
```

## 本地仓库与远程仓库的绑定

```
ssh:  git remote add [origin] [git@github.com:linghuix/Linux.git]
http: git remote add [origin] [https://github.com/linghuix/Linux.git]
git remote -v       查看远程地址信息
git push -f --set-upstream [origin] [master]
```







## error

error: src refspec master does not match any
引起该错误的原因是，目录中没有文件，空目录是不能提交上去的

Merge made by the 'recursive' strategy
git合并2个分支的策略


## other

[github ssh加密方式的配置](https://help.github.com/en/articles/connecting-to-github-with-ssh)

ssh的秘钥一般放在~/.ssh的隐藏文件中，~/.ssh/中的public秘钥，复制到git服务其中

注意，一对ssh公钥与私钥只能绑定一个仓库！！！！

