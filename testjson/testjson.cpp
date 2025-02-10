#include "json.hpp"
using json = nlohmann::json;

#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;

// json序列化 普通序列化
void fun1()
{
    json js;
    js["msg_type"] = 2;
    js["from"] = "zhang san";
    js["to"] = "li si";
    js["msg"] = "hello world";

    cout << js << endl;
}

// json反序列化 
string fun1f()
{
    json js;
    js["msg_type"] = 2;
    js["from"] = "zhang san";
    js["to"] = "li si";
    js["msg"] = "hello world";

    string sendBuf = js.dump();
    return sendBuf;
}

// json序列化 vector序列化
void fun2()
{
    json js;
    // 直接序列化一个vector容器
    vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(5);
    js["list"] = vec;
    // 直接序列化一个map容器
    map<int, string> m;
    m.insert({1, "黄山"});
    m.insert({2, "华山"});
    m.insert({3, "泰山"});
    js["path"] = m;

    string sendBuf = js.dump(); // json序列化 转成字符串
    cout << js << endl;
}

// json反序列化
string fun2f()
{
    json js;
    // 直接序列化一个vector容器
    vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(5);
    js["list"] = vec;
    // 直接序列化一个map容器
    map<int, string> m;
    m.insert({1, "黄山"});
    m.insert({2, "华山"});
    m.insert({3, "泰山"});
    js["path"] = m;

    string sendBuf = js.dump(); // json序列化 转成字符串
    return sendBuf;
}
int main()
{
    fun1();

    string recvBuf = fun1f();
    json buf = json::parse(recvBuf); // 反序列化 得到数据对象
    cout << buf["msg_type"] << endl;
    return 0;
}