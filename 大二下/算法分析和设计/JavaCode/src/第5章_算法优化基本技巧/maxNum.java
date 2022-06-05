package 第5章_算法优化基本技巧;


/**
 * 5.1.3 最大最小乘数问题
 */

public class maxNum {
    public static void main(String[] args) {
        int[] a = {
                1,16,10,16,1,17,8,
                12,5,9,3,8,6,12,15,
                9
        };
        print(a,a.length-1);
    }

    static void  print(int[] array,int num){
        int max = 0;
        int min = 100;
        int m=0,n=0,s=0,t=0; // 保存的两对数
        int p,q; // 下标
        int k; // 保存临时结果
        for (int i = 0; i < array.length; i++) {
            p = (num+i-1) % num;
            q = (i + 1) % num;
            k = array[p] * array[q];
            if(k > max){
                max = k;
                m = array[p];
                n = array[q];
            }
            if (k < min) {
                min = k;
                s = array[p];
                t = array[q];
            }
        }

        System.out.println("max=" + m + "*" + n +"="+max);
        System.out.println("min=" + s + "*" + t +"="+min);
    }
}
