package kuang.demo01;

public class Race implements Runnable{

    private static String winner;

    private  Boolean gameOver(int steps){
        // 确保只有一个胜利
        if (winner != null){
            return true;
        }else {
            if(steps == 100){
                winner = Thread.currentThread().getName();
                System.out.println("比赛结束！");
                System.out.println("winner is " + winner);
                return true;
            }
        }
        return false;
    }

    @Override
    public void run() {
        System.out.println("比赛开始!");


        for (int i = 0; i <= 100; i++) {
            Boolean flag = gameOver(i);
            if (flag){
                break;
            }

            if(Thread.currentThread().getName().equals("兔子") && i == 50){
                try {
                    Thread.sleep(1);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }

            System.out.println(Thread.currentThread().getName() + "跑了第" + ++i + "步");
        }

    }

    public static void main(String[] args) {
        Race race = new Race();

        new Thread(race,"兔子").start();
        new Thread(race, "乌龟").start();
    }
}
