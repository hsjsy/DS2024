#include <cmath>
#include <string>
#include <iostream>
using namespace std;
template<class T>
class Stack;
template<class T>
class Node
{
private:
    T m_data;               //������
    Node* m_next = nullptr; //ָ����
public:
    Node(const T& val)
    {
        this->m_data = val;
    }                                          //�вι���
    Node& operator=(const Node& rhs) = delete; //��ֹ��ֵ
    friend class Stack<T>;                     //������Ԫ
};                                             //�������


template<class T>
class Stack
{
private:
    Node<T>* m_top = nullptr; //����ͷ���
public:
    Stack() = default;                       //Ĭ�Ϲ��캯��
    Stack(const Stack&) = delete;            //���Ƹ���
    Stack& operator=(const Stack&) = delete; //���Ƹ���
    
    ~Stack()
    {
        clear();
        this->m_top = nullptr;
    } //��������

    void clear()
    {
        Node<T>* p = nullptr;
        while (this->m_top != nullptr)
        {
            p = this->m_top;
            this->m_top = this->m_top->m_next;
            delete p;
        }
    } //��ջ����

    void push(const T& val)
    {
        Node<T>* node = new Node<T>(val);
        node->m_next = this->m_top;
        this->m_top = node;
    } //��ջ����

    void pop()
    {
        if (empty()) { return; }
        Node<T>* p = this->m_top;
        this->m_top = this->m_top->m_next;
        delete p;
    } //��ջ����

    bool empty() const
    {
        return this->m_top == nullptr;
    } //�ж��Ƿ�Ϊ��

    const T& top()
    {
        return this->m_top->m_data;
    } //����ͷָ������

}; //����ջ


class Calculator
{
private:
    Stack<double> m_num;                        //���ڴ������
    Stack<char> m_opr;                          //���ڴ�������
    int precedence(const char& input) const;    //�ж����ȼ�
    double readNum(string::const_iterator& it); //��������
    char readOpr(string::const_iterator& it);   //���������
    void calculate();                           //�������ֺ����������
    bool isNum(string::const_iterator& c) const
    {
        return *c >= '0' && *c <= '9' || *c == '.';
    } //�ж��Ƿ�Ϊ����

public:
    ~Calculator()
    {
        this->m_num.clear();
        this->m_opr.clear();
    } //��������
    Calculator()
    {
        this->m_opr.push('#');
    }                               //��ʼ��
    double doIt(const string& exp); //������ʽ����
};


int Calculator::precedence(const char& input) const
{
    switch (input)
    {
    case '=': return 0;
    case '#': return 1;
    case '+':case '-': return 2;
    case '*':case '/':case '%': return 3;
    case 's':case 'c':case 't':case 'r': return 4;
    case '^': return 5;
    default: return 1;
    }
} //�ж����ȼ�


double Calculator::readNum(string::const_iterator& it)
{
    string t;
    if (*it == 'p' && *(it + 1) == 'i')
    {
        return atan(1.0) * 4;
    } //�ж��Ƿ�Ϊpi

    while (isNum(it) || *it == '.')
    {
        t += *it++;
    }
    while (isspace(*it))
    {
        ++it; // �����ո�
    }
    return stod(t); //���ַ���ת��Ϊdouble����
} //��������


char Calculator::readOpr(string::const_iterator& it)
{
    string t1;
    string t2;
    t1 = *it;       //��һ����ĸ
    t2 = *(it + 1); //�ڶ�����ĸ
    while (isspace(*it))
    {
        ++it; // �����ո�
    }
    //cout << "��ȡ�����" << endl;
    if (t1 == "s" && t2 == "i")
    {
        //cout << "��ȡsin";
        return 's';
    } //sin
    else if (t1 == "c")
    {
        return 'c';
    } //cos
    else if (t1 == "t")
    {
        return 't';
    } //tan
    else if (t1 == "s" && t2 == "q")
    {
        return 'r';
    } //sqrt
} //���������


void Calculator::calculate()
{
    if (this->m_num.empty())
    {
        return;
    }
    double rightnum = this->m_num.top(); //ȡ���ұߵ�������
    this->m_num.pop();                   //��ջ�е���ȡ����������
    switch (this->m_opr.top())
    {
    case 's':
        this->m_num.push(sin(rightnum)); //sin
        break;
    case 'c':
        this->m_num.push(cos(rightnum)); //cos
        break;
    case 't':
        this->m_num.push(tan(rightnum)); //tan
        break;
    case 'r':
        this->m_num.push(sqrt(rightnum)); //sqrt
        break;
    default:                                //�ж��Ƿ�ΪһĿ���㲻Ϊ�����½���
        double leftnum = this->m_num.top(); //ȡ����ߵ�������
        this->m_num.pop();                  //��ջ�е���ȡ����������
        if (this->m_opr.top() == '+')
        {
            this->m_num.push(leftnum + rightnum);
        } //+����
        else if (this->m_opr.top() == '-')
        {
            this->m_num.push(leftnum - rightnum);
        } //-����
        else if (this->m_opr.top() == '*')
        {
            this->m_num.push(leftnum * rightnum);
        } //*����
        else if (this->m_opr.top() == '/')
        {
            this->m_num.push(leftnum / rightnum);
        } // /����
        else if (this->m_opr.top() == '%')
        {
            this->m_num.push(static_cast<int>(leftnum) % static_cast<int>(rightnum));
        } //%����
        else if (this->m_opr.top() == '^')
        {
            this->m_num.push(pow(leftnum, rightnum));
        } //������
        break;
    }
    //cout << "��������" << this->m_opr.top();
    this->m_opr.pop(); //��ջ�е���ȡ���������
} //���㺯��


double Calculator::doIt(const string& exp)
{
    this->m_num.clear(); //���ջ
    for (auto it = exp.begin(); it != exp.end();)
    {
        while (isspace(*it))
        {
            ++it; // �����ո�
        }
        if (isNum(it) || *it == 'p')
        {
            this->m_num.push(readNum(it));
            if (*it == 'p')
            {
                ++it;
                ++it;
            } //��Ϊpi������i��ѭ��
              //cout << "��ȡ����" << this->m_num.top();
        }     //���ж��Ƿ�Ϊ����
        else if (*it == '(')
        {
            this->m_opr.push(*it);
            //cout << "��ȡ�����1" << this->m_opr.top();
            ++it;
        } //�ж��Ƿ���������
        else if (*it == ')')
        {
            while (this->m_opr.top() != '(')
            {
                calculate();
            }
            //cout << "��������" << this->m_opr.top() << endl;
            this->m_opr.pop(); //����"("���������ڵ�����
            ++it;
        } //������")"�������������ֱ�������ջ��Ϊ"("
        else
        {
            while (precedence(*it) <= precedence(this->m_opr.top()))
            {
                if (this->m_opr.top() == '#')
                {
                    //cout << "��ֹ";
                    break;
                }
                calculate();
            } //
            if (*it != '=' && *it != 's' && *it != 'c' && *it != 't')
            {
                this->m_opr.push(*it); //����ͨ�������ջ
            }
            else
            {
                if (*it == 's' || *it == 'c' || *it == 't')
                {
                    this->m_opr.push(this->readOpr(it));
                    if (this->readOpr(it) == 'r')
                    {
                        ++it;
                    } //��Ϊsqrt����Ҫ����һλ
                    ++it;
                    ++it;
                } //��ջ���������ַ����ж�
            }     //�������������ջ
            ++it;
        }
    } //���ǵ�һ��for����������
    return this->m_num.top(); //�����󷵻�����ջ���ݣ��õ����
}


int main()
{
    string a = "3-2*4+(6-1)/2+5=";
    string b = "sin(pi/6)=";
  
    Calculator cal;
    double d = cal.doIt(a);
    double e = cal.doIt(b);
   
    cout << "��һ�������:" << d << endl
         << "�ڶ��������:" << e << endl;
}