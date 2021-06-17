#include <string>
#include "stack.h"


void thucHien(string kytu, StackFloat& so, Stack& toantu);
bool isParam(string a);
int doUuTien(string toanTu);
float tinhToan(float a, float b, string toanTu);
bool isParam(string line)
{
    if (line.compare("(")!=0&&line.compare(")")!=0&&line.compare("+")!=0&&line.compare("-")!=0&&
        line.compare("*")!=0&&line.compare("/")!=0&&line.compare("^")!=0){
            return true;
    }
    return false;
}


bool kiemTraHaiSoLienTuc(int& laHaiSoLienTuc, string kytu) {
    if (isParam(kytu)) {
        laHaiSoLienTuc++;
    }
    else if ((kytu.compare("(") != 0 && kytu.compare(")")) != 0) {
        laHaiSoLienTuc = 0;
    }

    if (laHaiSoLienTuc == 2)
        return true;
    return false;
}

int doUuTien(string toanTu)
{
    if (toanTu == "+" || toanTu == "-")
        return 1;
    if (toanTu == "*" || toanTu == "/")
        return 2;
    if (toanTu == "^")
        return 3;
    return 0;
}

float tinhToan(float a, float b, string toanTu)
{
    switch (toanTu[0])
    {
    case '+':
        return a + b;
    case '-':
        return a - b;
    case '*':
        return a * b;
    case '/':
        return a / b;
    case '^':
        return pow(a, b);
    }

    return 0;
}

void thucHien(string kytu, StackFloat& so, Stack& toantu){
    if (isParam(kytu)) {
        so.push(stof(kytu));
    }
    else if (kytu == "(") {
        toantu.push(kytu);
    }
    else if (kytu == ")") {
        while (toantu.top() != "(" && !toantu.empty()) {
            float soThuNhat = so.top();
            so.pop();
            float soThuHai = so.top();
            so.pop();
            so.push(tinhToan(soThuHai, soThuNhat, toantu.top()));
            toantu.pop();
        }
        toantu.pop();
    }
    else {
        while (!toantu.empty() && doUuTien(toantu.top()) >= doUuTien(kytu)) {
            float soThuNhat = so.top();
            so.pop();
            float soThuHai = so.top();
            so.pop();
            so.push(tinhToan(soThuHai, soThuNhat, toantu.top()));
            toantu.pop();
        }
        toantu.push(kytu);
    }
}
void thucHien2(string kytu, Stack& so, Stack& toantu){
    if (isParam(kytu)) {
        so.push(kytu);
    }
    else if (kytu == "(") {
        toantu.push(kytu);
    }
    else if (kytu == ")") {
        while (toantu.top() != "(" && !toantu.empty()) {
            string soThuNhat = so.top();
            so.pop();
            string soThuHai = so.top();
            so.pop();
            string imp = soThuHai + (soThuHai!="" ? " " : "") +  soThuNhat + (soThuNhat!="" ? " " : "") + toantu.top();
            so.push(imp);
            toantu.pop();
        }
        toantu.pop();
    }
    else {
        while (!toantu.empty() && doUuTien(toantu.top()) >= doUuTien(kytu)) {
            string soThuNhat = so.top();
            so.pop();
            string soThuHai = so.top();
            so.pop();
            string imp = soThuHai + (soThuHai!="" ? " " : "") +  soThuNhat + (soThuNhat!="" ? " " : "") + toantu.top() ;
            so.push(imp);                       
            toantu.pop();                                                       
        }                     
        toantu.push(kytu);                                     
    }
}

int timViTriThapNhat(int a, int b, int c){
    int min = (a == -1 ? INT_MAX : a);
    if (min > b && b > -1)
        min = b;
    else if (min > c && c > -1)
        min = c;
    return min;
}
