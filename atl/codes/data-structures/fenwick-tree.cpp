template <class T>
class BIT {
 private:
  int size;
  vector<T> bit;
  vector<T> arr;

 public:
  BIT(int size) : size(size), bit(size + 1), arr(size) {}

  /** Sets the value at index ind to val. */
  void set(int ind, int val) { add(ind, val - arr[ind]); }

  /** Adds val to the element at index ind. */
  void add(int ind, int val) {
    arr[ind] += val;
    ind++;
    for (; ind <= size; ind += ind & -ind) {
      bit[ind] += val;
    }
  }

  /** @return The sum of all values in [0, ind]. */
  T pref_sum(int ind) {
    ind++;
    T total = 0;
    for (; ind > 0; ind -= ind & -ind) {
      total += bit[ind];
    }
    return total;
  }
};