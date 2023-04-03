#include <iostream>
#include <string>

using namespace std;

class ComplexNumber{
    public:
        int a = 0;
        int b = 0;
};

void print(ComplexNumber num){
    if (num.b == 0)
        printf("%d", num.a);
    else if (num.a == 0 && num.b > 1)
        printf("%di", num.b);
    else if (num.a == 0 && num.b == 1)
        printf("i");
    else if (num.b > 0 && num.b > 1)
        printf("%d + %di", num.a, num.b);
    else if (num.b > 0 && num.b == 1)
        printf("%d + i", num.a);
    else
        printf("%d - %di", num.a, num.b*(-1));
    cout << endl;
}

void add(ComplexNumber num1, ComplexNumber num2){
    ComplexNumber result;

    result.a = num1.a + num2.a;
    result.b = num1.b + num2.b;

    print(result);
}

void multiply(ComplexNumber num1, ComplexNumber num2){
    ComplexNumber result;

    result.a = num1.a*num2.a - num1.b*num2.b;
    result.b = num1.a*num2.b + num1.b*num2.a;

    print(result);
}

int main()
{
    int n;
    cin >> n;
    char temp = ' ';
    ComplexNumber num1;
    ComplexNumber num2;

    for (int i = 0; i < n; i++){
        cin >> temp;
        switch(temp){
            case 'p':
                cin >> num1.a >> num1.b;
                print(num1);
                break;
            case '+':
                cin >> num1.a >> num1.b >> num2.a >> num2.b;
                add(num1, num2);
                break;
            case '*':
                cin >> num1.a >> num1.b >> num2.a >> num2.b;
                multiply(num1, num2);
                break;
        }
    }
    return 0;
}
