package clone;

public class CHAR implements Cloneable {
    String s;
    int a;

    public CHAR(String s, int a) {
        this.s = s;
        this.a = a;
    }

    public Object clone() {
        try {
            return super.clone();
        } catch (CloneNotSupportedException cse) {
        }
        return null;
    }

    public static void main(String[] args){
        CHAR ob1=new CHAR("ABCD",10);
        CHAR ob2=(CHAR)ob1.clone();
        System.out.println("原本："+ob1.hashCode());
        System.out.println("副本："+ob2.hashCode());
    }
}
