package kuang.better;

import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class testPool {
    public static void main(String[] args) {
        // 创建线程池
        ExecutorService service = Executors.newFixedThreadPool(10);
        // 丢尽线程池

        service.execute(new myThread());
        service.execute(new myThread());
        service.execute(new myThread());
        service.execute(new myThread());
        service.execute(new myThread());

        // 关闭连接
        service.shutdown();

    }
}

class myThread implements Runnable {

    @Override
    public void run() {
        for (int i = 0; i < 100; i++) {
            System.out.println(Thread.currentThread().getName() + i);
        }
    }
}