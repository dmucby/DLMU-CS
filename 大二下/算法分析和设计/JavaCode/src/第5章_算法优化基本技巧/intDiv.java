package 第5章_算法优化基本技巧;

import java.util.Scanner;

/**
 * 5.2.5 整除问题
 */

public class intDiv {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        while(true){
            int n = sc.nextInt();
            printDiv(n);
        }
    }

    static void printDiv(int n){
        int k =0;
        if (n % 3 == 0){
            k++;
        }
        if (n % 5 == 0){
            k = k + 2;
        }
        if (n % 7 == 0) {
            k = k + 4;
        }

        switch (k){
            case 0 :
                System.out.println("none");
                break;
            case 1 :
                System.out.println("3");
                break;
            case 2 :
                System.out.println("5");
                break;
            case 3 :
                System.out.println("5 and 3");
                break;
            case 4 :
                System.out.println("7");
                break;
            case 5 :
                System.out.println("3 and 7");
                break;
            case 6 :
                System.out.println("5 and 7");
                break;
            case 7 :
                System.out.println("all");
                break;
        }
    }

}
