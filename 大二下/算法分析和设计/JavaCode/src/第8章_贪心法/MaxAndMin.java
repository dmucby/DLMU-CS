package 第8章_贪心法;

/**
 * 数列极差问题
 */

import java.util.Arrays;
import java.util.Comparator;
import java.util.Scanner;

    /*
     * 如果要求最大值的话，那么每次先用最小的连个数相乘的结果+1，
     * 相反，如果要求最小值的话，每次先用最大的两个数相乘的结果+1.
     */
public class MaxAndMin {
        static Integer m[] = new Integer[3];
        static Integer n[] = new Integer[3];
        static Comparator<Integer> cmp = new Comparator<Integer>() {
            public int compare(Integer i1, Integer i2) {
                return i2 - i1;
            }
        };

        public static void main(String args[]) {
            System.out.println("输入数组长度：");
            Scanner sc = new Scanner(System.in);
            int a = 0;
            a = sc.nextInt();
            System.out.println("输入数组元素：");
            for (int i = 0; i < a; i++) {
                m[i] = sc.nextInt();
                n[i] = m[i];
            }
            //升序排序
            Arrays.parallelSort(m, 0, a);
            for (int i = 1; i < a; i++) {
                m[i] = m[i] * m[i - 1] + 1;//从小到大排完序之后，先从前边最小的两个数相乘然后存放到数组里
                Arrays.parallelSort(m, i, a);/*算法的核心部分，由于每次从最小的两个数相乘后的数值
							  放到原来的数组中有可能会破坏数组从小到大的顺序,
						  所以再用一个sort排序，使新的数组变得有序,依次循环下去，就会得到最大值。*/
            }

            int max = m[a - 1];
            System.out.println("max:" + max);
            Arrays.sort(n, cmp);//逆序排序
            for (Integer a1 : n) {
                System.out.println(a1);
            }
            for (int i = 1; i < a; i++) {
                n[i] = n[i - 1] * n[i] + 1;/*而求最小值的时候就不用sort每次都排序啦，因为前边两个最大的数乘起来
								   的数不可能会比后边小的数还要小，所以求最小值得时候会比上边要简单一些*/
            }

            int min = n[a - 1];
            System.out.println("min:" + min);
            System.out.println("极差为：" + (max - min));
        }
    }
