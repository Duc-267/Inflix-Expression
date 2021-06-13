#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

struct Node {
    string s = "\n";
    Node* next=NULL;
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

void thucHien(string kytu, stack<float>& so, Stack& toantu);
bool kiemTraSo(char a);
int doUuTien(string toanTu);
float tinhToan(float a, float b, string toanTu);

void thucHien(string kytu, stack<float>& so, Stack& toantu)
{
    if (kiemTraSo(kytu[0])) {
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
            so.push(tinhToan(soThuNhat, soThuHai, toantu.top()));
            toantu.pop();
        }
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

bool kiemTraSo(char s)
{
    if (isdigit(s))
        return true;
    return false;
}

int main()
{
    stack <float> so;
    Stack toanTu;

    ifstream filein;
    filein.open("input.txt");
    string s;
    while (!filein.eof())
    {
        string newS;
        while (getline(filein, s)) {
            stringstream ss(s);
            while (getline(ss, newS, ' ')) {
                thucHien(newS, so, toanTu);
            }
            while (!toanTu.empty()) {
                while (!toanTu.empty()) {
                    float soThuNhat = so.top();
                    so.pop();
                    float soThuHai = so.top();
                    so.pop();
                    so.push(tinhToan(soThuHai, soThuNhat, toanTu.top()));
                    toanTu.pop();
                }
            }
            cout << so.top() << endl;
        }

    }
    system("pause");
    return 0;
}