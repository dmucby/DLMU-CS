package 第7章_蛮力法;

import java.util.Scanner;

public class yuli {
    public static void main(String[] args) {
        Scanner reader=new Scanner(System.in);
        int n=reader.nextInt();
        for(int i=1;i<=Math.sqrt(n);i++) {
            System.out.println("第"+i*i+"号牢房门锁是打开的");
        }
    }
}
