import java.util.ArrayList;
import java.util.List;
public class 作业一 {
    class Account{
        private List<Customer> cus;
        public Account(){
            cus = new ArrayList<Customer>();
        }
        public void addSignatory(Customer customer){
            cus.add(customer);
        }
    }
    class Customer{
        private List<Account> acc;
        public Customer(){
            acc = new ArrayList<Account>();
        }
        public void addSignatory(Account account){
            acc.add(account);
            account.addSignatory(this);// 添加同时把自身绑定
        }
    }
}
