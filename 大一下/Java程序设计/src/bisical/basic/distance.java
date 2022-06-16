package bisical.basic;

class Point{
    int x;int y;
    Point(int x,int y){//构造方法
        this.x=x;this.y=y;}
    double distance(Point p){
        double d=Math.sqrt((x-p.x)*(x-p.x)+(y-p.y)*(y-p.y));
        return d;}
}
public class distance {
    public static void main(String[] args) {
        Point op1=new Point(2,3);Point op2=new Point(3,4);
        System.out.println(op1.distance(op2));}
}
