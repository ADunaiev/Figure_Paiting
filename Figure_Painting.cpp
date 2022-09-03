#include<iostream>
#include<fstream>
#include<windows.h>
#include<string.h>

//«адание 2.
//—оздайте абстрактный класс Shape дл€ рисовани€ плоских фигур.
//ќпределите виртуальные методы :
//Х Show() Ч вывод на экран информации о фигуре,
//Х Save() Ч сохранение фигуры в файл,
//Х Load() Ч считывание фигуры из файла.
//ќпределите производные классы :
//Х Square Ч квадрат, который характеризуетс€ коорди - 
//натами левого верхнего угла и длиной стороны;
//Х Rectangle Ч пр€моугольник с заданными координатами верхнего левого угла и размерами;
//Х Circle Ч окружность с заданными координатами центра и радиусом;
//Х Ellipse Ч эллипс с заданными координатами верхне - 
//го угла описанного вокруг него пр€моугольника со
//сторонами, параллельными ос€м координат, и размерами этого пр€моугольника.
//—оздайте массив фигур, сохраните фигуры в файл, загрузите в другой массив и
//отобразите информацию о каждой из фигур.
class Point
{
	int x;
	int y;
public:
	Point(int xP, int yP);
	Point();
	int get_x() const;
	int get_y() const;
	void set_x(int xP);
	void set_y(int yP);
};
Point::Point(int xP, int yP) : x{ xP }, y{ yP }{}
Point::Point() : Point(0,0){}
int Point::get_x() const
{
	return x;
}
int Point::get_y() const
{
	return y;
}
void Point::set_x(int xP)
{
	x = xP;
}
void Point::set_y(int yP)
{
	y = yP;
}

class Shape
{
protected:
	Point upper_point;
public:
	Shape(Point upper_pointP);
	virtual void Show() const = 0;
	virtual void Save() const = 0;
	virtual void Load() = 0;
};
Shape::Shape(Point upper_pointP):upper_point {upper_pointP}{}

class Square : public Shape
{
	int side;
public:
	Square(int sideP, Point upper_pointP);
	Square();
	virtual void Show() const;
	virtual void Save() const;
    virtual void Load();
};
Square::Square(int sideP, Point upper_pointP):Shape(upper_pointP)
{
	side = sideP;
}
Square::Square() : Shape({ 0, 0 }) { side = 0; }
void Square::Show() const
{
	std::cout << "The figure is square." << std::endl;
	std::cout << "It's upper left cornet coordinates are: " <<
		upper_point.get_x() << ", " << upper_point.get_y() << std::endl;
	std::cout << "Square side is " << side << std::endl;
	std::cout << "\n";
}
void Square::Save() const
{

    std::fstream f("figures.txt", std::ios::out | std::ios::binary | std::ios::app); 
   
    if (!f) {
        std::cout << "File is not opened for writing" << std::endl;
        exit(1);
    }

    int temp1 = upper_point.get_x();
    int temp2 = upper_point.get_y();
   
	f.write((char*)&"s", sizeof(char));
    f.write((char*)&temp1, sizeof(int));
    f.write((char*)&temp2, sizeof(int));
    f.write((char*)&side, sizeof(int));

    f.close();
}
void Square::Load()
{
    std::fstream f("figures.txt", std::ios::in | std::ios::binary);
    if (!f) {
        std::cout << "File is not opened for reading" << std::endl;
        exit(1);
    }
    int temp_x, temp_y, sideP;
	char c;
   
    while (f.read((char*)&c, sizeof(char))) {
		if (c == 's')
		{
			f.read((char*)&temp_x, sizeof(int));
			upper_point.set_x(temp_x);
			f.read((char*)&temp_y, sizeof(int));
			upper_point.set_y(temp_y);
			f.read((char*)&sideP, sizeof(int));
			side = sideP;
		}
        }
}

class Rect : public Shape
{
	int height;
	int width;
public:
	Rect(int heightP, int widthP, Point upper_pointP);
	Rect();
	virtual void Show() const;
	virtual void Save() const;
	virtual void Load();
	int get_rect_x() const;
	int get_rect_y() const;
	int get_height() const;
	int get_width() const;
	void set_height(int heightP);
	void set_width(int widthP);
};
Rect::Rect(int heightP, int widthP, Point upper_pointP) :Shape(upper_pointP)
{
	height = heightP;
	width = widthP;
}
Rect::Rect() : Shape({ 0, 0 }) { height = 0; width = 0; }
void Rect::Show() const
{
	std::cout << "The figure is rectangle." << std::endl;
	std::cout << "It's upper left cornet coordinates are: " <<
		upper_point.get_x() << ", " << upper_point.get_y() << std::endl;
	std::cout << "Height is " << height << std::endl;
	std::cout << "Width is " << width << std::endl;
	std::cout << "\n";
}
void Rect::Save() const
{

	std::fstream f("figures.txt", std::ios::out | std::ios::binary | std::ios::app);

	if (!f) {
		std::cout << "File is not opened for writing" << std::endl;
		exit(1);
	}

	int temp1 = upper_point.get_x();
	int temp2 = upper_point.get_y();

	f.write((char*)&"r", sizeof(char));
	f.write((char*)&temp1, sizeof(int));
	f.write((char*)&temp2, sizeof(int));
	f.write((char*)&height, sizeof(int));
	f.write((char*)&width, sizeof(int));

	f.close();
}
void Rect::Load()
{
	std::fstream f("figures.txt", std::ios::in | std::ios::binary);
	if (!f) {
		std::cout << "File is not opened for reading" << std::endl;
		exit(1);
	}
	int temp_x, temp_y;
	char c;

	while (f.read((char*)&c, sizeof(char))) {
		if (c == 'r')
		{
			f.read((char*)&temp_x, sizeof(int));
			upper_point.set_x(temp_x);
			f.read((char*)&temp_y, sizeof(int));
			upper_point.set_y(temp_y);
			f.read((char*)&height, sizeof(int));
			f.read((char*)&width, sizeof(int));
		
		}
	}
}
int Rect::get_rect_x() const
{
	return upper_point.get_x();
}
int Rect::get_rect_y() const
{
	return upper_point.get_y();
}
int Rect::get_height() const
{
	return height;

}
int Rect::get_width() const
{
	return width;
}
void Rect::set_height(int heightP)
{
	height = heightP;
}
void Rect::set_width(int widthP)
{
	width = widthP;
}

class Circle : public Shape
{
	int radius;
public:
	Circle(int radiusP, Point upper_pointP);
	Circle();
	virtual void Show() const;
	virtual void Save() const;
	virtual void Load();
};
Circle::Circle(int radiusP, Point upper_pointP) :Shape(upper_pointP)
{
	radius = radiusP;
}
Circle::Circle() : Shape({ 0, 0 }) { radius = 0; }
void Circle::Show() const
{
	std::cout << "The figure is circle." << std::endl;
	std::cout << "It's center coordinates are: " <<
		upper_point.get_x() << ", " << upper_point.get_y() << std::endl;
	std::cout << "Radius is " << radius << std::endl;
	std::cout << "\n";
}
void Circle::Save() const
{

	std::fstream f("figures.txt", std::ios::out | std::ios::binary | std::ios::app);

	if (!f) {
		std::cout << "File is not opened for writing" << std::endl;
		exit(1);
	}

	int temp1 = upper_point.get_x();
	int temp2 = upper_point.get_y();

	f.write((char*)&"c", sizeof(char));
	f.write((char*)&temp1, sizeof(int));
	f.write((char*)&temp2, sizeof(int));
	f.write((char*)&radius, sizeof(int));

	f.close();
}
void Circle::Load()
{
	std::fstream f("figures.txt", std::ios::in | std::ios::binary);
	if (!f) {
		std::cout << "File is not opened for reading" << std::endl;
		exit(1);
	}
	int temp_x, temp_y;
	char c;

	while (f.read((char*)&c, sizeof(char))) {
		if (c == 'c')
		{
			f.read((char*)&temp_x, sizeof(int));
			upper_point.set_x(temp_x);
			f.read((char*)&temp_y, sizeof(int));
			upper_point.set_y(temp_y);
			f.read((char*)&radius, sizeof(int));
		}
	}
}

class Ellips: public Shape
{
	Rect rectangle;
public:
	Ellips(Rect rectangleP);
	Ellips();
	virtual void Show() const;
	virtual void Save() const;
	virtual void Load();
};
Ellips::Ellips(Rect rectangleP) 
	: Shape({ rectangleP.get_rect_x(), rectangleP.get_rect_y()})
{
	rectangle.set_height(rectangleP.get_height());
	rectangle.set_width(rectangleP.get_width());
}
Ellips::Ellips() 
	: Shape({ 0, 0 }) {
	rectangle.set_height(0); rectangle.set_width(0);
}
void Ellips::Show() const
{
	std::cout << "The figure is ellipse." << std::endl;
	std::cout << "It's upper left corner coordinates are: " <<
		upper_point.get_x() << ", " << upper_point.get_y() << std::endl;
	std::cout << "Height is " << rectangle.get_height() << std::endl;
	std::cout << "Width is " << rectangle.get_width() << std::endl;
	std::cout << "\n";
}
void Ellips::Save() const
{

	std::fstream f("figures.txt", std::ios::out | std::ios::binary | std::ios::app);

	if (!f) {
		std::cout << "File is not opened for writing" << std::endl;
		exit(1);
	}

	int temp1 = upper_point.get_x();
	int temp2 = upper_point.get_y();
	int temp3 = rectangle.get_height();
	int temp4 = rectangle.get_width();


	f.write((char*)&"e", sizeof(char));
	f.write((char*)&temp1, sizeof(int));
	f.write((char*)&temp2, sizeof(int));
	f.write((char*)&temp3, sizeof(int));
	f.write((char*)&temp4, sizeof(int));

	f.close();
}
void Ellips::Load()
{
	std::fstream f("figures.txt", std::ios::in | std::ios::binary);
	if (!f) {
		std::cout << "File is not opened for reading" << std::endl;
		exit(1);
	}
	int temp_x, temp_y;
	int temp_h, temp_w;
	char c;

	while (f.read((char*)&c, sizeof(char))) {
		if (c == 'e')
		{
			f.read((char*)&temp_x, sizeof(int));
			upper_point.set_x(temp_x);
			f.read((char*)&temp_y, sizeof(int));
			upper_point.set_y(temp_y);
			f.read((char*)&temp_h, sizeof(int));
			rectangle.set_height(temp_h);
			f.read((char*)&temp_w, sizeof(int));
			rectangle.set_width(temp_w);

		}
	}
}

int main()
{
	Point A(5, 5);
	Square S1(3, A);
	std::cout << "About S1: ";
	S1.Show();
	S1.Save();

	Square S2;
	S2.Load();  
	std::cout << "About S2: ";
	S2.Show();

	Point B(2, 4);
	Rect R1(3, 4, B);
	std::cout << "About R1: ";
	R1.Show();
	R1.Save();

	Rect R2;
	R2.Load();
	std::cout << "About R2: ";
	R2.Show();
	
	Point C(1, 1);
	Circle C1(5, C);
	std::cout << "About C1: ";
	C1.Show();
	C1.Save();

	Circle C2;
	C2.Load();
	std::cout << "About C2: ";
	C2.Show();

	Ellips E1(R1);
	std::cout << "About E1: ";
	E1.Show();
	E1.Save();

	Ellips E2;
	E2.Load();
	std::cout << "About E2: ";
	E2.Show();


	return 0;
}