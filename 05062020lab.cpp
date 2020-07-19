#include <iostream>
using namespace std;
class Fraction {
	int sign;           // знак дроби (+ или -)
	int intPart;        // целая часть дроби
	int numerator;      // числитель дроби
	int denominator;    // знаменатель дроби
			//преобразование в смешанный вид
	void GetMixedView();
	void Cancellation();  //сокращение дроби
	void GetIntPart();    //выделение целой части дроби
public:
	//КОНСТРУТОРЫ:
// конструктор без параметров
	inline Fraction();
	// конструктор c параметрами
	inline Fraction(int, int, int = 0, int = 1);
	// конструктор копирования
	inline Fraction(const Fraction& other);
	//деструктор
	~Fraction();
	// МЕТОДЫ:
// метод сложения двух дробей // РАБОТАЕТ
	Fraction operator + (Fraction);
	// метод вычитания двух дробей // РАБОТАЕТ
	Fraction operator - (Fraction);
	// метод умножения двух дробей // РАБОТАЕТ
	Fraction operator * (Fraction);
	// метод деления двух дробей // РАБОТАЕТ
	Fraction operator / (Fraction);
	inline void Print();
};
inline Fraction::Fraction(const Fraction& other) { // конструктор копирования
	sign = other.sign;
	intPart = other.intPart;
	numerator = other.numerator;
	denominator = other.denominator;
	//cout << "Вызвался конструктор копирования " << this << endl;
}
// конструктор класса "Рациональная дробь"
inline Fraction::Fraction(int n, int d, int i, int s) {
	intPart = i;
	numerator = n;
	denominator = d;
	sign = s;
	GetMixedView();
}
// конструктор по умолчанию класса "Рациональная дробь"
inline Fraction::Fraction() {
	intPart = 0;
	numerator = 0;
	denominator = 1;
	sign = 1;
}
// метод преобразования дроби в смешанный вид
void Fraction::GetMixedView() {
	GetIntPart(); //выделение целой части числа
	Cancellation(); //сокращение дроби
}
// метод выделения целой части рационального числа
void Fraction::GetIntPart() {
	if (numerator >= denominator) {
		intPart += (numerator / denominator);
		numerator %= denominator;
	}
}
// метод сокращения рациональной дроби
void Fraction::Cancellation() {
	if (numerator != 0) {
		int m = denominator,
			n = numerator,
			ost = m % n;
		// вычисление НОД(числитель, знаменатель)
		// алгоритмом Евклида
		while (ost != 0) {
			m = n; n = ost;
			ost = m % n;
		}
		int nod = n;
		if (nod != 1) {
			numerator /= nod; denominator /= nod;
		}
	}
}
// деструктор дроби
Fraction::~Fraction() {
	//cout << "Вызвался деструХтор для " << this << endl;
}
/*
Найти сумму или разность двух и более дробей:
Если в одной или нескольких дробях выделена целая часть, переведите эти дроби в неправильные;
-Приведите все дроби к общему знаменателю любым удобным для вас способом (если, конечно, этого не сделали составители задач);
-Сложите или вычтите полученные числа по правилам сложения и вычитания дробей с одинаковыми знаменателями;
-Если возможно, сократите полученный результат. Если дробь оказалась неправильной, выделите целую часть.
Помните, что выделять целую часть лучше в самом конце задачи, непосредственно перед записью ответа.
*/
Fraction Fraction::operator + (Fraction d) {
	Fraction res;
	res.numerator = sign * (intPart * denominator + numerator) * d.denominator + //numerator =  1 * ( 7 * 5 + 1 ) * 2 "+" 1 * (4 * 2 + 3) * 5
		d.sign * (d.intPart * d.denominator + d.numerator) * denominator;
	res.denominator = denominator * d.denominator; // denominator = 5 * 2
	if (res.numerator < 0) {
		res.numerator *= -1; res.sign = -1;
	}
	res.GetMixedView();
	return res;
}
Fraction Fraction::operator - (Fraction d) {
	Fraction res;
	res.numerator = sign * (intPart * denominator + numerator) * d.denominator - //numerator =  1 * ( 7 * 5 + 1 ) * 2 "-" 1 * (4 * 2 + 3) * 5
		d.sign * (d.intPart * d.denominator + d.numerator) * denominator;
	res.denominator = denominator * d.denominator;
	if (res.numerator < 0) {
		res.numerator *= -1; res.sign = -1;
	}
	res.GetMixedView();
	return res;
}
Fraction Fraction::operator * (Fraction d) { //https://www.berdov.com/docs/fraction/multiplication_division/
	Fraction res;
	res.numerator = (sign * (intPart * denominator + numerator)) * //numerator =  (1 * ( 7 * 5 + 1 ) ) "*" (1 * (4 * 2 + 3) )
		(d.sign * (d.intPart * d.denominator + d.numerator));
	res.denominator = denominator * d.denominator;
	if (res.numerator < 0) {
		res.numerator *= -1; res.sign = -1;
	}
	res.GetMixedView();
	return res;
}
Fraction Fraction::operator / (Fraction d) { //https://www.berdov.com/docs/fraction/multiplication_division/
	Fraction res;
	res.numerator = (sign * (numerator + intPart * denominator) * d.denominator); //http://ua.onlinemschool.com/math/assistance/fraction/fraction_calc/
	res.denominator = (denominator * (d.sign * (d.numerator + d.intPart * d.denominator)));
	if (res.numerator < 0) {
		res.numerator *= -1; res.sign = -1;
	}
	res.GetMixedView();
	return res;
}
inline void Fraction::Print() {
	cout << " " << sign << endl << intPart << ' ' << numerator << "/" << denominator << endl;
}
int main() {
	/*	числитель;	знаменатель;	целая часть;	знак числа	*/
	Fraction a(1, 5, 7, -1); // -7 1/5
	Fraction b(3, 2, 4, 1); // 4 3/2
	cout << "***************\" + \"***************" << endl;
	Fraction c1;
	c1 = a + b;
	c1.Print();
	cout << "***************\" - \"***************" << endl;
	Fraction c2;
	c2 = (a - b);
	c2.Print();
	cout << "***************\" * \"***************" << endl;
	Fraction c3;
	c3 = (a * b);
	c3.Print();
	cout << "***************\" / \"***************" << endl;
	Fraction c4;
	c4 = (a / b);
	c4.Print();
}