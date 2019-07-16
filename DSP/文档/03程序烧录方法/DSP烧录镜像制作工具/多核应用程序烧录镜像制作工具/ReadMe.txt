使用方法：
1.将多核镜像拷贝到工具所在目录
2.打开CMD工具，进入工具所在目录
3.运行工具，在终端中输入：
b2bin.exe xxx0.hex xxx1.hex app.bin

命令说明：
b2bin.exe 为转换工具
xxx0.hex xxx1.hex为各个核通过编译生成的boot表格式的输出文件，必须按照核的顺序由低到高输入
app.bin 为输出的文件