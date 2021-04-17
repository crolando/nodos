#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

#include <string>
#include <map>

typedef std::string attr_name;
typedef double      attr_fnumber;
typedef long        attr_inumber;
typedef std::string attr_string;

enum attr_type { string, fnumber, inumber};

class attr_value
{
public:
    // Default constructor so I can use map["blah"] = newValue;
    attr_value(){};
    attr_value(const attr_string& Value) {
        s = Value;
        t = string;
    };

    attr_value(const attr_fnumber Value) {
        f = Value;
        t = fnumber;
    }

    attr_value(const attr_inumber Value) {
        i = Value;
        t = inumber;
    }

    void set(const attr_string& value) {
        s = value;
        t = string;
        }
    void set(const double value) {
        f = value;
        t = fnumber;
    };
    void set(const long value) {
        i = value;
        t = inumber;
    };

    attr_type get_type(void) {return t;};
    attr_string& get_string(void) {return s;};
    attr_fnumber get_float(void) {return f;};
    attr_inumber get_integer(void) {return i;};
private:
    attr_type       t;
    attr_string     s;
    attr_fnumber    f = 0.0;
    attr_inumber    i = 0;
};

class attr_table {
public:
    bool has_attr(const attr_name& Key)
    {
        std::map <attr_name, attr_value>::iterator it;
        it = table.find(Key);
        if (it == table.end()) {
            return false;
        } else {
            return true;
        }
    }

    void set_attr(const attr_name& Key, attr_string& Value) {
        if(has_attr(Key) == false) {
            table[Key] = attr_value(Value);
        } else {
            table[Key].set(Value);
        }
    }

    void set_attr(const attr_name& Key, attr_fnumber Value) {
        if(has_attr(Key) == false) {
            table[Key] = attr_value(Value);
        } else {
            table[Key].set(Value);
        }
    }

    void set_attr(const attr_name& Key, attr_inumber Value) {
        if(has_attr(Key) == false) {
            table[Key] = attr_value(Value);
        } else {
            table[Key].set(Value);

        }
    }

    attr_value& get_attr(const attr_name& Key) {
        return table[Key];
    }


private:
    std::map <attr_name, attr_value> table;
};


#endif // ATTRIBUTE_H
