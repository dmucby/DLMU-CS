package 第6章_迭代法;

/**
 * 赶鸭子问题
 */
public class Duck {
    public static void main(String[] args) {
        int sum = 2;
        for (int i = 0; i < 7; i++) {
            sum = (sum + 1) * 2;
        }
        System.out.println("sum=" + sum);
    }
}
