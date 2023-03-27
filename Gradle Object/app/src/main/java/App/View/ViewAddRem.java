package App.View;

import java.awt.Container;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.util.Arrays;

import javax.swing.JFrame;
import App.Control.Control;

public class ViewAddRem extends JFrame implements View {
    protected J3D[] objs;
    protected Container container;

    public ViewAddRem(Control control, J3D[] objs) {
        super();
        init(control, objs, 500, 500);
    }

    public ViewAddRem(Control control, J3D[] objs, int width, int height) {
        super();
        init(control, objs, width, height);
    }

    protected void init(Control control, J3D[] objs, int width, int height) {
        setLayout(null);
        setSize(width, height);
        setVisible(true);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        addMouseMotionListener(control);
        addMouseWheelListener(control);
        this.objs = objs;
        for (J3D o : objs)
            if (o instanceof JObject) {
                add((JObject) o);
                ((JObject) o).setSize(width, height);
            }
        this.container = new Container() {
            @Override
            public void paint(Graphics g) {
                super.paint(g);
                Graphics2D g2 = (Graphics2D) g;
                for (J3D o : objs)
                    if (o instanceof Sprite)
                        g2.draw((Sprite) o);
            }
        };
        container.setSize(width, height);
        add(container);
        rotate(0, 0, 0);
    }

    public void rotate(double theta_x, double theta_y, double theta_z) {
        remove(container);
        for (J3D o : objs) {
            if (o instanceof JObject)
                remove((JObject) o);
            o.rotate(theta_x, theta_y, theta_z);
        }
        Arrays.sort(objs, (a, b) -> (int) (a.getDepth() - b.getDepth()));
        for (J3D o : objs) {
            if (o instanceof JObject) {
                add((JObject) o);
                ((JObject) o).repaint();
            }
        }
        add(container);
        container.repaint();
    }
}
