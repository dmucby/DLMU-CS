package 第4章_算法与数据结构;

import java.util.Scanner;

/**
 * 4.3.2 身高统计问题
 */
public class DivideHeight {
    public static void main(String[] args) {
        int[] divide = new int[9];
        height(divide);
        for (int i = 0; i <= 7  ; i++) {
            System.out.println((i+1)+"field the number of the persons"+divide[i]);
        }
    }

    static void height(int[] divide){
        Scanner sc = new Scanner(System.in);
        int h = sc.nextInt();
        while (h != -1 ){
            if (h > 179){
                divide[7]++;
            }else if(h < 150){
                divide[0]++;
            }else {
                divide[h/5-29]++;
            }
            h = sc.nextInt();
        }
    }

}
