// 单件类的实现
public class B {
    private static B uniqueInstance;

    private B(){

    }

    public static B getUniqueInstance() {
        if(uniqueInstance==null){
            uniqueInstance = new B();
        }
        return uniqueInstance;
    }

}
