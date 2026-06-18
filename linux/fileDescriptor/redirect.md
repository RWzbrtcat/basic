# 重定向

首先了解一下文件描述符：
1. 0 = 标准输入（stdin）
2. 1 = 标准输出（stdout）
3. 2 = 标准错误（stderr）

## 一、基本重定向操作符

### 1. `>`重定向标准输出

```bash
# 将 stdout 写入文件（覆盖）
command > output.txt

# 将 stdout 追加文件
command > output.txt
```

### 2. `2>`重定向标准错误

```bash
# 将 stderr 写入文件（覆盖）
command 2> error.txt

# 将 stderr 追加文件
command 2> error.txt
```

### 3. `&>`同时重定向 stdout 和 stderr

```bash
# 将 stdout 和 stderr 都写入同一个文件
command &> output.txt

# 追加写入文件
command &>> output.txt
```

### 4. `>`和`2>&1`组合

```bash
# 将 stdout 重定向到文件，stderr 重定向到 stdout（即也重定向到文件）
# 必须先重定向 stdout，再让 stderr 跟随 stdout
command > output 2>&1

# 错误示范
command 2>&1 > output.txt
```


## 二、丢弃输出

### 1. 丢弃标准输出

```bash
# stdout 消失，stderr 仍显示在屏幕
command > /dev/null
```

### 2. 丢弃标准错误

```bash
# stderr 消失，stdout 仍显示在终端
command 2> /dev/null
```

### 3. 丢弃所有输出

```bash
# 方法1 - 分别重定向
command > /dev/null 2> /dev/null

# 方法2 - 合并重定向
command > /dev/null 2>&1

# 方法3 - 使用 &>
command &> /dev/null
```


## 三、管道和重定向组合

### 1. 传递标准输出给管道

```bash
command | grep "pattern"
```

### 2. 传递 stderr 和 stdour 给管道

```bash
command 2>&1 | grep "pattern"
```

### 3. 管道和文件保存

```bash
# stdout 进入管道，stderr 保存到文件
command 2> error.log | grep "pattern"

# stdout 保存到文件，stderr 进入管道
command > output.txt 2>&1 | grep "pattern"
```



