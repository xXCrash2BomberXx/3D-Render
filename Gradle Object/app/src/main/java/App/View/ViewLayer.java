package App.View;

import App.Model.J3D;
import App.Model.JObject;
import App.Model.Sprite;

import java.awt.Container;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.util.Arrays;
import javax.swing.JFrame;
import javax.swing.JLayeredPane;
import App.Control.Control;

public class ViewLayer extends JFrame implements View {
    protected JLayeredPane pane = new JLayeredPane();
    protected Container container;

    public ViewLayer(Control control, J3D[] objs) {
        super();
        init(control, objs, 500, 500);
    }

    public ViewLayer(Control control, J3D[] objs, int width, int height) {
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
        pane.setLayout(null);
        pane.setSize(width, height);
        for (J3D o : objs)
            if (o instanceof JObject) {
                pane.add((JObject) o, JLayeredPane.DEFAULT_LAYER);
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
        pane.add(this.container, JLayeredPane.DEFAULT_LAYER);
        add(pane);
        draw(objs);
    }

    public void draw(J3D[] objs) {
        Arrays.sort(objs, (a, b) -> (int) (-a.getDepth() + b.getDepth()));
        for (J3D o : objs)
            if (o instanceof JObject) {
                pane.moveToFront((JObject) o);
                ((JObject) o).repaint();
            }
        pane.moveToFront(container);
        container.repaint();
    }
}
