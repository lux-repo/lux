// compile time string constant
// support beyond c++11
// see https://zhuanlan.zhihu.com/p/377145104

#pragma once
#include <cstddef>

template <char... C>
struct MPString
{
    constexpr static std::size_t N = sizeof...(C) + 1;
    constexpr static const char data[N] = { C..., 0 };
};

template <std::size_t M, std::size_t N>
constexpr char get_char_from_str(const char(&arr)[N])
{
    return arr[M < N ? M : N - 1];
}

template<char... C>
auto make_mpstring(MPString<C...>)
->MPString<C...>;

template <char... C1, char C, char... C2>
auto make_mpstring(MPString<C1...>, MPString<C>, MPString<C2>...)
->decltype(make_mpstring(MPString<C1..., C>{}, MPString<C2>{}...));

template<char... C1, char... C2>
auto make_mpstring(MPString<C1...>, MPString<'\0'>, MPString<C2>...)
->MPString<C1...>;

template<char... C>
auto auto_split_string(MPString<C...>)
->decltype(make_mpstring(MPString<C>{}...));

#define MakeCharIndex(n,str)        get_char_from_str<0x##n##0>(str),get_char_from_str<0x##n##1>(str),\
                                    get_char_from_str<0x##n##2>(str),get_char_from_str<0x##n##3>(str),\
                                    get_char_from_str<0x##n##4>(str),get_char_from_str<0x##n##5>(str),\
                                    get_char_from_str<0x##n##6>(str),get_char_from_str<0x##n##7>(str),\
                                    get_char_from_str<0x##n##8>(str),get_char_from_str<0x##n##9>(str),\
                                    get_char_from_str<0x##n##a>(str),get_char_from_str<0x##n##b>(str),\
                                    get_char_from_str<0x##n##c>(str),get_char_from_str<0x##n##d>(str),\
                                    get_char_from_str<0x##n##e>(str),get_char_from_str<0x##n##f>(str)

#define MakeCharIndex32_L(str)      MakeCharIndex(0,str),MakeCharIndex(1,str)
#define MakeCharIndex32_H(str)      MakeCharIndex(2,str),MakeCharIndex(3,str)
#define MakeCharIndexSequence(str)  MakeCharIndex32_L(str),MakeCharIndex32_H(str)

#define MAKE_MPSTRING(str)          decltype(auto_split_string(MPString<MakeCharIndexSequence(str)>{}))