package kuang.syn;

public class unsafeByTicket {

    public static void main(String[] args) {
        buyTicket thread = new buyTicket();

        new Thread(thread,"小明").start();
        new Thread(thread,"小王").start();
        new Thread(thread,"小刘").start();
    }
}


class buyTicket implements Runnable{

    private int ticketNum = 10;
    private boolean flag = true;

    @Override
    public void run() {
        while (flag) {
           buy();
        }
    }

    void buy(){
        if (ticketNum <= 0) {
           flag = false;
           return;
        }
        try {
            Thread.sleep(100);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        System.out.println(Thread.currentThread().getName() + "买到了第" + ticketNum-- + "张票");
    }
}