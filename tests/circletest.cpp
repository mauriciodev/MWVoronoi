#include <QtTest/QtTest>
#include "circle.h"

class CircleTest: public QObject
{
    Q_OBJECT
private:
    float * newRandomArray(int, double, double);
private slots:
    //void initTestCase();
    void toUpper();
    void toUpper_data();
    void stressTest();
    void CircleIntersectionCount();
    void CircleIntersectionCount_data();
    void CircleString();
    void CircleArcXyToPolar();
    void CircleArcXyToPolar_data();
    void reduceAngle();
    void reduceAngle_data();
    void splitArc();
};


void CircleTest::toUpper()
{
    QFETCH(QString, string);
    QFETCH(QString, result);

    QCOMPARE(string.toUpper(), result);
}


void CircleTest::toUpper_data()
{
    QTest::addColumn<QString>("string");
    QTest::addColumn<QString>("result");

    QTest::newRow("all lower") << "hello" << "HELLO";
    QTest::newRow("mixed")     << "Hello" << "HELLO";
    QTest::newRow("all upper") << "HELLO" << "HELLO";
}

void CircleTest::CircleIntersectionCount_data() {
    QTest::addColumn<double>("x1");
    QTest::addColumn<double>("y1");
    QTest::addColumn<double>("r1");
    QTest::addColumn<double>("x2");
    QTest::addColumn<double>("y2");
    QTest::addColumn<double>("r2");
    QTest::addColumn<int>("count");


    QTest::newRow("Disjoint")   << 0. << 0.<< 1.<< 0.<< 3.<< 1.<<0;
    QTest::newRow("Touches")    << 0. << 0.<< 1.<< 0.<< 2.<< 1.<<1;
    QTest::newRow("Intersects") << 0. << 0.<< 1.<< 0.<< 1.<< 1.<<2;

}

void CircleTest::CircleIntersectionCount() {
    QFETCH(double, x1);
    QFETCH(double, x2);
    QFETCH(double, y1);
    QFETCH(double, y2);
    QFETCH(double, r1);
    QFETCH(double, r2);
    QFETCH(int, count);
    Circle *t1 =  new Circle(r1,x1,y1);
    Circle *t2 =  new Circle(r2,x2,y2);

    //cout<< "First circle: "<< t1->asString() <<endl;
    std::vector<xy> res;
    t1->intersection(t2,res);
    QCOMPARE((int)res.size(),count);

    //std::vector<double> res2;
    //t1->polarIntersection(t2,res2);
    //QCOMPARE(res2.size(),count);
    delete t1;
    delete t2;
}

void CircleTest::CircleString() {
    Circle *t1 =  new Circle(0,0,10);
    std::string text = t1->asApproximatedString();
    QCOMPARE(text[1],text[text.size()-1]);
    delete t1;
}

void CircleTest::reduceAngle_data() {
    QTest::addColumn<double>("angle");
    QTest::addColumn<double>("reduced");
    QTest::newRow("2pi") << 2*pi<< 0.;
    QTest::newRow("5pi/2") << 5*pi/2.<< pi/2.;
    QTest::newRow("-pi/2") << pi/-2.<< 3*pi/2;
}

void CircleTest::reduceAngle() {
    QFETCH(double, angle);
    QFETCH(double, reduced);
    CircularArc c;
    double tol=0.00001;
    QCOMPARE(fabs(c.reduceAngle(angle)-reduced)<tol,true);
}

void CircleTest::CircleArcXyToPolar_data() {
    double meupi=pi;
    QTest::addColumn<double>("x");
    QTest::addColumn<double>("y");
    QTest::addColumn<double>("res");
    double d30=sqrt(200*200-100*100);
    QTest::newRow("Q 1o") << 100. << 100. << (meupi/4);
    QTest::newRow("Q 2o") << -d30 << 100. << (meupi-meupi/6);
    QTest::newRow("Q 3o") << -d30 << -100. << (3*meupi/2 - meupi/6);
    QTest::newRow("Q 4o") << 100. << -100. << (2*meupi-meupi/4);
}

void CircleTest::CircleArcXyToPolar() {
    Circle c(10,0,0);
    QFETCH(double, x);
    QFETCH(double, y);
    QFETCH(double, res);
    xy p=xy(x,y);
    double tol=0.00001;
    double ang=c.xyToPolar(p);
    QCOMPARE(ang-res<tol,true);

}

void CircleTest::splitArc() {
    Circle c(10,0,0);
    ST_CircularString cs;
    CircularArc arc(10,10,0,pi/2,3*pi/2);
    cs.arcList.push_back(arc);
    cs.clip(c);
}

void CircleTest::stressTest() {
    srand((unsigned)time(0));
    //tested sizes
    float *x, *y, *w;
    for (int n=10; n<10000;n*=10) {
        //many samples for each size
        for (int m; m<10;m++) {
            //x=newRandomArray(n,0,5000);
            //y=newRandomArray(n,0,5000);
            //w=newRandomArray(n,0,10);

            //delete[] x,y,w;
        }
    }

}

float * CircleTest::newRandomArray(int n, double min, double max) {
    float *arr=new float[n];
    return arr;
}




#include "../bin/circletest.moc"
//QTEST_MAIN(CircleTest)
int main(void){
    CircleTest * test = new CircleTest();

    QTest::qExec(test);
    delete test;
}
