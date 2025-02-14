#include "chatservice.hpp"
#include "public.hpp"
#include <string>
#include <muduo/base/Logging.h>

using namespace std;
using namespace muduo;

// 获取单例对象接口函数
ChatService *ChatService::instance()
{
    static ChatService service;
    return &service;
}

// 注册消息和对应的Handler回调操作
ChatService::ChatService()
{
    _msgHandlerMap.insert({LOGIN_MSG, std::bind(&ChatService::login, this, _1, _2, _3)});
    _msgHandlerMap.insert({REG_MSG, std::bind(&ChatService::reg, this, _1, _2, _3)});
}

// 获取消息对应的处理器
MsgHandler ChatService::getHandler(int msgid)
{
    // 记录错误日志，msgid没有对应的事件处理回调
    if (_msgHandlerMap.find(msgid) == _msgHandlerMap.end())
    {
        // 返回一个默认的处理器，空操作
        return [=](const TcpConnectionPtr &conn, json &js, Timestamp)
        {
            LOG_ERROR << "msgid:" << msgid << " can not find handler!";
        };
    }
    else
    {
        return _msgHandlerMap[msgid];
    }
}

// 处理登录业务
void ChatService::login(const TcpConnectionPtr &conn, json &js, Timestamp time)
{
    LOG_INFO << "do login business...";
}

// 处理注册业务
void ChatService::reg(const TcpConnectionPtr &conn, json &js, Timestamp time)
{
    LOG_INFO << "do reg business...";
}
