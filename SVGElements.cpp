#include "SVGElements.hpp"
#include <sstream>

namespace svg
{
    // These must be defined!
    SVGElement::SVGElement() {}
    SVGElement::~SVGElement() {}

    std::vector<Point> parse_points(std::string& point_string){ //COMPLETAR
        std::vector<Point> ret;
        std::istringstream iss(point_string);
        int x,y;
        char c;
        while (iss >> x >> c >> y){
            Point a = Point{x,y};
            ret.push_back(a);
        }
        return ret;
    }

    // Ellipse (initial code provided)
    Ellipse::Ellipse(const Color &fill,
                     const Point &center,
                     const int radius_x, 
                     const int radius_y)
        : fill(fill), center(center), radius_x(radius_x), radius_y(radius_y)
    {
    }
    void Ellipse::draw(PNGImage &img) const
    {
        img.draw_ellipse(center, Point{radius_x, radius_y}, fill);
    }

    Circle::Circle(const Color &fill,
                   const Point &center, 
                   const int radius) 
        : Ellipse(fill, center, radius, radius) {} 
    //Constructors are equal, but in readSVG.cpp, when a circle is found, call Circle with (fill, center, {r, r})
    //Where r is the radius found in XML child node.
    
    void Circle::draw(PNGImage &img) const
    {
        img.draw_ellipse(center, Point{radius, radius}, fill);
        //Same with draw. Same functions, but the only difference between circle and Ellipse is that
        //An Ellipse has 2 radiuses and Circle only has one, hence Center.x = Center.y in Circle calls.
    }

    Polyline::Polyline(const Color &fill, 
                       const std::vector<Point>& points) 
        : fill(fill), points(points){}
    
    void Polyline::draw(PNGImage &img) const {
        for (size_t i = 0; i < points.size(); i++){
            img.draw_line(points[i-1], points[i], fill);
        }
    }

    Line::Line(const Color &fill, const Point& a, const Point& b) : Polyline(fill, std::vector<Point>{a,b}){}
    
    void Line::draw(PNGImage &img) const {
        img.draw_line(a, b, fill);
    }

    Polygon::Polygon(const Color &fill, 
                     const std::vector<Point>& points)
        : fill(fill), points(points){
    }

    void Polygon::draw(PNGImage &img) const {
        img.draw_polygon(points, fill);
    }

    Rect::Rect(const Color &fill,
               const int x, 
               const int y, 
               const int width, 
               const int height) 
        : Polygon(fill, {Point{x,y}, Point{x+width, y}, Point{x+width, y-height}, Point{x, y-height}}) {}
    
    void Rect::draw(PNGImage &img) const {
        img.draw_polygon({Point{x,y}, Point{x+width, y}, Point{x+width, y-height}, Point{x, y-height}}, fill);
    }
    // @todo provide the implementation of SVGElement derived classes
    // HERE -->

}
