#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "stack.h"
using namespace std;


void thucHien(string kytu, StackFloat& so, Stack& toantu);
bool isParam(string a);
int doUuTien(string toanTu);
float tinhToan(float a, float b, string toanTu);
bool isParam(string line)
{
    if (line.compare("(")!=0&&line.compare(")")!=0&&line.compare("+")!=0&&line.compare("-")!=0&&
        line.compare("*")!=0&&line.compare("/")!=0){
            return true;
    }
    return false;
}
void thucHien(string kytu, StackFloat& so, Stack& toantu)
{
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
    {
        return 1;
    }
    if (toanTu == "*" || toanTu == "/")
    {
        return 2;
    }
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
    }
    return 0;
}


int main()
{
   

    ifstream filein;
    filein.open("input.txt");
    ofstream fileout;
    fileout.open("output.txt");
    string s;
    while (!filein.eof())
    {
        string newS;
        while (getline(filein, s)) {
            stringstream ss(s);
            int laHaiSoLienTuc = 0;
            StackFloat so;
            Stack toanTu;
            while (getline(ss, newS, ' ')) {
                if (newS[0] == '(') {
                    string dauMoNgoac = newS.substr(0, 1);
                    kiemTraHaiSoLienTuc(laHaiSoLienTuc, dauMoNgoac);
                    newS.erase(0, 1);
                    if (kiemTraHaiSoLienTuc(laHaiSoLienTuc, newS)) {
                        fileout << "E" << endl;
                        break;
                    }
                    thucHien(dauMoNgoac, so, toanTu);
                    thucHien(newS, so, toanTu);
                }
                else if (newS[newS.size() - 1] == ')') {
                    string dauDongNgoac = newS.substr(newS.size() - 1, 1);
                    kiemTraHaiSoLienTuc(laHaiSoLienTuc, dauDongNgoac);
                    newS.erase(newS.size() - 1, 1);
                    if (kiemTraHaiSoLienTuc(laHaiSoLienTuc, newS)) {
                        fileout << "E" << endl;
                        break;
                    }
                    thucHien(newS, so, toanTu);
                    thucHien(dauDongNgoac, so, toanTu);
                }
                else {
                    if (kiemTraHaiSoLienTuc(laHaiSoLienTuc, newS)) {
                        fileout << "E" << endl;
                        break;
                    }
                    thucHien(newS, so, toanTu);
                }

            }
            if (laHaiSoLienTuc != 2) {
                while (!toanTu.empty()) {
                    float soThuNhat = so.top();
                    so.pop();
                    float soThuHai = so.top();
                    so.pop();
                    so.push(tinhToan(soThuHai, soThuNhat, toanTu.top()));
                    toanTu.pop();
                }
                fileout << fixed <<setprecision(2) <<so.top() << endl;
            }
        }
        filein.close();
        fileout.close();
    }
    system("pause");
    return 0;
}