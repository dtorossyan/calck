#include <iostream>
#include <cstring>
#include <cmath>
#include <fstream>
#include "StackNums.h"
#include "StackOpers.h"

using namespace std;
bool isInt(char e) {if(47<e && e<58) return true; else return false;}

void ERROR(string text,char *str,StackNums nums,StackOpers opers){
    cout<<endl<<text<<" "<<endl;
    delete[](str);
    nums.clear();
    opers.clear();
    exit(0);
}

float getFloat(int i,char*str, int &len){
    float res=0;
    len=0;
    bool isDigit=false;
    bool cat = false;
    int doCat = 1;
    for(i;i<strlen(str)+1;++i){
        if(isInt(str[i])){
            if(isDigit){
                if(cat){
                    res+=(str[i] - 48)*pow(0.1f,doCat);
                    ++doCat;
                } else {
                    res = res * 10 + (str[i] - 48);
                }
            }else{
                res = str[i]-48;
                isDigit = true;
            }
        }else if(str[i]=='.' && !cat){
            cat= true;
        }else{
            return res;
        }
        ++len;
    }
}

char * getCharArr(int argc,char **argv){
    string path = "/home/oem/c++/calk/Test/";
    for(int i=0;i<strlen(argv[1]);++i){
        path=path+argv[1][i];
    }
    fstream f(path, ios::in);
    char *res = nullptr;
    if(f.is_open()){
        string line;
        while (getline(f, line))
        {
            int size = line.length() + 1;
            res = new char[size];
            strcpy(res, line.c_str());
        }
    }else {
        int size = 0;
        for (int i = 1; i < argc; ++i) {
            printf("argc - %d, args - %s\n", i, argv[i]);
            size += strlen(argv[i]);
        }
        size++;
        res = new char[size];
        memset(res, 0, size);
        for (int i = 1; i < argc; ++i) {
            res = strcat(res, argv[i]);
        }
        printf("calc - %s\n", res);
    }
    if(strlen(res)!=0){
        for (int i = 0, j = 0; res[i]; (res[j++] = res[i] != ' ' ? res[i] : (j--, res[j]), i++, (!res[i] ? (res[j] = 0) : 0)));
        return res;
    }
    cout<<"данный файл не харнит в себе ничего"<<endl;
    exit(0);

}

float primer(char *str){
    float scob=0;
    int len;
    StackNums nums;
    StackOpers opers;
    for(int i=0;i<strlen(str);++i){
        if(isInt(str[i])) {
            float temp = getFloat(i,str, len);
            i = i + len - 1;
            nums.push(temp);
        }else if(str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/' || str[i] == ')' || str[i] == '(' ) {
            if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/') {
                if (str[i] == '+' || str[i] == '-') {
                    if (!opers.empty()) {
                        char oper = opers.pop();
                        if ((oper == '+' || oper == '-' || oper == '*' || oper == '/') && nums.size>=2) {
                            float b = nums.pop();
                            float a = nums.pop();
                            if (oper == '*') nums.push(a * b);
                            else if (oper == '/') {
                                if(b==0){
                                    ERROR("ERROR на 0 делить нельзя",str,nums,opers);
                                }
                                nums.push(a / b);
                            }
                            else if (oper == '-') nums.push(a - b);
                            else nums.push(a + b);
                            --i;
                        } else {
                            opers.push(oper);
                            if (str[i] == '+') opers.push('+'); else opers.push('-');

                        }
                    } else {
                        if (str[i] == '+') opers.push('+'); else opers.push('-');

                    }
                } else if (str[i] == '*' || str[i] == '/') {
                    if (!opers.empty()) {
                        char oper = opers.pop();
                        if ((oper == '*' || oper == '/') && nums.size>2) {
                            float b = nums.pop();
                            float a = nums.pop();
                            if (oper == '*')nums.push(a * b); else{
                                if(b==0){
                                    ERROR("ERROR на 0 делить нельзя",str,nums,opers);
                                }
                                nums.push(a / b);
                            }
                            --i;
                        } else {
                            opers.push(oper);
                            if (str[i] == '*') opers.push('*'); else opers.push('/');
                        }
                    } else {
                        if (str[i] == '*') opers.push('*'); else opers.push('/');
                    }
                }
                if (i > 0 && i < strlen(str) - 1) {
                    if (str[i] == '-' && str[i - 1] == '(' && isInt(str[i + 1])) {
                        int temp = getFloat(i + 1, str,len);
                        i = i+len;
                        opers.pop();
                        nums.push(temp * (-1));
                    }
                }
            } else if (str[i] == '(') {
                if (i == strlen(str) - 1) {
                    ERROR("ERROR нельзя ставить в конце '('",str,nums,opers);
                }
                ++scob;
                opers.push('(');
            } else if (str[i] == ')') {
                if(i==0 || str[i-1]=='('){
                    ERROR("ERROR",str,nums,opers);
                }
                char oper = opers.pop();
                if (oper != '(') {
                    float b = nums.pop();
                    float a = nums.pop();
                    if (oper == '*') nums.push(a * b);
                    else if (oper == '/'){
                        if(b==0){
                            ERROR("ERROR",str,nums,opers);
                        }
                        nums.push(a / b);
                    }
                    else if (oper == '-') nums.push(a - b);
                    else nums.push(a + b);
                    --i;
                } else {
                    if (!opers.empty()) {
                        char temp = opers.pop();
                        if (temp == 's') {
                            nums.push(sin(nums.pop()));
                        } else if (temp == 'c') {
                            nums.push(cos(nums.pop()));
                        }else{
                            opers.push(temp);
                        }
                    }
                    --scob;
                }
            }
        }else if(str[i]=='c' || str[i]=='s'){
            if(i<strlen(str)-4) {
                if (str[i] == 'c' && str[i + 1] == 'o' && str[i + 2] == 's' && str[i + 3] == '(') {
                    opers.push('c');
                } else if (str[i] == 's' && str[i + 1] == 'i' && str[i + 2] == 'n' && str[i + 3] == '(') {
                    opers.push('s');
                }
                i = i + 2;
            }
        }else{
            ERROR("ERROR",str,nums,opers);
        }
    }
    if(scob!=0){
        ERROR("ERROR",str,nums,opers);
    }
    while(!opers.empty()) {
        if (nums.size >= 2) {
            char o = opers.pop();
            float b = nums.pop();
            float a = nums.pop();
            if (o == '+')nums.push(a + b);
            else if (o == '-')nums.push(a - b);
            else if (o == '/'){
                if(b==0){
                    ERROR("ERROR",str,nums,opers);
                }
                nums.push(a / b);
            }
            else if (o == '*')nums.push(a * b);
        }else{
            ERROR("ERROR",str,nums,opers);
        }
    }

    if(nums.size>1 || opers.size>0){
        ERROR("ERROR",str,nums,opers);
    }
    return nums.pop();
}

char *obs(char*str){

}

char *sql(char *str){

}

int main(int argc, char * argv[]) {
    if(argc==1){
        cout<<"1.чтение с консоли \n2.решение обычных вырожений +,-,*,/ \n3.решение выражений со cos и sin \n4.чтение с файла в папке Test"<<endl;
        return 0;
    }
    char *str = getCharArr(argc,argv);
    //cout<<endl<<"gay "<<openScob(str);
    delete[](str);
}
