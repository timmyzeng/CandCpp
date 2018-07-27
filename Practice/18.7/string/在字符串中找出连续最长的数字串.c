/*
接口说明

函数原型：
   unsignedint Continumax(char** pOutputstr,  char* intputstr)
输入参数：
   char* intputstr  输入字符串；
输出参数：
   char** pOutputstr: 连续最长的数字串，如果连续最长的数字串的长度为0，应该返回空字符串；如果输入字符串是空，也应该返回空字符串；  
返回值：
  连续最长的数字串的长度

输入描述:
输入一个字符串。

输出描述:
输出字符串中最长的数字字符串和它的长度。如果有相同长度的串，则要一块儿输出，但是长度还是一串的长度

示例1
输入
abcd12345ed125ss123058789
输出
123058789,9

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

unsigned int Continumax(char** pOutputstr,  char* intputstr){
    int size = strlen(intputstr);
    *pOutputstr = (char*)malloc(size+1);
    char* input = intputstr;
    char* output = *pOutputstr;
    unsigned int num = 0;
    unsigned int max = 0;
    while(*input != '\0'){
        num = 0;
        if(isdigit(*input)){
            char* cur = input;
            while(*cur != '\0' && isdigit(*cur)){
                num ++;
                cur ++;
            }
            if(num > max){
                strncpy(output, input, num);
                max = num;
                *(output+num) = '\0';
            }
            else if(num == max){
                strncpy(output+max, input, num);
                *(output+max+num) = '\0';
            }
            input = cur;
        }
        input ++;
    }

    return max;
}

int main(){
    char input[1000];
    char* output = NULL;
    char** poutput = &output;
    while(scanf("%s", input) != EOF){
        unsigned int num = Continumax(poutput, input);
        printf("%s,%d\n",*poutput, num);
    }
    return 0;
}
