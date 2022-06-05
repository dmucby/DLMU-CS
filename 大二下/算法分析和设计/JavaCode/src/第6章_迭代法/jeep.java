package 第6章_迭代法;

/**
 * 6.3.2 输油问题
 */
public class jeep {
    public static void main(String[] args) {
        int s=1000;int l=0;int i=0;
        int[] a=new int[100];
        while(l<1000) {
            a[i]=500*(i+1);
            l+=500/(2*(i+1)-1);
            if(l<1000) {
                System.out.println("第"+(i+1)+"个点，"+"距终点"+l+"米"+"储油量"+a[i]+"升");
            }
            else {//控制距终点长度不超出沙漠总长
                System.out.println("第"+(i+1)+"个点，"+"距终点1000米"+"储油量"+a[i]+"升");
            }
            i++;
        }
    }
}
