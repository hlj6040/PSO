#include "acllib.h"
#include "PSO.h"
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <Windows.h>
#pragma warning(disable : 4996)
using  namespace std;

int n;
int mapX, mapY;//表示窗口的大小
const int  d = 6; // 绘制的单位
typedef pair <double, double> poin;
typedef  vector<poin> arr;  // 存放路径

//绘制路径
void drawPath(arr a) {

	if (a.size())
		moveTo((a[0].first) * d + d / 2, (a[0].second) * d + d / 2);
	for (int i = 1; i < a.size(); i++) {
			lineTo(a[i].first * d + d / 2, a[i].second * d + d / 2);
			//printf("%lf  %lf\n", a[i].first, a[i].second);
	}
}


//绘制障碍
void drawBar(arr a) {

	for (int i = 0; i < a.size(); i++) {
		arc(a[i].first * d, a[i].second * d, a[i].first * d + d, a[i].second * d + d, a[i].first * d, a[i].first * d + d / 2, a[i].first * d, a[i].first * d + d / 2);
	}
}


void  draw() {

	for (int i = 0; i < 500; i += d) {
		moveTo(i, 0);
		lineTo(i, 500);
		moveTo(0, i);
		lineTo(500, i);
	}
}

bool cmp(poin x, poin y) {
	if (x.first == y.first)
		return x.second < y.second;
	return x.first < y.first;
}

//判断障碍与路径是否重合

bool  True(arr path, arr bar) {
	sort(path.begin(), path.end(), cmp);
	sort(bar.begin(), bar.end(), cmp);
	int i = 0, j = 0;
	int lenP = path.size();
	int lenB = bar.size();
	while (i < lenP && j < lenB) {
		if (path[i].first == bar[j].first && path[i].second == bar[j].second)
			return false;
		if (path[i].first < bar[j].first || (path[i].first == bar[j].first && path[i].second < bar[j].second))
			i++;
		else {
			j++;
		}
	}
	return true;
}

double  f(double x) {
	return (1 - cos(3 * x) * exp(-x));
}

void drawline(double x, double y) {
	moveTo(x, mapY);
	lineTo(x, mapY - y);
}

int i = 0, j = 0;
arr track_A, track_B;
void timer(int){
	
	
	beginPaint();
	//clearDevice();
	if (i < track_A.size())
		drawBar({ track_A[i] }),
		i++;

	//setPenColor(BLACK);
	if (j < track_B.size())
		drawBar({ track_B[j] }),
		j++;

	if (i >= track_A.size() && j >= track_B.size())
		/*cancelTimer(0);*/
		i = j = 0;
	endPaint();
}

int Setup()
{

	mapX = 500;
	mapY = 500;
	/*int tmp = 500 / d - 1;*/
	//arr  a = { poin(0,tmp - 0),poin(0,tmp - 7),poin(6.5,tmp - 7),poin(6,tmp - 9),poin(5,tmp - 9),poin(5,tmp - 14) };// 路径
	//arr  b = { poin(0,0),poin(3,9), poin(9,9) };					//障碍
	initWindow("submer", DEFAULT, DEFAULT, mapX, mapY);

	Motion_track  c = Motion_track({ 12,10 }, { 18,15 });
	vector<vector<double>> A = c.getA_track();
	vector<vector<double>> B = c.getB_track();
	
	int len = A.size();
	
	for (int i = 0; i < len; i++) {
		track_A.push_back(poin(A[i][0], A[i][1]));
		
	}

	for (int i = 0; i < len ; i++) {
		track_B.push_back(poin(B[i][0],B[i][1]));
	}
	

	registerTimerEvent(timer);
	startTimer(0, 10);
	return 0;
}
