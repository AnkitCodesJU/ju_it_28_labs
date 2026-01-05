#include <iostream>
#include <cmath>
using namespace std;

class Device {
        private:    
                int id, x, y, z, range;

                double distance(const Device* other) const {
                        return sqrt(pow(x - other->x, 2) + pow(y - other->y, 2) + pow(z - other->z, 2));
                }

        public:
                Device() : id(0), x(0), y(0), z(0), range(0) {}

                Device(int uid, int ux, int uy, int uz, int urange)
                        : id(uid), x(ux), y(uy), z(uz), range(urange) {}

                void setLoc(int ux, int uy, int uz) {
                        x = ux;
                        y = uy;
                        z = uz;
                }

                void setId(int uid) {
                        id = uid;
                }

                void setRange(int r) {
                        range = r;
                }

                int getId() const {
                        return id;
                }

                bool isNeighbour(const Device* other) const {
                        return distance(other) <= range;
                }
};

int main() {
        Device* devices = new Device[10];

        for (int i = 0; i < 3; i++) {
                devices[i].setId(i + 1);
                devices[i].setRange(5);
        }

        devices[0].setLoc(0, 0, 0);
        devices[1].setLoc(0, 1, 0);
        devices[2].setLoc(0, 0, 4);

        for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                        if (i != j && devices[i].isNeighbour(&devices[j])) {
                                cout << devices[i].getId() << " is the neighbour of " << devices[j].getId() << endl;
                        }
                }
        }

        devices[0].setLoc(0, 0, 0);
        devices[1].setLoc(0, 1, 0);
        devices[2].setLoc(0, 0, 999);

        for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                        if (i != j && devices[i].isNeighbour(&devices[j])) {
                                cout << devices[i].getId() << " is the neighbour of " << devices[j].getId() << endl;
                        }
                }
        }

        delete[] devices;
        return 0;
}

