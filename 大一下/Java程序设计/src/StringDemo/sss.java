package StringDemo;

public class sss {
    public static void main(String[] args){
        String s1 = "abc";
        StringBuffer s2 = new StringBuffer(s1);
        s1.concat("123");
        s2.append("123");
        System.out.println(s1);
        System.out.println(s1.equals(new String("abc")));
        System.out.println(s1==(new String("abc")));
        System.out.println(s2);
    }
}

