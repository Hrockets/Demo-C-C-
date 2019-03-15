#include "pch.h"
#include <iostream>
//1 引入头文件，导入静态库
#include <WinSock2.h>
#include <WS2tcpip.h> 
#pragma comment(lib,"ws2_32.lib")

int main()
{
	//	2获取协议版本
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (HIBYTE(wsaData.wVersion) != 2 || LOBYTE(wsaData.wVersion) != 2) {
		printf("请求版本失败!\n");
		return -1;
	}
	printf("请求版本成功!\n");

	//	3创建socket		         协议格式 数据格式 保护模式
	SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (INVALID_SOCKET == serverSocket) {
		printf("创建socket失败!\n");
		return -1;
	}
	printf("创建socket成功!\n");
	//	4创建协议地址族		
	SOCKADDR_IN addr = { 0 };
	addr.sin_family = AF_INET;//必须和socket函数的第一个参数保持一致
	addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");//ip地址
	addr.sin_port = htons(10086);//端口
	

	int r = connect(serverSocket, (sockaddr*)&addr, sizeof addr);
	if (r == -1) {
		printf("连接服务器失败!\n");
		return -1;
	}
	printf("连接服务器成功!\n");
	//	8通信	
	char buff[256];
	while (1) {
		printf("请输入:");
		scanf("%s", buff);
		r = send(serverSocket, buff, strlen(buff), NULL);
		if (r > 0) {
			printf("往服务器发送了%d字节的数据!\n", r);
		}
		
	}
		
	//	9关闭socket				
	closesocket(serverSocket);
	//	10清除版本信息				
	WSACleanup();

}
