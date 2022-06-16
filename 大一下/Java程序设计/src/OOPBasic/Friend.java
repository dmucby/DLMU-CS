package OOPBasic;

public class Friend {

    String name = "";
    int height;

    void playBasketBallWell(){
        String name = "彭于晏";
        System.out.println( name +"会打篮球");
    }

    public Friend() {

    }

    public Friend(String name){
        this.name = name;
    }

    public static void main(String[] args) {
        Friend friend1 = new Friend();
        friend1.playBasketBallWell();
        Friend friend2 = new Friend("胡歌");
        System.out.println(friend2.name);
    }

}
