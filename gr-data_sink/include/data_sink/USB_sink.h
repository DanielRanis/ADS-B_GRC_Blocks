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


#ifndef INCLUDED_DATA_SINK_USB_SINK_H
#define INCLUDED_DATA_SINK_USB_SINK_H

#include <data_sink/api.h>
#include <gnuradio/sync_block.h>

namespace gr {
  namespace data_sink {

    /**
     * @brief Reference class.
     */
    class DATA_SINK_API USB_sink : virtual public gr::sync_block
    {
     public:
      typedef boost::shared_ptr<USB_sink> sptr;

      /**
       * @brief Return a shared_ptr to a new instance of data_sink::USB_sink.
       * data_sink::USB_sink::make is the public interface for creating new instances.
       */
      static sptr make(const int vendorID, const int productID, bool test);
    };

  } // namespace data_sink
} // namespace gr

#endif /* INCLUDED_DATA_SINK_USB_SINK_H */

