import jdk.nashorn.api.scripting.ScriptObjectMirror;

/*
import java.util.ArrayList;

import java.util.Enumeration;
import java.util.List;
import java.util.Vector;

public class 作业二 {

    public abstract static class Component {
        protected static void elements() {
        }

        public abstract void check(Component t);

    }

    abstract class Assembly extends Component {
        private List<Component> com;

        public Assembly() {
            com = new ArrayList<Component>();
        }

        public void addAssembly(Component c) {
            c.check(this);
            com.add(c);
        }
    }

    class Part extends Component {
        public void check(Component t) {
            if (this.equals(t)) {
                try {
                    throw new NoException() {};
                } catch (NoException e) {
                    e.printStackTrace();
                }
            }
            //Enumeration<Component> enum =Component.elements();
            Enumeration<Component> enumeration = new Enumeration<Component>() {
                @Override
                public boolean hasMoreElements() {
                    return false;
                }

                @Override
                public Component nextElement() {
                    return null;
                }
            };
            Component f;
            while (enumeration.hasMoreElements()) {
                f = enumeration.nextElement();
                f.check(this);
            }
        }

        public Part() {

        }
    }


    //public class Assembly1 extends Component {
        private Vector components = new Vector();

        public double cost() {
            double total = 0.0;
            Enumeration enumeration = new Enumeration() {
                @Override
                public boolean hasMoreElements() {
                    return false;
                }

                @Override
                public Object nextElement() {
                    return null;
                }
            };

            while ( enumeration.hasMoreElements()){

            }
            return total;
        }
        public void check(){

        }
    }

    //public class NoException extends Exception{

    }
}
*/
