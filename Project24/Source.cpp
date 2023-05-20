#include <QtWidgets>
const int LENGTH_ROAD = 600;
const int COUNT_CARS = 3;
class Road {
public:
	Road(double newLength, int newWidth);
	double Length;
	int Width;
};

Road::Road(double newLength, int newWidth) {

	Length = newLength;
	Width = newWidth;
}

class Car {
public:
	Car(int newP, double newV, Road* ptrRoad);
	Road* _road;
	double X;
	int P;
	double V;

	void move();

};

Car::Car(int newP, double newV, Road* ptrRoad) {
	_road = ptrRoad;
	X = 0;
	P = newP;
	V = newV;

}
void Car::move() {
	X += V;
	if (X > _road->Length) {
		X = 0;
	}
}



class MainWindow : public QMainWindow {
public:
	//MainWindow(Car *ptrCarA,Car *ptrCarB);
	MainWindow(Car* ptrCars[]);
	void updateCars();
private:
	void paintEvent(QPaintEvent*);
	//Car *_carA;
	//Car *_carB;
	Car** _cars;
	int timerInterval;
	//int xCarA = 0;
	//int xCarB = 0;
   // QLabel *carLabel;
  //  QLabel *carBLabel;
	QTimer* timer;
};

//MainWindow::MainWindow( Car *ptrCarA,Car *ptrCarB) {
MainWindow::MainWindow(Car* ptrCars[]) {
	//_carA = ptrCarA;
	//_carB = ptrCarB;
	_cars = ptrCars;
	setFixedSize(1100, LENGTH_ROAD);
	setWindowTitle("Racing Labels v9.4");
	/*
	QFont labelAFont("TypeWritet", 72, QFont::Bold);
	QFont labelBFont("Fanstasy", 72, QFont::Bold);
	carLabel = new QLabel("A", this);
	carLabel->setGeometry(0,100,100,150);
	carLabel->setFont(labelAFont);

	carBLabel = new QLabel("B", this);
	carBLabel->setGeometry(0,0,100,150);
	carBLabel->setFont(labelBFont);
	*/
	timer = new QTimer(this);
	timer->setInterval(100);
	timer->start();

	connect(timer, &QTimer::timeout, this, &MainWindow::updateCars);
}

void MainWindow::updateCars() {
	for (int i = 0; i < COUNT_CARS;i++) {
		_cars[i]->move();
	}
	//xCarA+=_carA->V;
	//_carA->move();
	//xCarA = _carA->X;
	//carLabel->setGeometry(_carA->X,0,100,150);
	//carLabel->setGeometry(_cars[0]->X,0,100,150);
	//xCarB+=_carB->V;
	//_carB->move();
	//xCarB = _carB->X;
	//carBLabel->setGeometry(_carB->X,100,100,150);
	//carBLabel->setGeometry(_cars[1]->X,100,100,150);
	update();
}
void MainWindow::paintEvent(QPaintEvent*) {
	QPainter painter(this);
	QPen redPen4(Qt::red, 4, Qt::SolidLine);
	QBrush greenBrush(Qt::green, Qt::SolidPattern);
	painter.setPen(redPen4);
	painter.setBrush(greenBrush);
	painter.drawEllipse(_cars[1]->X, 100, 120, 80);

}
int main(int argc, char* argv[]) {
	QApplication app(argc, argv);
	Road road(LENGTH_ROAD, 3);

	//Car carA(1,2,&road);
	//Car carB(1,4,&road);
	Car* cars[COUNT_CARS];
	for (int i = 0; i < COUNT_CARS; i++) {
		cars[i] = new Car(i, 2 * (i + 1), &road);
	}
	//MainWindow mainWin(&carA,&carB);
	MainWindow mainWin(cars);
	mainWin.show();
	return app.exec();

}
