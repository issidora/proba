#include "pbPlots.hpp"
#include "supportLib.hpp"
#include <iostream>
#include <cmath>
#include <stack>
#include <algorithm>

#define PI acos(-1)

using namespace std;

class Tacka
{
public:
	float X, Y, Z;

	Tacka() : Tacka(0, 0, 0) { }
	Tacka(float x, float y, float z = 1)
	{
		X = x;
		Y = y;
		Z = z;
	}

	void ekran()
	{
		cout << " (" << X << ", " << Y << ", " << Z << ") ";
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
		X = x; Y = y; Z = z;
	}
	float norma()
	{
		return sqrt(X * X + Y * Y + Z * Z);
	}

	float skalarni_proizvod(Vektor v)
	{
		return X * v.X + Y * v.Y + Z * v.Z;
	}
	Vektor vektorski_proizvod(Vektor v)
	{
		return Vektor(Tacka(Y * v.Z, Z * v.X, X * v.Y), Tacka(Z * v.Y, X * v.Z, Y * v.X));
	}
	float ugao()
	{
		if (X == 0 && Y != 0) return (PI/2);
		else if (X == 0) return 0;
		else if(Y / X < 0) return atan(Y / X) + PI;
		else return atan(Y / X);
	}
	float ugao(Vektor v)
	{
		if (this->norma() != 0 && v.norma() != 0)
			return acos(this->skalarni_proizvod(v) / (this->norma() * v.norma()));
	}
	short int orijentacija(Vektor v)
	{
		if (this->vektorski_proizvod(v).skalarni_proizvod(Vektor(0, 0, 1) )< 0) return 1;
		else if (this->vektorski_proizvod(v).skalarni_proizvod(Vektor(0, 0, 1) )> 0) return -1;
		else return 0;
	}
	void ekran()
	{
		cout << " (" << X << ", " << Y << ", " << Z << ") " << endl;
	}
};

class Prava : public Vektor
{
public:
	//float X, Y, Z;
	Tacka T;
	Vektor prava;

	Prava(Tacka p, Tacka k)
	{
		prava = Vektor(p, k);
		T.X = p.X;
		T.Y = p.Y;
		T.Z = p.Z;
	}
	float ugao()
	{
		if (prava.X - T.X == 0) return PI / 2;
		else return atan((prava.Y - T.Y) / (prava.X - T.X));
	}
	float odsecak()
	{
		if (prava.Y - T.Y == 0) return T.Y;
		else if (prava.X - T.X == 0) return 0;
		else return T.Y - (T.Y - prava.Y) * T.X / (T.X - prava.X);
	}
	float ugaoPravih(Prava p)
	{
		return abs(ugao() - p.ugao());
	}
};
class Duz : public Tacka
{
protected:
	Tacka a1, b1;
public:
	Duz(Tacka a, Tacka b)
	{
		a1 = a;
		b1 = b;
	}
	float duzina()
	{
		Vektor v1 = Vektor(Tacka(a1.X, a1.Y, a1.Z), Tacka(b1.X, b1.Y, b1.Z));
		return v1.norma();
	}
	float ugao()
	{
		if (a1.X - b1.X == 0) return 90;
		else return atan((a1.Y - b1.Y) / (a1.X - b1.X)) * 180 / (atan(1) * 4);
	}
};
class Trougao : public Tacka
{
protected:
	Tacka a1, b1, c1;
public:
	Trougao(Tacka a, Tacka b, Tacka c)
	{
		if (sqrt(pow((a.Y - b.Y) * (a.Z - c.Z) - (a.Z - b.Z) * (a.Y - c.Y), 2) + pow((a.Z - b.Z) * (a.X - c.X) - (a.X - b.X) * (a.Z - c.Z), 2) + pow((a.X - b.X) * (a.Y - c.Y) - (a.Y - b.Y) * (a.X - c.X), 2)) == 0)
		{
			throw runtime_error("Greska! Tacke su kolinearne");
		}
		a1 = a;
		b1 = b;
		c1 = c;

	}
	float povrsina()
	{
		Vektor v1 = Vektor(a1, b1);
		Vektor v2 = Vektor(a1, c1);
		return (v1.vektorski_proizvod(v2)).norma() / 2;
	}
	float obim()
	{
		Vektor v1 = Vektor(a1, b1);
		Vektor v2 = Vektor(a1, c1);
		Vektor v3 = Vektor(b1, c1);
		return v1.norma() + v2.norma() + v3.norma();
	}
	void ekran()
	{
		cout << " Tacka 1 (" << a1.X << ", " << a1.Y << ", " << a1.Z << ") " << endl;
		cout << " Tacka 2 (" << b1.X << ", " << b1.Y << ", " << b1.Z << ") " << endl;
		cout << " Tacka 3 (" << c1.X << ", " << c1.Y << ", " << c1.Z << ") " << endl;
		RGBABitmapImageReference* imageReference = CreateRGBABitmapImageReference();

		vector<double> xs{ a1.X, b1.X, c1.X, a1.X };
		vector<double> ys{ a1.Y, b1.Y, c1.Y, a1.Y };
		/*wstring s;*/
		StringReference* error = CreateStringReference(toVector(L""));
		DrawScatterPlot(imageReference, 600, 400, &xs, &ys);
		vector<double>* pngdata = ConvertToPNG(imageReference->image);
		WriteToFile(pngdata, "example5.png");
		DeleteImage(imageReference->image);
	}
};

Tacka Min_Tacka;
bool sortPoUglu(Tacka T1, Tacka T2)
{
	Vektor v1(Min_Tacka, T1);
	Vektor v2(Min_Tacka, T2);
	if (v1.ugao() < v2.ugao()) return true;
	else if (v1.ugao() == v2.ugao() && v1.norma() < v2.norma()) return true;
	else return false;
}
class Poligon {
public:
	vector<Tacka> Temena;
	int N;
	Poligon(vector<Tacka> _Temena)
	{
		Temena = _Temena;
		N = _Temena.size();
	}
	void prost()
	{
		Tacka Min = Temena[0];
		//nalazimo najlevlju, najnizu tacku
		for (auto T : Temena)
		{
			if (Min.Y > T.Y) Min = T;
			else if ((Min.Y == T.Y) && (Min.X > T.X)) Min = T;
		}
		Min_Tacka = Min;
		sort(Temena.begin(), Temena.end(), sortPoUglu);
	}
	Poligon giftWrapping() 
	{
		vector<Tacka> v;
		v.push_back(Temena[0]);
		v.push_back(Temena[1]);
		v.push_back(Temena[2]);
		short int skretanje = Vektor(Temena[0], Temena[1]).orijentacija(Vektor(Temena[1], Temena[2]));
		cout << skretanje << endl;
		int t;		
		for (int i=3; i<N; i++)
		{
			t = v.size()-1;
			if (Vektor(v[t-1], v[t]).orijentacija(Vektor(v[t], Temena[i])) == skretanje) v.push_back(Temena[i]);
			else {				
				do 
				{
					v[t].ekran();
					cout << endl << endl;
					v.pop_back();
					t--;
				} while (Vektor(v[t - 1], v[t]).orijentacija(Vektor(v[t], Temena[i])) != skretanje && t > 1);
				v.push_back(Temena[i]);
			}							
		}
		return Poligon(v);
	}
	void ekran(string ime)
	{
		vector<double> xs;
		vector<double> ys;
		for (auto T : Temena)
		{
			cout << " (" << T.X << ", " << T.Y << ", " << T.Z << ") " << endl;
			xs.push_back(T.X);
			ys.push_back(T.Y);
		}
		cout << endl;
		xs.push_back(Temena[0].X);
		ys.push_back(Temena[0].Y);

		RGBABitmapImageReference* imageReference = CreateRGBABitmapImageReference();

		/*wstring s;*/
		StringReference* error = CreateStringReference(toVector(L""));
		DrawScatterPlot(imageReference, 600, 600, &xs, &ys);
		vector<double>* pngdata = ConvertToPNG(imageReference->image);
		WriteToFile(pngdata, ime);
		DeleteImage(imageReference->image);
	}
};
int main()
{
	float x, y;
	vector<Tacka> temena;
	while (cin >> x >> y)
	{
		temena.push_back(Tacka(x, y));
	}
	Poligon p(temena);
	p.ekran("poligon1.png");
		p.prost();
	p.ekran("poligon2.png");
	Poligon convexHull = p.giftWrapping();
	convexHull.ekran("poligon3.png");

	return 0;
}


