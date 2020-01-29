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


#ifndef INCLUDED_SQUITTER_MUX_SQUITTER_OUTPUT_H
#define INCLUDED_SQUITTER_MUX_SQUITTER_OUTPUT_H

#include <squitter_mux/api.h>
#include <gnuradio/block.h>

namespace gr {
  namespace squitter_mux {

    /**
     * @brief Reference class. 
     */
    class SQUITTER_MUX_API squitter_output : virtual public gr::block
    {
     public:
      typedef boost::shared_ptr<squitter_output> sptr;

      /**
       * @brief Return a shared_ptr to a new instance of data_sink::USB_sink.
       * data_sink::USB_sink::make is the public interface for creating new instances.
       */
      static sptr make(const float alpha_param,
                       const int pw_param,
                       const int sr_param,
                       const int span_param,
                       const int sps_param,
                       const int imx_param,
                       const int md,
                       const int testmsg);
      
    };

  } // namespace squitter_mux
} // namespace gr

#endif /* INCLUDED_SQUITTER_MUX_SQUITTER_OUTPUT_H */

