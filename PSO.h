#pragma once
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <cmath>
using namespace std;

class PSO_findPoin
{
public:
	const  int N = 5; // 种群规模
	const  int D = 2; //粒子维度
	const  int T = 500; // 迭代次数
	const  double C1 = 1.5;  // 个体学习因子
	const  double C2 = 1.5;  // 社会学习因子
	const  double W = 0.8;   // 权重因子


	double Xmax = 20;
	double Xmin = -20; //X位置，位置就是自变量的值

	int Vmax = 10; // 速度最大值，每一步自变量X改变的大小
	int Vmin = -10;

	double gBestValue; //全局最优解
	int  gBestValue_index;

	vector<vector<double>> tBest;
	vector<vector<double>> popx;
	vector<vector<double>> popv;

	vector<vector<double>> pBest;
	vector<double> pBestValue;
	vector<double> gBest;
	vector<double> poinB; // 逼近点

	double  RA = 1;
	double  RB = 2;
	

	// 最优解

	vector<double> BestAns;

	vector<vector<double>> drawPath;
	//随机数
	long long getnum(int x = 3);

	long long random(long long x, long long y);//生成[x,y]的随机数

	double  Rand();//返回[0,1]的随机数

	//目标函数


	double  juli(double x1, double y1, double x2, double y2);

	vector<double> findPoin(vector<vector<double>> popx);

	double  findPoin(vector<double> popx);




	vector<vector<double>> zeros(int row, int column);//生成row行 column列的矩阵

	vector<vector<double>> initPopX(int row, int column);//初始化粒子群的位置row行 column列

	vector<vector<double>> initPopV(int row, int column);

	int  findIndex(vector<double> vect);//返回向量的最大值下标

	void updatePopv(vector<double>& popv, vector<double> popx, vector<double> pBest, vector<double> gBest);//速度

	void updatePopx(vector<double>& popx, vector<double> popv); //位置更新

	void defBoundaries(vector<double>& popx, vector<double>& popv);//限定边界

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
	const  int N = 5; // 种群规模
	const  int D = 1; //粒子维度
	const  int T = 200; // 迭代次数
	const  double C1 = 1.5;  // 个体学习因子
	const  double C2 = 1.5;  // 社会学习因子
	const  double W = 0.8;   // 权重因子


	double Xmax = PI;
	double Xmin = -PI; //X位置，位置就是自变量的值

	int Vmax = PI/2; // 速度最大值，每一步自变量X改变的大小
	int Vmin = -PI/2;

	double gBestValue; //全局最优解
	int  gBestValue_index;

	vector<vector<double>> tBest;
	vector<vector<double>> popx;
	vector<vector<double>> popv;

	vector<vector<double>> pBest;
	vector<double> pBestValue;
	vector<double> gBest;
	vector<double> poinA; // 更新点
	vector<double> poinB; // 逼近点

	double  RA = 1;
	double  RB = 2;


	// 最优解

	vector<double> BestAns;

	vector<vector<double>> drawPath;
	//随机数
	long long getnum(int x = 3);

	long long random(long long x, long long y);//生成[x,y]的随机数

	double  Rand();//返回[0,1]的随机数

	//目标函数


	double  juli(double x, double y);

	vector<double> findPoin(vector<vector<double>> popx);

	double  findPoin(vector<double> popx);

	vector<vector<double>> zeros(int row, int column);//生成row行 column列的矩阵

	vector<vector<double>> initPopX(int row, int column);//初始化粒子群的位置row行 column列

	vector<vector<double>> initPopV(int row, int column);

	int  findIndex(vector<double> vect);//返回向量的最大值下标

	void updatePopv(vector<double>& popv, vector<double> popx, vector<double> pBest, vector<double> gBest);//速度

	void updatePopx(vector<double>& popx, vector<double> popv); //位置更新

	void defBoundaries(vector<double>& popx, vector<double>& popv);//限定边界

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
	typedef vector<double> Point;//点
	typedef vector<double> V; //速度
	vector<double> poinA;
	vector<double> poinB;
	vector<Point> A_track;  // A的运动轨迹
	vector<Point> B_track;	// B的运动轨迹
	const  double  A_maxV = 4; // A的速度大小
	const  double  B_maxV = 2;	// B的速度大小
	vector<V>  B_V;//存放B的速度变化
	double  t = 300; // 迭代次数

public:
	Motion_track(Point A, Point B);
	void  makeTrack(vector<Point>& tack, double t);
	Point yunFunction(double t);
	Point VFunction(double t);
	void  make_V(vector<V> &B, double t);
	double  dushu(Point A, Point B); //求两点连线的角度
	vector < vector<double> >getA_track();
	vector < vector<double> >getB_track();
	void  test();
};
