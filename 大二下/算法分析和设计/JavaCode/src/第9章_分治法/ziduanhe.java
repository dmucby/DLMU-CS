package 第9章_分治法;

import java.util.Arrays;
import java.util.Scanner;

/**
 * 最大子段和
 */

public class ziduanhe {
    public static void main(String[] args) {
        Scanner reader=new Scanner(System.in);
        String s=reader.nextLine();
        String a[]=s.split(" ");
        int[] b=new int[a.length];
        for(int i=0;i<a.length;i++) {
            b[i]=Integer.parseInt(a[i]);
        }
        int zc=0;
        for(int i=a.length;i>0;i--) {
            zc+=i;
        }
        int[] sum=new int[zc];
        int t=0;
        for(int i=0;i<a.length;i++) {
            for(int j=i;j<a.length;j++) {
                for(int k=i;k<=j;k++) {
                    sum[t]+=b[k];
                }
                t++;
            }
        }
        Arrays.sort(sum);
        System.out.println(sum[zc-1]);
    }
}
