#include <iostream>
#include <cmath>
#include <vector>
#include <set>
#include <SFML/Graphics.hpp>
# define pi 3.14159265358979323846

class Object {
  static double getDepth (std::vector<std::vector<double>> face) {
    double avg {0};
    for (auto i : face) {
      avg += i[2];
    }
    return avg/face.size();
  }
  static void rotatePoint (std::vector<double> &vec, double theta_x, double theta_y, double theta_z) {
    double x {
      vec[0]*cos(theta_z*pi/180)*cos(theta_y*pi/180) + 
      vec[1]*cos(theta_z*pi/180)*sin(theta_y*pi/180)*sin(theta_x*pi/180) - 
      vec[1]*sin(theta_z*pi/180)*cos(theta_x*pi/180) + 
      vec[2]*cos(theta_z*pi/180)*sin(theta_y*pi/180)*cos(theta_x*pi/180) + 
      vec[2]*sin(theta_z*pi/180)*sin(theta_x*pi/180)
    };
    double y {
      vec[0]*sin(theta_z*pi/180)*cos(theta_y*pi/180) + 
      vec[1]*sin(theta_z*pi/180)*sin(theta_y*pi/180)*sin(theta_x*pi/180) + 
      vec[1]*cos(theta_z*pi/180)*cos(theta_x*pi/180) + 
      vec[2]*sin(theta_z*pi/180)*sin(theta_y*pi/180)*cos(theta_x*pi/180) - 
      vec[2]*cos(theta_z*pi/180)*sin(theta_x*pi/180)
    };
    double z {
      -vec[0]*sin(theta_y*pi/180) + 
      vec[1]*cos(theta_y*pi/180)*sin(theta_x*pi/180) + 
      vec[2]*cos(theta_y*pi/180)*cos(theta_x*pi/180)
    };
    vec[0] = x;
    vec[1] = y;
    vec[2] = z;
  }
  public: static Object cube (double x=0, double y=0, double z=0, double width=1, double height=1, double depth=1) {
    Object temp;

    temp.addPoint(0, x, y, z);
    temp.addPoint(0, x+width, y, z);
    temp.addPoint(0, x+width, y+height, z);
    temp.addPoint(0, x, y+height, z);
    temp.setColor(0, sf::Color {255, 0, 0, 255});  // Red

    temp.addPoint(1, x, y, z);
    temp.addPoint(1, x, y, z+depth);
    temp.addPoint(1, x, y+height, z+depth);
    temp.addPoint(1, x, y+height, z);
    temp.setColor(1, sf::Color {0, 255, 0, 255});  // Green

    temp.addPoint(2, x, y+height, z);
    temp.addPoint(2, x, y+height, z+depth);
    temp.addPoint(2, x+width, y+height, z+depth);
    temp.addPoint(2, x+width, y+height, z);
    temp.setColor(2, sf::Color {0, 0, 255, 255});  // Blue

    temp.addPoint(3, x+width, y+height, z);
    temp.addPoint(3, x+width, y+height, z+depth);
    temp.addPoint(3, x+width, y, z+depth);
    temp.addPoint(3, x+width, y, z);
    temp.setColor(3, sf::Color {255, 255, 0, 255});  // Yellow

    temp.addPoint(4, x+width, y, z);
    temp.addPoint(4, x, y, z);
    temp.addPoint(4, x, y, z+depth);
    temp.addPoint(4, x+width, y, z+depth);
    temp.setColor(4, sf::Color {0, 255, 255, 255});  // Cyan

    temp.addPoint(5, x+width, y, z+depth);
    temp.addPoint(5, x+width, y+height, z+depth);
    temp.addPoint(5, x, y+height, z+depth);
    temp.addPoint(5, x, y, z+depth);
    temp.setColor(5, sf::Color {255, 0, 255, 255});  // Magenta
    return temp;
  }
  public: static Object tetrahedron (double x=0, double y=0, double z=0, double width=1, double height=1, double depth=1) {
    Object temp;
    temp.addPoint(0, x+width, y+height, z+depth);
    temp.addPoint(0, x+width, y, z);
    temp.addPoint(0, x, y+height, z);
    temp.setColor(0, sf::Color {255, 0, 0, 255});  // Red

    temp.addPoint(1, x+width, y+height, z+depth);
    temp.addPoint(1, x+width, y, z);
    temp.addPoint(1, x, y, z+depth);
    temp.setColor(1, sf::Color {0, 255, 0, 255});  // Green

    temp.addPoint(2, x+width, y+height, z+depth);
    temp.addPoint(2, x, y+height, z);
    temp.addPoint(2, x, y, z+depth);
    temp.setColor(2, sf::Color {0, 0, 255, 255});  // Blue

    temp.addPoint(3, x+width, y, z);
    temp.addPoint(3, x, y+height, z);
    temp.addPoint(3, x, y, z+depth);
    temp.setColor(3, sf::Color {255, 255, 0});  // Yellow
    return temp;
  }
  public: static Object octahedron (double x=0, double y=0, double z=0, double width=1, double height=1, double depth=1) {
    Object temp;
    temp.addPoint(0, x, y+height/2, z+depth/2);
    temp.addPoint(0, x+width/2, y, z+depth/2);
    temp.addPoint(0, x+width/2, y+height/2, z);
    temp.setColor(0, sf::Color {255, 0, 0, 255});  // Red
    
    temp.addPoint(1, x, y+height/2, z+depth/2);
    temp.addPoint(1, x+width/2, y, z+depth/2);
    temp.addPoint(1, x+width/2, y+height/2, z+depth);
    temp.setColor(1, sf::Color {0, 255, 0, 255});  // Green

    temp.addPoint(2, x+width, y+height/2, z+depth/2);
    temp.addPoint(2, x+width/2, y, z+depth/2);
    temp.addPoint(2, x+width/2, y+height/2, z);
    temp.setColor(2, sf::Color {0, 0, 255, 255});  // Blue

    temp.addPoint(3, x+width, y+height/2, z+depth/2);
    temp.addPoint(3, x+width/2, y, z+depth/2);
    temp.addPoint(3, x+width/2, y+height/2, z+depth);
    temp.setColor(3, sf::Color {255, 255, 0, 255});  // Yellow

    temp.addPoint(4, x, y+height/2, z+depth/2);
    temp.addPoint(4, x+width/2, y+height, z+depth/2);
    temp.addPoint(4, x+width/2, y+height/2, z);
    temp.setColor(4, sf::Color {0, 255, 255, 255});  // Cyan

    temp.addPoint(5, x, y+height/2, z+depth/2);
    temp.addPoint(5, x+width/2, y+height, z+depth/2);
    temp.addPoint(5, x+width/2, y+height/2, z+depth);
    temp.setColor(5, sf::Color {255, 0, 255, 255});  // Magenta

    temp.addPoint(6, x+width, y+height/2, z+depth/2);
    temp.addPoint(6, x+width/2, y+height, z+depth/2);
    temp.addPoint(6, x+width/2, y+height/2, z);
    temp.setColor(6, sf::Color {0, 0, 0, 255});  // Black

    temp.addPoint(7, x+width, y+height/2, z+depth/2);
    temp.addPoint(7, x+width/2, y+height, z+depth/2);
    temp.addPoint(7, x+width/2, y+height/2, z+depth);
    temp.setColor(7, sf::Color {127, 127, 127, 255});  // Gray
    return temp;
  }
  public: static Object dodecahedron (double x=0, double y=0, double z=0, double width=1, double height=1, double depth=1) {
    Object temp;
    temp.addPoint(0, x+width*(3-std::sqrt(5))/4, y+height*(3-std::sqrt(5))/4, z+depth*(3-std::sqrt(5))/4);
    temp.addPoint(0, x+width/2, y, z+depth*(std::sqrt(5)-1)/4);
    temp.addPoint(0, x+width/2, y, z+depth*(5-std::sqrt(5))/4);
    temp.addPoint(0, x+width*(3-std::sqrt(5))/4, y+height*(3-std::sqrt(5))/4, z+depth*(1+std::sqrt(5))/4);
    temp.addPoint(0, x, y+height*(std::sqrt(5)-1)/4, z+depth/2);
    temp.setColor(0, sf::Color {255, 0, 0, 255});  // Red

    temp.addPoint(1, x+width*(1+std::sqrt(5))/4, y+height*(3-std::sqrt(5))/4, z+depth*(3-std::sqrt(5))/4);
    temp.addPoint(1, x+width/2, y, z+depth*(std::sqrt(5)-1)/4);
    temp.addPoint(1, x+width/2, y, z+depth*(5-std::sqrt(5))/4);
    temp.addPoint(1, x+width*(1+std::sqrt(5))/4, y+height*(3-std::sqrt(5))/4, z+depth*(1+std::sqrt(5))/4);
    temp.addPoint(1, x+width, y+height*(std::sqrt(5)-1)/4, z+depth/2);
    temp.setColor(1, sf::Color {0, 255, 0, 255});  // Green

    temp.addPoint(2, x+width*(3-std::sqrt(5))/4, y+height*(3-std::sqrt(5))/4, z+depth*(1+std::sqrt(5))/4);
    temp.addPoint(2, x+width/2, y, z+depth*(5-std::sqrt(5))/4);
    temp.addPoint(2, x+width*(1+std::sqrt(5))/4, y+height*(3-std::sqrt(5))/4, z+depth*(1+std::sqrt(5))/4);
    temp.addPoint(2, x+width*(5-std::sqrt(5))/4, y+height/2, z+depth);
    temp.addPoint(2, x+width*(std::sqrt(5)-1)/4, y+height/2, z+depth);
    temp.setColor(2, sf::Color {0, 0, 255, 255});  // Blue

    temp.addPoint(3, x+width*(3-std::sqrt(5))/4, y+height*(3-std::sqrt(5))/4, z+depth*(3-std::sqrt(5))/4);
    temp.addPoint(3, x+width/2, y, z+depth*(std::sqrt(5)-1)/4);
    temp.addPoint(3, x+width*(1+std::sqrt(5))/4, y+height*(3-std::sqrt(5))/4, z+depth*(3-std::sqrt(5))/4);
    temp.addPoint(3, x+width*(5-std::sqrt(5))/4, y+height/2, z);
    temp.addPoint(3, x+width*(std::sqrt(5)-1)/4, y+height/2, z);
    temp.setColor(3, sf::Color {255, 255, 0, 255});  // Yellow

    temp.addPoint(4, x+width*(3-std::sqrt(5))/4, y+height*(1+std::sqrt(5))/4, z+depth*(3-std::sqrt(5))/4);
    temp.addPoint(4, x+width/2, y+height, z+depth*(std::sqrt(5)-1)/4);
    temp.addPoint(4, x+width/2, y+height, z+depth*(5-std::sqrt(5))/4);
    temp.addPoint(4, x+width*(3-std::sqrt(5))/4, y+height*(1+std::sqrt(5))/4, z+depth*(1+std::sqrt(5))/4);
    temp.addPoint(4, x, y+height*(5-std::sqrt(5))/4, z+depth/2);
    temp.setColor(4, sf::Color {0, 255, 255, 255});  // Cyan

    temp.addPoint(5, x+width*(1+std::sqrt(5))/4, y+height*(1+std::sqrt(5))/4, z+depth*(3-std::sqrt(5))/4);
    temp.addPoint(5, x+width/2, y+height, z+depth*(std::sqrt(5)-1)/4);
    temp.addPoint(5, x+width/2, y+height, z+depth*(5-std::sqrt(5))/4);
    temp.addPoint(5, x+width*(1+std::sqrt(5))/4, y+height*(1+std::sqrt(5))/4, z+depth*(1+std::sqrt(5))/4);
    temp.addPoint(5, x+width, y+height*(5-std::sqrt(5))/4, z+depth/2);
    temp.setColor(5, sf::Color {255, 0, 255, 255});  // Magenta

    temp.addPoint(6, x+width*(3-std::sqrt(5))/4, y+height*(1+std::sqrt(5))/4, z+depth*(1+std::sqrt(5))/4);
    temp.addPoint(6, x+width/2, y+height, z+depth*(5-std::sqrt(5))/4);
    temp.addPoint(6, x+width*(1+std::sqrt(5))/4, y+height*(1+std::sqrt(5))/4, z+depth*(1+std::sqrt(5))/4);
    temp.addPoint(6, x+width*(5-std::sqrt(5))/4, y+height/2, z+depth);
    temp.addPoint(6, x+width*(std::sqrt(5)-1)/4, y+height/2, z+depth);
    temp.setColor(6, sf::Color {0, 0, 0, 255});  // Black

    temp.addPoint(7, x+width*(3-std::sqrt(5))/4, y+height*(1+std::sqrt(5))/4, z+depth*(3-std::sqrt(5))/4);
    temp.addPoint(7, x+width/2, y+height, z+depth*(std::sqrt(5)-1)/4);
    temp.addPoint(7, x+width*(1+std::sqrt(5))/4, y+height*(1+std::sqrt(5))/4, z+depth*(3-std::sqrt(5))/4);
    temp.addPoint(7, x+width*(5-std::sqrt(5))/4, y+height/2, z);
    temp.addPoint(7, x+width*(std::sqrt(5)-1)/4, y+height/2, z);
    temp.setColor(7, sf::Color {127, 127, 127, 255});  // Gray

    temp.addPoint(8, x+width*(1+std::sqrt(5))/4, y+height*(3-std::sqrt(5))/4, z+depth*(3-std::sqrt(5))/4);
    temp.addPoint(8, x+width*(5-std::sqrt(5))/4, y+height/2, z);
    temp.addPoint(8, x+width*(1+std::sqrt(5))/4, y+height*(1+std::sqrt(5))/4, z+depth*(3-std::sqrt(5))/4);
    temp.addPoint(8, x+width, y+height*(5-std::sqrt(5))/4, z+depth/2);
    temp.addPoint(8, x+width, y+height*(std::sqrt(5)-1)/4, z+depth/2);
    temp.setColor(8, sf::Color {127, 0, 0, 255});  // Dark Red

    temp.addPoint(9, x+width*(1+std::sqrt(5))/4, y+height*(3-std::sqrt(5))/4, z+depth*(1+std::sqrt(5))/4);
    temp.addPoint(9, x+width*(5-std::sqrt(5))/4, y+height/2, z+depth);
    temp.addPoint(9, x+width*(1+std::sqrt(5))/4, y+height*(1+std::sqrt(5))/4, z+depth*(1+std::sqrt(5))/4);
    temp.addPoint(9, x+width, y+height*(5-std::sqrt(5))/4, z+depth/2);
    temp.addPoint(9, x+width, y+height*(std::sqrt(5)-1)/4, z+depth/2);
    temp.setColor(9, sf::Color {0, 127, 0, 255});  // Dark Green

    temp.addPoint(10, x+width*(3-std::sqrt(5))/4, y+height*(3-std::sqrt(5))/4, z+depth*(3-std::sqrt(5))/4);
    temp.addPoint(10, x+width*(std::sqrt(5)-1)/4, y+height/2, z);
    temp.addPoint(10, x+width*(3-std::sqrt(5))/4, y+height*(1+std::sqrt(5))/4, z+depth*(3-std::sqrt(5))/4);
    temp.addPoint(10, x, y+height*(5-std::sqrt(5))/4, z+depth/2);
    temp.addPoint(10, x, y+height*(std::sqrt(5)-1)/4, z+depth/2);
    temp.setColor(10, sf::Color {0, 0, 127, 255});  // Dark Blue

    temp.addPoint(11, x+width*(3-std::sqrt(5))/4, y+height*(3-std::sqrt(5))/4, z+depth*(1+std::sqrt(5))/4);
    temp.addPoint(11, x+width*(std::sqrt(5)-1)/4, y+height/2, z+depth);
    temp.addPoint(11, x+width*(3-std::sqrt(5))/4, y+height*(1+std::sqrt(5))/4, z+depth*(1+std::sqrt(5))/4);
    temp.addPoint(11, x, y+height*(5-std::sqrt(5))/4, z+depth/2);
    temp.addPoint(11, x, y+height*(std::sqrt(5)-1)/4, z+depth/2);
    temp.setColor(11, sf::Color {127, 127, 0, 255});  // Dark Yellow
    return temp;
  }
  public: static Object icosahedron (double x=0, double y=0, double z=0, double width=1, double height=1, double depth=1) {
    Object temp;
    temp.addPoint(0, x+width/2, y, z+depth*(3-std::sqrt(5))/4);
    temp.addPoint(0, x+width*(3-std::sqrt(5))/4, y+height/2, z);
    temp.addPoint(0, x+width*(1+std::sqrt(5))/4, y+height/2, z);
    temp.setColor(0, sf::Color {255, 0, 0, 255});  // Red

    temp.addPoint(1, x+width/2, y+height, z+depth*(3-std::sqrt(5))/4);
    temp.addPoint(1, x+width*(3-std::sqrt(5))/4, y+height/2, z);
    temp.addPoint(1, x+width*(1+std::sqrt(5))/4, y+height/2, z);
    temp.setColor(1, sf::Color {0, 255, 0, 255});  // Green

    temp.addPoint(2, x+width/2, y+height, z+depth*(3-std::sqrt(5))/4);
    temp.addPoint(2, x+width*(1+std::sqrt(5))/4, y+height/2, z);
    temp.addPoint(2, x+width, y+height*(1+std::sqrt(5))/4, z+depth/2);
    temp.setColor(2, sf::Color {0, 0, 255, 255});  // Blue

    temp.addPoint(3, x+width/2, y, z+depth*(3-std::sqrt(5))/4);
    temp.addPoint(3, x+width*(1+std::sqrt(5))/4, y+height/2, z);
    temp.addPoint(3, x+width, y+height*(3-std::sqrt(5))/4, z+depth/2);
    temp.setColor(3, sf::Color {255, 255, 0, 255});  // Yellow

    temp.addPoint(4, x+width*(1+std::sqrt(5))/4, y+height/2, z);
    temp.addPoint(4, x+width, y+height*(1+std::sqrt(5))/4, z+depth/2);
    temp.addPoint(4, x+width, y+height*(3-std::sqrt(5))/4, z+depth/2);
    temp.setColor(4, sf::Color {0, 255, 255, 255});  // Cyan

    temp.addPoint(5, x+width/2, y+height, z+depth*(1+std::sqrt(5))/4);
    temp.addPoint(5, x+width/2, y+height, z+depth*(3-std::sqrt(5))/4);
    temp.addPoint(5, x+width, y+height*(1+std::sqrt(5))/4, z+depth/2);
    temp.setColor(5, sf::Color {255, 0, 255, 255});  // Magenta

    temp.addPoint(6, x+width/2, y+height, z+depth*(1+std::sqrt(5))/4);
    temp.addPoint(6, x+width/2, y+height, z+depth*(3-std::sqrt(5))/4);
    temp.addPoint(6, x, y+height*(1+std::sqrt(5))/4, z+depth/2);
    temp.setColor(6, sf::Color {0, 0, 0, 255});  // Black

    temp.addPoint(7, x+width*(1+std::sqrt(5))/4, y+height/2, z+depth);
    temp.addPoint(7, x+width, y+height*(1+std::sqrt(5))/4, z+depth/2);
    temp.addPoint(7, x+width, y+height*(3-std::sqrt(5))/4, z+depth/2);
    temp.setColor(7, sf::Color {127, 127, 127, 255});  // Gray

    temp.addPoint(8, x+width/2, y, z+depth*(1+std::sqrt(5))/4);
    temp.addPoint(8, x+width*(3-std::sqrt(5))/4, y+height/2, z+depth);
    temp.addPoint(8, x+width*(1+std::sqrt(5))/4, y+height/2, z+depth);
    temp.setColor(8, sf::Color {127, 0, 0, 255});  // Dark Red

    temp.addPoint(9, x+width/2, y+height, z+depth*(1+std::sqrt(5))/4);
    temp.addPoint(9, x+width*(3-std::sqrt(5))/4, y+height/2, z+depth);
    temp.addPoint(9, x+width*(1+std::sqrt(5))/4, y+height/2, z+depth);
    temp.setColor(9, sf::Color {0, 127, 0, 255});  // Dark Green

    temp.addPoint(10, x+width, y+height*(1+std::sqrt(5))/4, z+depth/2);
    temp.addPoint(10, x+width/2, y+height, z+depth*(1+std::sqrt(5))/4);
    temp.addPoint(10, x+width*(1+std::sqrt(5))/4, y+height/2, z+depth);
    temp.setColor(10, sf::Color {0, 0, 127, 255});  // Dark Blue

    temp.addPoint(11, x+width/2, y, z+depth*(1+std::sqrt(5))/4);
    temp.addPoint(11, x+width*(1+std::sqrt(5))/4, y+height/2, z+depth);
    temp.addPoint(11, x+width, y+height*(3-std::sqrt(5))/4, z+depth/2);
    temp.setColor(11, sf::Color {127, 127, 0, 255});  // Dark Yellow

    temp.addPoint(12, x+width/2, y, z+depth*(1+std::sqrt(5))/4);
    temp.addPoint(12, x+width/2, y, z+depth*(3-std::sqrt(5))/4);
    temp.addPoint(12, x+width, y+height*(3-std::sqrt(5))/4, z+depth/2);
    temp.setColor(12, sf::Color {0, 127, 127, 255});  // Darl Cyan

    temp.addPoint(13, x+width/2, y, z+depth*(1+std::sqrt(5))/4);
    temp.addPoint(13, x+width/2, y, z+depth*(3-std::sqrt(5))/4);
    temp.addPoint(13, x, y+height*(3-std::sqrt(5))/4, z+depth/2);
    temp.setColor(13, sf::Color {127, 0, 127, 255});  // Dark Magenta

    temp.addPoint(14, x+width/2, y+height, z+depth*(3-std::sqrt(5))/4);
    temp.addPoint(14, x+width*(3-std::sqrt(5))/4, y+height/2, z);
    temp.addPoint(14, x, y+height*(1+std::sqrt(5))/4, z+depth/2);
    temp.setColor(14, sf::Color {255, 127, 127, 255});  // Light Red

    temp.addPoint(15, x+width/2, y, z+depth*(3-std::sqrt(5))/4);
    temp.addPoint(15, x+width*(3-std::sqrt(5))/4, y+height/2, z);
    temp.addPoint(15, x, y+height*(3-std::sqrt(5))/4, z+depth/2);
    temp.setColor(15, sf::Color {127, 255, 127, 255});  // Light Green

    temp.addPoint(16, x+width*(3-std::sqrt(5))/4, y+height/2, z);
    temp.addPoint(16, x, y+height*(1+std::sqrt(5))/4, z+depth/2);
    temp.addPoint(16, x, y+height*(3-std::sqrt(5))/4, z+depth/2);
    temp.setColor(16, sf::Color {127, 127, 255, 255});  // Light Blue

    temp.addPoint(17, x, y+height*(1+std::sqrt(5))/4, z+depth/2);
    temp.addPoint(17, x+width/2, y+height, z+depth*(1+std::sqrt(5))/4);
    temp.addPoint(17, x+width*(3-std::sqrt(5))/4, y+height/2, z+depth);
    temp.setColor(17, sf::Color {255, 255, 127, 255});  // Light Yellow

    temp.addPoint(18, x+width/2, y, z+depth*(1+std::sqrt(5))/4);
    temp.addPoint(18, x+width*(3-std::sqrt(5))/4, y+height/2, z+depth);
    temp.addPoint(18, x, y+height*(3-std::sqrt(5))/4, z+depth/2);
    temp.setColor(18, sf::Color {127, 255, 255, 255});  // Light Cyan

    temp.addPoint(19, x+width*(3-std::sqrt(5))/4, y+height/2, z+depth);
    temp.addPoint(19, x, y+height*(1+std::sqrt(5))/4, z+depth/2);
    temp.addPoint(19, x, y+height*(3-std::sqrt(5))/4, z+depth/2);
    temp.setColor(19, sf::Color {255, 127, 255, 255});  // Light Magenta
    return temp;
  }
  private:
    std::vector<std::vector<std::vector<double>>> coords;
    std::vector<sf::ConvexShape> polygon;
    double center_x {0};
    double center_y {0};
    double center_z {0};

  public:
    void setPoint (int face, int index, double x, double y, double z) {
      if (face >= coords.size()) {
        coords.push_back(std::vector<std::vector<double>> {});
        polygon.push_back(sf::ConvexShape {});
      }
      if (index >= coords[face].size()) {
        coords[face].push_back(std::vector<double> {});
      }
      coords[face][index] = std::vector<double> {x, y, z};
      polygon[face].setPoint(index, sf::Vector2f(x, y));
      autoCenter();
    }
    void addPoint (int face, double x, double y, double z) {
      if (face >= coords.size()) {
        coords.push_back(std::vector<std::vector<double>> {});
        polygon.push_back(sf::ConvexShape {});
      }
      coords[face].push_back(std::vector<double> {x, y, z});
      polygon[face].setPointCount(coords[face].size());
      polygon[face].setPoint(coords[face].size()-1, sf::Vector2f(x, y));
      autoCenter();
    }
    void setColor(int face, sf::Color color=sf::Color {(0, 0, 0, 255)}) {
      polygon[face].setFillColor(color);
    }
    void setOutlineColor(int face, sf::Color color=sf::Color {(0, 0, 0, 255)}) {
      polygon[face].setOutlineColor(color);
    }
    void setOutlineThickness (int face, int thick=1) {
      polygon[face].setOutlineThickness(thick);
    }
    void setPosition (float x=0, float y=0, float z=0) {
      for (int face {0}; face < coords.size(); face++) {
        for (int point {0}; point < coords[face].size(); point++) {
          coords[face][point][0] += (x - center_x);
          coords[face][point][1] += (y - center_y);
          coords[face][point][2] += (z - center_z);
        }
      }
    }
    void movePosition (float x=0, float y=0, float z=0) {
      for (int face {0}; face < coords.size(); face++) {
        for (int point {0}; point < coords[face].size(); point++) {
          coords[face][point][0] += x;
          coords[face][point][1] += y;
          coords[face][point][2] += z;
        }
      }
    }
    void autoCenter () {
      center_x = 0;
      center_y = 0;
      center_z = 0;
      int vertices {0};
      for (auto face : coords) {
        for (auto i : face) {
          center_x += i[0];
          center_y += i[1];
          center_z += i[2];
          vertices++;
        }
      }
      center_x /= vertices;
      center_y /= vertices;
      center_z /= vertices;
    }
    void rotate (double theta_x=0, double theta_y=0, double theta_z=0) {
      for (int face {0}; face < coords.size(); face++) {
        for (int point {0}; point < coords[face].size(); point++) {
          coords[face][point][0] -= center_x;
          coords[face][point][1] -= center_y;
          coords[face][point][2] -= center_z;
          rotatePoint(coords[face][point], theta_x, theta_y, theta_z);
          coords[face][point][0] += center_x;
          coords[face][point][1] += center_y;
          coords[face][point][2] += center_z;
          polygon[face].setPoint(point, sf::Vector2f(coords[face][point][0], coords[face][point][1]));
        }
      }
    }
    void draw (sf::RenderWindow& window) const {
      std::set<int> indeces;
      for (int loop {0}; loop < coords.size(); loop++) {
        int current {-1};
        for (int index {0}; index < coords.size(); index++) {
          if (((current!=-1)?(getDepth(coords[index]) >= getDepth(coords[current])):true) && indeces.find(index) == indeces.end())
            current = index;
        }
        window.draw(polygon[current]);
        indeces.insert(current);
      }
    }
};

int main()
{
  Object polygon {Object::icosahedron(50, 50, 50, 100, 100, 100)};

	sf::RenderWindow window(sf::VideoMode(200, 200), "3D");

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
      if(event.type == sf::Event::KeyReleased) {
        if(event.key.code == sf::Keyboard::W) {
          polygon.rotate(-20, 0, 0);
        }
        if(event.key.code == sf::Keyboard::S) {
          polygon.rotate(20, 0, 0);
        }
        if(event.key.code == sf::Keyboard::A) {
          polygon.rotate(0, 20, 0);
        }
        if(event.key.code == sf::Keyboard::D) {
          polygon.rotate(0, -20, 0);
        }
      }
		}
		window.clear();
    polygon.draw(window);
    
		window.display();
	}
}
