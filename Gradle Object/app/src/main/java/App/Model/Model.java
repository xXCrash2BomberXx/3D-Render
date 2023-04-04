package App.Model;

import App.Control.Control;
import App.View.ViewLayer;
//import App.View.ViewAddRem;
import App.View.View;

import java.awt.Point;
import java.awt.event.MouseEvent;
import java.awt.event.MouseWheelEvent;

public class Model {
    protected Point lastPoint = null;
    protected View view;
    protected int sensitivity = 10;
    protected J3D[] objs;

    public Model(Control control, J3D[] objs) {
        this.objs = objs;
        view = new ViewLayer(control, objs);
    }

    public Model(Control control, J3D[] objs, int width, int height) {
        this.objs = objs;
        view = new ViewLayer(control, objs, width, height);
    }

    public void update(MouseEvent e) {
        Point newPoint = e.getPoint();
        if (lastPoint != null) {
            double theta_x = e.getY() - lastPoint.getY();
            double theta_y = -e.getX() + lastPoint.getX();
            for (J3D o : objs)
                o.irotate(theta_x, theta_y, 0);
            view.draw(objs);
        }
        lastPoint = newPoint;
    }

    public void update(MouseWheelEvent e) {
        double theta_z = e.getPreciseWheelRotation() * sensitivity;
        for (J3D o : objs)
            o.irotate(0, 0, theta_z);
        view.draw(objs);
    }
}
