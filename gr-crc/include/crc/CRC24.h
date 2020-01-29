/* -*- c++ -*- */
/* 
 * Copyright 2017 <+YOU OR YOUR COMPANY+>.
 * 
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 * 
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifndef INCLUDED_CRC_CRC24_H
#define INCLUDED_CRC_CRC24_H

#include <crc/api.h>
#include <gnuradio/block.h>

namespace gr {
  namespace crc {

    /**
     * @brief Reference class. 
     */
    class CRC_API CRC24 : virtual public gr::block
    {
     public:
      typedef boost::shared_ptr<CRC24> sptr;
      
      /**
       * @brief Return a shared_ptr to a new instance of crc::CRC24.
       * crc::CRC24::make is the public interface for creating new instances.
       */
      static sptr make(int msglength, bool check);
    };

  } // namespace crc
} // namespace gr

#endif /* INCLUDED_CRC_CRC24_H */

