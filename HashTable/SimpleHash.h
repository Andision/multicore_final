template <typename K>
class SimpleHash {
public:
    int operator()(const K& key) const {
        return static_cast<int>(key);
    }
};

template <>
class SimpleHash<std::string> {
public:
    int operator()(const std::string& key) const {
        int hash = 0;
        for (char ch : key) {
            hash = (hash * 31 + ch) % 100000;
        }
        return hash;
    }
};
