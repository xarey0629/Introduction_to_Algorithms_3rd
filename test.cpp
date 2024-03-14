#include <iostream>
#include <sstream>
#include <string>
using namespace std;

int main()
{
    std::string input = "PUT:12&1";

    // 使用 stringstream 将字符串 input 转换为流
    std::stringstream ss(input);

    std::string command;
    int key, value;

    // 使用提取运算符从字符串中提取指令和键值
    getline(ss, command);
    ss.ignore(); // 忽略冒号
    ss >> key;   // 提取键
    ss.ignore(); // 忽略分隔符（这里是 &）
    ss >> value; // 提取值

    // 输出解析结果
    std::cout << "Command: " << command << std::endl;
    std::cout << "Key: " << key << std::endl;
    std::cout << "Value: " << value << std::endl;
    return 0;
}