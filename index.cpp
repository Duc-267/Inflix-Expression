#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <climits>
#include <math.h>
using namespace std;


struct Node {
    string s = "\n";
    Node* next = NULL;
};

class Stack {
private:
    Node* head;
public:
    Stack() {
        head = NULL;
    }
    string top()
    {
        if (!head)
            return "";
        return head->s;
    }
    void pop() {
        if (!head)
            return;
        if (!head->next) {
            delete head;
            head = NULL;
            return;
        }
        Node* temp = head->next;
        delete head;
        head = temp;
    }
    void push(string s) {
        Node* temp = new Node;
        if (temp == 0) {
            return;
        }
        if (head == NULL) {
            temp->s = s;
            temp->next = NULL;
            head = temp;
            return;
        }
        else {
            temp->s = s;
            temp->next = head;
            head = temp;
            return;
        }
    }
    bool empty() {
        if (head == NULL)
            return 1;
        else return 0;
    }
};

struct NodeFloat
{
    float s;
    NodeFloat* next = NULL;
};

class StackFloat{
private:
    NodeFloat* head;
public:
    StackFloat() {
        head = NULL;
    }
    float top()
    {
        if (!head)
            return 234843.7243432;
        return head->s;
    }
    void pop() {
        if (!head)
            return;
        if (!head->next) {
            delete head;
            head = NULL;
            return;
        }
        NodeFloat* temp = head->next;
        delete head;
        head = temp;
    }
    void push(float s) {
        NodeFloat* temp = new NodeFloat;
        if (temp == 0) {
            return;
        }
        if (head == NULL) {
            temp->s = s;
            temp->next = NULL;
            head = temp;
            return;
        }
        else {
            temp->s = s;
            temp->next = head;
            head = temp;
            return;
        }
    }
    bool empty() {
        if (head == NULL)
            return 1;
        else return 0;
    }
};

int timViTriThapNhat(int a, int b, int c){
    int min = (a == -1 ? INT_MAX : a);
    if (min > b && b > -1)
        min = b;
    else if (min > c && c > -1)
        min = c;
    return min;
}

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

int main(int argc, char* argv[])
{
    
    ifstream filein;
    filein.open(argv[1]);
    ofstream fileout;
    fileout.open(argv[4]);
    string s;
    string mode(argv[3]);
    while (!filein.eof())
    {
        string newS;
        if (mode == "-c"){
            while (getline(filein, s)) {
                stringstream ss(s);
                int laHaiSoLienTuc = 0;
                StackFloat so;
                Stack toanTu;
                while (getline(ss, newS, ' ')) {
                    if (newS[0] == '(' || newS[0] == '{' || newS[0] == '[') {
                        while(newS[0] == '(' || newS[0] == '{' || newS[0] == '['){
                            string dauMoNgoac = "(";
                            thucHien(dauMoNgoac, so, toanTu);
                            newS.erase(0, 1);
                        }
                        if (kiemTraHaiSoLienTuc(laHaiSoLienTuc, newS)) {
                            fileout << "E" << endl;
                            break;
                        }
                        thucHien(newS, so, toanTu);
                    }
                    else if (newS[newS.size() - 1] == ')' || newS[newS.size() - 1] == '}' ||newS[newS.size() - 1] == ']' ) {
                        int viTriNgoacTron = newS.find(")");
                        int viTriNgoacNhon = newS.find("}");
                        int viTriNgoacVuong = newS.find("]");
                        int viTri = timViTriThapNhat(viTriNgoacTron, viTriNgoacNhon, viTriNgoacVuong);
                        string motSo = newS.substr(0, viTri);
                        newS.erase(0, viTri);
                        if (kiemTraHaiSoLienTuc(laHaiSoLienTuc, motSo)) {
                            fileout << "E" << endl;
                            break;
                        }
                        thucHien(motSo, so, toanTu);
                        while (newS[0] == ')' ||newS[0] == ']'||newS[0] == '}')
                        {
                            string dauDongNgoac = ")";
                            thucHien(dauDongNgoac, so, toanTu);
                            newS.erase(newS.size() - 1, 1);
                        }                    
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
                    if (so.top() != 234843.7243432){
                        fileout << fixed <<setprecision(2) <<so.top() << endl;
                    }
                    else{
                        fileout << "E" << endl;
                    }
                }
            }
        }
        else if (mode == "-t"){
            while (getline(filein, s)) {
                stringstream ss(s);
                int laHaiSoLienTuc = 0;
                Stack so;
                Stack toanTu;
                while (getline(ss, newS, ' ')) {
                    if (newS[0] == '(' || newS[0] == '{' || newS[0] == '[') {
                        while(newS[0] == '(' || newS[0] == '{' || newS[0] == '['){
                            string dauMoNgoac = "(";
                            thucHien2(dauMoNgoac, so, toanTu);
                            newS.erase(0, 1);
                        }
                        if (kiemTraHaiSoLienTuc(laHaiSoLienTuc, newS)) {
                            fileout << "E" << endl;
                            break;
                        }
                        thucHien2(newS, so, toanTu);
                    }
                    else if (newS[newS.size() - 1] == ')' || newS[newS.size() - 1] == '}' ||newS[newS.size() - 1] == ']') {
                        int viTriNgoacTron = newS.find(")");
                        int viTriNgoacNhon = newS.find("}");
                        int viTriNgoacVuong = newS.find("]");
                        int viTri = timViTriThapNhat(viTriNgoacTron, viTriNgoacNhon, viTriNgoacVuong);
                        string motSo = newS.substr(0, viTri);
                        newS.erase(0, viTri);
                        if (kiemTraHaiSoLienTuc(laHaiSoLienTuc, motSo)) {
                            fileout << "E" << endl;
                            break;
                        }
                        thucHien2(motSo, so, toanTu);
                        while (newS[0] == ')'||newS[0] == ']'||newS[0] == '}')
                        {
                            string dauDongNgoac = ")";
                            thucHien2(dauDongNgoac, so, toanTu);
                            newS.erase(0, 1);
                        }                    
                    }
                    else {
                        if (kiemTraHaiSoLienTuc(laHaiSoLienTuc, newS)) {
                            fileout << "E" << endl;
                            break;
                        }
                        thucHien2(newS, so, toanTu);
                    }

                }
                if (laHaiSoLienTuc != 2) {
                    while (!toanTu.empty()) {
                        string soThuNhat = so.top();
                        so.pop();
                        string soThuHai = so.top();
                        so.pop();
                        
                        string imp = soThuHai + (soThuHai!="" ? " " : "") +  soThuNhat + (soThuHai!="" ? " " : "") + toanTu.top() + (toanTu.top()!="" ? " " : "");
                        so.push(imp);
                        toanTu.pop();
                    }
                    fileout << so.top() << endl;
                }
            }
        }
        filein.close();
        fileout.close();
    }


    system("pause");
    return 0;
}