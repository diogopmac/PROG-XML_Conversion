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

        /// @brief Draws an element in a PNG file
        /// @param img PNG image
        virtual void draw(PNGImage &img) const = 0;

        /// @brief Translates an element, already drawn
        /// @param x X-Coordinate to be moved
        /// @param y Y-Coordinate to be moved
        virtual void translate(int x, int y) = 0;

        /// @brief Rotates an element, through an origin
        /// @param origin_x Rotation origin, X-Axis
        /// @param origin_y Rotation origin, Y-Axis
        /// @param angle Angle of rotation
        virtual void rotate(int origin_x, int origin_y, int angle) = 0;

        /// @brief Scales an element, through an origin
        /// @param origin_x Scaling origin, X-Axis
        /// @param origin_y Scaling origin, Y-Axis
        /// @param value Scaling value
        virtual void scale(int origin_x, int origin_y, int value) = 0;

        /// @brief Duplicates an element
        /// @param id ID of an element
        /// @param elem Element 
        /// @return Returns an SVGElement duplicated
        virtual SVGElement *duplicate(std::string id, SVGElement *elem) = 0;
    };

    /// @brief Function to parse a string of int values separated by a blank space, and put it in a vector of Point{x, y}
    /// @param point_string String of different points, of the type "x y x y x y"
    /// @return returns a vector of Point values
    std::vector<Point> parse_points(std::string& point_string);


    /// @brief Removes commas of a given string. Used in point parsing.
    /// @param str Given string
    void remove_commas(std::string& str);

    void readSVG(const std::string &svg_file,
                 Point &dimensions,
                 std::vector<SVGElement *> &svg_elements);
    void convert(const std::string &svg_file,
                 const std::string &png_file);

    class Ellipse : public SVGElement
    {
    public:
        /// @brief Constructor
        /// @param fill Fill Color
        /// @param center Center
        /// @param radius_x Radius, X-Axis
        /// @param radius_y Radius, Y-Axis
        Ellipse(const Color &fill, const Point &center, const int radius_x, const int radius_y);

        /// @brief Copy constructor
        /// @param copy Ellipse to be copied
        Ellipse(const Ellipse& copy) : SVGElement(copy), fill(copy.fill), center(copy.center), radius_x(copy.radius_x), radius_y(copy.radius_y){}

        void draw(PNGImage &img) const override;
        void translate(int x, int y) override;
        void rotate(int origin_x, int origin_y, int angle) override;
        void scale(int origin_x, int origin_y, int value) override;
        SVGElement *duplicate(std::string id, SVGElement *elem) override;
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
            /// @brief Constructor
            /// @param fill Fill Color
            /// @param center Center
            /// @param radius_x Radius
            Circle(const Color &fill, const Point &center, const int radius_x); 
            void draw(PNGImage &img) const override;
    };

    class Polyline : public SVGElement {
        public:
            /// @brief Constructor
            /// @param stroke Stroke Color
            /// @param points Vector of Points
            Polyline(const Color &stroke, const std::vector<Point>& points);

            /// @brief Copy constructor
            /// @param copy Polyline to be copied
            Polyline(const Polyline& copy) : SVGElement(copy), stroke(copy.stroke), points(copy.points) {}

            void draw(PNGImage &img) const override;
            void translate(int x, int y) override;
            void rotate(int origin_x, int origin_y, int angle) override;
            void scale(int origin_x, int origin_y, int value) override;
            SVGElement *duplicate(std::string id, SVGElement *elem) override;
        protected:
            Color stroke;
            std::vector<Point> points;
    };

    class Line : public Polyline {
        public:
            /// @brief Constructor
            /// @param stroke Stroke color
            /// @param x1 Point 1, X-Axis
            /// @param y1 Point 1, Y-Axis
            /// @param x2 Point 2, X-Axis
            /// @param y2 Point 2, Y-Axis
            Line(const Color &stroke, const int x1, const int y1, const int x2, const int y2);
            void draw(PNGImage &img) const override;
    };

    class Polygon : public SVGElement{
        public:
            /// @brief Constructor
            /// @param fill Fill Color
            /// @param points Vector of points
            Polygon(const Color &fill, const std::vector<Point>& points);

            /// @brief Copy constructor
            /// @param copy Polygon to be copied
            Polygon(const Polygon& copy) : SVGElement(copy), fill(copy.fill), points(copy.points) {}

            void draw(PNGImage &img) const override;
            void translate(int x, int y) override;
            void rotate(int origin_x, int origin_y, int angle) override;
            void scale(int origin_x, int origin_y, int value) override;
            SVGElement *duplicate(std::string id, SVGElement *elem) override;
        protected:
            Color fill;
            std::vector<Point> points;
    };

    class Rect : public Polygon{
        public:
            /// @brief Constructor
            /// @param fill Fill Color
            /// @param x Upper-Left point, X-Axis
            /// @param y Upper-Left point, Y-Axis
            /// @param width Rectangle Width
            /// @param height Rectangle Height
            Rect(const Color &fill, int x, int y, int width, int height);
            void draw(PNGImage &img) const override;
    };

    class Group : public SVGElement {
        public:
            /// @brief Constructor
            /// @param elements Vector of SVGElement
            Group(std::vector<SVGElement *> elements);

            /// @brief Copy constructor
            /// @param copy Group to be copied
            Group(const Group& copy) : SVGElement(copy), elements(copy.elements) {}
            void draw(PNGImage &img) const override;
            void translate(int x, int y) override;
            void rotate(int origin_x, int origin_y, int angle) override;
            void scale(int origin_x, int origin_y, int value) override;

            /// @brief Getter
            /// @return Vector of SVGElement
            std::vector<SVGElement *> get_elements() {return elements;};
            
            SVGElement *duplicate(std::string id, SVGElement *elem) override;
        private:
            std::vector<SVGElement *> elements;

    };

}
#endif
