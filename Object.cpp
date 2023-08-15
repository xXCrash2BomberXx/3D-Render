#include <SDL2/SDL.h>
#include <vector>
#include <array>
#include <cmath>
#define pi 3.14159265358979323846

class Object
{
private:
	struct Prop
	{
		std::array<char, 4> fill = {0, 0, 0, 0};
		std::array<char, 4> outline = {0, 0, 0, 0};
		int thickness = 1;
		bool useOutline = false;

		void setFillColor(char r, char g, char b, char a = 255)
		{
			fill[0] = r;
			fill[1] = g;
			fill[2] = b;
			fill[3] = a;
			if (!useOutline)
			{
				outline = fill;
			}
		}
		void setOutlineColor(char r, char g, char b, char a = 255)
		{
			useOutline = true;
			outline[0] = r;
			outline[1] = g;
			outline[2] = b;
			outline[3] = a;
		}

		void setOutlineThickness(int thick = 1)
		{
			thickness = thick;
		}
	};

	static bool isInsidePolygon(const std::vector<std::array<double, 3>> &polygon,
								double x = 0, double y = 0)
	{
		return isInsidePolygon(polygon, 0, 0, 0, 0, 0, 0, x, y);
	}

	static bool isInsidePolygon(const std::vector<std::array<double, 3>> &polygon,
								std::array<double, 2> point)
	{
		return isInsidePolygon(polygon, 0, 0, 0, 0, 0, 0, point[0], point[1]);
	}

	static bool isInsidePolygon(const std::vector<std::array<double, 3>> &polygon,
								std::array<double, 3> center,
								std::array<double, 3> theta,
								std::array<double, 2> point)
	{
		return isInsidePolygon(polygon, center[0], center[1], center[2], theta[0], theta[1], theta[2], point[0], point[1]);
	}

	static bool isInsidePolygon(const std::vector<std::array<double, 3>> &polygon,
								std::array<double, 3> center,
								std::array<double, 3> theta,
								double x, double y)
	{
		return isInsidePolygon(polygon, center[0], center[1], center[2], theta[0], theta[1], theta[2], x, y);
	}

	static bool isInsidePolygon(const std::vector<std::array<double, 3>> &polygon,
								const std::array<double, 3> &center,
								double theta_x, double theta_y, double theta_z,
								double x, double y)
	{
		return isInsidePolygon(polygon, center[0], center[1], center[2], theta_x, theta_y, theta_z, x, y);
	}

	static bool isInsidePolygon(const std::vector<std::array<double, 3>> &polygon,
								double center_x, double center_y, double center_z,
								double theta_x, double theta_y, double theta_z,
								double x, double y)
	{
		const int n = polygon.size();
		int cnt = 0;
		std::array<double, 3> p1, p2;

		for (int i = 0; i < n; i++)
		{
			p1 = polygon[i];
			p2 = polygon[(i + 1) % n];
			if (theta_x || theta_y || theta_z)
			{
				p1[0] -= center_x;
				p1[1] -= center_y;
				p1[2] -= center_z;
				p1 = rotatePoint(p1, theta_x, theta_y, theta_z);
				p1[0] += center_x;
				p1[1] += center_y;
				p1[2] += center_z;

				p2[0] -= center_x;
				p2[1] -= center_y;
				p2[2] -= center_z;
				p2 = rotatePoint(p2, theta_x, theta_y, theta_z);
				p2[0] += center_x;
				p2[1] += center_y;
				p2[2] += center_z;
			}

			if ((p1[1] <= y && p2[1] <= y) || (p1[1] > y && p2[1] > y))
				continue;

			double xIntersection = (p1[0] * (p2[1] - y) + p2[0] * (y - p1[1])) / (p2[1] - p1[1]);

			if (xIntersection > x)
				cnt++;
		}

		return cnt % 2 == 1;
	}

	static double getDepth(const std::vector<std::array<double, 3>> &face,
						   std::array<double, 3> theta)
	{
		return getDepth(face, 0, 0, 0, theta[0], theta[1], theta[2]);
	}

	static double getDepth(const std::vector<std::array<double, 3>> &face,
						   double theta_x, double theta_y, double theta_z)
	{
		return getDepth(face, 0, 0, 0, theta_x, theta_y, theta_z);
	}

	static double getDepth(const std::vector<std::array<double, 3>> &face,
						   double center_x, double center_y, double center_z,
						   std::array<double, 3> theta)
	{
		return getDepth(face, center_x, center_y, center_z, theta[0], theta[1], theta[1]);
	}

	static double getDepth(const std::vector<std::array<double, 3>> &face,
						   std::array<double, 3> center,
						   std::array<double, 3> theta)
	{
		return getDepth(face, center[0], center[1], center[2], theta[0], theta[1], theta[1]);
	}

	static double getDepth(const std::vector<std::array<double, 3>> &face,
						   std::array<double, 3> center,
						   double theta_x, double theta_y, double theta_z)
	{
		return getDepth(face, center[0], center[1], center[2], theta_x, theta_y, theta_z);
	}

	static double getDepth(const std::vector<std::array<double, 3>> &face,
						   double center_x, double center_y, double center_z,
						   double theta_x, double theta_y, double theta_z)
	{
		double avg{0};
		for (auto i : face)
		{
			i[0] -= center_x;
			i[1] -= center_y;
			i[2] -= center_z;
			avg += rotatePoint(i, theta_x, theta_y, theta_z)[2] + center_z;
			i[0] += center_x;
			i[1] += center_y;
			i[2] += center_z;
		}
		return avg / face.size();
	}

	static std::array<double, 3> rotatePoint(double x, double y, double z, std::array<double, 3> theta)
	{
		return rotatePoint(std::array<double, 3>{x, y, z}, theta[0], theta[1], theta[2]);
	}

	static std::array<double, 3> rotatePoint(double x, double y, double z, double theta_x, double theta_y, double theta_z)
	{
		return rotatePoint(std::array<double, 3>{x, y, z}, theta_x, theta_y, theta_z);
	}

	static std::array<double, 3> rotatePoint(const std::array<double, 3> &vec, const std::array<double, 3> &theta)
	{
		return rotatePoint(vec, theta[0], theta[1], theta[2]);
	}

	static std::array<double, 3> rotatePoint(const std::array<double, 3> &vec, double theta_x, double theta_y, double theta_z)
	{
		if (!(theta_x || theta_y || theta_z))
			return vec;
		return std::array<double, 3>{
			vec[0] * cos(theta_z * pi / 180) * cos(theta_y * pi / 180) +
				vec[1] * cos(theta_z * pi / 180) * sin(theta_y * pi / 180) * sin(theta_x * pi / 180) -
				vec[1] * sin(theta_z * pi / 180) * cos(theta_x * pi / 180) +
				vec[2] * cos(theta_z * pi / 180) * sin(theta_y * pi / 180) * cos(theta_x * pi / 180) +
				vec[2] * sin(theta_z * pi / 180) * sin(theta_x * pi / 180),

			vec[0] * sin(theta_z * pi / 180) * cos(theta_y * pi / 180) +
				vec[1] * sin(theta_z * pi / 180) * sin(theta_y * pi / 180) * sin(theta_x * pi / 180) +
				vec[1] * cos(theta_z * pi / 180) * cos(theta_x * pi / 180) +
				vec[2] * sin(theta_z * pi / 180) * sin(theta_y * pi / 180) * cos(theta_x * pi / 180) -
				vec[2] * cos(theta_z * pi / 180) * sin(theta_x * pi / 180),

			-vec[0] * sin(theta_y * pi / 180) +
				vec[1] * cos(theta_y * pi / 180) * sin(theta_x * pi / 180) +
				vec[2] * cos(theta_y * pi / 180) * cos(theta_x * pi / 180)};
	}

	enum ObjectType
	{
		pyramid,
		prism
	};

public:
	static Object Pyramid(unsigned int edges,
						  double x = 0, double y = 0, double z = 0,
						  double width = 1, double height = 1, double depth = 1,
						  double theta_x = 0, double theta_y = 0, double theta_z = 0)
	{
		return generate(ObjectType::pyramid, edges, x, y, z, width, height, depth, theta_x, theta_y, theta_z);
	}

	static Object Prism(unsigned int edges,
						double x = 0, double y = 0, double z = 0,
						double width = 1, double height = 1, double depth = 1,
						double theta_x = 0, double theta_y = 0, double theta_z = 0)
	{
		return generate(ObjectType::prism, edges, x, y, z, width, height, depth, theta_x, theta_y, theta_z);
	}

private:
	static Object generate(ObjectType objectType, unsigned int edges,
						   double x = 0, double y = 0, double z = 0,
						   double width = 1, double height = 1, double depth = 1,
						   double theta_x = 0, double theta_y = 0, double theta_z = 0)
	{
		std::vector<std::array<char, 4>> args{
			{(char)255, 0, 0, (char)255},
			{0, (char)255, 0, (char)255},
			{0, 0, (char)255, (char)255},
			{(char)255, (char)255, 0, (char)255},
			{0, (char)255, (char)255, (char)255},
			{(char)255, 0, (char)255, (char)255},
			{0, 0, 0, (char)255},
			{(char)127, (char)127, (char)127, (char)255},
			{(char)127, 0, 0, (char)255},
			{0, (char)127, 0, (char)255},
			{0, 0, (char)127, (char)255},
			{(char)127, (char)127, 0, (char)255},
			{0, (char)127, (char)127, (char)255},
			{(char)127, 0, (char)127, (char)255},
			{(char)255, (char)127, (char)127, (char)255},
			{(char)127, (char)255, (char)127, (char)255},
			{(char)127, (char)127, (char)255, (char)255},
			{(char)255, (char)255, (char)127, (char)255},
			{(char)127, (char)255, (char)255, (char)255},
			{(char)255, (char)127, (char)255, (char)255},
		};
		return generate(objectType, edges, args, x, y, z, width, height, depth, theta_x, theta_y, theta_z);
	}

public:
	static Object Pyramid(unsigned int edges, const std::vector<std::array<char, 4>> &fill,
						  double x = 0, double y = 0, double z = 0,
						  double width = 1, double height = 1, double depth = 1,
						  double theta_x = 0, double theta_y = 0, double theta_z = 0)
	{
		return generate(ObjectType::pyramid, edges, fill, x, y, z, width, height, depth, theta_x, theta_y, theta_z);
	}

	static Object Prism(unsigned int edges, const std::vector<std::array<char, 4>> &fill,
						double x = 0, double y = 0, double z = 0,
						double width = 1, double height = 1, double depth = 1,
						double theta_x = 0, double theta_y = 0, double theta_z = 0)
	{
		return generate(ObjectType::prism, edges, fill, x, y, z, width, height, depth, theta_x, theta_y, theta_z);
	}

private:
	static Object generate(ObjectType objectType, unsigned int edges, const std::vector<std::array<char, 4>> &fill,
						   double x = 0, double y = 0, double z = 0,
						   double width = 1, double height = 1, double depth = 1,
						   double theta_x = 0, double theta_y = 0, double theta_z = 0)
	{
		std::vector<Prop> temp;
		temp.reserve(fill.size());
		for (auto color : fill)
		{
			Prop temp2;
			temp2.setFillColor(color[0], color[1], color[2], color[3]);
			temp.push_back(temp2);
		}
		return generate(objectType, edges, temp, x, y, z, width, height, depth, theta_x, theta_y, theta_z);
	}

public:
	static Object Pyramid(unsigned int edges, const std::vector<std::array<std::array<char, 4>, 2>> &colors,
						  double x = 0, double y = 0, double z = 0,
						  double width = 1, double height = 1, double depth = 1,
						  double theta_x = 0, double theta_y = 0, double theta_z = 0)
	{
		return generate(ObjectType::pyramid, edges, colors, x, y, z, width, height, depth, theta_x, theta_y, theta_z);
	}

	static Object Prism(unsigned int edges, const std::vector<std::array<std::array<char, 4>, 2>> &colors,
						double x = 0, double y = 0, double z = 0,
						double width = 1, double height = 1, double depth = 1,
						double theta_x = 0, double theta_y = 0, double theta_z = 0)
	{
		return generate(ObjectType::prism, edges, colors, x, y, z, width, height, depth, theta_x, theta_y, theta_z);
	}

private:
	static Object generate(ObjectType objectType, unsigned int edges, const std::vector<std::array<std::array<char, 4>, 2>> &colors,
						   double x = 0, double y = 0, double z = 0,
						   double width = 1, double height = 1, double depth = 1,
						   double theta_x = 0, double theta_y = 0, double theta_z = 0)
	{
		std::vector<Prop> temp;
		temp.reserve(colors.size());
		for (auto color : colors)
		{
			Prop temp2;
			temp2.setOutlineColor(color[1][0], color[1][1], color[1][2], color[1][3]);
			temp2.setFillColor(color[0][0], color[0][1], color[0][2], color[0][3]);
			temp.push_back(temp2);
		}
		return generate(objectType, edges, temp, x, y, z, width, height, depth, theta_x, theta_y, theta_z);
	}

public:
	static Object Pyramid(unsigned int edges, const std::vector<Prop> &args,
						  double x = 0, double y = 0, double z = 0,
						  double width = 1, double height = 1, double depth = 1,
						  double theta_x = 0, double theta_y = 0, double theta_z = 0)
	{
		return generate(ObjectType::pyramid, edges, args, x, y, z, width, height, depth, theta_x, theta_y, theta_z);
	}

	static Object Prism(unsigned int edges, const std::vector<Prop> &args,
						double x = 0, double y = 0, double z = 0,
						double width = 1, double height = 1, double depth = 1,
						double theta_x = 0, double theta_y = 0, double theta_z = 0)
	{
		return generate(ObjectType::prism, edges, args, x, y, z, width, height, depth, theta_x, theta_y, theta_z);
	}

private:
	static Object generate(ObjectType objectType, unsigned int edges, const std::vector<Prop> &args,
						   double x = 0, double y = 0, double z = 0,
						   double width = 1, double height = 1, double depth = 1,
						   double theta_x = 0, double theta_y = 0, double theta_z = 0)
	{
		Object temp;
		switch (objectType)
		{
		case ObjectType::prism:
			temp.polygon.reserve(edges + 2);
			temp.coords.reserve(edges + 2);

			for (unsigned int vertex = 0; vertex < edges; vertex++)
			{
				double angle = (vertex / static_cast<double>(edges)) * 2 * pi;
				double curX = x + (cos(angle) + 1) / 2 * width;
				double curY = y + (sin(angle) + 1) / 2 * height;
				temp.addPoint(0, curX, curY, z);
				temp.addPoint(1, curX, curY, z + depth);
				temp.addPoint(vertex + 2, curX, curY, z);
				temp.addPoint(vertex + 2, curX, curY, z + depth);
				temp.addPoint(vertex + 2, x + (cos(angle + 1.0 / edges * 2 * pi) + 1) / 2 * width, y + (sin(angle + 1.0 / edges * 2 * pi) + 1) / 2 * height, z + depth);
				temp.addPoint(vertex + 2, x + (cos(angle + 1.0 / edges * 2 * pi) + 1) / 2 * width, y + (sin(angle + 1.0 / edges * 2 * pi) + 1) / 2 * height, z);
				temp.polygon[vertex + 2] = args[(vertex + 2) % args.size()];
			}
			temp.polygon[0] = args[0 % args.size()];
			temp.polygon[1] = args[1 % args.size()];
			break;
		case ObjectType::pyramid:
			temp.polygon.reserve(edges + 1);
			temp.coords.reserve(edges + 1);

			for (unsigned int vertex = 0; vertex < edges; vertex++)
			{
				double angle = (vertex / static_cast<double>(edges)) * 2 * pi;
				double curX = x + (cos(angle) + 1) / 2 * width;
				double curY = y + (sin(angle) + 1) / 2 * height;
				temp.addPoint(0, curX, curY, z);
				temp.addPoint(vertex + 1, curX, curY, z);
				temp.addPoint(vertex + 1, x + width / 2, y + height / 2, z + depth);
				temp.addPoint(vertex + 1, x + (cos(angle + 1.0 / edges * 2 * pi) + 1) / 2 * width, y + (sin(angle + 1.0 / edges * 2 * pi) + 1) / 2 * height, z);
				temp.polygon[vertex + 1] = args[(vertex + 1) % args.size()];
			}
			temp.polygon[0] = args[0 % args.size()];
			break;
		}

		temp.irotate(theta_x, theta_y, theta_z);
		return temp;
	}

public:
	static Object Cube(double x = 0, double y = 0, double z = 0,
					   double width = 1, double height = 1, double depth = 1,
					   double theta_x = 0, double theta_y = 0, double theta_z = 0)
	{
		Object temp;
		temp.polygon.reserve(6);
		temp.coords.reserve(6);

		temp.addPoint(0, x, y, z);
		temp.addPoint(0, x + width, y, z);
		temp.addPoint(0, x + width, y + height, z);
		temp.addPoint(0, x, y + height, z);
		temp.setColor(0, 255, 0, 0, 255); // Red

		temp.addPoint(1, x, y, z);
		temp.addPoint(1, x, y, z + depth);
		temp.addPoint(1, x, y + height, z + depth);
		temp.addPoint(1, x, y + height, z);
		temp.setColor(1, 0, 255, 0, 255); // Green

		temp.addPoint(2, x, y + height, z);
		temp.addPoint(2, x, y + height, z + depth);
		temp.addPoint(2, x + width, y + height, z + depth);
		temp.addPoint(2, x + width, y + height, z);
		temp.setColor(2, 0, 0, 255, 255); // Blue

		temp.addPoint(3, x + width, y + height, z);
		temp.addPoint(3, x + width, y + height, z + depth);
		temp.addPoint(3, x + width, y, z + depth);
		temp.addPoint(3, x + width, y, z);
		temp.setColor(3, 255, 255, 0, 255); // Yellow

		temp.addPoint(4, x + width, y, z);
		temp.addPoint(4, x, y, z);
		temp.addPoint(4, x, y, z + depth);
		temp.addPoint(4, x + width, y, z + depth);
		temp.setColor(4, 0, 255, 255, 255); // Cyan

		temp.addPoint(5, x + width, y, z + depth);
		temp.addPoint(5, x + width, y + height, z + depth);
		temp.addPoint(5, x, y + height, z + depth);
		temp.addPoint(5, x, y, z + depth);
		temp.setColor(5, 255, 0, 255, 255); // Magenta

		temp.irotate(theta_x, theta_y, theta_z);
		return temp;
	}

	static Object Tetrahedron(double x = 0, double y = 0, double z = 0,
							  double width = 1, double height = 1, double depth = 1,
							  double theta_x = 0, double theta_y = 0, double theta_z = 0)
	{
		Object temp;
		temp.polygon.reserve(4);
		temp.coords.reserve(4);

		temp.addPoint(0, x + width, y + height, z + depth);
		temp.addPoint(0, x + width, y, z);
		temp.addPoint(0, x, y + height, z);
		temp.setColor(0, 255, 0, 0, 255); // Red

		temp.addPoint(1, x + width, y + height, z + depth);
		temp.addPoint(1, x + width, y, z);
		temp.addPoint(1, x, y, z + depth);
		temp.setColor(1, 0, 255, 0, 255); // Green

		temp.addPoint(2, x + width, y + height, z + depth);
		temp.addPoint(2, x, y + height, z);
		temp.addPoint(2, x, y, z + depth);
		temp.setColor(2, 0, 0, 255, 255); // Blue

		temp.addPoint(3, x + width, y, z);
		temp.addPoint(3, x, y + height, z);
		temp.addPoint(3, x, y, z + depth);
		temp.setColor(3, 255, 255, 0, 255); // Yellow

		temp.irotate(theta_x, theta_y, theta_z);
		return temp;
	}

	static Object Octahedron(double x = 0, double y = 0, double z = 0,
							 double width = 1, double height = 1, double depth = 1,
							 double theta_x = 0, double theta_y = 0, double theta_z = 0)
	{
		Object temp;
		temp.polygon.reserve(8);
		temp.coords.reserve(8);

		temp.addPoint(0, x, y + height / 2, z + depth / 2);
		temp.addPoint(0, x + width / 2, y, z + depth / 2);
		temp.addPoint(0, x + width / 2, y + height / 2, z);
		temp.setColor(0, 255, 0, 0, 255); // Red

		temp.addPoint(1, x, y + height / 2, z + depth / 2);
		temp.addPoint(1, x + width / 2, y, z + depth / 2);
		temp.addPoint(1, x + width / 2, y + height / 2, z + depth);
		temp.setColor(1, 0, 255, 0, 255); // Green

		temp.addPoint(2, x + width, y + height / 2, z + depth / 2);
		temp.addPoint(2, x + width / 2, y, z + depth / 2);
		temp.addPoint(2, x + width / 2, y + height / 2, z);
		temp.setColor(2, 0, 0, 255, 255); // Blue

		temp.addPoint(3, x + width, y + height / 2, z + depth / 2);
		temp.addPoint(3, x + width / 2, y, z + depth / 2);
		temp.addPoint(3, x + width / 2, y + height / 2, z + depth);
		temp.setColor(3, 255, 255, 0, 255); // Yellow

		temp.addPoint(4, x, y + height / 2, z + depth / 2);
		temp.addPoint(4, x + width / 2, y + height, z + depth / 2);
		temp.addPoint(4, x + width / 2, y + height / 2, z);
		temp.setColor(4, 0, 255, 255, 255); // Cyan

		temp.addPoint(5, x, y + height / 2, z + depth / 2);
		temp.addPoint(5, x + width / 2, y + height, z + depth / 2);
		temp.addPoint(5, x + width / 2, y + height / 2, z + depth);
		temp.setColor(5, 255, 0, 255, 255); // Magenta

		temp.addPoint(6, x + width, y + height / 2, z + depth / 2);
		temp.addPoint(6, x + width / 2, y + height, z + depth / 2);
		temp.addPoint(6, x + width / 2, y + height / 2, z);
		temp.setColor(6, 0, 0, 0, 255); // Black

		temp.addPoint(7, x + width, y + height / 2, z + depth / 2);
		temp.addPoint(7, x + width / 2, y + height, z + depth / 2);
		temp.addPoint(7, x + width / 2, y + height / 2, z + depth);
		temp.setColor(7, 127, 127, 127, 255); // Gray

		temp.irotate(theta_x, theta_y, theta_z);
		return temp;
	}

	static Object Dodecahedron(double x = 0, double y = 0, double z = 0,
							   double width = 1, double height = 1, double depth = 1,
							   double theta_x = 0, double theta_y = 0, double theta_z = 0)
	{
		Object temp;
		temp.polygon.reserve(12);
		temp.coords.reserve(12);

		temp.addPoint(0, x + width * (3 - std::sqrt(5)) / 4, y + height * (3 - std::sqrt(5)) / 4, z + depth * (3 - std::sqrt(5)) / 4);
		temp.addPoint(0, x + width / 2, y, z + depth * (std::sqrt(5) - 1) / 4);
		temp.addPoint(0, x + width / 2, y, z + depth * (5 - std::sqrt(5)) / 4);
		temp.addPoint(0, x + width * (3 - std::sqrt(5)) / 4, y + height * (3 - std::sqrt(5)) / 4, z + depth * (1 + std::sqrt(5)) / 4);
		temp.addPoint(0, x, y + height * (std::sqrt(5) - 1) / 4, z + depth / 2);
		temp.setColor(0, 255, 0, 0, 255); // Red

		temp.addPoint(1, x + width * (1 + std::sqrt(5)) / 4, y + height * (3 - std::sqrt(5)) / 4, z + depth * (3 - std::sqrt(5)) / 4);
		temp.addPoint(1, x + width / 2, y, z + depth * (std::sqrt(5) - 1) / 4);
		temp.addPoint(1, x + width / 2, y, z + depth * (5 - std::sqrt(5)) / 4);
		temp.addPoint(1, x + width * (1 + std::sqrt(5)) / 4, y + height * (3 - std::sqrt(5)) / 4, z + depth * (1 + std::sqrt(5)) / 4);
		temp.addPoint(1, x + width, y + height * (std::sqrt(5) - 1) / 4, z + depth / 2);
		temp.setColor(1, 0, 255, 0, 255); // Green

		temp.addPoint(2, x + width * (3 - std::sqrt(5)) / 4, y + height * (3 - std::sqrt(5)) / 4, z + depth * (1 + std::sqrt(5)) / 4);
		temp.addPoint(2, x + width / 2, y, z + depth * (5 - std::sqrt(5)) / 4);
		temp.addPoint(2, x + width * (1 + std::sqrt(5)) / 4, y + height * (3 - std::sqrt(5)) / 4, z + depth * (1 + std::sqrt(5)) / 4);
		temp.addPoint(2, x + width * (5 - std::sqrt(5)) / 4, y + height / 2, z + depth);
		temp.addPoint(2, x + width * (std::sqrt(5) - 1) / 4, y + height / 2, z + depth);
		temp.setColor(2, 0, 0, 255, 255); // Blue

		temp.addPoint(3, x + width * (3 - std::sqrt(5)) / 4, y + height * (3 - std::sqrt(5)) / 4, z + depth * (3 - std::sqrt(5)) / 4);
		temp.addPoint(3, x + width / 2, y, z + depth * (std::sqrt(5) - 1) / 4);
		temp.addPoint(3, x + width * (1 + std::sqrt(5)) / 4, y + height * (3 - std::sqrt(5)) / 4, z + depth * (3 - std::sqrt(5)) / 4);
		temp.addPoint(3, x + width * (5 - std::sqrt(5)) / 4, y + height / 2, z);
		temp.addPoint(3, x + width * (std::sqrt(5) - 1) / 4, y + height / 2, z);
		temp.setColor(3, 255, 255, 0, 255); // Yellow

		temp.addPoint(4, x + width * (3 - std::sqrt(5)) / 4, y + height * (1 + std::sqrt(5)) / 4, z + depth * (3 - std::sqrt(5)) / 4);
		temp.addPoint(4, x + width / 2, y + height, z + depth * (std::sqrt(5) - 1) / 4);
		temp.addPoint(4, x + width / 2, y + height, z + depth * (5 - std::sqrt(5)) / 4);
		temp.addPoint(4, x + width * (3 - std::sqrt(5)) / 4, y + height * (1 + std::sqrt(5)) / 4, z + depth * (1 + std::sqrt(5)) / 4);
		temp.addPoint(4, x, y + height * (5 - std::sqrt(5)) / 4, z + depth / 2);
		temp.setColor(4, 0, 255, 255, 255); // Cyan

		temp.addPoint(5, x + width * (1 + std::sqrt(5)) / 4, y + height * (1 + std::sqrt(5)) / 4, z + depth * (3 - std::sqrt(5)) / 4);
		temp.addPoint(5, x + width / 2, y + height, z + depth * (std::sqrt(5) - 1) / 4);
		temp.addPoint(5, x + width / 2, y + height, z + depth * (5 - std::sqrt(5)) / 4);
		temp.addPoint(5, x + width * (1 + std::sqrt(5)) / 4, y + height * (1 + std::sqrt(5)) / 4, z + depth * (1 + std::sqrt(5)) / 4);
		temp.addPoint(5, x + width, y + height * (5 - std::sqrt(5)) / 4, z + depth / 2);
		temp.setColor(5, 255, 0, 255, 255); // Magenta

		temp.addPoint(6, x + width * (3 - std::sqrt(5)) / 4, y + height * (1 + std::sqrt(5)) / 4, z + depth * (1 + std::sqrt(5)) / 4);
		temp.addPoint(6, x + width / 2, y + height, z + depth * (5 - std::sqrt(5)) / 4);
		temp.addPoint(6, x + width * (1 + std::sqrt(5)) / 4, y + height * (1 + std::sqrt(5)) / 4, z + depth * (1 + std::sqrt(5)) / 4);
		temp.addPoint(6, x + width * (5 - std::sqrt(5)) / 4, y + height / 2, z + depth);
		temp.addPoint(6, x + width * (std::sqrt(5) - 1) / 4, y + height / 2, z + depth);
		temp.setColor(6, 0, 0, 0, 255); // Black

		temp.addPoint(7, x + width * (3 - std::sqrt(5)) / 4, y + height * (1 + std::sqrt(5)) / 4, z + depth * (3 - std::sqrt(5)) / 4);
		temp.addPoint(7, x + width / 2, y + height, z + depth * (std::sqrt(5) - 1) / 4);
		temp.addPoint(7, x + width * (1 + std::sqrt(5)) / 4, y + height * (1 + std::sqrt(5)) / 4, z + depth * (3 - std::sqrt(5)) / 4);
		temp.addPoint(7, x + width * (5 - std::sqrt(5)) / 4, y + height / 2, z);
		temp.addPoint(7, x + width * (std::sqrt(5) - 1) / 4, y + height / 2, z);
		temp.setColor(7, 127, 127, 127, 255); // Gray

		temp.addPoint(8, x + width * (1 + std::sqrt(5)) / 4, y + height * (3 - std::sqrt(5)) / 4, z + depth * (3 - std::sqrt(5)) / 4);
		temp.addPoint(8, x + width * (5 - std::sqrt(5)) / 4, y + height / 2, z);
		temp.addPoint(8, x + width * (1 + std::sqrt(5)) / 4, y + height * (1 + std::sqrt(5)) / 4, z + depth * (3 - std::sqrt(5)) / 4);
		temp.addPoint(8, x + width, y + height * (5 - std::sqrt(5)) / 4, z + depth / 2);
		temp.addPoint(8, x + width, y + height * (std::sqrt(5) - 1) / 4, z + depth / 2);
		temp.setColor(8, 127, 0, 0, 255); // Dark Red

		temp.addPoint(9, x + width * (1 + std::sqrt(5)) / 4, y + height * (3 - std::sqrt(5)) / 4, z + depth * (1 + std::sqrt(5)) / 4);
		temp.addPoint(9, x + width * (5 - std::sqrt(5)) / 4, y + height / 2, z + depth);
		temp.addPoint(9, x + width * (1 + std::sqrt(5)) / 4, y + height * (1 + std::sqrt(5)) / 4, z + depth * (1 + std::sqrt(5)) / 4);
		temp.addPoint(9, x + width, y + height * (5 - std::sqrt(5)) / 4, z + depth / 2);
		temp.addPoint(9, x + width, y + height * (std::sqrt(5) - 1) / 4, z + depth / 2);
		temp.setColor(9, 0, 127, 0, 255); // Dark Green

		temp.addPoint(10, x + width * (3 - std::sqrt(5)) / 4, y + height * (3 - std::sqrt(5)) / 4, z + depth * (3 - std::sqrt(5)) / 4);
		temp.addPoint(10, x + width * (std::sqrt(5) - 1) / 4, y + height / 2, z);
		temp.addPoint(10, x + width * (3 - std::sqrt(5)) / 4, y + height * (1 + std::sqrt(5)) / 4, z + depth * (3 - std::sqrt(5)) / 4);
		temp.addPoint(10, x, y + height * (5 - std::sqrt(5)) / 4, z + depth / 2);
		temp.addPoint(10, x, y + height * (std::sqrt(5) - 1) / 4, z + depth / 2);
		temp.setColor(10, 0, 0, 127, 255); // Dark Blue

		temp.addPoint(11, x + width * (3 - std::sqrt(5)) / 4, y + height * (3 - std::sqrt(5)) / 4, z + depth * (1 + std::sqrt(5)) / 4);
		temp.addPoint(11, x + width * (std::sqrt(5) - 1) / 4, y + height / 2, z + depth);
		temp.addPoint(11, x + width * (3 - std::sqrt(5)) / 4, y + height * (1 + std::sqrt(5)) / 4, z + depth * (1 + std::sqrt(5)) / 4);
		temp.addPoint(11, x, y + height * (5 - std::sqrt(5)) / 4, z + depth / 2);
		temp.addPoint(11, x, y + height * (std::sqrt(5) - 1) / 4, z + depth / 2);
		temp.setColor(11, 127, 127, 0, 255); // Dark Yellow

		temp.irotate(theta_x, theta_y, theta_z);
		return temp;
	}

	static Object Icosahedron(double x = 0, double y = 0, double z = 0,
							  double width = 1, double height = 1, double depth = 1,
							  double theta_x = 0, double theta_y = 0, double theta_z = 0)
	{
		Object temp;
		temp.polygon.reserve(20);
		temp.coords.reserve(20);

		temp.addPoint(0, x + width / 2, y, z + depth * (3 - std::sqrt(5)) / 4);
		temp.addPoint(0, x + width * (3 - std::sqrt(5)) / 4, y + height / 2, z);
		temp.addPoint(0, x + width * (1 + std::sqrt(5)) / 4, y + height / 2, z);
		temp.setColor(0, 255, 0, 0, 255); // Red

		temp.addPoint(1, x + width / 2, y + height, z + depth * (3 - std::sqrt(5)) / 4);
		temp.addPoint(1, x + width * (3 - std::sqrt(5)) / 4, y + height / 2, z);
		temp.addPoint(1, x + width * (1 + std::sqrt(5)) / 4, y + height / 2, z);
		temp.setColor(1, 0, 255, 0, 255); // Green

		temp.addPoint(2, x + width / 2, y + height, z + depth * (3 - std::sqrt(5)) / 4);
		temp.addPoint(2, x + width * (1 + std::sqrt(5)) / 4, y + height / 2, z);
		temp.addPoint(2, x + width, y + height * (1 + std::sqrt(5)) / 4, z + depth / 2);
		temp.setColor(2, 0, 0, 255, 255); // Blue

		temp.addPoint(3, x + width / 2, y, z + depth * (3 - std::sqrt(5)) / 4);
		temp.addPoint(3, x + width * (1 + std::sqrt(5)) / 4, y + height / 2, z);
		temp.addPoint(3, x + width, y + height * (3 - std::sqrt(5)) / 4, z + depth / 2);
		temp.setColor(3, 255, 255, 0, 255); // Yellow

		temp.addPoint(4, x + width * (1 + std::sqrt(5)) / 4, y + height / 2, z);
		temp.addPoint(4, x + width, y + height * (1 + std::sqrt(5)) / 4, z + depth / 2);
		temp.addPoint(4, x + width, y + height * (3 - std::sqrt(5)) / 4, z + depth / 2);
		temp.setColor(4, 0, 255, 255, 255); // Cyan

		temp.addPoint(5, x + width / 2, y + height, z + depth * (1 + std::sqrt(5)) / 4);
		temp.addPoint(5, x + width / 2, y + height, z + depth * (3 - std::sqrt(5)) / 4);
		temp.addPoint(5, x + width, y + height * (1 + std::sqrt(5)) / 4, z + depth / 2);
		temp.setColor(5, 255, 0, 255, 255); // Magenta

		temp.addPoint(6, x + width / 2, y + height, z + depth * (1 + std::sqrt(5)) / 4);
		temp.addPoint(6, x + width / 2, y + height, z + depth * (3 - std::sqrt(5)) / 4);
		temp.addPoint(6, x, y + height * (1 + std::sqrt(5)) / 4, z + depth / 2);
		temp.setColor(6, 0, 0, 0, 255); // Black

		temp.addPoint(7, x + width * (1 + std::sqrt(5)) / 4, y + height / 2, z + depth);
		temp.addPoint(7, x + width, y + height * (1 + std::sqrt(5)) / 4, z + depth / 2);
		temp.addPoint(7, x + width, y + height * (3 - std::sqrt(5)) / 4, z + depth / 2);
		temp.setColor(7, 127, 127, 127, 255); // Gray

		temp.addPoint(8, x + width / 2, y, z + depth * (1 + std::sqrt(5)) / 4);
		temp.addPoint(8, x + width * (3 - std::sqrt(5)) / 4, y + height / 2, z + depth);
		temp.addPoint(8, x + width * (1 + std::sqrt(5)) / 4, y + height / 2, z + depth);
		temp.setColor(8, 127, 0, 0, 255); // Dark Red

		temp.addPoint(9, x + width / 2, y + height, z + depth * (1 + std::sqrt(5)) / 4);
		temp.addPoint(9, x + width * (3 - std::sqrt(5)) / 4, y + height / 2, z + depth);
		temp.addPoint(9, x + width * (1 + std::sqrt(5)) / 4, y + height / 2, z + depth);
		temp.setColor(9, 0, 127, 0, 255); // Dark Green

		temp.addPoint(10, x + width, y + height * (1 + std::sqrt(5)) / 4, z + depth / 2);
		temp.addPoint(10, x + width / 2, y + height, z + depth * (1 + std::sqrt(5)) / 4);
		temp.addPoint(10, x + width * (1 + std::sqrt(5)) / 4, y + height / 2, z + depth);
		temp.setColor(10, 0, 0, 127, 255); // Dark Blue

		temp.addPoint(11, x + width / 2, y, z + depth * (1 + std::sqrt(5)) / 4);
		temp.addPoint(11, x + width * (1 + std::sqrt(5)) / 4, y + height / 2, z + depth);
		temp.addPoint(11, x + width, y + height * (3 - std::sqrt(5)) / 4, z + depth / 2);
		temp.setColor(11, 127, 127, 0, 255); // Dark Yellow

		temp.addPoint(12, x + width / 2, y, z + depth * (1 + std::sqrt(5)) / 4);
		temp.addPoint(12, x + width / 2, y, z + depth * (3 - std::sqrt(5)) / 4);
		temp.addPoint(12, x + width, y + height * (3 - std::sqrt(5)) / 4, z + depth / 2);
		temp.setColor(12, 0, 127, 127, 255); // Darl Cyan

		temp.addPoint(13, x + width / 2, y, z + depth * (1 + std::sqrt(5)) / 4);
		temp.addPoint(13, x + width / 2, y, z + depth * (3 - std::sqrt(5)) / 4);
		temp.addPoint(13, x, y + height * (3 - std::sqrt(5)) / 4, z + depth / 2);
		temp.setColor(13, 127, 0, 127, 255); // Dark Magenta

		temp.addPoint(14, x + width / 2, y + height, z + depth * (3 - std::sqrt(5)) / 4);
		temp.addPoint(14, x + width * (3 - std::sqrt(5)) / 4, y + height / 2, z);
		temp.addPoint(14, x, y + height * (1 + std::sqrt(5)) / 4, z + depth / 2);
		temp.setColor(14, 255, 127, 127, 255); // Light Red

		temp.addPoint(15, x + width / 2, y, z + depth * (3 - std::sqrt(5)) / 4);
		temp.addPoint(15, x + width * (3 - std::sqrt(5)) / 4, y + height / 2, z);
		temp.addPoint(15, x, y + height * (3 - std::sqrt(5)) / 4, z + depth / 2);
		temp.setColor(15, 127, 255, 127, 255); // Light Green

		temp.addPoint(16, x + width * (3 - std::sqrt(5)) / 4, y + height / 2, z);
		temp.addPoint(16, x, y + height * (1 + std::sqrt(5)) / 4, z + depth / 2);
		temp.addPoint(16, x, y + height * (3 - std::sqrt(5)) / 4, z + depth / 2);
		temp.setColor(16, 127, 127, 255, 255); // Light Blue

		temp.addPoint(17, x, y + height * (1 + std::sqrt(5)) / 4, z + depth / 2);
		temp.addPoint(17, x + width / 2, y + height, z + depth * (1 + std::sqrt(5)) / 4);
		temp.addPoint(17, x + width * (3 - std::sqrt(5)) / 4, y + height / 2, z + depth);
		temp.setColor(17, 255, 255, 127, 255); // Light Yellow

		temp.addPoint(18, x + width / 2, y, z + depth * (1 + std::sqrt(5)) / 4);
		temp.addPoint(18, x + width * (3 - std::sqrt(5)) / 4, y + height / 2, z + depth);
		temp.addPoint(18, x, y + height * (3 - std::sqrt(5)) / 4, z + depth / 2);
		temp.setColor(18, 127, 255, 255, 255); // Light Cyan

		temp.addPoint(19, x + width * (3 - std::sqrt(5)) / 4, y + height / 2, z + depth);
		temp.addPoint(19, x, y + height * (1 + std::sqrt(5)) / 4, z + depth / 2);
		temp.addPoint(19, x, y + height * (3 - std::sqrt(5)) / 4, z + depth / 2);
		temp.setColor(19, 255, 127, 255, 255); // Light Magenta

		temp.irotate(theta_x, theta_y, theta_z);
		return temp;
	}

private:
	std::vector<std::vector<std::array<double, 3>>> coords;
	std::vector<Prop> polygon;
	double center_x{0};
	double center_y{0};
	double center_z{0};
	double theta_x{0};
	double theta_y{0};
	double theta_z{0};

public:
	bool borderless = false;
	bool wireframe = false;

	Object()
	{
	}

	Object(std::vector<std::vector<std::array<double, 3>>> coords)
	{
		this->coords = coords;
		autoCenter();
	}

	Object(std::vector<std::vector<std::array<double, 3>>> coords,
		   std::array<double, 3> axis)
	{
		this->coords = coords;
		center_x = axis[0];
		center_y = axis[1];
		center_z = axis[2];
	}

	Object(std::vector<std::vector<std::array<double, 3>>> coords,
		   double x_axis, double y_axis, double z_axis)
	{
		this->coords = coords;
		center_x = x_axis;
		center_y = y_axis;
		center_z = z_axis;
	}

	void setPoint(int face, int index, const std::array<double, 3> &point)
	{
		setPoint(face, index, point[0], point[1], point[2]);
	}

	void setPoint(int face, int index, double x, double y, double z)
	{
		coords.reserve(face + 1);
		polygon.reserve(face + 1);
		while (face >= coords.size())
		{
			coords.push_back(std::vector<std::array<double, 3>>{});
			polygon.push_back(Prop());
		}
		coords[face].reserve(index + 1);
		while (index >= coords[face].size())
			coords[face].push_back(std::array<double, 3>{0, 0, 0});
		coords[face][index][0] = x;
		coords[face][index][1] = y;
		coords[face][index][2] = z;
		autoCenter();
	}

	void addPoint(int face, const std::array<double, 2> &point)
	{
		addPoint(face, point[0], point[1], 0);
	}

	void addPoint(int face, const std::array<double, 3> &point)
	{
		addPoint(face, point[0], point[1], point[2]);
	}

	void addPoint(int face, double x, double y, double z = 0)
	{
		coords.reserve(face + 1);
		polygon.reserve(face + 1);
		while (face >= coords.size())
		{
			coords.push_back(std::vector<std::array<double, 3>>{});
			polygon.push_back(Prop());
		}
		coords[face].push_back(std::array<double, 3>{x, y, z});
		autoCenter();
	}

	void setColor(int face, const std::array<char, 3> &rgb)
	{
		setColor(face, rgb[0], rgb[1], rgb[2]);
	}

	void setColor(int face, const std::array<char, 4> &rgba)
	{
		setColor(face, rgba[0], rgba[1], rgba[2], rgba[3]);
	}

	void setColor(int face, char r, char g, char b, char a = 255)
	{
		polygon[face].setFillColor(r, g, b, a);
	}

	void setOutlineColor(int face, const std::array<char, 3> &rgb)
	{
		setOutlineColor(face, rgb[0], rgb[1], rgb[2]);
	}

	void setOutlineColor(int face, const std::array<char, 4> &rgba)
	{
		setOutlineColor(face, rgba[0], rgba[1], rgba[2], rgba[3]);
	}

	void setOutlineColor(int face, char r, char g, char b, char a = 255)
	{
		polygon[face].setOutlineColor(r, g, b, a);
	}

	void setOutlineThickness(int face, int thick = 1)
	{
		polygon[face].setOutlineThickness(thick);
	}

	void setPosition(const std::array<double, 2> &point)
	{
		setPosition(point[0], point[1], 0);
	}

	void setPosition(const std::array<double, 3> &point)
	{
		setPosition(point[0], point[1], point[2]);
	}

	void setPosition(double x = 0, double y = 0, double z = 0)
	{
		for (int face{0}; face < coords.size(); face++)
			for (int point{0}; point < coords[face].size(); point++)
			{
				coords[face][point][0] += (x - center_x);
				coords[face][point][1] += (y - center_y);
				coords[face][point][2] += (z - center_z);
			}
	}

	void movePosition(const std::array<double, 2> &point)
	{
		movePosition(point[0], point[1], 0);
	}

	void movePosition(const std::array<double, 3> &point)
	{
		movePosition(point[0], point[1], point[2]);
	}

	void movePosition(double x = 0, double y = 0, double z = 0)
	{
		for (int face{0}; face < coords.size(); face++)
			for (int point{0}; point < coords[face].size(); point++)
			{
				coords[face][point][0] += x;
				coords[face][point][1] += y;
				coords[face][point][2] += z;
			}
	}

	void autoCenter()
	{
		center_x = 0;
		center_y = 0;
		center_z = 0;
		int vertices{0};
		for (auto face : coords)
			for (auto i : face)
			{
				center_x += i[0];
				center_y += i[1];
				center_z += i[2];
				vertices++;
			}
		center_x /= vertices;
		center_y /= vertices;
		center_z /= vertices;
	}

	void setCenter(const std::array<double, 2> &point)
	{
		setCenter(point[0], point[1], 0);
	}

	void setCenter(const std::array<double, 3> &point)
	{
		setCenter(point[0], point[1], point[2]);
	}

	void setCenter(double x = 0, double y = 0, double z = 0)
	{
		center_x = x;
		center_y = y;
		center_z = z;
	}

	static std::array<double, 3> joinRotations(double theta1_x, double theta1_y, double theta1_z,
											   double theta2_x, double theta2_y, double theta2_z)
	{
		return joinRotations(std::array<double, 3>{theta1_x, theta1_y, theta1_z},
							 std::array<double, 3>{theta2_x, theta2_y, theta2_z});
	}

	static std::array<double, 3> joinRotations(const std::array<double, 3> &theta1,
											   double theta2_x, double theta2_y, double theta2_z)
	{
		return joinRotations(theta1, std::array<double, 3>{theta2_x, theta2_y, theta2_z});
	}

	static std::array<double, 3> joinRotations(const std::array<double, 3> &theta1,
											   const std::array<double, 3> &theta2)
	{
		double c1 = cos(theta1[0] * pi / 180);
		double c2 = cos(theta1[1] * pi / 180);
		double c3 = cos(theta1[2] * pi / 180);
		double s1 = sin(theta1[0] * pi / 180);
		double s2 = sin(theta1[1] * pi / 180);
		double s3 = sin(theta1[2] * pi / 180);
		std::array<std::array<double, 3>, 3> Rx1{
			std::array<double, 3>{1, 0, 0},
			std::array<double, 3>{0, c1, -s1},
			std::array<double, 3>{0, s1, c1}};
		std::array<std::array<double, 3>, 3> Ry1{
			std::array<double, 3>{c2, 0, s2},
			std::array<double, 3>{0, 1, 0},
			std::array<double, 3>{-s2, 0, c2}};
		std::array<std::array<double, 3>, 3> Rz1{
			std::array<double, 3>{c3, -s3, 0},
			std::array<double, 3>{s3, c3, 0},
			std::array<double, 3>{0, 0, 1}};
		std::array<std::array<double, 3>, 3> R1 = multiplyMatrices(multiplyMatrices(Rz1, Ry1), Rx1);
		double c4 = cos(theta2[0] * pi / 180);
		double c5 = cos(theta2[1] * pi / 180);
		double c6 = cos(theta2[2] * pi / 180);
		double s4 = sin(theta2[0] * pi / 180);
		double s5 = sin(theta2[1] * pi / 180);
		double s6 = sin(theta2[2] * pi / 180);
		std::array<std::array<double, 3>, 3> Rx2{
			std::array<double, 3>{1, 0, 0},
			std::array<double, 3>{0, c4, -s4},
			std::array<double, 3>{0, s4, c4}};
		std::array<std::array<double, 3>, 3> Ry2{
			std::array<double, 3>{c5, 0, s5},
			std::array<double, 3>{0, 1, 0},
			std::array<double, 3>{-s5, 0, c5}};
		std::array<std::array<double, 3>, 3> Rz2{
			std::array<double, 3>{c6, -s6, 0},
			std::array<double, 3>{s6, c6, 0},
			std::array<double, 3>{0, 0, 1}};
		std::array<std::array<double, 3>, 3> R2 = multiplyMatrices(multiplyMatrices(Rz2, Ry2), Rx2);
		std::array<std::array<double, 3>, 3> R3 = multiplyMatrices(R2, R1);
		double theta_x = atan2(R3[2][1], R3[2][2]);
		double theta_y = atan2(-R3[2][0], sqrt(R3[2][1] * R3[2][1] + R3[2][2] * R3[2][2]));
		double theta_z = atan2(R3[1][0], R3[0][0]);

		return std::array<double, 3>{fmod(theta_x * 180 / pi + 360, 360),
									 fmod(theta_y * 180 / pi + 360, 360),
									 fmod(theta_z * 180 / pi + 360, 360)};
	}

	static std::array<std::array<double, 3>, 3> multiplyMatrices(const std::array<std::array<double, 3>, 3> &A,
																 const std::array<std::array<double, 3>, 3> &B)
	{
		std::array<std::array<double, 3>, 3> C;
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
			{
				C[i][j] = 0;
				for (int k = 0; k < 3; k++)
					C[i][j] += A[i][k] * B[k][j];
			}
		return C;
	}

	void rotate(const std::array<double, 3> &theta)
	{
		rotate(theta[0], theta[1], theta[2]);
	}

	void rotate(double theta_x = 0, double theta_y = 0, double theta_z = 0)
	{
		std::array<double, 3> temp = joinRotations(this->theta_x, this->theta_y, this->theta_z, theta_x, theta_y, theta_z);
		this->theta_x = std::fmod(temp[0] + 360, 360);
		this->theta_y = std::fmod(temp[1] + 360, 360);
		this->theta_z = std::fmod(temp[2] + 360, 360);
	}

	void irotate(const std::array<double, 3> &theta)
	{
		irotate(theta[0], theta[1], theta[2]);
	}

	void irotate(double theta_x = 0, double theta_y = 0, double theta_z = 0)
	{
		if (!(theta_x || theta_y || theta_z))
			return;
		std::array<double, 3> temp;
		for (int face{0}; face < coords.size(); face++)
			for (int point{0}; point < coords[face].size(); point++)
			{
				coords[face][point][0] -= center_x;
				coords[face][point][1] -= center_y;
				coords[face][point][2] -= center_z;
				temp = rotatePoint(coords[face][point], theta_x, theta_y, theta_z);
				coords[face][point][0] = temp[0] + center_x;
				coords[face][point][1] = temp[1] + center_y;
				coords[face][point][2] = temp[2] + center_z;
			}
	}

	void draw(SDL_Renderer *window) const
	{
		std::vector<bool> indeces(coords.size(), false);
		std::array<double, 4> minmax{0, 0, 0, 0};
		std::array<double, 3> point1, point2;
		if (!wireframe)
		{
			double temp;
			bool first = true;
			for (auto face : coords)
				for (auto point : face)
				{
					temp = rotatePoint(point[0] - center_x, point[1] - center_y, point[2] - center_z, theta_x, theta_y, theta_z)[0] + center_x;
					if (first)
					{
						minmax[0] = temp;
						minmax[2] = temp;
					}
					else if (temp < minmax[0])
						minmax[0] = temp;
					else if (temp > minmax[2])
						minmax[2] = temp;
					temp = rotatePoint(point[0] - center_x, point[1] - center_y, point[2] - center_z, theta_x, theta_y, theta_z)[1] + center_y;
					if (first)
					{
						minmax[1] = temp;
						minmax[3] = temp;
					}
					else if (temp < minmax[1])
						minmax[1] = temp;
					else if (temp > minmax[3])
						minmax[3] = temp;
					first = false;
				}
		}
		for (int loop{0}; loop < coords.size(); loop++)
		{
			int current{-1};
			for (int index{0}; index < coords.size(); index++)
				if (((current != -1) ? (
										   getDepth(coords[index], center_x, center_y, center_z, theta_x, theta_y, theta_z) >=
										   getDepth(coords[current], center_x, center_y, center_z, theta_x, theta_y, theta_z))
									 : true) &&
					!indeces[index])
					current = index;
			if (!borderless)
			{
				SDL_SetRenderDrawColor(window, polygon[current].fill[0], polygon[current].outline[1],
									   polygon[current].outline[2], polygon[current].outline[3]);
				for (int index{0}; index < coords[current].size(); index++)
				{
					point1 = coords[current][index];
					point2 = coords[current][index == coords[current].size() - 1 ? 0 : index + 1];
					if (theta_x || theta_y || theta_z)
					{
						point1[0] -= center_x;
						point1[1] -= center_y;
						point1[2] -= center_z;
						point1 = rotatePoint(point1, theta_x, theta_y, theta_z);
						point1[0] += center_x;
						point1[1] += center_y;
						point1[2] += center_z;

						point2[0] -= center_x;
						point2[1] -= center_y;
						point2[2] -= center_z;
						point2 = rotatePoint(point2, theta_x, theta_y, theta_z);
						point2[0] += center_x;
						point2[1] += center_y;
						point2[2] += center_z;
					}
					SDL_RenderDrawLine(window, point1[0], point1[1], point2[0], point2[1]);
				}
			}
			if (!wireframe)
			{
				SDL_SetRenderDrawColor(window, polygon[current].fill[0], polygon[current].fill[1],
									   polygon[current].fill[2], polygon[current].fill[3]);
				for (double x{minmax[0]}; x < minmax[2]; x++)
					for (double y{minmax[1]}; y < minmax[3]; y++)
						if (isInsidePolygon(coords[current], center_x, center_y, center_z, theta_x, theta_y, theta_z, x, y))
							SDL_RenderDrawPoint(window, x, y);
			}
			indeces[current] = true;
		}
	}
};

int main(int argc, char *argv[])
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		SDL_Log("SDL initialization failed: %s", SDL_GetError());
		return 1;
	}

	SDL_Window *window = SDL_CreateWindow("SDL2 Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 500, 500, SDL_WINDOW_SHOWN);
	if (!window)
	{
		SDL_Log("Window creation failed: %s", SDL_GetError());
		SDL_Quit();
		return 1;
	}

	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (!renderer)
	{
		SDL_Log("Renderer creation failed: %s", SDL_GetError());
		SDL_DestroyWindow(window);
		SDL_Quit();
		return 1;
	}

	SDL_EventState(SDL_MOUSEMOTION, SDL_ENABLE);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

	Object polygons[] = {
		Object::Cube(200, 200, 0, 50, 50, 50),
		Object::Pyramid(6, 50, 50, 0, 50, 50, 50),
		Object::Prism(5, 400, 50, 0, 50, 50, 50),
		Object::Pyramid(6,
						std::vector<std::array<char, 4>>{
							{(char)255, 0, 0, (char)255},
							{0, 0, (char)255, (char)255}},
						400, 400, 0, 50, 50, 50),
		Object::Icosahedron(50, 400, 0, 50, 50, 50)};
	polygons[2].wireframe = true;

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);
	for (Object polygon : polygons)
		polygon.draw(renderer);
	SDL_RenderPresent(renderer);

	bool quit = false;
	SDL_Event event;
	int mouseX = 0;
	int mouseY = 0;

	while (!quit)
	{
		while (SDL_PollEvent(&event) != 0)
		{
			switch (event.type)
			{
			case SDL_QUIT:
				quit = true;
				break;
			case SDL_MOUSEMOTION:
				for (Object &polygon : polygons)
					polygon.irotate(-mouseY + event.motion.y, mouseX - event.motion.x, 0);
				mouseX = event.motion.x;
				mouseY = event.motion.y;
				break;
			case SDL_MOUSEWHEEL:
				for (Object &polygon : polygons)
					polygon.irotate(0, 0, -10 * event.wheel.y);
				break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					quit = true;
					break;
				case SDLK_UP:
				case SDLK_w:
					for (Object &polygon : polygons)
						polygon.irotate(-20, 0, 0);
					break;
				case SDLK_DOWN:
				case SDLK_s:
					for (Object &polygon : polygons)
						polygon.irotate(20, 0, 0);
					break;
				case SDLK_LEFT:
				case SDLK_a:
					for (Object &polygon : polygons)
						polygon.irotate(0, 20, 0);
					break;
				case SDLK_RIGHT:
				case SDLK_d:
					for (Object &polygon : polygons)
						polygon.irotate(0, -20, 0);
					break;
				case SDLK_LSHIFT:
				case SDLK_RSHIFT:
					for (Object &polygon : polygons)
						polygon.irotate(0, 0, -20);
					break;
				case SDLK_SPACE:
					for (Object &polygon : polygons)
						polygon.irotate(0, 0, 20);
					break;
				default:
					break;
				}
				break;
			default:
				break;
			}
			if (!quit)
			{
				SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
				SDL_RenderClear(renderer);
				for (Object polygon : polygons)
					polygon.draw(renderer);
				SDL_RenderPresent(renderer);
			}
		}
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit();

	return 0;
}
