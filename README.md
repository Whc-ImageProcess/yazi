# yazi
c++ framework

## 测试脚本

make plugin

make

然后去修改config/main.ini配置文件

// 这一步需要开启root权限
netstat -an | grep :8080

ps axj | grep main

// python测试代码
python3 client/python/bench.py

// 查看cpu核心数
cat /proc/cpuinfo | grep processor

cat /proc/meminfo

## makefile

### shell函数

shell函数也不像其它的函数。顾名思义，它的参数应该就是操作系统Shell的命令。它和反引号“`”是相同的功能。这就是说，shell函数把执行操作系统命令后的输出作为函数返回。于是，我们可以用操作系统命令以及字符串处理命令awk，sed等等命令来生成一个变量，如：

contents := $(shell cat foo)
files := $(shell echo *.c)
注意，这个函数会新生成一个Shell程序来执行命令，所以你要注意其运行性能，如果你的Makefile中有一些比较复杂的规则，并大量使用了这个函数，那么对于你的系统性能是有害的。特别是Makefile的隐式规则可能会让你的shell函数执行的次数比你想像的多得多。

### patsubst

$(patsubst <pattern>,<replacement>,<text>)
名称：模式字符串替换函数。

功能：查找 <text> 中的单词（单词以“空格”、“Tab”或“回车”“换行”分隔）是否符合模式 <pattern> ，如果匹配的话，则以 <replacement> 替换。这里， <pattern> 可以包括通配符 % ，表示任意长度的字串。如果 <replacement> 中也包含 % ，那么， <replacement> 中的这个 % 将是 <pattern> 中的那个 % 所代表的字串。（可以用 \ 来转义，以 \% 来表示真实含义的 % 字符）

返回：函数返回被替换过后的字符串。

示例：

$(patsubst %.c,%.o,x.c.c bar.c)
把字串 x.c.c bar.c 符合模式 %.c 的单词替换成 %.o ，返回结果是 x.c.o bar.o

备注：这和我们前面“变量章节”说过的相关知识有点相似。如 $(var:<pattern>=<replacement>;) 相当于 $(patsubst <pattern>,<replacement>,$(var)) ，而 $(var: <suffix>=<replacement>) 则相当于 $(patsubst %<suffix>,%<replacement>,$(var)) 。

例如有:

objects = foo.o bar.o baz.o，
那么， $(objects:.o=.c) 和 $(patsubst %.o,%.c,$(objects)) 是一样的。

### filter

$(filter <pattern...>,<text>)
名称：过滤函数

功能：以 <pattern> 模式过滤 <text> 字符串中的单词，保留符合模式 <pattern> 的单词。可以有多个模式。

返回：返回符合模式 <pattern> 的字串。

示例：

sources := foo.c bar.c baz.s ugh.h
foo: $(sources)
    cc $(filter %.c %.s,$(sources)) -o foo
$(filter %.c %.s,$(sources)) 返回的值是 foo.c bar.c baz.s 。

```shell
root@VM5811-oslab:~/vsCodeProjects/vlabRepository/yazi# make
Makefile:6: SRCS is ./engine/Work.cpp ./engine/Workflow.cpp ./engine/PluginHelper.cpp ./json/Parser.cpp ./json/Json.cpp ./server/Server.cpp ./socket/ServerSocket.cpp ./socket/SocketHandler.cpp ./socket/Socket.cpp ./socket/ClientSocket.cpp ./socket/EventPoller.cpp ./task/EchoTask.cpp ./task/WorkTask.cpp ./task/PingTask.cpp ./thread/Task.cpp ./thread/Condition.cpp ./thread/Mutex.cpp ./thread/TaskDispatcher.cpp ./thread/ThreadPool.cpp ./thread/AutoLock.cpp ./thread/WorkerThread.cpp ./thread/Thread.cpp ./utility/IniFile.cpp ./utility/Logger.cpp ./utility/System.cpp ./xml/Document.cpp ./xml/Element.cpp
Makefile:10: OBJS is  ./engine/Work.o  ./engine/Workflow.o  ./engine/PluginHelper.o  ./json/Parser.o  ./json/Json.o  ./server/Server.o  ./socket/ServerSocket.o  ./socket/SocketHandler.o  ./socket/Socket.o  ./socket/ClientSocket.o  ./socket/EventPoller.o  ./task/EchoTask.o  ./task/WorkTask.o  ./task/PingTask.o  ./thread/Task.o  ./thread/Condition.o  ./thread/Mutex.o  ./thread/TaskDispatcher.o  ./thread/ThreadPool.o  ./thread/AutoLock.o  ./thread/WorkerThread.o  ./thread/Thread.o  ./utility/IniFile.o  ./utility/Logger.o  ./utility/System.o  ./xml/Document.o  ./xml/Element.o
Makefile:14: CFLAGS is -g -O2 -Wall -Werror -Wno-unused -ldl -fPIC
Makefile:19: INCLUDE is -I ./engine -I ./json -I ./server -I ./socket -I ./task -I ./thread -I ./userTest -I ./utility -I ./xml
g++ -g -O2 -Wall -Werror -Wno-unused -ldl -fPIC -I ./engine -I ./json -I ./server -I ./socket -I ./task -I ./thread -I ./userTest -I ./utility -I ./xml -c main.cpp -o main.o
g++ -g -O2 -Wall -Werror -Wno-unused -ldl -fPIC -I ./engine -I ./json -I ./server -I ./socket -I ./task -I ./thread -I ./userTest -I ./utility -I ./xml -c engine/Work.cpp -o engine/Work.o
g++ -g -O2 -Wall -Werror -Wno-unused -ldl -fPIC -I ./engine -I ./json -I ./server -I ./socket -I ./task -I ./thread -I ./userTest -I ./utility -I ./xml -c engine/Workflow.cpp -o engine/Workflow.o
g++ -g -O2 -Wall -Werror -Wno-unused -ldl -fPIC -I ./engine -I ./json -I ./server -I ./socket -I ./task -I ./thread -I ./userTest -I ./utility -I ./xml -c engine/PluginHelper.cpp -o engine/PluginHelper.o
g++ -g -O2 -Wall -Werror -Wno-unused -ldl -fPIC -I ./engine -I ./json -I ./server -I ./socket -I ./task -I ./thread -I ./userTest -I ./utility -I ./xml -c json/Parser.cpp -o json/Parser.o
g++ -g -O2 -Wall -Werror -Wno-unused -ldl -fPIC -I ./engine -I ./json -I ./server -I ./socket -I ./task -I ./thread -I ./userTest -I ./utility -I ./xml -c json/Json.cpp -o json/Json.o
g++ -g -O2 -Wall -Werror -Wno-unused -ldl -fPIC -I ./engine -I ./json -I ./server -I ./socket -I ./task -I ./thread -I ./userTest -I ./utility -I ./xml -c server/Server.cpp -o server/Server.o
g++ -g -O2 -Wall -Werror -Wno-unused -ldl -fPIC -I ./engine -I ./json -I ./server -I ./socket -I ./task -I ./thread -I ./userTest -I ./utility -I ./xml -c socket/ServerSocket.cpp -o socket/ServerSocket.o
g++ -g -O2 -Wall -Werror -Wno-unused -ldl -fPIC -I ./engine -I ./json -I ./server -I ./socket -I ./task -I ./thread -I ./userTest -I ./utility -I ./xml -c socket/SocketHandler.cpp -o socket/SocketHandler.o
g++ -g -O2 -Wall -Werror -Wno-unused -ldl -fPIC -I ./engine -I ./json -I ./server -I ./socket -I ./task -I ./thread -I ./userTest -I ./utility -I ./xml -c socket/Socket.cpp -o socket/Socket.o
g++ -g -O2 -Wall -Werror -Wno-unused -ldl -fPIC -I ./engine -I ./json -I ./server -I ./socket -I ./task -I ./thread -I ./userTest -I ./utility -I ./xml -c socket/ClientSocket.cpp -o socket/ClientSocket.o
g++ -g -O2 -Wall -Werror -Wno-unused -ldl -fPIC -I ./engine -I ./json -I ./server -I ./socket -I ./task -I ./thread -I ./userTest -I ./utility -I ./xml -c socket/EventPoller.cpp -o socket/EventPoller.o
g++ -g -O2 -Wall -Werror -Wno-unused -ldl -fPIC -I ./engine -I ./json -I ./server -I ./socket -I ./task -I ./thread -I ./userTest -I ./utility -I ./xml -c task/EchoTask.cpp -o task/EchoTask.o
g++ -g -O2 -Wall -Werror -Wno-unused -ldl -fPIC -I ./engine -I ./json -I ./server -I ./socket -I ./task -I ./thread -I ./userTest -I ./utility -I ./xml -c task/WorkTask.cpp -o task/WorkTask.o
g++ -g -O2 -Wall -Werror -Wno-unused -ldl -fPIC -I ./engine -I ./json -I ./server -I ./socket -I ./task -I ./thread -I ./userTest -I ./utility -I ./xml -c task/PingTask.cpp -o task/PingTask.o
g++ -g -O2 -Wall -Werror -Wno-unused -ldl -fPIC -I ./engine -I ./json -I ./server -I ./socket -I ./task -I ./thread -I ./userTest -I ./utility -I ./xml -c thread/Task.cpp -o thread/Task.o
g++ -g -O2 -Wall -Werror -Wno-unused -ldl -fPIC -I ./engine -I ./json -I ./server -I ./socket -I ./task -I ./thread -I ./userTest -I ./utility -I ./xml -c thread/Condition.cpp -o thread/Condition.o
g++ -g -O2 -Wall -Werror -Wno-unused -ldl -fPIC -I ./engine -I ./json -I ./server -I ./socket -I ./task -I ./thread -I ./userTest -I ./utility -I ./xml -c thread/Mutex.cpp -o thread/Mutex.o
g++ -g -O2 -Wall -Werror -Wno-unused -ldl -fPIC -I ./engine -I ./json -I ./server -I ./socket -I ./task -I ./thread -I ./userTest -I ./utility -I ./xml -c thread/TaskDispatcher.cpp -o thread/TaskDispatcher.o
g++ -g -O2 -Wall -Werror -Wno-unused -ldl -fPIC -I ./engine -I ./json -I ./server -I ./socket -I ./task -I ./thread -I ./userTest -I ./utility -I ./xml -c thread/ThreadPool.cpp -o thread/ThreadPool.o
g++ -g -O2 -Wall -Werror -Wno-unused -ldl -fPIC -I ./engine -I ./json -I ./server -I ./socket -I ./task -I ./thread -I ./userTest -I ./utility -I ./xml -c thread/AutoLock.cpp -o thread/AutoLock.o
g++ -g -O2 -Wall -Werror -Wno-unused -ldl -fPIC -I ./engine -I ./json -I ./server -I ./socket -I ./task -I ./thread -I ./userTest -I ./utility -I ./xml -c thread/WorkerThread.cpp -o thread/WorkerThread.o
g++ -g -O2 -Wall -Werror -Wno-unused -ldl -fPIC -I ./engine -I ./json -I ./server -I ./socket -I ./task -I ./thread -I ./userTest -I ./utility -I ./xml -c thread/Thread.cpp -o thread/Thread.o
g++ -g -O2 -Wall -Werror -Wno-unused -ldl -fPIC -I ./engine -I ./json -I ./server -I ./socket -I ./task -I ./thread -I ./userTest -I ./utility -I ./xml -c utility/IniFile.cpp -o utility/IniFile.o
g++ -g -O2 -Wall -Werror -Wno-unused -ldl -fPIC -I ./engine -I ./json -I ./server -I ./socket -I ./task -I ./thread -I ./userTest -I ./utility -I ./xml -c utility/Logger.cpp -o utility/Logger.o
g++ -g -O2 -Wall -Werror -Wno-unused -ldl -fPIC -I ./engine -I ./json -I ./server -I ./socket -I ./task -I ./thread -I ./userTest -I ./utility -I ./xml -c utility/System.cpp -o utility/System.o
g++ -g -O2 -Wall -Werror -Wno-unused -ldl -fPIC -I ./engine -I ./json -I ./server -I ./socket -I ./task -I ./thread -I ./userTest -I ./utility -I ./xml -c xml/Document.cpp -o xml/Document.o
g++ -g -O2 -Wall -Werror -Wno-unused -ldl -fPIC -I ./engine -I ./json -I ./server -I ./socket -I ./task -I ./thread -I ./userTest -I ./utility -I ./xml -c xml/Element.cpp -o xml/Element.o
g++ -o main main.o engine/Work.o engine/Workflow.o engine/PluginHelper.o json/Parser.o json/Json.o server/Server.o socket/ServerSocket.o socket/SocketHandler.o socket/Socket.o socket/ClientSocket.o socket/EventPoller.o task/EchoTask.o task/WorkTask.o task/PingTask.o thread/Task.o thread/Condition.o thread/Mutex.o thread/TaskDispatcher.o thread/ThreadPool.o thread/AutoLock.o thread/WorkerThread.o thread/Thread.o utility/IniFile.o utility/Logger.o utility/System.o xml/Document.o xml/Element.o -g -O2 -Wall -Werror -Wno-unused -ldl -fPIC -I ./engine -I ./json -I ./server -I ./socket -I ./task -I ./thread -I ./userTest -I ./utility -I ./xml -lpthread -std=c++11
```
