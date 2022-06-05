package 第9章_分治法;

/**
 * 金块二分法
 */
public class BullionProblem {
    public static void main(String[] args) {
        int[] a= {1,23,54353,4343,2,43,457,34};
        System.out.println(Max(a,0,a.length-1));
        System.out.println(Min(a,0,a.length-1));
    }

    public static int Max(int a[],int i,int j)//找最大值
    {
        int m1,m2,mid,max=0;
        if(i==j)
            max=a[i];//当分组的下标i与j相等时，将a[i]赋给最大值
        else if(i==j-1)//当分组的下标i与j相等时，判断a[i]与a[j]大小并赋予max值
        {
            if(a[i]>=a[j])
                max=a[i];
            else
                max=a[j];
        }
        else
        {
            mid=i+(j-i)/2;//找到中点
            m1=Max(a,i,mid);//递归找出第一组最大值m1
            m2=Max(a,mid+1,j);//递归找出第二组最大值m2
            if(m1>=m2)//判断m1和m2的大小，得到最大值max
                max=m1;
            else
                max=m2;
            return max;//返回值max
        }
        return max;
    }
    public static int Min(int[] a,int i,int j)//找最小值
    {
        int n1,n2,mid,min=0;
        if(i==j)
            min=a[i];//当分组的下标i与j相等时，将a[i]赋给最大值和最小值
        else if(i==j-1)//当分组的下标i与j相等时，判断a[i]与a[j]大小并赋予max,min值
        {
            if(a[i]<=a[j])
                min=a[i];
            else
                min=a[j];
        }
        else
        {
            mid=i+(j-i)/2;//找到中点
            n1=Min(a,i,mid);//递归找出第一组最小值n1
            n2=Min(a,mid+1,j);//递归找出第二组最小值n2
            if(n1<=n2)//判断n1和n2的大小，得到最小值min
                min=n1;
            else
                min=n2;
            return min;//返回值min
        }
        return min;
    }
}
