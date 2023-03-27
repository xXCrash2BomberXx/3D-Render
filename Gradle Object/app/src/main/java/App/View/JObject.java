package App.View;

import java.awt.Color;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.Container;
import java.lang.Math;
import java.awt.geom.Path2D;

public class JObject extends Container implements J3D {
        protected double[][][] coords = new double[1][1][3]; // [faces][lines][coordinates]
        protected Path2D[] polygon = new Path2D[0]; // [faces]
        protected Color[] colors = new Color[0]; // [colors]
        protected double center_x = 0;
        protected double center_y = 0;
        protected double center_z = 0;
        protected Boolean auto = true;
        public Boolean wireframe = false;

        public JObject(String obj, double width, double height, double depth) {
                super();
                generate(obj, 0, 0, 0, width, height, depth);
        }

        public JObject(String obj, double width, double height, double depth, Boolean wire) {
                super();
                generate(obj, 0, 0, 0, width, height, depth);
                wireframe = wire;
        }

        public JObject(String obj, double x, double y, double z, double width, double height, double depth) {
                super();
                generate(obj, x, y, z, width, height, depth);
        }

        public JObject(String obj, double x, double y, double z, double width, double height, double depth,
                        Boolean wire) {
                super();
                generate(obj, x, y, z, width, height, depth);
                wireframe = wire;
        }

        public JObject(String obj, double x, double y, double z, double width, double height, double depth,
                        double x_axis,
                        double y_axis, double z_axis) {
                super();
                generate(obj, x, y, z, width, height, depth);
                auto = false;
                center_x = x_axis;
                center_y = y_axis;
                center_z = z_axis;
        }

        public JObject(String obj, double x, double y, double z, double width, double height, double depth,
                        double x_axis,
                        double y_axis, double z_axis, Boolean wire) {
                super();
                generate(obj, x, y, z, width, height, depth);
                auto = false;
                center_x = x_axis;
                center_y = y_axis;
                center_z = z_axis;
                wireframe = wire;
        }

        public JObject(double[][][] obj) {
                super();
                setLocation(0, 0);
                coords = obj;
                for (int i = 0; i < coords.length; i++)
                        regenPolygon(i);
        }

        protected void generate(String obj, double x, double y, double z, double width, double height, double depth) {
                setLocation(0, 0);
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
                                polygon = new Path2D[6];
                                colors = new Color[] {
                                                Color.RED,
                                                Color.GREEN,
                                                Color.BLUE,
                                                Color.YELLOW,
                                                Color.CYAN,
                                                Color.MAGENTA
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
                                polygon = new Path2D[4];
                                colors = new Color[] {
                                                Color.RED,
                                                Color.GREEN,
                                                Color.BLUE,
                                                Color.YELLOW
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
                                polygon = new Path2D[8];
                                colors = new Color[] {
                                                Color.RED,
                                                Color.GREEN,
                                                Color.BLUE,
                                                Color.YELLOW,
                                                Color.CYAN,
                                                Color.MAGENTA,
                                                Color.BLACK,
                                                Color.GRAY
                                };
                                break;
                        case "dodecahedron":
                                coords = new double[][][] {
                                                {
                                                                { x + width * (3 - Math.sqrt(5)) / 4,
                                                                                y + height * (3 - Math.sqrt(5)) / 4,
                                                                                z + depth * (3 - Math.sqrt(5)) / 4 },
                                                                { x + width / 2, y,
                                                                                z + depth * (Math.sqrt(5) - 1) / 4 },
                                                                { x + width / 2, y,
                                                                                z + depth * (5 - Math.sqrt(5)) / 4 },
                                                                { x + width * (3 - Math.sqrt(5)) / 4,
                                                                                y + height * (3 - Math.sqrt(5)) / 4,
                                                                                z + depth * (1 + Math.sqrt(5)) / 4 },
                                                                { x, y + height * (Math.sqrt(5) - 1) / 4,
                                                                                z + depth / 2 }
                                                },
                                                {
                                                                { x + width * (1 + Math.sqrt(5)) / 4,
                                                                                y + height * (3 - Math.sqrt(5)) / 4,
                                                                                z + depth * (3 - Math.sqrt(5)) / 4 },
                                                                { x + width / 2, y,
                                                                                z + depth * (Math.sqrt(5) - 1) / 4 },
                                                                { x + width / 2, y,
                                                                                z + depth * (5 - Math.sqrt(5)) / 4 },
                                                                { x + width * (1 + Math.sqrt(5)) / 4,
                                                                                y + height * (3 - Math.sqrt(5)) / 4,
                                                                                z + depth * (1 + Math.sqrt(5)) / 4 },
                                                                { x + width, y + height * (Math.sqrt(5) - 1) / 4,
                                                                                z + depth / 2 }
                                                },
                                                {
                                                                { x + width * (3 - Math.sqrt(5)) / 4,
                                                                                y + height * (3 - Math.sqrt(5)) / 4,
                                                                                z + depth * (1 + Math.sqrt(5)) / 4 },
                                                                { x + width / 2, y,
                                                                                z + depth * (5 - Math.sqrt(5)) / 4 },
                                                                { x + width * (1 + Math.sqrt(5)) / 4,
                                                                                y + height * (3 - Math.sqrt(5)) / 4,
                                                                                z + depth * (1 + Math.sqrt(5)) / 4 },
                                                                { x + width * (5 - Math.sqrt(5)) / 4, y + height / 2,
                                                                                z + depth },
                                                                { x + width * (Math.sqrt(5) - 1) / 4, y + height / 2,
                                                                                z + depth }
                                                },
                                                {
                                                                { x + width * (3 - Math.sqrt(5)) / 4,
                                                                                y + height * (3 - Math.sqrt(5)) / 4,
                                                                                z + depth * (3 - Math.sqrt(5)) / 4 },
                                                                { x + width / 2, y,
                                                                                z + depth * (Math.sqrt(5) - 1) / 4 },
                                                                { x + width * (1 + Math.sqrt(5)) / 4,
                                                                                y + height * (3 - Math.sqrt(5)) / 4,
                                                                                z + depth * (3 - Math.sqrt(5)) / 4 },
                                                                { x + width * (5 - Math.sqrt(5)) / 4, y + height / 2,
                                                                                z },
                                                                { x + width * (Math.sqrt(5) - 1) / 4, y + height / 2,
                                                                                z }
                                                },
                                                {
                                                                { x + width * (3 - Math.sqrt(5)) / 4,
                                                                                y + height * (1 + Math.sqrt(5)) / 4,
                                                                                z + depth * (3 - Math.sqrt(5)) / 4 },
                                                                { x + width / 2, y + height,
                                                                                z + depth * (Math.sqrt(5) - 1) / 4 },
                                                                { x + width / 2, y + height,
                                                                                z + depth * (5 - Math.sqrt(5)) / 4 },
                                                                { x + width * (3 - Math.sqrt(5)) / 4,
                                                                                y + height * (1 + Math.sqrt(5)) / 4,
                                                                                z + depth * (1 + Math.sqrt(5)) / 4 },
                                                                { x, y + height * (5 - Math.sqrt(5)) / 4,
                                                                                z + depth / 2 }
                                                },
                                                {
                                                                { x + width * (1 + Math.sqrt(5)) / 4,
                                                                                y + height * (1 + Math.sqrt(5)) / 4,
                                                                                z + depth * (3 - Math.sqrt(5)) / 4 },
                                                                { x + width / 2, y + height,
                                                                                z + depth * (Math.sqrt(5) - 1) / 4 },
                                                                { x + width / 2, y + height,
                                                                                z + depth * (5 - Math.sqrt(5)) / 4 },
                                                                { x + width * (1 + Math.sqrt(5)) / 4,
                                                                                y + height * (1 + Math.sqrt(5)) / 4,
                                                                                z + depth * (1 + Math.sqrt(5)) / 4 },
                                                                { x + width, y + height * (5 - Math.sqrt(5)) / 4,
                                                                                z + depth / 2 }
                                                },
                                                {
                                                                { x + width * (3 - Math.sqrt(5)) / 4,
                                                                                y + height * (1 + Math.sqrt(5)) / 4,
                                                                                z + depth * (1 + Math.sqrt(5)) / 4 },
                                                                { x + width / 2, y + height,
                                                                                z + depth * (5 - Math.sqrt(5)) / 4 },
                                                                { x + width * (1 + Math.sqrt(5)) / 4,
                                                                                y + height * (1 + Math.sqrt(5)) / 4,
                                                                                z + depth * (1 + Math.sqrt(5)) / 4 },
                                                                { x + width * (5 - Math.sqrt(5)) / 4, y + height / 2,
                                                                                z + depth },
                                                                { x + width * (Math.sqrt(5) - 1) / 4, y + height / 2,
                                                                                z + depth }
                                                },
                                                {
                                                                { x + width * (3 - Math.sqrt(5)) / 4,
                                                                                y + height * (1 + Math.sqrt(5)) / 4,
                                                                                z + depth * (3 - Math.sqrt(5)) / 4 },
                                                                { x + width / 2, y + height,
                                                                                z + depth * (Math.sqrt(5) - 1) / 4 },
                                                                { x + width * (1 + Math.sqrt(5)) / 4,
                                                                                y + height * (1 + Math.sqrt(5)) / 4,
                                                                                z + depth * (3 - Math.sqrt(5)) / 4 },
                                                                { x + width * (5 - Math.sqrt(5)) / 4, y + height / 2,
                                                                                z },
                                                                { x + width * (Math.sqrt(5) - 1) / 4, y + height / 2,
                                                                                z }
                                                },
                                                {
                                                                { x + width * (1 + Math.sqrt(5)) / 4,
                                                                                y + height * (3 - Math.sqrt(5)) / 4,
                                                                                z + depth * (3 - Math.sqrt(5)) / 4 },
                                                                { x + width * (5 - Math.sqrt(5)) / 4, y + height / 2,
                                                                                z },
                                                                { x + width * (1 + Math.sqrt(5)) / 4,
                                                                                y + height * (1 + Math.sqrt(5)) / 4,
                                                                                z + depth * (3 - Math.sqrt(5)) / 4 },
                                                                { x + width, y + height * (5 - Math.sqrt(5)) / 4,
                                                                                z + depth / 2 },
                                                                { x + width, y + height * (Math.sqrt(5) - 1) / 4,
                                                                                z + depth / 2 }
                                                },
                                                {
                                                                { x + width * (1 + Math.sqrt(5)) / 4,
                                                                                y + height * (3 - Math.sqrt(5)) / 4,
                                                                                z + depth * (1 + Math.sqrt(5)) / 4 },
                                                                { x + width * (5 - Math.sqrt(5)) / 4, y + height / 2,
                                                                                z + depth },
                                                                { x + width * (1 + Math.sqrt(5)) / 4,
                                                                                y + height * (1 + Math.sqrt(5)) / 4,
                                                                                z + depth * (1 + Math.sqrt(5)) / 4 },
                                                                { x + width, y + height * (5 - Math.sqrt(5)) / 4,
                                                                                z + depth / 2 },
                                                                { x + width, y + height * (Math.sqrt(5) - 1) / 4,
                                                                                z + depth / 2 }
                                                },
                                                {
                                                                { x + width * (3 - Math.sqrt(5)) / 4,
                                                                                y + height * (3 - Math.sqrt(5)) / 4,
                                                                                z + depth * (3 - Math.sqrt(5)) / 4 },
                                                                { x + width * (Math.sqrt(5) - 1) / 4, y + height / 2,
                                                                                z },
                                                                { x + width * (3 - Math.sqrt(5)) / 4,
                                                                                y + height * (1 + Math.sqrt(5)) / 4,
                                                                                z + depth * (3 - Math.sqrt(5)) / 4 },
                                                                { x, y + height * (5 - Math.sqrt(5)) / 4,
                                                                                z + depth / 2 },
                                                                { x, y + height * (Math.sqrt(5) - 1) / 4,
                                                                                z + depth / 2 }
                                                },
                                                {
                                                                { x + width * (3 - Math.sqrt(5)) / 4,
                                                                                y + height * (3 - Math.sqrt(5)) / 4,
                                                                                z + depth * (1 + Math.sqrt(5)) / 4 },
                                                                { x + width * (Math.sqrt(5) - 1) / 4, y + height / 2,
                                                                                z + depth },
                                                                { x + width * (3 - Math.sqrt(5)) / 4,
                                                                                y + height * (1 + Math.sqrt(5)) / 4,
                                                                                z + depth * (1 + Math.sqrt(5)) / 4 },
                                                                { x, y + height * (5 - Math.sqrt(5)) / 4,
                                                                                z + depth / 2 },
                                                                { x, y + height * (Math.sqrt(5) - 1) / 4,
                                                                                z + depth / 2 }
                                                }
                                };
                                polygon = new Path2D[12];
                                colors = new Color[] {
                                                Color.RED,
                                                Color.GREEN,
                                                Color.BLUE,
                                                Color.YELLOW,
                                                Color.CYAN,
                                                Color.MAGENTA,
                                                Color.BLACK,
                                                Color.GRAY,
                                                new Color(127, 0, 0, 255), // Dark Red
                                                new Color(0, 127, 0, 255), // Dark Green
                                                new Color(0, 0, 127, 255), // Dark Blue
                                                new Color(127, 127, 0, 255) // Dark Yellow
                                };
                                break;
                        case "icosahedron":
                                coords = new double[][][] {
                                                {
                                                                { x + width / 2, y,
                                                                                z + depth * (3 - Math.sqrt(5)) / 4 },
                                                                { x + width * (3 - Math.sqrt(5)) / 4, y + height / 2,
                                                                                z },
                                                                { x + width * (1 + Math.sqrt(5)) / 4, y + height / 2,
                                                                                z }
                                                },
                                                {
                                                                { x + width / 2, y + height,
                                                                                z + depth * (3 - Math.sqrt(5)) / 4 },
                                                                { x + width * (3 - Math.sqrt(5)) / 4, y + height / 2,
                                                                                z },
                                                                { x + width * (1 + Math.sqrt(5)) / 4, y + height / 2,
                                                                                z }
                                                },
                                                {
                                                                { x + width / 2, y + height,
                                                                                z + depth * (3 - Math.sqrt(5)) / 4 },
                                                                { x + width * (1 + Math.sqrt(5)) / 4, y + height / 2,
                                                                                z },
                                                                { x + width, y + height * (1 + Math.sqrt(5)) / 4,
                                                                                z + depth / 2 }
                                                },
                                                {
                                                                { x + width / 2, y,
                                                                                z + depth * (3 - Math.sqrt(5)) / 4 },
                                                                { x + width * (1 + Math.sqrt(5)) / 4, y + height / 2,
                                                                                z },
                                                                { x + width, y + height * (3 - Math.sqrt(5)) / 4,
                                                                                z + depth / 2 }
                                                },
                                                {
                                                                { x + width * (1 + Math.sqrt(5)) / 4, y + height / 2,
                                                                                z },
                                                                { x + width, y + height * (1 + Math.sqrt(5)) / 4,
                                                                                z + depth / 2 },
                                                                { x + width, y + height * (3 - Math.sqrt(5)) / 4,
                                                                                z + depth / 2 }
                                                },
                                                {
                                                                { x + width / 2, y + height,
                                                                                z + depth * (1 + Math.sqrt(5)) / 4 },
                                                                { x + width / 2, y + height,
                                                                                z + depth * (3 - Math.sqrt(5)) / 4 },
                                                                { x + width, y + height * (1 + Math.sqrt(5)) / 4,
                                                                                z + depth / 2 }
                                                },
                                                {
                                                                { x + width / 2, y + height,
                                                                                z + depth * (1 + Math.sqrt(5)) / 4 },
                                                                { x + width / 2, y + height,
                                                                                z + depth * (3 - Math.sqrt(5)) / 4 },
                                                                { x, y + height * (1 + Math.sqrt(5)) / 4,
                                                                                z + depth / 2 }
                                                },
                                                {
                                                                { x + width * (1 + Math.sqrt(5)) / 4, y + height / 2,
                                                                                z + depth },
                                                                { x + width, y + height * (1 + Math.sqrt(5)) / 4,
                                                                                z + depth / 2 },
                                                                { x + width, y + height * (3 - Math.sqrt(5)) / 4,
                                                                                z + depth / 2 }
                                                },
                                                {
                                                                { x + width / 2, y,
                                                                                z + depth * (1 + Math.sqrt(5)) / 4 },
                                                                { x + width * (3 - Math.sqrt(5)) / 4, y + height / 2,
                                                                                z + depth },
                                                                { x + width * (1 + Math.sqrt(5)) / 4, y + height / 2,
                                                                                z + depth }
                                                },
                                                {
                                                                { x + width / 2, y + height,
                                                                                z + depth * (1 + Math.sqrt(5)) / 4 },
                                                                { x + width * (3 - Math.sqrt(5)) / 4, y + height / 2,
                                                                                z + depth },
                                                                { x + width * (1 + Math.sqrt(5)) / 4, y + height / 2,
                                                                                z + depth }
                                                },
                                                {
                                                                { x + width, y + height * (1 + Math.sqrt(5)) / 4,
                                                                                z + depth / 2 },
                                                                { x + width / 2, y + height,
                                                                                z + depth * (1 + Math.sqrt(5)) / 4 },
                                                                { x + width * (1 + Math.sqrt(5)) / 4, y + height / 2,
                                                                                z + depth }
                                                },
                                                {
                                                                { x + width / 2, y,
                                                                                z + depth * (1 + Math.sqrt(5)) / 4 },
                                                                { x + width * (1 + Math.sqrt(5)) / 4, y + height / 2,
                                                                                z + depth },
                                                                { x + width, y + height * (3 - Math.sqrt(5)) / 4,
                                                                                z + depth / 2 }
                                                },
                                                {
                                                                { x + width / 2, y,
                                                                                z + depth * (1 + Math.sqrt(5)) / 4 },
                                                                { x + width / 2, y,
                                                                                z + depth * (3 - Math.sqrt(5)) / 4 },
                                                                { x + width, y + height * (3 - Math.sqrt(5)) / 4,
                                                                                z + depth / 2 }
                                                },
                                                {
                                                                { x + width / 2, y,
                                                                                z + depth * (1 + Math.sqrt(5)) / 4 },
                                                                { x + width / 2, y,
                                                                                z + depth * (3 - Math.sqrt(5)) / 4 },
                                                                { x, y + height * (3 - Math.sqrt(5)) / 4,
                                                                                z + depth / 2 }
                                                },
                                                {
                                                                { x + width / 2, y + height,
                                                                                z + depth * (3 - Math.sqrt(5)) / 4 },
                                                                { x + width * (3 - Math.sqrt(5)) / 4, y + height / 2,
                                                                                z },
                                                                { x, y + height * (1 + Math.sqrt(5)) / 4,
                                                                                z + depth / 2 }
                                                },
                                                {
                                                                { x + width / 2, y,
                                                                                z + depth * (3 - Math.sqrt(5)) / 4 },
                                                                { x + width * (3 - Math.sqrt(5)) / 4, y + height / 2,
                                                                                z },
                                                                { x, y + height * (3 - Math.sqrt(5)) / 4,
                                                                                z + depth / 2 }
                                                },
                                                {
                                                                { x + width * (3 - Math.sqrt(5)) / 4, y + height / 2,
                                                                                z },
                                                                { x, y + height * (1 + Math.sqrt(5)) / 4,
                                                                                z + depth / 2 },
                                                                { x, y + height * (3 - Math.sqrt(5)) / 4,
                                                                                z + depth / 2 }
                                                },
                                                {
                                                                { x, y + height * (1 + Math.sqrt(5)) / 4,
                                                                                z + depth / 2 },
                                                                { x + width / 2, y + height,
                                                                                z + depth * (1 + Math.sqrt(5)) / 4 },
                                                                { x + width * (3 - Math.sqrt(5)) / 4, y + height / 2,
                                                                                z + depth }
                                                },
                                                {
                                                                { x + width / 2, y,
                                                                                z + depth * (1 + Math.sqrt(5)) / 4 },
                                                                { x + width * (3 - Math.sqrt(5)) / 4, y + height / 2,
                                                                                z + depth },
                                                                { x, y + height * (3 - Math.sqrt(5)) / 4,
                                                                                z + depth / 2 }
                                                },
                                                {
                                                                { x + width * (3 - Math.sqrt(5)) / 4, y + height / 2,
                                                                                z + depth },
                                                                { x, y + height * (1 + Math.sqrt(5)) / 4,
                                                                                z + depth / 2 },
                                                                { x, y + height * (3 - Math.sqrt(5)) / 4,
                                                                                z + depth / 2 }
                                                }
                                };
                                polygon = new Path2D[20];
                                colors = new Color[] {
                                                Color.RED,
                                                Color.GREEN,
                                                Color.BLUE,
                                                Color.YELLOW,
                                                Color.CYAN,
                                                Color.MAGENTA,
                                                Color.BLACK,
                                                Color.GRAY,
                                                new Color(127, 0, 0, 255), // Dark Red
                                                new Color(0, 127, 0, 255), // Dark Green
                                                new Color(0, 0, 127, 255), // Dark Blue
                                                new Color(127, 127, 0, 255), // Dark Yellow
                                                new Color(0, 127, 127, 255), // Dark Cyan
                                                new Color(127, 0, 127, 255), // Dark Magenta
                                                new Color(255, 127, 127, 255), // Light Red
                                                new Color(127, 255, 127, 255), // Light Green
                                                new Color(127, 127, 255, 255), // Light Blue
                                                new Color(255, 255, 127, 255), // Light Yellow
                                                new Color(127, 255, 255, 255), // Light Cyan
                                                new Color(255, 127, 255, 255) // Light Magenta
                                };
                                break;
                        default:
                                System.out.println("Incorrect String Argument");
                                break;
                }
                for (int i = 0; i < coords.length; i++)
                        regenPolygon(i);
                if (auto)
                        autoCenter();
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
                Path2D[] polygon2 = new Path2D[coords2.length];
                Color[] colors2 = new Color[coords2.length];
                for (int face = 0; face < coords.length; face++) {
                        coords2[face] = coords[face];
                        polygon2[face] = polygon[face];
                        colors2[face] = colors[face];
                }
                coords = coords2;
                polygon = polygon2;
                colors = colors2;
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
                regenPolygon(face);
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

        public void setColor(int face, Color color) {
                colors[face] = color;
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
                        regenPolygon(face);
                }
        }

        protected void regenPolygon(int face) {
                polygon[face] = new Path2D.Double();
                polygon[face].moveTo(coords[face][0][0], coords[face][0][1]);
                for (double[] coord : coords[face])
                        try {
                                polygon[face].lineTo(coord[0], coord[1]);
                        } catch (NullPointerException e) {
                        }
                polygon[face].closePath();
        }

        public double[] compare(JObject other) {
                double[] v1 = new double[3];
                double[] v2 = new double[3];
                double[] max = new double[4];
                double v1mag, v2mag, res = 0;
                for (int face = 0; face < coords.length; face++)
                        for (int point = 0; point < coords[face].length; point++) {
                                v1[0] = coords[face][point][0] - center_x;
                                v1[1] = coords[face][point][1] - center_y;
                                v1[2] = coords[face][point][2] - center_z;
                                v2[0] = other.coords[face][point][0] - other.center_x;
                                v2[1] = other.coords[face][point][1] - other.center_y;
                                v2[2] = other.coords[face][point][2] - other.center_z;
                                v1mag = Math.sqrt(v1[0] * v1[0] + v1[1] * v1[1] + v1[2] * v1[2]);
                                v2mag = Math.sqrt(v2[0] * v2[0] + v2[1] * v2[1] + v2[2] * v2[2]);
                                res = Math.toDegrees(Math.acos(
                                                (v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2]) / (v1mag * v2mag)));
                                if (res >= max[0]) {
                                        max[0] = res;
                                        max[1] = Math.abs(v1[0] - v2[0]);
                                        max[2] = Math.abs(v1[1] - v2[1]);
                                        max[3] = Math.abs(v1[2] - v2[2]);
                                }
                        }
                return max;
        }

        @Override
        public void paint(Graphics g) {
                super.paint(g); // Clear the canvas
                Graphics2D g2D = (Graphics2D) g;
                Boolean[] indeces = new Boolean[coords.length];
                for (int loop = 0; loop < coords.length; loop++) {
                        int current = -1;
                        for (int index = 0; index < coords.length; index++)
                                if (indeces[index] == null && (current == -1
                                                || getDepth(coords[index]) >= getDepth(coords[current])))
                                        current = index;
                        g2D.setColor(colors[current]);
                        if (wireframe)
                                g2D.draw(polygon[current]);
                        else
                                g2D.fill(polygon[current]);
                        indeces[current] = true;
                }
        }

        public void update(double theta_x, double theta_y, double theta_z) {
                rotate(theta_x, theta_y, theta_z);
                repaint();
        }
}
