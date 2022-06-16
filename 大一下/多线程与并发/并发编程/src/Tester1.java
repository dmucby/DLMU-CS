import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.concurrent.Semaphore;

public class Tester1 {
    private final Semaphore permit = new Semaphore(10,true);
    // 整型数字代表许可证数量 acquire获得许可 release归还许可

    public void process(){
        try{
            permit.acquire();
            // 允许操作
        }catch (InterruptedException e){
            e.printStackTrace();
        }
        finally {
            permit.release();
            // 释放
        }
    }

    public static void main(String[] args){
        String start = new SimpleDateFormat("yyyy").format(new Date());
        RateLimiter limiter = RateLimiter.create(1.0);

    }
}
