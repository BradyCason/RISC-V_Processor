#ifndef __WIRE
#define __WIRE
#include <vector>
#include <stdexcept>

class Wire{
    private:
        std::vector<bool> values;
    public:
        Wire(int length) : values(length, 0){}
        Wire(int length, unsigned long long val) : values(length, 0){
            for (size_t i = 0; i < length; ++i) {
                values[i] = (val & (1ull << i)) != 0; // Check if the i-th bit is set
            }
        }
        Wire(int a, int b, const std::vector<bool>& v){
            if (a < b || a >= v.size() || b < 0) {
                throw std::invalid_argument("Invalid range for slice");
            }
            for (int i = a; i >= b; --i) {
                values.push_back(v[i]); // Fill in the sliced values
            }
        }
        Wire slice(int a, int b){
            return Wire(a, b, values);
        }
        unsigned long long value(){
            unsigned long long result = 0;

            for (size_t i = 0; i < values.size(); ++i) {
                if (values[i]) {
                    result |= (1u << i); // Set the corresponding bit if boolArray[i] is true
                }
            }

            return result;
        }

        Wire& operator=(unsigned long long a){
            for (size_t i = 0; i < values.size(); ++i) {
                values[i] = (a & (1ull << i)) != 0; // Check if the i-th bit is set
            }
            return *this;
        }

        Wire& operator=(const Wire& other){
            values = other.values;
            return *this;
        }
};

#endif