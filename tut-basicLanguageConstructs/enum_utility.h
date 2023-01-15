#ifndef enum_utility_h
#define enum_utility_h
/**
   @brief provide utliy for enums
 **/
#include <iostream>
template<typename T> std::ostream& operator << (typename std::enable_if<
						std::is_enum<T>::value, // FIXME: explore the "is_enum" attribute ... how to use this?
						std::ostream
						>::type& stream, const T& e)
{
  /**
     @return the string-reptation of enums
   **/
  //! SRc: [ https://changkun.de/modern-cpp/en-us/02-usability/]
    return stream << static_cast<typename std::underlying_type<T>::type>(e);
}
template <typename T> constexpr auto operator+(T e) noexcept //! used to autmcially cast enum to undlerying type [https://stackoverflow.com/questions/8357240/how-to-automatically-convert-strongly-typed-enum-into-int]
    -> std::enable_if_t<std::is_enum<T>::value, std::underlying_type_t<T>>
{
  /**
     @return the underlying type (Eg, the integer) reprntign the enum
   **/
    return static_cast<std::underlying_type_t<T>>(e);
}



#endif //! EOF
