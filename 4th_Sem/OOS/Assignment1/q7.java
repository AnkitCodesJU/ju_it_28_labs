import java.util.*;
abstract class Publication {
        private int noOfPages;
        private double price;
        private String publisherName;

        public Publication(int noOfPages, double price, String publisherName) {
                this.noOfPages = noOfPages;
                this.price = price;
                this.publisherName = publisherName;
        }

        public int getNoOfPages() {
                return noOfPages;
        }

        public void setNoOfPages(int noOfPages) {
                this.noOfPages = noOfPages;
        }

        public double getPrice() {
                return price;
        }

        public void setPrice(double price) {
                this.price = price;
        }

        public String getPublisherName() {
                return publisherName;
        }

        public void setPublisherName(String publisherName) {
                this.publisherName = publisherName;
        }

        public abstract void printDetails();
}

class Book extends Publication {
        private String title;
        private String author;

        public Book(String title, String author, int noOfPages, double price, String publisherName) {
                super(noOfPages, price, publisherName);
                this.title = title;
                this.author = author;
        }

        public void printDetails() {
                System.out.println("Book");
                System.out.println(title);
                System.out.println(author);
                System.out.println(getNoOfPages());
                System.out.println(getPrice());
                System.out.println(getPublisherName());
                System.out.println();
        }
}

class Journal extends Publication {
        private int issueNumber;

        public Journal(int issueNumber, int noOfPages, double price, String publisherName) {
                super(noOfPages, price, publisherName);
                this.issueNumber = issueNumber;
        }

        public void printDetails() {
                System.out.println("Journal");
                System.out.println(issueNumber);
                System.out.println(getNoOfPages());
                System.out.println(getPrice());
                System.out.println(getPublisherName());
                System.out.println();
        }
}

class Library {
        private Publication[] publications;
        private int count;

        public Library(int size) {
                publications = new Publication[size];
                count = 0;
        }

        public void addPublication(Publication p) {
                if (count < publications.length) {
                        publications[count++] = p;
                }
        }

        public void printAllPublications() {
                for (int i = 0; i < count; i++) {
                        publications[i].printDetails();
                }
        }
        public static void main(String[] args) {
                Library library = new Library(5);

                library.addPublication(new Book("Java Basics", "James Gosling", 350, 450, "Sun Microsystems"));
                library.addPublication(new Book("OOP Concepts", "Herbert Schildt", 500, 650, "McGraw-Hill"));
                library.addPublication(new Book("Data Structures", "Mark Allen", 400, 550, "Pearson"));

                library.addPublication(new Journal(101, 120, 200, "IEEE"));
                library.addPublication(new Journal(202, 150, 250, "Springer"));

                library.printAllPublications();
        }

}

