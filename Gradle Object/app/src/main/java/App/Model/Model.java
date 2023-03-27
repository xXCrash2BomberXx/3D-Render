package App.Model;

import App.Control.Control;
import App.View.J3D;
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

    public Model(Control control, J3D[] objs) {
        view = new ViewLayer(control, objs);
    }

    public Model(Control control, J3D[] objs, int width, int height) {
        view = new ViewLayer(control, objs, width, height);
    }

    public void update(MouseEvent e) {
        Point newPoint = e.getPoint();
        if (lastPoint != null)
            view.rotate(e.getY() - lastPoint.getY(), -e.getX() + lastPoint.getX(), 0);
        lastPoint = newPoint;
    }

    public void update(MouseWheelEvent e) {
        view.rotate(0, 0, e.getPreciseWheelRotation() * sensitivity);
    }
}
