/* <!-- copyright */
/*
 * aria2 - The high speed download utility
 *
 * Copyright (C) 2006 Tatsuhiro Tsujikawa
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * In addition, as a special exception, the copyright holders give
 * permission to link the code of portions of this program with the
 * OpenSSL library under certain conditions as described in each
 * individual source file, and distribute linked combinations
 * including the two.
 * You must obey the GNU General Public License in all respects
 * for all of the code used other than OpenSSL.  If you modify
 * file(s) with this exception, you may extend this exception to your
 * version of the file(s), but you are not obligated to do so.  If you
 * do not wish to do so, delete this exception statement from your
 * version.  If you delete this exception statement from all source
 * files in the program, then also delete it here.
 */
/* copyright --> */
#include "Data.h"
#include "MetaEntryVisitor.h"
#include <cstring>
#include <cstdlib> // <-- TODO remove this if strtoll is replaced with Util::parseLLInt()

namespace aria2 {

Data::Data(const unsigned char* data, size_t len, bool number):
  _data(reinterpret_cast<const char*>(data), len),
  number(number) {}

Data::Data(const char* data, size_t len, bool number):
  _data(data, len),
  number(number) {}

Data::Data(const std::string& data, bool number):_data(data), number(number) {}

Data::~Data() {}

const std::string& Data::toString() const {
  return _data;
}

const unsigned char* Data::getData() const {
  if(_data.empty()) {
    return 0;
  } else {
    return reinterpret_cast<const unsigned char*>(_data.c_str());
  }
}

size_t Data::getLen() const {
  return _data.size();
}

int32_t Data::toInt() const {
  return toLLInt();
}

int64_t Data::toLLInt() const {
  return strtoll(_data.c_str(), 0, 10);
}

bool Data::isNumber() const {
  return number;
}

void Data::accept(MetaEntryVisitor* v) const {
  v->visit(this);
}

} // namespace aria2
