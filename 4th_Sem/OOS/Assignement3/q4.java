import java.lang.reflect.*;

class Person {
    private String secretName = "James Bond 007";
    public String publicStatus = "On Mission";

    public Person() {}

    public void sayHello() {
        System.out.println("Hello from the public method!");
    }

    private void whisperSecret() {
        System.out.println("The secret name is: " + secretName);
    }
}

class Main {
    public static void main(String[] args) {
        try {
            Person agent = new Person();
            Class<?> cls = agent.getClass();

            System.out.println("Class Name: " + cls.getName());

            System.out.println("\nPublic Methods:");
            Method[] methods = cls.getMethods();
            for (Method m : methods) {
                System.out.println("- " + m.getName());
            }

            System.out.println("\nAll Declared Constructors:");
            Constructor<?>[] constructors = cls.getDeclaredConstructors();
            for (Constructor<?> c : constructors) {
                System.out.println("- " + c);
            }

            Field field = cls.getDeclaredField("secretName");
            field.setAccessible(true);
            System.out.println("\nIntercepted Private Field: " + field.get(agent));

            Method privateMethod = cls.getDeclaredMethod("whisperSecret");
            privateMethod.setAccessible(true);
            System.out.print("Invoking Classified Method: ");
            privateMethod.invoke(agent);

            Field publicField = cls.getField("publicStatus");
            System.out.println("Public Status: " + publicField.get(agent));

        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
