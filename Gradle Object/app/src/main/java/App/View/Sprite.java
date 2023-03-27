package App.View;

import javax.swing.JFrame;
import java.awt.Container;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.geom.Path2D;
import java.lang.Math;
import javax.swing.SwingUtilities;
import java.awt.MouseInfo;
import java.awt.Point;

public class Sprite extends Path2D.Double implements J3D {
    protected double[][][] coords = new double[1][1][3]; // [faces][lines][coordinates]
    protected double center_x = 0;
    protected double center_y = 0;
    protected double center_z = 0;
    protected Boolean auto = true;

    public Sprite(String obj, double x, double y, double z, double width, double height, double depth) {
        super();
        generate(obj, x, y, z, width, height, depth);
    }

    public Sprite(String obj, double x, double y, double z, double width, double height, double depth, double x_axis,
            double y_axis, double z_axis) {
        super();
        generate(obj, x, y, z, width, height, depth);
        auto = false;
        center_x = x_axis;
        center_y = y_axis;
        center_z = z_axis;
    }

    public Sprite(double[][][] obj) {
        super();
        coords = obj;
        regenPolygon();
    }

    protected void generate(String obj, double x, double y, double z, double width, double height, double depth) {
        switch (obj) {
            case "cube":
                coords = new double[][][] {
                        {
                                { x, y, z },
                                { x + width, y, z },
                                { x + width, y + height, z },
                                { x, y + height, z }
                        },
                        {
                                { x, y, z },
                                { x, y, z + depth },
                                { x, y + height, z + depth },
                                { x, y + height, z }
                        },
                        {
                                { x, y + height, z },
                                { x, y + height, z + depth },
                                { x + width, y + height, z + depth },
                                { x + width, y + height, z }
                        },
                        {
                                { x + width, y + height, z },
                                { x + width, y + height, z + depth },
                                { x + width, y, z + depth },
                                { x + width, y, z }
                        },
                        {
                                { x + width, y, z },
                                { x, y, z },
                                { x, y, z + depth },
                                { x + width, y, z + depth }
                        },
                        {
                                { x + width, y, z + depth },
                                { x + width, y + height, z + depth },
                                { x, y + height, z + depth },
                                { x, y, z + depth }
                        }
                };
                break;
            case "tetrahedron":
                coords = new double[][][] {
                        {
                                { x + width, y + height, z + depth },
                                { x + width, y, z },
                                { x, y + height, z }
                        },
                        {
                                { x + width, y + height, z + depth },
                                { x + width, y, z },
                                { x, y, z + depth }
                        },
                        {
                                { x + width, y + height, z + depth },
                                { x, y + height, z },
                                { x, y, z + depth }
                        },
                        {
                                { x + width, y, z },
                                { x, y + height, z },
                                { x, y, z + depth }
                        }
                };
                break;
            case "octahedron":
                coords = new double[][][] {
                        {
                                { x, y + height / 2, z + depth / 2 },
                                { x + width / 2, y, z + depth / 2 },
                                { x + width / 2, y + height / 2, z }
                        },
                        {
                                { x, y + height / 2, z + depth / 2 },
                                { x + width / 2, y, z + depth / 2 },
                                { x + width / 2, y + height / 2, z + depth }
                        },
                        {
                                { x + width, y + height / 2, z + depth / 2 },
                                { x + width / 2, y, z + depth / 2 },
                                { x + width / 2, y + height / 2, z }
                        },
                        {
                                { x + width, y + height / 2, z + depth / 2 },
                                { x + width / 2, y, z + depth / 2 },
                                { x + width / 2, y + height / 2, z + depth }
                        },
                        {
                                { x, y + height / 2, z + depth / 2 },
                                { x + width / 2, y + height, z + depth / 2 },
                                { x + width / 2, y + height / 2, z }
                        },
                        {
                                { x, y + height / 2, z + depth / 2 },
                                { x + width / 2, y + height, z + depth / 2 },
                                { x + width / 2, y + height / 2, z + depth }
                        },
                        {
                                { x + width, y + height / 2, z + depth / 2 },
                                { x + width / 2, y + height, z + depth / 2 },
                                { x + width / 2, y + height / 2, z }
                        },
                        {
                                { x + width, y + height / 2, z + depth / 2 },
                                { x + width / 2, y + height, z + depth / 2 },
                                { x + width / 2, y + height / 2, z + depth }
                        }
                };
                break;
            case "dodecahedron":
                coords = new double[][][] {
                        {
                                { x + width * (3 - Math.sqrt(5)) / 4, y + height * (3 - Math.sqrt(5)) / 4,
                                        z + depth * (3 - Math.sqrt(5)) / 4 },
                                { x + width / 2, y, z + depth * (Math.sqrt(5) - 1) / 4 },
                                { x + width / 2, y, z + depth * (5 - Math.sqrt(5)) / 4 },
                                { x + width * (3 - Math.sqrt(5)) / 4, y + height * (3 - Math.sqrt(5)) / 4,
                                        z + depth * (1 + Math.sqrt(5)) / 4 },
                                { x, y + height * (Math.sqrt(5) - 1) / 4, z + depth / 2 }
                        },
                        {
                                { x + width * (1 + Math.sqrt(5)) / 4, y + height * (3 - Math.sqrt(5)) / 4,
                                        z + depth * (3 - Math.sqrt(5)) / 4 },
                                { x + width / 2, y, z + depth * (Math.sqrt(5) - 1) / 4 },
                                { x + width / 2, y, z + depth * (5 - Math.sqrt(5)) / 4 },
                                { x + width * (1 + Math.sqrt(5)) / 4, y + height * (3 - Math.sqrt(5)) / 4,
                                        z + depth * (1 + Math.sqrt(5)) / 4 },
                                { x + width, y + height * (Math.sqrt(5) - 1) / 4, z + depth / 2 }
                        },
                        {
                                { x + width * (3 - Math.sqrt(5)) / 4, y + height * (3 - Math.sqrt(5)) / 4,
                                        z + depth * (1 + Math.sqrt(5)) / 4 },
                                { x + width / 2, y, z + depth * (5 - Math.sqrt(5)) / 4 },
                                { x + width * (1 + Math.sqrt(5)) / 4, y + height * (3 - Math.sqrt(5)) / 4,
                                        z + depth * (1 + Math.sqrt(5)) / 4 },
                                { x + width * (5 - Math.sqrt(5)) / 4, y + height / 2, z + depth },
                                { x + width * (Math.sqrt(5) - 1) / 4, y + height / 2, z + depth }
                        },
                        {
                                { x + width * (3 - Math.sqrt(5)) / 4, y + height * (3 - Math.sqrt(5)) / 4,
                                        z + depth * (3 - Math.sqrt(5)) / 4 },
                                { x + width / 2, y, z + depth * (Math.sqrt(5) - 1) / 4 },
                                { x + width * (1 + Math.sqrt(5)) / 4, y + height * (3 - Math.sqrt(5)) / 4,
                                        z + depth * (3 - Math.sqrt(5)) / 4 },
                                { x + width * (5 - Math.sqrt(5)) / 4, y + height / 2, z },
                                { x + width * (Math.sqrt(5) - 1) / 4, y + height / 2, z }
                        },
                        {
                                { x + width * (3 - Math.sqrt(5)) / 4, y + height * (1 + Math.sqrt(5)) / 4,
                                        z + depth * (3 - Math.sqrt(5)) / 4 },
                                { x + width / 2, y + height, z + depth * (Math.sqrt(5) - 1) / 4 },
                                { x + width / 2, y + height, z + depth * (5 - Math.sqrt(5)) / 4 },
                                { x + width * (3 - Math.sqrt(5)) / 4, y + height * (1 + Math.sqrt(5)) / 4,
                                        z + depth * (1 + Math.sqrt(5)) / 4 },
                                { x, y + height * (5 - Math.sqrt(5)) / 4, z + depth / 2 }
                        },
                        {
                                { x + width * (1 + Math.sqrt(5)) / 4, y + height * (1 + Math.sqrt(5)) / 4,
                                        z + depth * (3 - Math.sqrt(5)) / 4 },
                                { x + width / 2, y + height, z + depth * (Math.sqrt(5) - 1) / 4 },
                                { x + width / 2, y + height, z + depth * (5 - Math.sqrt(5)) / 4 },
                                { x + width * (1 + Math.sqrt(5)) / 4, y + height * (1 + Math.sqrt(5)) / 4,
                                        z + depth * (1 + Math.sqrt(5)) / 4 },
                                { x + width, y + height * (5 - Math.sqrt(5)) / 4, z + depth / 2 }
                        },
                        {
                                { x + width * (3 - Math.sqrt(5)) / 4, y + height * (1 + Math.sqrt(5)) / 4,
                                        z + depth * (1 + Math.sqrt(5)) / 4 },
                                { x + width / 2, y + height, z + depth * (5 - Math.sqrt(5)) / 4 },
                                { x + width * (1 + Math.sqrt(5)) / 4, y + height * (1 + Math.sqrt(5)) / 4,
                                        z + depth * (1 + Math.sqrt(5)) / 4 },
                                { x + width * (5 - Math.sqrt(5)) / 4, y + height / 2, z + depth },
                                { x + width * (Math.sqrt(5) - 1) / 4, y + height / 2, z + depth }
                        },
                        {
                                { x + width * (3 - Math.sqrt(5)) / 4, y + height * (1 + Math.sqrt(5)) / 4,
                                        z + depth * (3 - Math.sqrt(5)) / 4 },
                                { x + width / 2, y + height, z + depth * (Math.sqrt(5) - 1) / 4 },
                                { x + width * (1 + Math.sqrt(5)) / 4, y + height * (1 + Math.sqrt(5)) / 4,
                                        z + depth * (3 - Math.sqrt(5)) / 4 },
                                { x + width * (5 - Math.sqrt(5)) / 4, y + height / 2, z },
                                { x + width * (Math.sqrt(5) - 1) / 4, y + height / 2, z }
                        },
                        {
                                { x + width * (1 + Math.sqrt(5)) / 4, y + height * (3 - Math.sqrt(5)) / 4,
                                        z + depth * (3 - Math.sqrt(5)) / 4 },
                                { x + width * (5 - Math.sqrt(5)) / 4, y + height / 2, z },
                                { x + width * (1 + Math.sqrt(5)) / 4, y + height * (1 + Math.sqrt(5)) / 4,
                                        z + depth * (3 - Math.sqrt(5)) / 4 },
                                { x + width, y + height * (5 - Math.sqrt(5)) / 4, z + depth / 2 },
                                { x + width, y + height * (Math.sqrt(5) - 1) / 4, z + depth / 2 }
                        },
                        {
                                { x + width * (1 + Math.sqrt(5)) / 4, y + height * (3 - Math.sqrt(5)) / 4,
                                        z + depth * (1 + Math.sqrt(5)) / 4 },
                                { x + width * (5 - Math.sqrt(5)) / 4, y + height / 2, z + depth },
                                { x + width * (1 + Math.sqrt(5)) / 4, y + height * (1 + Math.sqrt(5)) / 4,
                                        z + depth * (1 + Math.sqrt(5)) / 4 },
                                { x + width, y + height * (5 - Math.sqrt(5)) / 4, z + depth / 2 },
                                { x + width, y + height * (Math.sqrt(5) - 1) / 4, z + depth / 2 }
                        },
                        {
                                { x + width * (3 - Math.sqrt(5)) / 4, y + height * (3 - Math.sqrt(5)) / 4,
                                        z + depth * (3 - Math.sqrt(5)) / 4 },
                                { x + width * (Math.sqrt(5) - 1) / 4, y + height / 2, z },
                                { x + width * (3 - Math.sqrt(5)) / 4, y + height * (1 + Math.sqrt(5)) / 4,
                                        z + depth * (3 - Math.sqrt(5)) / 4 },
                                { x, y + height * (5 - Math.sqrt(5)) / 4, z + depth / 2 },
                                { x, y + height * (Math.sqrt(5) - 1) / 4, z + depth / 2 }
                        },
                        {
                                { x + width * (3 - Math.sqrt(5)) / 4, y + height * (3 - Math.sqrt(5)) / 4,
                                        z + depth * (1 + Math.sqrt(5)) / 4 },
                                { x + width * (Math.sqrt(5) - 1) / 4, y + height / 2, z + depth },
                                { x + width * (3 - Math.sqrt(5)) / 4, y + height * (1 + Math.sqrt(5)) / 4,
                                        z + depth * (1 + Math.sqrt(5)) / 4 },
                                { x, y + height * (5 - Math.sqrt(5)) / 4, z + depth / 2 },
                                { x, y + height * (Math.sqrt(5) - 1) / 4, z + depth / 2 }
                        }
                };
                break;
            case "icosahedron":
                coords = new double[][][] {
                        {
                                { x + width / 2, y, z + depth * (3 - Math.sqrt(5)) / 4 },
                                { x + width * (3 - Math.sqrt(5)) / 4, y + height / 2, z },
                                { x + width * (1 + Math.sqrt(5)) / 4, y + height / 2, z }
                        },
                        {
                                { x + width / 2, y + height, z + depth * (3 - Math.sqrt(5)) / 4 },
                                { x + width * (3 - Math.sqrt(5)) / 4, y + height / 2, z },
                                { x + width * (1 + Math.sqrt(5)) / 4, y + height / 2, z }
                        },
                        {
                                { x + width / 2, y + height, z + depth * (3 - Math.sqrt(5)) / 4 },
                                { x + width * (1 + Math.sqrt(5)) / 4, y + height / 2, z },
                                { x + width, y + height * (1 + Math.sqrt(5)) / 4, z + depth / 2 }
                        },
                        {
                                { x + width / 2, y, z + depth * (3 - Math.sqrt(5)) / 4 },
                                { x + width * (1 + Math.sqrt(5)) / 4, y + height / 2, z },
                                { x + width, y + height * (3 - Math.sqrt(5)) / 4, z + depth / 2 }
                        },
                        {
                                { x + width * (1 + Math.sqrt(5)) / 4, y + height / 2, z },
                                { x + width, y + height * (1 + Math.sqrt(5)) / 4, z + depth / 2 },
                                { x + width, y + height * (3 - Math.sqrt(5)) / 4, z + depth / 2 }
                        },
                        {
                                { x + width / 2, y + height, z + depth * (1 + Math.sqrt(5)) / 4 },
                                { x + width / 2, y + height, z + depth * (3 - Math.sqrt(5)) / 4 },
                                { x + width, y + height * (1 + Math.sqrt(5)) / 4, z + depth / 2 }
                        },
                        {
                                { x + width / 2, y + height, z + depth * (1 + Math.sqrt(5)) / 4 },
                                { x + width / 2, y + height, z + depth * (3 - Math.sqrt(5)) / 4 },
                                { x, y + height * (1 + Math.sqrt(5)) / 4, z + depth / 2 }
                        },
                        {
                                { x + width * (1 + Math.sqrt(5)) / 4, y + height / 2, z + depth },
                                { x + width, y + height * (1 + Math.sqrt(5)) / 4, z + depth / 2 },
                                { x + width, y + height * (3 - Math.sqrt(5)) / 4, z + depth / 2 }
                        },
                        {
                                { x + width / 2, y, z + depth * (1 + Math.sqrt(5)) / 4 },
                                { x + width * (3 - Math.sqrt(5)) / 4, y + height / 2, z + depth },
                                { x + width * (1 + Math.sqrt(5)) / 4, y + height / 2, z + depth }
                        },
                        {
                                { x + width / 2, y + height, z + depth * (1 + Math.sqrt(5)) / 4 },
                                { x + width * (3 - Math.sqrt(5)) / 4, y + height / 2, z + depth },
                                { x + width * (1 + Math.sqrt(5)) / 4, y + height / 2, z + depth }
                        },
                        {
                                { x + width, y + height * (1 + Math.sqrt(5)) / 4, z + depth / 2 },
                                { x + width / 2, y + height, z + depth * (1 + Math.sqrt(5)) / 4 },
                                { x + width * (1 + Math.sqrt(5)) / 4, y + height / 2, z + depth }
                        },
                        {
                                { x + width / 2, y, z + depth * (1 + Math.sqrt(5)) / 4 },
                                { x + width * (1 + Math.sqrt(5)) / 4, y + height / 2, z + depth },
                                { x + width, y + height * (3 - Math.sqrt(5)) / 4, z + depth / 2 }
                        },
                        {
                                { x + width / 2, y, z + depth * (1 + Math.sqrt(5)) / 4 },
                                { x + width / 2, y, z + depth * (3 - Math.sqrt(5)) / 4 },
                                { x + width, y + height * (3 - Math.sqrt(5)) / 4, z + depth / 2 }
                        },
                        {
                                { x + width / 2, y, z + depth * (1 + Math.sqrt(5)) / 4 },
                                { x + width / 2, y, z + depth * (3 - Math.sqrt(5)) / 4 },
                                { x, y + height * (3 - Math.sqrt(5)) / 4, z + depth / 2 }
                        },
                        {
                                { x + width / 2, y + height, z + depth * (3 - Math.sqrt(5)) / 4 },
                                { x + width * (3 - Math.sqrt(5)) / 4, y + height / 2, z },
                                { x, y + height * (1 + Math.sqrt(5)) / 4, z + depth / 2 }
                        },
                        {
                                { x + width / 2, y, z + depth * (3 - Math.sqrt(5)) / 4 },
                                { x + width * (3 - Math.sqrt(5)) / 4, y + height / 2, z },
                                { x, y + height * (3 - Math.sqrt(5)) / 4, z + depth / 2 }
                        },
                        {
                                { x + width * (3 - Math.sqrt(5)) / 4, y + height / 2, z },
                                { x, y + height * (1 + Math.sqrt(5)) / 4, z + depth / 2 },
                                { x, y + height * (3 - Math.sqrt(5)) / 4, z + depth / 2 }
                        },
                        {
                                { x, y + height * (1 + Math.sqrt(5)) / 4, z + depth / 2 },
                                { x + width / 2, y + height, z + depth * (1 + Math.sqrt(5)) / 4 },
                                { x + width * (3 - Math.sqrt(5)) / 4, y + height / 2, z + depth }
                        },
                        {
                                { x + width / 2, y, z + depth * (1 + Math.sqrt(5)) / 4 },
                                { x + width * (3 - Math.sqrt(5)) / 4, y + height / 2, z + depth },
                                { x, y + height * (3 - Math.sqrt(5)) / 4, z + depth / 2 }
                        },
                        {
                                { x + width * (3 - Math.sqrt(5)) / 4, y + height / 2, z + depth },
                                { x, y + height * (1 + Math.sqrt(5)) / 4, z + depth / 2 },
                                { x, y + height * (3 - Math.sqrt(5)) / 4, z + depth / 2 }
                        }
                };
                break;
            default:
                System.out.println("Incorrect String Argument");
                break;
        }
        if (auto)
            autoCenter();
        regenPolygon();
    }

    public static double getDepth(double[][] face) {
        double avg = 0;
        for (double[] i : face)
            try {
                avg += i[2];
            } catch (NullPointerException e) {
            }
        return avg / face.length;
    }

    public double getDepth() {
        double min = coords[0][0][2];
        for (double[][] face : coords)
            for (double[] line : face)
                if (line[2] < min)
                    min = line[2];
        return min;
    }

    public static void rotatePoint(double[] vec, double theta_x, double theta_y, double theta_z) {
        double x = vec[0] * Math.cos(theta_z * Math.PI / 180) * Math.cos(theta_y * Math.PI / 180) +
                vec[1] * Math.cos(theta_z * Math.PI / 180) * Math.sin(theta_y * Math.PI / 180)
                        * Math.sin(theta_x * Math.PI / 180)
                -
                vec[1] * Math.sin(theta_z * Math.PI / 180) * Math.cos(theta_x * Math.PI / 180) +
                vec[2] * Math.cos(theta_z * Math.PI / 180) * Math.sin(theta_y * Math.PI / 180)
                        * Math.cos(theta_x * Math.PI / 180)
                +
                vec[2] * Math.sin(theta_z * Math.PI / 180) * Math.sin(theta_x * Math.PI / 180);
        double y = vec[0] * Math.sin(theta_z * Math.PI / 180) * Math.cos(theta_y * Math.PI / 180) +
                vec[1] * Math.sin(theta_z * Math.PI / 180) * Math.sin(theta_y * Math.PI / 180)
                        * Math.sin(theta_x * Math.PI / 180)
                +
                vec[1] * Math.cos(theta_z * Math.PI / 180) * Math.cos(theta_x * Math.PI / 180) +
                vec[2] * Math.sin(theta_z * Math.PI / 180) * Math.sin(theta_y * Math.PI / 180)
                        * Math.cos(theta_x * Math.PI / 180)
                -
                vec[2] * Math.cos(theta_z * Math.PI / 180) * Math.sin(theta_x * Math.PI / 180);
        double z = -vec[0] * Math.sin(theta_y * Math.PI / 180) +
                vec[1] * Math.cos(theta_y * Math.PI / 180) * Math.sin(theta_x * Math.PI / 180) +
                vec[2] * Math.cos(theta_y * Math.PI / 180) * Math.cos(theta_x * Math.PI / 180);
        vec[0] = x;
        vec[1] = y;
        vec[2] = z;
    }

    protected void increaseFaces() {
        double[][][] coords2 = new double[coords.length * 2][coords.length == 0 ? 1 : coords[0].length][3];
        for (int face = 0; face < coords.length; face++)
            coords2[face] = coords[face];
        coords = coords2;
    }

    protected void increasePoints() {
        double[][][] coords2 = new double[coords.length][coords[0].length * 2][3];
        for (int face = 0; face < coords.length; face++) {
            double[][] face2 = new double[coords[0].length * 2][3];
            for (int point = 0; point < coords[face].length; point++)
                face2[point] = coords[face][point];
            coords2[face] = face2;
        }
        coords = coords2;
    }

    public void setPoint(int face, int index, double x, double y, double z) {
        if (face >= coords.length)
            increaseFaces();
        if (index >= coords[0].length)
            increasePoints();
        coords[face][index][0] = x;
        coords[face][index][1] = y;
        coords[face][index][2] = z;
        regenPolygon();
        if (auto)
            autoCenter();
    }

    public void addPoint(int face, double x, double y, double z) {
        setPoint(face, (coords.length == 0 || coords.length <= face ? 0 : coords[face].length), x, y, z);
    }

    public void setPosition(double x, double y, double z) {
        for (int face = 0; face < coords.length; face++)
            for (int point = 0; point < coords[face].length; point++) {
                coords[face][point][0] += (x - center_x);
                coords[face][point][1] += (y - center_y);
                coords[face][point][2] += (z - center_z);
            }
    }

    public void movePosition(double x, double y, double z) {
        for (int face = 0; face < coords.length; face++)
            for (int point = 0; point < coords[face].length; point++) {
                coords[face][point][0] += x;
                coords[face][point][1] += y;
                coords[face][point][2] += z;
            }
    }

    public void autoCenter() {
        center_x = 0;
        center_y = 0;
        center_z = 0;
        int vertices = 0;
        for (double[][] face : coords)
            for (double[] i : face)
                try {
                    center_x += i[0];
                    center_y += i[1];
                    center_z += i[2];
                    vertices++;
                } catch (NullPointerException e) {
                }
        center_x /= vertices;
        center_y /= vertices;
        center_z /= vertices;
    }

    public void rotate(double theta_x, double theta_y, double theta_z) {
        for (int face = 0; face < coords.length; face++) {
            for (int point = 0; point < coords[face].length; point++)
                try {
                    coords[face][point][0] -= center_x;
                    coords[face][point][1] -= center_y;
                    coords[face][point][2] -= center_z;
                    rotatePoint(coords[face][point], theta_x, theta_y, theta_z);
                    coords[face][point][0] += center_x;
                    coords[face][point][1] += center_y;
                    coords[face][point][2] += center_z;
                } catch (NullPointerException e) {
                }
            regenPolygon();
        }
    }

    protected void regenPolygon() {
        reset();
        Boolean[] indeces = new Boolean[coords.length];
        for (int loop = 0; loop < coords.length; loop++) {
            int current = -1;
            for (int index = 0; index < coords.length; index++)
                if (indeces[index] == null && (current == -1 || getDepth(coords[index]) >= getDepth(coords[current])))
                    current = index;
            moveTo(coords[current][0][0], coords[current][0][1]);
            for (int i = 1; i < coords[current].length; i++)
                try {
                    lineTo(coords[current][i][0], coords[current][i][1]);
                } catch (NullPointerException e) {
                }
            closePath();
            indeces[current] = true;
        }
    }

    public static void main(String[] args) {
        JFrame frame = new JFrame();
        frame.setContentPane(new Container() {
            Point lastPoint;
            Sprite sprite1 = new Sprite("cube", 225, 200, 0, 50, 50, 50);
            Sprite sprite2 = new Sprite("icosahedron", 25, 25, 0, 50, 50, 50);
            Sprite sprite3 = new Sprite("dodecahedron", 425, 400, 0, 50, 50, 50);
            Sprite sprite4 = new Sprite("octahedron", 25, 400, 0, 50, 50, 50);
            Sprite sprite5 = new Sprite("tetrahedron", 425, 25, 0, 50, 50, 50);

            @Override
            public void paint(Graphics g) {
                super.paint(g);
                Point point = MouseInfo.getPointerInfo().getLocation();
                SwingUtilities.convertPointFromScreen(point, this);
                if (lastPoint != null) {
                    Graphics2D g2 = (Graphics2D) g;
                    sprite1.rotate(point.getY() - lastPoint.getY(), -point.getX() + lastPoint.getX(), 0);
                    g2.draw(sprite1);
                    sprite2.rotate(point.getY() - lastPoint.getY(), -point.getX() + lastPoint.getX(), 0);
                    g2.draw(sprite2);
                    sprite3.rotate(point.getY() - lastPoint.getY(), -point.getX() + lastPoint.getX(), 0);
                    g2.draw(sprite3);
                    sprite4.rotate(point.getY() - lastPoint.getY(), -point.getX() + lastPoint.getX(), 0);
                    g2.draw(sprite4);
                    sprite5.rotate(point.getY() - lastPoint.getY(), -point.getX() + lastPoint.getX(), 0);
                    g2.draw(sprite5);
                }
                lastPoint = point;
                repaint();
            }
        });
        frame.setSize(500, 500);
        frame.setVisible(true);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    }
}
