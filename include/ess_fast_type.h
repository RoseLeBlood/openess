/****************************************************************************
 * Copyright (C) 2019 by Anna Sopdia Schröck                                *
 *                                                                          *
 * This file is part of ess.                                                *
 *                                                                          *
 *   ess is free software: you can redistribute it and/or modify it         *
 *   under the terms of the GNU Lesser General Public License as published  *
 *   by the Free Software Foundation, either version 3 of the License, or   *
 *   (at your option) any later version.                                    *
 *                                                                          *
 *   ess is distributed in the hope that it will be useful,                 *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          *
 *   GNU Lesser General Public License for more details.                    *
 *                                                                          *
 *   You should have received a copy of the GNU Lesser General Public       *
 *   License along with Box.  If not, see <http://www.gnu.org/licenses/>.   *
 ****************************************************************************/


/**
 * @file ess_fast_type.h
 * @author Anna Sopdia Schröck
 * @date 08 März 2019
 *
 *
 */
 /**
 * @addtogroup ess
 * @{
 */
 #ifndef FAST_TYPE_HPP
 #define FAST_TYPE_HPP

 #include <stdint.h>
 #include <cstddef>

 class fbit {
 public:
     union {
         unsigned char bit : 1;
     };
     fbit() : bit(0) { }
     fbit(bool b) { bit = b ? 1 : 0; }
     fbit(const fbit& b) : bit(b.bit) { }

     operator bool() { return bit == 1; }
     fbit& operator = (const fbit& other) {
         bit = other.bit;
					return *this;
     }
     bool operator == (const fbit& other) {
         return bit == other.bit;
     }
     bool operator != (const fbit& other) {
         return bit != other.bit;
     }

     void flip() { bit = (bit ==1) ? 0 : 1; }
 };



template <size_t Bits, typename TBaseType>
class fast_type {
public:
   using self_type = fast_type<Bits, TBaseType>;
   using value_type = TBaseType;
   using bit_type = fbit;

   union {
       value_type Value;
       bit_type bits[Bits];
   };
   explicit fast_type(value_type v) : Value(v) {}
   fast_type(const fast_type& c) { Value = c.Value; }

   unsigned int count() {
       unsigned int i;
       for(int j = 0; j < Bits; j++)
           i += bits[i].bit;
       return i;
   }
   unsigned int zeros() {
       return Bits-count();
   }
   unsigned int set(size_t pos, bool p) {
       bits[pos].bit = p ? 1 : 0;
  			return bits[pos];
   }
   size_t size() {
       return Bits;
   }

   value_type& operator [] (const size_t p) {
       return bits[p];
   }
   self_type& operator = (value_type& v) {
       Value = v; return *this;
   }
   self_type& operator = (self_type& other) {
       Value = other.Value; return *this;
   }
   bool operator == (self_type& other) {
       return Value == other.Value;
   }
   bool operator != (self_type& other) {
       return Value != other.Value;
   }
   bool operator <= (self_type& other) {
       return Value <= other.Value;
   }
   bool operator >= (self_type& other) {
       return Value >= other.Value;
   }
   bool operator < (self_type& other) {
       return Value < other.Value;
   }
   bool operator > (self_type& other) {
       return Value > other.Value;
   }

   self_type& operator += (self_type& other) {
       Value += other.Value; return *this;
   }
   self_type& operator -= (self_type& other) {
       Value -= other.Value; return *this;
   }
   self_type& operator *= (self_type& other) {
       Value *= other.Value; return *this;
   }
   self_type& operator &= (self_type& other) {
       Value &= other.Value; return *this;
   }
   self_type& operator |= (self_type& other) {
       Value |= other.Value; return *this;
   }
   self_type& operator ^= (self_type& other) {
       Value ^= other.Value; return *this;
   }
   self_type& operator <<= (self_type& other) {
       Value <<= other.Value; return *this;
   }
   self_type& operator >>= (self_type& other) {
       Value >>= other.Value; return *this;
   }
   self_type& operator /= (self_type& other) {
       Value /= other.Value; return *this;
   }
   self_type& operator += (value_type& v) {
       Value += v; return *this;
   }
   self_type& operator -= (value_type& v) {
       Value -= v; return *this;
   }
   self_type& operator *= (value_type& v) {
       Value *= v; return *this;
   }
   self_type& operator /= (value_type& v) {
       Value /= v; return *this;
   }
   self_type& operator <<= (value_type& v) {
       Value <<= v; return *this;
   }
   self_type& operator >>= (value_type& v) {
       Value >>= v; return *this;
   }
   self_type& operator - ( const self_type& rhs) {
       return self_type(*this) -= rhs;
   }
   self_type& operator + ( const self_type& rhs) {
       return self_type(*this) += rhs;
   }
   self_type& operator * ( const self_type& rhs) {
       return self_type(*this) *= rhs;
   }
   self_type& operator / ( const self_type& rhs) {
       return self_type(*this) /= rhs;
   }
   self_type& operator << ( const self_type& rhs) {
       return self_type(*this) <<= rhs;
   }
   self_type& operator >> ( const self_type& rhs) {
       return self_type(*this) >>= rhs;
   }
   self_type& operator | ( const self_type& rhs) {
       self_type result = self_type(*this);
       result.Value |= rhs.Value;
       return result;
   }
   self_type& operator ^ ( const self_type& rhs) {
       self_type result = self_type(*this);
       result.Value ^= rhs.Value;
       return result;
   }
   self_type& operator & ( const self_type& rhs) {
       self_type result = self_type(*this);
       result.Value &= rhs.Value;
       return result;
   }
   self_type& operator ~ () {
       self_type result = self_type(*this);
       result.Value = ~result.Value;
       return result;
   }

   self_type& operator ++ () {
       Value++; return *this;
   }
   self_type& operator -- () {
       Value--; return *this;
   }
};

using fuint8_t = fast_type<8, uint8_t>;
using fuint16_t = fast_type<16, uint16_t>;
using fuint32_t = fast_type<32, uint32_t>;
using fuint64_t = fast_type<64, uint64_t>;

using fint8_t = fast_type<8,   int8_t>;
using fint16_t = fast_type<16, int16_t>;
using fint32_t = fast_type<32, int32_t>;
using fint64_t = fast_type<64, int64_t>;


 #endif
