#include <iostream>
using namespace std;

class Encrypt {
private:
        const int pin;
        mutable int payload;

public:
        Encrypt(const int& secret, const int& data) : pin(secret), payload(data) {}

        void modifyPayload(const int& key, const int& newdata) const {
                if (pin == key) {
                        payload = newdata; // allowed in a const member function as data member is mutable
                        cout << "Payload modified to " << payload << endl;
                }
                else {
                        cout << "Wrong pin! Payload not modified." << endl;
                }
        }

        void displayPayload(const int& key) const {
                if (pin == key) {
                        cout << "Payload: " << payload << endl;
                }
                else {
                        cout << "Wrong pin! Cannot display payload." << endl;
                }
        }
};

int main() {
        Encrypt obj(1234, 555);

        obj.displayPayload(1234);
        obj.displayPayload(1111);

        obj.modifyPayload(1234, 999);
        obj.displayPayload(1234);

        return 0;
}

