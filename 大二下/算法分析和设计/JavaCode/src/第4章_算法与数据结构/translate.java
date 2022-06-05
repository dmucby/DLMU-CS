package 第4章_算法与数据结构;

import java.util.Scanner;

/**
 * 4.4.1 编号翻译
 */
public class translate {

    static String[] nums = {"zero","one","two","three","four","five","six","seven","eight","nine"};

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        translation(n);
    }
    static void translation(int n){
        int num = n;
        int ind = 0;
        String[] a = new String[10000];
        while (num != 0) {
            a[ind++] = nums[num%10];
            num /= 10;
        }
        for (int i = ind-1; i >= 0; i-- ){
            System.out.print(a[i]);
            if (i != 0) {
                System.out.print("-");
            }
        }
    }
}
