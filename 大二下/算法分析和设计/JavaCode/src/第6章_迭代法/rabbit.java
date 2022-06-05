package 第6章_迭代法;

/**
 * 6.2 递推法
 * 兔子繁殖问题
 */
public class rabbit {
    public static void main(String[] args) {
        print();
    }

    static void print(){
        int a = 1;
        int b = 1;
        int i = 2;
        System.out.println(a);
        System.out.println(b);
        for (i=1;i<=5;i++){
            a = a + b;
            b = a + b;
            System.out.println(a);
            System.out.println(b);
        }
    }
}
