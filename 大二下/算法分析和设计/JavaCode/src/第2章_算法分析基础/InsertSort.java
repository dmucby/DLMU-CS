package 第2章_算法分析基础;


import java.util.Arrays;
import java.util.Random;

public class InsertSort {
    public static void main(String[] args) {
        Random random = new Random();
        int[] a = new int[10];
        for (int i = 0; i < a.length; i++) {
            a[i] = random.nextInt();
        }
        System.out.println(Arrays.toString(a));
        System.out.println(Arrays.toString(sort2(a)));
    }

    static int[]  sort (int[] Arrays){
        int key,i;
        for (int j = 1;j <= Arrays.length-1; j++){
            key = Arrays[j]; // 比较关键字
            i = j-1;
            while (i >= 0 && Arrays[i]>key){ // 找到插入位置进行调整
                Arrays[i+1] = Arrays[i];
                i--;
            }
            Arrays[i+1] = key;
        }
        return Arrays;
    }

    static int[] sort2(int[] Arrays){
        int key,i;
        for (int j = 1; j <= Arrays.length-1; j++){
            key = Arrays[j];
            i = j-1;
            while (i >= 0 && Arrays[i] > key){
                Arrays[i+1] = Arrays[i];
                i--;
            }
            Arrays[i+1] = key;
        }
        return Arrays;
    }
}
