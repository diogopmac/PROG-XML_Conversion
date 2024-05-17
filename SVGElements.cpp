#include "SVGElements.hpp"
#include <sstream>
#include <iostream>

namespace svg
{
    // These must be defined!
    SVGElement::SVGElement() {}
    SVGElement::~SVGElement() {}

    /// @brief Function to parse a string of int values separated by a comma, and put it in a vector of Point{x, y}
    /// @param point_string String of different points, of the type "x,y x,y, x,y"
    /// @return returns a vector of Point values
    std::vector<Point> parse_points(std::string& point_string){
        std::vector<Point> ret;
        remove_commas(point_string);
        std::istringstream iss(point_string);
        int x,y;
        while (iss >> x  >> y){
            Point a = Point{x,y};
            ret.push_back(a);
        }
        return ret;
    }

    void remove_commas(std::string& str){
        for (char &c : str)
        {
            if (c == ',')
            {
                c = ' ';
            }
        }
    }

    /// @brief Ellipse Constructor
    /// @param fill Fill Color
    /// @param center Ellipse center
    /// @param radius_x Radius in X-Axis
    /// @param radius_y Radius in Y-Axis
    Ellipse::Ellipse(const Color &fill,
                     const Point &center,
                     const int radius_x, 
                     const int radius_y)
        : fill(fill), center(center), radius_x(radius_x), radius_y(radius_y)
    {
    }

    /// @brief Ellipse draw function, provided
    /// @param img PNG Image 
    void Ellipse::draw(PNGImage &img) const
    {
        img.draw_ellipse(center, Point{radius_x, radius_y}, fill);
    }

    //Ellipse Translate Tranformation
    //!@param x X-Axis deviation
    //!@param y Y-Axis deviation
    void Ellipse::translate(int x, int y) 
    {
        center.x += x;
        center.y += y;
    }

    /// @brief Ellipse Rotation Transformation
    /// @param origin_x Rotation Origin, X-Axis
    /// @param origin_y Rotation Origin, Y-Axis
    /// @param angle Rotation Angle, in degrees 
    void Ellipse::rotate(int origin_x, int origin_y, int angle) 
    {
        Point rotate_origin = Point{origin_x, origin_x};
        center = center.rotate(rotate_origin, angle);
    }

    void Ellipse::scale(int origin_x, int origin_y, int value) {
        Point scale_origin = Point{origin_x, origin_y};
        center = center.scale(scale_origin, value);
        radius_x = radius_x*value;
        radius_y = radius_y*value;
    }

    SVGElement *Ellipse::duplicate(std::string id, SVGElement *elem){
        Ellipse *new_ellipse = new Ellipse(*dynamic_cast<Ellipse*>(elem));
        return new_ellipse;
    }

    /// @brief Circle constructor, subclass of Ellipse
    /// @param fill Fill Color
    /// @param center Circle Center
    /// @param radius Circle Radius
    Circle::Circle(const Color &fill,
                   const Point &center, 
                   const int radius) 
        : Ellipse(fill, center, radius, radius) {} 
    
    void Circle::draw(PNGImage &img) const
    {
        img.draw_ellipse(center, Point{radius_x, radius_x}, fill);
        // Comentar sobre isto depois (Point{radius_x, radius_x})
    }

    Polyline::Polyline(const Color &stroke, 
                       const std::vector<Point>& points) 
        : stroke(stroke), points(points){}
    
    void Polyline::draw(PNGImage &img) const 
    {
        for (size_t i = 1; i < points.size(); i++)
        {
            img.draw_line(points[i-1], points[i], stroke);
        }
    }

    void Polyline::translate(int x, int y) 
    {
        for(Point& point : points){
            point.x += x;
            point.y += y;
        }
    }

    void Polyline::rotate(int origin_x, int origin_y, int angle)  
    {
        Point origin = Point{origin_x, origin_y};
        std::vector<Point> nPoints;
        for(Point& point : points) 
        {
            point = point.rotate(origin, angle);
        }
    }

    void Polyline::scale(int origin_x, int origin_y, int value) 
    {
        Point origin = Point{origin_x, origin_y};
        for(Point& point : points){
            point = point.scale(origin, value);
        }
    }

    SVGElement *Polyline::duplicate(std::string id, SVGElement *elem){
        Polyline *new_polyline = new Polyline(*dynamic_cast<Polyline*>(elem));
        return new_polyline;
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

    void Polygon::translate(int x, int y)  
    {
        for(Point& point : points){
            point.x+=x;
            point.y+=y;
        }
    }
    void Polygon::rotate(int origin_x, int origin_y, int angle)  
    {
        Point origin = Point{origin_x, origin_y};
        for(Point& point : points) 
        {
            point = point.rotate(origin, angle);
        }
    }
    void Polygon::scale(int origin_x, int origin_y, int value)  
    {
        Point origin = Point{origin_x, origin_y};
        for(Point& point : points){
            point = point.scale(origin, value);
        }
    }

    SVGElement *Polygon::duplicate(std::string id, SVGElement *elem){
        Polygon *new_polygon = new Polygon(*dynamic_cast<Polygon*>(elem));
        return new_polygon;
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

    Group::Group(std::vector<SVGElement *> elements) : elements(elements) {};

    void Group::draw(PNGImage &img) const{
        for(SVGElement *elem : elements){
            elem->draw(img);
        }
    }

    void Group::translate(int x, int y){
        for(SVGElement *elem : elements){
            elem->translate(x,y);
        }
    }

    void Group::rotate(int origin_x, int origin_y, int angle){
        for(SVGElement *elem : elements){
            elem->rotate(origin_x, origin_y, angle);
        }
    }

    void Group::scale(int origin_x, int origin_y, int value){
        for(SVGElement *elem : elements){
            elem->scale(origin_x, origin_y, value);
        }
    }

    SVGElement *Group::duplicate(std::string id, SVGElement *elem){
        Group *group = dynamic_cast<Group*>(elem);
        std::vector<SVGElement *> members = group->get_elements();
        std::vector<SVGElement *> new_elements;
        for(SVGElement *e : elements){
            new_elements.push_back(e->duplicate(id, e));
        }
        Group *new_group = new Group(new_elements);
        return new_group;
    }

    // @todo provide the implementation of SVGElement derived classes
    // HERE -->

}
