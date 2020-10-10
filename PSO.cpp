#include "PSO.h"

vector<double> PSO_findPoin::gettBest() {
    return  this->tBest[0];
}

PSO_findPoin::PSO_findPoin(vector<double> poinB, double RA, double RB) {
    srand(unsigned(time(NULL)));

    this->poinB = poinB;
    this->RA = RA;
    this->RB = RB;

    tBest = zeros(1, 100);
    popx = initPopX(N, D);
    popv = initPopV(N, D);
    poinB = { 3,4 };


    pBest = popx; //初始化每个粒子的最优位置 矩阵维度为[100,10]
    pBestValue = findPoin(pBest);   //初始化每个最佳个体的适应度 矩阵维度为为[100,1]

    vector<double> t;
    t = findPoin(popx);
    gBestValue_index = findIndex(t); // 返回列向量的最大值的下标
	BestAns = popx[gBestValue_index];
    if (t.size())
        gBestValue = t[gBestValue_index],
        gBest = popx[gBestValue_index]; // 根据最大值返回的索引，找到粒子的位置
    else
        printf("error");
    test();
}



//随机数

long long PSO_findPoin::getnum(int x)
{
    long long res = 0;
    for (int i = 1; i <= x; i++)
    {
        long long ttt = 1;
        for (int j = 1; j <= i; j++)
        {
            ttt *= rand();
        }
        res += ttt;
    }
    return abs(res);
}

//生成[x,y]的随机数
long long PSO_findPoin::random(long long x, long long y)
{
    return x + getnum() % (y - x + 1);
}

//返回[0,1]的随机数void PSO_findPoin::
double PSO_findPoin::Rand() {
    return (rand() / (1. * RAND_MAX));
}



double PSO_findPoin::juli(double x1, double y1, double x2, double y2)
{
    return (sqrt((x1 - x2) * (x1 - x2)) + (y1 - y2) * (y1 - y2));
}

vector<double> PSO_findPoin::findPoin(vector<vector<double>> popx)
{
    double x1 = poinB[0], y1 = poinB[1];
    vector<double> obj;
    for (int i = 0; i < popx.size(); i++) {
        int x = popx[i][0],
            y = popx[i][1];
        obj.push_back(abs(RB+RA-juli(x1, y1, x, y)));
    }
    return obj;
}

double PSO_findPoin::findPoin(vector<double> pop)
{
    return  (abs(RA+RB-(juli(pop[0], pop[1], poinB[0], poinB[1]))));
}

//生成row行 column列的矩阵
vector<vector<double>> PSO_findPoin::zeros(int row, int column) {
    vector<vector<double>> re;
    for (int i = 0; i < row; i++) {
        vector<double> t;
        for (int j = 0; j < column; j++)
            t.push_back(.0);

        re.push_back(t);
    }
    return re;
}

//初始化粒子群的位置row行 column列
vector<vector<double>> PSO_findPoin::initPopX(int row, int column) {
    vector<vector<double>> popx;

    for (int i = 0; i < row; i++) {
        vector<double> t;
        for (int j = 0; j < column; j++)
            t.push_back(Rand() * (Xmax*1. - Xmin*1.) + Xmin);
        popx.push_back(t);
    }

    return popx;
}


vector<vector<double>> PSO_findPoin::initPopV(int row, int column) {
    vector<vector<double>> popV;

    for (int i = 0; i < row; i++) {
        vector<double> t;

        for (int j = 0; j < column; j++)
            t.push_back(Rand() * (Vmax*1. - Vmin*1.) + Vmin);

        popV.push_back(t);
    }

    return popV;
}

//返回向量的最大值下标
int  PSO_findPoin::findIndex(vector<double> vect) {
    int index = 0;
    for (int i = 0; i < vect.size(); i++) {
        if (vect[i] < vect[index])
            index = i;
    }

    return index;
}

//速度更新
void PSO_findPoin::updatePopv(vector<double>& popv, vector<double> popx, vector<double> pBest, vector<double> gBest) {
    for (int i = 0; i < popv.size(); i++) {
        popv[i] = W * popv[i] + C1 * Rand() * (pBest[i] - popx[i]) + C2 * Rand() * (gBest[i] - popx[i]);
    }
}


//位置更新
void PSO_findPoin::updatePopx(vector<double>& popx, vector<double> popv) {
    for (int i = 0; i < popx.size(); i++) {
        popx[i] += popv[i];
    }
}

//限定边界
void PSO_findPoin::defBoundaries(vector<double>& popx, vector<double>& popv) {
    for (int i = 0; i < D; i++) {
        if (popx[i] > Xmax || popx[i] < Xmin) {
            popx[i] = Rand() * (Xmax*1. - Xmin*1.) + Xmin;
        }

        if (popv[i] > Vmax || popv[i] < Vmin) {
            popv[i] = Rand() * (Vmax*1. - Vmin*1.) + Vmin;
        }
    }
}

vector<vector<double>> PSO_findPoin::getpopx() {
    return this->popx;
}
vector<vector<double>> PSO_findPoin::getpBest() {
    return this->pBest;
}

vector<double> PSO_findPoin::getpBestValue()
{
    return this->pBestValue;
}

void PSO_findPoin::test()
{
    for (int t = 0; t < T; t++) {    //迭代次数
        for (int i = 0; i < N; i++) {

            // 更新速度位置
            updatePopv(popv[i], popx[i], pBest[i], gBest);
            updatePopx(popx[i], popv[i]);

            //限定边界
            defBoundaries(popx[i], popv[i]);

            //更新最优

            double tValue = findPoin(popx[i]);
            if (tValue  < pBestValue[i]) {
                pBest[i] = popx[i];
                pBestValue[i] = tValue;

            }
            else if (pBestValue[i] < gBestValue) {
                gBest = pBest[i];
                gBestValue = pBestValue[i];
            }
        }
		int  indexx = findIndex(pBestValue);
		BestAns = popx[indexx];
        for (int i = 0; i < popx.size(); i++)
            drawPath.push_back(popx[i]);
    }
}


//PSO_updata

vector<double> PSO_updata::gettBest() {
    return  this->tBest[0];
}

PSO_updata::PSO_updata(vector<double> poinA, vector<double> poinB, double RA, double RB) {
    srand(unsigned(time(NULL)));
    this->poinA = poinA;
    this->poinB = poinB;
    this->RA = RA;
    this->RB = RB;

    tBest = zeros(1, 100);
    popx = initPopX(N, D);
    popv = initPopV(N, D);
   


    pBest = popx; //初始化每个粒子的最优位置 矩阵维度为[100,10]
    pBestValue = findPoin(pBest);   //初始化每个最佳个体的适应度 矩阵维度为为[100,1]

    vector<double> t;
    t = findPoin(popx);
    gBestValue_index = findIndex(t); // 返回列向量的最大值的下标
    BestAns = popx[gBestValue_index];
    if (t.size())
        gBestValue = t[gBestValue_index],
        gBest = popx[gBestValue_index]; // 根据最大值返回的索引，找到粒子的位置
    else
        printf("error");
    test();
}



//随机数

long long PSO_updata::getnum(int x)
{
    long long res = 0;
    for (int i = 1; i <= x; i++)
    {
        long long ttt = 1;
        for (int j = 1; j <= i; j++)
        {
            ttt *= rand();
        }
        res += ttt;
    }
    return abs(res);
}

//生成[x,y]的随机数
long long PSO_updata::random(long long x, long long y)
{
    return x + getnum() % (y - x + 1);
}

//返回[0,1]的随机数void PSO_updata::
double PSO_updata::Rand() {
    return (rand() / (1. * RAND_MAX));
}



double PSO_updata::juli(double x, double y)
{
    return ((x-poinB[0])* (x - poinB[0])+ (y - poinB[1]) * (y - poinB[1]));
}

vector<double> PSO_updata::findPoin(vector<vector<double>> popx)
{
    vector<double> obj;
    for (int i = 0; i < popx.size(); i++) {
        int x = poinA[0] + RA * cos(popx[i][0]),
            y = poinA[1] + RA * sin(popx[i][0]);
        obj.push_back(abs(RB + RA - juli(x, y)));
    }
    return obj;
}

double PSO_updata::findPoin(vector<double> pop)
{
    int x = poinA[0] + RA * cos(pop[0]),
        y = poinA[1] + RA * sin(pop[0]);
    return  (abs(RA + RB - (juli(x,y))));
}

//生成row行 column列的矩阵
vector<vector<double>> PSO_updata::zeros(int row, int column) {
    vector<vector<double>> re;
    for (int i = 0; i < row; i++) {
        vector<double> t;
        for (int j = 0; j < column; j++)
            t.push_back(.0);

        re.push_back(t);
    }
    return re;
}

//初始化粒子群的位置row行 column列
vector<vector<double>> PSO_updata::initPopX(int row, int column) {
    vector<vector<double>> popx;

    for (int i = 0; i < row; i++) {
        vector<double> t;
        for (int j = 0; j < column; j++)
            t.push_back(Rand() * (Xmax * 1. - Xmin * 1.) + Xmin);
        popx.push_back(t);
    }

    return popx;
}


vector<vector<double>> PSO_updata::initPopV(int row, int column) {
    vector<vector<double>> popV;

    for (int i = 0; i < row; i++) {
        vector<double> t;

        for (int j = 0; j < column; j++)
            t.push_back(Rand() * (Vmax * 1. - Vmin * 1.) + Vmin);

        popV.push_back(t);
    }

    return popV;
}

//返回向量的最大值下标
int  PSO_updata::findIndex(vector<double> vect) {
    int index = 0;
    for (int i = 0; i < vect.size(); i++) {
        if (vect[i] < vect[index])
            index = i;
    }

    return index;
}

//速度更新
void PSO_updata::updatePopv(vector<double>& popv, vector<double> popx, vector<double> pBest, vector<double> gBest) {
    for (int i = 0; i < popv.size(); i++) {
        popv[i] = W * popv[i] + C1 * Rand() * (pBest[i] - popx[i]) + C2 * Rand() * (gBest[i] - popx[i]);
    }
}


//位置更新
void PSO_updata::updatePopx(vector<double>& popx, vector<double> popv) {
    for (int i = 0; i < popx.size(); i++) {
        popx[i] += popv[i];
    }
}

//限定边界
void PSO_updata::defBoundaries(vector<double>& popx, vector<double>& popv) {
    for (int i = 0; i < D; i++) {
        if (popx[i] > Xmax || popx[i] < Xmin) {
            popx[i] = Rand() * (Xmax * 1. - Xmin * 1.) + Xmin;
        }

        if (popv[i] > Vmax || popv[i] < Vmin) {
            popv[i] = Rand() * (Vmax * 1. - Vmin * 1.) + Vmin;
        }
    }
}

vector<vector<double>> PSO_updata::getpopx() {
    return this->popx;
}
vector<vector<double>> PSO_updata::getpBest() {
    return this->pBest;
}

vector<double> PSO_updata::getpBestValue()
{
    return this->pBestValue;
}

void PSO_updata::test()
{
    for (int t = 0; t < T; t++) {    //迭代次数
        for (int i = 0; i < N; i++) {

            // 更新速度位置
            updatePopv(popv[i], popx[i], pBest[i], gBest);
            updatePopx(popx[i], popv[i]);

            //限定边界
            defBoundaries(popx[i], popv[i]);

            //更新最优

            double tValue = findPoin(popx[i]);
            if (tValue < pBestValue[i]) {
                pBest[i] = popx[i];
                pBestValue[i] = tValue;

            }
            else if (pBestValue[i] < gBestValue) {
                gBest = pBest[i];
                gBestValue = pBestValue[i];
            }
        }
        int  indexx = findIndex(pBestValue);
        BestAns = { poinA[0] + cos(popx[indexx][0]), poinA[1] + sin(popx[indexx][0]) };
        for (int i = 0; i < popx.size(); i++)
            drawPath.push_back(popx[i]);
    }
}

Motion_track::Motion_track(Point A, Point B)
{
    this->poinA = A;
    this->poinB = B;
    test();
}

void Motion_track::makeTrack(vector<Point>& tack, double t)
{
    for (int i = 0; i <= t; i++) {
        tack.push_back(yunFunction(t));
    }
}

vector<double> Motion_track::yunFunction(double t)
{
    double x1 = 2 * t;
    double x2 = 2 * t;
    Point obj = { x1,x2 };
    return obj;
}

vector<double> Motion_track::VFunction(double t)
{
    return {2.,2.};
}

void Motion_track::make_V(vector<V> &B, double t)
{
    for (int i = 0; i <= t; i++)
        B.push_back(VFunction(t));
}

double Motion_track::dushu(Point A, Point B)
{
    double Long = sqrt((B[0] - A[0]) * (B[0] - A[0]) + (B[1] - A[1]) * (B[1] - A[1]));
    if ((B[1] - A[1]) >= 0) {
        return (acos((B[0] - A[0]) / Long) / PI * 180);
    }
    else {
        return -(acos((B[0] - A[0]) / Long) / PI * 180);
    }
 
}

vector<vector<double>> Motion_track::getA_track()
{
    return A_track;
}



vector<vector<double>> Motion_track::getB_track()
{
    return B_track;
}

void Motion_track::test()
{
    A_track.clear();
    B_track.clear();
    A_track.push_back(poinA);
    B_track.push_back(poinB);
    for (int i = 1; i <= t*10; i++) {
        Point B = B_track[B_track.size()-1];
        Point A = A_track[A_track.size()-1];
        double k = dushu(A, B)+90;

        //DOUBLE K1 = K + 30;
        if (k > 180) k = k - 360;
        

        //DOUBLE K2 = K - 30;
        //IF (K2 > 180) K2 = K2 - 360;
        //IF (K2 < 180) K2 = 360 + K2;

        //k = abs(k1) > abs(k2) ? k1 : k2;//确定运动方向

        A = { A[0] + A_maxV * cos(k / 180 * PI)*0.01,A[1] + A_maxV * sin(k / 180 * PI)*0.01 };
        A_track.push_back(A);

        B = { poinB[0] + B_maxV * i * 0.01 * cos(PI / 6),poinB[1] + B_maxV * i*0.01*sin(PI/6)};
        //printf("\n %lf", B[0]);
        B_track.push_back(B);
    }
}
