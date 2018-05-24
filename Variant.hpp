#include <string>
#include <vector>
using namespace std;

/*
*Clase que hace las veces de variable que puede guardar muchos tipos de datos, necesaria para enviar datos de todo tipo con los mensajes
*/
class Variant
{
	enum Type
	{
		NIL, BOOL, CHAR, INT, FLOAT, POINTER, STRING, VECTOR_INT
	};

	union Data
	{
		bool		  boolean_value;
		wchar_t     	 char_value;
		int		   	   	  int_value;
		float           float_value;
		void        * pointer_value;
		string *  string_value;
		vector<int> * vector_int_value;

	};

	Type type;
	Data data;

public:

	Variant() : type(NIL)
	{
	}

	Variant(bool v) : type(BOOL)
	{
		data.boolean_value = v;
	}

	Variant(int v) : type(INT)
	{
		data.int_value = v;
	}

	Variant(float v) : type(FLOAT)
	{
		data.float_value = v;
	}

	Variant(const string & v) : type(STRING)
	{
		data.string_value = new string(v);
	}

	Variant(vector<int> & v) : type(VECTOR_INT)
	{
		data.vector_int_value = new vector<int>(v);
	}

	~Variant()
	{
		clear();
	}

	Variant & operator = (const nullptr_t &)
	{
		clear(NIL); return *this;
	}

	Variant & operator = (const float f)
	{
		clear(FLOAT);
		data.float_value = f;
		return *this;
	}

public:

	void clear(Type t = NIL)
	{
		if (type == STRING) delete data.string_value;

		type = t;
	}

	bool is_nil() const { return type == NIL; }
	bool is_boolean() const { return type == BOOL; }
	bool is_int() const { return type == INT; }
	bool is_float() const { return type == FLOAT; }
	bool is_pointer() const { return type == POINTER; }
	bool is_string() const { return type == STRING; }

	int as_int() const
	{
		switch (type)
		{
		case INT: 	  return    (data.int_value);
		case FLOAT:   return int(data.float_value);
		case CHAR:    return int(data.char_value);
		case POINTER: return int(data.pointer_value);
		case STRING:  return std::stoi(*data.string_value);
		default: 	  return 0;
		}
	}

	string as_string() const
	{
		switch (type)
		{
		case INT: 	  return to_string(data.int_value);
		case FLOAT:   return to_string(data.float_value);
		case CHAR:    return string(1, data.char_value);
		//case POINTER: return string(size_t,(data.pointer_value));
		case STRING:  return *data.string_value;
		default: 	  return string();
		}
	}

};
