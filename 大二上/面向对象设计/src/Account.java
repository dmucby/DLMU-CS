import java.util.Vector;

// 单向可选关联 一对一可选关联
public class Account {
    private DebitCard theCard;
    public DebitCard getTheCard(){
        return theCard;
    }

    public void setTheCard(DebitCard theCard) {
        this.theCard = theCard;
    }

    public void removeTheCard(){
        theCard = null;
    }

    // 单向可选不变关联
    //一对一关联
    public void setTheCard1(DebitCard theCard){
        if(theCard != null){
            try {
                throw new Exception();
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
        this.theCard = theCard;
    }

    // 重数为多的关联
    private Vector theAccount;
    public void addAccount(Account acc){
        theAccount.add(acc);
    }

    public void removeAccount(Account acc){
        theAccount.removeElement(acc);
    }

    // 一致性问题解决 将维护责任交给两个类中的一个类
    public void addCard(){
        theCard = new DebitCard(this);
    }
}
