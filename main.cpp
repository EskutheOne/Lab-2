#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include "winbgi2.h"
#include "kwad.h"
#include <stdlib.h>

double funkcja1(double x);
double funkcja2(double x);

double anali1(double a, double b);
double anali2(double a, double b);
double kwadratura(double a, double b, double (*pf)(double), long double xi[5], long double wi[5]);

void wyczyscbufor()      //funkcja czysczaca bufor, potrzebna do obslugi bledow np gdy ktos wpisze znak zamiast liczby

{
                int n;
                while ((n = getchar()) != EOF && n != '\n');
}

void main()
{

	int n,m,warunek;
	double a,b, *cn, ca, *blad;
	FILE *g;

	long double wi[5] = {0.2369268850561890875142640, 0.4786286704993664680412915, 0.5688888888888888888888889, 0.4786286704993664680412915, 0.2369268850561890875142640};
	long double xi[5] = {-0.9061798459386639927976269, -0.5384693101056830910363144, 0.0, 0.5384693101056830910363144, 0.9061798459386639927976269};

do
{
	printf("Jaka funkcje chcesz rozpratywac \n \t 1  1/x^2 \n \t 2  1/x \n");
	scanf("%d",&warunek);
	wyczyscbufor();
}while(warunek!=1 && warunek!=2);

do
{
	printf("Podaj potege m \n");
	scanf("%d",&m);
	wyczyscbufor();
}while(m<=0);

	cn = (double*)malloc(m*sizeof(double));
	blad = (double*)malloc(m*sizeof(double));

	if(cn==NULL && ca==NULL && blad==NULL)
		{
			printf("Wystapil blad alokacji :( \n");
			exit(1);
		}

	g = fopen("plik.txt","w");
	if(!g)
		{
			printf("Wystapil blad przy otwieraniu pliku!");
			exit(1);
		}
	fprintf(g," \tCN\tCA\tBLAD\tSIMP\tBLAD SIMP\n");

	printf("Podaj a, b \n");
	scanf("%lf\n %lf",&a,&b);
	

	if(warunek==1)
		{
			double p;
			double simp1;
			ca=anali1(a,b);
			for(int i=0;i<m;i++)
				{ 
					p=i+1;
					n=pow(2,p);
					cn[i]=trapez(a,b,funkcja1,n);
					blad[i]=abs(cn[i]-ca);

					printf("Cn[%i] = %.8f \t",i,cn[i]);
					fprintf(g,"%i\t%.8f\t",i,cn[i]);
					printf("Ca = %.8f \t",ca);
					fprintf(g,"%.8f\t",ca);
					printf("Blad[%i] = %.8f \n",i,blad[i]);
					fprintf(g,"%.8f\t",blad[i]);

					simp1=simpson(a,b,funkcja1,n);
					printf("Metoda Simpsona = %.8f \t",simp1);
					fprintf(g,"%.8f\t",simp1);
					printf("Blad Simpsona = %.8f \n\n",abs(ca-simp1));
					fprintf(g,"%.8f\n",abs(ca-simp1));

				}
			double kwad1=kwadratura(a,b,funkcja1,xi,wi);
			printf("Kwadratura = %.8f\t",kwad1);
			printf("Blad kwadratury = %.8f\n",abs(ca-kwad1));
		}

	else
		{
			double z;
			double simp2;
			ca=anali2(a,b);
			for(int j=0;j<m;j++)
				{
					z=j+1;
					n=pow(2,z);
					cn[j]=trapez(a,b,funkcja2,n);
					blad[j]=abs(cn[j]-ca);

					printf("Cn[%i] = %.8f \t",j,cn[j]);
					fprintf(g,"%i\t%.8f\t",j,cn[j]);
					printf("Ca = %.8f \t",ca);
					fprintf(g,"%.8f\t",ca);
					printf("Blad[%i] = %.8f \n",j,blad[j]);
					fprintf(g,"%.8f\t",blad[j]);

					simp2=simpson(a,b,funkcja2,n);
					printf("Metoda Simpsona = %.8f \t",simp2);
					fprintf(g,"%.8f\t",simp2);
					printf("Blad Simpsona = %.8f \n\n",abs(ca-simp2));
					fprintf(g,"%.8f\n",abs(ca-simp2));

				}
			double kwad2=kwadratura(a,b,funkcja2,xi,wi);
			printf("Kwadratura = %.8f \t",kwad2);
			printf("Blad kwadratury = %.8f\n",abs(ca-kwad2));
		}

	fclose(g);
	free(cn);
	free(blad);
	wait();
}

double funkcja1(double x)
{
	return 1/(x*x);
}

double funkcja2(double x)
{
	return 1/x;
}

double anali1(double a, double b)
{
	return (-(1/b)+(1/a));
}

double anali2(double a, double b)
{
	return log(abs(b))-log(abs(a));
}

double kwadratura(double a, double b, double (*pf)(double), long double xi[5], long double wi[5])
{
	double wynik=0;
	double t=0;
			
			for(int i=0;i<5;i++)
				{
					t = (a+b)/2 + ((b-a)/2)*xi[i];
					wynik += wi[i]*pf(t);

				}
	return ((b-a)/2)*wynik;
}


