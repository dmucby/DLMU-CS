package 第9章_分治法;

import java.util.Arrays;

/**
 * 选择此小数
 */
public class topK {
    public static void main(String[] args) {
        int[] a ={1,2,3,4,5,643,3,2,34,532};
        System.out.println(print(a));
        int[] ans = seconds(a,0, a.length-1);
        for (int i = 0; i < ans.length; i++) {
            System.out.println(ans[i]);
        }
    }

    /**
     * 暴力排序法
     * @param a
     * @return
     */
    static int print(int[] a){
        Arrays.sort(a);
        System.out.println(Arrays.toString(a));
        return a[1];
    }

    static int fmin1;
    static int fmin2;
    static int lmin1;
    static int lmin2;
    static int rmin1;
    static int rmin2;

    /**
     * 两组 二分法
     */
     static int[] seconds(int[] a,int i,int j){
         int mid;
         if(i == j){
             fmin1 = a[i];
             fmin2 = a[i];
             return new int[] {fmin1, fmin2};
         }
         else if(i == j-1){
             if(a[i] < a[j]) {
                 fmin1 = a[i];
                 fmin2 = a[j];
                 return new int[]{fmin1, fmin2};
             }
              else{
                 fmin2 = a[i];
                 fmin1 = a[j];
                 return new int[] {fmin1, fmin2};
             }
         }else {
            mid = (i + j)/2;
            lmin1 = seconds(a, i, mid)[0];
            lmin2 = seconds(a, i, mid)[1];
            rmin1 = seconds(a, mid + 1, j)[0];
            rmin2 = seconds(a, mid + 1, j)[1];
         }
         if(lmin1 < rmin1){
             if(lmin2 < rmin1){
                 fmin1 = lmin1;
                 fmin2 = lmin2;
             }else {
                 fmin1 = lmin1;
                 fmin2 = rmin1;
             }
         }else {
             if(rmin2 < lmin1){
                 fmin1 = rmin1;
                 fmin2 = rmin2;
             }else {
                 fmin1 = rmin1;
                 fmin2 = lmin1;
             }
         }
         return new int[]{fmin1,fmin2};
     }

}
