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
    void set(const attr_string& value) {s = value;}
    void set(const double value) {f = value;};
    void set(const long value) {f = value;};
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

typedef std::map <attr_name, attr_value> attr_table;

#endif // ATTRIBUTE_H
