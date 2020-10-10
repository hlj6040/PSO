#pragma once
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <cmath>
using namespace std;

class PSO_findPoin
{
public:
	const  int N = 5; // ��Ⱥ��ģ
	const  int D = 2; //����ά��
	const  int T = 500; // ��������
	const  double C1 = 1.5;  // ����ѧϰ����
	const  double C2 = 1.5;  // ���ѧϰ����
	const  double W = 0.8;   // Ȩ������


	double Xmax = 20;
	double Xmin = -20; //Xλ�ã�λ�þ����Ա�����ֵ

	int Vmax = 10; // �ٶ����ֵ��ÿһ���Ա���X�ı�Ĵ�С
	int Vmin = -10;

	double gBestValue; //ȫ�����Ž�
	int  gBestValue_index;

	vector<vector<double>> tBest;
	vector<vector<double>> popx;
	vector<vector<double>> popv;

	vector<vector<double>> pBest;
	vector<double> pBestValue;
	vector<double> gBest;
	vector<double> poinB; // �ƽ���

	double  RA = 1;
	double  RB = 2;
	

	// ���Ž�

	vector<double> BestAns;

	vector<vector<double>> drawPath;
	//�����
	long long getnum(int x = 3);

	long long random(long long x, long long y);//����[x,y]�������

	double  Rand();//����[0,1]�������

	//Ŀ�꺯��


	double  juli(double x1, double y1, double x2, double y2);

	vector<double> findPoin(vector<vector<double>> popx);

	double  findPoin(vector<double> popx);




	vector<vector<double>> zeros(int row, int column);//����row�� column�еľ���

	vector<vector<double>> initPopX(int row, int column);//��ʼ������Ⱥ��λ��row�� column��

	vector<vector<double>> initPopV(int row, int column);

	int  findIndex(vector<double> vect);//�������������ֵ�±�

	void updatePopv(vector<double>& popv, vector<double> popx, vector<double> pBest, vector<double> gBest);//�ٶ�

	void updatePopx(vector<double>& popx, vector<double> popv); //λ�ø���

	void defBoundaries(vector<double>& popx, vector<double>& popv);//�޶��߽�

	PSO_findPoin(vector<double> poinB, double RA, double RB);
	vector<double> gettBest();
	vector<vector<double>> getpopx();
	vector<vector<double>> getpBest();
	vector<double> getpBestValue();
	void  test();
}
;

class PSO_updata
{
public:
	const  double PI = 3.14159265358979323846;
	const  int N = 5; // ��Ⱥ��ģ
	const  int D = 1; //����ά��
	const  int T = 200; // ��������
	const  double C1 = 1.5;  // ����ѧϰ����
	const  double C2 = 1.5;  // ���ѧϰ����
	const  double W = 0.8;   // Ȩ������


	double Xmax = PI;
	double Xmin = -PI; //Xλ�ã�λ�þ����Ա�����ֵ

	int Vmax = PI/2; // �ٶ����ֵ��ÿһ���Ա���X�ı�Ĵ�С
	int Vmin = -PI/2;

	double gBestValue; //ȫ�����Ž�
	int  gBestValue_index;

	vector<vector<double>> tBest;
	vector<vector<double>> popx;
	vector<vector<double>> popv;

	vector<vector<double>> pBest;
	vector<double> pBestValue;
	vector<double> gBest;
	vector<double> poinA; // ���µ�
	vector<double> poinB; // �ƽ���

	double  RA = 1;
	double  RB = 2;


	// ���Ž�

	vector<double> BestAns;

	vector<vector<double>> drawPath;
	//�����
	long long getnum(int x = 3);

	long long random(long long x, long long y);//����[x,y]�������

	double  Rand();//����[0,1]�������

	//Ŀ�꺯��


	double  juli(double x, double y);

	vector<double> findPoin(vector<vector<double>> popx);

	double  findPoin(vector<double> popx);

	vector<vector<double>> zeros(int row, int column);//����row�� column�еľ���

	vector<vector<double>> initPopX(int row, int column);//��ʼ������Ⱥ��λ��row�� column��

	vector<vector<double>> initPopV(int row, int column);

	int  findIndex(vector<double> vect);//�������������ֵ�±�

	void updatePopv(vector<double>& popv, vector<double> popx, vector<double> pBest, vector<double> gBest);//�ٶ�

	void updatePopx(vector<double>& popx, vector<double> popv); //λ�ø���

	void defBoundaries(vector<double>& popx, vector<double>& popv);//�޶��߽�

	PSO_updata(vector<double> poinA, vector<double> poinB, double RA, double RB);
	vector<double> gettBest();
	vector<vector<double>> getpopx();
	vector<vector<double>> getpBest();
	vector<double> getpBestValue();
	void  test();
}
;

class Motion_track
{	
	const  double PI = 3.14159265358979323846;
	typedef vector<double> Point;//��
	typedef vector<double> V; //�ٶ�
	vector<double> poinA;
	vector<double> poinB;
	vector<Point> A_track;  // A���˶��켣
	vector<Point> B_track;	// B���˶��켣
	const  double  A_maxV = 4; // A���ٶȴ�С
	const  double  B_maxV = 2;	// B���ٶȴ�С
	vector<V>  B_V;//���B���ٶȱ仯
	double  t = 300; // ��������

public:
	Motion_track(Point A, Point B);
	void  makeTrack(vector<Point>& tack, double t);
	Point yunFunction(double t);
	Point VFunction(double t);
	void  make_V(vector<V> &B, double t);
	double  dushu(Point A, Point B); //���������ߵĽǶ�
	vector < vector<double> >getA_track();
	vector < vector<double> >getB_track();
	void  test();
};
