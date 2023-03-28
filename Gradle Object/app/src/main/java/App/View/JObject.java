package App.View;

// import javax.swing.JFrame;
import java.awt.Color;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.Container;

public class JObject extends Container implements J3D {
    protected Sprite[] sprites = new Sprite[0];
    protected Color[] colors = new Color[0];
    protected Color[] colors2 = new Color[0];
    protected double center_x = 0;
    protected double center_y = 0;
    protected double center_z = 0;
    protected Boolean auto = true;
    public Boolean outer = false;
    public Boolean inner = true;

    public JObject(String obj, double width, double height, double depth) {
        super();
        generate(obj, 0, 0, 0, width, height, depth);
    }

    public JObject(String obj, double width, double height, double depth, Color[] colors) {
        super();
        generate(obj, 0, 0, 0, width, height, depth);
        this.colors = colors;
    }

    public JObject(String obj, double width, double height, double depth, Color[] colors, Color[] colors2) {
        super();
        generate(obj, 0, 0, 0, width, height, depth);
        this.colors = colors;
        outer = true;
        this.colors2 = colors2;
    }

    public JObject(String obj, double width, double height, double depth, Boolean inner) {
        super();
        generate(obj, 0, 0, 0, width, height, depth);
        this.inner = inner;
    }

    public JObject(String obj, double width, double height, double depth, Boolean inner, Boolean outer) {
        super();
        generate(obj, 0, 0, 0, width, height, depth);
        this.inner = inner;
        this.outer = outer;
    }

    public JObject(String obj, double width, double height, double depth, Color[] colors, Boolean outer) {
        super();
        generate(obj, 0, 0, 0, width, height, depth);
        this.colors = colors;
        this.outer = outer;
    }

    public JObject(String obj, double width, double height, double depth, Boolean inner, Color[] colors2) {
        super();
        generate(obj, 0, 0, 0, width, height, depth);
        this.inner = inner;
        outer = true;
        this.colors2 = colors2;
    }

    public JObject(String obj, double x, double y, double z, double width, double height, double depth) {
        super();
        generate(obj, x, y, z, width, height, depth);
    }

    public JObject(String obj, double x, double y, double z, double width, double height, double depth,
            Color[] colors) {
        super();
        generate(obj, x, y, z, width, height, depth);
        this.colors = colors;
    }

    public JObject(String obj, double x, double y, double z, double width, double height, double depth, 
            Color[] colors, Color[] colors2) {
        super();
        generate(obj, x, y, z, width, height, depth);
        this.colors = colors;
        this.outer = true;
        this.colors2 = colors2;
    }

    public JObject(String obj, double x, double y, double z, double width, double height, double depth,
            Boolean inner) {
        super();
        generate(obj, x, y, z, width, height, depth);
        this.inner = inner;
    }

    public JObject(String obj, double x, double y, double z, double width, double height, double depth,
            Boolean inner, Boolean outer) {
        super();
        generate(obj, x, y, z, width, height, depth);
        this.inner = inner;
        this.outer = outer;
    }

    public JObject(String obj, double x, double y, double z, double width, double height, double depth,
            Color[] colors, Boolean outer) {
        super();
        generate(obj, x, y, z, width, height, depth);
        this.colors = colors;
        this.outer = outer;
    }

    public JObject(String obj, double x, double y, double z, double width, double height, double depth,
            Boolean inner, Color[] colors2) {
        super();
        generate(obj, x, y, z, width, height, depth);
        this.inner = inner;
        outer = true;
        this.colors2 = colors2;
    }

    public JObject(String obj, double x, double y, double z, double width, double height, double depth,
            double x_axis, double y_axis, double z_axis) {
        super();
        auto = false;
        center_x = x_axis;
        center_y = y_axis;
        center_z = z_axis;
        generate(obj, x, y, z, width, height, depth);
        for (Sprite sprite : sprites) {
            sprite.setCenter(new double[] { center_x, center_y, center_z });
        }
    }

    public JObject(String obj, double x, double y, double z, double width, double height, double depth,
            double x_axis, double y_axis, double z_axis, Color[] colors) {
        super();
        auto = false;
        center_x = x_axis;
        center_y = y_axis;
        center_z = z_axis;
        generate(obj, x, y, z, width, height, depth);
        for (Sprite sprite : sprites) {
            sprite.setCenter(new double[] { center_x, center_y, center_z });
        }
        this.colors = colors;
    }

    public JObject(String obj, double x, double y, double z, double width, double height, double depth,
            double x_axis, double y_axis, double z_axis, Color[] colors, Color[] colors2) {
        super();
        auto = false;
        center_x = x_axis;
        center_y = y_axis;
        center_z = z_axis;
        generate(obj, x, y, z, width, height, depth);
        for (Sprite sprite : sprites) {
            sprite.setCenter(new double[] { center_x, center_y, center_z });
        }
        this.colors = colors;
        this.outer = true;
        this.colors2 = colors2;
    }

    public JObject(String obj, double x, double y, double z, double width, double height, double depth,
            double x_axis, double y_axis, double z_axis, Boolean inner) {
        super();
        auto = false;
        center_x = x_axis;
        center_y = y_axis;
        center_z = z_axis;
        generate(obj, x, y, z, width, height, depth);
        for (Sprite sprite : sprites) {
            sprite.setCenter(new double[] { center_x, center_y, center_z });
        }
        this.inner = inner;
    }

    public JObject(String obj, double x, double y, double z, double width, double height, double depth,
            double x_axis, double y_axis, double z_axis, Boolean inner, Boolean outer) {
        super();
        auto = false;
        center_x = x_axis;
        center_y = y_axis;
        center_z = z_axis;
        generate(obj, x, y, z, width, height, depth);
        for (Sprite sprite : sprites) {
            sprite.setCenter(new double[] { center_x, center_y, center_z });
        }
        this.inner = inner;
        this.outer = outer;
    }

    public JObject(String obj, double x, double y, double z, double width, double height, double depth,
            double x_axis, double y_axis, double z_axis, Color[] colors, Boolean outer) {
        super();
        auto = false;
        center_x = x_axis;
        center_y = y_axis;
        center_z = z_axis;
        generate(obj, x, y, z, width, height, depth);
        for (Sprite sprite : sprites) {
            sprite.setCenter(new double[] { center_x, center_y, center_z });
        }
        this.colors = colors;
        this.outer = outer;
    }

    public JObject(String obj, double x, double y, double z, double width, double height, double depth,
            double x_axis, double y_axis, double z_axis, Boolean inner, Color[] colors2) {
        super();
        auto = false;
        center_x = x_axis;
        center_y = y_axis;
        center_z = z_axis;
        generate(obj, x, y, z, width, height, depth);
        for (Sprite sprite : sprites) {
            sprite.setCenter(new double[] { center_x, center_y, center_z });
        }
        this.inner = inner;
        outer = true;
        this.colors2 = colors2;
    }

    public JObject(Sprite[] sprites) {
        super();
        setLocation(0, 0);
        this.sprites = sprites;
        autoCenter();
    }

    public JObject(Sprite[] sprites, Color[] colors) {
        super();
        setLocation(0, 0);
        this.sprites = sprites;
        autoCenter();
        this.colors = colors;
    }

    public JObject(Sprite[] sprites, Color[] colors, Color[] colors2) {
        super();
        setLocation(0, 0);
        this.sprites = sprites;
        autoCenter();
        this.colors = colors;
        outer = true;
        this.colors2 = colors2;
    }

    public JObject(Sprite[] sprites, Boolean inner) {
        super();
        setLocation(0, 0);
        this.sprites = sprites;
        autoCenter();
        this.inner = inner;
    }

    public JObject(Sprite[] sprites, Boolean inner, Boolean outer) {
        super();
        setLocation(0, 0);
        this.sprites = sprites;
        autoCenter();
        this.inner = inner;
        this.outer = outer;
    }

    public JObject(Sprite[] sprites, Color[] colors, Boolean outer) {
        super();
        setLocation(0, 0);
        this.sprites = sprites;
        autoCenter();
        this.colors = colors;
        this.outer = outer;
    }

    public JObject(Sprite[] sprites, Boolean inner, Color[] colors2) {
        super();
        setLocation(0, 0);
        this.sprites = sprites;
        autoCenter();
        this.inner = inner;
        outer = true;
        this.colors2 = colors2;
    }

    public JObject(double[][][] obj) {
        super();
        setLocation(0, 0);
        this.sprites = new Sprite[] { new Sprite(obj) };
        autoCenter();
    }

    public JObject(double[][][] obj, Color[] colors) {
        super();
        setLocation(0, 0);
        this.sprites = new Sprite[] { new Sprite(obj) };
        autoCenter();
        this.colors = colors;
    }

    public JObject(double[][][] obj, Color[] colors, Color[] colors2) {
        super();
        setLocation(0, 0);
        this.sprites = new Sprite[] { new Sprite(obj) };
        autoCenter();
        this.colors = colors;
        outer = true;
        this.colors2 = colors2;
    }

    public JObject(double[][][] obj, Boolean inner) {
        super();
        setLocation(0, 0);
        this.sprites = new Sprite[] { new Sprite(obj) };
        autoCenter();
        this.inner = inner;
    }

    public JObject(double[][][] obj, Boolean inner, Boolean outer) {
        super();
        setLocation(0, 0);
        this.sprites = new Sprite[] { new Sprite(obj) };
        autoCenter();
        this.inner = inner;
        this.outer = outer;
    }

    public JObject(double[][][] obj, Color[] colors, Boolean outer) {
        super();
        setLocation(0, 0);
        this.sprites = new Sprite[] { new Sprite(obj) };
        autoCenter();
        this.colors = colors;
        this.outer = outer;
    }

    public JObject(double[][][] obj, Boolean inner, Color[] colors2) {
        super();
        setLocation(0, 0);
        this.sprites = new Sprite[] { new Sprite(obj) };
        autoCenter();
        this.inner = inner;
        outer = true;
        this.colors2 = colors2;
    }

    protected void generate(String obj, double x, double y, double z, double width, double height, double depth) {
        setLocation(0, 0);
        Sprite temp = new Sprite(obj, x, y, z, width, height, depth);
        sprites = new Sprite[temp.getCoords().length];
        for (int i = 0; i < temp.getCoords().length; i++) {
            sprites[i] = new Sprite(new double[][][] { temp.getCoords()[i] });
        }
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
        colors2 = new Color[] {
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
        if (auto)
            autoCenter();
    }

    public void rotate(double theta_x, double theta_y, double theta_z) {
        for (Sprite o : sprites)
            o.rotate(theta_x, theta_y, theta_z);
    }

    public double getDepth() {
        double avg = 0;
        for (Sprite sprite : sprites)
                avg += sprite.getDepth();
        return avg / sprites.length;
        /*
        double min = sprites[0].getDepth();
        double min2;
        for (int i = 1; i < sprites.length; i++) {
            min2 = sprites[i].getDepth();
            if (min2 < min)
                min = min2;
        }
        return min;
        */
    }

    public double[] getCenter() {
        return new double[] { center_x, center_y, center_z };
    }

    public void setPosition(double x, double y, double z) {
        for (Sprite sprite : sprites)
            sprite.setPosition(x, y, z);
    }

    public void movePosition(double x, double y, double z) {
        for (Sprite sprite : sprites)
            sprite.movePosition(x, y, z);
    }

    public void autoCenter() {
        center_x = 0;
        center_y = 0;
        center_z = 0;
        int vertices = 0;
        for (Sprite sprite : sprites) {
            sprite.autoCenter();
            double[] center = sprite.getCenter();
            center_x += center[0];
            center_y += center[1];
            center_z += center[2];
            vertices++;
        }
        center_x /= vertices;
        center_y /= vertices;
        center_z /= vertices;
        for (Sprite sprite : sprites) {
            sprite.setCenter(new double[] { center_x, center_y, center_z });
        }
    }

    @Override
    public void paint(Graphics g) {
        super.paint(g); // Clear the canvas
        Graphics2D g2D = (Graphics2D) g;
        Boolean[] indeces = new Boolean[sprites.length];
        for (int loop = 0; loop < sprites.length; loop++) {
            int current = -1;
            for (int index = 0; index < sprites.length; index++)
                if (indeces[index] == null && (current == -1
                        || sprites[index].getDepth() > sprites[current].getDepth()))
                    current = index;
            if (inner) {
                if (colors.length > 0)
                        g2D.setColor(colors[current % colors.length]);
                else
                        g2D.setColor(Color.BLACK);
                g2D.fill(sprites[current]);
            }
            if (outer) {
                if (colors2.length > 0)
                        g2D.setColor(colors2[current % colors2.length]);
                else
                        g2D.setColor(Color.BLACK);
                g2D.draw(sprites[current]);
            }
            indeces[current] = true;
        }
    }
    /*
    public static void main(String args[]) {
        JFrame frame = new JFrame();
        JObject obj = new JObject("cube", 225, 225, 225, 50, 50, 50);
        obj.setSize(500, 500);
        frame.add(obj);
        frame.setSize(500, 500);
        frame.setVisible(true);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    }
    */
}
