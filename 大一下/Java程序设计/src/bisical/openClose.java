package bisical;

abstract class Geometry
{
    public abstract double getArea();
}
class Lader extends Geometry
{  double a,b,h;
    Lader(double a,double b,double h)
    {   this.a=a;this.b=b;this.h=h;
    }
    public double getArea()
    {   return((1/2.0)*(a+b)*h);
    }
}
class Circle extends Geometry
{   double r;
    Circle(double r)
    { this.r=r;
    }
    public double getArea()
    {  return(3.14*r*r);
    }
}
class Cone//椎体
{
    Geometry bottom;
    double height;
    Cone (Geometry bottom,double height)
    {
        this.bottom=bottom;
        this.height=height;
    }
    void changeBottom(Geometry bottom)
    {  this.bottom=bottom;
    }
    public double getVolume()
    {
        return (bottom.getArea()*height)/3.0;
    }
}


public class openClose {
    public static void main(String args[])
    {
        Cone zui;

        Geometry tuxing;
        tuxing=new Lader(2.0,7.0,10.7);
        System.out.println("梯形的面积"+tuxing.getArea());
        zui=new Cone(tuxing,30);
        System.out.println("梯形底的锥的体积"+zui.getVolume());
        tuxing=new Circle(10);
        System.out.println("半径是10的圆的面积"+tuxing.getArea());
        zui.changeBottom(tuxing);
        System.out.println("圆形底的锥的体积"+zui.getVolume());
    }
}

