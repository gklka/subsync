#ifndef __UTF8_H__
#define __UTF8_H__

#include <cstdint>
#include <string>


namespace std
{
	template<>
	struct char_traits<uint32_t>
	{
		typedef uint32_t char_type;
		typedef uint32_t int_type;
		typedef streamoff off_type;
		typedef streampos pos_type;
		typedef mbstate_t state_type;

		static void assign(char_type& r, const char_type& a) noexcept { r = a; }
		static bool eq(char_type a, char_type b) noexcept { return a == b; }
		static bool lt(char_type a, char_type b) noexcept { return a < b; }
		static int compare(const char_type* s1, const char_type* s2, size_t n)
		{
			for (size_t i = 0; i < n; ++i)
			{
				if (s1[i] < s2[i]) return -1;
				if (s1[i] > s2[i]) return 1;
			}
			return 0;
		}
		static size_t length(const char_type* s)
		{
			size_t n = 0;
			while (s[n] != 0) ++n;
			return n;
		}
		static const char_type* find(const char_type* s, size_t n, const char_type& a)
		{
			for (size_t i = 0; i < n; ++i)
				if (s[i] == a) return s + i;
			return nullptr;
		}
		static char_type* move(char_type* dst, const char_type* src, size_t n)
		{
			if (dst < src)
				for (size_t i = 0; i < n; ++i) dst[i] = src[i];
			else if (dst > src)
				for (size_t i = n; i > 0; --i) dst[i - 1] = src[i - 1];
			return dst;
		}
		static char_type* copy(char_type* dst, const char_type* src, size_t n)
		{
			for (size_t i = 0; i < n; ++i) dst[i] = src[i];
			return dst;
		}
		static char_type* assign(char_type* s, size_t n, char_type a)
		{
			for (size_t i = 0; i < n; ++i) s[i] = a;
			return s;
		}
		static int_type not_eof(int_type c) noexcept { return c == eof() ? 0 : c; }
		static char_type to_char_type(int_type c) noexcept { return char_type(c); }
		static int_type to_int_type(char_type c) noexcept { return int_type(c); }
		static bool eq_int_type(int_type a, int_type b) noexcept { return a == b; }
		static int_type eof() noexcept { return static_cast<int_type>(-1); }
	};
}


class Utf8
{
	public:
		class iterator
		{
			public:
				iterator();
				iterator(const std::string &str);
				iterator(const char *str);

				uint32_t operator* () const;

				iterator &operator++ ();
				iterator &operator-- ();

				iterator operator++ (int);
				iterator operator-- (int);

				iterator &operator+= (size_t len);
				iterator &operator-= (size_t len);

				bool operator== (const iterator &it) const;
				bool operator!= (const iterator &it) const;

				// codepoints left to the end of the string
				size_t size() const;

				// current codepoint size
				unsigned cpSize() const;

				uint32_t toLower() const;
				uint32_t toUpper() const;

				bool isLower() const;
				bool isUpper() const;

				const char *getRawData() const;
				unsigned getiteratorSize() const;

				static const uint32_t invalid;

			private:
				const uint8_t *m_ptr;
		};

	public:
		static std::basic_string<uint32_t> decode(const std::string &str);
		static std::string encode(uint32_t codePoint);
		static std::string encode(const std::basic_string<uint32_t> &codePoints);

		static std::string toLower(const std::string &str);
		static std::string toUpper(const std::string &str);

		static std::string reverse(const std::string &str);

		static std::string substr(const iterator &begin, const iterator &end);

		static size_t size(const std::string &str);
		static size_t size(const char *str);

		static bool validate(const std::string &str);
		static bool validate(const char *str);

		static std::string escape(const std::string &str);
		static std::string escape(const char *str);
};

#endif
