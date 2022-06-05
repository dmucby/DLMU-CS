package 第12章_启发式搜索;

/**
 * 12.3.5 装载问题
 */
public class Load {
    static int n;//货箱数目
    static int[] w;//货箱重量数组
    static int c;//第一艘船的重量
    static int cw;//当前装载的重量
    static int bestw;//目前最优装载的重量
    static int r;//剩余货箱的重量

    static int[] x;//当前解，记录从根至当前结点的路径
    static int[] bestx;//记录当前最优解


    public static int MaxLoading(int[] ww,int cc) {
        //初始化数据成员，数组下标从1开始
        n = ww.length - 1;
        w = ww;
        c = cc;
        cw = 0;
        bestw = 0;
        x = new int[n+1];
        bestx = new int[n+1];

        //初始化r，即剩余最大重量
        for(int i =1;i<=n;i++) {
            r += w[i];
        }

        //计算最优载重量
        backtrack(1);
        return bestw;
    }

    //回溯算法
    public static void backtrack(int t) {
        if(t>n) {//到达叶结点
            if(cw>bestw) {
                for(int i=1;i<=n;i++) {
                    bestx[i] = x[i];
                }
                bestw = cw;
            }
            return;
        }

        r -= w[t];
        if(cw + w[t] <= c) {//搜索左子树
            x[t] = 1;
            cw += w[t];
            backtrack(t+1);
            cw -= w[t];//回溯
        }

        if(cw + r>bestw) {
            x[t] = 0;//搜索右子树
            backtrack(t+1);
        }

        r += w[t];//恢复现场

    }
    /*
     * 如果当前节点的右子树不可能包含比当前最优解更好的解时，就不移动到右子树上！
    设bestw为当前最优解，Z为解空间树的第i 层的一个节点
        为剩余货箱的重量;当cw+r<=bestw时，没有必要去搜索Z 的右子树：
        当前载重量cw+剩余集装箱的重量r当前最优载重量bestw
     */
    public static void main(String[] args) {
        // TODO Auto-generated method stub
        int[] ww = {0,10,40,40};
        int c1 = 50;
        int c2 = 50;
        int n = ww.length - 1;

        MaxLoading(ww,c1);
        int weight2 = 0;//保存第二艘船可能要装的重量
        for(int i=1;i<=n;i++) {
            weight2 += ww[i]*(1-bestx[i]);//bestx[i]的值只能为0或1

        }
        if(weight2>c2) {
            System.out.println("无解");
        }
        else {
            System.out.println("第一艘船装载货物的重量： " + bestw);
            System.out.println("第二艘船装载货物的重量： " + weight2);

            //第一艘船的装载情况
            for(int i = 1;i<=n;i++) {
                if(bestx[i] == 1) {
                    System.out.println("第" + i + "件货物装入第一艘船");
                }
            }

            //第二艘船的装载情况
            for(int i = 1;i<=n;i++) {
                if(bestx[i] == 0) {
                    System.out.println("第" + i + "件货物装入第二艘船");

                }
            }

        }

    }

}
