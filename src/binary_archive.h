#pragma once

/*  
 *  binary_archive.h
 *	It is only used for local data serialization, not support net transfer, so it's very fast, efficient.
 *  I first used this to serialize offline data, and save it in sqlite blob. I had used the boost::binary_archive, 
 *	but i found it spend much more dish memory, the serialzie data is three times large than the orginal data.
 *  
 *  USAGE: primitive types can use the binary_oarchive::operator<< and  binary_iarchive::operator>> directly to serialize and deserialize datas, 
 *  for class types, you should define a serialize function like this:
 *    template<class Archive>
 *    void serialize(Archive &ar)
 *    {
 *			ar & m_data1;
 *			ar & m_data2;
 *    }
 *    m_data1 and m_data2 are the members of the class.
 *  
 *  There are examples in the test_binary_archive.h files.
 */

#include <vector>
#include <string>
#include <assert.h>
#include <typeinfo>


#define IS_PRIMITIVE_TYPE(t) ((typeid(t) == typeid(char)) || (typeid(t) == typeid(unsigned char)) || \
								(typeid(t) == typeid(int)) || (typeid(t) == typeid(unsigned int)) || \
								(typeid(t) == typeid(long)) || (typeid(t) == typeid(unsigned long))|| \
								(typeid(t) == typeid(float)) || (typeid(t) == typeid(double))) //||
								//(typeid(t) == typeid(std::string)))


/*
 * input archive
 */
class binary_iarchive
{
public:
	binary_iarchive(void *data, size_t len)
		: m_data (data)
		, m_len (len)
		, m_pos (0)
	{
	}

	template<class T>
	binary_iarchive& operator>>(T &t_)
	{
		(*this) & t_;
		return *this;
	}

	template<class T>
	void operator&(T &t_)
	{
		assert(!IS_PRIMITIVE_TYPE(t_));
		t_.serialize(*this);
	}



	template<class AnyType>
	void operator&(std::vector<AnyType> &data)
	{
		size_t num;
		(*this) & num;
		data.clear();
		for(size_t i = 0; i < num; ++i)
		{
			AnyType item;
			(*this) & item;
			data.push_back(item);
		}
	}

private:

	template<class PrimitiveType>
	void archive_primitive(PrimitiveType& data)
	{
		assert(IS_PRIMITIVE_TYPE(data));
		data = *((PrimitiveType*)((char*)m_data + m_pos));
		m_pos += sizeof(PrimitiveType);
	}

	void *m_data;
	size_t m_len;
	size_t m_pos;
};

/*
 *  output archive
 */
class binary_oarchive
{
public:
	binary_oarchive()
	{
	}

	void *get_buffer() {return (unsigned char*)&m_buffer[0]; }
	size_t get_size() {return m_buffer.size(); }
	
	template<class T>
	binary_oarchive& operator <<(const T &t_)
	{
		(*this) & t_;
		return *this;
	}

	template<class T>
	binary_oarchive& operator<<(T &t_)
	{
		(*this) & t_;
		return *this;
	}

	template<class T>
	void operator&(T &t_)
	{
		assert(!IS_PRIMITIVE_TYPE(t_));
		t_.serialize(*this);
	}


	template<class PrimitiveType>
	void operator&(const PrimitiveType &data)
	{
		assert(IS_PRIMITIVE_TYPE(data));
		unsigned char *start_addr = (unsigned char *)&data;
		for(size_t i = 0; i < sizeof(PrimitiveType); ++i)
		{
			m_buffer.push_back(*(start_addr+i));
		}
	}

	template<class AnyType>
	void operator&(std::vector<AnyType> &data)
	{
		(*this) & data.size();
		for(typename std::vector<AnyType>::iterator it = data.begin(); it != data.end(); ++it)
		{
			(*this) & (*it);
		}
	}


private:
	std::vector<unsigned char> m_buffer;
};


// iarchive
template<>
inline void binary_iarchive::operator&(std::string& data)
{
	data = (char*)m_data + m_pos;
	m_pos += data.length()+1;
}

template<>
inline void binary_iarchive::operator&(char &t_)
{
	archive_primitive(t_);
}

template<>
inline void binary_iarchive::operator&(unsigned char &t_)
{
	archive_primitive(t_);
}

template<>
inline void binary_iarchive::operator&(int &t_)
{
	archive_primitive(t_);
}

template<>
inline void binary_iarchive::operator&(unsigned int &t_)
{
	archive_primitive(t_);
}

template<>
inline void binary_iarchive::operator&(long &t_)
{
	archive_primitive(t_);
}

template<>
inline void binary_iarchive::operator&(unsigned long &t_)
{
	archive_primitive(t_);
}

template<>
inline void binary_iarchive::operator&(float &t_)
{
	archive_primitive(t_);
}

template<>
inline void binary_iarchive::operator&(double &t_)
{
	archive_primitive(t_);
}

// oarchive
template<>
inline void binary_oarchive::operator& (const std::string &data)
{
	unsigned char *start_addr = (unsigned char *)data.c_str();
	for(size_t i = 0; i < data.size() + 1; ++i)
	{
		m_buffer.push_back(*(start_addr+i));
	}
}

template<>
inline void binary_oarchive::operator& (std::string &t_)
{
	(*this) & (const std::string&)t_;
}

// none const

template<>
inline void binary_oarchive::operator&(char &t_)
{
	(*this) & (const char&)t_;
}

template<>
inline void binary_oarchive::operator&(unsigned char &t_)
{
	(*this) & (const unsigned char&)t_;
}

template<>
inline void binary_oarchive::operator&(int &t_)
{
	(*this) & (const int&)t_;
}

template<>
inline void binary_oarchive::operator&(unsigned int &t_)
{
	(*this) & (const unsigned int&)t_;
}

template<>
inline void binary_oarchive::operator&(long &t_)
{
	(*this) & (const long&)t_;
}

template<>
inline void binary_oarchive::operator&(unsigned long &t_)
{
	(*this) & (const unsigned long&)t_;
}

template<>
inline void binary_oarchive::operator&(float &t_)
{
	(*this) & (const float&)t_;
}

template<>
inline void binary_oarchive::operator&(double &t_)
{
	(*this) & (const double&)t_;
}


