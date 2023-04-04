package App.Model;

public interface J3D {
    public void rotate(double theta_x, double theta_y, double theta_z);

    public void irotate(double theta_x, double theta_y, double theta_z);

    public double getDepth();

    public double[] getCenter();

    public double[] calcCenter();
}
