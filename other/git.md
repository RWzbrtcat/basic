# Git 使用方法总结

## 配置

```bash
# 设置用户名
git config --global user.name "Your Name"

# 设置邮箱
git config --global user.email "your@email.com"

# 查看配置
git config --list
```

## 初始化与克隆

```bash
# 初始化仓库
git init
# 示例：git init my-project

# 克隆远程仓库
git clone <url>
# 示例：git clone https://github.com/user/repo.git
```

## 基本工作流

```bash
# 查看状态
git status
# 示例：git status

# 添加文件到暂存区
git add <file>
# 示例：git add index.html

# 添加所有改动
git add .
# 示例：git add .

# 提交改动
git commit -m "message"
# 示例：git commit -m "fix: 修复登录页面样式"

# 查看提交历史
git log
# 示例：git log --oneline -10
```

## 分支操作

```bash
# 查看分支
git branch
# 示例：git branch -a

# 创建分支
git branch <branch-name>
# 示例：git branch feature-login

# 切换分支
git checkout <branch-name>
# 示例：git checkout feature-login

# 创建并切换分支
git checkout -b <branch-name>
# 示例：git checkout -b feature-payment

# 删除分支
git branch -d <branch-name>
# 示例：git branch -d feature-login

# 强制删除未合并的分支
git branch -D <branch-name>
# 示例：git branch -D feature-old
```

## 合并与变基

```bash
# 合并分支
git merge <branch>
# 示例：git merge feature-login

# 变基
git rebase <branch>
# 示例：git rebase main

# 交互式变基（合并最近 N 个提交）
git rebase -i HEAD~<n>
# 示例：git rebase -i HEAD~3
```

## 远程仓库

```bash
# 查看远程仓库
git remote -v

# 添加远程仓库
git remote add <name> <url>
# 示例：git remote add origin https://github.com/user/repo.git

# 推送到远程
git push <remote> <branch>
# 示例：git push origin main

# 首次推送并设置上游
git push -u origin <branch>
# 示例：git push -u origin feature-login

# 拉取远程更新
git pull <remote> <branch>
# 示例：git pull origin main

# 只拉取不合并
git fetch <remote>
# 示例：git fetch origin

# 强制推送（谨慎使用）
git push --force-with-lease
```

## 撤销与回退

```bash
# 撤销工作区修改
git checkout -- <file>
# 示例：git checkout -- index.html

# 取消暂存
git reset HEAD <file>
# 示例：git reset HEAD index.html

# 回退到指定提交（保留修改）
git reset <commit>
# 示例：git reset HEAD~1

# 回退到指定提交（丢弃修改）
git reset --hard <commit>
# 示例：git reset --hard a1b2c3d

# 撤回某次提交（生成反向提交）
git revert <commit>
# 示例：git revert a1b2c3d
```

## 暂存工作现场

```bash
# 暂存修改
git stash
# 示例：git stash save "临时保存登录功能修改"

# 查看暂存列表
git stash list

# 恢复最近暂存
git stash pop

# 恢复暂存但不删除
git stash apply
# 示例：git stash apply stash@{0}

# 删除暂存
git stash drop stash@{0}
```

## 标签

```bash
# 创建标签
git tag <tag-name>
# 示例：git tag v1.0.0

# 创建带注释的标签
git tag -a <tag-name> -m "message"
# 示例：git tag -a v1.0.0 -m "正式发布 v1.0.0"

# 推送标签
git push origin <tag-name>
# 示例：git push origin v1.0.0

# 推送所有标签
git push origin --tags
```

## 差异比较

```bash
# 查看工作区改动
git diff

# 查看暂存区改动
git diff --staged

# 比较两个分支
git diff <branch1>..<branch2>
# 示例：git diff main..feature-login

# 查看某个文件的改动历史
git log -p <file>
# 示例：git log -p src/app.js
```

## Cherry-pick

```bash
# 将某个提交应用到当前分支
git cherry-pick <commit>
# 示例：git cherry-pick a1b2c3d
```

## 清理

```bash
# 清除未跟踪的文件（dry-run 预览）
git clean -n

# 清除未跟踪的文件和目录
git clean -fd
```
