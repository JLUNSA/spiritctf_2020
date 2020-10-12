// secure_app.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
// Spirit{2aa57287-603a-4c2e-b7a8-978dae5fdd1f}
const char* flag = "}f1ddf5ead879-8a7b-e2c4-a306-78275aa2{tiripS";
int main()
{
    char rev[20];
    for (int i = 0; i < 20; i++) {
        rev[19 - i] = flag[24 + i];
    }
    rev[19] = 0;
    printf("For security reasons, I can only give you first part of your flags.\n");
    printf("It is: %s\n", rev);
    printf("Good Luck!\n");
    system("pause");
}
