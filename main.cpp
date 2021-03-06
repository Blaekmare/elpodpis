#include<string>
#include <iostream>
#include <ctime>
#include "MD5.h"
using namespace std;
int Evclid(int e, int fi){
	int a=0,b=0;
	if(e>fi){
		a=e;
		b=fi;
	}else{
		b=e;
		a=fi;
	}
	int u=0;
	int v=1;
	int m=a;
	while (b!=0){
		int q=a/b;
		int r=a%b;
		int vk=u-v*q;
		a=b;
		b=r;
		u=v;
		v=vk;
	}
	while(u<0)u+=m;
	while(u>=m)u-=m;
	return u;
}
int Prost(int P){
	for(int i=2;i<=P/2;i++){
		if(P%i==0)return 0;
	}
	return 1;
}
int Gen_P(){
	int P;
	do{
		P=rand()%99+10;
	}while(Prost(P)!=1);
	return P;
}
int Gen_Q(int p){
	int q;
	do{
		q=rand()%99+10;
	}while(Prost(q)!=1);
	return q;
}
int gcd(int a,int b){
	if(a>b){a=a,b=b;}else{int c=a;a=b,b=c;}
	int r;
	while(b!=0){
		r=a%b;
		a=b;b=r;
	}
	return a;
}
int Gen_e(int fi){
	int e;
	do{
		e=rand()%(fi-1)+2;
	}while(gcd(e, fi)!=1);
	return e;
}
int step(int a,int b,int c){
	int r=a;
	for(int i=1;i<b;i++){
		r*=a;
		while (r>c){
			r=r-c;
		}
	}
	return r;
}
void RSA(int mass[]){
	int p, q, n, fi, e, d,m;
	int l = 1,t,c;
	p = Gen_P();
	std::cout << p << std::endl;
	q = Gen_Q(p);
	std::cout << q << std::endl;
	n = p * q;
	fi = (p - 1) * (q - 1);
	std::cout << fi << std::endl;
	e = Gen_e(fi);
	std::cout<<"e"<< e << std::endl;
	d=Evclid(e,fi);
	std::cout<<"d" << d << std::endl;
	m=100;
	c = step(m, e, n);
	t = step(c, d, n);
	std::cout << c << std::endl;
	std::cout << t << std::endl;
	if(t==m)std::cout<<"OK";
	mass[0]=e;
	mass[1]=d;
	mass[3]=n;

}

int main() {
	srand(time(0));
	int i, m;
	int mass[3];
	string text, Code,rsac1,rsac2;
	cin >> text;
	RSA(mass);
	Code= md5(text);
	for(i=0;Code.length();i++){
	m=int(Code[i]);
	rsac1+=step(m,mass[1],mass[3]);
	}
	cout<<"shifr "<<rsac1<<endl;

	for(i=0;Code.length();i++){
		m=int(rsac1[i]);
		rsac2+=step(m,mass[2],mass[3]);
	}
	cout<<"deshifr "<<rsac2<<endl;
	/*for(int i=0;i<2;i++)
		cout<<mass[i]<<endl;
	*/
}