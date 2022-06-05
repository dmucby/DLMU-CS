package 第8章_贪心法;

import java.util.Scanner;

/**
 * 删数问题
 */
public class Delete_Num {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int N = sc.nextInt();
        int S = sc.nextInt();
        if(N<=0 || S<=0){
            System.out.println("ERROR!");
        }
        System.out.println(DeleteNum(N,S));
    }

    static int DeleteNum(int N,int S){
        StringBuilder sb = new StringBuilder(N+"");
        int i,j;
        for (i = 0; i < S ; ++i) {
            /*
            1. 各位数字递增，删除最后一个
            2. 删除第一个递减的数字
             */
            for (j = 0; j < sb.length()-1 && sb.charAt(j) <= sb.charAt(j+1); ++j) {

            }
            sb.delete(j, j + 1);
        }
        return sb.length()==0?0:Integer.parseInt(sb.toString());
    }
}
