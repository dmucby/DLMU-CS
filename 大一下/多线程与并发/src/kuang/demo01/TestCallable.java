package kuang.demo01;

import java.util.concurrent.*;


public class TestCallable implements Callable<Boolean> {


    /**
     *
     * @return
     * @throws Exception
     */

    @Override
    public Boolean call() throws Exception {
        for (int i = 0; i < 2000; i++) {
            System.out.println("sb");
        }
        return true;
    }

    /**
     *
     * @param args
     */
    public static void main(String[] args) {

        TestCallable t1 = new TestCallable();
        // 创建执行服务
        ExecutorService ser = Executors.newFixedThreadPool(3);

        // 提交执行
        Future<Boolean> r1 = ser.submit(t1);

        // 获取结果
        try {
            Boolean unused = r1.get();
        } catch (InterruptedException e) {
            e.printStackTrace();
        } catch (ExecutionException e) {
            e.printStackTrace();
        }

        for (int i = 0; i < 2000;i++) {
            System.out.println("liuChang");
        }

        // 关闭服务
        ser.shutdown();
    }
}
