package 第4章_算法与数据结构;

import java.util.Scanner;

/**
 * 4.3.1 选票统计问题
 */
public class BallotStatistics {
    public static void main(String[] args) {

    }

    static void printf(int xp){
        int[] S = new int[6];

        Scanner scanner = new Scanner(System.in);
        while(xp != -1){
            if (xp >= 1 && xp <=5) {
                S[xp]++;
            }else {
                System.out.println("ERROR!");
            }
            xp = scanner.nextInt();
        }
        for (int i = 1; i <= 5; i++) {
            System.out.println(i+"number get"+S[i]+"votes");
        }
    }
}
