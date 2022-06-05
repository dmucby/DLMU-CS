package 第4章_算法与数据结构;

import java.util.Scanner;

/**
 * 4.4.2 找零钱问题
 */
public class change {

    static int[] array = {50,20,10,5,2,1};

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int x = scanner.nextInt();
        int y = scanner.nextInt();
        print(x,y);
    }

    static void print(int x,int y){
        int z = y - x;
        int a;
        int[] s = new int[array.length];

        System.out.println("要找的零钱数为： " + z );

        for (int i = 0; i < array.length; i++) {
            a = z / array[i];
            s[i] = s[i] + a;
            z -= a * array[i];
        }

        for (int i = 0; i < array.length ; i++) {
            if (s[i]!=0) {
                System.out.println(array[i] + " " + s[i]);
            }
        }
    }
}
