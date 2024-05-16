
#include <iostream>
#include <sstream>
#include "SVGElements.hpp"
#include "external/tinyxml2/tinyxml2.h"

using namespace std;
using namespace tinyxml2;

namespace svg
{
    std::vector<SVGElement *> parseGroup(XMLElement* child, vector<SVGElement *>& elements, const char* transform){

        while (child != nullptr){
            std::string elementName = child->Name();
            SVGElement* element;

            if (elementName == "ellipse"){
                    int cx = child->IntAttribute("cx");
                    int cy = child->IntAttribute("cy");
                    int rx = child->IntAttribute("rx");
                    int ry = child->IntAttribute("ry"); 
                    string fill = child->Attribute("fill");
                    Color fillColor = parse_color(fill);

                    Point center = Point{cx,cy};
                    element = new Ellipse(fillColor, center, rx, ry); 
            }
            else if (elementName == "circle"){
                int cx = child->IntAttribute("cx");
                int cy = child->IntAttribute("cy");
                int r = child->IntAttribute("r");
                string fill = child->Attribute("fill");
                Color fillColor = parse_color(fill);

                Point center = Point{cx,cy};

                element = new Circle(fillColor, center, r);
            }
            else if (elementName == "polyline") {
                    std::string pointsStr = child->Attribute("points");
                    std::vector<Point> points = parse_points(pointsStr);
                    std::string stroke = child->Attribute("stroke");
                    Color strokeColor = parse_color(stroke);

                    element = new Polyline(strokeColor, points);
            }
            else if (elementName == "line") {
                    int x1 = child->IntAttribute("x1");
                    int y1 = child->IntAttribute("y1");
                    int x2 = child->IntAttribute("x2");
                    int y2 = child->IntAttribute("y2");
                    std::string stroke = child->Attribute("stroke");
                    Color strokeColor = parse_color(stroke);

                    element = new Line(strokeColor, x1,y1,x2,y2);
            }
            else if (elementName == "polygon") {
                std::string pointsStr = child->Attribute("points");
                std::vector<Point> points = parse_points(pointsStr);
                std::string fill = child->Attribute("fill");
                Color fillColor = parse_color(fill);

                element = new Polygon(fillColor, points);
            }
            else if (elementName == "rect") {
                int x = child->IntAttribute("x");
                int y = child->IntAttribute("y");
                int width = child->IntAttribute("width");
                int height = child->IntAttribute("height");
                std::string fill = child->Attribute("fill");
                Color fillColor = parse_color(fill);

                element = new Rect(fillColor, x, y, width, height);
            } 
            else if(elementName == "g") {
                std::vector<SVGElement *> elements;
                elements = parseGroup(child->FirstChildElement(), elements, child->Attribute("transform"));
                element = new Group(elements);
            }

            //transf
            if (child->Attribute("transform")){
                        //!@param tr Transformação do elemento
                        string tr = child->Attribute("transform");
                        
                        int ox = 0;
                        int oy = 0; //default origin values

                        Point origin = Point{ox, oy};

                        if (child->Attribute("transform-origin")){
                            string origin_str = child->Attribute("transform-origin");
                            istringstream iss(origin_str);
                            int x, y;
                            iss >> x >> y;

                            origin.x = x;
                            origin.y = y;
                        }

                        if(tr.find("translate")!= string::npos){
                            istringstream iss(tr);

                            int x, y;
                            char ch;

                            iss.ignore(tr.size(), '(');
                            iss >> x;
                            if (iss.peek() == ',') iss >> ch;
                            iss  >> y;

                            element->translate(x, y);
                        }
                        else if(tr.find("rotate") != string::npos){
                            istringstream iss(tr);

                            iss.ignore(tr.size(), '(');
                            int angle;
                            iss >> angle;

                            

                            element->rotate(origin.x, origin.y, angle);
                        }
                        else if(tr.find("scale") != string::npos){
                            istringstream iss(tr);

                            iss.ignore(tr.size(), '(');
                            int factor;
                            iss >> factor;

                            element->scale(origin.x, origin.y, factor);
                        }
            }
            //push back
            elements.push_back(element);
            child = child->NextSiblingElement();
        }
        return elements;
    }


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
            SVGElement* element;

            if (elementName == "ellipse"){
                    int cx = child->IntAttribute("cx");
                    int cy = child->IntAttribute("cy");
                    int rx = child->IntAttribute("rx");
                    int ry = child->IntAttribute("ry"); 
                    string fill = child->Attribute("fill");
                    Color fillColor = parse_color(fill);

                    Point center = Point{cx,cy};
                    element = new Ellipse(fillColor, center, rx, ry); 
            }
            else if (elementName == "circle"){
                    int cx = child->IntAttribute("cx");
                    int cy = child->IntAttribute("cy");
                    int r = child->IntAttribute("r");
                    string fill = child->Attribute("fill");
                    Color fillColor = parse_color(fill);

                    Point center = Point{cx,cy};

                    element = new Circle(fillColor, center, r);
            }
            else if (elementName == "polyline") {
                    std::string pointsStr = child->Attribute("points");
                    std::vector<Point> points = parse_points(pointsStr);
                    std::string stroke = child->Attribute("stroke");
                    Color strokeColor = parse_color(stroke);

                    element = new Polyline(strokeColor, points);
            }
            else if (elementName == "line") {
                    int x1 = child->IntAttribute("x1");
                    int y1 = child->IntAttribute("y1");
                    int x2 = child->IntAttribute("x2");
                    int y2 = child->IntAttribute("y2");
                    std::string stroke = child->Attribute("stroke");
                    Color strokeColor = parse_color(stroke);

                    element = new Line(strokeColor, x1,y1,x2,y2);
            }
            else if (elementName == "polygon") {
                std::string pointsStr = child->Attribute("points");
                std::vector<Point> points = parse_points(pointsStr);
                std::string fill = child->Attribute("fill");
                Color fillColor = parse_color(fill);

                element = new Polygon(fillColor, points);
            }
            else if (elementName == "rect") {
                int x = child->IntAttribute("x");
                int y = child->IntAttribute("y");
                int width = child->IntAttribute("width");
                int height = child->IntAttribute("height");
                std::string fill = child->Attribute("fill");
                Color fillColor = parse_color(fill);

                element = new Rect(fillColor, x, y, width, height);
            } 
            else if(elementName == "g") {
                std::vector<SVGElement *> elements;
                elements = parseGroup(child->FirstChildElement(), elements, child->Attribute("transform"));
                element = new Group(elements);
            }
            if(child == nullptr) return;
            
            //transf
            if (child->Attribute("transform")){
                        //!@param tr Transformação do elemento
                        string tr = child->Attribute("transform");
                        
                        int ox = 0;
                        int oy = 0; //default origin values

                        Point origin = Point{ox, oy};

                        if (child->Attribute("transform-origin")){
                            string origin_str = child->Attribute("transform-origin");
                            istringstream iss(origin_str);
                            int x, y;
                            iss >> x >> y;

                            origin.x = x;
                            origin.y = y;
                        }

                        if(tr.find("translate")!= string::npos){

                            istringstream iss(tr);

                            int x, y;
                            char ch;

                            iss.ignore(tr.size(), '(');
                            iss >> x;
                            if (iss.peek() == ',') iss >> ch;
                            iss  >> y;

                            element->translate(x, y);
                        }
                        else if(tr.find("rotate") != string::npos){
                            istringstream iss(tr);

                            iss.ignore(tr.size(), '(');
                            int angle;
                            iss >> angle;

                            

                            element->rotate(origin.x, origin.y, angle);
                        }
                        else if(tr.find("scale") != string::npos){
                            istringstream iss(tr);

                            iss.ignore(tr.size(), '(');
                            int factor;
                            iss >> factor;

                            element->scale(origin.x, origin.y, factor);
                        }
                    }

            //push back
        svg_elements.push_back(element);
        child = child->NextSiblingElement();
                
        }
    }
}