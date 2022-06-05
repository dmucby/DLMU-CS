package 第9章_分治法;

/**
 * 最大子段和
 */
public class MaxNum {
    public static void main(String[] args) {
        int[] a = {-2,11,-4,13,-5,-2};
        System.out.println(MaxSum(a));
        System.out.println(MaxSubSum(a,1,a.length-1));
    }

    /**
     * 动态规划解法
     * @param a
     * @return
     */
    static int MaxSum(int[] a){
        int sum=0,b=0;
        for (int i = 0; i < a.length; i++) {
            if (b > 0){ // b标识部分和（可能的最大值）
                b += a[i];
            }else {
                b = a[i];
            }
            if (b > sum) { // sum一直存储最大值
                sum = b;
            }
        }
        return sum;
    }

    /**
     * 分治解法
     * @param a
     * @param left
     * @param right
     * @return
     */
    public static int MaxSubSum(int a[],int left,int right) {
        int sum = 0;
        if(left == right)
            sum = a[left] > 0 ? a[left] : 0;
        else {
            int center = (left + right)/2;
            int leftsum = MaxSubSum(a,left,center);
            int rightsum = MaxSubSum(a,center+1,right);
            int s1 = 0;
            int lefts = 0;
            for(int i = center;i >= left;i--) {
                lefts += a[i];
                if(lefts > 0)
                    s1 = lefts;
            }
            int s2 = 0;
            int rights = 0;
            for(int i = center+1;i <= right;i++) {
                rights += a[i];
                if(rights > 0)
                    s2 = rights;
            }
            sum = s1 + s2;
            if(sum < leftsum)
                sum = leftsum;
            if(sum < rightsum)
                sum = rightsum;
        }
        return sum;
    }

}
