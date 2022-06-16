import java.util.Enumeration;
import java.util.Vector;

public class Assembly extends Component {
    private Vector components = new Vector();
    public double cost(){
        double total = 0.0;
        Enumeration enumeration = components.elements();
        while(enumeration.hasMoreElements()){
            total += ((Component)enumeration.nextElement()).cost();
        }
        return total;
    }
}
