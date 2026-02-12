class Date {
        private int day, month, year;
        private static final int[] DAYS_IN_MONTH = {0,31,28,31,30,31,30,31,31,30,31,30,31};

        Date() {
                this.day = 1;
                this.month = 1;
                this.year = 1970;
        }

        Date(int d) {
                this.day = d;
                this.month = 1;
                this.year = 1970;
                validateDate();
        }

        Date(int d, int m) {
                this.day = d;
                this.month = m;
                this.year = 1970;
                validateDate();
        }

        Date(int d, int m, int y) {
                this.day = d;
                this.month = m;
                this.year = y;
                validateDate();
        }

        private void validateDate() {
                if(month < 1 || month > 12) month = 1;
                int maxDays = daysInMonth(month, year);
                if(day < 1 || day > maxDays) day = 1;
        }

        private boolean isLeapYear(int y) {
                return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
        }

        private int daysInMonth(int m, int y) {
                if(m == 2 && isLeapYear(y)) return 29;
                return DAYS_IN_MONTH[m];
        }

        void printDate() {
                System.out.printf("%02d/%02d/%04d\n", day, month, year);
        }

        void nextDay() {
                day++;
                if(day > daysInMonth(month, year)) {
                        day = 1;
                        month++;
                        if(month > 12) {
                                month = 1;
                                year++;
                        }
                }
        }

        void previousDay() {
                day--;
                if(day < 1) {
                        month--;
                        if(month < 1) {
                                month = 12;
                                year--;
                        }
                        day = daysInMonth(month, year);
                }
        }

        public static void main(String[] args) {
                Date d1 = new Date();
                d1.printDate();
                d1.nextDay();
                d1.printDate();
                d1.previousDay();
                d1.previousDay();
                d1.printDate();

                Date d2 = new Date(28, 2, 2024);
                d2.printDate();
                d2.nextDay();
                d2.printDate();
        }
}

