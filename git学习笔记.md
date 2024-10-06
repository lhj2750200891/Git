# 一、git基础命令

## git  init

​	直接执行就可以，创建.git文件在相应目录下

## git status

​	查看当前文件夹下文件的状态

## git add file_name

​	将当前文件夹下有修改变动的文件做备份

## git add .

​	将当前文件夹下有修改变动的文件做备份，此处的 . 表示添加全部

## git commit -m "xxx"

​	对备份的文件进行注释说明，xxx为说明内容

## git log

​	查看已经备份的文件，以及其版本号

## git reflog 

​	查找之前的版本号

​	![image-20241007014216283](C:\Users\lhj2750200891\AppData\Roaming\Typora\typora-user-images\image-20241007014216283.png)

## git reset --hard xxx

​	回滚到之前的文件版本，xxx为文件的版本号

# 二、分支

## git branch 

​	查看分支

## git branch xxx

​	创建分支，xxx为分支名称

## git checkout xxx

​	切换分支，xxx表示分支名

## git merge xxx

​	分支合并，A合并到B，则先需要切换到分支B，相反也成立，xxx为将要合并的分支

## git branch -d xxx

​	删除分支，xxx代表将要删除的分支

# 三、GitHub代码托管

## git remote add origin xxx

​	给远程仓库起别名，代表将本地代码推送到github中，xxx为GitHub中的ssh或http地址，origin为别名，可任意取

## git remote rm xxx

​	删除别名，xxx表示之前用过的或者已经存在的别名

## git branch -M main

​	表示创建分支

## git push -u origin main

​	向远程仓库推送代码，表示把代码放到新建的分支main中

## git clone xxx

克隆远程仓库的代码，xxx代表远程仓库代码的ssh或http地址，克隆下的代码，看不到分支名称，但是可以根据已有的分支直接切换

## 注意：

​	在克隆时，别名也已经克隆出来，所以在提交到远程仓库时，直接使用之前的别名就好，无需再起别名

