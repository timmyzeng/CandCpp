/*
 *题目描述
请实现一个函数，将一个字符串中的空格替换成“%20”。例如，当字符串为We Are Happy.则经过替换之后的字符串为We%20Are%20Happy。
 */

class Solution {
public:
	void replaceSpace(char *str,int length) {
        if(str == nullptr)
            return;
        char* sour = str;
        char* tar = str;
        int tar_len = 0;
        while(*sour != '\0'){
            if(*sour == ' ')
                tar_len += 3;
            else
                ++ tar_len;
            ++ sour;
        }
        if(tar_len > length)
            return;
        tar = str + tar_len;
        while(tar != sour){
            if(*sour == ' '){
                *tar-- = '0';
                *tar-- = '2';
                *tar-- = '%';
            }
            else{
                *tar-- = *sour;
            }
            -- sour;
        }
    }
};
