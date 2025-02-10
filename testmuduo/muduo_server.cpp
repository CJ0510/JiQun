/*
TcpServer: 用于编写服务器端程序
TcpClient: 用于编写客户端程序

底层：epoll+线程池
好处：把网络I/O和业务处理分开，提高了程序的可维护性
业务处理：用户的连接和断开 + 用户的数据读写
*/

#include <muduo/net/TcpServer.h>
#include <muduo/net/EventLoop.h>
#include <functional>
#include <iostream>
using namespace std;
using namespace muduo;
using namespace muduo::net;
using namespace placeholders;

/*muduo库服务端程序
1、组合TcpServer对象
2、创建EventLoop事件循环对象的指针
3、明确TcpServer构造函数需要什么参数，EventLoop*，端口号，IP地址，输出ChatServer的构造函数
4、在当前服务器类的构造函数当中，注册处理连接的回调函数和处理读写的回调函数
5、设置服务器端的线程数量
*/
class ChatServer
{
public:
    ChatServer(EventLoop *loop,               // 事件循环
               const InetAddress &listenAddr, // IP地址和端口号
               const string &nameArg)         // 服务器名称
        : _server(loop, listenAddr, nameArg), _loop(loop)
    {
        // 给服务器注册用户连接的创建和断开回调
        _server.setConnectionCallback(std::bind(&ChatServer::onConnection, this, _1));
        // 给服务器注册用户读写事件回调
        _server.setMessageCallback(std::bind(&ChatServer::onMessage, this, _1, _2, _3));

        // 设置服务器端的线程数量 1个I/O线程   3个worker线程
        _server.setThreadNum(4);
    }

    // 开启事件循环
    void start()
    {
        _server.start();
    }

private:
    // 处理用户连接创建和断开的回调
    void onConnection(const TcpConnectionPtr &conn)
    {
        if (conn->connected())
        {
            cout << conn->peerAddress().toIpPort() << " -> " << conn->localAddress().toIpPort() << " state:online" << endl;
        }
        else
        {
            cout << conn->peerAddress().toIpPort() << " -> " << conn->localAddress().toIpPort() << " state:offline" << endl;
            conn->shutdown(); // close(fd)
                              // _loop->quit();
        }
    }
    // 专门处理用户的读写事件
    void onMessage(const TcpConnectionPtr &conn, // 连接
                   Buffer *buffer,               // 缓冲区
                   Timestamp time)               // 接收到数据的时间信息
    {
        string buf = buffer->retrieveAllAsString();
        cout << "recv data:" << buf << " time:" << time.toFormattedString() << endl;
        conn->send(buf);
    }
    TcpServer _server;
    EventLoop *_loop;
};

int main()
{
    // 创建事件循环对象
    EventLoop loop;
    // 创建服务器对象
    InetAddress addr("127.0.0.1", 6000);
    ChatServer server(&loop, addr, "ChatServer");

    // 开启事件循环
    server.start();
    // 开启事件循环
    loop.loop();
}