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

#ifndef INCLUDED_SQUITTER_SELECT_SQUITTER_MUX_IMPL_H
#define INCLUDED_SQUITTER_SELECT_SQUITTER_MUX_IMPL_H

#include <squitter_select/squitter_mux.h>
#include <string.h>
#include <stdio.h>

#define P_LEN 107

namespace gr {
  namespace squitter_select {

    class squitter_mux_impl : public squitter_mux
    {
     private:
     pmt::pmt_t d_msg;

     protected:
      int calculate_output_stream_length(const gr_vector_int &ninput_items);

     public:

     void set_time(pmt::pmt_t msg) {d_msg = msg;}
     pmt::pmt_t msg() const { return d_msg; }
     
     squitter_mux_impl(const std::string lengthname);
      ~squitter_mux_impl();

      // Where all the action really happens
      int work(int noutput_items,
		       gr_vector_int &ninput_items,
		       gr_vector_const_void_star &input_items,
		       gr_vector_void_star &output_items);
    };

  } // namespace squitter_select
} // namespace gr

#endif /* INCLUDED_SQUITTER_SELECT_SQUITTER_MUX_IMPL_H */

