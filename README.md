# FileSpliter
你是否遇到过上传文件时遇到文件大小的限制？

这个工具可以轻易帮你解决这个问题。

你可以用这个工具将大文件分为若干小文件，然后自行分片上传，最后使用该工具将小文件合并成一个文件。

## 使用方法
1. [在这里](https://github.com/GoodenoughPhysicsLab/FileSpliter/releases)下载文件
2. 运行命令
```
FileSpliter -h
```
或者
```
FileSpliter --help
```
你就可以获取使用帮助, 也可以看README获得帮助

查看版本：
```
FileSpliter --version
```

## 示例
1. 将文件拆分成小文件
```
FileSpliter /YOUR/FILE/PATH -o /YOUR/OUTPUT/DIR/PATH
```
此时每个输出的小文件默认为1MB(1024KB)

2. 将小文件合并成一个文件
```
FileSpliter --integrate /YOUR/OUTPUT/DIR/PATH
```

3. 指定小文件大小
```
FileSpliter /YOUR/FILE/PATH -o /YOUR/OUTPUT/DIR/PATH --split-size 2000
```
此时每个输出的小文件大小为2000KB
