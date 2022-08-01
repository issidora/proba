#include <stdio.h>
#include <cmath>
#include <iostream>

using namespace std;

class Tacka {

public:
    float X, Y, Z;
    Tacka() : Tacka(0, 0, 1) {}
    Tacka(float x, float y, float z = 1) {
        X = x;
        Y = y;
        Z = z;
    }
    void ekran()
    {
        cout << " (" << X << ", " << Y << ", " << Z << ") ";
    }

};
class Duz {


public:
    Tacka a, b;

    Duz(Tacka A, Tacka B) {
        a = A;
        b = B;
    }

    float duzina() {

        return sqrt((a.X - b.X) * (a.X - b.X) + (a.Y - b.Y) * (a.Y - b.Y));
    }

    float ugao() {
        if (a.X - b.X == 0) {
            return 90;
        }
        return atan((a.Y - b.Y) / (a.X - b.X)) * 180 / (atan(1) * 4);
    }

};
class Vektor : public Tacka
{

public:
    Vektor() : Vektor(Tacka(), Tacka()) { }
    Vektor(Tacka p, Tacka k)
    {
        X = k.X - p.X;
        Y = k.Y - p.Y;
        Z = k.Z - p.Z;

    }
    Vektor(float x, float y, float z)
    {
        X = x;
        Y = y;
        Z = z;

    }
    double duzina() {

        return sqrt(X * X + Y * Y + Z * Z);
    }
    double skalarniProizvod(Vektor v) {

        return v.X * X + v.Y * Y + v.Z * Z;
    }
    Vektor vektorskiProizvod(Vektor v) {

        return Vektor(Y * v.Z - Z * v.Y, -X * v.Z + Z * v.X, X * v.Y - Y * v.X);
    }
    void ekran()
    {
        cout << " (" << X << ", " << Y << ", " << Z << ") " << endl;
    }
    float ugao() {
       return acos(this->skalarniProizvod(Vektor(1, 0, 0))/this->duzina());
    }

};
class Trougao
{
public:
    Tacka A, B, C;
    Vektor vektor1;
    Vektor vektor2;
    Vektor vektor3;
    Trougao(Tacka a, Tacka b, Tacka c)
    {
        ;
        A = a;
        B = b;
        C = c;
        vektor1 = Vektor(A, B);
        vektor2 = Vektor(A, C);
        vektor3 = Vektor(B, C);

        if (vektor1.vektorskiProizvod(vektor2).duzina() == 0)
        {
            throw invalid_argument("Tacke su kolinearne");
        }
    }
    float povrsina()
    {
        return (vektor1.vektorskiProizvod(vektor2)).duzina() / 2;
    }
    float obim()
    {
        return vektor1.duzina() + vektor2.duzina() + vektor3.duzina();
    }
    void ekran()
    {
        cout << " Tacka 1 (" << A.X << ", " << A.Y << ", " << A.Z << ") " << endl;
        cout << " Tacka 2 (" << B.X << ", " << B.Y << ", " << B.Z << ") " << endl;
        cout << " Tacka 3 (" << C.X << ", " << C.Y << ", " << C.Z << ") " << endl;
    }

};
class Prava : public Vektor {
public:
    Tacka A;
    Vektor vektor;
    Prava(Tacka p, Tacka k)
    {
        vektor = Vektor(p, k);
        A = p;
    }
    float ugao() {
        if (vektor.X - X == 0) {
            return 90;
        }
        return atan((vektor.Y - Y) / (vektor.X - X)) * 180 / (atan(1) * 4);
    }
    float ugaoIzmedjuDvePrave(Prava p)
    {
        return abs(ugao() - p.ugao());
    }
    float odsecak()
    {
        if (vektor.Y - Y == 0) {
            return Y;
        }
        else if (vektor.X - X == 0) {
            return 0;
        }
        return Y - (Y - vektor.Y) * X / (X - vektor.X);
    }
};

int main()
{

    return 0;
}





