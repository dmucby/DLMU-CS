package OOP_Te_Xing.extendsDemo;

/**
 * 变量
 */
public class F {
    public static void main(String[] args){
            A a=new A();
            B b=new B();
            b.i=3;
            System.out.println(a.i);
            System.out.println(b.i);
    }
}

class A {
    // static
    public  int i = 1;
    //int i = 1;
}

class B extends A{

}



