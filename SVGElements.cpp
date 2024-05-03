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
        img.draw_ellipse(center, Point{radius_x, radius_x}, fill);
        //Same with draw. Same functions, but the only difference between circle and Ellipse is that
        //An Ellipse has 2 radiuses and Circle only has one, hence Center.x = Center.y in Circle calls.
    }

    Polyline::Polyline(const Color &stroke, 
                       const std::vector<Point>& points) 
        : stroke(stroke), points(points){}
    
    void Polyline::draw(PNGImage &img) const {
        for (size_t i = 1; i < points.size(); i++){
            img.draw_line(points[i-1], points[i], stroke);
        }
    }

    Line::Line(const Color &stroke, const int x1, const int y1, const int x2, const int y2) : Polyline(stroke, {Point{x1,y1},Point{x2,y2}}){}
    
    void Line::draw(PNGImage &img) const {
        img.draw_line(points[0], points[1] , stroke);
    }

    Polygon::Polygon(const Color &fill, 
                     const std::vector<Point>& points)
        : fill(fill), points(points){
    }

    void Polygon::draw(PNGImage &img) const {
        img.draw_polygon(points, fill);
    }

    Rect::Rect(const Color &fill,
               int x,
               int y,
               int width,
               int height) 
        : Polygon(fill, {Point{x,y}, Point{x+width-1, y}, Point{x+width-1, y+height-1}, Point{x, y+height-1}}) {}
    
    void Rect::draw(PNGImage &img) const {
        img.draw_polygon(points, fill);
    }
    // @todo provide the implementation of SVGElement derived classes
    // HERE -->

}
