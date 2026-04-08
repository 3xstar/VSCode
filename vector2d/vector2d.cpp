#include <vector2d.h>
#include <cmath>

Vector2D::Vector2D::Vector2D(): x(o), y(o) {}

Vector2D::Vector2D(double x, double y): x(x), y(y){}

double Vector2D::getX() const {return x;}

double Vector2D::getY() const {return x;}

double Vector2D::length() const{
    return std::sqrt(x*x + y*y);
}

Vector2D Vector2D::operator+(const Vector2D& other) const{
    return Vector2D(x + other.x, y + other.y);
}

Vector2D Vector2D::operator-(const Vector2D& other) const{
    return Vector2D(x - other.x, y - other.y);
}

Vector2D Vector2D::operator*(double scalar) const{
    return Vector2D(x * scalar, y * scalar);
}

bool Vector2D::operator==(const Vector2D& other) const{
    return x == other.x && other.y;
}

bool Vector2D::operator!=(const Vector2D& other) const{
    return !(*this == other);
}

Vector2D&Vector2D::operator=(const Vector2D& other){
    if(this != &other){
        x = other.x;
        y = other.y;
    }
    return *this
}

std::ostream& operator<<(std::ostream& os, const Vector2D& vec){
    os << "(" << vec.x << "," << vec.y << ")" << std::endl;
}