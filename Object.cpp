#include <SDL2/SDL.h>
#include <vector>
#include <array>
#define pi 3.14159265358979323846

class Object
{
private:
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

	static double getDepth(std::vector<std::array<double, 3>> face)
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
	static Object cube(double x = 0, double y = 0, double z = 0, double width = 1, double height = 1, double depth = 1)
	{
		Object temp;

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
	std::vector<std::vector<std::array<double, 3>>> coords;
	std::vector<Prop> polygon;
	double center_x{0};
	double center_y{0};
	double center_z{0};

public:
	bool borderless = false;
	bool wireframe = false;
	void setPoint(int face, int index, double x, double y, double z, double a = 255)
	{
		if (face >= coords.size())
		{
			coords.push_back(std::vector<std::array<double, 3>>{});
			polygon.push_back(Prop());
		}
		if (index >= coords[face].size())
			coords[face].push_back(std::array<double, 3>{0, 0, 0});
		coords[face][index][0] = x;
		coords[face][index][1] = y;
		coords[face][index][2] = z;
		coords[face][index][3] = a;
		autoCenter();
	}
	void addPoint(int face, double x, double y, double z)
	{
		if (face >= coords.size())
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

	Object polygons[] = {
		Object::icosahedron(50, 50, 50, 100, 100, 100),
		Object::cube(200, 200, 200, 50, 50, 50)
	};
	polygons[0].wireframe = true;
	
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);
	for (Object polygon : polygons)
		polygon.draw(renderer);
	SDL_RenderPresent(renderer);

	bool quit = false;
	SDL_Event event;

	while (!quit)
	{
		// Event loop
		while (SDL_PollEvent(&event) != 0)
		{
			if (event.type == SDL_QUIT)
			{
				quit = true;
			}
			else if (event.type == SDL_KEYDOWN)
			{
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
				default:
					break;
				}
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
