//
//  main.cpp
//  26_Conversion_In_Inheritance_RTTI_and_Dynamic_Cast
//
//  Created by 세광 on 2021/07/13.
//

// static_cast: 정적 (컴파일)
// dynamic_cast: 동적 (런타임)

// RTTI (Run Time Type Information/Identification)
// 다형 class: 가상 함수가 하나라도 있는 class
// dynamic_cast -> 반드시 다형 class여야 함 (다형 class가 아닐 경우 RTTI 지원 X)

#include <iostream>
#include <cmath>

using namespace std;

class Shape {
public:
    virtual double GetArea() const = 0;
    virtual void Resize(double k) = 0;
};

class Circle : public Shape {
public:
    Circle(double r) : r(r) { }
    double GetArea() const { return r * r * 3.14; }
    void Resize(double k) { r*= k; }
    
private:
    double r;
};

class Rectangle : public Shape {
public:
    Rectangle(double a, double b) : a(a), b(b) { }
    double GetArea() const { return a * b; }
    void Resize(double k) {
        a *= k;
        b *= k;
    }
    double GetDiag() const { return sqrt(a * a + b * b); }
    
private:
    double a, b;
};

int main() {
    Shape *shapes[] = { new Circle(1), new Rectangle(1, 2) };
    
    // 도형의 넓이
    // 만약 직사각형일 경우, 대각선 길이 출력
    for (int i = 0; i < 2; i++) {
        cout << "도형의 넓이: " << shapes[i]->GetArea() << endl;
        Rectangle *r = dynamic_cast<Rectangle*>(shapes[i]);
        // shapes[i]가 가리키고 있는 객체의 타입이 Rectangle일 경우 주소값이 들어감
        // shapes[i]가 가리키고 있는 객체의 타입이 Circle이거나 다른 타입일 경우 (형변환에 실패할 경우) NULL return (dynamic_cast와 static_cast의 차이점)
        if (r != NULL) cout << "대각선의 길이: " << r->GetDiag() << endl;
    }
    
    for (int i = 0; i < 2; i++) delete shapes[i];
}
