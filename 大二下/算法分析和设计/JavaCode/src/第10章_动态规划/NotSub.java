package 第10章_动态规划;

import java.util.Scanner;

/**
 * 10.6 最长不降子序列
 * 所给序列长度为5的非降子序列可能有多个，这里只输出其中一个
 */
public class NotSub{

    static int n;
    static int[] ans = new int[100];
    static int max = 0;

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        n = sc.nextInt();
        for (int i = 0; i < n; i++) {
            ans[i] = sc.nextInt();
        }
        print();
        System.out.println();
        System.out.println(max);
    }

    static int findNot(int i){
        int j,f,max;
        if(i==n)f=1;	//如果是最后一个数，则为1
        else {
            max=0;
            for(j=i+1;j<n;j++){
                if(ans[j]>ans[i]&&findNot(j)>max){
                    //因为ans[i]比ans[j]小，
                    //所以ans[i]就可以加入ans[j]到ans[n]构成的非降序列
                    max=findNot(j);
                }
            }
            f=max+1;
            //长度加一
        }
        return f;
    }

    static void print(){
        for (int i = n-1; i >= 1;i-- ) {
            if(findNot(i) > max){
                max = findNot(i);
            }
        }
        int x = max;
        for (int i = 1; i <= n ; i++) {
            if(findNot(i) == x){
                System.out.print(ans[i] + " ");
                x--;
            }
        }
    }
}
