import java.util.ArrayList;

public class SeekJobCenter implements Subject{
    ArrayList<Observer> personList;
    String mess;
    boolean changed;

    public SeekJobCenter(){
        personList = new ArrayList<>();
        mess = "";
        changed = false;
    }

    @Override
    public void addObserver(Observer o) {
        if(!personList.contains(o)){
            personList.add(o);
        }
    }

    @Override
    public void deleteObserver(Observer o) {
        if(personList.contains(o)){
            personList.remove(o);
        }
    }

    @Override
    // 更新消息后 更新所有信息
    public void notifyObserver() {
        if(changed){
            for (Observer o:personList) {
                Observer observer = o;
                observer.hearTelephone(mess);
            }
            changed = false;
        }
    }

    public void getNewMess(String str){
        if(str.equals(mess)){
            changed = false;
        }
        else{
            mess = str;// 每当获取新的讯息就更新旧信息
            changed = true;
        }
    }
}
