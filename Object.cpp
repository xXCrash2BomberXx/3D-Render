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

		void setFillColor(char r, char g, char b, char a)
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
		void setOutlineColor(char r, char g, char b, char a)
		{
			useOutline = true;
			outline[0] = r;
			outline[1] = g;
			outline[2] = b;
			outline[3] = a;
		}

		void setOutlineThickness(int thick)
		{
			thickness = thick;
		}
	};

	static bool isInsidePolygon(const std::vector<std::array<double, 3>> &polygon, double x, double y)
	{
		int n = polygon.size();
		int cnt = 0;

		for (int i = 0; i < n; i++)
		{
			const std::array<double, 3> &p1 = polygon[i];
			const std::array<double, 3> &p2 = polygon[(i + 1) % n];

			if ((p1[1] <= y && p2[1] <= y) || (p1[1] > y && p2[1] > y))
				continue;

			double xIntersection = (p1[0] * (p2[1] - y) + p2[0] * (y - p1[1])) / (p2[1] - p1[1]);

			if (xIntersection > x)
				cnt++;
		}

		return cnt % 2 == 1;
	}

	static double getDepth(const std::vector<std::array<double, 3>> &face)
	{
		double avg{0};
		for (auto i : face)
			avg += i[2];
		return avg / face.size();
	}

	static void rotatePoint(std::array<double, 3> &vec, double theta_x, double theta_y, double theta_z)
	{
		double x{
			vec[0] * cos(theta_z * pi / 180) * cos(theta_y * pi / 180) +
			vec[1] * cos(theta_z * pi / 180) * sin(theta_y * pi / 180) * sin(theta_x * pi / 180) -
			vec[1] * sin(theta_z * pi / 180) * cos(theta_x * pi / 180) +
			vec[2] * cos(theta_z * pi / 180) * sin(theta_y * pi / 180) * cos(theta_x * pi / 180) +
			vec[2] * sin(theta_z * pi / 180) * sin(theta_x * pi / 180)};
		double y{
			vec[0] * sin(theta_z * pi / 180) * cos(theta_y * pi / 180) +
			vec[1] * sin(theta_z * pi / 180) * sin(theta_y * pi / 180) * sin(theta_x * pi / 180) +
			vec[1] * cos(theta_z * pi / 180) * cos(theta_x * pi / 180) +
			vec[2] * sin(theta_z * pi / 180) * sin(theta_y * pi / 180) * cos(theta_x * pi / 180) -
			vec[2] * cos(theta_z * pi / 180) * sin(theta_x * pi / 180)};
		double z{
			-vec[0] * sin(theta_y * pi / 180) +
			vec[1] * cos(theta_y * pi / 180) * sin(theta_x * pi / 180) +
			vec[2] * cos(theta_y * pi / 180) * cos(theta_x * pi / 180)};
		vec[0] = x;
		vec[1] = y;
		vec[2] = z;
	}

public:
	enum ObjectType
	{
		Pyramid,
		Prism
	};

	static Object pyramid(unsigned int edges,
						  double x = 0, double y = 0, double z = 0, double width = 1, double height = 1, double depth = 1)
	{
		return generate(ObjectType::Pyramid, edges, x, y, z, width, height, depth);
	}

	static Object prism(unsigned int edges,
						double x = 0, double y = 0, double z = 0, double width = 1, double height = 1, double depth = 1)
	{
		return generate(ObjectType::Prism, edges, x, y, z, width, height, depth);
	}

	static Object generate(ObjectType objectType, unsigned int edges,
						   double x = 0, double y = 0, double z = 0, double width = 1, double height = 1, double depth = 1)
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
		return generate(objectType, edges, args, x, y, z, width, height, depth);
	}

	static Object pyramid(unsigned int edges, const std::vector<std::array<char, 4>> &fill,
						  double x = 0, double y = 0, double z = 0, double width = 1, double height = 1, double depth = 1)
	{
		return generate(ObjectType::Pyramid, edges, fill, x, y, z, width, height, depth);
	}

	static Object prism(unsigned int edges, const std::vector<std::array<char, 4>> &fill,
						double x = 0, double y = 0, double z = 0, double width = 1, double height = 1, double depth = 1)
	{
		return generate(ObjectType::Prism, edges, fill, x, y, z, width, height, depth);
	}

	static Object generate(ObjectType objectType, unsigned int edges, const std::vector<std::array<char, 4>> &fill,
						   double x = 0, double y = 0, double z = 0, double width = 1, double height = 1, double depth = 1)
	{
		std::vector<Prop> temp;
		temp.reserve(fill.size());
		for (auto color : fill)
		{
			Prop temp2;
			temp2.setFillColor(color[0], color[1], color[2], color[3]);
			temp.push_back(temp2);
		}
		return generate(objectType, edges, temp, x, y, z, width, height, depth);
	}

	static Object pyramid(unsigned int edges, const std::vector<std::array<std::array<char, 4>, 2>> &colors,
						  double x = 0, double y = 0, double z = 0, double width = 1, double height = 1, double depth = 1)
	{
		return generate(ObjectType::Pyramid, edges, colors, x, y, z, width, height, depth);
	}

	static Object prism(unsigned int edges, const std::vector<std::array<std::array<char, 4>, 2>> &colors,
						double x = 0, double y = 0, double z = 0, double width = 1, double height = 1, double depth = 1)
	{
		return generate(ObjectType::Prism, edges, colors, x, y, z, width, height, depth);
	}

	static Object generate(ObjectType objectType, unsigned int edges, const std::vector<std::array<std::array<char, 4>, 2>> &colors,
						   double x = 0, double y = 0, double z = 0, double width = 1, double height = 1, double depth = 1)
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
		return generate(objectType, edges, temp, x, y, z, width, height, depth);
	}

	static Object pyramid(unsigned int edges, const std::vector<Prop> &args,
						  double x = 0, double y = 0, double z = 0, double width = 1, double height = 1, double depth = 1)
	{
		return generate(ObjectType::Pyramid, edges, args, x, y, z, width, height, depth);
	}

	static Object prism(unsigned int edges, const std::vector<Prop> &args,
						double x = 0, double y = 0, double z = 0, double width = 1, double height = 1, double depth = 1)
	{
		return generate(ObjectType::Prism, edges, args, x, y, z, width, height, depth);
	}

	static Object generate(ObjectType objectType, unsigned int edges, const std::vector<Prop> &args,
						   double x = 0, double y = 0, double z = 0, double width = 1, double height = 1, double depth = 1)
	{
		Object temp;
		switch (objectType)
		{
		case ObjectType::Prism:
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
		case ObjectType::Pyramid:
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

		return temp;
	}

	static Object cube(double x = 0, double y = 0, double z = 0, double width = 1, double height = 1, double depth = 1)
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

		return temp;
	}

	static Object tetrahedron(double x = 0, double y = 0, double z = 0, double width = 1, double height = 1, double depth = 1)
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

		return temp;
	}

	static Object octahedron(double x = 0, double y = 0, double z = 0, double width = 1, double height = 1, double depth = 1)
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

		return temp;
	}

	static Object dodecahedron(double x = 0, double y = 0, double z = 0, double width = 1, double height = 1, double depth = 1)
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

		return temp;
	}

	static Object icosahedron(double x = 0, double y = 0, double z = 0, double width = 1, double height = 1, double depth = 1)
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

		return temp;
	}

private:
	std::vector<std::vector<std::array<double, 3>>> coords;
	std::vector<Prop> polygon;
	double center_x{0};
	double center_y{0};
	double center_z{0};

public:
	bool borderless = false;
	bool wireframe = false;

	Object()
	{
	}

	Object(std::vector<std::vector<std::array<double, 3>>> coords, double x_axis, double y_axis, double z_axis)
	{
		this->coords = coords;
		center_x = x_axis;
		center_y = y_axis;
		center_z = z_axis;
	}

	void setPoint(int face, int index, double x, double y, double z, double a = 255)
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
		coords[face][index][3] = a;
		autoCenter();
	}

	void addPoint(int face, double x, double y, double z)
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

	void setColor(int face, char r, char g, char b, char a = 255)
	{
		polygon[face].setFillColor(r, g, b, a);
	}

	void setOutlineColor(int face, char r, char g, char b, char a)
	{
		polygon[face].setOutlineColor(r, g, b, a);
	}

	void setOutlineThickness(int face, int thick = 1)
	{
		polygon[face].setOutlineThickness(thick);
	}

	void setPosition(float x = 0, float y = 0, float z = 0)
	{
		for (int face{0}; face < coords.size(); face++)
			for (int point{0}; point < coords[face].size(); point++)
			{
				coords[face][point][0] += (x - center_x);
				coords[face][point][1] += (y - center_y);
				coords[face][point][2] += (z - center_z);
			}
	}

	void movePosition(float x = 0, float y = 0, float z = 0)
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

	void setCenter(double x, double y, double z)
	{
		center_x = x;
		center_y = y;
		center_z = z;
	}

	void rotate(double theta_x = 0, double theta_y = 0, double theta_z = 0)
	{
		for (int face{0}; face < coords.size(); face++)
			for (int point{0}; point < coords[face].size(); point++)
			{
				coords[face][point][0] -= center_x;
				coords[face][point][1] -= center_y;
				coords[face][point][2] -= center_z;
				rotatePoint(coords[face][point], theta_x, theta_y, theta_z);
				coords[face][point][0] += center_x;
				coords[face][point][1] += center_y;
				coords[face][point][2] += center_z;
			}
	}
	
	void draw(SDL_Renderer *window) const
	{
		std::vector<bool> indeces(coords.size(), false);
		std::array<double, 4> minmax = {coords[0][0][0], coords[0][0][1], coords[0][0][0], coords[0][0][1]};
		if (!wireframe)
			for (auto face : coords)
				for (auto point : face)
				{
					if (point[0] < minmax[0])
						minmax[0] = point[0];
					else if (point[0] > minmax[2])
						minmax[2] = point[0];
					if (point[1] < minmax[1])
						minmax[1] = point[1];
					else if (point[1] > minmax[3])
						minmax[3] = point[1];
				}
		for (int loop{0}; loop < coords.size(); loop++)
		{
			int current{-1};
			for (int index{0}; index < coords.size(); index++)
				if (((current != -1) ? (getDepth(coords[index]) >= getDepth(coords[current])) : true) && !indeces[index])
					current = index;
			if (!borderless)
			{
				SDL_SetRenderDrawColor(window, polygon[current].fill[0], polygon[current].outline[1],
									   polygon[current].outline[2], polygon[current].outline[3]);
				for (int index{0}; index < coords[current].size(); index++)
					if (index == coords[current].size() - 1)
						SDL_RenderDrawLine(window, coords[current][index][0], coords[current][index][1],
										   coords[current][0][0], coords[current][0][1]);
					else
						SDL_RenderDrawLine(window, coords[current][index][0], coords[current][index][1],
										   coords[current][index + 1][0], coords[current][index + 1][1]);
			}
			if (!wireframe)
			{
				SDL_SetRenderDrawColor(window, polygon[current].fill[0], polygon[current].fill[1],
									   polygon[current].fill[2], polygon[current].fill[3]);
				for (double x{minmax[0]}; x < minmax[2]; x++)
					for (double y{minmax[1]}; y < minmax[3]; y++)
						if (isInsidePolygon(coords[current], x, y))
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
		Object::cube(200, 200, 0, 50, 50, 50),
		Object::pyramid(6, 50, 50, 0, 50, 50, 50),
		Object::prism(5, 400, 50, 0, 50, 50, 50),
		Object::pyramid(6,
						std::vector<std::array<char, 4>>{
							{(char)255, 0, 0, (char)255},
							{0, 0, (char)255, (char)255}},
						400, 400, 0, 50, 50, 50), // pyramid, red/blue
		Object::icosahedron(50, 400, 0, 50, 50, 50)};
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
					polygon.rotate(-mouseY + event.motion.y, mouseX - event.motion.x, 0);
				mouseX = event.motion.x;
				mouseY = event.motion.y;
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
						polygon.rotate(-20, 0, 0);
					break;
				case SDLK_DOWN:
				case SDLK_s:
					for (Object &polygon : polygons)
						polygon.rotate(20, 0, 0);
					break;
				case SDLK_LEFT:
				case SDLK_a:
					for (Object &polygon : polygons)
						polygon.rotate(0, 20, 0);
					break;
				case SDLK_RIGHT:
				case SDLK_d:
					for (Object &polygon : polygons)
						polygon.rotate(0, -20, 0);
					break;
				case SDLK_LSHIFT:
				case SDLK_RSHIFT:
					for (Object &polygon : polygons)
						polygon.rotate(0, 0, -20);
					break;
				case SDLK_SPACE:
					for (Object &polygon : polygons)
						polygon.rotate(0, 0, 20);
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
