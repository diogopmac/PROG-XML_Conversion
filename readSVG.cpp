
#include <iostream>
#include <sstream>
#include "SVGElements.hpp"
#include "external/tinyxml2/tinyxml2.h"

using namespace std;
using namespace tinyxml2;

namespace svg
{
    void readSVG(const string& svg_file, Point& dimensions, vector<SVGElement *>& svg_elements)
    {
        XMLDocument doc;
        XMLError r = doc.LoadFile(svg_file.c_str());
        if (r != XML_SUCCESS)
        {
            throw runtime_error("Unable to load " + svg_file);
        }
        XMLElement *xml_elem = doc.RootElement();

        dimensions.x = xml_elem->IntAttribute("width");
        dimensions.y = xml_elem->IntAttribute("height");
        
        XMLElement *child = xml_elem->FirstChildElement(); //Changed from svg_elem

        while (child != nullptr){

            std::string elementName = child->Name();

            if (elementName == "ellipse"){
                    int cx = child->IntAttribute("cx");
                    int cy = child->IntAttribute("cy");
                    int rx = child->IntAttribute("rx");
                    int ry = child->IntAttribute("ry"); 
                    string fill = child->Attribute("fill");
                    Color fillColor = parse_color(fill);

                    SVGElement* ellipse = new Ellipse(fillColor, Point{cx, cy}, rx, ry); 
                    svg_elements.push_back(ellipse);
            }
            else if (elementName == "circle"){
                    int cx = child->IntAttribute("cx");
                    int cy = child->IntAttribute("cy");
                    int r = child->IntAttribute("r");
                    string fill = child->Attribute("fill");
                    Color fillColor = parse_color(fill);

                    SVGElement* circle = new Circle(fillColor, Point{cx,cy}, r);
                    svg_elements.push_back(circle);
            }
            else if (elementName == "polyline") {
                    std::string pointsStr = child->Attribute("points");
                    std::vector<Point> points = parse_points(pointsStr);
                    std::string stroke = child->Attribute("stroke");
                    Color strokeColor = parse_color(stroke);

                    SVGElement* polyline = new Polyline(strokeColor, points);
                    svg_elements.push_back(polyline);
            }
            else if (elementName == "line") {
                    int x1 = child->IntAttribute("x1");
                    int y1 = child->IntAttribute("y1");
                    int x2 = child->IntAttribute("x2");
                    int y2 = child->IntAttribute("y2");
                    std::string stroke = child->Attribute("stroke");
                    Color strokeColor = parse_color(stroke);

                    SVGElement* line = new Line(strokeColor, Point{x1, y1}, Point{x2, y2} );
                    svg_elements.push_back(line);
            }
            else if (elementName == "polygon") {
                    std::string pointsStr = child->Attribute("points");
                    std::vector<Point> points = parse_points(pointsStr);
                    std::string fill = child->Attribute("fill");
                    Color fillColor = parse_color(fill);

                SVGElement* polygon = new Polygon(fillColor, points);
                    svg_elements.push_back(polygon);
            }
            else if (elementName == "rect") {
                int x = child->IntAttribute("x");
                int y = child->IntAttribute("y");
                int width = child->IntAttribute("width");
                int height = child->IntAttribute("height");
                std::string fill = child->Attribute("fill");
                Color fillColor = parse_color(fill);

                cout << "Point 1: " << x << " " << y << endl;
                cout << "Point 2: " << x+width << " " << y << endl;
                cout << "Point 3: " << x+width << " " << y+height << endl;
                cout << "Point 4: " << x << " " << y+height << endl; 

                SVGElement* rect = new Rect(fillColor, x, y, width, height);
                svg_elements.push_back(rect);
            } 
        child = child->NextSiblingElement();
                
        }
    }
}