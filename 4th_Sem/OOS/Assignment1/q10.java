class Book {
        private String author;
        private String title;
        private String publisher;
        private double cost;
        private int stock;

        public Book(String title, String author, String publisher, double cost, int stock) {
                this.title = title;
                this.author = author;
                this.publisher = publisher;
                this.cost = cost;
                this.stock = stock;
        }

        public String getAuthor() {
                return author;
        }

        public String getTitle() {
                return title;
        }

        public double getCost() {
                return cost;
        }

        public int getStock() {
                return stock;
        }

        public void setStock(int stock) {
                this.stock = stock;
        }

        public void displayDetails() {
                System.out.println("Title: " + title);
                System.out.println("Author: " + author);
                System.out.println("Publisher: " + publisher);
                System.out.println("Cost: Rs. " + cost);
                System.out.println("Available Copies: " + stock);
        }

        public boolean isAvailable(int requiredCopies) {
                return stock >= requiredCopies;
        }

        public double calculateTotalCost(int copies) {
                return copies * cost;
        }
}

class BookShop {
        private Book[] inventory;
        private int count;

        public BookShop(int size) {
                inventory = new Book[size];
                count = 0;
        }

        public void addBook(Book book) {
                if (count < inventory.length) {
                        inventory[count++] = book;
                }
        }

        public Book searchBook(String title, String author) {
                for (int i = 0; i < count; i++) {
                        Book b = inventory[i];
                        if (b.getTitle().equalsIgnoreCase(title) && b.getAuthor().equalsIgnoreCase(author)) {
                                return b;
                        }
                }
                return null;
        }

        public void sellBook(String title, String author, int requiredCopies) {
                Book book = searchBook(title, author);
                if (book == null) {
                        System.out.println("Book not available in inventory.");
                        return;
                }
                book.displayDetails();
                if (book.isAvailable(requiredCopies)) {
                        double totalCost = book.calculateTotalCost(requiredCopies);
                        book.setStock(book.getStock() - requiredCopies);
                        System.out.println("Total Cost: Rs. " + totalCost);
                        System.out.println(requiredCopies + " copies sold. Remaining stock: " + book.getStock());
                } else {
                        System.out.println("Required copies not in stock.");
                }
        }
}

class Main10 {
        public static void main(String[] args) {
                BookShop shop = new BookShop(5);

                shop.addBook(new Book("Book1", "Author1", "Publisher1", 20.0, 10));
                shop.addBook(new Book("Book2", "Author2", "Publisher2", 15.0, 5));
                shop.addBook(new Book("Book3", "Author3", "Publisher3", 25.0, 8));

                shop.sellBook("Book1", "Author1", 3);
                System.out.println("----------------");
                shop.sellBook("Book2", "Author2", 6);
                System.out.println("----------------");
                shop.sellBook("Book3", "Author3", 5);
                System.out.println("----------------");
                shop.sellBook("Book4", "Author4", 1);
        }
}
