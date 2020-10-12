// keygen.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include <Windows.h>
#include <iostream>

DWORD WINAPI antidebug1(LPVOID lpParameter) {
    while (true) {
        if (IsDebuggerPresent()) {
            exit(0);
        }
    }
}

BOOL CheckDebug()
{
    char result = 0;
    __asm
    {
        mov eax, fs: [30h]
        mov al, BYTE PTR[eax + 2]
        mov result, al
    }
    return result != 0;
}

DWORD WINAPI antidebug2(LPVOID lpParameter) {
    srand(0x1145140);
    while (true) {
        if (CheckDebug()) {
            exit(0);
        }
    }
}

// Spirit{a59298c9-3cde-4684-9784-f456bd324e97}
const char encrypted_flag[] = "a59298c9-3cde-4684-9784-f456bd324e97"; // patched after compile
__declspec(noinline) uint8_t* get_flag() {
    uint8_t* flag = new uint8_t[37];
    for (int i = 0; i < 36; i++) {
        uint8_t key = rand() % 0xff;
        printf("%02x", key);
        flag[i] = key ^ encrypted_flag[i];
    }
    flag[36] = 0;
    return flag;
}

int main()
{
    HANDLE thread1 = CreateThread(NULL, 0, antidebug1, NULL, 0, NULL);
    HANDLE thread2 = CreateThread(NULL, 0, antidebug2, NULL, 0, NULL);
    char buf[0x100];
    memset(buf, 0, 0x100);
    printf("Enter your license key to get the flag: ");
    scanf_s("%s", buf, 0x100);
    uint8_t* flag = get_flag();
    if (strcmp(buf, (char*)flag) == 0) {
        printf("Accepted! Your flag is Spirit{%s}", buf);
    } else {
        printf("Please try again!");
    }
}
