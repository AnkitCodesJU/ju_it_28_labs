import java.util.Date;

class ChatRoom {
    public static void showMessage(User usr, String msg) {
        System.out.println(new Date().toString() + " [" + usr.getName() + "] : " + msg);
    }
}

class User {
    private String name;

    public User(String name) {
        this.name = name;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public void sendMessage(String msg) {
        ChatRoom.showMessage(this, msg);
    }
}

class Prog3 {
    public static void main(String[] arg) {
        User u1 = new User("Ankit");
        User u2 = new User("Saptarshi");
        u1.sendMessage("Hi");
        u2.sendMessage("Hey");
    }
}