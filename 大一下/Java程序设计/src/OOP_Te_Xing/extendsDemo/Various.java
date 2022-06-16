package OOP_Te_Xing.extendsDemo;

class ball{

    String s = new String("ball2");

    static void print2(){
        System.out.println("ball3");
    }

    public void print(){
        System.out.println("ball" + this.s);
    }
}

class basketBall extends ball {

    String s = new String("basketball2");

    @Override
    public void print() {
        System.out.println("basketball"+this.s);
    }



}

class football extends ball {
    @Override
    public void print() {
        System.out.println("football");
    }
}

class pingpang extends ball {
    @Override
    public void print() {
        System.out.println("pingpang");
    }
}

public class Various {
    public static void main(String[] args) {
        // 3. 向上转型
        ball ba = new basketBall();
        ba.print();

        ba = new football();
        ba.print();

        ba = new pingpang();
        ba.print();

        ba = new ball();
        ba.print();

    }
}

