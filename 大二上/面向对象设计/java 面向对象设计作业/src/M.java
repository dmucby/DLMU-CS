import java.util.Vector;

public class M {
    public static void main(String[] args){
        Mul o1 = new Mul(3,5);
        //System.out.println(o1.res);
        Mul o2 = new Mul(6,4);
        //System.out.println(o2.res);
        Add o3 = new Add(2,o1);
        //System.out.println(o3.res);
        Add o4 = new Add(o3,o2);
        System.out.println(o4.getValue());
    }
}

class Four{
    double x1,x2,x3,x4;
    double res;

    Mul mul;
    Div div;
    Add add;
    Min min;

}

class Two extends Four{}

class Number extends Two{}

class Mul extends Two{
    Two two = new Two();
    Vector<Two> twos = new Vector<>();

    public Mul(double x1,double x2){
        this.x1 = x1;
        this.x2 = x2;

        this.res = this.x1 * this.x2;

        two.res = this.res;
        twos.add(two);
    }

    public double getValue(){
        return this.res;
    }
}

class Div extends Two{
    Two two = new Two();
    Vector<Two> twos = new Vector<>();

    public Div(double x1,double x2){
        this.x1 = x1;
        this.x2 = x2;

        this.res = this.x1 / this.x2;

        two.res = this.res;
        twos.add(two);
    }

    public double getValue(){
        return this.res;
    }
}

class Add extends Four{
    Four four = new Four();

    Vector<Four> fours = new Vector<>();

    public Add(double x,Mul mul){
        this.x3 = x;
        this.x4 = mul.res;

        this.res = this.x3 + this.x4;

        four.res = this.res;
        fours.add(four);
    }

    public Add(Add add,Mul mul){
        this.x3 = add.res;
        this.x4 = mul.res;

        this.res = this.x3 + this.x4;

        four.res = this.res;
        fours.add(four);
    }

    public double getValue(){
        return this.res;
    }
}

class Min extends Four{
    Four four = new Four();

    Vector<Four> fours = new Vector<>();

    public Min(double x,Mul mul){
        this.x3 = x;
        this.x4 = mul.res;

        this.res = this.x3 - this.x4;

        four.res = this.res;
        fours.add(four);
    }

    public Min(Add add,Mul mul){
        this.x3 = add.res;
        this.x4 = mul.res;

        this.res = this.x3 - this.x4;

        four.res = this.res;
        fours.add(four);
    }

    public double getValue(){
        return this.res;
    }
}