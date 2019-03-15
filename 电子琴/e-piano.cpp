#include "pch.h"
#include <iostream>

#include <conio.h>//getch()
#include <graphics.h>//windows.h
#include <mmsystem.h>

#pragma comment(lib,"winmm.lib")

#define WIDTH 100
#define HEIGHT 400

IMAGE img[7];
IMAGE down;
void init() {
	//加载图片
	char temp[256];
	for (int i = 0; i < 7; i++) {
		memset(temp, 0, 256);
		sprintf_s(temp, "images\\%d.bmp", i + 1);
		loadimage(&img[i], temp);
	}

	loadimage(&down, "images\\down.bmp");

	//贴图
	for (int i = 0; i < 7; i++) {
		putimage(i*WIDTH, 0, &img[i]);
	}
}
void playSound(char* str)
{
	char buff[256] = { 0 };
	sprintf_s(buff,"open sounds\\%s alias m",str);
	mciSendString(buff, 0, 0, 0);
	mciSendString("play m", 0, 0, 0);
	Sleep(300);
	mciSendString("close m", 0, 0, 0);
}

DWORD proc(LPVOID lpThreadParameter) {
	char buff[256] = { 0 };
	sprintf_s(buff, "open sounds\\%s alias m", (char*)lpThreadParameter);
	int index = ((char*)lpThreadParameter)[0] - '0';
	//用灰色图片覆盖对应颜色图片
	putimage((index - 1)*WIDTH, 0, &down);

	printf("index:%d\n", index);
	mciSendString(buff, 0, 0, 0);//打开
	mciSendString("play m", 0, 0, 0);//播放
	Sleep(300);//睡觉
	//用原来颜色的图片贴回来
	putimage((index - 1)*WIDTH, 0, &img[index - 1]);
	//	mciSendString("close m", 0, 0, 0);//关闭   让它自动关闭
	return 0;
}
int music[] = { 0,3,0,3,0,5,0,5,0,1,0,1,0,7,0,7,0,6,0,3,0,6,0,6,0,0,0,0,6,0,6,0,7,0,7,0,3,0,3,0,7,0,0,0,7,0,5,0,3,0,5,0,5,0,0,0,0,0,0,3,0,3,0,5,0,5,0,1,0,1,0,7,0,0,0,7,0,6,0,3,0,6,0,6,0,6,0,7,0,
0,0,0,6,0,7,0,3,0,3,0,2,0,1,0
};
int len = sizeof(music) / sizeof(music[0]);
int index = 0;
VOID timeProc(HWND hWnd, UINT uInt, UINT_PTR ptr, DWORD dWord) {
	if (index > len) index = 0;
	switch (music[index++]) {
	case 1:SendMessage(hWnd, WM_KEYDOWN, 49, NULL); break;
	case 2:SendMessage(hWnd, WM_KEYDOWN, 50, NULL); break;
	case 3:SendMessage(hWnd, WM_KEYDOWN, 51, NULL); break;
	case 4:SendMessage(hWnd, WM_KEYDOWN, 52, NULL); break;
	case 5:SendMessage(hWnd, WM_KEYDOWN, 53, NULL); break;
	case 6:SendMessage(hWnd, WM_KEYDOWN, 54, NULL); break;
	case 7:SendMessage(hWnd, WM_KEYDOWN, 55, NULL); break;
	}
}
int main()
{
	int c;
	DWORD id;
	HWND hWnd = initgraph(7 * WIDTH, HEIGHT, SHOWCONSOLE);//命令行窗口
	init();
  //注释去掉可以自动按数组音律播放
	//SetTimer(hWnd, 8880, 150, (TIMERPROC)timeProc);//定时器
	while (1) {
		c = getch();//获取按键值并返回
		printf("%d\n", c);
		switch (c)
		{
		case 49:	CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)proc, (LPVOID) "1.mp3", NULL, &id); break;
		case 50:	CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)proc, (LPVOID)"2.mp3", NULL, &id); break;
		case 51:	CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)proc, (LPVOID)"3.mp3", NULL, &id); break;
		case 52:	CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)proc, (LPVOID)"4.mp3", NULL, &id); break;
		case 53:	CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)proc, (LPVOID)"5.mp3", NULL, &id); break;
		case 54:	CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)proc, (LPVOID)"6.mp3", NULL, &id); break;
		case 55:	CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)proc, (LPVOID)"7.mp3", NULL, &id); break;
		default:    break;
		}
	}

	while (1);
	return 0;
}
