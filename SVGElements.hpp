//! @file shape.hpp
#ifndef __svg_SVGElements_hpp__
#define __svg_SVGElements_hpp__

#include "Color.hpp"
#include "Point.hpp"
#include "PNGImage.hpp"

namespace svg
{
    class SVGElement
    {

    public:
        SVGElement();
        virtual ~SVGElement();
        virtual void draw(PNGImage &img) const = 0;
    };

    // Declaration of namespace functions
    // readSVG -> implement it in readSVG.cpp
    // convert -> already given (DO NOT CHANGE) in convert.cpp

    std::vector<Point> parse_points(std::string& point_string);

    void readSVG(const std::string &svg_file,
                 Point &dimensions,
                 std::vector<SVGElement *> &svg_elements);
    void convert(const std::string &svg_file,
                 const std::string &png_file);

    class Ellipse : public SVGElement
    {
    public:
        Ellipse(const Color &fill, const Point &center, const int radius_x, const int radius_y);
        void draw(PNGImage &img) const override;

    protected:
        Color fill;
        Point center;
        int radius_x;
        int radius_y;
    };

    //cirlce class, derived of Ellipse
    class Circle : public Ellipse 
    {
        public:
            Circle(const Color &fill, const Point &center, const int radius_x); 
            //WARNING: Circle is derived of Ellipse, when doing constructor get the default constructor from Ellipse
            void draw(PNGImage &img) const override;
    };

    class Polyline : public SVGElement {
        public:
            Polyline(const Color &stroke, const std::vector<Point>& points);
            void draw(PNGImage &img) const override;
        protected:
            Color stroke;
            std::vector<Point> points;
    };

    class Line : public Polyline {
        public:
            Line(const Color &stroke, const int x1, const int y1, const int x2, const int y2);
            void draw(PNGImage &img) const override;
    };

    class Polygon : public SVGElement{
        public:
            Polygon(const Color &fill, const std::vector<Point>& points);
            void draw(PNGImage &img) const override;
        protected:
            Color fill;
            std::vector<Point> points;
    };

    class Rect : public Polygon{
        public:
            Rect(const Color &fill, int x, int y, int width, int height);
            void draw(PNGImage &img) const override;
    };

}
#endif
