package OOP_Te_Xing.extendsDemo;

public class Father {
    public void playBasketball(){
        System.out.println("play well!");
    }

    public static void main(String[] args) {
        Father fa = new son();
        fa.playBasketball();
//        son s = (son) new Father();
//        s.playBasketball();
    }
}


class son extends Father {

    // 注解 标识这个方法被重写
    @Override
    public void playBasketball() {
        System.out.println("play perfectly!");
    }

}