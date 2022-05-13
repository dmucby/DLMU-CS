package Greedy;

public class DeleteNumber{

    public static void main(String[] args) {
        int[] n = {2,3,1,1,8,3};
        int s = 3;
        int len = n.length;
        int[] data = new int[len];

        int i = 0;
        int j = 1;
        int j1 = 0;

        while (i < s && j <=len-1){
            while(n[j] <= n[j+1]){
                if(j <= len){
                    delete(n,j,1);
                    if(j > j1){
                        data[i] = j + i;
                    }else {
                        data[i] = data[i-1] - 1;
                    }
                }
                i++;
                j1 = j;
                j--;
            }
        }

        for (i = i; i <= s; i++) {
            j = len - i + 1;
            delete(n,j,1);
            data[i] = j;
        }

        for (i = i;i<=s;i++){
            System.out.print(data[i]);
        }
    }

    public static void delete(int[] n, int b, int k){
        for (int m = b; m <= n.length -k; m++) {
            n[m] = n[m+k];
        }
    }

}
