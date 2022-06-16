package kuang.demo01;

public class TestThread4 implements Runnable{

    private int ticketNums = 10;

    @Override
    public void run() {
        while (true) {

            if (ticketNums <= 0) {
                break;
            }
            // 模拟延迟
            try {
                Thread.sleep(200);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            System.out.println(Thread.currentThread().getName() + "拿到了第" + ticketNums-- + "票");
        }


    }

    public static void main(String[] args) {

        TestThread4 test = new TestThread4();

        new Thread(test,"小明").start();
        new Thread(test,"小王").start();
        new Thread(test,"小刘").start();

    }


}
