import javax.swing.JPanel;
import javax.swing.JFrame;
import java.awt.Color;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.lang.Math;

import javax.swing.SwingUtilities;
import java.awt.MouseInfo;
import java.awt.Point;
import java.awt.geom.Path2D;

class Object extends JPanel {
    private Point lastPoint;
    private Double[][][] coords = new Double[0][0][3];  // [faces][lines][coordinates]
    private Path2D[] polygon = new Path2D[0];  // [faces]
    private Color[] colors = new Color[0];  // [colors]
    private double center_x = 0;
    private double center_y = 0;
    private double center_z = 0;
    private Boolean auto = true;
    public Boolean wireframe = false;
    public Object (String obj, double x, double y, double z, double width, double height, double depth) {
        super();
        generate(obj, x, y, z, width, height, depth);
    }
    public Object (String obj, double x, double y, double z, double width, double height, double depth, Boolean wire) {
        super();
        generate(obj, x, y, z, width, height, depth);
        wireframe = wire;
    }
    public Object (String obj, double x, double y, double z, double width, double height, double depth, double x_axis, double y_axis, double z_axis) {
        super();
        generate(obj, x, y, z, width, height, depth);
        auto = false;
        center_x = x_axis;
        center_y = y_axis;
        center_z = z_axis;
    }
    public Object (String obj, double x, double y, double z, double width, double height, double depth, double x_axis, double y_axis, double z_axis, Boolean wire) {
        super();
        generate(obj, x, y, z, width, height, depth);
        auto = false;
        center_x = x_axis;
        center_y = y_axis;
        center_z = z_axis;
        wireframe = wire;
    }
    public Object (Double[][][] obj) {
        super();
        coords = obj;
        for (int i = 0; i < coords.length; i++)
            regenPolygon(i);
    }
    private void generate (String obj, double x, double y, double z, double width, double height, double depth) {
        switch (obj) {
            case "cube":
                addPoint(0, x, y, z);
                addPoint(0, x+width, y, z);
                addPoint(0, x+width, y+height, z);
                addPoint(0, x, y+height, z);
                setColor(0, Color.RED);  // Red
            
                addPoint(1, x, y, z);
                addPoint(1, x, y, z+depth);
                addPoint(1, x, y+height, z+depth);
                addPoint(1, x, y+height, z);
                setColor(1, Color.GREEN);  // Green
            
                addPoint(2, x, y+height, z);
                addPoint(2, x, y+height, z+depth);
                addPoint(2, x+width, y+height, z+depth);
                addPoint(2, x+width, y+height, z);
                setColor(2, Color.BLUE);  // Blue
            
                addPoint(3, x+width, y+height, z);
                addPoint(3, x+width, y+height, z+depth);
                addPoint(3, x+width, y, z+depth);
                addPoint(3, x+width, y, z);
                setColor(3, Color.YELLOW);  // Yellow
            
                addPoint(4, x+width, y, z);
                addPoint(4, x, y, z);
                addPoint(4, x, y, z+depth);
                addPoint(4, x+width, y, z+depth);
                setColor(4, Color.CYAN);  // Cyan
            
                addPoint(5, x+width, y, z+depth);
                addPoint(5, x+width, y+height, z+depth);
                addPoint(5, x, y+height, z+depth);
                addPoint(5, x, y, z+depth);
                setColor(5, Color.MAGENTA);  // Magenta
                break;
            case "tetrahedron":
                addPoint(0, x+width, y+height, z+depth);
                addPoint(0, x+width, y, z);
                addPoint(0, x, y+height, z);
                setColor(0, Color.RED);  // Red
            
                addPoint(1, x+width, y+height, z+depth);
                addPoint(1, x+width, y, z);
                addPoint(1, x, y, z+depth);
                setColor(1, Color.GREEN);  // Green
            
                addPoint(2, x+width, y+height, z+depth);
                addPoint(2, x, y+height, z);
                addPoint(2, x, y, z+depth);
                setColor(2, Color.BLUE);  // Blue
            
                addPoint(3, x+width, y, z);
                addPoint(3, x, y+height, z);
                addPoint(3, x, y, z+depth);
                setColor(3, Color.YELLOW);  // Yellow
                break;
            case "octahedron":
                addPoint(0, x, y+height/2, z+depth/2);
                addPoint(0, x+width/2, y, z+depth/2);
                addPoint(0, x+width/2, y+height/2, z);
                setColor(0, Color.RED);  // Red
                
                addPoint(1, x, y+height/2, z+depth/2);
                addPoint(1, x+width/2, y, z+depth/2);
                addPoint(1, x+width/2, y+height/2, z+depth);
                setColor(1, Color.GREEN);  // Green
            
                addPoint(2, x+width, y+height/2, z+depth/2);
                addPoint(2, x+width/2, y, z+depth/2);
                addPoint(2, x+width/2, y+height/2, z);
                setColor(2, Color.BLUE);  // Blue
            
                addPoint(3, x+width, y+height/2, z+depth/2);
                addPoint(3, x+width/2, y, z+depth/2);
                addPoint(3, x+width/2, y+height/2, z+depth);
                setColor(3, Color.YELLOW);  // Yellow
            
                addPoint(4, x, y+height/2, z+depth/2);
                addPoint(4, x+width/2, y+height, z+depth/2);
                addPoint(4, x+width/2, y+height/2, z);
                setColor(4, Color.CYAN);  // Cyan
            
                addPoint(5, x, y+height/2, z+depth/2);
                addPoint(5, x+width/2, y+height, z+depth/2);
                addPoint(5, x+width/2, y+height/2, z+depth);
                setColor(5, Color.MAGENTA);  // Magenta
            
                addPoint(6, x+width, y+height/2, z+depth/2);
                addPoint(6, x+width/2, y+height, z+depth/2);
                addPoint(6, x+width/2, y+height/2, z);
                setColor(6, Color.BLACK);  // Black
            
                addPoint(7, x+width, y+height/2, z+depth/2);
                addPoint(7, x+width/2, y+height, z+depth/2);
                addPoint(7, x+width/2, y+height/2, z+depth);
                setColor(7, Color.GRAY);  // Gray
                break;
            case "dodecahedron":
                addPoint(0, x+width*(3-Math.sqrt(5))/4, y+height*(3-Math.sqrt(5))/4, z+depth*(3-Math.sqrt(5))/4);
                addPoint(0, x+width/2, y, z+depth*(Math.sqrt(5)-1)/4);
                addPoint(0, x+width/2, y, z+depth*(5-Math.sqrt(5))/4);
                addPoint(0, x+width*(3-Math.sqrt(5))/4, y+height*(3-Math.sqrt(5))/4, z+depth*(1+Math.sqrt(5))/4);
                addPoint(0, x, y+height*(Math.sqrt(5)-1)/4, z+depth/2);
                setColor(0, Color.RED);  // Red
            
                addPoint(1, x+width*(1+Math.sqrt(5))/4, y+height*(3-Math.sqrt(5))/4, z+depth*(3-Math.sqrt(5))/4);
                addPoint(1, x+width/2, y, z+depth*(Math.sqrt(5)-1)/4);
                addPoint(1, x+width/2, y, z+depth*(5-Math.sqrt(5))/4);
                addPoint(1, x+width*(1+Math.sqrt(5))/4, y+height*(3-Math.sqrt(5))/4, z+depth*(1+Math.sqrt(5))/4);
                addPoint(1, x+width, y+height*(Math.sqrt(5)-1)/4, z+depth/2);
                setColor(1, Color.GREEN);  // Green
            
                addPoint(2, x+width*(3-Math.sqrt(5))/4, y+height*(3-Math.sqrt(5))/4, z+depth*(1+Math.sqrt(5))/4);
                addPoint(2, x+width/2, y, z+depth*(5-Math.sqrt(5))/4);
                addPoint(2, x+width*(1+Math.sqrt(5))/4, y+height*(3-Math.sqrt(5))/4, z+depth*(1+Math.sqrt(5))/4);
                addPoint(2, x+width*(5-Math.sqrt(5))/4, y+height/2, z+depth);
                addPoint(2, x+width*(Math.sqrt(5)-1)/4, y+height/2, z+depth);
                setColor(2, Color.BLUE);  // Blue
            
                addPoint(3, x+width*(3-Math.sqrt(5))/4, y+height*(3-Math.sqrt(5))/4, z+depth*(3-Math.sqrt(5))/4);
                addPoint(3, x+width/2, y, z+depth*(Math.sqrt(5)-1)/4);
                addPoint(3, x+width*(1+Math.sqrt(5))/4, y+height*(3-Math.sqrt(5))/4, z+depth*(3-Math.sqrt(5))/4);
                addPoint(3, x+width*(5-Math.sqrt(5))/4, y+height/2, z);
                addPoint(3, x+width*(Math.sqrt(5)-1)/4, y+height/2, z);
                setColor(3, Color.YELLOW);  // Yellow
            
                addPoint(4, x+width*(3-Math.sqrt(5))/4, y+height*(1+Math.sqrt(5))/4, z+depth*(3-Math.sqrt(5))/4);
                addPoint(4, x+width/2, y+height, z+depth*(Math.sqrt(5)-1)/4);
                addPoint(4, x+width/2, y+height, z+depth*(5-Math.sqrt(5))/4);
                addPoint(4, x+width*(3-Math.sqrt(5))/4, y+height*(1+Math.sqrt(5))/4, z+depth*(1+Math.sqrt(5))/4);
                addPoint(4, x, y+height*(5-Math.sqrt(5))/4, z+depth/2);
                setColor(4, Color.CYAN);  // Cyan
            
                addPoint(5, x+width*(1+Math.sqrt(5))/4, y+height*(1+Math.sqrt(5))/4, z+depth*(3-Math.sqrt(5))/4);
                addPoint(5, x+width/2, y+height, z+depth*(Math.sqrt(5)-1)/4);
                addPoint(5, x+width/2, y+height, z+depth*(5-Math.sqrt(5))/4);
                addPoint(5, x+width*(1+Math.sqrt(5))/4, y+height*(1+Math.sqrt(5))/4, z+depth*(1+Math.sqrt(5))/4);
                addPoint(5, x+width, y+height*(5-Math.sqrt(5))/4, z+depth/2);
                setColor(5, Color.MAGENTA);  // Magenta
            
                addPoint(6, x+width*(3-Math.sqrt(5))/4, y+height*(1+Math.sqrt(5))/4, z+depth*(1+Math.sqrt(5))/4);
                addPoint(6, x+width/2, y+height, z+depth*(5-Math.sqrt(5))/4);
                addPoint(6, x+width*(1+Math.sqrt(5))/4, y+height*(1+Math.sqrt(5))/4, z+depth*(1+Math.sqrt(5))/4);
                addPoint(6, x+width*(5-Math.sqrt(5))/4, y+height/2, z+depth);
                addPoint(6, x+width*(Math.sqrt(5)-1)/4, y+height/2, z+depth);
                setColor(6, Color.BLACK);  // Black
            
                addPoint(7, x+width*(3-Math.sqrt(5))/4, y+height*(1+Math.sqrt(5))/4, z+depth*(3-Math.sqrt(5))/4);
                addPoint(7, x+width/2, y+height, z+depth*(Math.sqrt(5)-1)/4);
                addPoint(7, x+width*(1+Math.sqrt(5))/4, y+height*(1+Math.sqrt(5))/4, z+depth*(3-Math.sqrt(5))/4);
                addPoint(7, x+width*(5-Math.sqrt(5))/4, y+height/2, z);
                addPoint(7, x+width*(Math.sqrt(5)-1)/4, y+height/2, z);
                setColor(7, Color.GRAY);  // Gray
            
                addPoint(8, x+width*(1+Math.sqrt(5))/4, y+height*(3-Math.sqrt(5))/4, z+depth*(3-Math.sqrt(5))/4);
                addPoint(8, x+width*(5-Math.sqrt(5))/4, y+height/2, z);
                addPoint(8, x+width*(1+Math.sqrt(5))/4, y+height*(1+Math.sqrt(5))/4, z+depth*(3-Math.sqrt(5))/4);
                addPoint(8, x+width, y+height*(5-Math.sqrt(5))/4, z+depth/2);
                addPoint(8, x+width, y+height*(Math.sqrt(5)-1)/4, z+depth/2);
                setColor(8, new Color(127, 0, 0, 255));  // Dark Red
            
                addPoint(9, x+width*(1+Math.sqrt(5))/4, y+height*(3-Math.sqrt(5))/4, z+depth*(1+Math.sqrt(5))/4);
                addPoint(9, x+width*(5-Math.sqrt(5))/4, y+height/2, z+depth);
                addPoint(9, x+width*(1+Math.sqrt(5))/4, y+height*(1+Math.sqrt(5))/4, z+depth*(1+Math.sqrt(5))/4);
                addPoint(9, x+width, y+height*(5-Math.sqrt(5))/4, z+depth/2);
                addPoint(9, x+width, y+height*(Math.sqrt(5)-1)/4, z+depth/2);
                setColor(9, new Color(0, 127, 0, 255));  // Dark Green
            
                addPoint(10, x+width*(3-Math.sqrt(5))/4, y+height*(3-Math.sqrt(5))/4, z+depth*(3-Math.sqrt(5))/4);
                addPoint(10, x+width*(Math.sqrt(5)-1)/4, y+height/2, z);
                addPoint(10, x+width*(3-Math.sqrt(5))/4, y+height*(1+Math.sqrt(5))/4, z+depth*(3-Math.sqrt(5))/4);
                addPoint(10, x, y+height*(5-Math.sqrt(5))/4, z+depth/2);
                addPoint(10, x, y+height*(Math.sqrt(5)-1)/4, z+depth/2);
                setColor(10, new Color(0, 0, 127, 255));  // Dark Blue
            
                addPoint(11, x+width*(3-Math.sqrt(5))/4, y+height*(3-Math.sqrt(5))/4, z+depth*(1+Math.sqrt(5))/4);
                addPoint(11, x+width*(Math.sqrt(5)-1)/4, y+height/2, z+depth);
                addPoint(11, x+width*(3-Math.sqrt(5))/4, y+height*(1+Math.sqrt(5))/4, z+depth*(1+Math.sqrt(5))/4);
                addPoint(11, x, y+height*(5-Math.sqrt(5))/4, z+depth/2);
                addPoint(11, x, y+height*(Math.sqrt(5)-1)/4, z+depth/2);
                setColor(11, new Color(127, 127, 0, 255));  // Dark Yellow
                break;
            case "icosahedron":
                addPoint(0, x+width/2, y, z+depth*(3-Math.sqrt(5))/4);
                addPoint(0, x+width*(3-Math.sqrt(5))/4, y+height/2, z);
                addPoint(0, x+width*(1+Math.sqrt(5))/4, y+height/2, z);
                setColor(0, Color.RED);  // Red
            
                addPoint(1, x+width/2, y+height, z+depth*(3-Math.sqrt(5))/4);
                addPoint(1, x+width*(3-Math.sqrt(5))/4, y+height/2, z);
                addPoint(1, x+width*(1+Math.sqrt(5))/4, y+height/2, z);
                setColor(1, Color.GREEN);  // Green
            
                addPoint(2, x+width/2, y+height, z+depth*(3-Math.sqrt(5))/4);
                addPoint(2, x+width*(1+Math.sqrt(5))/4, y+height/2, z);
                addPoint(2, x+width, y+height*(1+Math.sqrt(5))/4, z+depth/2);
                setColor(2, Color.BLUE);  // Blue
            
                addPoint(3, x+width/2, y, z+depth*(3-Math.sqrt(5))/4);
                addPoint(3, x+width*(1+Math.sqrt(5))/4, y+height/2, z);
                addPoint(3, x+width, y+height*(3-Math.sqrt(5))/4, z+depth/2);
                setColor(3, Color.YELLOW);  // Yellow
            
                addPoint(4, x+width*(1+Math.sqrt(5))/4, y+height/2, z);
                addPoint(4, x+width, y+height*(1+Math.sqrt(5))/4, z+depth/2);
                addPoint(4, x+width, y+height*(3-Math.sqrt(5))/4, z+depth/2);
                setColor(4, Color.CYAN);  // Cyan
            
                addPoint(5, x+width/2, y+height, z+depth*(1+Math.sqrt(5))/4);
                addPoint(5, x+width/2, y+height, z+depth*(3-Math.sqrt(5))/4);
                addPoint(5, x+width, y+height*(1+Math.sqrt(5))/4, z+depth/2);
                setColor(5, Color.MAGENTA);  // Magenta
            
                addPoint(6, x+width/2, y+height, z+depth*(1+Math.sqrt(5))/4);
                addPoint(6, x+width/2, y+height, z+depth*(3-Math.sqrt(5))/4);
                addPoint(6, x, y+height*(1+Math.sqrt(5))/4, z+depth/2);
                setColor(6, Color.BLACK);  // Black
            
                addPoint(7, x+width*(1+Math.sqrt(5))/4, y+height/2, z+depth);
                addPoint(7, x+width, y+height*(1+Math.sqrt(5))/4, z+depth/2);
                addPoint(7, x+width, y+height*(3-Math.sqrt(5))/4, z+depth/2);
                setColor(7, Color.GRAY);  // Gray
            
                addPoint(8, x+width/2, y, z+depth*(1+Math.sqrt(5))/4);
                addPoint(8, x+width*(3-Math.sqrt(5))/4, y+height/2, z+depth);
                addPoint(8, x+width*(1+Math.sqrt(5))/4, y+height/2, z+depth);
                setColor(8, new Color(127, 0, 0, 255));  // Dark Red
            
                addPoint(9, x+width/2, y+height, z+depth*(1+Math.sqrt(5))/4);
                addPoint(9, x+width*(3-Math.sqrt(5))/4, y+height/2, z+depth);
                addPoint(9, x+width*(1+Math.sqrt(5))/4, y+height/2, z+depth);
                setColor(9, new Color(0, 127, 0, 255));  // Dark Green
            
                addPoint(10, x+width, y+height*(1+Math.sqrt(5))/4, z+depth/2);
                addPoint(10, x+width/2, y+height, z+depth*(1+Math.sqrt(5))/4);
                addPoint(10, x+width*(1+Math.sqrt(5))/4, y+height/2, z+depth);
                setColor(10, new Color(0, 0, 127, 255));  // Dark Blue
            
                addPoint(11, x+width/2, y, z+depth*(1+Math.sqrt(5))/4);
                addPoint(11, x+width*(1+Math.sqrt(5))/4, y+height/2, z+depth);
                addPoint(11, x+width, y+height*(3-Math.sqrt(5))/4, z+depth/2);
                setColor(11, new Color(127, 127, 0, 255));  // Dark Yellow
            
                addPoint(12, x+width/2, y, z+depth*(1+Math.sqrt(5))/4);
                addPoint(12, x+width/2, y, z+depth*(3-Math.sqrt(5))/4);
                addPoint(12, x+width, y+height*(3-Math.sqrt(5))/4, z+depth/2);
                setColor(12, new Color(0, 127, 127, 255));  // Darl Cyan
            
                addPoint(13, x+width/2, y, z+depth*(1+Math.sqrt(5))/4);
                addPoint(13, x+width/2, y, z+depth*(3-Math.sqrt(5))/4);
                addPoint(13, x, y+height*(3-Math.sqrt(5))/4, z+depth/2);
                setColor(13, new Color(127, 0, 127, 255));  // Dark Magenta
            
                addPoint(14, x+width/2, y+height, z+depth*(3-Math.sqrt(5))/4);
                addPoint(14, x+width*(3-Math.sqrt(5))/4, y+height/2, z);
                addPoint(14, x, y+height*(1+Math.sqrt(5))/4, z+depth/2);
                setColor(14, new Color(255, 127, 127, 255));  // Light Red
            
                addPoint(15, x+width/2, y, z+depth*(3-Math.sqrt(5))/4);
                addPoint(15, x+width*(3-Math.sqrt(5))/4, y+height/2, z);
                addPoint(15, x, y+height*(3-Math.sqrt(5))/4, z+depth/2);
                setColor(15, new Color(127, 255, 127, 255));  // Light Green
            
                addPoint(16, x+width*(3-Math.sqrt(5))/4, y+height/2, z);
                addPoint(16, x, y+height*(1+Math.sqrt(5))/4, z+depth/2);
                addPoint(16, x, y+height*(3-Math.sqrt(5))/4, z+depth/2);
                setColor(16, new Color(127, 127, 255, 255));  // Light Blue
            
                addPoint(17, x, y+height*(1+Math.sqrt(5))/4, z+depth/2);
                addPoint(17, x+width/2, y+height, z+depth*(1+Math.sqrt(5))/4);
                addPoint(17, x+width*(3-Math.sqrt(5))/4, y+height/2, z+depth);
                setColor(17, new Color(255, 255, 127, 255));  // Light Yellow
            
                addPoint(18, x+width/2, y, z+depth*(1+Math.sqrt(5))/4);
                addPoint(18, x+width*(3-Math.sqrt(5))/4, y+height/2, z+depth);
                addPoint(18, x, y+height*(3-Math.sqrt(5))/4, z+depth/2);
                setColor(18, new Color(127, 255, 255, 255));  // Light Cyan
            
                addPoint(19, x+width*(3-Math.sqrt(5))/4, y+height/2, z+depth);
                addPoint(19, x, y+height*(1+Math.sqrt(5))/4, z+depth/2);
                addPoint(19, x, y+height*(3-Math.sqrt(5))/4, z+depth/2);
                setColor(19, new Color(255, 127, 255, 255));  // Light Magenta
                break;
            default:
                System.out.println("Incorrect String Argument");
        }
    }
    public static double getDepth (Double[][] face) {
        double avg = 0;
        for (Double[] i : face) {
            try {
                avg += i[2];
            } catch (NullPointerException e) {}
        }
        return avg/face.length;
    }
    public void rotatePoint (Double[] vec, double theta_x, double theta_y, double theta_z) {
        double x = vec[0]*Math.cos(theta_z*Math.PI/180)*Math.cos(theta_y*Math.PI/180) + 
            vec[1]*Math.cos(theta_z*Math.PI/180)*Math.sin(theta_y*Math.PI/180)*Math.sin(theta_x*Math.PI/180) - 
            vec[1]*Math.sin(theta_z*Math.PI/180)*Math.cos(theta_x*Math.PI/180) + 
            vec[2]*Math.cos(theta_z*Math.PI/180)*Math.sin(theta_y*Math.PI/180)*Math.cos(theta_x*Math.PI/180) + 
            vec[2]*Math.sin(theta_z*Math.PI/180)*Math.sin(theta_x*Math.PI/180);
        double y = vec[0]*Math.sin(theta_z*Math.PI/180)*Math.cos(theta_y*Math.PI/180) + 
            vec[1]*Math.sin(theta_z*Math.PI/180)*Math.sin(theta_y*Math.PI/180)*Math.sin(theta_x*Math.PI/180) + 
            vec[1]*Math.cos(theta_z*Math.PI/180)*Math.cos(theta_x*Math.PI/180) + 
            vec[2]*Math.sin(theta_z*Math.PI/180)*Math.sin(theta_y*Math.PI/180)*Math.cos(theta_x*Math.PI/180) - 
            vec[2]*Math.cos(theta_z*Math.PI/180)*Math.sin(theta_x*Math.PI/180);
        double z = -vec[0]*Math.sin(theta_y*Math.PI/180) + 
            vec[1]*Math.cos(theta_y*Math.PI/180)*Math.sin(theta_x*Math.PI/180) + 
            vec[2]*Math.cos(theta_y*Math.PI/180)*Math.cos(theta_x*Math.PI/180);
        vec[0] = x;
        vec[1] = y;
        vec[2] = z;
    }
    private void increaseFaces () {
        Double[][][] coords2 = new Double[coords.length+1][coords.length==0?1:coords[0].length][3];
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
    private void increasePoints () {
        Double[][][] coords2 = new Double[coords.length][coords[0].length+1][3];
        for (int face = 0; face < coords.length; face++) {
            Double[][] face2 = new Double[coords[0].length+1][3];
            for (int point = 0; point < coords[face].length; point++) {
                face2[point] = coords[face][point];
            }
            coords2[face] = face2;
        }
        coords = coords2;
    }
    public void setPoint (int face, int index, double x, double y, double z) {
        if (face >= coords.length) {
            increaseFaces();
        }
        if (index >= coords[0].length) {
            increasePoints();
        }
        coords[face][index][0] = x;
        coords[face][index][1] = y;
        coords[face][index][2] = z;
        regenPolygon(face);
        if (auto)
            autoCenter();
    }
    public void addPoint (int face, double x, double y, double z) {
        setPoint(face, (coords.length == 0 || coords.length <= face ? 0 : coords[face].length), x, y, z);
    }
    public void setPosition (double x, double y, double z) {
        for (int face = 0; face < coords.length; face++) {
            for (int point = 0; point < coords[face].length; point++) {
                coords[face][point][0] += (x - center_x);
                coords[face][point][1] += (y - center_y);
                coords[face][point][2] += (z - center_z);
            }
        }
    }
    public void movePosition (double x, double y, double z) {
        for (int face = 0; face < coords.length; face++) {
            for (int point = 0; point < coords[face].length; point++) {
                coords[face][point][0] += x;
                coords[face][point][1] += y;
                coords[face][point][2] += z;
            }
        }
    }
    public void setColor (int face, Color color) {
        colors[face] = color;
    }
    public void autoCenter () {
        center_x = 0;
        center_y = 0;
        center_z = 0;
        int vertices = 0;
        for (Double[][] face : coords) {
            for (Double[] i : face) {
                try {
                    center_x += i[0];
                    center_y += i[1];
                    center_z += i[2];
                    vertices++;
                } catch (NullPointerException e) {}
            }
        }
        center_x /= vertices;
        center_y /= vertices;
        center_z /= vertices;
    }
    public void rotate (double theta_x, double theta_y, double theta_z) {
        for (int face = 0; face < coords.length; face++) {
            for (int point = 0; point < coords[face].length; point++) {
                try {
                    coords[face][point][0] -= center_x;
                    coords[face][point][1] -= center_y;
                    coords[face][point][2] -= center_z;
                    rotatePoint(coords[face][point], theta_x, theta_y, theta_z);
                    coords[face][point][0] += center_x;
                    coords[face][point][1] += center_y;
                    coords[face][point][2] += center_z;
                } catch (NullPointerException e) {}
            }
            regenPolygon(face);
        }
    }
    private void regenPolygon (int face) {
        polygon[face] = new Path2D.Double();
        polygon[face].moveTo(coords[face][0][0], coords[face][0][1]);
        for (Double[] coord : coords[face]) {
            try {
                polygon[face].lineTo(coord[0], coord[1]);
            } catch (NullPointerException e) {}
        }
        polygon[face].closePath();
    }
    @Override
    public void paint (Graphics g) {
        super.paint(g);  // Clear the canvas
        Point point = MouseInfo.getPointerInfo().getLocation();  // Get mouse location
        SwingUtilities.convertPointFromScreen(point, this);  // Convert points to relative to panel
        if (lastPoint != null) {
            rotate(point.getY()-lastPoint.getY(), -point.getX()+lastPoint.getX(), 0);
            Graphics2D g2D = (Graphics2D) g;

            Boolean[] indeces = new Boolean[coords.length];
            for (int loop = 0; loop < coords.length; loop++) {
                int current = -1;
                for (int index = 0; index < coords.length; index++) {
                    if (indeces[index] == null && (current == -1 || getDepth(coords[index]) >= getDepth(coords[current])))
                        current = index;
                }
                g2D.setColor(colors[current]);
                if (wireframe)
                    g2D.draw(polygon[current]);
                else
                    g2D.fill(polygon[current]);
                indeces[current] = true;
            }
        }
        lastPoint = point;
        repaint();
    }
    public static void main (String[] args) {
        JFrame frame = new JFrame("Movement");
        frame.add(new Object("icosahedron", 200, 200, 50, 50, 50, 50));
        frame.setSize(500, 500);
        frame.setVisible(true);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    }
}
